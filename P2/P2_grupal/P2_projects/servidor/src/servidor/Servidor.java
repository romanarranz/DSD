package servidor;

import common.ICliente;
import common.IServidor;
import common.Mensaje;
import common.Utils;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

/**
 *
 * @author roman
 * $ rmiregistry -J-Djava.rmi.server.useCodebaseOnly=false
 * para lanzar el demonio rmi
 */

public class Servidor implements IServidor{
    private Map<Integer, String> totales = new HashMap<Integer, String>();
    private Map<String, Integer> totales_id = new HashMap<String, Integer>();
    private Map<Integer, String> conectados = new HashMap<Integer, String>();
    private Map<String, Integer> conectados_id = new HashMap<String, Integer>();
    private int user_id = 1;
    public Servidor(){}
 
    @Override
    public int login(String username) throws RemoteException {
        if(!totales.containsValue(username)){            
            user_id++;
            totales.put(user_id, username);
            totales_id.put(username, user_id);
        }     
        if(!conectados.containsValue(username)){            
            conectados.put(user_id, username);
            conectados_id.put(username, user_id);
                        
            System.out.println("Se ha conectado el usuario "+username);
            return user_id;
        }
        else {
            System.out.println("El usuario "+username+" ya esta conectado");
            return conectados_id.get(username);
        } 
    }

    @Override
    public void logout(int user_id) throws RemoteException {
        String usuario = conectados.get(user_id);
            
        conectados.remove(user_id);
        conectados_id.remove(usuario);
        System.out.println("El usuario "+usuario+" se ha desconectado");
    }

    @Override
    public boolean existeUsuario(String username) throws RemoteException {
        boolean result = true;
        if(!totales.containsValue(username)){
            System.out.println("El usuario "+username+" no existe");
            result = false;
        }
        return result;
    }
    
    @Override
    public void sendBroadcast(String remitente, String mensaje, String ip) throws RemoteException{
        for (Map.Entry<Integer, String> entry : conectados.entrySet()){
            //System.out.println(entry.getKey() + "/" + entry.getValue());
            if(!entry.getValue().equals(remitente)){
                try{
                    Registry registry = LocateRegistry.getRegistry();
                    ICliente cliente = (ICliente) registry.lookup(entry.getValue());

                    cliente.almacenarMensajeGrupal(new Mensaje(mensaje, remitente));
                    cliente.mostrarMensajes();
                }catch (Exception e){
                    e.printStackTrace();
                }
            }
        }        
    }      
    
    @Override
    public void updateLoginList() throws RemoteException{
        List<String> l = new LinkedList<String>();
        l.addAll(conectados.values());
        
        for (Map.Entry<Integer, String> entry : conectados.entrySet()){
            try{
                Registry registry = LocateRegistry.getRegistry();
                ICliente cliente = (ICliente) registry.lookup(entry.getValue());

                cliente.actualizarListaContactos(l);
            }catch (Exception e){
                e.printStackTrace();
            }            
        } 
    }
    
    public static void main(String[] args) {
        Utils.setCodeBase(IServidor.class);         
        
        try {
            Servidor servidor = new Servidor();
            IServidor stub = (IServidor)UnicastRemoteObject.exportObject(servidor, 0);

            // stub
            Registry reg = LocateRegistry.getRegistry();
            String remote_object = "Servidor";
            reg.rebind(remote_object, stub);

            System.out.println("Servidor listo, presione enter para continuar");
            System.in.read();

            reg.unbind(remote_object);
            UnicastRemoteObject.unexportObject((Remote) servidor, true);        
        } catch (Exception e) {
            e.printStackTrace();
	}
    }   
}
