/* Varvara Vorobieva
* Chapter 20 Assignment
*CISC 187
* 4/5/2022
*/
 
#include <iostream>
#include <iomanip>
#include <string>
#include "MarketQueue.h"
using namespace std;

//Function prototypes

void DisplayMenu(MarketQueue &);
void AddName(MarketQueue &);
void PlaceOrder(MarketQueue &);
void CountNames(MarketQueue &);
void DrawWinner(MarketQueue &);
void DisplayLine(MarketQueue &);
void Leave();

int main()
{
   MarketQueue FishLine;
   DisplayMenu(FishLine);
   
    return 0;
}


//Menu displaying function 
void DisplayMenu(MarketQueue &FishLine)
{
    //While testvar is not 7, display menu
    int menuOption=0;
    string option="";
    while (menuOption!=6)
    {
      cout<<"Welcome to San Pedro Fish Market!\n";
      cout<<"1. Add a name \n" ;
      cout<<"2. Place an Order \n";
      cout<<"3. Count names in queue \n";
      cout<<"4. Draw Raffle Number \n";
      cout<<"5. Display Line \n";
      cout<<"6. Exit Menu \n";
      cout<<"Please choose your menu option.\n";
      
      getline(cin,option);
      menuOption=stoi(option);
      
      if (menuOption==1)
      {
         AddName(FishLine);
      }
      else if (menuOption==2)
      {
         PlaceOrder(FishLine);
      }  
      else if (menuOption==3)
      {
         CountNames(FishLine);
      }
      else if (menuOption==4)
      {
         DrawWinner(FishLine);
      }
      else if (menuOption==5)
      {
         DisplayLine(FishLine);
      }

      else if (menuOption==6)
      {
          Leave();
      }
      else
      {
          cout<<"Error: That is not a valid menu selection.\n";
          cout<<"Please enter a valid integer, 1-7.\n";
          
      }
    
    
    }
}

int number=1;
//Function adds name to queue
void AddName(MarketQueue &FishLine)
{
    string name="";
    cout<<"Please enter your name.\n";
    getline(cin,name);
    
    //First level input validation
    while(name.size()<1 || name.size()>19)
    {
        cout<<"Error: " << name<< " is not between 1 and 19 letters.\n";
        cout<<"Please enter a different name to add to the queue.\n\n";
        getline(cin, name);
    }
    
    //Call class method for adding to back of queue
    FishLine.enqueue(name, number);
    
    //Add one to raffle and display their number.
    cout<<"Welcome to the SP Fish Market - your raffle number is "<< number << endl;
    
    //If reached raffle #500, restart
    if (number<500)
        number++;
    else
        number=1;
}

//Function lets customer place order and dequeues them from the queue
void PlaceOrder(MarketQueue &FishLine)
{
    string catchString;
    FishLine.dequeue(catchString);
}

//Function returns the number of names in the queue
void CountNames(MarketQueue &FishLine)
{
   int numberInLine=FishLine.numNodes();
   cout << "There are " << numberInLine << " names in the queue.\n\n";
   if(numberInLine=0)
   {
       cout<<"Please add names to the line.\n\n";
   }
}

//Function draws the name of a raffle DrawWinner
void DrawWinner(MarketQueue &FishLine)
{
    //Draw winner randomly
    int winnerRaffle=FishLine.winner();
    cout<< winnerRaffle<< " is the winning raffle number.\n";
    
    
    //Locate lottery number in queue and store
    int winnerSpot=FishLine.searchQueue(winnerRaffle);
    
    //Evaluate the result of search method
    if (winnerSpot==-1)
    {
        cout<<"The person with the raffle number " << winnerRaffle <<" is no longer in line.\n";
    }
    else if (winnerSpot==1)
    {
        cout<<"This person is already at the front of the line. They will order soon.\n";
        cout<<"Please pick another winner.\n\n";
    }
    
    else 
    {
        int winnerIndex=winnerSpot-1;
        int winnerOption=0;
        string input;
        cout <<"CONGRATULATIONS!The person in position " << winnerSpot <<" in line is the RAFFLE WINNER!\n";
        cout <<"Please select your choice below.\n";
        cout <<"1.Move to the front of the line. \n";
        cout <<"2.Free T-shirt!\n";
        
        //Obtain raffle winner's choice
        getline(cin, input);
        winnerOption=stoi(input);
        
        while (!(winnerOption==1 || winnerOption==2))
        {
            cout<<"Please enter a valid selection of 1 or 2.\n";
            getline(cin,input);
            winnerOption=stoi(input);
        }
        
        if (winnerOption==1)
        {
            string catchString;
            cout<<"You have chosen to move to the front of the line.\n";
            catchString=FishLine.cutLine(winnerIndex);
            FishLine.moveToFront(catchString);
            cout<<"Congratulations "<<catchString<<"! You have been moved to the front of the line.\n";
            FishLine.dequeue(catchString);
            
        }
        
        else 
        {
            cout<<"Congratulations on choosing a free T-shirt! Enjoy!\n.";
            cout<<"You will not be moving to the front of the line.\n";
        }
        
    }
    
}
//Function displays the people in line and their info
void DisplayLine(MarketQueue &FishLine)
{
    if(FishLine.isEmpty())
    {
        cout<<"There are no names in line. Please enter names into the queue.\n";
    }
    else
    {
        cout<<"San Pedro Fish Market Line\n";
        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout<<"Number"<<setw(14)<<"Name"<<setw(10)<<"Raffle\n\n";
        FishLine.displayNodes();
    }
}

void Leave()
{
    cout<<"Thanks for visiting the San Pedro Fish Market! \n";
}