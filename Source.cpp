#include<iostream>
#include<vector>
#include<armadillo>
#include<fstream>
#include<string>
#include"node.h"
#include"element.h"
#include"voltage.h"
#include"current.h"
#include"Vdep.h"
#include"Cdep.h"
//#define pi
using namespace arma;
using namespace std;


////defining function to read the .txt  file
string* split(int size, string line)
{
	int j = 0;
	string* strptr = new string[5];

	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] == ' ')
		{
			j++;
			continue;
		}
		strptr[j] += line[i];
	}
	return strptr;
}



int main()
{

	int num_vs = 0;
	int num_cs = 0;
	int num_elem = 0;
	int num_dep = 0;

	double frequency = 0;
	cout << "Please Enter Frequency:";
	cin >> frequency;
	double omega = double(2 * frequency * 3.1415926);
	string name;
	cout << endl;
	cout << "Please enter netlist name(without .txt) :";
	cin >> name;
	cout << endl;
	name += ".txt";
	////////////////////////////////////////////////////////////////////////////////
	ifstream file(name);
	string in;
	vector<string> lines;
	if (file.is_open())
	{

		while (getline(file, in))
		{
			lines.push_back(in);
		}
	}
	file.close();
	////////////////////////////////////////////////////////////////////////////
	int max = 0;
	for (int k = 0; k < lines.size(); k++)
	{
		string* strptr = split(4, lines[k]);
		int i = stoi(strptr[1]);
		int j = stoi(strptr[2]);
		if (max < i)
			max = i;
		if (max < j)
			max = j;
	}

	///setting the array of node
	node* arrnode = new node[max + 1];
	for (int i = 0; i < max + 1; i++)
	{
		arrnode[i].setNumber(i);
	}
	////////////////////////////////////////////////////////////////////////////
	vector<voltage> arrbattery;
	vector<current>arrcurrent;
	vector<element> arrelement;
	vector<Vdep>arrVdep;
	vector<Cdep>arrCdep;
	////////////////////////////////////////////////////////////////////////////
	//Storing each element in its class
	for (int k = 0; k < lines.size(); k++)
	{
		switch (lines[k][0])
		{
		case'V':
		{
			string* strptr = split(5, lines[k]);
			//	cout << stof(strptr[3])<<endl;
			voltage theBattery(strptr[0], arrnode[stoi(strptr[1])], arrnode[stoi(strptr[2])], stof(strptr[3]), stof(strptr[4]));
			arrbattery.push_back(theBattery);
			num_vs++;
			break;
		}
		///////////////////////////////////////////////////////////////////////////
		case'L':
		{
			string* strptr = split(4, lines[k]);
			element the_element(strptr[0], arrnode[stoi(strptr[1])], arrnode[stoi(strptr[2])], stof(strptr[3]), omega);
			arrelement.push_back(the_element);
			num_elem++;
			break;
		}
		////////////////////////////////////////////////////////////////////////////
		//adding the Case of I *the ind. current source *
		case 'I':
		{
			string* strptr = split(4, lines[k]);
			//	cout << stof(strptr[3])<<endl;
			current CS(strptr[0], arrnode[stoi(strptr[1])], arrnode[stoi(strptr[2])], stof(strptr[3]), stof(strptr[4]));
			arrcurrent.push_back(CS);
			num_cs++;
			break;
		}
		////////////////////////////////////////////////////////////////////////////////
		case'C':
		{
			string* strptr = split(4, lines[k]);
			element the_element(strptr[0], arrnode[stoi(strptr[1])], arrnode[stoi(strptr[2])], stof(strptr[3]), omega);
			arrelement.push_back(the_element);
			num_elem++;

			break;
		}
		/////////////////////////////////////////////////////////////////////////////////
		case 'G': //(VCCS)
		{
			string* strptr = split(5, lines[k]);
			Cdep cdep(strptr[0], arrnode[stoi(strptr[1])], arrnode[stoi(strptr[2])], strptr[3], stof(strptr[4]), true);
			arrCdep.push_back(cdep);
			num_dep++;
			break;

		}
		/////////////////////////////////////////////////////////////////
		case 'F': ///(CCCS)
		{
			string* strptr = split(5, lines[k]);
			Cdep cdep(strptr[0], arrnode[stoi(strptr[1])], arrnode[stoi(strptr[2])], strptr[3], stof(strptr[4]), false);
			arrCdep.push_back(cdep);
			num_dep++;
			break;

		}
		/////////////////////////////////////////////////////////////////////////////////////
		case'E':///(VCVS)
		{
			string* strptr = split(5, lines[k]);
			Vdep vdep(strptr[0], arrnode[stoi(strptr[1])], arrnode[stoi(strptr[2])], strptr[3], stof(strptr[4]), true);
			arrVdep.push_back(vdep);
			num_dep++;
			break;
		}
		case'H'://(CCVS)
		{
			string* strptr = split(5, lines[k]);
			Vdep vdep(strptr[0], arrnode[stoi(strptr[1])], arrnode[stoi(strptr[2])], strptr[3], stof(strptr[4]), false);
			arrVdep.push_back(vdep);
			num_dep++;
			break;
		}
		/////////////////////////////////////////////////////////////////

		case'R':
		{
			string* strptr = split(4, lines[k]);
			element the_element(strptr[0], arrnode[stoi(strptr[1])], arrnode[stoi(strptr[2])], stof(strptr[3]), omega);
			arrelement.push_back(the_element);
			num_elem++;

			break;

		}

		}
	}
/////////////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < max + 1; i++)
	{
		for (int j = 0; j < arrelement.size(); j++)
		{
			if (arrelement[j].getnode1() == arrnode[i].getNumber())
			{
				arrnode[i].AddElement(arrelement[j]);
			}
			if (arrelement[j].getnode2() == arrnode[i].getNumber())
			{
				arrnode[i].AddElement(arrelement[j]);
			}
		}
		for (int j = 0; j < arrbattery.size(); j++)
		{
			if (arrbattery[j].getNode1() == arrnode[i].getNumber())
			{
				arrnode[i].AddBattery(arrbattery[j], 0);
			}
			if (arrbattery[j].getNode2() == arrnode[i].getNumber())
			{
				arrnode[i].AddBattery(arrbattery[j], 1);
			}
		}
	}
////////////////////////////////////////////////////////////////////////////////////////

	int num_nodes = max;
	/////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	


	arrnode[0].setNodeVolt(0);
	cx_fmat equations(max + arrbattery.size() + arrVdep.size(), max + arrbattery.size() + arrVdep.size(), fill::zeros);
	cx_fmat solver(max + arrbattery.size() + arrVdep.size(), 1, fill::zeros);

	cx_fmat sol = cx_fmat(max + arrbattery.size() + arrVdep.size(), 1);


	////////////////////////////////////////////////////////////////////////////////////


	//////filling matrix of G (equations)
	for (int i = 0; i < num_elem; i++)
	{
		if (arrelement[i].getnode1() != 0 && arrelement[i].getnode2() != 0)
		{
			equations(arrelement[i].getnode1() - 1, arrelement[i].getnode2() - 1) += -cx_float(1.0) / (arrelement[i].getZ());
			equations(arrelement[i].getnode2() - 1, arrelement[i].getnode1() - 1) += -cx_float(1.0) / (arrelement[i].getZ());

		}
		if (arrelement[i].getnode1() != 0)
			equations(arrelement[i].getnode1() - 1, arrelement[i].getnode1() - 1) += cx_float(1.0) / (arrelement[i].getZ());
		if (arrelement[i].getnode2() != 0)
			equations(arrelement[i].getnode2() - 1, arrelement[i].getnode2() - 1) += cx_float(1.0) / (arrelement[i].getZ());

	}
	///G matrix is filled with 1/R



	//Completing G matrix with supernode equations of ind.Src
	int counter_n = max;
	int counter_i = 0;
	while (counter_n < max + arrbattery.size() && counter_i < arrbattery.size())
	{
		if (arrbattery[counter_i].getNode1() == 0)
		{
			//equations(n, arrbattery[i].getNode1()) = cx_float(0, 0);
		}
		else
		{
			equations(counter_n, arrbattery[counter_i].getNode1() - 1) = cx_float(1, 0);
		}
		if (arrbattery[counter_i].getNode2() == 0)
		{
			//equations(n, arrbattery[i].getNode2()) = cx_float(0, 0);
		}
		else
		{
			equations(counter_n, arrbattery[counter_i].getNode2() - 1) = cx_float(-1, 0);
		}
		counter_i++;
		counter_n++;
	}

	int counter_n2 = max + arrbattery.size();
	int counter_j = 0;


	//Completing G matrix with supernode equations of Dep v.Src

	while (counter_n2 < max + arrbattery.size() + arrVdep.size() && counter_j < arrVdep.size())
	{

		if (arrVdep[counter_j].getNode1() == 0)
		{
		}
		else
		{
			equations(counter_n2, arrVdep[counter_j].getNode1() - 1) += cx_float(1, 0);
		}
		if (arrVdep[counter_j].getNode2() == 0)
		{
		}
		else
		{
			equations(counter_n2, arrVdep[counter_j].getNode2() - 1) += cx_float(-1, 0);
		}


		if (arrVdep[counter_j].Vc == true)
		{
			for (int j = 0; j < arrelement.size(); j++)
			{
				if (arrVdep[counter_j].elemDep == arrelement[j].name)
				{
					if (arrelement[j].getnode1() != 0)
						equations(counter_n2, (arrelement[j].getnode1()) - 1) += cx_float(-(arrVdep[counter_j].factor), 0);
					if (arrelement[j].getnode2() != 0)
						equations(counter_n2, (arrelement[j].getnode2()) - 1) += cx_float((arrVdep[counter_j].factor), 0);
				}
			}
		}
		else if (arrVdep[counter_j].Vc == false)
		{
			for (int j = 0; j < arrelement.size(); j++)
			{
				if (arrVdep[counter_j].elemDep == arrelement[j].name)
				{
					if (arrelement[j].getnode1() != 0)
						equations(counter_n2, (arrelement[j].getnode1()) - 1) += cx_float(-(arrVdep[counter_j].factor), 0) * (cx_float(1, 0) / (arrelement[j].getZ()));
					if (arrelement[j].getnode2() != 0)
						equations(counter_n2, (arrelement[j].getnode2()) - 1) += cx_float((arrVdep[counter_j].factor), 0) * (cx_float(1, 0) / (arrelement[j].getZ()));
				}
			}

		}




		counter_j++;
		counter_n2++;


	}
	//Completing G matrix with supernode equations of Dep C.Src

	for (int counter_n3 = 1; counter_n3 <= max; counter_n3++)
	{


		for (int counter_d = 0; counter_d < arrCdep.size(); counter_d++)
		{
			if (arrCdep[counter_d].getNode2() == counter_n3)
			{
				{if (arrCdep[counter_d].Vc == true)
					for (int i = 0; i < arrelement.size(); i++)
					{
						if (arrCdep[counter_d].elemDep == arrelement[i].name)
						{
							equations(counter_n3 - 1, (arrelement[i].getnode1()) - 1) -= cx_float(arrCdep[counter_d].factor, 0);
							equations(counter_n3 - 1, (arrelement[i].getnode2()) - 1) += cx_float(arrCdep[counter_d].factor, 0);

						}

					}
				else if (arrCdep[counter_d].Vc == false)
					for (int i = 0; i < arrelement.size(); i++)
					{
						if (arrCdep[counter_d].elemDep == arrelement[i].name)
						{
							equations(counter_n3 - 1, (arrelement[i].getnode1()) - 1) -= (cx_float(arrCdep[counter_d].factor, 0) / (arrelement[i].getZ()));
							equations(counter_n3 - 1, (arrelement[i].getnode2()) - 1) += (cx_float(arrCdep[counter_d].factor, 0) / (arrelement[i].getZ()));

						}

					}
				}
			}
			else if (arrCdep[counter_d].getNode1() == counter_n3)
			{
				if (arrCdep[counter_d].Vc == true)
					for (int i = 0; i < arrelement.size(); i++)
					{
						if (arrCdep[counter_d].elemDep == arrelement[i].name)
						{
							equations(counter_n3 - 1, (arrelement[i].getnode1()) - 1) += cx_float(arrCdep[counter_d].factor, 0);
							equations(counter_n3 - 1, (arrelement[i].getnode2()) - 1) -= cx_float(arrCdep[counter_d].factor, 0);

						}

					}
				else if (arrCdep[counter_d].Vc == false)
					for (int i = 0; i < arrelement.size(); i++)
					{
						if (arrCdep[counter_d].elemDep == arrelement[i].name)
						{
							if (arrelement[i].getnode1() != 0)
								equations(counter_n3 - 1, (arrelement[i].getnode1()) - 1) += (cx_float(arrCdep[counter_d].factor, 0) / (arrelement[i].getZ()));
							if (arrelement[i].getnode2() != 0)
								equations(counter_n3 - 1, (arrelement[i].getnode2()) - 1) -= (cx_float(arrCdep[counter_d].factor, 0) / (arrelement[i].getZ()));

						}

					}
			}



		}

	}
	//G matrix is DONE 



	/////Filling matrix of I (solver) with Current sources
	for (int n = 1; n <= num_nodes; n++)
	{
		for (int i = 0; i < num_cs; i++)
		{
			if (arrcurrent[i].getNode1() == n)
				solver(n - 1) -= arrcurrent[i].getcurrent();
			else if (arrcurrent[i].getNode2() == n)
				solver(n - 1) += arrcurrent[i].getcurrent();
		}

	}
	//Filling matrix "solver" with Batteries
	int n = num_nodes + 1;
	int i = 0;
	while (n <= max + arrbattery.size() && i < arrbattery.size())
	{
		solver(n - 1) = arrbattery[i].getVolt();
		n++;
		i++;
	}

	//Filling matrix "solver" with (depVS) Batteries
	for (int n = max + arrbattery.size() + 1; n <= max + arrbattery.size() + arrVdep.size(); n++)
	{

		solver(n - 1) = 0;


	}
	//Add the current of the batteris as unknowns in the matrix 
	//It is like the supernode method but done implicitly
	
	for (int n = max; n < max + arrbattery.size(); n++)
		for (int i = 0; i < max; i++)
			equations(i, n) += equations(n, i);
	//////////////////////////////////////////////////////////////

	for (int i = 0,  n = max + arrbattery.size(); i < (arrVdep.size()), (n < max + arrbattery.size() + arrVdep.size()); i++, n++)
	{
		if (arrVdep[i].getNode1() != 0)
			equations(arrVdep[i].getNode1() - 1, n) = cx_float(1, 0);
		if (arrVdep[i].getNode2() != 0)
			equations(arrVdep[i].getNode2() - 1, n) = cx_float(-1, 0);

	}
	//////////////////////////////////////////////////////////////


	cout << "G\n";
	cout << equations;
	cout << "I\n";
	cout << solver;
	sol=solve(equations,solver);
	cout << "Answer\n";
	cout << sol;
	////////////////////////////////////////////////////
	//SETTING NODE VOLTAGES
	ofstream solution("solution.txt");
	for (int i = 0; i < max; i++)
	{
		arrnode[i + 1].node_volt = sol(i, 0);
	}
	cout << "VOLT OF EACH NODE\n";
	for (int i = 0; i < max + 1; i++) //TESTING NODE VOLTAGES
	{
		cout << arrnode[i].node_volt << endl;
		solution << "volt node  " << i << "= " << arrnode[i].node_volt << endl;
	}
	solution << endl;
	cout << endl;
	//SETTING CURRENT OF EACH INDEP BATTERY  
	int counterbatteryfornextloop = 0; ///kol da name of var. :""" ... 7ad ysaketniii :/
	for (int i = max; i < max + arrbattery.size(); i++)
	{
		arrbattery[counterbatteryfornextloop].batteryCurrent= sol(i, 0);
		counterbatteryfornextloop++;
	}
	///Setting current for each dep battery 
	int counterdep = 0; 
	for (int i = max+arrbattery.size(); i < max + arrbattery.size()+arrVdep.size(); i++)
	{
		arrVdep[counterdep].currentdep = sol(i, 0);
		counterdep++;
	}
	cout << "Current through each BATTERY\n";
	/////setting voltage for each dep battery
	for (int vDep = 0; vDep < arrVdep.size(); vDep++)
		for (int i = 0; i < arrelement.size(); i++)
		{
			if (arrVdep[vDep].elemDep == arrelement[i].name)
				if (arrVdep[vDep].Vc == true)
					arrVdep[vDep].volt =cx_float((arrVdep[vDep].factor),0) * ((arrelement[i].node1->node_volt) - (arrelement[i].node2->node_volt));
				else if (arrVdep[vDep].Vc == false)
					arrVdep[vDep].volt = cx_float((arrVdep[vDep].factor),0) *( ((arrelement[i].node1->node_volt) - (arrelement[i].node2->node_volt))/arrelement[i].z);
		}
	//////////////////////////////////////////////////////////////////////////
	////////setting current for each dep.Current Src
	for (int cDep = 0; cDep < arrCdep.size(); cDep++)
		for (int i = 0; i < arrelement.size(); i++)
		{
			if (arrCdep[cDep].elemDep == arrelement[i].name)
				if (arrCdep[cDep].Vc == true)
					arrCdep[cDep].I = cx_float(arrCdep[cDep].factor,0) * ((arrelement[i].node1->node_volt) - (arrelement[i].node2->node_volt));
				else if (arrCdep[cDep].Vc == false)
					arrCdep[cDep].I = cx_float(arrCdep[cDep].factor,0) * (((arrelement[i].node1->node_volt) - (arrelement[i].node2->node_volt)) / arrelement[i].z);
		}
	////////////////////////////////////////////////////////////////////////
	///////displaying the power of each part
	////first power of ind batteries
	
	cout << "Results" << endl;
	solution << "Results\n";
	cout << "power of ind Batteries " << endl << endl;
	solution << "power of ind Batteries " << endl << endl;
	for (int i = 0; i < arrbattery.size(); i++)
	{
		arrbattery[i].print_power();
		cout << endl;
		solution << arrbattery[i].getPower()<<endl;
	}
	cout << endl;
	solution << endl;

	////power of current sources (ind)
	cout << "power of current sources (ind)" << endl << endl;
	solution << "power of current sources (ind)" << endl << endl;

	for (int i = 0; i < arrcurrent.size(); i++)

	{
		arrcurrent[i].print_power();
		cout << endl;
		solution << arrcurrent[i].getPower() << endl;
	}
	cout << endl;
	solution << endl;

	////power of elements 
	cout << "power of elements " << endl << endl;
	solution << "power of elements " << endl << endl;

	for (int i = 0; i < arrelement.size(); i++)
	{
		arrelement[i].print_power();
		cout << endl;
		solution << arrelement[i].getPower()<<endl;
	}
	cout << endl;
	solution << endl;
	///power of dep VS 
	cout << "power of dep VS" << endl << endl;
	solution << "power of dep VS" << endl << endl;
	for (int i = 0; i < arrVdep.size(); i++)
	{
		arrVdep[i].print_power();
		cout << endl;
		solution << arrVdep[i].getPower() << endl;

	}
	cout << endl;
	solution << endl;
	///power of dep CS
	cout << "power of dep CS" << endl << endl;
	solution << "power of dep CS" << endl << endl;
	for (int i = 0; i < arrCdep.size(); i++)
	{
		arrCdep[i].print_power();
		cout << endl;
		solution << arrCdep[i].getPower() << endl;
	}
	cout << "DONE!";
	solution << "DONE!";
	solution.close();
	int hhhh;
	cin >> hhhh;
	return 0;
}


///Appendix
///Not working blocks of code 

	//for (int i = 1; i < max + 1; i++)
	//{
	//	for (int j = 0; j < arrnode[i].node_elements.size(); j++)
	//	{
	//		if (arrnode[i].node_elements[j].getnode1() == i|| arrnode[i].node_elements[j].getnode2() == i)
	//		{
	//			equations(i-1, i-1) += pow(arrnode[i].node_elements[j].z,-1); // hna l mafrood yb2a += m4 = bs a3taqed
	//		}
	//		else 
	//		{
	//			equations(i-1, i-1) += pow(-arrnode[i].node_elements[j].z, -1); //Same hna
	//		}
	//			//arrnode[i].node_elements[j].getnode1();
	//	}
	//}
	/*cout << sol;*/
	/*cout << equations;
	cout << solver;*/






	/*mat A;
		A << 1 << 3<< endr
			<< 5 << 8<< endr;
		mat B;
		B << 8 << endr
			<< 5 << endr;
		mat C = solve(A, B);
	


	cout << C;*/
	//solution << cx_float(4, 5) << " DONIA\n";  //TESTNG CREATING A TXT

	//for (int i = 0; i < max; i++)
	//{
	//	for (int j = 0; j < arrbattery.size(); j++)
	//	{
	//		if (arrbattery[j].getNode1() == i + 1)
	//		{
	//			equations(i, max + j) = cx_float(1, 0);
	//		}
	//		if (arrbattery[j].getNode2() == i + 1)
	//		{
	//			equations(i, max + j) = cx_float(-1, 0);
	//		}
	//	}

	//}


	/*for (int i = 0; i < arrbattery.size(); i++) //TESTING  CURRENT OF BATTERIES
	{
		cout << arrbattery[i].batteryCurrent;
	}*/