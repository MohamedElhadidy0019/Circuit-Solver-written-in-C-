#include "Vdep.h"
Vdep::Vdep(string n, node& n1, node& n2, string dep, double fact,bool vc)
	
{
	Vc = vc;
	elemDep = dep;
	factor = fact;
	name = n;
	node1 = &n1;
	node2 = &n2;
	


}
int Vdep::getNode1()
{
	return (node1->getNumber());
}
int Vdep::getNode2()
{
	return (node2->getNumber());
}
cx_float Vdep::getPower()
{
	cx_float power;
	power =cx_float(-0.5,0) * volt * conj(currentdep);
	return power;
}

void Vdep::print_power()
{
	cout << "Power( " << name << " ) =  " << getPower();
}

