var table;

function historial(){
    var nombre = document.getElementById('esp32').value;
    // console.log(nombre);
    table =     '<table class="table table-bordered mostrar">' +
                '<thead><tr>' +
                '<th scope="col">ID Alerta</th>' +
                '<th scope="col">Fecha y Hora</th>'+
                '<th scope="col">Valor del Sensor</th>' +
                '<th scope="col">Latitud</th>' +
                '<th scope="col">Longitud</th>' +
                '<th scope="col">ESP32</th>' +
                '</tr></thead><tbody>';
    create(nombre);
}

function create(name) {
    axios
    .request({
        url: 'http://localhost:8080/gas/historial',
        method: 'get',
        params: {
            nombre_esp: name
        }
    })
    .then(response => llenarTabla(response.data))
    .catch(err => console.log(err.message));
}

function llenarTabla(json){
    json.forEach(alerta => {
        // console.log(alerta.id_alerta);
        table+="<tr>"
        table+="<td>"+alerta.id_alerta+"</td>"
        table+="<td>"+alerta.fecha_hora+"</td>"
        table+="<td>"+alerta.valor_sensor+"</td>"
        table+="<td>"+alerta.latitud+"</td>"
        table+="<td>"+alerta.longitud+"</td>"
        table+="<td>"+alerta.nombreEsp+"</td>"
        table+="</tr>"
    })
    table+='</tbody></table>';
    // console.log(table);
    document.getElementById('here').innerHTML = table;
}
