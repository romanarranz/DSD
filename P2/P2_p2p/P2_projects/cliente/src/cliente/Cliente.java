package cliente;

import common.ICliente;
import common.IServidor;
import common.Mensaje;
import common.Utils;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
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
    private static Map<String, List<Mensaje>> inbox = new HashMap<String, List<Mensaje>>();
    
    public static GUI cliente_gui;  
    
    @Override
    public void mostrarMensajes() throws RemoteException {
        cliente_gui.actualizarMensajes();
    }

    @Override
    public void almacenarMensajeP2P(String destinatario, Mensaje m) throws RemoteException {
        List<Mensaje> l = inbox.get(destinatario);
        if(l == null){
            l = new LinkedList<Mensaje>();
            inbox.put(destinatario, l);
        }
        System.out.println(destinatario+": "+m.getCuerpo());
        l.add(m);        
    }
    
    public static void login() throws RemoteException{       
        user_id = servidor.login(username);
        registry.rebind(username, stub);
        System.out.println("Me he bindeado como "+username);
    }
    
    public static void logout() throws RemoteException{       
        servidor.logout(user_id);
        user_id = -1;
    }
    
    public static void send(String miMensaje, String destinatario) throws RemoteException{
        servidor.sendP2P(destinatario, username, miMensaje, ip);
        List<Mensaje> l = inbox.get(destinatario);
        if(l == null){
            l = new LinkedList<Mensaje>();
            inbox.put(destinatario, l);
        }
        l.add(new Mensaje(miMensaje, username));
        cliente_gui.actualizarMensajes();
    }
    
    public static int getUserId(){return user_id;}
    
    public static String getNombre(){return username;}    
    
    public static void setNombre(String nombre){username = nombre;}
    
    public static String getIp(){return ip;}
     
    public static List<Mensaje> getConversacion(String usuario){
        List<Mensaje> l = inbox.get(usuario);
        if(l == null){
            l = new LinkedList<Mensaje>();
        }
        return l;
    }
    
    public static DefaultListModel listaContactos(){
        List<String> contactos = new LinkedList<String>();
        contactos.addAll(inbox.keySet());
        
        DefaultListModel dlm = new DefaultListModel();
        dlm.addElement("");
        for(String c : contactos){
            dlm.addElement(c);
        }
        
        return dlm;
    }
    
    public void addFriend(String friendname) throws RemoteException{        
        if(friendname != null && !friendname.isEmpty() && !this.username.equals(friendname)){
            if(servidor.existeUsuario(friendname)){
                if(inbox.containsKey(friendname)){
                    cliente_gui.displayErrorsChat("El usuario ya pertenece a tu lista de amigos");
                }
                else {
                    List<Mensaje> l = inbox.get(friendname);
                    if(l == null){
                        l = new LinkedList<Mensaje>();
                        inbox.put(friendname, l);
                    }
                }
            }
            else {
                cliente_gui.displayErrorsChat("El usuario no existe");
            }
        }
        else {
            cliente_gui.displayErrorsChat("El nombre de tu amigo no puede ser vacio, ni ser tu mismo");
        }
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
