# Readme

## Format de sauvegarde pour les Transactions

Pour les transactions : `<transaction>\n\t<date>%ld</date>\n\t<ref>%s</ref>\n\t<memo>%s</memo>\n\t<valide>%h</valide>\n\t<operations>\n\t`

et pour les opérations : `\t<operation>\n\t\t\t<compte>%d</compte>\n\t\t\t<credit>%lf</credit>\n\t\t\t<debit>%lf</debit>\n\t\t</operation>\n\t`

Exemple : voir le fichier Transaction.xml

## Liste des codes d'exceptions

CodeExcepTransaction :

- UKWN\_EXC\_T exception inconnue (par défaut)
- MEMO\_EXC\_T exception d'allocation de mémoire 
- RULE\_EXC\_T exception de logique (ne respecte pas la logique de l'application)
- NULL\_EXC\_T exception de pointer `nullptr` non-attendu
- SRCH\_EXC\_T exception de recherche infructueuse

CodeExcepFichier

- UKWN\_EXC\_F exception inconnue (par défaut)
- UFND\_EXC\_F exception de fichier introuvable/inaccessible
- SNTX\_EXC\_F exception de syntaxe incorrecte dans le fichier