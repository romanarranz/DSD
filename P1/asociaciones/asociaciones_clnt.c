/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "asociaciones.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

Estado *
ponerasociacion_1(ID arg1, Clave arg2, Valor arg3,  CLIENT *clnt)
{
	ponerasociacion_1_argument arg;
	static Estado clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	arg.arg1 = arg1;
	arg.arg2 = arg2;
	arg.arg3 = arg3;
	if (clnt_call (clnt, PonerAsociacion, (xdrproc_t) xdr_ponerasociacion_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_Estado, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

valor_estado *
obtenerasociacion_1(ID arg1, Clave arg2,  CLIENT *clnt)
{
	obtenerasociacion_1_argument arg;
	static valor_estado clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	arg.arg1 = arg1;
	arg.arg2 = arg2;
	if (clnt_call (clnt, ObtenerAsociacion, (xdrproc_t) xdr_obtenerasociacion_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_valor_estado, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

Estado *
borrarasociacion_1(ID arg1, Clave arg2,  CLIENT *clnt)
{
	borrarasociacion_1_argument arg;
	static Estado clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	arg.arg1 = arg1;
	arg.arg2 = arg2;
	if (clnt_call (clnt, BorrarAsociacion, (xdrproc_t) xdr_borrarasociacion_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_Estado, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

asociacion_estado *
enumerar_1(ID arg1,  CLIENT *clnt)
{
	static asociacion_estado clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, Enumerar,
		(xdrproc_t) xdr_ID, (caddr_t) &arg1,
		(xdrproc_t) xdr_asociacion_estado, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}
