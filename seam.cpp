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
#include <climits>
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

   	
   	int currVert = rows, currHoriz = columns;
// remove vertical seams
   	for(int i = 0; i < vertical; i++){
   		int en[currVert][currHoriz];
  		
	  	// Creates Energy Array
	    for (int i = 0; i < currVert; i++){
	    	for(int j = 0; j < currHoriz; j++){
	    		int energy = 0;
	    		if(i != 0){
	    			energy += abs(array[i][j] - array[i-1][j]);
	    		}
	    		if(currVert-1 != i){
	    			energy += abs(array[i][j] - array[i+1][j]);
	    		}
	    		if(j != 0){
	    			energy += abs(array[i][j] - array[i][j-1]);
	    		}
	    		if(j != currHoriz - 1){
	    			energy += abs(array[i][j] - array[i][j+1]);
	    		}
	    		en[i][j] = energy;
	    		
	    	}
	    	
	    }

	    int combinedEn[currVert][currHoriz];

	    //creates cumulative energy array
	    for (int i = 0; i < currVert; i++){
	    	for(int j = 0; j < currHoriz; j++){
	       		
	       		if(i == 0){
	    			combinedEn[i][j] = en[i][j];
	    		}
	    		else if(j == 0){
	    			combinedEn[i][j] = en[i][j] + 
	    			min(combinedEn[i - 1][j], combinedEn[i - 1][j + 1]);
	    		}
	    		else if(j == currHoriz - 1){
	    			combinedEn[i][j] = en[i][j] + 
	    			min(combinedEn[i - 1][j], combinedEn[i - 1][j - 1]);
	    		}
	    		else{
	    			combinedEn[i][j] = en[i][j] + 
	    			min(min(combinedEn[i - 1][j - 1], combinedEn[i - 1][j]), combinedEn[i - 1][j + 1]);
	    		}
	    	}
	    }
	int smallest = INT_MAX;
	int minCol = 0;

	for(int i = 0; i < currHoriz; i++){
		if(combinedEn[currVert-1][i] < smallest){
			smallest = combinedEn[currVert - 1][i];
			minCol = i;
		}
	}
    
	// remove seams    
	    for(int i = currVert-1; i >=0; i--){
	    	for(int column = minCol; column < currHoriz; column++){
	    		array[i][column] = array[i][column+1];
	    	}
	    	if(minCol == 0){
	    		if(combinedEn[i - 1][minCol+1] < combinedEn[i-1][minCol]){
	    			minCol+=1;
	    			
	    		}
	    	}
	    		else if(minCol == currHoriz-1){
	    			if(combinedEn[i-1][minCol-1] <= combinedEn[i-1][minCol]){
	    				minCol -= 1;
	    			}
	    		}
	    		else{
	    			if((combinedEn[i-1][minCol-1] <= combinedEn[i-1][minCol]) && (combinedEn[i-1][minCol-1] <= combinedEn[i-1][minCol+1])){
	    				minCol -= 1;
	    			}
	    			if((combinedEn[i-1][minCol+1] < combinedEn[i-1][minCol]) && (combinedEn[i-1][minCol+1] < combinedEn[i-1][minCol-1])){
	    				minCol += 1;
	    				
	    			}
	    		}
	    	
	    }
	    currHoriz--;
	}
// remove horizontal seams
	for(int i = 0; i < horizontal; i++){
   		int en[currVert][currHoriz];
  		
	  	// Creates Energy Array
	    for (int i = 0; i < currVert; i++){
	    	for(int j = 0; j < currHoriz; j++){
	    		int energy = 0;
	    		if(i != 0){
	    			energy += abs(array[i][j] - array[i-1][j]);
	    		}
	    		if(currVert-1 != i){
	    			energy += abs(array[i][j] - array[i+1][j]);
	    		}
	    		if(j != 0){
	    			energy += abs(array[i][j] - array[i][j-1]);
	    		}
	    		if(j != currHoriz - 1){
	    			energy += abs(array[i][j] - array[i][j+1]);
	    		}
	    		en[i][j] = energy;
	    	}	
	    }

	    int combinedEn[currVert][currHoriz];

	    //creates cumulative energy array
	    for(int c = 0; c < currHoriz; c++){
	    	for(int r = 0; r < currVert; r++){
	       		
	       		if(c == 0){
	    			combinedEn[r][c] = en[r][c];
	    		}
	    		else if(r == 0){
	    			combinedEn[r][c] = en[r][c] + 
	    			min(combinedEn[r][c-1], combinedEn[r+1][c-1]);
	    		}
	    		else if(r == currVert - 1){
	    			combinedEn[r][c] = en[r][c] + 
	    			min(combinedEn[r][c-1], combinedEn[r-1][c-1]);
	    		}
	    		else{
	    			combinedEn[r][c] = en[r][c] + 
	    			min(min(combinedEn[r-1][c-1], combinedEn[r][c-1]), combinedEn[r+1][c-1]);
	    		}
	    	
	    	}	
	
	   }
	int smallest = INT_MAX;
	int minCol = 0;

	for(int i = 0; i < currVert; i++){
		if(combinedEn[i][currHoriz-1] < smallest){
			smallest = combinedEn[i][currHoriz-1];
			minCol = i;
		}
	}
    
    // remove seams
	    for(int i = currHoriz-1; i >=0; i--){
	    	for(int row = minCol; row < currVert; row++){
	    		array[row][i] = array[row+1][i];
	    	}
	    	if(minCol == 0){
	    		if(combinedEn[minCol+1][i - 1] < combinedEn[minCol][i-1]){
	    			minCol+=1;
	    			
	    		}
	    	}
	    		else if(minCol == currHoriz-1){
	    			if(combinedEn[minCol-1][i-1] <= combinedEn[minCol][i-1]){
	    				minCol -= 1;
	    			}
	    		}
	    		else{
	    			if((combinedEn[minCol-1][i-1] <= combinedEn[minCol][i-1]) && (combinedEn[minCol-1][i-1] <= combinedEn[minCol+1][i-1])){
	    				minCol -= 1;
	    			}
	    			if((combinedEn[minCol+1][i-1] < combinedEn[minCol][i-1]) && (combinedEn[minCol+1][i-1] < combinedEn[minCol-1][i-1])){
	    				minCol += 1;
	    				
	    			}
	    		}
	    	
	    }
	   currVert--;
	} 
outfile << currHoriz << " " << currVert << '\n';
    outfile << size << '\n';

for(int i = 0; i < currVert; i++){
	for(int j = 0; j < currHoriz; j++){
		outfile << array[i][j] << " ";
	}
	outfile << '\n';
}
   		
    outfile.close();
}
