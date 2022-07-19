/**
    @file HierarchieBuilder.cpp
    @brief Définition des fonctions membres de la classe HierarchieBuilder.
    @author Ophélie Delattre / Simon Lepage
    @version v3
    @date 30 avril 2020
    @bug aucun détecté
    @warning COMPILE
    @note Aucune
*/
#include "../header/CompteManager.h"

int HierarchieBuilder::idcompte = 0;

CompteHierarchie* HierarchieBuilder::creerEmpty() noexcept{
    CompteHierarchie* racine = new CompteVirtuel("Racine", idcompte);
    idcompte++;
    racine->poste = &Racine::getInstance();
    return racine;
}

CompteHierarchie* HierarchieBuilder::creerFils(std::string _nom, Type _t, Poste _p){
    CompteHierarchie* c = nullptr;

    Originator *o = CompteManager::getInstance().getOriginator();
    switch (_t) {
        case REEL:
            c = new CompteReel(_nom,idcompte);
            o->setSolde(0,0);
            c->saveState(*o);
            o->setSolde(0);
            c->saveState(*o); //un memento pour le solde actuel
            break;
        case VIRTUEL:
            c = new CompteVirtuel(_nom,idcompte);
            break;
        default:
            throw ExceptionHierarchie("Type Inconnu.", ExceptionHierarchie::CodeExcepHierarchie::TYPE_EXC_H);
            break;
    }
    switch (_p) {
        case ACTIF:
            c->poste = &Actif::getInstance();
            break;
        case PASSIF:
            c->poste = &Passif::getInstance();
            break;
        case DEPENSE:
            c->poste = &Depense::getInstance();
            break;
        case RECETTE:
            c->poste = &Recette::getInstance();
            break;
        default:
            throw ExceptionHierarchie("Poste Inconnu.", ExceptionHierarchie::CodeExcepHierarchie::POSTE_EXC_H);
            break;
    }
    return c;
}

CompteHierarchie* HierarchieBuilder::creerAvecFichier(std::string _path){
    Originator *o = CompteManager::getInstance().getOriginator();

    idcompte = 0;

    // Ouverture du fichier
    QFile qfile(QString::fromStdString(_path));
    if (!qfile.open(QIODevice::ReadOnly))
    {
        ExceptionFichier("[!]Impossible d'ouvrir le fichier suivant en lecture : " + _path,
                                  ExceptionFichier::CodeExcepFichier::UFND_EXC_F);
    }

    QDomDocument xml;
    xml.setContent(&qfile);
    qfile.close();

    // Initialisation des variables
    CompteHierarchie* racine = creerEmpty();
    CompteHierarchie* temp = nullptr;
    stack<CompteHierarchie*> peres_stack;
    set<int> deja_visite;

    string nom, p;
    int id;
    time_t date;
    double solde;

    map<std::string, const PosteCompte*> postes = {
        {"R", &Recette::getInstance()},
        {"D", &Depense::getInstance()},
        {"P", &Passif::getInstance()},
        {"A", &Actif::getInstance()}
    };

    // save > CompteManager > Racine > Premier fils de la racine
    QDomNode actual = xml.documentElement().firstChild().firstChild().firstChild();
    peres_stack.push(racine);
    QDomElement memento;


    // Tant qu'on n'est pas remonté à la racine
    while(!actual.isNull() && actual.toElement().attribute(QString("nom"), QString("")).toStdString() != "Racine"){
        nom = actual.toElement().attribute(QString("nom"), QString("")).toStdString();
        p = actual.toElement().attribute(QString("poste"), QString("")).toStdString();
        id = actual.toElement().attribute(QString("id"), QString("")).toInt();

        // Si on est sur un compte réel
        if(actual.toElement().tagName() == "CompteReel"){
            // Crée le compte
            temp = new CompteReel(nom, id);
            temp->poste = postes[p];
            idcompte = (id > idcompte? id : idcompte);

            // Récupère les memento
            memento = actual.firstChild().toElement();
            while(!memento.isNull()){
                date = memento.attribute(QString("date"), QString("0")).toLong();
                solde = memento.attribute(QString("solde"), QString("0")).toDouble();

                o->setSolde(solde, date);
                temp->saveState(*o);

                memento = memento.nextSibling().toElement();
            }
            // Ajoute le compte à son père
            peres_stack.top()->ajouterFils(temp);

            // Si le noeud n'a pas de frère, on remonte
            if(actual.nextSibling().isNull()){
                actual = actual.parentNode();
                peres_stack.pop();
            } else {
                actual = actual.nextSibling();
            }

        // Si on est sur un compte virtuel
        } else {
            // Première fois qu'on descend sur ce compte
            if(deja_visite.find(id) == deja_visite.end()){
                deja_visite.insert(id);

                // On instancie le compte
                temp = new CompteVirtuel(nom, id);
                temp->poste = postes[p];
                idcompte = (id > idcompte? id : idcompte);

                // Pour la racine, pere_stack peut être empty
                if(!peres_stack.empty()) peres_stack.top()->ajouterFils(temp);

                // Si le noeud a des fils
                if(actual.hasChildNodes()){
                    peres_stack.push(temp);
                    actual = actual.firstChild();
                // Si le noeud n'a pas de fils, mais des frères
                } else if (!actual.nextSibling().isNull()){
                    actual = actual.nextSibling();
                // Si le noeud n'a ni fils ni frère
                } else {
                    actual = actual.parentNode();
                    peres_stack.pop();
                }
            // On remonte d'un de ses fils
            } else {
                // Si pas de sibling, on remonte
                if(actual.nextSibling().isNull()){
                    actual = actual.parentNode();
                    if(!peres_stack.empty()) peres_stack.pop();
                // Sinon, on passe au compte suivant
                } else {
                    actual = actual.nextSibling();
                }
            }
        }
    }

    // Ici, idcompte est le plus grand id de compte qui a été lu. On l'incrémente pour obtenir le premier id disponible.
    idcompte++;
    return racine;
}
