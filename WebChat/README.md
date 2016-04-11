Socket.io
==========

Implementación simple de un **IRC**.

La idea de socket.io es que podamos enviar y recibir cualquier evento que queramos, con los datos que queramos. Cualquier dato puede ser enviado en formato JSON o incluso como binary data.

En nuestro cliente chat lo que haremos será definir un evento `chat message` para enviar el contenido del campo de texto del usuario al servidor.


##Instalación

En caso de que no tengamos instalado NodeJS lo instalamos.

```bash
$ sudo apt-get install nodejs
```

**IMPORTANTE todas las instalaciones siguientes se harán en el propio directorio** `chat-example`

Lo primero que tendremos que hacer es servir una página HTML con un formulario y una lista de mensajes. Para esta tarea usaremos el framework `express` de **NodeJS**.

```bash
$ npm install --save express@4.10.2
```

Integramos Socket.IO que se compone de dos partes:
- Servidor integra la respuesta HTTP: `socket.io`
- Libreria que el cliente debe cargar: `socket.io-client`

```bash
$ npm install --save socket.io
```

##Broadcast

¿Cómo podemos enviar un mensaje al servidor y que les llegue al resto de usuarios?

Socket.IO nos ofrece una gran flexibilidad por el hecho de usar JSON, asi que esta tarea se podría simplificar en el siguiente código.

```js
io.emit('some event', { for: 'everyone' });
```

Si queremos enviar un mensaje a todos salvo a un socket podemos usar la etiqueta `broadcast`.

```js
io.on('connection', function(socket){
  socket.broadcast.emit('hi');
});
```

Por simplicidad se ha decidido enviar el mensaje a todos incluido el propio emisor.

```js
io.on('connection', function(socket){
	// ...  	socket.on('chat message', function(msg){  		io.emit('chat message', msg);    	console.log('message: ' + msg);  	});
});
```

##Pendiente
Ideas para mejorar la aplicación.

- Enviar un mensaje a todos los usuarios conectados cuando un usuario se conecte o desconecte.
- Añadir opcion para que los usuarios puedan ponerse un nick.
- No enviar el mismo mensaje al mismo usuario remitente.
- Añadir "{user} esta escribiendo..." como funcionalidad.
- Mostrar quien esta en linea.
- Añadir un mensaje privado.