package cliente;

import java.rmi.Remote;
import java.rmi.RemoteException;

/**
 *
 * @author roman
 */
public interface INodo extends Remote{
    public void enviarMensajeEleccion(int id) throws RemoteException;
    public void enviarMensajeCoordinador(int id) throws RemoteException;
}
