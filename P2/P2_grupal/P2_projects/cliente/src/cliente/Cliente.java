package cliente;

import common.ICliente;
import common.IServidor;
import common.Mensaje;
import common.Utils;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.LinkedList;
import java.util.List;
import javax.swing.DefaultListModel;

/**
 *
 * @author roman
 */
public class Cliente implements ICliente{
    
    private static ICliente stub;
    private static IServidor servidor;
    private static String remote_object;
    private static Registry registry;
    
    private static int user_id = -1;
    private static String username;
    private static String ip;
    private static List<Mensaje> inbox = new LinkedList<Mensaje>();
    
    private static List<String> contactlist = new LinkedList<String>();
    
    public static GUI cliente_gui;  
    
    @Override
    public void mostrarMensajes() throws RemoteException {
        cliente_gui.actualizarMensajes();
    }

    @Override
    public void almacenarMensajeGrupal(Mensaje m) throws RemoteException {        
        if(inbox == null){
            inbox = new LinkedList<Mensaje>();            
        }
        
        inbox.add(m);        
    }
    
    @Override
    public void actualizarListaContactos(List<String> contactos) throws RemoteException{        
        contactlist = contactos;
        //System.out.println(contactlist.toString());
        cliente_gui.updateContactList();
    }    
    
    public static void login() throws RemoteException{       
        user_id = servidor.login(username);
        registry.rebind(username, stub);
        System.out.println("Me he bindeado como "+username);
        servidor.updateLoginList();
    }
    
    public static void logout() throws RemoteException{       
        servidor.logout(user_id);
        user_id = -1;
        servidor.updateLoginList();
    }
    
    public static void send(String miMensaje) throws RemoteException{
        servidor.sendBroadcast(username, miMensaje, ip);
        inbox.add(new Mensaje(miMensaje, username));
        cliente_gui.actualizarMensajes();
    }
    
    public static int getUserId(){return user_id;}
    
    public static String getNombre(){return username;}    
    
    public static void setNombre(String nombre){username = nombre;}
    
    public static String getIp(){return ip;}                  
    
    public static List<Mensaje> getConversacion(){return inbox;}
    
    public DefaultListModel getContactList(){
        DefaultListModel dlm = new DefaultListModel();
        dlm.addElement("");
        for(String c : contactlist){
            dlm.addElement(c);
        }
        
        return dlm;
    }
    
    public static void main(String[] args) {
        Utils.setCodeBase(IServidor.class);
        
        try {
            //ip = args[0];
            registry = LocateRegistry.getRegistry();
            
            remote_object = "Servidor";
            servidor = (IServidor) registry.lookup(remote_object);
                
            ICliente cliente = new Cliente();
            stub = (ICliente) UnicastRemoteObject.exportObject(cliente, 0);
                
            cliente_gui = new GUI();
            cliente_gui.setClient((Cliente) cliente);            
        } catch (Exception e) {
            System.err.println("Error en el cliente al conectarse al servidor...");
            e.printStackTrace();
        }
    }    
}
