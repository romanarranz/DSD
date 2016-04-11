// express inicializa la app
var app = require('express')();

// la servimos como un servicio http
var http = require('http').Server(app);

// inicio socket.io con el servicio http
var io = require('socket.io')(http);

// definimos una ruta que sirva como bienvenida a la pagina index.html
app.get('/', function(req, res){
  	res.sendFile(__dirname + '/index.html');
});

// escucho el evento connection para conexiones entrantes y las muestro por consola
io.on('connection', function(socket){
  	console.log('a user connected');

  	// si se desconecta lo mostramos en la consola
  	socket.on('disconnect', function(){
    	console.log('user disconnected');
  	});

  	// si nos llega un evento chat message lo enviamos a todos los que esten conectados y lo mostramos por consola
  	socket.on('chat message', function(msg){
  		io.emit('chat message', msg);
    	console.log('message: ' + msg);
  	});

});

// ponemos el servicio a la escucha en el puerto 3000
http.listen(3000, function(){
  	console.log('listening on *:3000');
});