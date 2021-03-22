from flask_ngrok import run_with_ngrok
from flask import Flask, jsonify, request
from flask_cors import CORS
app=Flask(__name__)
CORS(app)
run_with_ngrok(app)
@app.route('/hola', methods=['POST'])
def hola1():
	return jsonify({"saludo": "Hola Mundo 1," + request.json['nombre', 'apellido', 'edad', 'correo']})
@app.route('/hola', methods=['GET'])
def hola2():
	return jsonify({"saludo": "Hola Mundo 2," + request.json['nomb']})	
app.run()
