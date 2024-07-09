#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;



struct data_auction{
    vector<double> _RPr;
    vector<double> _InitialPPr;
    int _PPrStep;
    vector<double> _PCost;
    vector<double> _InitialAPr;    
    int _APrStep;
    vector<vector<int>> _Matrix;
};

data_auction read_data(string name_file) 
{ 
    data_auction local_data;
	// File pointer 
	fstream fin; 
    
	// Open an existing file 
	fin.open(name_file, ios::in); 

	// Read the Data from the file 
	// as String Vector 
    vector<double> row, _RPr, _InitialPPr, _PCost, _InitialAPr; 
	string line, word;
    int pr_step;
    vector<vector<int>> _matrix;
    vector<int> row_m;

    // read an entire row and 
    // store it in a string variable 'line'
    int i = 0;
    int line_nmbr = 1; 
    while(getline(fin, line)){ //&& line_nmbr<13
        row.clear();
        row_m.clear();
        // used for breaking words 
        stringstream s(line);

        if (line_nmbr>13) {
            while (getline(s, word, ';')) { 

                // add all the column data of a row to a vector
                int nmbr = stoi(word); //stoi convert string to integer
                row_m.push_back(nmbr); 
            } 
            _matrix.push_back(row_m);
        }

        if (line_nmbr%2==0) {
            // read every column data of a row and 
            // store it in a string variable, 'word' 

            while (getline(s, word, ';')) { 

                // add all the column data 
                // of a row to a vector
                if (i == 2|| i == 5) {
                    int nmbr = stoi(word); //stoi convert string to integer
                    pr_step = nmbr;
                } else {
                    double nmbr = stof(word); //stoi convert string to integer
                    row.push_back(nmbr); 
                }
                
            } 

            if (i==0){
                local_data._RPr = row;
            } else if (i==1){
                local_data._InitialPPr = row;
            } else if (i==2) {
                local_data._PPrStep = pr_step;
            } else if (i==3) {
                local_data._PCost = row;
            } else if (i==4) {
                local_data._InitialAPr = row;
            } else if (i==5) {
                local_data._APrStep = pr_step;
            }
            i++;
        
        }
        line_nmbr ++;
        
    }
    local_data._Matrix = _matrix;

	return local_data;
} 