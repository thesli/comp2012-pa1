#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <string.h>
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
  busRoute* bRPtr = new busRoute;
  busRoute bR;  
  ifstream infile;
  string routeLine,routeNo;  
  infile.open(filename);  
  getline(infile,routeNo);    
  bRPtr->routeNo = atoi(routeNo.c_str());
  bRPtr->start = new stop_node;
  bool isFirst = true;
  stop_pointer prevPtr;
  while(getline(infile,routeLine)){            
    stop_pointer ptr = new stop_node;
    istringstream iss(routeLine);
    string data;
    int no = 0;
    while(getline(iss,data,',')){
      switch(no){
        case 0:
          ptr->stop_name = data;
          break;
        case 1:
          ptr->longitude = atof(data.c_str());
          break;
        case 2:
          ptr->latitude = atof(data.c_str());
          break;
      }
      no++;
    }
    if(isFirst){
      bRPtr->start = ptr;
      ptr->prev = NULL;
      isFirst = false;      
      prevPtr = ptr;
      ptr->next = NULL;
    }else{      
      prevPtr->next = ptr;   
      ptr->prev = prevPtr;
      prevPtr = ptr;
      ptr->next=NULL;     
    }
  }
  infile.close();
  return *bRPtr;
}

/* Erase the route object and deallocate all the nodes in the linked list */
void eraseRoute(busRoute& route)
{  
  busRoute* routePtr = &route;
  if(routePtr==NULL){    
    return;
  }    
  stop_pointer ptr = routePtr->start;
  stop_pointer tempPtr;  
  delete ptr->prev;
  while(true){        
    tempPtr = ptr;
    if(ptr->next!=NULL){
      ptr = ptr->next;
      delete tempPtr;
    }else{
      delete tempPtr;
      break;
    }
  }  
  // delete &route;  
}

/* To search and return the pointer to the node of the linked list,
   stop_node,with the given name, stopName, in the route object */
stop_pointer searchlist(busRoute route, string stopName)
{  
  stop_pointer ptr = route.start;
  if(ptr==NULL){
    return NULL;
  }
  if(ptr->stop_name.compare(stopName)==0){        
    return ptr;
  }
  while(ptr->next!=NULL){
    ptr = ptr->next;
    if(ptr->stop_name.compare(stopName)==0){      
      return ptr;
    } 
  }
  return NULL;
}

/* To search if a bus stop with the given name existed in the route.
   If found, returns true, otherwise, returns false. */
bool searchStop(busRoute route, string stopName)
{
  stop_pointer ptr = route.start;
  if(ptr==NULL){
    return false;
  }
  while(true){
    if(ptr->stop_name.compare(stopName)==0){
      return true;
    }
    if(ptr->next!=NULL){
      ptr = ptr->next;      
    }else{
      break;
    }
  }
  return false;
}

/* To remove a bus stop with the given name from the route */
void removeStop(busRoute& route, string stopName)
{
  // fill your code here
  busRoute* routePtr = &route;  
  if(searchStop(route,stopName)){
    stop_pointer toDelPtr = searchlist(route,stopName);    
    if(toDelPtr->prev!=NULL){
      if(toDelPtr->next!=NULL){
        toDelPtr->next->prev = toDelPtr->prev;
        toDelPtr->prev->next = toDelPtr->next;
        delete toDelPtr;
      }else{
        toDelPtr->prev->next = NULL;
        delete toDelPtr;
      }      
    }else{
      routePtr->start = toDelPtr->next;
      toDelPtr->next->prev = routePtr->start;
      delete toDelPtr;
    }    
  }

}

/* To find the displacement, i.e. the difference between th e first and the last bus stops */
float directDistance(busRoute route)
{
  if(route.start==NULL || route.start->next==NULL){
    return 0;
  }
  stop_pointer firstPtr = route.start;
  stop_pointer lastPtr = route.start;    
  while(true){
    if(lastPtr->next!=NULL){      
      lastPtr = lastPtr->next;
    }else{
      break;
    }
  }  
  return 
    pow(
      pow(firstPtr->latitude - lastPtr->latitude , 2)+
      pow(firstPtr->longitude - lastPtr->longitude , 2)
    ,0.5);
}

/* To find the sum of displacements, i.e. differences,  between every two consecutive bus stops on the bus route */
float pathLength(busRoute route)
{
  float sum = 0;
  if(route.start==NULL||route.start->next==NULL){
    return sum;
  }
  stop_pointer ptr = route.start;
  while(true){
    if(ptr->next!=NULL){
      float diff = 
        pow(
          pow(ptr->latitude - ptr->next->latitude , 2)+
          pow(ptr->longitude - ptr->next->longitude , 2)
        ,0.5);      
      sum += diff;
      ptr = ptr->next;
    }else{
      break;
    }
  }  
  return sum;
}

/* To reverse the doubly linked list of the route object */
void reverseRoute(busRoute& route)
{
  // stop_pointer temp=route.start;
  // if (temp->next != NULL)
  // {
  //   while (temp->next != NULL)
  //   {
  //     temp = temp->next; 
  //   }  
  //   reverseList(route, route.start->stop_name, temp->stop_name);    
  // }  
  stop_pointer endPtr = route.start;  
  stop_pointer tPtr;  
  while(true){
    if(endPtr->next==NULL){      
      break;
    }
    endPtr = endPtr->next;
  }
  route.start = endPtr;
  tPtr = endPtr;
  cout << endPtr->stop_name << endl;
  cout << endPtr->prev->stop_name << endl;
  cout << endPtr->prev->prev->stop_name << endl;
  // while(tPtr->prev!=NULL){
  //   tPtr->next = tPtr->prev;
  //   tPtr = tPtr->next;
  // }
  route.start = endPtr;
}

/* To reverse the nodes between stopA to stopB in the doubly linked list of the route object */
void reverseList(busRoute& route, string stopA, string stopB)
{
  // fill your code here
  if(!(searchStop(route,stopA)&&searchStop(route,stopB))){
    return;
  }

  stop_pointer stopAptr = searchlist(route,stopA);
  stop_pointer stopBptr = searchlist(route,stopB);      

  stop_pointer aNext = stopAptr->next;
  stop_pointer aPrev = stopAptr->prev;
  stop_pointer bNext = stopBptr->next;
  stop_pointer bPrev = stopBptr->prev;

  if(stopAptr->next == stopBptr){    
    // case when A is first    
    if(aPrev!=NULL){
      aPrev->next = stopBptr;
      stopBptr->prev = aPrev;
      stopBptr->next = stopAptr;
      stopAptr->prev = stopBptr;
      stopAptr->next = bNext;
    }else{
      route.start = stopBptr;
      stopBptr->prev = NULL;
      stopBptr->next = stopAptr;
      stopAptr->prev = stopBptr;
      stopAptr->next = bNext;
    }    
  }else if(stopBptr->next == stopAptr){
    // case when A is second
    reverseList(route,stopB,stopA);
  }
}


/* To insert a bus stop in between two closest consecutive bus stops */
void insertStop(busRoute& route, string stopname, float longitude, float latitude)
{
  // fill your code here
  stop_pointer nPtr = new stop_node;
    nPtr->stop_name = stopname;
    nPtr->longitude = longitude;
    nPtr->latitude = latitude;
  if(route.start==NULL){    
    nPtr->prev = NULL;
    route.start = nPtr;
  }else if(route.start->next==NULL){    
    nPtr->next = NULL;
    route.start->next = nPtr;
  }else{
    stop_pointer tPtr = route.start;
    stop_pointer closestPtr;
    float min = 999999.0;
    while(true){
      if(tPtr->next == NULL){
        break;
      }
      float diff = 
          pow(
            pow(latitude - tPtr->latitude , 2)+
            pow(longitude - tPtr->longitude , 2)
          ,0.5) + 
          pow(
            pow(latitude - tPtr->next->latitude , 2)+
            pow(longitude - tPtr->next->longitude , 2)
          ,0.5);                
      if(min>=diff){
        closestPtr = tPtr;
        min = diff;
      }
      tPtr = tPtr->next;
    }
    stop_pointer cNext = closestPtr->next;
    cNext->prev = nPtr;
    nPtr->next = cNext;
    nPtr->prev = closestPtr;
    closestPtr->next = nPtr;
  }
}

// End of file
