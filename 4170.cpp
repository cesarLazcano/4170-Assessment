/*
Author Cesar Lazcano
4/22/109

4170 Trading Coding Assessment
*/

#include <array>
#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <map>

const std::string DIVIDER = "************************************";
const int TARGET_VALUE = 500;

// create coins as enum
enum Coins {
  U1 = 1,
  U5 = 5,
  U10 = 10,
  U20 = 20,
  U50 = 50,
  U100 = 100
};


// helper function for problem 1
// use a table to plot store solutions
int combinations()
{
  // table will store number of solutions dynamically, start base case
  std::array<int, TARGET_VALUE+1> table = { 0 };
  table[0] = 1;

  // given our coins we will have every index account for x amount of solutions
  // as the index increases we will use higher valued coins efficiently
  int i;
  for (i = U1; i <= TARGET_VALUE; i++)
    table[i] += table[i - U1];

  for (i = U5; i <= TARGET_VALUE; i++)
    table[i] += table[i - U5];

  for (i = U10; i <= TARGET_VALUE; i++)
    table[i] += table[i - U10];

  for (i = U20; i <= TARGET_VALUE; i++)
    table[i] += table[i - U20];

  for (i = U50; i <= TARGET_VALUE; i++)
    table[i] += table[i - U50];

  for (i = U100; i <= TARGET_VALUE; i++)
    table[i] += table[i - U100];

  return table[TARGET_VALUE];
}


// determine dynamically, the ways we can reach U500 
// this strategy allows use to do less iterations of
// the solutions than some more brute force approaches, learned strategy for
// similar question in coursework using USD coins
void problem1()
{
  std::string part1 = "On Pandora, the currency is called Unob, U. There are six coins in circulation: \n"
    "U1, U5, U10, U20, U50, U100\n"
    "It is possible to make U500 in the following way : \n"
    "3xU100 + 2xU50 + 4xU20 + 1xU10 + 1xU5 + 5xU1\n";

  //part 1, retrieve sum for first part of question : 3xU100 + 2xU50 + 4xU20 + 1xU10 + 1xU5 + 5xU1 
  // store in arrays, simple and fast execution
  std::array<Coins, 6> coins = { U1,U5,U10,U20,U50,U100 };
  std::array<int, 6> quantities = { 5,1,1,4,2,3 };

  int sum = 0;
  const int TARGET_VALUE = 500;
  for (int i = 0; i < quantities.size(); i++)
  {
    sum += coins[i] * quantities[i];
  }
  // check for match
  std::cout << part1 << std::endl;
  if (sum == TARGET_VALUE)
    std::cout << "Yes it matches U500!" << std::endl;
  else
    std::cout << "No, you can't generate U500" << std::endl;

  // part 2
  // How many different ways can U500 be made using any number of coins? 
  // use a dynamic approach for efficiency
  std::string part2 = "How many different ways can U500 be made using any number of coins? \n";
  int ways = combinations();
  std::cout << "Number of ways to generate U" << TARGET_VALUE << " is " << ways << std::endl;
}


// determine the probability by running simulations of dice rolls
void problem2()
{
  std::string problem2 = "Problem 2. Gregor has eight five-sided dice, each with faces numbered 1, 2, 3, 4, 5.\n"
    "Oberyn has four ten-sided dice, each with faces numbered 1, 2, 3, 4, 5, 6, 7, 8, 9, 10.\n"
    "Gregor and Oberyn roll their dice and compare totals: the highest total wins.\n"
    "The result is a draw if the totals are equal.\n"
    "What is the probability that Gregor beats Oberyn (i.e. Gregor wins / N games)?\n";
  std::cout << problem2 <<  std::endl;

  int n_games;
  std::cout << "Enter number of dice roll games to simulate" << std::endl;
  std::cin >> n_games;

  // initialize values
  int gregor_Ws = 0;
  const int gregor_dice_sides = 5;
  const int gregor_dice = 8;
  const int oberyn_dice_sides = 10;
  const int oberyn_dice = 4;
  const int gregor_roll_max = gregor_dice_sides * gregor_dice;
  const int oberyn_roll_max = oberyn_dice_sides * oberyn_dice;

  // simulation of games
  // rather than have a bad run time we can simulate the sum of the rolls intead of rollin each die
  srand(time(NULL));
  for (int i = 0; i < n_games; i++)
  {
    // simulations
    int gregor_sim = (rand() % gregor_roll_max) + gregor_dice_sides;
    int oberyn_sim = (rand() % oberyn_roll_max) + oberyn_dice_sides;
    std::cout << ">> gregory roll: " << gregor_sim << "\toberyn roll: " << oberyn_sim << std::endl;
    if (gregor_sim > oberyn_sim)
      gregor_Ws++;
    else if (gregor_sim == oberyn_sim)
      n_games--; // ties dont count
  }

  float prob = gregor_Ws / float(n_games) * 100;
  std::cout << "probability that Gregor beats Oberyn: " << prob << "%" << std::endl;
}


// approach by keeping a map of used columns to record used row and columns
// was running low on time and went for an approach that has the right start
// but needs additional check to swap for optimal values
void problem3()
{
  std::string prob3 = " Find the maximum value from the matrix where each number is the only one in his row and column.\n"
    "For example, for the matrix below the maximum value equals 3315 ( = 863 + 383 + 343 + 959 + 767): \n";
  std::cout << prob3 << std::endl;

  int matrix[15][15] = {
    7,53,183,439,863,497,383,563,79,973,287,63,343,169,583,
    627,343,773,959,943,767,473,103,699,303,957,703,583,639,913,
    447,283,463,29,23,487,463,993,119,883,327,493,423,159,743,
    217,623,3,399,853,407,103,983,89,463,290,516,212,462,350,
    960,376,682,962,300,780,486,502,912,800,250,346,172,812,350,
    870,456,192,162,593,473,915,45,989,873,823,965,425,329,803,
    973,965,905,919,133,673,665,235,509,613,673,815,165,992,326,
    322,148,972,962,286,255,941,541,265,323,925,281,601,95,973,
    445,721,11,525,473,65,511,164,138,672,18,428,154,448,848,
    414,456,310,312,798,104,566,520,302,248,694,976,430,392,198,
    184,829,373,181,631,101,969,613,840,740,778,458,284,760,390,
    821,461,843,513,17,901,711,993,293,157,274,94,192,156,574,
    34,124,4,878,450,476,712,914,838,669,875,299,823,329,699,
    815,559,813,459,522,788,168,586,966,232,308,833,251,631,107,
    813,883,451,509,615,77,281,613,459,205,380,274,302,35,805
  };

  // use map to store row and column of maxes
  std::map<int, int> row_map;
  int sum = 0;
  for (int row = 0; row < 15; row++)
  {
    auto beg = std::begin(matrix[row]);
    auto end = std::end(matrix[row]);
    int *max = std::max_element(beg,end);
    int col = max - beg;
    auto it = row_map.find(col);

    // validation check
    while ( it != row_map.end())
    { 
      // col taken, find another max col
      int temp = matrix[row][col];
      matrix[row][col] = 0;
      beg = std::begin(matrix[row]);
      end = std::end(matrix[row]);
      max = std::max_element(beg, end);
      col = max - beg;
      it = row_map.find(col);
    }
    row_map.insert(std::pair<int, int>(col, row));
    sum += *max;
    std::cout <<  *max << std::endl;
  }
  std::cout << ">> Sum = " << sum << std::endl;

}


// Driving code in main method
// calls functions specific to each question asked
int main()
{
  
  problem1();

  std::cout << DIVIDER << std::endl;

  problem2();

  std::cout << DIVIDER << std::endl;

  problem3();

  return 0;
}

