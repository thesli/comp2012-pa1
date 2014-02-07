#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <math.h>

using namespace std;

typedef struct stop_node* stop_pointer;

typedef struct stop_node {
  string stop_name;  // the name of the stop
  float longitude; // the longitude of the geographic coordinates of the stop
  float latitude; // the latitude of the geographic coordinates of the stop
  stop_pointer next; // the next pointer
  stop_pointer prev; // the prev pointer
};

typedef struct busRoute {
  int routeNo;  // the route number of the stop
  stop_pointer start;  // the head of the linked list
};

/* To check if the route is empty.
   If the linked list, route, is empty, returns true, otherwise, returns false. */
bool isEmpty(busRoute route);

/* Given a bus stop name, find the next stop's name */ 
string getNextStopName(busRoute route, string stopName);

/* Given a bus stop name, find the previous stop's name */ 
string getPrevStopName(busRoute route, string stopName);

/* To print the information of a bus stop with the given name */
void printStop(stop_pointer stop, ostream& os);

/* To print all the information of the bus route */
void printRoute(busRoute route, ostream& os);

/* To construct the linked list from the bus route information in the file */
busRoute readlist(const char* filename);

/* Erase the route object and deallocate all the nodes in the linked list */
void eraseRoute(busRoute& route);

/* To search and return the pointer to the node of the linked list, 
   stop_node,with the given name, stopName, in the route object */
stop_pointer searchlist(busRoute route, string stopName);

/* To search if a bus stop with the given name existed in the route.
   If found, returns true, otherwise, returns false. */
bool searchStop(busRoute route, string stopName);

/* To remove a bus stop with the given name from the route */
void removeStop(busRoute& route, string stopName);

/* To find the displacement, i.e. the difference between the first and the last bus stops */
float directDistance(busRoute route);

/* To find the sum of displacements, i.e. differences,  between every two consecutive bus stops on the bus route */
float pathLength(busRoute route);

/* To reverse the whole linked list in the route object */
void reverseRoute(busRoute& route);

/* To reverse the nodes between stopA to stopB in the doubly linked list of the route object */
void reverseList(busRoute& route, string stopA, string stopB);

/* To insert a bus stop in between two closest consecutive bus stops */
void insertStop(busRoute& route, string stopname, float longitude, float latitude);

