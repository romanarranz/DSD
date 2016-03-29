/* msg_proc.c: implementacion del procedimiento remoto */
#include <stdio.h>
#include "msg.h"

/* el archivo lo genera rpcgen */

int * printmessage_1(msg, req)
char **msg;
struct svc_req *req;

/* detalles de la llamada */
{
	static int result;
	/* es obligatorio que sea estatica */
	FILE *f;
	f = fopen("/dev/console", "w");
		if (f == (FILE *)NULL) {
			result = 0;
			return (&result);
		}
	fprintf(f,"%s\n", *msg);
	fclose(f);
	result = 1;
	return (&result);
}