#pragma once
#include<iostream>
#include<armadillo>
#include"node.h"
#include"element.h"
using namespace arma;
using namespace std;
class node;
class Vdep
{
public:
	node* node1;
	node* node2;
	cx_float volt;
	string name;
	string elemDep;
	double factor;
	bool Vc;
	cx_float currentdep;

	cx_float getPower();
	Vdep(string, node&, node&, string, double,bool vc);
	cx_float getVolt();
	int getNode1();
	int getNode2();
	void setVolt();
	void print_power();
};

