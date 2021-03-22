var bPedir = document.getElementById('pedir')
bPedir.addEventListener('click', function() {
    axios.post ('http://dd27044734ca.ngrok.io/hola', 
    {
        nombre : document.getElementById('nombre').value,
        apellido: document.getElementById('apellido').value,
        edad: document.getElementById('edad').value,
        correo: document.getElementById('correo').value
    }).then (function(res){
        console.log(res.data)
    }).catch(function(err){
        console.log(err)
    })
})