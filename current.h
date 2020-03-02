#pragma once
#include"node.h"
//constexpr double pi = 3.14159265359;
#include<iostream>
#include<armadillo>

using namespace arma;
using namespace std;
class node;

class current
{
private:
	node* node1;
	node* node2;
	cx_float I;
	string name;
public:
	current(string, node&, node&, double, double);
	cx_float getcurrent();
	int getNode1();
	int getNode2();
	void setcurrent(cx_float);
	void print();
	cx_float getPower();
	void print_power();


};

