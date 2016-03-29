package common;

import java.rmi.Remote;
import java.rmi.RemoteException;

/**
 *
 * @author roman
 */
public interface ICliente extends Remote {
    public void mostrarMensajes() throws RemoteException;
    public void almacenarMensajeP2P(String usuario, Mensaje m) throws RemoteException;
}
