# eight queens problem
I learned about backtracking and just had to use it.

This program prints the 92 possible ways of positioning 8 queens on a chessboard such that no queen threatens another.

Considering that there are 64 choose 8 possible ways to place the pieces across the board (~4.4 trillion), I'm happy to say this program is reasonably fast. It runs in 8ms on my machine with optimizations turned on.

### solution
What helped me the most in understanding the nature of backtracking was visualizing the paths towards each given solution as a tree: at the root, an empty board.
Each successive level adds a piece to the board, and each new addition can either be considered correct or incorrect. If incorrect, we effective prune that subtree by backtracking.

The other breakthrough I had was recognizing that one can avoid using a hash map to memoize previous states by simply only placing the next piece at some point after the last played piece. This ensures that no duplicate positions are followed, and also avoids the hassle of programming a hash map for the previous states (although the chess board could conveniently be hashed into a unique 64 bit integer).

### credits
The wikipedia page on backtracking was quite useful.
