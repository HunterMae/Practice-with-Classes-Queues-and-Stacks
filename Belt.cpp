/*************************************************************************//**
 * @file 
 * @brief Functions for the belt class "belt.h"
 *****************************************************************************/
#include "belt.h"

/*************************************************************************//**
 * @author Hunter Comer, Garrett McIntosh, Jeremy Holwell, Anne Voigt
 *
 * @par Description:
 * Sets up an belt and initializes all dimensions to zero
 *****************************************************************************/
belt::belt()
{
    //initialize all dimensions of belt
    beltWidth = 0;
    beltLength = 0;
    accumulateLength = 0;
}

/*************************************************************************//**
 * @author Hunter Comer, Garrett McIntosh, Jeremy Holwell, Anne Voigt
 *
 * @par Description:
 * Destroys the belt when it goes out of scope
 *****************************************************************************/
belt::~belt()
{

}

/*************************************************************************//**
 * @author Hunter Comer
 *
 * @par Description:
 * Checks to see if a box fell off a specific belt. It fell off if the very 
 * first belt that was put on the queue is more than halfway off the total 
 * length of the belt. It decreases accumulated length if one fell.
 *
 * @param[in]     totalLength - the total length of the belt
 * @param[in,out] beltLetter - the belt that we're checking
 * @param[in,out] b - the box that is at the front of the queue, will be
 *                    returned if it fell off.
 *
 * @returns true if box fell off, false if one didn't
 *****************************************************************************/
bool belt::fallsoffBelt(struct box &b, myqueue<box> &beltLetter, 
    int totalLength)
{
    int overflow;

    //get front box on the belt
    beltLetter.front(b);

    //subtract the length of the belt from the accumulated length
    overflow = accumulateLength - totalLength;

    //if the answer is greater than half of the front box, get rid of box
    if (overflow >= (b.depth / 2))
    {
        beltLetter.deque(b);
        accumulateLength -= b.depth;
        return true;
    }

    return false;
}

/*************************************************************************//**
 * @author Hunter Comer
 *
 * @par Description:
 * Places a box on a specified belt and adds to the accumulated length.
 *
 * @param[in,out] beltLetter - the belt that we're adding to
 * @param[in]     b - the box that we are placing onto the belt
 *
 * @returns true to say that box was added correctly
 *****************************************************************************/
bool belt::placeonBelt(struct box b, myqueue<box> &beltLetter)
{
    //add to accumulated length the depth of the box (length)
    accumulateLength += b.depth;

    //add box to belt
    beltLetter.enque(b);
    
    return true;
}

/*************************************************************************//**
 * @author Hunter Comer
 *
 * @par Description:
 * This gives us access to return which belt is stored in an array element.
 *
 * @param[in]     i - the element of the array
 * @param[in]     conveyors - the array we're searching in
 * @param[in,out] beltLetter - the returned value; sets which belt is in the 
 *                specific element in the array
 *
 * @returns beltLetter
 *****************************************************************************/
char belt::getBelt(char &beltLetter, belt conveyors[], int i)
{
    //get belt letter from array
    beltLetter = conveyors[i].beltLetter;

    return beltLetter;
}

/*************************************************************************//**
 * @author Hunter Comer
 *
 * @par Description:
 * Allows us to access the width of a belt in a specific element of an array.
 * Returns the width of the specific array.
 *
 * @param[in]     i - the element of the array
 * @param[in]     conveyors - the array that we're searching
 *
 * @returns width
 *****************************************************************************/
int belt::getWidth(int i, belt conveyors[])
{
    int width;

    //get width of belt from array
    width = conveyors[i].beltWidth;

    return width;
}

/*************************************************************************//**
 * @author Hunter Comer
 *
 * @par Description:
 * This allows us to initialize the specific values that we got from the 
 * input file and store them in specific elements of an array.
 *
 * @param[in]     length - the total length of the belt
 * @param[in]     letter - the belt letter (A, B, or C)
 * @param[in]     conveyors - the array we're changing
 * @param[in]     i - the element in the array
 * @param[in]     w - the width of the array that we're adding
 * @param[in,out] queueLetter - the actual queue that we're assigning to 
 *                each belt.
 *
 * @returns nothing
 *****************************************************************************/
void belt::initializeBelts(belt conveyors[], int i, int length, int w, 
    char letter, myqueue<box> &queueLetter) //hunter
{
    //initialize the belt length, width, and letter from inputed values
    conveyors[i].beltLength = length;
    conveyors[i].beltWidth = w;
    conveyors[i].beltLetter = letter;
    conveyors[i].accumulateLength = 0;
    conveyors[i].theBelt = queueLetter;
}

/*************************************************************************//**
 * @author Hunter Comer, Garrett McIntosh, Jeremy Holwell, Anne Voigt
 *
 * @par Description:
 * This empty's each belt of all boxes so that we can start with a new case.
 *
 * @param[in,out] beltLetter - the belt that we're emptying
 *
 * @returns nothing
 *****************************************************************************/
void belt::emptyBelt(myqueue<box> &beltLetter)
{
    box b;

    //while the belt isn't empty, get rid of the top box
    while (!beltLetter.isEmpty())
    {
        beltLetter.front(b);
        beltLetter.deque(b);
    }
}

/*************************************************************************//**
 * @author Hunter Comer, Garrett McIntosh, Jeremy Holwell, Anne Voigt
 *
 * @par Description:
 * This function overloads an operator so that we have access to the individual
 * widths of each belt that way we can order the elements of each array 
 * according to belt widths.
 *
 * @param[in]     lhs - the left hand side of the > sign
 * @param[in]     rhs - the right hand side of the > sign
 *
 * @returns true if left hand side is greater than the right hand side, 
 * returns false if otherwise
 *****************************************************************************/
bool operator>(const belt lhs, const belt rhs)
{
    if (lhs.beltWidth > rhs.beltWidth)
        return true;
    return false;
}