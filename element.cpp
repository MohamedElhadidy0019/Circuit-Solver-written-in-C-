#include "element.h"

element::element(string x, node&n1, node&n2, double number,double omega)
{
	name = x;
	node1 = &n1;
	node2 = &n2;
	if (name[0] == 'C'|| name[0] == 'c')
	{
		z = cx_float(0, -1 / (number * omega));
	}
	else if (name[0] == 'L'|| name[0] == 'l')
	{
		z = cx_float(0, number * omega);
	}
	else if(name[0]=='R'||name[0]=='r')
	{
		z = cx_float(number, 0);
	}

}

void element::setnode1(node &n1)
{
	node1 = &n1;
}

void element::setnode2(node& n2)
{
	node2 = &n2;
}

void element::setName(string a)
{
	name = a;
}

int element::getnode1()
{
	return (node1->getNumber());
}

int element::getnode2()
{
	return (node2->getNumber());
}

cx_float element::getZ()
{
	return z;
}

cx_float element::getPower()
{
	cx_float x;
	x =pow( abs( (node1->node_volt)-(node2->node_volt) ),2)/(cx_float(2.0,0.0)*conj(z));
	return x;
}

void element::print()
{
	cout << "name=" << name<<endl;
	cout << "z=" << z << endl;
	cout << "node1 is" << node1->getNumber() << endl;
	cout << "node2 is" << node2->getNumber() << endl;
	cout << "////////////////////////\n";
}


void element::print_power()
{
	cout << "Power( " << name << " ) =  " << getPower();
}
