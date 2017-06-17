/***********************************************************************//**
* @file
* @brief headerfile for the belt class, contains the functions to 
* the belt
***************************************************************************/
#include "myqueue.h"

/**
* @brief the functions in the belt class
*/
#ifndef __BELT__H__
#define __BELT__H__

/**
* @brief A structure to hold the information of the boxes
*/
struct box
{
    int boxNumber;   /*!< Integer that holds the box number */
    int width;  /*!< Integer that holds the box width*/
    int depth; /*!< Integer that holds the box depth*/
    int height; /*!< Integer that holds the box height*/
};

/**
* @brief A class that holds all the functions that use the conveyer
belt, such as moving boxes onto and off of the belt. 
*/

class belt
{
    public:
        /*! the function used to construct the belt*/
        belt();
        /*! the function used to deconstruct the belt*/
        ~belt();

        /*! the function used to place a box on a belt*/
        bool placeonBelt(struct box b, myqueue<box> &beltLetter);
        /*! the function used for removing a box off a belt*/
        bool fallsoffBelt(struct box &b, myqueue<box> &beltLetter, 
            int totalLength);
        /*! the function used to get the current belt letter */
        char getBelt(char &beltLetter, belt conveyors[], int i);
        /*! the function used to get the width of a certain belt*/
        int getWidth(int i, belt conveyors[]);
        /*! the function used to create the belts*/
        void initializeBelts(belt conveyors[], int i, int length, int w, 
            char letter, myqueue<box> &queueLetter);
        /*! the function used to compare belts*/
        friend bool belt::operator>(const belt lhs, const belt rhs);
        /*! the function used to determine if a belt is empty*/
        void emptyBelt(myqueue<box> &beltLetter);

    private:
        myqueue<box> theBelt;  /*!< The packages on the belt*/
        int beltWidth;         /*!< The width of the belt*/
        int beltLength;        /*!< The length of the conveyor belt*/
        char beltLetter;       /*!< The label for the belt*/
        int accumulateLength;  /*!< The amount of the belt used*/
};
#endif