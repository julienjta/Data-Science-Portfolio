
import os
from flask import Flask, render_template, url_for, json

app = Flask(__name__)


@app.route("/api",methods=['GET','POST'])
def hello_www():
# Test de lectur d'un fichier via l'API

    with open('selected_functions.json', 'r') as f:
        #data = list(json.load(f).items())
        data = json.load(f) 
        #print(data)
        return data

    #return data
