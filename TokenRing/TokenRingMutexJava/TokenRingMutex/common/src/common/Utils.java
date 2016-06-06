package common;

/**
 *
 * @author roman
 */
public class Utils {
    
    public static final String CODEBASE = "java.rmi.server.codebase";
    
    public static void setCodeBase(Class<?> c){
        String ruta = c.getProtectionDomain().getCodeSource().getLocation().toString();
        
        String path = System.getProperty(CODEBASE);
        
        // Se ha establecido ya el codebase?
        // si se llaman varias veces al codebase solucionamos el problema
        if(path != null && !path.isEmpty()){
            ruta = path + " " + ruta;
        }
        
        System.setProperty(CODEBASE, ruta);
        
        System.out.println(CODEBASE+"="+ruta);
    }
}
