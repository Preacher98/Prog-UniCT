package Java.ArrayList;
import java.util.ArrayList;


public class ArrayListProva {

    public static void main(String[] args){
        //In this way we can create a new ArrayList by using in the angular brackets the type of the item.
        ArrayList<String> nameList = new ArrayList<String>();
        //We can add a new item in the ArrayList
        nameList.add("Fabrizio");
        nameList.add("Hello");

        //To print the whole array we can use:
        System.out.println(nameList);
        
    }   
}
