package common;

import java.rmi.Remote;
import java.rmi.RemoteException;

/**
 *
 * @author roman
 */
public interface IServidor extends Remote {
    
    public int login(String username) throws RemoteException;
    public void logout(int idSesion) throws RemoteException;
    public boolean existeUsuario(String email) throws RemoteException;
    public void sendBroadcast(String remitente, String mensaje, String ip) throws RemoteException;
    public void updateLoginList() throws RemoteException;
}
