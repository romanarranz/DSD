/*
   Usar rpcgen -NCa asociaciones.x para generar los archivos
   Modificar solo los archivos asociaciones_server.c y asociaciones_client.c
*/

enum Estado {OK, Sustitucion, NoEncontrado};

typedef int ID;
typedef string Clave<255>;
typedef string Valor<255>;

struct asociacion {
	Clave clave;
	Valor valor;
	asociacion *next;
};

struct valor_estado {
	Valor valor;
	Estado s;
};

struct asociacion_estado {
	asociacion * asoc;
	Estado s;
};

program ASOCIACIONES {
	version ASOCIACIONESVER {
		Estado PonerAsociacion(ID, Clave, Valor) = 1;
		valor_estado ObtenerAsociacion(ID, Clave) = 2;
		Estado BorrarAsociacion(ID, Clave) = 3;
		asociacion_estado Enumerar(ID) = 4;
	} = 1;
} = 0x20000002;
