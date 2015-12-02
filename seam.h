/*****************************************
*  Programmer: Tyler Potochnik           *
*  The University Of Akron               *
*                                        *
*  Last Edited:                 *
*                                        *
*****************************************/

#ifndef SEAM_H
#define SEAM_H

using namespace std;

class SeamCarving{
private:
	int vert, horz;
	string file;
public:
	SeamCarving(int, int, string);
	void removeVertical();
	void removeHorizontal();
};

#endif