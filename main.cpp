#include <iostream>
#include <ctime>

#include "LinkedList.h"

using namespace std;

void verifyLinks(LinkedList < int >& list);
void randomNumbersInsert();
void randomNumbersRemove();
void randomNumbersInsertAndRemove();
void simpleList();

//some constants so that I can experiment with my tests
const int NUM_ITERATIONS = 100;
const int SCALE_FACTOR = 100;
const int INT_MIN = 0;

int main()
{
    cout<<"Ordered Linked List Driver"<<endl;
    
    //use different random numbers each time
    srand(time(0));
    
    //use the same random numbers from one run to another
    //srand(0);

    //test very basic stuff
    simpleList();
    
    //really try and break it with random inserts and removes
    for(int i = 0;i < 100;i++)
    {
        cout<<"iteration: "<<(i + 1)<<" "<<endl;
        randomNumbersInsert();
        randomNumbersRemove();
        randomNumbersInsertAndRemove();
    }
    
    cout<<"Done"<<endl;
    return 0;
}
//--
void simpleList()
{
    //elem to be returned by removeFromFront
    int val;

    //create a list
    LinkedList < int > list;
    
    //do some inserts
    list.insert(20); //20
    list.insert(10); //10 20
    list.insert(30); //10 20 30
    list.insert(25); //10 20 25 30
    list.insert(5);  //5 10 20 25 30
    list.insert(20); //5 10 20 20 25 30
    list.insert(20); //5 10 20 20 20 25 30
    list.insert(40); //5 10 20 20 20 25 30 40
    list.insert(15); //5 10 15 20 20 20 25 30 40
    list.insert(5);  //5 5 10 15 20 20 20 25 30 40
    list.insert(40); //5 5 10 15 20 20 20 25 30 40 40
    
    int x;
    //print out all the items in the list in order
    if (list.first(x))
      {
    	cout << x << endl;
    	while (list.next(x))
    	  {
    	    cout << x << endl;

    	    if (x == 30)
    	      {
    		//moving the current pointer inside find means that
    		//we might not get the items back in order
    		list.find(20);
    	      }
    	  }
      }

    //test the most efficient route to pos
    if(list.at(9) != 40 ||
       list.at(0) != 5  ||
       list.at(3) != 15 ||
       list.at(2) != 10 ||
       list.at(4) != 20)
    {
		cout << "Problems with at()" << endl;
		cout << "list.at(9): " << list.at(9) << " should be: " << 40 << endl;
		cout << "list.at(0): " << list.at(0) << " should be: " << 5 << endl;
		cout << "list.at(3): " << list.at(3) << " should be: " << 15 << endl;
		cout << "list.at(2): " << list.at(2) << " should be: " << 10 << endl;
		cout << "list.at(4): " << list.at(4) << " should be: " << 20 << endl;
    }
    
    
    try
    {
        list.at(100);
        cout<<"Problem with exception NOT being thrown"<<endl;
    }
    catch (...) //catch any type of exception here
    {
        //do nothing, this should happen
    }
    
    
    //verify
    verifyLinks(list);
    
    //remove some elements
    list.removeFromFront(val); //5 5 10 15 20 20 20 30 40 40
    list.removeFromFront(val);  //10 15 20 20 20 30 40 40
    list.removeFromFront(val); //10 15 30 40 40
    list.removeFromFront(val); //15 30 40 40
    list.removeFromFront(val); //15 30 40 40
    
    //verify
    verifyLinks(list);
    
    
    //remove some elements
    list.removeFromFront(val); //15 40 40
    list.removeFromFront(val); //15
    list.removeFromFront(val); //empty
    list.removeFromFront(val);//remove something that is not there
}
//--
void verifyLinks(LinkedList < int >& list)
{
    //make sure we read all of the elements, count them and compare to the length
    int count = 0;
    
    //loop through all the elements
    int data;
    
    if(list.first(data))
    {
        //count the read
        count++;
        
        while(list.next(data))
        {
            //count the read
            count++;
        }
    }
    
    //make sure there were the same number of reads as elements
    if(count != list.size())
    {
        cout<<"Forward direction problems"<<endl;
    }
    
    //check the count
    if(count != list.size())
    {
        cout<<"Backward direction problems"<<endl;
    }
}

//--
void randomNumbersInsert()
{
    //create a list
    LinkedList < int > list;
    
    //add random integers to it
    for(int i = 0;i < NUM_ITERATIONS;i++)
    {
        //choose a random integer and insert it
        list.insert(rand());
        
        //verify
        verifyLinks(list);
        
    }
}
//--
void randomNumbersRemove()
{
    //elem to be returned by removeFromFront
    int val;

    //create a list
    LinkedList < int > list;
    
    //add some random numbers
    for(int i = 0;i < NUM_ITERATIONS;i++)
    {
        //scale down to numbers between 0-(SCALE_FACTOR-1)
        list.insert(rand() % SCALE_FACTOR);
    }

    //see what is in this list
    //list.printAllFromHead();
    
    //while the list is not empty
    while(!list.isEmpty())
    {
      //attempt to remove a random number
      list.removeFromFront(val);
        
      //verify
      verifyLinks(list);
      
    }

    //see what is in the list now
    //list.printAllFromHead();
}
//--
void randomNumbersInsertAndRemove()
{
    //elem to be returned by removeFromFront
    int val;

    //create a list
    LinkedList < int > list;
    
    //mix inserts and removes
    for(int i = 0;i < NUM_ITERATIONS;i++)
    {
        //flip a coin- insert
        if(rand() % 2 == 0)
        {
	    //insert a random number
	  int rando = rand() % SCALE_FACTOR;
            list.insert(rando);
            
            //verify
            verifyLinks(list);
            
        }
        else//flip a coin- remove
        {
            //attempt to remove a random number
            list.removeFromFront(val);
            
            //verify
            verifyLinks(list);
            
        }
    }
    
    //int count = 0;

    //while the list is not empty
    while(!list.isEmpty())
    {
        //attempt to remove a random number
        list.removeFromFront(val);
        
        //verify
        verifyLinks(list);
        
	//count++;

	//cout << "iteration: " << count << endl;
    }
}
