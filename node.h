#pragma once
#include<iostream>
#include <vector>
#include<armadillo>
#include"element.h"
#include"voltage.h"
using namespace std;
using namespace arma;

class element;
class voltage;

class node
{
public:
	int node_number;
	cx_float node_volt;
	vector<element>node_elements;
	vector<voltage>node_batteries;


	int getNumber();
	void setNumber(int);
	void setNodeVolt(cx_float);
	void AddElement(element);
	void AddBattery(voltage,bool);
	void printElement();
	void printBatteries();

};

