package Java.ciao;

import java.io.InputStreamReader;
import java.io.BufferedReader;

public class tentativi {
    
    public static void main(String[] args) {
        String nome=" ";
        InputStreamReader input = new InputStreamReader(System.in);
        BufferedReader tastiera = new BufferedReader(input);
        System.out.println("Metti il nome: ");
        try {
           nome = tastiera.readLine();
        } catch (Exception e) {
            e.printStackTrace();
        }
        System.out.println(nome);
        int valore=2,valore2=4;
        valore=valore+valore2;
        System.out.println(valore);
        
    }
}
