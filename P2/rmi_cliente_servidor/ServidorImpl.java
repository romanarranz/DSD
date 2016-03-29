import java.rmi.RemoteException;

public class ServidorImpl implements Servidor_I{
    ServidorImpl() throws RemoteException {}

    public void escribir_mensaje (int id_proceso) throws RemoteException {
        System.out.println("Recibida petición de proceso: "+id_proceso);
    if (id_proceso == 0) {
            try{
        System.out.println("Empezamos a dormir");
        Thread.sleep(5000);
        System.out.println("Terminamos de dormir");
            }
            catch (Exception e) {
                System.err.println("Ejemplo exception:");
        e.printStackTrace();
            }
    }
    System.out.println("\nHebra "+id_proceso);
    }
} 