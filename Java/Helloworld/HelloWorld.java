package Java.Helloworld;
import java.time.LocalDate;
//Stiamo creando una classe di nome HelloWorld
public class HelloWorld { //Distanziare la graffa con uno spazio

    private static String nomeCorso = "Ingegneria del Software";
    /**
     * tipologia javadoc per commentare con le parole chiavi all'interno dei commenti
     * @param args strighe che possono essere passate al main 
     */
    public static void main(String[] args) {
        System.out.println("Hello World :)"); //System = Classe Out = Attributo println = metodo  
        System.out.println(nomeCorso);
        HelloWorld hw = new HelloWorld(); //Abbiamo creato un istanza della classe di HelloWorld
        System.out.println(hw.nomeCorso); //Stiamo utilizzando l'oggeto hw per richiamare l'attributo nomeCorso
        hw.stampaData("ciaone"); //Stiamo richiamndo un metodo della classe HelloWorld
        //StampaHelper.stampa(hw.nomeCorso); //Abbiamo richiamato un metodo di un altra classe in un altro file
    }
    private void stampaData(String saluto) { //Stiamo creando una funzione di nome stampaData gli stiamo passando un parametro
        System.out.println("7 Marzo 2024");
        System.out.println(saluto);
        LocalDate d = LocalDate.now(); //now è un metodo statico
        System.out.println(d);
        float f = 1.2f;
        Float dato = new Float(f);
        
    }
}