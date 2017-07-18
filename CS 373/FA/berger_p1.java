//package p1;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

public class berger_p1{
    public static void main(String[] args) throws IOException{
//      String fileName = "sample_1.txt";
      
//      Scanner file = new Scanner(new File(fileName));
//      String line = file.nextLine();
//      System.out.println(line);
      ArrayList<String> states = new ArrayList<String>();
      ArrayList<String> pos = new ArrayList<String>();
      ArrayList<String> trans = new ArrayList<String>();
      String[] code = {};
      String[] path;
      Scanner userIn = new Scanner(System.in);
      while(true){
        String input = userIn.nextLine();// "/Users/SnowFox/Desktop/sample_2.txt";    System.out.println("here");
        path = input.split("\\s+", 2); 
        if(path.length == 2){
          break;
        } else {
          System.out.println("Please enter the path followed by the code");
        }
      }
      String wait = path[1];
      code = wait.split("");
      
      try{
      FileReader fr = new FileReader(path[0]);
      BufferedReader bf = new BufferedReader(fr);
      String line;
      String[] lines;
      String blerg = "";
      while(true){
        line = bf.readLine();
        try{
          lines = line.split("\t", 4);

          if(lines[0].startsWith("tr")){
            break;
          }
          
            states.add(lines[1]);
            try{
              if(lines[2].startsWith("ac") || lines[3].startsWith("ac")){
                pos.add(lines[1]);
              }
            } catch (ArrayIndexOutOfBoundsException outof){
              
            }
            try{    
              if(lines[2].startsWith("st") || lines[3].startsWith("st")){
              blerg = lines[1];
            }
          } catch (ArrayIndexOutOfBoundsException outof){
            
          }
            
        } catch (NullPointerException outof) {
          break;
      }
      }

      boolean first = true;
      while(true){
        if(first){
          lines = line.split("\t", 4);
          trans.add(lines[1]);
          trans.add(lines[2]);
          trans.add(lines[3]);
        first = false;
        }
        line = bf.readLine();
        if(line == null){
          break;
        }
        lines = line.split("\t", 4);
        trans.add(lines[1]);
        trans.add(lines[2]);
        trans.add(lines[3]); 
      }
      bf.close();

      ArrayList<String> current = new ArrayList<String>();
      current.add(blerg);
      boolean moved = false;
      boolean already = false;
      int hold;
      for(int j = 0; j < code.length -1; j++){
        moved = false;
        hold = current.size();
        for(int k = 0; k < hold; k++){
          for(int i = 0; i < (trans.size() /3); i++){
            if(current.get(k).equals(trans.get(i*3))){
              if(code[j+1].equals(trans.get((i*3) +1))){
                for(int b = 0; b < (current.size() - hold); b++){//
                  if(current.get(b + hold).equals(trans.get((i*3) +2))){//
                    already = true;//
                  } //
                }//
                if(!already){//
                  current.add(trans.get((i*3) + 2));
                  moved = true;
                }//
                already = false;
              }
            }
          }
        }
        if(moved == true){
          for(int l = 0; l < hold; l++){
            current.remove(0);
          }
        }
      }
      ArrayList<String> acc = new ArrayList<String>();
      boolean good = false;
      for(int n = 0; n < current.size(); n++){
        for(int g = 0; g < pos.size(); g++){
          if(pos.get(g).equals(current.get(n))){
            acc.add(pos.get(g));
            good = true;
          }
        }
      }
      if(good){
        System.out.print("accept");
        for(int r = 0; r < acc.size(); r++){
          System.out.print(" " + acc.get(r));
        }
      } else{
        System.out.print("reject");
        for(int p = 0; p < current.size(); p++){
          System.out.print(" " + current.get(p));
        }
      }
      
      System.out.println("");
      
      } catch (FileNotFoundException fn){
        System.out.println("File not found!");
      }
    }
    

    
    

}
