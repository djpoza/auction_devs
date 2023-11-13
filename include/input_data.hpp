#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

struct info_agents{
    std::vector<double> _Pr;
    std::vector<double> _InitialPr;
};

std::vector<std::vector<int>> read_matrix() 
{ 
	// File pointer 
	std::fstream fin; 
    // Open an existing file 
	fin.open("matrix.txt", std::ios::in); 
	// Read the Data from the file 
	// as String Vector 
	std::vector<std::vector<int>> matrix;
    std::vector<int> row; 
	std::string line, word; 

    int i=0;
    // read an entire row and 
    // store it in a string variable 'line' 
    while(getline(fin, line)){
        row.clear(); 
        // used for breaking words 
        std::stringstream s(line); 

        // read every column data of a row and store
        // it in a string variable, 'word' 
        while (getline(s, word, ';')) { 

            // add all the column data of a row to a vector
            int nmbr = std::stoi(word); //stoi convert string to integer
            row.push_back(nmbr); 
        } 
        matrix.push_back(row);

        i++;
    } 

	for(int j=0; j<matrix.size(); j++){
        for(int k=0; k<matrix[0].size(); k++){
            std::cout << matrix [j][k] << " ";
        }
        std::cout << std::endl;
    }	
	return matrix;
}

info_agents read_agents(std::string name_file) 
{ 
    info_agents local_agents;
	// File pointer 
	std::fstream fin; 
    
	// Open an existing file 
	fin.open(name_file, std::ios::in); 

	// Read the Data from the file 
	// as String Vector 
    std::vector<double> row, _Pr, _InitialPr; 
	std::string line, word; 

    // read an entire row and 
    // store it in a string variable 'line'
    int i = 0; 
    while(getline(fin, line)){
        row.clear(); 
        // used for breaking words 
        std::stringstream s(line); 

        // read every column data of a row and 
        // store it in a string variable, 'word' 
        while (getline(s, word, ';')) { 

            // add all the column data 
            // of a row to a vector
            double nmbr = std::stof(word); //stoi convert string to integer
            row.push_back(nmbr); 
        } 

        if (i==0){
            local_agents._Pr = row;
            for(int i=0; i<local_agents._Pr.size(); i++){
            std::cout << local_agents._Pr[i] << " ";
            }
            std::cout << std::endl;
        } else {
            local_agents._InitialPr = row;
            for(int i=0; i<local_agents._InitialPr.size(); i++){
            std::cout << local_agents._InitialPr[i] << " ";
            }
            std::cout << std::endl;
        }
        i++;
        
    } 	
	return local_agents;
} 
