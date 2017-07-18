
import java.util.ArrayList;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Gus
 */
public class Test {
    public static void main(String[] args){
        ConnectFour cf = new ConnectFour();
        ArrayList<Integer> testlist = new ArrayList<>(43);
        testlist.add(2);
        
        testlist.add(2);
        testlist.add(0);
        testlist.add(0);
        testlist.add(1);
        testlist.add(1);
        testlist.add(2);
        testlist.add(2);
        
        testlist.add(0);
        testlist.add(0);
        testlist.add(0);
        testlist.add(1);
        testlist.add(1);
        testlist.add(2);
        testlist.add(0);
        
        testlist.add(0);
        testlist.add(0);
        testlist.add(0);
        testlist.add(1);
        testlist.add(2);
        testlist.add(1);
        testlist.add(0);
        
        testlist.add(0);
        testlist.add(0);
        testlist.add(0);
        testlist.add(2);
        testlist.add(0);
        testlist.add(0);
        testlist.add(0);
        
        testlist.add(0);
        testlist.add(0);
        testlist.add(0);
        testlist.add(0);
        testlist.add(0);
        testlist.add(0);
        testlist.add(0);
        
        testlist.add(0);
        testlist.add(0);
        testlist.add(0);
        testlist.add(0);
        testlist.add(0);
        testlist.add(0);
        testlist.add(0);
        
        System.out.println(cf.getState(testlist));
        System.out.println(cf.legalMoves(testlist).size());
    }
}


/*
0 | 1 | 2 | 3 | 4 | 5 | 6 | 
0 | 0 | 0 | 0 | 0 | 0 | 0 | 
0 | 0 | 0 | 0 | 0 | 0 | 0 | 
0 | 0 | 0 | 2 | 0 | 0 | 0 | 
0 | 0 | 0 | 1 | 0 | 1 | 0 | 
0 | 0 | 0 | 1 | 1 | 2 | 0 | 
2 | 0 | 0 | 1 | 1 | 2 | 2 | 
*/














