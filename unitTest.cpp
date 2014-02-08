#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <cassert>
#include <stdio.h>

#include "busRoute.h"

using namespace std;

int main(int argc, char const *argv[])
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


	// test the function of searchStop
	assert(searchStop(route1,"South")==false);
	assert(searchStop(route1,"Diamond Hill MTR Station")==true);
	assert(searchStop(route1,"Choi Hung MTR Station")==true);
	assert(searchStop(route1,"UST North")==true);

	// test the function of searchlist 
	assert(searchlist(route1,"South")==NULL);
	assert(searchlist(route1,"Diamond Hill MTR Station")->stop_name.compare("Diamond Hill MTR Station")==0);
	assert(searchlist(route1,"Choi Hung MTR Station")->stop_name.compare("Choi Hung MTR Station")==0);
	assert(searchlist(route1,"UST North")->stop_name.compare("UST North")==0);

	//test the function of removeStop
	// check for first case
	removeStop(route1,"Diamond Hill MTR Station");	
	assert(route1.start->stop_name.compare("Diamond Hill MTR Station")!=0);
	assert(route1.start->stop_name.compare("Choi Hung MTR Station")==0);	
	// check for middle case
	route1 = readlist("input1.txt");
	removeStop(route1,"Choi Hung MTR Station");	
	assert(route1.start->stop_name.compare("Choi Hung MTR Station")!=0);
	assert(route1.start->stop_name.compare("Diamond Hill MTR Station")==0);
	assert(route1.start->next->stop_name.compare("UST North")==0);
	// check for last case
	route1 = readlist("input1.txt");
	removeStop(route1,"UST North");
	assert(route1.start->next->stop_name.compare("UST North")!=0);
	assert(route1.start->stop_name.compare("Diamond Hill MTR Station")==0);
	assert(route1.start->next->stop_name.compare("Choi Hung MTR Station")==0);


	return 0;
}