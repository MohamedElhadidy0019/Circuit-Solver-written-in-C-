# Circuit-Solver-written-in-C++
this code takes a netlist and get the voltages at all nodes and gets the power dissipated at all elements (Kinda like SPICE simulator)
Notes on writing the netlist file:
	For any source or element, it must begin with capital letter.  i.e: R1,I1,Vs,V2,…..
	For dependent sources : 
	E is the symbol for (VCVS)
	H is for (CCVS)
	F is for (CCCS)
	G is for (VCCS)
	You must enter the symbol of the element that the source depends on then the factor of dependency ,i.e : E1 1 2 R1 4
	If the source is  dependent on R1 for example , and from node 1 to node 2 so when u write it in the netlist file you must write the nodes in the appropriate order i.e : R1 1 2 value 
	You must enter the frequency (not in the netlist file but in the .exe “u will be asked to enter it “).
	If the phasor of the ind. source is equal to zero you must enter it too . i.e : V1 1 2 20 0.
	Please , don’t add extra spaces or extra blank lines in the netlist so not to get runtime errors.
	You must enter the name of the netlist file without the .txt extension .
	Netlist file must be in the same folder as the .exe file 



	you should write the netlist  in the same way that is written in (“example.txt”)file attached with the project ”there are other netlist files too  but this one is the netlist of the project document”.
	The output will be displayed in both the .exe file and a .txt file called (solution.txt)
