package common;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.List;

/**
 *
 * @author roman
 */
public interface ICliente extends Remote {
    public void mostrarMensajes() throws RemoteException;
    public void almacenarMensajeGrupal(Mensaje m) throws RemoteException;
    public void actualizarListaContactos(List<String> contactos) throws RemoteException;
}
