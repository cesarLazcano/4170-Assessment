========================================================================
Author: Cesar Lazcano
4170 Trading Coding Assessment

=======================================================================
Files:
4170.cpp

=======================================================================
Run Instructions:
-on the cmd line find your way to the working directory of this file
-to compile enter the following command
        g++ -std=c++11 4170.cpp
-to run enter the following command
        ./a.out

The program will run and require a single user input for problem 2 dice roll
========================================================================
/////////////////////////////////////////////////////////////////////////////
Other notes:

Problem1:
        I broke down this problem into the two parts to facilitate the readability and coding
        I used a dynamic approach that seems to make use of more space than needed but allows
        terminate faster than some other methods using more brute force approaches.
        
        Run time: O(nlog(n)), due to the way we dynamically iterated the for each coin 


Problem 2:
        The dice game I realized does not need to keep track of the individual dice. We only
        need to simulate the sum so I figure that a more efficient strategy was to simulate a roll
        by randomizing rolls between the minimum and maximum possible values

        Run time: O(n), as we simulate each game

Problem 3:
        I figured that a mapping of column and row checks was the most efficient strategy.
        I managed to get a pretty fast and execution given the use of the standard library.
        My problems became apparent when trying to validate used row/columns are figuring a way 
        to swap. A clear solution didn't hit me in reasonable time.

        Run time: O(nlog(n)), we used max finding algorithms to find max value in rows and column
                and repeated on mapped/used columns.

/////////////////////////////////////////////////////////////////////////////
