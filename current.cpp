#include "current.h"
//#include<iostream>
//using namespace std;
current::current(string n, node& n1, node& n2, double real, double phasor)
{
	name = n;
	node1 = &n1;
	node2 = &n2;
	I = polar(real, phasor * float(pi / 180));
}
cx_float current::getcurrent()
{
	return I;
}
int current::getNode1()
{
	return (node1->getNumber());
}
int current::getNode2()
{
	return (node2->getNumber());
}
void current::setcurrent(cx_float x)
{
	I = x;
}
void current::print()
{
	cout << "CurrentSource=" <<I << endl;
	cout << "////////////////\n";
}

cx_float current::getPower()
{
	cx_float x = cx_float(0.5, 0)*( node2->node_volt-node1->node_volt )*conj(I);
	return x;
}
void current::print_power()
{
	cout << "Power( " << name << " ) =  " << getPower();
}
