/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "asociaciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

static Estado *
_ponerasociacion_1 (ponerasociacion_1_argument *argp, struct svc_req *rqstp)
{
	return (ponerasociacion_1_svc(argp->arg1, argp->arg2, argp->arg3, rqstp));
}

static valor_estado *
_obtenerasociacion_1 (obtenerasociacion_1_argument *argp, struct svc_req *rqstp)
{
	return (obtenerasociacion_1_svc(argp->arg1, argp->arg2, rqstp));
}

static Estado *
_borrarasociacion_1 (borrarasociacion_1_argument *argp, struct svc_req *rqstp)
{
	return (borrarasociacion_1_svc(argp->arg1, argp->arg2, rqstp));
}

static asociacion_estado *
_enumerar_1 (ID  *argp, struct svc_req *rqstp)
{
	return (enumerar_1_svc(*argp, rqstp));
}

static void
asociaciones_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		ponerasociacion_1_argument ponerasociacion_1_arg;
		obtenerasociacion_1_argument obtenerasociacion_1_arg;
		borrarasociacion_1_argument borrarasociacion_1_arg;
		ID enumerar_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case PonerAsociacion:
		_xdr_argument = (xdrproc_t) xdr_ponerasociacion_1_argument;
		_xdr_result = (xdrproc_t) xdr_Estado;
		local = (char *(*)(char *, struct svc_req *)) _ponerasociacion_1;
		break;

	case ObtenerAsociacion:
		_xdr_argument = (xdrproc_t) xdr_obtenerasociacion_1_argument;
		_xdr_result = (xdrproc_t) xdr_valor_estado;
		local = (char *(*)(char *, struct svc_req *)) _obtenerasociacion_1;
		break;

	case BorrarAsociacion:
		_xdr_argument = (xdrproc_t) xdr_borrarasociacion_1_argument;
		_xdr_result = (xdrproc_t) xdr_Estado;
		local = (char *(*)(char *, struct svc_req *)) _borrarasociacion_1;
		break;

	case Enumerar:
		_xdr_argument = (xdrproc_t) xdr_ID;
		_xdr_result = (xdrproc_t) xdr_asociacion_estado;
		local = (char *(*)(char *, struct svc_req *)) _enumerar_1;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}

int
main (int argc, char **argv)
{
	register SVCXPRT *transp;

	pmap_unset (ASOCIACIONES, ASOCIACIONESVER);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, ASOCIACIONES, ASOCIACIONESVER, asociaciones_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (ASOCIACIONES, ASOCIACIONESVER, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, ASOCIACIONES, ASOCIACIONESVER, asociaciones_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (ASOCIACIONES, ASOCIACIONESVER, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}
