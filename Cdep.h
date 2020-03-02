#pragma once
#include"node.h"
//constexpr double pi = 3.14159265359;
#include<iostream>
#include<armadillo>

using namespace arma;
using namespace std;
class node;

class Cdep
{
public:
	node* node1;
	node* node2;
	cx_float I;
	string name;
	string elemDep;
	double factor;
	bool Vc;
	Cdep(string, node&, node&, string, double,bool);

	cx_float getPower();

	int getNode1();
	int getNode2();
	void print_power();
};

