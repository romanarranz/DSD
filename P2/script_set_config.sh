#!/bin/bash

jdk=""

# buscamos la ruta del jdk que tenga instalado el usuario
busqueda=`sudo find / -type d -name 'jdk1*' -print`

# obtenemos el numero de jdks que tiene instalado
numeroresultados=`echo $jdk | tr -cd " " | wc -c`

# si el numero es mayor a 1 quiere decir que tiene varios y por lo tanto debe elegir cual
if [ $numeroresultados -gt 1 ]; then
	read -p $'Introduzca la ruta de su JDK:' jdk
else
	jdk=`echo $busqueda | cut -d " " -f 1`
fi
echo "JDK seleccionado : $jdk"

for x in $(ls $jdk/bin);
do 
	# Comprobamos si existen ya esos comandos en el PATH del sistema
	exist=`which ${x}`
	if [ -z "$exist" ]; then
		echo "Creando enlace a /usr/local/bin/${x} ..."
		src=`echo "$jdk/bin"`
		dst="/usr/local/bin"
		sudo ln -s `echo "$src/${x}"` `echo "$dst/${x}"`
	else
		echo "El comando ${x} ya se encuentra en el PATH de su sistema"
	fi
done

# Creacion del fichero de politicas de seguridad server.policy
# ========================================================================

DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
#echo "$DIR"

output=""
i=0
while (( i++ <= ${#DIR} ))
do
   	char=$(expr substr "$DIR" $i 1)
   	if [ "$char" == " " ] || [ "$char" == "[" ] || [ "$char" == "]" ] ; then
   		output="$output\\$char"
   	else
   		output="$output$char"
   	fi
done

output=`echo "$output/server.policy"`

echo "grant codeBase \"$output\" {" 2>&1 > aux
echo -e "\t permission java.security.AllPermission;" 2>&1 >> aux
echo "};" 2>&1 >> aux

mv aux "$DIR/server.policy"