#include "calculadora.h"
#include <stdio.h>
#include <stdlib.h>

void
calculadora_1(char *host, int operando1, char operador, int operando2)
{
	CLIENT *clnt;
	double *result, *result2;
	char op;
	int a, b;

	#ifndef	DEBUG
		clnt = clnt_create (host, CALCULADORA, CALCULADORAVER, "udp");
		if (clnt == NULL) {
			clnt_pcreateerror (host);
			exit (1);
		}
	#endif	/* DEBUG */

		a = operando1;
		op = operador;
		b = operando2;
		printf("%i %c %i = ", a, op, b);
		switch(op){
			case '+':
				result = suma_1(a, b, clnt);
				printf("%lf \n", *result);
				break;
			case '-': 
				result = resta_1(a, b, clnt);	
				printf("%lf \n", *result);
				break;
			case 'x': 
				result = multiplicacion_1(a, b, clnt);	
				printf("%lf \n", *result);
				break;
			case '/': 
				result = division_1(a, b, clnt);
				printf("%lf \n", *result);
				break;
		};

		if( result == NULL) {
			clnt_perror (clnt, "call failed");
		}

	#ifndef	DEBUG
		clnt_destroy (clnt);
	#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	int operando1, operando2;
	char operador;
	if (argc != 5) {
		printf ("usage: %s <hostname/ip> <entero> <operador> <entero>\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	operando1 = atoi(argv[2]);
	operador = (char)argv[3][0];
	operando2 = atoi(argv[4]);
	calculadora_1 (host, operando1, operador, operando2);
	exit (0);
}
