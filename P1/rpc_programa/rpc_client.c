/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "rpc.h"


void
suma_1(char *host)
{
	CLIENT *clnt;
	int  *result_1;
	int suma_1_arg1;
	int suma_1_arg2;

#ifndef	DEBUG
	clnt = clnt_create (host, SUMA, SUMAVER, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = suma_1(suma_1_arg1, suma_1_arg2, clnt);
	if (result_1 == (int *) NULL) {
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

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	suma_1 (host);
exit (0);
}
