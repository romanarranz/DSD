Desarrollo de Sistemas Distribuidos
===================

Prácticas y seminarios de la asignatura Desarrollo de Sistemas Distribuiods cursada en el Grado en Informática de la **Universidad de Granada**

----------

Índice de Prácticas
-------------
#### Práctica 1: Llamada a Procedimiento Remoto (RPC)
En esta práctica trabajamos con las llamadas a procedimientos remotos con las cuales podemos operar bajo una arquitectura cliente - servidor en la cual abstraemos el hardware y el software subyacente de la máquina servidor así como los mecanimos de comunicación de datos.

> **Consideraciones**
> 
> - Utilizaremos `rpcbind` como **portmapper** ya que los servicios de transporte no proporcionan servicios de búsqueda de direcciones, sólo proporcionan transferenceia de mensajes a través de la red.
> - Utilizaremos la utilidad `rpcgen` para despreocuparnos de los servicios de nivel más bajo y así generar automáticamente los programas RPC.
> - Usamos **XDR** como representación de datos estándar, ya que es una descripción de datos independiente de la máquina y con un protocolo de codificación.
