#pragma once
#include"node.h"
constexpr auto pi = 3.14159265359;
#include<iostream>
#include<armadillo>
using namespace arma;
using namespace std;
class node;

class voltage
{
public:
	node* node1;
	node* node2;
	cx_float volt;
	string name;
	cx_float batteryCurrent;

	voltage(string,node&,node&,double,double);
	cx_float getVolt();
	int getNode1();
	int getNode2();
	void setVolt(cx_float);
	cx_float getPower();
	void print();
	void print_power();
/*	node* getnode1(); 
	node *getnode2();
	*/
};

