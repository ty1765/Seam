/*****************************************
*  Programmer: Tyler Potochnik           *
*  The University Of Akron               *
*                                        *
*  Last Edited:                 *
*                                        *
*****************************************/
#include <iostream>
#include <stdlib.h>
#include <string>
#include "seam.h"

using namespace std;

int main(int argc, char *argv[]){
	if(argc == 4){
		string file = argv[1];
		int vertical = atoi(argv[2]);
		int horizontal = atoi(argv[3]);
		cout << file << " vertical: " << vertical << " horizontal: " << horizontal << endl;
		SeamCarving seam(vertical, horizontal, file);
	}
	else{
		cerr << "Invalid Number of Arguments" << endl;
	}
}