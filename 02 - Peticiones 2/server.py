from flask_ngrok import run_with_ngrok
from flask import Flask, jsonify, request
from flask_cors import CORS
app=Flask(__name__)
CORS(app)
run_with_ngrok(app)
@app.route('/hola', methods=['POST'])
def hola1():
	return jsonify({"Alumno": "Hola, Nombre: " + request.json['nombre'] + " Apellido: " + request.json['apellido'] +
                 " Edad: " + request.json['edad'] + " Correo: " + request.json['correo']})	
app.run()