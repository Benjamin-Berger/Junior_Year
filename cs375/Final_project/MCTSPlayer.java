
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
public class MCTSPlayer extends Player{
    MCTS ai;
    int rounds;
    int playouts;
    
    public MCTSPlayer(int rounds, int playouts){
        this.rounds = rounds;
        this.playouts = playouts;
    }
    
    public void restart(){
        
    }
    
    
     public byte getMove(byte lastMove, ArrayList<Byte> board) throws Exception{
            ai = new MCTS(cf, board.get(0), board, playouts);
            int c = 0;
            boolean solved = false;
            while((!solved)&&c<rounds) {
                solved = ai.round();
                c++;
                //if(c%10000==0)System.out.println(c);
            }
            //System.out.print(":"+c+":");
            byte move = ai.getMove();
            //System.out.println(move);
            return move;
    }
}
