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

#### Práctica 2: Programación en RMI
En esta práctica trabajamos con la **API RMI** de **Java** la cual nos ofrece mecanismos para implementar programas de forma distribuida y al igual que RPC nos olvidemos de la parte hardware y software que tenga la máquina servidor y de los mecanismos de comuncación de datos.

A diferencia con RPC, RMI si cumple con los requisitos para implementar sistemas de objetos distribuidos, donde se requiere comunicación entre clases residentes en espacios de direcciones distintos.

> **Consideraciones**
> 
> - Utilizaremos `rmiregistry` como servicio para registrar los objetos remotos además de que puede enviar y devolver referencias a objetos remotos como argumentos y resultados de procedimientos.
> - Se facilitan scripts para hacer el mapeo de los servicios y para arrancar tanto el cliente como el servidor.

#### Práctica 3: Node JS
[NodeJS](http://nodejs.org) es una plataforma que nos permite implementar servicios web haciendo uso del lenguaje de programación Javascript. Estos servicios son asíncronos y dirigidos por eventos, enfocados a maximizar la escalabilidad y eficiencia de los mismos.

Con el estándar HTML5 surge la posibilidad de usar `WebSockets` con **Javascript**, con los que podemos realizar notificaiones `Push` a los clientes sin necesidad de que refresquen la página o que tengamos un código consultando cada X tiempo mandando peticiones.

> **Consideraciones**
> 
> - Usaremos una interfaz de tipo `REST` para gestionar las peticiones.
> - Como es asíncrono las respuestas serán ofrecidas con `XMLHttpRequest`.
> - Para gestionar las notificaciones `Push` usaremos `Socket.io`.
> - Para almacenar los mensajes entrantes de la implementación del chat usaremos `MongoDB` por su integración con el formato JSON.
> 
> **Implementaciones**
> - Calculadora usando API REST
> - Cliente Chat

## Licencia

MIT License

Copyright (c) [2016] [Román Arranz Guerrero]

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.