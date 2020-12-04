draughts（毛哥规则版本）
=
The project is a personal project and students need to work independently.Students need to use C language to implement a "checkers" subroutine (hereinafter referred to as the brain program), using stdin to receive the opponent drop situation, after calculation, using stdout to output their own drop (see input output format).Algorithms are unlimited, but there are time and memory limitations (see game rules).


Core algorithm
-

#### Part 1: Search functions
&emsp;&emsp;Adopted two kinds of search function, the first is ab, the second is the PVS search, the main variable direction search, is a variant of alpha, beta pruning, and before it first assumption is to find the best value (the value of alpha), search, and then apply zero window for quick judging the correctness of this hypothesis: if zero window search result is the value of alpha, or less then before the hypothesis is correct, that this move will not have a better valuation, the program will abandon this move directly.In this case, the search time will be greatly reduced.<br>
&emsp;&emsp;But if the null window search results show that the previous assumption is wrong, then a regular window search needs to be repeated.In this case, the PVS algorithm actually performs one more search.However, due to the time consuming of zero-window search, alphabeta search was used for the first layer ranking with a search depth of 5, followed by PVS with a search depth of 14<br>
&emsp;&emsp;If you want PVS to search significantly better than ab, you should work on the valuation function, using different valuation functions <br> in different situations (e.g., opening, final, 25-35 steps, etc.)

#### Part 2: Hash tables
&emsp;&emsp;Use hash table to increase the speed of my search <br>
&emsp;&emsp;The first is to implement a hash table.At the beginning of the game, create a 3d array and then fill the array with random numbers.If the hash value of a situation is required, the random numbers corresponding to all the pieces on the board in the array Z are added.(To get a 32-bit hash, the elements in the array Z should be 32 bits;To get a 64-bit hash, the elements in the array Z should be 64-bit.<br>
&emsp;&emsp;For each node to be searched, a 32-bit hash value (a 32-bit modulus for the hash table size) is calculated to determine the position of the situation in the hash table.Compute another 64-bit hash value (Checksum) to verify that the item in the table is the desired item
The Zobrist method can be solved by incremental calculation, without adding up all the pieces at each time.When searching for a new node, the hash value of the child node can be calculated by subtracting the corresponding random number from the hash value before the pawn moves and adding the corresponding random number after the pawn moves.)<br>
&emsp;&emsp;Board games, on the other hand, generally do not change much from move to move, so a more efficient increment method can be used to calculate the hash.Put the hash into the MakeMove/UnmakeMove process.<br>
&emsp;&emsp;The process of adding and subtracting a hash value can also be replaced by (bitwise) xor operations.<br>
