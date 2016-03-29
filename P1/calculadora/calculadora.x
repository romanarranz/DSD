/*
   Usar rpcgen -NCa calculadora.x para generar los archivos
   Modificar solo los archivos calculadora_server.c y calculadora_client.c
*/
program CALCULADORA {
	version CALCULADORAVER {
		double suma(int,int) = 1;
		double resta(int,int) = 2;
		double multiplicacion(int,int) = 3;
		double division(int,int) = 4;
	} = 1;
} = 0x20000001;
