#pragma once
#include <iostream>
#include<armadillo>
#include "node.h"
using namespace arma;
using namespace std;
class node;

class element
{
protected:
public:
	cx_float z;
	string name;
	node* node1;
	node* node2;
	

	element(string, node&, node&, double,double);
	void setnode1(node &);
	void setnode2(node&);
	void setName(string);

	int getnode1();
	int getnode2();
	cx_float getZ();
	cx_float getPower();
	void print();
	void print_power();

};

