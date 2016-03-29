package common;

import java.io.Serializable;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

/**
 *
 * @author roman
 */
public class Mensaje implements Serializable{
    private static final long serialVersionUID = 6473037307367070437L;
    private String cuerpo, remitente, fecha;
    
    public Mensaje(String cuerpo, String remitente){
        this.cuerpo = cuerpo;
        this.remitente = remitente;
        this.fecha = obtenerFecha();
    }
    
    private String obtenerFecha(){
       //getting current date and time using Date class
       DateFormat df = new SimpleDateFormat("dd/MM/yy HH:mm:ss");
       Date dateobj = new Date();
       System.out.println(df.format(dateobj));

       /*getting current date time using calendar class 
        * An Alternative of above*/
       Calendar calobj = Calendar.getInstance();
       return df.format(calobj.getTime());
    }
    
    public String getCuerpo(){
        return cuerpo;
    }
    
    public String getRemitente(){
        return remitente;
    }
    
    public String getFecha(){
        return fecha;
    }
}