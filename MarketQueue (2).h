//Specification file for Story class
#ifndef MARKETQUEUE_H
#define MARKETQUEUE_H
#include <iostream>
#include <string>
using namespace std;


class MarketQueue 
{
  private:
    //Structure for the queue nodes
    struct FishNode
     {
        string value;
        int raffle;
        FishNode *next;
     };
  
    FishNode *front; //Front of queue
    FishNode *rear; //Rear of queue
    int numItems;
    
    int countNodes(FishNode *) const;
  
  public:
    //Constructor
    MarketQueue();
    
    //Destructor
    ~MarketQueue();
    
    //Queue operations
    void enqueue(string, int&);
    void dequeue(string &);
    bool isEmpty() const;
    int numNodes() const
        {return countNodes(front); }
    int winner();
    int searchQueue(int);
    int searchQueue2(FishNode *, int);
    string cutLine(int);
    void moveToFront(string);
    void displayNodes();
    
};

#endif