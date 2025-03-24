package AnotherJava.Iniziamo;
import java.util.ArrayList;
public class PrimaClasse {
    
    public static void main(String[] args) {
        int var1 = 10;
        int var2 = 0x1a;
        char carattere = 'A';
        //In this way we can create a new ArrayList by using in the angular brackets the type of the item.
        ArrayList<String> name = new ArrayList<String>(); 
        name.add("Fabrizio");
        name.add("Java");

        
        System.out.println("Hello world!"+(var1+var2));
        System.out.println(carattere+" "+var1+" "+var2);
    }
}
