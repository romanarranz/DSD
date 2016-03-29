#!/bin/bash

DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

port=1099
read -p "Indique el puerto por defecto de rmiregistry (default 1099): " port

status=` netstat -a | grep rmiregistry | wc -w`
if [ $status -gt 0 ] ; then
	pid=`pgrep rmiregistry`
	echo "Error: El servicio rmiregistry (PID $pid) ya fue iniciado"
else
	echo "Iniciando servicio rmiregistry ..."
	rmiregistry "$port" &
fi

# ubicación desde la que poder descargar definiciones de clases desde el servidor
codebase="$DIR/bin/simple"

# server donde colocar los stubs para los objetos remotos
host=localhost

# especifica el fichero de políticas de seguridad que se pretenden seguir o conceder
policy="$DIR/server.policy"

java -cp . -Djava.rmi.server.codebase="$codebase" -Djava.rmi.server.hostname="$host" -Djava.security.policy="$policy" Ejemplo