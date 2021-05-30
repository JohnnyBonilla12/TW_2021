var idAlerta=0;

function setValues(){
    idAlerta = document.getElementById('idAlerta').value;
    parseInt(idAlerta);
}

function deleteP(){
    setValues();
    axios.delete('http://localhost:8080/gas/borrarAlerta', {
        params: {
            id_alerta: idAlerta
        }  
    })
    .then(response => alert(response.data))
    .catch(err => console.log(err.message));
}