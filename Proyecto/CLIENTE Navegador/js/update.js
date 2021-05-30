var oldEsp, newEsp;

function setValues(){
    oldEsp = document.getElementById('oldEsp').value;
    newEsp = document.getElementById('newEsp').value;
}

function update() {
    setValues();
    axios
    .request({
      url: 'http://localhost:8080/gas/cambiarESP32',
      method: 'put',
      params: {
        nombre_esp: oldEsp,
        nuevo: newEsp
      }
    })
    .then(response => alert("Se actualizaron " + Object.keys(response.data).length + " Alertas."))
    .catch(err => console.log(err.message));
  }