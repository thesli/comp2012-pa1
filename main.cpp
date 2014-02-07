#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <math.h>

#include "busRoute.h"

using namespace std;

int main(int argc, char* argv[])
{
   streambuf* buf;
   ofstream of;
   if (argc > 1) {
     of.open(argv[1]);
     buf = of.rdbuf();
   } else {
     buf = std::cout.rdbuf();
   }
   ostream out(buf);

   busRoute route1;

   out << "...Reading the input file ..." << endl;
   route1=readlist("input1.txt");

   out << "...Info of the route:" << endl;
   printRoute(route1, out);
   out << endl;

   out << "...The direct distance of the route is " << directDistance(route1) << endl;
   out << "...The path length of the route is " << pathLength(route1) << endl;
   out << endl;

   string currentStop = "UST North";
   out << "...Searching for the stop \"" << currentStop << "\"... " << endl;
   if (searchStop(route1, currentStop)) {
      out << "...The stop is found.\n";
      out << "...The next stop is: " << getNextStopName(route1, currentStop) << endl;
      out << "...The prev stop is: " << getPrevStopName(route1, currentStop) << endl;
   } else 
      out << "...The stop is not found." << endl;
   out << endl;

   out << "...Inserting the stop \"UST South\":"<<endl;
   insertStop(route1, "UST South", 22.3374534, 114.262941);

   out << "...Info of the updated route:" << endl;
   printRoute(route1, out);
   out << endl;

   out << "...Removing the stop \"UST South\":"<<endl;
   removeStop(route1, "UST South");

   out << "...Info of the updated route:" << endl;
   printRoute(route1, out);
   out << endl;

   out << "...Reversing the route:" << endl;
   reverseRoute(route1);
   printRoute(route1, out);
   out << endl;

   string stopA = "Diamond Hill MTR Station", stopB="Choi Hung MTR Station";
   out << "...Reversing the stops between " << stopA << " to " << stopB << ":" << endl;
   reverseList(route1, stopA, stopB);
   printRoute(route1, out);
   out << endl;

   eraseRoute(route1);

   of.close();

   return(0);
}
