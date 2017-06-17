/*************************************************************************//**
 * @file
 * @brief Contains the main function
 *
 * @mainpage Program 4
 *
 * @section course_section Course Information
 *
 * @authors Garrett McIntosh, Hunter Comer, Jeremy Holwell, Anne Voigt
 *
 * @date April 28, 2017
 *
 * @par Professor:
 *         Roger Schrader
 *
 * @par Course:
 *         CSC 250 - section 1 - 1:00 pm
 *
 * @par Location:
 *         McLaury - Room 313
 *
 * @section program_section Program Information
 *
 * @details This program will open a file from the command line arguments
 * and read the first 3 number and input them into the belt width. The
 * belt length is also aquired from the command line arguments. Then every
 * row after that will contain the dimension of the boxes that are being
 * placed on the belts which will be read into a structure. 
 *
 * These dimensions are then organized so that the smallest number is always
 * the width, then the length and then the height. Then a function in the
 * belt class will decide which belt the box will go on as well as which
 * orientation of the box will take up the least amount of space on the belt.
 * Once that is decided the box will be placed in the queue class that will
 * store it's length. The belt class will then call a function to check if
 * the length of the boxes exceeds the length of the belt and if it does it
 * will check to see if half or more of the box is hanging off the edge
 * in which case the belt class will call the deque function to delete
 * that box. The program will then output which boxes fell off and from
 * which belts.
 *
 * Once the program reaches three -1's in a row it will end the simulation
 * and delete the contents of the queue and restart. Once the program
 * reaches three 0's it will then end the simulation and quit the 
 * program.
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instruction
 *	None
 *
 * @par Usage
   @verbatim
   c:\> prog4.exe data.sim length
        prog4.exe - This contains the program
        data.sim - an input text file that contains different simulations
        length - an argument for the lenght of the belt
   @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 * @bug none
 *
 * @todo none
 *
 * @par Modifications and Development Timeline:
 * <a href="https://gitlab.mcs.sdsmt.edu/csc250s17prog4/team26/commits/master">
 * Please see Gitlab Repository</a>
 *
 *****************************************************************************/
#include "belt.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void orderBox(struct box &b);
void add_check(belt conveyors[], int i, myqueue<box> &letter, box b,
    int totalLength, char beltLetter, ofstream &fout);
void orderBelts(belt conveyors[]);

/*************************************************************************//**
* @author Hunter Comer, Garrett McIntosh, Jeremy Holwell, Anne Voigt
*
* @par Description
* This Function is that starting function for the program. It calls all of the
* other functions and organizes them in a top to bottom fashion.
*
* @param[in] argc - contains the count for the arguments provided in the 
*                   command prompt
* @param[in] argv - the arguments provided at the command prompt
*
* @returns 0 if no error and -1 if there is an error
*
*****************************************************************************/
int main(int argc, char *argv[])
{
    belt conveyors[3];
    box b;
    myqueue<box> A, B, C;
    char beltLetter;
    ifstream fin;
    ofstream fout;
    int width1, width2, width3;
    int i = 0, count = 1, count2 = 1;

    //set command line entry to total length of all belts
    int totalLength = stoi(argv[2]);

    //check to see if there are enough arguements in the command line
    if (argc != 3)
    {
        cout << "Not enough command line arguements. Must include the name"
            << " of the file that contains all the simulations and the length"
            << " of the belts. Exiting." << endl;
        return -1;
    }

    //open and test input file
    fin.open(argv[1]);

    if (!fin)
    {
        cout << "Problem opening input file. Exiting." << endl;
        return -1;
    }

    //open and test output file
    fout.open("run.out");

    if (!fout)
    {
        cout << "Problem opening output file. Exiting." << endl;
        return -1;
    }

    //get widths and lengths of belts
    while (fin >> width1 >> width2 >> width3 && width1 != 0)
    {
        //empty belts of all boxes
        conveyors[0].emptyBelt(A);
        conveyors[1].emptyBelt(B);
        conveyors[2].emptyBelt(C);

        //initialize conveyors
        conveyors[0].initializeBelts(conveyors, 0, totalLength, 
            width1, 'A', A);
        conveyors[1].initializeBelts(conveyors, 1, totalLength, 
            width2, 'B', B);
        conveyors[2].initializeBelts(conveyors, 2, totalLength, 
            width3, 'C', C);

        //put belts in order from least to greatest inside the array
        orderBelts(conveyors);

        //output case number
        fout << "Case " << count2 << ":" << endl;
            
        //reset boxNumbers
        count = 1;

        //add one to case
        count2++;

        //input dimensions of a single box
        while (fin >> b.width >> b.depth >> b.height && b.width != -1)
        {
            //set box number to count
            b.boxNumber = count;

            //order the width, depth, and height of each box
            orderBox(b);

            //decide which belt the box goes on
            i = 0;

            while (conveyors[i].getWidth(i,conveyors) < b.width)
            {
                i++;
            }

            //get the letter of the belt at that array
            conveyors[i].getBelt(beltLetter, conveyors, i);

            //check if depth can fit on the conveyor as well, if it can
            //swap depth and width to insure we take up the smallest length
            //on the belt
            if (b.depth <= conveyors[i].getWidth(i, conveyors))
            {
                swap(b.depth, b.width);
            }

            //add box and check if it fell
            if (beltLetter == 'A')
            {
                add_check(conveyors, i, A, b, totalLength, beltLetter, fout);
            }
            else if (beltLetter == 'B')
            {
                add_check(conveyors, i, B, b, totalLength, beltLetter, fout);
            }
            else if (beltLetter == 'C')
            {
                add_check(conveyors, i, C, b, totalLength, beltLetter, fout);
            }
            
            //add to box number count
            count++;
        }
    }

    //close files
    fin.close();
    fout.close();
    
    return 0;
}

/*************************************************************************//**
* @author Hunter Comer, Anne Voigt
*
* @par Description
* This Function orders the conveyors belts from the belts with the least
* to greatest width
*
* @param[in] conveyors[] - an array that contains the belts
*
* @returns none
*
*****************************************************************************/
void orderBelts(belt conveyors[])
{
    belt a;

    //switch elements in array from least to greatest width
    if (conveyors[0] > conveyors[1])
    {
        a = conveyors[0];
        conveyors[0] = conveyors[1];
        conveyors[1] = a;
    }
    if (conveyors[0] > conveyors[2])
    {
        a = conveyors[0];
        conveyors[0] = conveyors[2];
        conveyors[2] = a;
    }
    if (conveyors[1] > conveyors[2])
    {
        a = conveyors[1];
        conveyors[1] = conveyors[2];
        conveyors[2] = a;
    }
    return;
}

/*************************************************************************//**
* @author Garrett McIntosh
*
* @par Description
* This functions orders the dimensions of the box so that the smallest
* dimension is the width, then the length, then the height.
*
* @param[in, out] b - a strucure that contain the dimensions of
* the box.
*
* @returns none
*
*****************************************************************************/
void orderBox(struct box &b)
{
    //orders the box dimensions from least to greatest
    if (b.width > b.height)
        swap(b.width, b.height);

    if (b.width > b.depth)
        swap(b.width, b.depth);

    if (b.depth > b.height)
        swap(b.depth, b.height);
}

/*************************************************************************//**
* @author Hunter Comer, Garrett McIntosh, Jeremy Holwell, Anne Voigt
*
* @par Description
* Checks to see if any boxes fell off the belt and then outputs
* which box and from which belt it fell off of.
*
* @param[in] conveyors[] - array of the belts
* @param[in] i - a counter
* @param[in, out] letter - the letter of the belt
* @param[in] b - the box that fell off
* @param[in] totalLength - the length off the boxes
* @param[in] beltLetter - the belt letters
* @param[in] fout - the output file
*
* @returns none
*
*****************************************************************************/
void add_check(belt conveyors[], int i, myqueue<box> &letter, box b, 
    int totalLength, char beltLetter, ofstream &fout)
{
    //place onto conveyor
    conveyors[i].placeonBelt(b, letter);

    //check if last box fell off the conveyor
    while (conveyors[i].fallsoffBelt(b, letter, totalLength))
    {
        //output wich box fell
        fout << "       Box " << b.boxNumber << " fell off conveyor " 
            << beltLetter << endl;
    }
}