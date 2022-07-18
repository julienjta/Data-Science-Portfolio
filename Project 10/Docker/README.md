Image Docker pour l'API

Installation
creer le répertoire 'shoecustomapi'
copier le répertoire 'API' et les fichier 'dockerfile' et 'docker-compose.yml' dans 'shoecustomapi'
editer les champs 'container_name' et 'ports' dans docker-compose.yml pour correspondre à votre installation.
Exécuter la commande 'docker-compose up -d --build' pour instancier le container.
L'API est prête a répondre à l'url http://localhost:9236/api (configuration par défaut)
