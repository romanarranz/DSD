#include "asociaciones.h"

void asociaciones_1(char *host, int opcion)
{
	CLIENT *clnt;

	#ifndef	DEBUG
		clnt = clnt_create (host, ASOCIACIONES, ASOCIACIONESVER, "udp");
		if (clnt == NULL) {
			clnt_pcreateerror (host);
			exit (1);
		}
	#endif	/* DEBUG */

	ID id;
	Clave key = malloc(sizeof(char) * 255);
	Valor dato = malloc(sizeof(char) * 255);
	Estado * result_1;
	valor_estado * result_2;
	asociacion_estado * result_4;
	switch(opcion){
		case 1: 
			printf("ID: ");		scanf("%i",&id);	printf("\n");
			printf("Clave: ");	scanf("%253s",key);	printf("\n");
			printf("Valor: ");	scanf("%253s",dato);	printf("\n");
			result_1 = ponerasociacion_1(id, key, dato, clnt);

			if (result_1 == NULL)
				clnt_perror (clnt, "call failed");
			else 
			{
				if(*result_1 == OK)
					printf("Estado de la operacion -> OK\n");
				else if(*result_1 == Sustitucion)
					printf("Estado de la operacion -> Sustitucion\n");
				else
					printf("Estado de la operacion -> NoEncontrado\n");
			}
			
			break;
		case 2: 
			printf("ID: ");		scanf("%i",&id);	printf("\n");
			printf("Clave: ");	scanf("%253s",key);	printf("\n");
			result_2 = obtenerasociacion_1(id, key, clnt);

			if(result_2 == NULL)
				clnt_perror (clnt, "call failed");
			else 
			{
				if((*result_2).s == OK){
					printf("Estado: OK\n");
					printf("Valor: %s\n", (char *)(*result_2).valor);
				}
				else 
					printf("Estado: NoEncontrado\n");
			}

			break;
		case 3: 
			printf("ID: ");		scanf("%i",&id);	printf("\n");
			printf("Clave: ");	scanf("%253s",key);	printf("\n");
			result_1 = borrarasociacion_1(id, key, clnt);

			if(result_1 == NULL)
				clnt_perror(clnt, "call failed");
			else 
			{
				if(*result_1 == OK)
					printf("Estado de la operacion -> OK\n");
				else
					printf("Estado de la operacion -> NoEncontrado\n");
			}

			break;
		case 4: 
			printf("ID: ");		scanf("%i",&id);	printf("\n");
			result_4 = enumerar_1(id, clnt);

			if(result_4 == NULL)
				clnt_perror (clnt, "call failed");
			else
			{
				if((*result_4).s == OK)
				{
					printf("Estado: OK\n");
					asociacion * aux = (*result_4).asoc;
					while(aux != NULL)
					{
						printf("[%s , %s ]\n", aux->clave, aux->valor);
						aux = aux->next;
					}
				}
				else
					printf("Estado: NoEncontrado\n");
			}

			break;
	};

	#ifndef	DEBUG
		clnt_destroy (clnt);
	#endif	 /* DEBUG */

	// Libero la memoria que he reservado con malloc
	free(key);
	free(dato);
}


int main (int argc, char *argv[])
{
	char *host;
	int opcion = 0;
	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];

	do {
		printf("# ------------------- Conjuntos de Asociaciones -------------------\n");
		printf("1. PonerAsociacion - ID x Clave x Valor -> Estado\n");
		printf("2. ObtenerAsociacion - ID x Clave -> Valor x Estado\n");
		printf("3. BorrarAsociacion - ID x Clave -> Estado\n");
		printf("4. Enumerar - ID -> Conjunto de Claves x Valores x Estado\n");
		printf("5. Salir\n\n");
		printf("Seleccione la opcion: ");
		scanf("%i", &opcion);
		printf("\n\n");
		asociaciones_1 (host, opcion);
	} while(opcion != 5);
	exit (0);
}