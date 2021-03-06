/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _CALCULADORA_H_RPCGEN
#define _CALCULADORA_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct suma_1_argument {
	int arg1;
	int arg2;
};
typedef struct suma_1_argument suma_1_argument;

struct resta_1_argument {
	int arg1;
	int arg2;
};
typedef struct resta_1_argument resta_1_argument;

struct multiplicacion_1_argument {
	int arg1;
	int arg2;
};
typedef struct multiplicacion_1_argument multiplicacion_1_argument;

struct division_1_argument {
	int arg1;
	int arg2;
};
typedef struct division_1_argument division_1_argument;

#define CALCULADORA 0x20000001
#define CALCULADORAVER 1

#if defined(__STDC__) || defined(__cplusplus)
#define suma 1
extern  double * suma_1(int , int , CLIENT *);
extern  double * suma_1_svc(int , int , struct svc_req *);
#define resta 2
extern  double * resta_1(int , int , CLIENT *);
extern  double * resta_1_svc(int , int , struct svc_req *);
#define multiplicacion 3
extern  double * multiplicacion_1(int , int , CLIENT *);
extern  double * multiplicacion_1_svc(int , int , struct svc_req *);
#define division 4
extern  double * division_1(int , int , CLIENT *);
extern  double * division_1_svc(int , int , struct svc_req *);
extern int calculadora_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define suma 1
extern  double * suma_1();
extern  double * suma_1_svc();
#define resta 2
extern  double * resta_1();
extern  double * resta_1_svc();
#define multiplicacion 3
extern  double * multiplicacion_1();
extern  double * multiplicacion_1_svc();
#define division 4
extern  double * division_1();
extern  double * division_1_svc();
extern int calculadora_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_suma_1_argument (XDR *, suma_1_argument*);
extern  bool_t xdr_resta_1_argument (XDR *, resta_1_argument*);
extern  bool_t xdr_multiplicacion_1_argument (XDR *, multiplicacion_1_argument*);
extern  bool_t xdr_division_1_argument (XDR *, division_1_argument*);

#else /* K&R C */
extern bool_t xdr_suma_1_argument ();
extern bool_t xdr_resta_1_argument ();
extern bool_t xdr_multiplicacion_1_argument ();
extern bool_t xdr_division_1_argument ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_CALCULADORA_H_RPCGEN */
