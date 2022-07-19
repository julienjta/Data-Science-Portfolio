/**
    @file CompteManager.cpp
    @brief Définition des fonctions membres de la classe CompteManager.
    @author Ophélie Delattre/ Simon Lepage
    @version v2
    @date 4 mai 2020
    @bug aucun détecté
    @warning COMPILE
*/

#include "../header/CompteManager.h"
#include <ctime>

const string DEFAULT_SAVE_PATH = QDir::currentPath().toStdString()+ "/default_backup.business";

CompteManager CompteManager::instance;
int CompteManager::init;

CompteManager::CompteManager() noexcept{
    racine = HierarchieBuilder::creerEmpty();

    // Init attributs CompteManager
    o = new Originator();
    o->setSolde(0,0);
    init = 1;
    nb_cloture = 1;
    path = DEFAULT_SAVE_PATH; // Nom é  changer.
}


CompteManager::~CompteManager(){
    // Libération mémoire
    delete o;
    VisiteurFree VF;
    racine->accepte(VF);
}


CompteHierarchie* CompteManager::getCompte(int _id)const{
    VisiteurRecherche VR(_id);
    racine->accepte(VR);
    CompteHierarchie* result = VR.getResultat();

    if(result == nullptr){
        throw ExceptionHierarchie("[!]Le compte " + to_string(_id) + "n'existe pas.",
                                  ExceptionHierarchie::CodeExcepHierarchie::IDNF_EXC_H);
    } else {
        return result;
    }
};


CompteHierarchie* CompteManager::getPere(CompteHierarchie* _c) const noexcept{
    VisiteurPere VP(_c);
    racine->accepte(VP);

    return VP.getResultat();
}


void CompteManager::affiche(QTreeWidget* const _arbre, QString const& _devise) const noexcept{
    _arbre->clear();
    _arbre->setCurrentItem(NULL);
    _arbre->setItemSelected(NULL, false);

    VisiteurAffichage VA(_arbre,_devise);
    racine->accepte(VA);
}

list<CompteHierarchie*> CompteManager::getListeComptePoste(Poste _p)const{
    VisiteurPoste VP(_p);
    racine->accepte(VP);
    return VP.getResultat();
}


void CompteManager::getListeComptes(QStringList* _liste_compte,list<int>* _liste_id,int const _seul_compte_reel)const noexcept
{
    _liste_compte->clear();
    _liste_id->clear();

    VisiteurListeCompte VLC(_liste_compte,_liste_id,_seul_compte_reel);
    racine->accepte(VLC);
}


void CompteManager::ajouterFils(int _id_pere, const string& _nom_fils, Type _t, Poste _p){
    CompteHierarchie* pere = getCompte(_id_pere);
    CompteHierarchie *c = HierarchieBuilder::creerFils(_nom_fils, _t, _p);
    if(pere->getPoste() == RACINE){
        pere->ajouterFils(c);
        HierarchieBuilder::idcompte++;

    } else if (pere->getPoste() == _p && pere->getType() == VIRTUEL){

        pere->ajouterFils(c);
         HierarchieBuilder::idcompte++;

    }else {
        throw ExceptionHierarchie("[!]Impossible d'ajouter ce compte fils a ce compte.",
                                  ExceptionHierarchie::CodeExcepHierarchie::RULE_EXC_H);
    }
    //pour la gestion d'actif/passif pour capitaux propre voir dans ajouter windows
}


void CompteManager::supprimerCompte(int _id){
    //  id      Compte
    //  0       Racine
    if(_id ==0 )
        throw ExceptionHierarchie("[!]Ce compte est necessaire au bon fonctionnement de l'application et ne peut etre supprime.",ExceptionHierarchie::CodeExcepHierarchie::RULE_EXC_H);
    CompteHierarchie* c = getCompte(_id);
    // Supprime le compte
    c->supprimerCompte();
};


void CompteManager::deplacerFils(int _id_fils, int _id_futur_pere){
    if(_id_fils == _id_futur_pere){
        throw ExceptionHierarchie("[!]Impossible de déplacer un compte sous lui-même.",
                                    ExceptionHierarchie::CodeExcepHierarchie::DSELF_EXC_H);
    }

    // Récupérer pointeurs sur fils et futur père.
    CompteHierarchie* fils = getCompte(_id_fils);
    CompteHierarchie* futur_pere = getCompte(_id_futur_pere);

    // Vérification de poste et de type
    if(fils->getPoste() != futur_pere->getPoste() && futur_pere->getPoste() != RACINE){
        throw ExceptionHierarchie("[!]Impossible de déplacer le compte (futur père incompatible).",
                                  ExceptionHierarchie::CodeExcepHierarchie::RULE_EXC_H);
    } else if (futur_pere->getType() == Type::REEL){
        throw ExceptionHierarchie("[!]Impossible de déplacer le compte (futur père est réel).",
                                  ExceptionHierarchie::CodeExcepHierarchie::FLSR_EXC_H);
    }

    // Vérifier que le futur père n'est pas un fils du compte é  déplacer
    CompteHierarchie* temp_pere = futur_pere;
    // nullptr = le visiteur n'a pas trouvé de père (aka on l'a appelé sur la racine)
    while((temp_pere = getPere(temp_pere))){
        if(temp_pere == fils)
            throw ExceptionHierarchie("[!]Impossible de déplacer le compte. Le futur père est un fils du compte é  déplacer.",
                                            ExceptionHierarchie::CodeExcepHierarchie::DSON_EXC_H);
    }

    // Si les types sont cohérents, retirer le fils du père, et l'ajouter dans le nouveau
    CompteHierarchie* pere = getPere(fils);
    pere->supprimerFils(fils);
    futur_pere->ajouterFils(fils);
}


void CompteManager::charger(const string& _file){
    // On crée une hiérarchie suivant le fichier qu'on a reçu.
    // On essaye de charger la hiérarchie.
    // Si HierarchieBuilder léve une exception, on ne veut pas perdre la racine ni changer path.
    CompteHierarchie* temp_racine = HierarchieBuilder::creerAvecFichier(_file);

    // S'il n'y a pas eu d'exception on efface la hiérarchie actuelle et on la remplace par la nouvelle
    VisiteurFree VF;
    racine->accepte(VF);
    racine = temp_racine;

    // On charge les autres paramétres du CompteManager
    QFile qfile(QString::fromStdString(_file));
    if (!qfile.open(QIODevice::ReadOnly))
    {
        throw ExceptionFichier("[!]Impossible d'ouvrir le fichier suivant en lecture : " + _file,
                                  ExceptionFichier::CodeExcepFichier::UFND_EXC_F);
    }

    QDomDocument xml;
    xml.setContent(&qfile);
    qfile.close();

    QDomElement CM_elt = xml.documentElement().firstChild().toElement();

    path = _file;
    init = CM_elt.attribute(QString("init"), QString("1")).toInt();
    nb_cloture = CM_elt.attribute(QString("nb_cloture"), QString("1")).toInt();

    TransactionManager::getInstance().charger(_file);
}


void CompteManager::setPath(const string& _file) noexcept{
    // Hypothèse : chemin passé en argument est valide ?
    path = _file;
}

string const& CompteManager::getPath() const noexcept
{
    return path;
}

bool CompteManager::isDefaultPath() const noexcept
{
    return path == DEFAULT_SAVE_PATH;
}

void CompteManager::sauver(const string& _file) {
    // Si on passe une chaîne vide,
    if(_file != "") setPath(_file);

    // On ouvre un fichier
    QFile qfile(QString::fromStdString(path));
    if(!qfile.open(QIODevice::WriteOnly)){
        throw ExceptionFichier("[!]Impossible d'ouvrir le fichier suivant en écriture : " + path,
                           ExceptionFichier::CodeExcepFichier::UFND_EXC_F);
    }

    QXmlStreamWriter xml(&qfile);

    // Paramètres du QXmlStreamWriter
    xml.setCodec(QTextCodec::codecForName("UTF-8"));
    xml.setAutoFormatting(true);

    // On écrit l'en-tête
    xml.writeStartDocument(QString("1.0"));
    xml.writeStartElement("save");


    //============SAUVEGARDE CM============//
    xml.writeStartElement("CompteManager");

    // On stocke les réglages du CM
    xml.writeAttribute(QString("init"), QString::number(init));
    xml.writeAttribute(QString("nb_cloture"), QString::number(nb_cloture));


    set<CompteHierarchie*> deja_visite;
    stack<CompteHierarchie*> peres;
    CompteHierarchie* actuel = racine;
    list<Memento*> m;
    bool found = false;

    while(actuel != nullptr){
        if(actuel->getType() == REEL)
        {
            // actuel est un compte réel
            // On ne descend dans un compte réel depuis son parent que s'il n'a jamais été visité.
            xml.writeStartElement("CompteReel");
            xml.writeAttribute(QString("nom"), QString::fromStdString(actuel->getNom()));
            xml.writeAttribute(QString("poste"), QString::fromStdString(actuel->poste->getLetter()));
            xml.writeAttribute(QString("id"), QString::number(actuel->getId()));

            if( !(m = actuel->getMementos()).empty()){
                for(auto elt : m){
                    xml.writeStartElement("Memento");

                    xml.writeAttribute(QString("date"), QString::number(elt->getDate()));
                    xml.writeAttribute(QString("solde"), QString::number(elt->getSolde()));
                    xml.writeEndElement(); // Memento
                }
            }

            xml.writeEndElement(); // CompteReel
            // On ajoute é  la liste des comptes déjé  sauvés
            deja_visite.insert(actuel);

            // On remonte
            actuel = peres.top();
            peres.pop();
        }
        else
        {
            // Si c'est la première fois qu'on voit actuel.
            if(deja_visite.find(actuel) == deja_visite.end()){
                xml.writeStartElement("CompteVirtuel");
                xml.writeAttribute(QString("nom"), QString::fromStdString(actuel->getNom()));
                xml.writeAttribute(QString("poste"), QString::fromStdString(actuel->poste->getLetter()));
                xml.writeAttribute(QString("id"), QString::number(actuel->getId()));

                deja_visite.insert(actuel);
            }

            // On parcourt les fils
            found = false;
            for(auto fils : actuel->getFils()){
                // Si on n'a encore jamais vu celui-ci
                if(deja_visite.find(fils) == deja_visite.end()){
                    // On empile le père avant de descendre
                    peres.push(actuel);
                    actuel = fils;
                    found = true;
                    break;
                }
            }

            // Si on arrive ici c'est qu'on a déjé  exploré tous les fils de l'élément actuel. On remonte.
           if(!found) {
               xml.writeEndElement();
               if(!peres.empty()){
                   actuel = peres.top();
                   peres.pop();
               } else {
                   actuel = nullptr;
               }
           }
        }
    }

    // On ferme presque la balise CompteManager et appelle la sauvegarde du TM
    xml.writeEndElement();



    //============SAUVEGARDE TM============//
    TransactionManager::getInstance().sauver(&xml);

    // On ferme les balises et le QFile.
    xml.writeEndElement();
    xml.writeEndDocument();

    qfile.flush();
    qfile.close();

}

void CompteManager::cloturer(CompteHierarchie *resultat){
    time_t date;
    std::list<CompteHierarchie*> liste_comptes;
    std::string reference_transaction;
    std::string memo;
    std::string nom;

    // On récupére les comptes de dépense
    VisiteurPoste VP(DEPENSE);
    racine->accepte(VP);
    liste_comptes = VP.getResultat();

    // On crée une transaction qui crédite tous les comptes dépense de leur solde
    // Et débite Résultat de la somme
    double somme = 0., solde = 0;
    TransactionManager& tm = TransactionManager::getInstance();

    std::list<Operation*> liste_op;
    for(auto elt : liste_comptes)
    {
        solde = elt->getDernierMemento()->getSolde();
        if(!tool::double_equal(solde,0.))
        {
            somme += solde;
            tm.ajouterOperation(&liste_op, elt, 0., solde);
        }
    }
    // RECUPERER UN POINTEUR SUR le CompteChoisi pour faire la cloture
    if (!tool::double_equal(somme,0.)){
         tm.ajouterOperation(&liste_op, resultat, somme, 0.);
    }

    if (!liste_op.empty()){
        // Créer la transaction
        date = std::time(nullptr);
        reference_transaction= "CLOTURE D "+to_string(nb_cloture);
        memo = "Cloture";
        tm.ajouterTransaction(date, reference_transaction, memo, liste_op);
    }

    // On récupére les comptes de recette
    VP.changePoste(RECETTE);
    racine->accepte(VP);
    liste_comptes = VP.getResultat();

    // On crée une transaction qui débite tous les comptes recette de leur solde
    // Et crédite Résultat de la somme
    liste_op.clear();
    somme = 0.;
    for(auto elt : liste_comptes)
    {
        solde = elt->getDernierMemento()->getSolde();
        if(!tool::double_equal(solde,0.))
        {
            somme += solde;
            tm.ajouterOperation(&liste_op, elt, solde, 0.);
        }
    }

    if (!tool::double_equal(somme,0.)){
        tm.ajouterOperation(&liste_op, resultat, 0., somme);
    }
    if (!liste_op.empty()){
        date = std::time(nullptr);
        reference_transaction= "CLOTURE R "+to_string(nb_cloture);
        memo = "Cloture";

        tm.ajouterTransaction(date, reference_transaction, memo, liste_op);

    }
        // Finalement, on transfére le résultat sur excédent ou déficit
        solde = getSolde(resultat->getId());
        liste_op.clear();
     if (tool::double_equal(solde,0.)){
       nb_cloture++;
       return;
     }
        tm.ajouterOperation(&liste_op, resultat,solde,0.);


    if (solde>0){
        VisiteurRecherche VR("Excedent");
        racine->accepte(VR);
        CompteHierarchie* excedent = VR.getResultat();
        if (excedent==nullptr){
            excedent = new CompteReel("Excedent", HierarchieBuilder::idcompte);
            excedent->poste = &Passif::getInstance();
            o->setSolde(0);
            excedent->saveState(*o); //un memento pour le dernier rapprochement
           excedent->saveState(*o); //un memento pour le solde actuel
            HierarchieBuilder::idcompte++;
            racine->ajouterFils(excedent);
        }else if (excedent->getType()==VIRTUEL || excedent->getPoste()!=PASSIF){
            throw ExceptionHierarchie("[!]Ce compte ne peut pas étre un compte Excedent.",
                                      ExceptionHierarchie::CodeExcepHierarchie::EXCE_EXC_H);
        }
        tm.ajouterOperation(&liste_op, excedent, 0., solde);
    }else{
        VisiteurRecherche VR("Deficit");
        racine->accepte(VR);
        CompteHierarchie* deficit = VR.getResultat();
        if (deficit==nullptr){
            deficit = new CompteReel("Deficit", HierarchieBuilder::idcompte);
            deficit->poste = &Passif::getInstance();
            o->setSolde(0);
            deficit->saveState(*o); //un memento pour le dernier rapprochement
            deficit->saveState(*o); //un memento pour le solde actuel
            HierarchieBuilder::idcompte++;
            racine->ajouterFils(deficit);
        }else if (deficit->getType()==VIRTUEL || deficit->getPoste()!=PASSIF){
            throw ExceptionHierarchie("[!] Ce compte ne peut pas être un compte Deficit.",
                                      ExceptionHierarchie::CodeExcepHierarchie::DEFI_EXC_H);
        }
        tm.ajouterOperation(&liste_op, deficit, 0., solde );
    }
    // Créer la transaction
    date = std::time(nullptr);
    reference_transaction="CLOTURE_BILAN"+to_string(nb_cloture);
    memo = "Cloture";
    tm.ajouterTransaction(date, reference_transaction, memo, liste_op);
    nb_cloture++;
}


//récupérer exception si on veut rapprocher un compte reel (exception du au undo)
void CompteManager::rapprocherCompte(int _id){
    list<Transaction*> liste_transaction;
    CompteHierarchie* c = getCompte(_id);
    try {
       liste_transaction = TransactionManager::getInstance().getListeTransactionsParValide(_id,false);
    } catch (Exception &e) {
        //alors c'est que tout ces opérations ont été rapprochée, on change juste dernier rapprochement
        //on récupère le solde actuel et le met en dernier raprrochement puis en solde actuel
        c->undo(o);
        o->setSolde(o->getSolde());
        c->saveState(*o);
        c->saveState(*o);
        return;
    }
    //sinon on parcout les transaction valides
    for (list<Transaction*>::iterator iterator_transaction=liste_transaction.begin();iterator_transaction!=liste_transaction.end();iterator_transaction++){

        (*iterator_transaction)->setValide(true);
    }

    //on récupère le solde actuel et le met en dernier raprrochement puis en solde actuel
    c->undo(o);
    o->setSolde(o->getSolde());
    c->saveState(*o);
    c->saveState(*o);
}
//interface ne pas oublier un undo sur le solde actuel rajouter un memento pour le dernier rapprochement puis remettre le solde actuel

double CompteManager::getSolde(int _id) {
    VisiteurGetSolde VS=VisiteurGetSolde();
    CompteHierarchie* c = getCompte(_id);

    c->accepte(VS);
    return VS.getSolde();
}


void CompteManager::crediterCompte(int _id, double montant){
    CompteHierarchie* c = getCompte(_id);
    //enleve le dernier memento
    c->undo(o);
    double tmp = o->getSolde();
    c->poste->crediter(&tmp, montant);
    //modifie solde
    o->setSolde(tmp);
    //remet memento
    c->saveState(*o);
}


void CompteManager::debiterCompte(int _id, double montant){
    CompteHierarchie* c = getCompte(_id);
    //enleve le dernier memento
    c->undo(o);
    double tmp = o->getSolde();
    c->poste->debiter(&tmp, montant);
    //modifie solde
    o->setSolde(tmp);
    //remet memento
    c->saveState(*o);
}

CompteHierarchie* CompteManager::gestionCapitauxPropre(bool _nouveau, int _id, QString _nom){
    CompteHierarchie* CapitauxPropre;
     //si nouveau
     if (_nouveau==true){
        if(_nom.isEmpty()) //pas de nom
              {
                 return nullptr;

               }else{
                   std::string nompere = _nom.toStdString();
                   CapitauxPropre = new CompteReel(nompere, HierarchieBuilder::idcompte);
                   CapitauxPropre->poste = &Passif::getInstance();
                   o->setSolde(0,0);
                   CapitauxPropre->saveState(*o); //un memento pour le dernier rapprochement
                   o->setSolde(0);
                   CapitauxPropre->saveState(*o); //un memento pour le solde actuel
                   HierarchieBuilder::idcompte++;
                   getCompte(_id)->ajouterFils(CapitauxPropre);
           }
     //si pas nouveau on récupère un pointeur sur le compte sélectionné
    }else{
                    CapitauxPropre=getCompte(_id);
  }
    return CapitauxPropre;
}

CompteHierarchie* CompteManager::gestionCompteResultat(bool _nouveau, int _id, QString _nom){
   CompteHierarchie * resultat;
    //si nouveau
    if (_nouveau==true){
        if(_nom.isEmpty()) //pas de nom
              {
                 throw ExceptionHierarchie("Veuillez renseignez un nom de Compte de cloture", ExceptionHierarchie:: CLOT_EXC_H);
                 return nullptr;

               }else{
                         resultat = new CompteReel(_nom.toStdString(), HierarchieBuilder::idcompte);

                          //n'arrive jamais normalement car liste bien initialisé
                          if ((getCompte(_id)->getPoste() != PASSIF&& getCompte(_id)->getPoste() != RACINE) || getCompte(_id)->getType() == REEL){
                                throw ExceptionHierarchie("Impossible d'ajoute le compte de cloture ici", ExceptionHierarchie:: CLOT_EXC_H);
                                return nullptr;
                          }

                         resultat->poste = &Passif::getInstance();
                         o->setSolde(0,0);
                         resultat->saveState(*o);//un memento pour le dernier rapprochement
                         o->setSolde(0);
                         resultat->saveState(*o); //un memento pour le solde actuel
                         HierarchieBuilder::idcompte++;
                         getCompte(_id)->ajouterFils(resultat);
            }
      }else{
        resultat= getCompte(_id);
        if(resultat == nullptr ||resultat->getPoste()!= PASSIF || resultat->getType()!= REEL){
            throw ExceptionHierarchie("Ce compte ne peut pas être un compte de cloture", ExceptionHierarchie:: CLOT_EXC_H);
        return nullptr;
        }
    }
   return resultat;
}
