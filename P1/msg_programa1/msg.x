/* Archivo msg.x: Protocolo de impresion de un mensaje remoto */
program MESSAGEPROG {
	version PRINTMESSAGEVERS {
		int PRINTMESSAGE (string) = 1;
	} = 1;
} = 0x20000001;