/*****************************************
*  Programmer: Tyler Potochnik           *
*  The University Of Akron               *
*                                        *
*  Last Edited:                 *
*                                        *
*****************************************/
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include "seam.h"

using namespace std;

SeamCarving::SeamCarving(int vertical, int horizontal, string filename){
    ifstream infile;
    infile.open(filename.c_str());
    int rows, columns, size;
    int vert = vertical;
    int horz = horizontal;

  	string line;

    getline(infile, line);

    ofstream outfile(((filename.substr(0,filename.length()-4))
                      +"_processed.pgm" ).c_str());

    outfile << "P2" << std::endl;

    int pos = 0;

    do {
        getline(infile, line);
        pos+= line.length()+1;
        if(line[0] == '#')
            outfile << line << std::endl;

    } while (line[0] == '#');

    if(line[line.length()-2] != ' ')
        pos += 1;
 
    infile.seekg(pos-line.length());

    stringstream ss;
    ss << infile.rdbuf();

    ss >> columns >> rows >> size;
 
    int array[rows][columns];
  
    for (int i = 0; i < rows; i++){
    	for(int j = 0; j < columns; j++){
    		ss >> array[i][j];
    	}
    }

    outfile << columns << " " << rows << '\n';
    outfile << size << '\n';

    int en[rows][columns];
  
    for (int i = 0; i < rows; i++){
    	for(int j = 0; j < columns; j++){
    		int energy = 0;
    		if(i != 0){
    			energy += abs(array[i][j] - array[i-1][j]);
    		}
    		if(rows-1 != i){
    			energy += abs(array[i][j] - array[i+1][j]);
    		}
    		if(j != 0){
    			energy += abs(array[i][j] - array[i][j-1]);
    		}
    		if(j != columns - 1){
    			energy += abs(array[i][j] - array[i][j+1]);
    		}
    		en[i][j] = energy;
    		//outfile << en[i][j] << " ";
    	}
    	//outfile << '\n';
    }

    int seams[rows][columns];

    for (int i = 0; i < rows; i++){
    	for(int j = 0; j < columns; j++){
       		
       		if(i == 0){
    			seams[i][j] = en[i][j];
    		}
    		else if(j == 0){
    			seams[i][j] = en[i][j] + min(seams[i - 1][j], seams[i - 1][j + 1]);
    		}
    		else if(j == columns - 1){
    			seams[i][j] = en[i][j] + min(seams[i - 1][j], seams[i - 1][j - 1]);
    		}
    		else{
    			seams[i][j] = en[i][j] + min(min(seams[i - 1][j - 1], seams[i - 1][j]), seams[i - 1][j + 1]);
    		}
    		
    		outfile << seams[i][j] << " ";
    	}
    	outfile << '\n';
    }
    

    outfile.close();
}