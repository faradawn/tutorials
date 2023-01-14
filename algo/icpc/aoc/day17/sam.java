import java.util.*;
import java.io.*;
import java.lang.Math;

public class Solution {
    //Idea: Part I: simulate with HashSet, add the coordinates of each tetris as if the bottom block is on row 0 into HashSet[] "tetris"
    //  Also record "top" for the top height after each block stops.
    //  Then for every iteration of the simulation of some block i (0 <= i <= 4), initialize it by moving the values in tetris[i] up by (top + 4)
    //      (problem statement incorrectly said we should initialize 3 above top, but actually it is 4 above)
    //  Then simulate it falling by alternating "turn"

    //Part II: observe whenever we iterate "wind" and return to the start of "wind", the height increase is the same (except the first cycle)
    //  Credit to Prof. Borja Sotomayor's idea
    //  So we compute the height increase and block # increase per cycle (recorded in top_changes and e_changes, respectively), 
    //  and use this to compute the final height
    public static int[][] t1 = {{0, 2}, {0, 3}, {0, 4}, {0, 5}}, t2 = {{0, 3}, {1, 2}, {1, 3}, {1, 4}, {2, 3}}, t3 = {{0, 2}, {0, 3}, {0, 4}, {1, 4}, {2, 4}}, t4 = {{0, 2}, {1, 2}, {2, 2}, {3, 2}}, t5 = {{0, 2}, {0, 3}, {1, 2}, {1, 3}};
    //compress int coordinates to a single long
    public static long convert(int a, int b){
        return 7 * (long)a + b;
    }

    //move elements in set vertically, up for "dir" distance
    public static HashSet<Long> move_ver(HashSet<Long> set, long dir){
        HashSet<Long> res = new HashSet<>();
        for(long ele : set){
            res.add(ele + 7 * dir);
        }
        return res;
    }

    //move elements in set horizontally, towards the right by one if c == '>', otherwise left by once
    public static HashSet<Long> move_hor(HashSet<Long> set, char c){
        HashSet<Long> res = new HashSet<>();
        int dir = c == '>' ? 1 : -1;
        for(long ele : set){
            long targ_col = ele % 7 + dir;
            //unmovable, set dir = 0 (res will be have the same values as set due to 0 offset)
            if(targ_col < 0 || targ_col >= 7){
                dir = 0;
                break;
            }
        }
        for(long ele : set){
            res.add(ele + dir);
        }
        return res;
    }

    //true if m1 intersects with m2 (made sure m1 is smaller than m2 in my code in "main")
    //  but could be easily optimized to make m1 smaller than m2 (just swap them, then swap back after finished, more efficient).
    public static boolean intersect(HashSet<Long> m1, HashSet<Long> m2){
        for(long ele : m1){
            if(m2.contains(ele)){
                return true;
            }
        }
        return false;
    }

    //max height of elements in a set
    public static long max_height(HashSet<Long> set){
        long max = 0L;
        for(long ele : set){
            max = Math.max(max, ele / 7);
        }
        return max;
    }

    @SuppressWarnings("unchecked")
    public static void main(String[] args){
        long N = 100000L;
        char[] wind = read_all_String()[0].toCharArray();
        //5 type of tetris block's coordinate compressed and stored in HashSet, with the bottom block at
        //  row 0, and the vertical position the same as how they appear each time
        List<int[][]> shape = new ArrayList<>();
        shape.add(t1); shape.add(t2); shape.add(t3); shape.add(t4); shape.add(t5); 
        HashSet<Long>[] tetris = new HashSet[5];
        HashSet<Long> rocks = new HashSet<>();
        for(int i = 0; i < 5; ++i){
            tetris[i] = new HashSet<>();
            for(int[] point : shape.get(i)){
                tetris[i].add(convert(point[0], point[1]));
            }
        }
        //fill rocks at row 0
        for(long i = 0; i < 7L; ++i){
            rocks.add(i);
        }
        //old_top and old_e for observing cycle of height increase through cycling through "wind" array
        long top = 0, old_top = 0, ans1 = 0, old_e = -1;
        //wind_ind is for current index of wind in the "wind" array
        //simulate block fall if turn == 1, else simulate wind shift
        int wind_ind = 0, turn = 0;

        //first_10000_top records the top in first 10000 iterations, useful later
        List<Long> new ArrayList<>(), e_changes = new ArrayList<>(), first_10000_top = new ArrayList<>();
        for(long _e = 0; _e < N; ++_e){
            //initialize the (_e % 5)-th type of block to initial height of top + 4
            HashSet<Long> block = move_ver(tetris[(int)(_e % 5)], top + 4);
            //to detect whether we reached the start of "wind" again
            boolean cycled_back = false;
            while(true){
                //simulate fall
                if(turn == 1){
                    HashSet<Long> block_fall_once = move_ver(block, -1);
                    --turn;
                    if(intersect(block_fall_once, rocks)){
                        break;
                    }
                    block = block_fall_once;
                }
                //simulate wind shift
                else{
                    //cycled back to the start of wind array, need to record in top_changes and e_changes after simulating
                    //  this block
                    //Since after all our answer for part II depends on how many blocks to simulate, not wind_ind
                    //  it would be better to show the effect each cycle has on "top" by updating top_changes based on cycles on block #, not wind_ind
                    if(wind_ind == 0 && top != 0L){
                        cycled_back = true;
                    }
                    HashSet<Long> block_shift_once = move_hor(block, wind[wind_ind]);
                    ++turn;
                    if(!intersect(block_shift_once, rocks)){
                        block = block_shift_once;
                    }
                    wind_ind = (wind_ind + 1) % wind.length;
                }
            }

            rocks.addAll(block);
            //update top height by maxing the original top height and the top height of elements in current block
            //  when it stops falling
            top = Math.max(top, max_height(block));

            if(_e < 10000)
                first_10000_top.add(top);

            //add the increase of top from each full cycle of wind to "top_changes" to observe cycle
            //add increase of blocks to "e_changes"
            if(cycled_back){
                top_changes.add(top - old_top);
                old_top = top;
                e_changes.add(_e - old_e);
                old_e = _e;
            }

            //storing Part I's answer
            if(_e == 2021L){
                ans1 = top;
            }
        }
        System.out.println("Task 1: " + ans1);

        //observe the cycle manually
        
        //print(top_changes);
        
        //for sample input, each cycle contains 5 elements
        //for real input, each cycle has 1 element only
        
        //we also notice each cycle after the first deals with exactly 1755 blocks, causing the same increase of "top" (2768)
        
        //print(e_changes);

        long N2 = 1000000000000L;
        //compute top for the first cycle (which is an exception)
        N = N2 - e_changes.get(0);
        top = top_changes.get(0);

        //compute top for all full cycles
        top += (N / e_changes.get(1)) * top_changes.get(1);

        //deal with the remainder (leftover part for the last incomplete cycle)
        N %= e_changes.get(1);

        //simulate as if we are on the start of the 3rd cycle (so that we are far from the ill effects
        //  of the first cycle) and simulating the leftover part (from the start of the 3rd cycle "st" to "st + N")
        long st = e_changes.get(0) - 1 + e_changes.get(1), end = st + N;
        top += first_10000_top.get((int)end) - first_10000_top.get((int)st);
        System.out.println("Task 2: " + top);
    }
}