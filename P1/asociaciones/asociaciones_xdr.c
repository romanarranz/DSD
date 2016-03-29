/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "asociaciones.h"

bool_t
xdr_Estado (XDR *xdrs, Estado *objp)
{
	register int32_t *buf;

	 if (!xdr_enum (xdrs, (enum_t *) objp))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ID (XDR *xdrs, ID *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, objp))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_Clave (XDR *xdrs, Clave *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, objp, 255))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_Valor (XDR *xdrs, Valor *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, objp, 255))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_asociacion (XDR *xdrs, asociacion *objp)
{
	register int32_t *buf;

	 if (!xdr_Clave (xdrs, &objp->clave))
		 return FALSE;
	 if (!xdr_Valor (xdrs, &objp->valor))
		 return FALSE;
	 if (!xdr_pointer (xdrs, (char **)&objp->next, sizeof (asociacion), (xdrproc_t) xdr_asociacion))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_valor_estado (XDR *xdrs, valor_estado *objp)
{
	register int32_t *buf;

	 if (!xdr_Valor (xdrs, &objp->valor))
		 return FALSE;
	 if (!xdr_Estado (xdrs, &objp->s))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_asociacion_estado (XDR *xdrs, asociacion_estado *objp)
{
	register int32_t *buf;

	 if (!xdr_pointer (xdrs, (char **)&objp->asoc, sizeof (asociacion), (xdrproc_t) xdr_asociacion))
		 return FALSE;
	 if (!xdr_Estado (xdrs, &objp->s))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ponerasociacion_1_argument (XDR *xdrs, ponerasociacion_1_argument *objp)
{
	 if (!xdr_ID (xdrs, &objp->arg1))
		 return FALSE;
	 if (!xdr_Clave (xdrs, &objp->arg2))
		 return FALSE;
	 if (!xdr_Valor (xdrs, &objp->arg3))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_obtenerasociacion_1_argument (XDR *xdrs, obtenerasociacion_1_argument *objp)
{
	 if (!xdr_ID (xdrs, &objp->arg1))
		 return FALSE;
	 if (!xdr_Clave (xdrs, &objp->arg2))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_borrarasociacion_1_argument (XDR *xdrs, borrarasociacion_1_argument *objp)
{
	 if (!xdr_ID (xdrs, &objp->arg1))
		 return FALSE;
	 if (!xdr_Clave (xdrs, &objp->arg2))
		 return FALSE;
	return TRUE;
}
