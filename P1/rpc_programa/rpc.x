/* msg.x: Remote sum operation */
/*  suma es el procedimiento 1, en la version 1 del programa remoto SUMA, con el numero de programa 0x20000001 */
program SUMA {
	version SUMAVER {
		int suma(int,int) = 1;
	} = 1;
} = 0x20000001;