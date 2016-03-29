#include "calculadora.h"

double * suma_1_svc(int arg1, int arg2,  struct svc_req *rqstp)
{
	static double  result;
	result = arg1 + arg2;
	return &result;
}

double * resta_1_svc(int arg1, int arg2,  struct svc_req *rqstp)
{
	static double  result;
	result = arg1 - arg2;
	return &result;
}

double * multiplicacion_1_svc(int arg1, int arg2,  struct svc_req *rqstp)
{
	static double  result;
	result = arg1 * arg2;
	return &result;
}

double * division_1_svc(int arg1, int arg2,  struct svc_req *rqstp)
{
	static double  result;
	result = (arg1 + 0.0) / arg2;	// con el truco de sumar 0.0 conseguimos obtener los decimales de la division
	return &result;
}