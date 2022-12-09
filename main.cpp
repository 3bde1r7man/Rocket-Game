#include "RocketGame.h"


int main() {
   RocketGame rocketGame;
   int ch;
   while (true)
   {
	   cout << "1- play with onther human\n2- play with computer\n--> ";
	   cin >> ch;
	   switch (ch)
	   {
	   case 1:
		   rocketGame.runHuman();
		   exit(0);
	   case 2:
		   rocketGame.runPC();
		   exit(0);
	   default:
		   break;
	   }
   }
}