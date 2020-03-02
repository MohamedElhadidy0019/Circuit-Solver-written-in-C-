#include "voltage.h"

voltage::voltage(string n, node&n1, node&n2, double real, double phasor)
{
	name = n;
	node1 = &n1;
	node2 = &n2;
	volt = polar(real, phasor * float(pi / 180));

}

cx_float voltage::getVolt()
{
	return volt;
}
int voltage::getNode1()
{
	return (node1->getNumber());
}
int voltage::getNode2()
{
	return (node2->getNumber());
}
void voltage::setVolt(cx_float x)
{
	volt = x;
}
cx_float voltage::getPower()
{
	cx_float x = cx_float(-0.5, 0) * (volt) * conj(batteryCurrent);
	return x;
}
void voltage::print()
{
	cout << "Voltage=" << volt << endl;
	cout << "////////////////\n";
}


void voltage::print_power()
{
	cout << "Power( " << name << " ) =  " << getPower();
}


/*node * voltage :: getnode1()
{
	return node1; 
}
node* voltage::getnode2()
{
	return node2;
}*/