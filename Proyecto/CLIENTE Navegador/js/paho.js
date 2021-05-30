/*Comando de envío de datos
mosquitto_pub -t temperaturas -m "{\"lat\":19.536215,\"lon\":-96.924203,\"tem\":25,\"idx\":\"JBL\"}"
*/

//Array de Markers
var marcadores = new Array();

// Create a client instance
client = new Paho.MQTT.Client("192.168.100.9", 9001, "ClienteWeb GAS-DETECTOR");

// set callback handlers
client.onConnectionLost = onConnectionLost;
client.onMessageArrived = onMessageArrived;

// connect the client
client.connect({ onSuccess: onConnect });


// called when the client connects
function onConnect() {
  // Once a connection has been made, make a subscription and send a message.
  console.log("onConnect");
  client.subscribe("gas");
  message = new Paho.MQTT.Message("0");
  message.destinationName = "inTopic";
  client.send(message);
}

// called when the client loses its connection
function onConnectionLost(responseObject) {
  if (responseObject.errorCode !== 0) {
    console.log("onConnectionLost:" + responseObject.errorMessage);
  }
}

// called when a message arrives
function onMessageArrived(message) {
  var mensaje = message.payloadString;
  //document.getElementById('temperatura').value = mensaje;
  //console.log("onMessageArrived:"+mensaje);

  console.log(mensaje);
  var js = JSON.parse(mensaje);
  //console.log(js);
  //console.log("La temperatura es: " + js.temperatura);

  createMarker(js);
  create(js);
}

//Inicio de seccion para Array de Marcadores
function createMarker(json) {
  var markerOptions = {
    title: json.esp,
    alt: "Anonymous"
  };

  var popup = L.popup();//.setContent('Temperatura: ' + json.tem);
  var marker = L.marker([json.lat, json.lon], markerOptions);
  marker.bindPopup(popup);

  if (marcadores.length == 0) {
    //console.log("El Array está vacío");
    marcadores.push(marker);

    marker.addTo(mymap);
    marker.getPopup().setContent('Gas: ' + json.gas);
    marker.getPopup().update();
    marker.openPopup();

    /* Forma de agregar un Evento 
    marker.on('mouseover', function(){
      marker._popup.setContent('something else')
    });*/
  } else {
    resultado = existsMarker(markerOptions.title);

    if (resultado == 0) {
      //console.log("Identificador no encontrado");
      marcadores.push(marker);

      marker.addTo(mymap);
      marker.getPopup().setContent('Gas: ' + json.gas);
      marker.getPopup().update();
      marker.openPopup();
    } else {
      //console.log("Identificador EXISTENTE");

      var marcador = searchMarker(markerOptions.title);
      var gas = marcador.getPopup().getContent().substr(5);
      var index = marcadores.indexOf(marcador);

      // console.log("Temperatura en Array: " + temperatura);
      // console.log("Temperatura deseada: " + json.tem);
      // console.log("Indice del Array: " + index);

      if (gas != json.gas) {
        marcadores[index].closePopup();

        marcadores[index].getPopup().setContent("Gas: " + json.gas);
        marcadores[index].update();

        marcadores[index].openPopup();
      }
    }
  }
  console.log("Tamaño: " + marcadores.length);
}

function existsMarker(titulo) {
  var boleano = 0;
  for (i in marcadores) {
    //console.log("Valor enviado: " + titulo);
    //console.log("Valor en Array: " + marcadores[i].options.title);
    if (titulo == marcadores[i].options.title) {
      boleano = 1;
    }
  }
  return boleano;
}

function searchMarker(titulo) {
  var marker;
  for (i in marcadores) {
    if (titulo == marcadores[i].options.title) {
      marker = marcadores[i];
    }
  }
  return marker;
}

function create(json) {
  axios
  .request({
    url: 'http://localhost:8080/gas/registrar',
    method: 'post',
    params: {
      valor: json.gas,
      latitud: json.lat,
      longitud: json.lon,
      nombre_esp: json.esp
    }
  })
  .then(response => alert(response.data.fecha_hora))
  .catch(err => console.log(err.message));
}