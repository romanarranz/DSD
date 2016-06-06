package cliente;

import common.Utils;
import java.rmi.Naming;
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

/**
 *
 * @author roman
 */

public class Nodo implements INodo{
    private static INodo stub;
    private static Registry reg;
    private static String ip;
    private static Integer id = 0;
    private static boolean participante = false;
    private static boolean coordinador = false;
    private static Integer id_coordinador = 0;
    private static Nodo me = null;
    
    // Esta va a ser la topologia en anillo que debe conocer cada nodo
    private static List<Integer> ring = new LinkedList<Integer>();
    
    public Nodo(String ip, int id){
        this.ip = ip;
        this.id = id;
        me = this;
    }
    
    @Override
    public void enviarMensajeEleccion(int id) throws RemoteException {
        procesoEleccion(id);
    }
    
    @Override
    public void enviarMensajeCoordinador(int id_coordinador) throws RemoteException {
        participante = false;
        System.out.println("Proceso "+id_coordinador+" es el coordinador asi que "+this.id+" ya no participa");
        this.id_coordinador = id_coordinador;
        
        Nodo.actualizarAnillo();
        this.imprimeAnillo();
            
        // le pasamos el mensaje de coordinador al vecino de la derecha
        Integer vecino = ring.get( (ring.indexOf(id)+1) % ring.size());
        try{
            Thread.sleep(2000);
            INodo nodo_vecino = (INodo) reg.lookup(vecino.toString());
            nodo_vecino.enviarMensajeCoordinador(id_coordinador);
        }
        catch(Exception e){
            e.printStackTrace();
        }
    }    
   
    public void procesoEleccion(int ideleccion) throws RemoteException{
        
        // antes de seleccionar vecino actualizo la topologia de anillo
        Nodo.actualizarAnillo();
        this.imprimeAnillo();
        
        if(id == ideleccion){ // si el id recibido es el propio receptor se marca como coordinador
            coordinador = true;
            participante = false;
            id_coordinador = this.id;
            System.out.println("Proceso "+id_coordinador+" es el coordinador y ya no participa");

            Nodo.actualizarAnillo();
            this.imprimeAnillo();

            // le pasamos el mensaje de coordinador al vecino de la derecha
            Integer vecino = ring.get( (ring.indexOf(id)+1) % ring.size());
            try{
                Thread.sleep(2000);
                INodo nodo_vecino = (INodo) reg.lookup(vecino.toString());
                System.out.println("vecino seleccionado"+vecino);
                nodo_vecino.enviarMensajeCoordinador(id_coordinador);
            }
            catch(Exception e){
                e.printStackTrace();
            }
        }
        else if(ideleccion < this.id){
            if(!participante)
                participante = true; // si no estaba marcado como participante se marca
            System.out.println(ideleccion+" < "+this.id);

            Nodo.actualizarAnillo();
            this.imprimeAnillo();
            
            // le pasamos el mensaje de coordinador al vecino de la derecha
            Integer vecino = ring.get( (ring.indexOf(id)+1) % ring.size());
            try{
                Thread.sleep(2000);
                INodo nodo_vecino = (INodo) reg.lookup(vecino.toString());
                System.out.println("vecino seleccionado"+vecino);
                nodo_vecino.enviarMensajeEleccion(this.id);
            }
            catch(Exception e){
                e.printStackTrace();
            }
        }
        else {            
            if(!participante){
                participante = true;
                System.out.println(ideleccion+" >= "+this.id);
                
                Nodo.actualizarAnillo();
                this.imprimeAnillo();
            
                // le pasamos el mensaje de coordinador al vecino de la derecha
                Integer vecino = ring.get( (ring.indexOf(id)+1) % ring.size());
                try{
                    Thread.sleep(1000);
                    INodo nodo_vecino = (INodo) reg.lookup(vecino.toString());
                    System.out.println("vecino seleccionado"+vecino);
                    nodo_vecino.enviarMensajeEleccion(this.id);
                }
                catch(Exception e){
                    e.printStackTrace();
                }  
            }            
        }
    }   
    
    public static void actualizarAnillo(){
        try{
            String[] names = Naming.list("//" + ip + "/");
            List<Integer> nodes = new LinkedList<Integer>();
            for (int i = 0; i < names.length; i++){
                // parto la cadena por el caracter "/" y me quedo con el ultimo campo que seria el id del nodo (explode de php)
                String[] split = names[i].split("/");                
                // convierto la cadena que contiene el id del nodo a entero y lo meto en una lista
                nodes.add(Integer.parseInt(split[split.length-1]));
            }
            ring = nodes;
        }
        catch(Exception e){
            e.printStackTrace();
        }
    }
    
    public Integer getIdCoordinador(){return this.id_coordinador;}
    
    public void imprimeAnillo(){
        for(int i = 0; i<ring.size(); i++){
            if(this.getIdCoordinador() == ring.get(i))
                System.out.print("*");
            if(participante)
                System.out.print("+");
            else 
                System.out.print("-");
            
            System.out.print(ring.get(i)+" ");
        }
        System.out.print("\n");
    }
    
    public void inicioAleatorio() throws InterruptedException{                
        try{
            participante = true;
            procesoEleccion(0);
        }
        catch(RemoteException e){
            e.printStackTrace();
        }       
    }   
    
    // Instrucciones que se van a ejecutar si se cierra el programa con ctrl+c o acaba el programa
    public void attachShutDownHook(){
        Runtime.getRuntime().addShutdownHook(new Thread() {        
            @Override
            public void run() {
                try{
                    reg.unbind(Integer.toString(id));
                    UnicastRemoteObject.unexportObject((Remote) me, true);
                    System.out.println("Se ha desvinculado el nodo "+id);
                }
                catch(Exception e){
                    e.printStackTrace();
                }
            }
        });
        System.out.println("");
    }
   
    public static void main(String[] args) {
        String host = args[0];
	String id = args[1];
        
        Utils.setCodeBase(INodo.class);                   
        
	try {
            Nodo n = new Nodo(host, Integer.parseInt(id));
            stub = (INodo)UnicastRemoteObject.exportObject(n, 0);
            
            reg = LocateRegistry.getRegistry();
            reg.rebind(id, stub);
            
            n.attachShutDownHook();
            
            System.out.print("Desea empezar la eleccion y/n: ");
            Scanner s = new Scanner(System.in);
            System.out.print("\n");
            
            if(s.next().equals("y")){
                n.inicioAleatorio();
            }
            
            while(true){	
                Thread.sleep(5000);                
            }            
	} 
	catch (Exception e){
            e.printStackTrace();
        }
        
        System.exit(0);
    }
}