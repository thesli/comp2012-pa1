#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <math.h>

#include "busRoute.h"

using namespace std;

/* To check if the route is empty.
   If the linked list, route, is empty, returns true, otherwise, returns false. */
bool isEmpty(busRoute route)
{
  return ((route.start)?false:true);
}

/* Given a bus stop name, find the next stop's name */ 
string getNextStopName(busRoute route, string stopName)
{
  string name = "";
  if (!isEmpty(route))
  {
    stop_pointer found = searchlist(route, stopName);
    if ((found!=NULL) && (found->next != NULL))
    {
       name = found->next->stop_name;
    }
  }
  return (name);
}

/* Given a bus stop name, find the previous stop's name */ 
string getPrevStopName(busRoute route, string stopName)
{
  string name = "";
  if (!isEmpty(route))
  {
    stop_pointer found = searchlist(route, stopName);
    if ((found!=NULL) && (found->prev != NULL))
    {
       name = found->prev->stop_name;
    }
  }
 
  return (name);
}

/* To print the information of a bus stop with the given stop_pointer */
void printStop(stop_pointer stop, ostream& os)
{
  if (stop != NULL)
    os << stop->stop_name << ", " << stop->longitude << ", " << stop->latitude << endl;
}

/* To print all the information of the bus route */
void printRoute(busRoute route, ostream& os) 
{
  stop_pointer temp;
  temp = route.start;
  os << "The list of bus stops for Route No. " << route.routeNo << ":" << endl;
  int stopNum = 1;
  while (temp != NULL) {
    os << "Stop " << stopNum << ":";
    printStop(temp, os);
    temp = temp->next;
    stopNum++;
  } 
}

/* To construct the linked list from the bus route information in the file */
busRoute readlist(const char* filename) 
{
  // fill your code here 

}

/* Erase the route object and deallocate all the nodes in the linked list */
void eraseRoute(busRoute& route)
{
  // fill your code here

}

/* To search and return the pointer to the node of the linked list,
   stop_node,with the given name, stopName, in the route object */
stop_pointer searchlist(busRoute route, string stopName)
{
  // fill your code here

}

/* To search if a bus stop with the given name existed in the route.
   If found, returns true, otherwise, returns false. */
bool searchStop(busRoute route, string stopName)
{
  // fill your code here

}

/* To remove a bus stop with the given name from the route */
void removeStop(busRoute& route, string stopName)
{
  // fill your code here
 
}

/* To find the displacement, i.e. the difference between the first and the last bus stops */
float directDistance(busRoute route)
{
  // fill your code here

}

/* To find the sum of displacements, i.e. differences,  between every two consecutive bus stops on the bus route */
float pathLength(busRoute route)
{
  // fill your code here

}

/* To reverse the doubly linked list of the route object */
void reverseRoute(busRoute& route)
{
  stop_pointer temp=route.start;
  if (temp->next != NULL)
  {
    while (temp->next != NULL)
    {
      temp = temp->next; 
    }
  
    reverseList(route, route.start->stop_name, temp->stop_name);
  }
}

/* To reverse the nodes between stopA to stopB in the doubly linked list of the route object */
void reverseList(busRoute& route, string stopA, string stopB)
{
  // fill your code here

}


/* To insert a bus stop in between two closest consecutive bus stops */
void insertStop(busRoute& route, string stopname, float longitude, float latitude)
{
  // fill your code here
}

// End of file
