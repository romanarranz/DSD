#include "asociaciones.h"

typedef struct ListaDeAsociaciones{
	ID id;
    asociacion *inicio;
    asociacion *fin;
	struct ListaDeAsociaciones * sig;
} Lista;

Lista * primero = (Lista *) NULL;
Lista * ultimo = (Lista *) NULL;

Estado *
ponerasociacion_1_svc(ID arg1, Clave arg2, Valor arg3,  struct svc_req *rqstp)
{
	static Estado  result;
	if( primero == NULL ){
		// reservo memoria para la nueva celda de la lista
		Lista * nuevo = (Lista *) malloc (sizeof(Lista));

	   	nuevo->id = arg1;
	   	nuevo->inicio = NULL;
		nuevo->fin = NULL;
		nuevo->sig = NULL;

		// reservo memoria para la nueva asociacion de la celda de la lista
		asociacion * key_value = (asociacion *) malloc (sizeof(asociacion));
		key_value->clave = (char *) malloc (255 * sizeof (char));
		key_value->valor = (char *) malloc (255 * sizeof (char));

		strcpy( key_value->clave, arg2);
		strcpy( key_value->valor, arg3);
	    key_value->next = NULL;

		nuevo->inicio = key_value;
    	nuevo->fin = key_value;

        primero = nuevo;
        ultimo = nuevo;

        result = OK;
	} 
	else {
		int findID = 0;
		int findAsoc = 0;
		Lista * aux = primero;
		asociacion * aux2;
		while( aux != NULL && findID == 0 ){
			// si encontramos el id en la lista de asociaciones insertamos una nueva asociacion en esa celda
			if( arg1 == aux->id ){
				findID = 1;

				// procedemos a ver si la clave que queremos insertar ya existe en la lista de asociaciones
				aux2 = aux->inicio;
			    while(aux2 != NULL && findAsoc == 0){
			    	if(strcmp( aux2->clave , arg2) == 0){
			    		findAsoc = 1;
			    		strcpy(aux2->valor, arg3);
			    		result = Sustitucion;
			    	}
			    	aux2 = aux2->next;
			    }
			    
			    // si no se encontró la clave en la lista de asociaciones la insertamos al final la nueva asociacion
			    if(findAsoc == 0) {
			    	asociacion * key_value = (asociacion *) malloc (sizeof(asociacion));
					key_value->clave = (char *) malloc (255 * sizeof (char));
					key_value->valor = (char *) malloc (255 * sizeof (char));

					strcpy( key_value->clave, arg2);
					strcpy( key_value->valor, arg3);
				    key_value->next = NULL;		
			   
			   		if(aux->inicio != NULL && aux->fin != NULL){
			    		aux->fin->next = key_value;
			    		aux->fin = key_value;
			    	}
			    	else {
			    		aux->inicio = key_value;
			    		aux->fin = key_value;
			    	}

			    	result = OK;
			    }
			}
			
			aux = aux->sig;
		}

		// si NO hemos encontrado el id en la lista de asociaciones insertarmos una nueva celda en la lista
		if(findID == 0)
		{
			// reservo memoria para la nueva celda de la lista
			Lista * nuevo = (Lista *) malloc (sizeof(Lista));
		   	nuevo->id = arg1;
		   	nuevo->inicio = NULL;
		   	nuevo->fin = NULL;
		   	nuevo->sig = NULL;

		   	// reservo memoria para la nueva asociacion de esa celda de la lista
			asociacion * key_value = (asociacion *) malloc (sizeof(asociacion));
			key_value->clave = (char *) malloc (255 * sizeof (char));
			key_value->valor = (char *) malloc (255 * sizeof (char));

			strcpy( key_value->clave, arg2);
			strcpy( key_value->valor, arg3);
			key_value->next = NULL;

			nuevo->inicio = key_value;
	    	nuevo->fin = key_value;

	    	if(primero != NULL && ultimo != NULL){
	    		ultimo->sig = nuevo;
	    		ultimo = nuevo;
	    	}
	    	else {
	    		primero = nuevo;
	    		ultimo = nuevo;
	    	}

	    	result = OK;
		}
	}
/*
	Lista * aux = primero;
	asociacion * aux2;
	while(aux !=  NULL){
		aux2 = aux->inicio;
		while(aux2 != NULL){
			printf("## %i : %s -> %s\n", aux->id, aux2->clave, aux2->valor);
			aux2 = aux2->next;
		}

		aux = aux->sig;
	}
	
	printf("------------\n");
*/
	return &result;
}

valor_estado *
obtenerasociacion_1_svc(ID arg1, Clave arg2,  struct svc_req *rqstp)
{
	static valor_estado  result;

	Lista * aux = primero;
	asociacion * aux2;
	while(aux != NULL)
	{
		if(arg1 == aux->id)
		{
			aux2 = aux->inicio;
			while(aux2 != NULL)
			{
				if(strcmp(arg2 ,aux2->clave) == 0){
					result.valor = aux2->valor;
					result.s = OK;
					return &result;
				}
				aux2 = aux2->next;
			}
		}
		aux = aux->sig;
	}

	result.valor = "";
	result.s = NoEncontrado;
	return &result;
}

Estado *
borrarasociacion_1_svc(ID arg1, Clave arg2,  struct svc_req *rqstp)
{
	static Estado  result;

	Lista * aux = primero;
	asociacion * aux2, * aux3;
	int i = 0;
	while( aux != NULL ){
		if(arg1 == aux->id)
		{
			aux2 = aux->inicio;
			aux3 = aux->inicio->next;
			
			// en caso de que sea el primero se borra y fin
			if(strcmp(arg2, aux2->clave) == 0 && i == 0){
				asociacion * borrar = aux2;
				aux2 = aux3;
				free(borrar->clave);
				free(borrar->valor);
				free(borrar);
				aux->inicio = aux3;

				result = OK;
				return &result;
			}
			else {	// si no fuera el primero hay que buscarlo
				while(aux3 != NULL){
					if(strcmp(arg2, aux3->clave) == 0 && i >= 0){
						asociacion * borrar = aux3;
						aux2->next = aux3->next;
						free(borrar->clave);
						free(borrar->valor);
						free(borrar);

						result = OK;
						return &result;
					}
					aux2 = aux2->next;
					aux3 = aux3->next;
					i++;
				}
			}
		}

		i = 0;
		aux = aux->sig;
	}
	
	result = NoEncontrado;
	return &result;
}

asociacion_estado *
enumerar_1_svc(ID arg1,  struct svc_req *rqstp)
{
	static asociacion_estado result;

	Lista * aux = primero;
	while( aux != NULL )
	{
		if( arg1 == aux->id )
		{
			result.asoc = aux->inicio;
			result.s = OK;
			return &result;
		}
		aux = aux->sig;
	}

	result.asoc = NULL;
	result.s = NoEncontrado;
	return &result;
}