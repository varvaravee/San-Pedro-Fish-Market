#include"MarketQueue.h"
#include<iostream>
#include<cstdlib>
#include<string>
#include <time.h>
#include <iomanip>
using namespace std;

//Constructor creates empty queue 
MarketQueue::MarketQueue()
{   
    front=nullptr;
    rear=nullptr;
    numItems=0;
}

//Destructor
MarketQueue::~MarketQueue()
{
    FishNode *nodePtr=nullptr, *nextNode=nullptr;
    nodePtr=front;
    
    while(nodePtr !=nullptr)
    {
        nextNode=nodePtr->next;
        delete nodePtr;
        nodePtr=nextNode;
    }
}

//Member method enqueue inserts value in string at the rear of the queue
void MarketQueue::enqueue(string a, int &rNumber)
{
    FishNode *newNode=nullptr;
    
    //Create new node and store a there
    newNode=new FishNode;
    newNode->value=a;
    newNode->next=nullptr;
    newNode->raffle=rNumber;
    
    //Adjust front and rear as necessary
    if (isEmpty())
    {
        front=newNode;
        rear=newNode;
    }
    else 
    {
        rear->next=newNode;
        rear=newNode;
    }
    
    //Update numItems
    numItems++;
}

//Member method dequeues the value at the front of the queue and copies it into b
void MarketQueue::dequeue(string &b)
{
    FishNode *temp=nullptr;
    
    if (isEmpty())
    {
        cout<<"The queue is empty. Please add a name to the queue from the main menu.\n";
    }
    else
    {
        //Save front node value in b
        b=front->value;
        
        //Remove front node and delete it
        temp=front;
        front=front->next;
        delete temp;
        
        //Update numItems
        numItems--;
        
        //Tell user they can order
        cout<<b << " you can order now!\n";
    }
}

//Member method isEmpty returns true if queue is empty, false otherwise
bool MarketQueue::isEmpty() const 
{
    bool status;
    if (numItems>0)
        status=false;
    else
        status=true;
        
    return status;
}

//Member method that counts the number of nodes in the queue
int MarketQueue::countNodes(FishNode *nodePtr) const
{
    if (nodePtr!=nullptr)
        return 1+ countNodes(nodePtr->next);
    else 
        return 0;
}

//Member that draws winner
int MarketQueue::winner()
{
    //Save front node raffle number in firstRaf 
    int firstRaf=0;
    firstRaf=front->raffle;
    int numRange1=countNodes(front)-1;
    int numRange2=firstRaf+numRange1;
    int winningRaffle=0;
    int rafflePosition=0;
   
    //Initialize random seed for random number generator and generate random number in the range of raffle numbers
    srand(time(0));
    winningRaffle=(rand() % numRange2) + firstRaf;
    
    return winningRaffle;
    
}

//Member method calls the method that searches the queue
int MarketQueue::searchQueue(int rafflenum)
{
    return searchQueue2(front, rafflenum);
}


//Member method locates the raffle winner in the queue
int index=1;
int MarketQueue::searchQueue2(FishNode* ptr, int raffleNum)
{   
    if (ptr==NULL)
    {
        cout<<"There are no people in line with this raffle number.\n\n";
        return -1;
    }
    else if (ptr->raffle==raffleNum)
    {
        return index;
    }
    else
    {
        index++;
        searchQueue2(ptr->next, raffleNum);
    }
}

//Member method places raffle winner in front of line 
string MarketQueue::cutLine(int linePosition)
{
    string catchString;
    FishNode *delThis;
    
    if (isEmpty())
       {
        cout<<"There is no person in line at this spot. \n\n";
       }
       
    else if (linePosition==0)
    {
        cout<<"This person is already at the front of the line. They will order soon.\n";
    }
    
    else
    {
        //Otherwise create temporary node and set it to the first node
        FishNode *tempNode;
        tempNode=front;
        int i=1;
        
        //While there is another node and the desired spot has not yet been reached
        //load the next node and increment the counter
        while((tempNode->next)&&(i<linePosition))
        {
             tempNode=tempNode->next;
             ++i;
        }
        
        //If desired spot not reached or there are no more nodes, deletion impossible
        if ((i<linePosition) || (!(tempNode->next)))
        {
            cout<<"There is no one at this number in line.\n";
        }
        
        else
        {
            delThis=tempNode->next;
            tempNode->next=delThis->next;
            catchString=delThis->value;
            delete delThis;
        }
    }
    return catchString;
}

void MarketQueue::moveToFront(string cutterpants)
{
    FishNode *newNode=nullptr;
    
    //Allocate new node and store value there
    newNode=new FishNode;
    newNode->value=cutterpants;
    
    if (isEmpty())
    {
        cout<<"There are no people in line. \n\n";
        front=newNode;
        newNode->next=nullptr;
    }
    
    else
    {
        newNode->next=front;
        front=newNode;
    }
}


//Member method displays the nodes
void MarketQueue::displayNodes()
{
    int index=0;
    if (isEmpty())
    {
        cout <<"There are no names to display.\n\n";
    }
    
    else 
    {
        FishNode *temp;
        temp=front;
        
        while (temp)
        {
            cout<< index+1 <<setw(19)<< temp->value <<setw(8)<<temp->raffle<<endl;
            temp=temp->next;
            index++;
        }
    }
}


