#include "node.h"

int node::getNumber()
{
	return node_number;
}

void node::setNumber(int n)
{
	node_number = n;
}

void node::setNodeVolt(cx_float x)
{
	node_volt = x;
}

void node::AddElement(element a)
{
	node_elements.push_back(a);
}

void node::AddBattery(voltage a,bool flag)
{
	if (flag == 0)
	{
		node_batteries.push_back(a);
		return;
	}
	if (flag == 1)
	{
		a.setVolt( a.getVolt());
		node_batteries.push_back(a);
	}
	
}

void node::printElement()
{
	for (int i = 0; i < node_elements.size(); i++)
	{
		cout << "node number=" << node_number << endl;
		node_elements[i].print();
	}
}

void node::printBatteries()
{
	if (!node_batteries.size())
	{
		cout << "NO BATTERIES" << endl;
		cout << "//////////////\n";
		return;
	}
	for (int i = 0; i < node_batteries.size(); i++)
	{
		node_batteries[i].print();
	}
}
