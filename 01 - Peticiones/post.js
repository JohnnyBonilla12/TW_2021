var bPedir = document.getElementById('pedir')
bPedir.addEventListener('click', function() {
    axios.post ('http://2b52ccbeb218.ngrok.io//hola', 
    {
        nomb : document.getElementById('nombre').value
    }).then (function(res){
        console.log(res.data)
    }).catch(function(err){
        console.log(err)
    })
})