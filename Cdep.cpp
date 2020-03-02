#include "Cdep.h"
Cdep::Cdep(string n, node& n1, node& n2, string dep, double fact, bool vc)

{
	Vc = vc;
	elemDep = dep;
	factor = fact;
	name = n;
	node1 = &n1;
	node2 = &n2;
}
	int Cdep::getNode1()
	{
		return (node1->getNumber());
	}
	int Cdep::getNode2()
	{
		return (node2->getNumber());
	}

	cx_float Cdep::getPower()
	{
		return ( cx_float(0.5,0) * ((node2->node_volt) - (node1->node_volt)) * conj(I) );
	}
	void Cdep::print_power()
	{
		cout << "Power( " << name << " ) =  " << getPower();
	}
