///
/// File: readcsv.c
///
/// Program reads in a CSV which contains US Census data and performs
/// metrics upon the information held within.
/// A run of readcsv will provide the following example output:
///
/// Total population across 50 zipcodes is 1750367.
/// The fewest people live in 14619, population 1234.
/// The most people live in 90210, population 56789.
///
/// @author kjb2503 : Kevin Becker
///
// // // // // // // // // // // // // // // // // // // // // // // // //

#include <stdio.h> // fgets
#include <stdlib.h> // EXIT_SUCCESS
#include <limits.h> // INT_MAX

#define OFFSET 6 // this is an offset used by getPopulation (the total population is always after
                 // the 5-digit zipcode so we can hard-code this offset
#define BUFFER_SIZE 256 // the size of buffer we want 
                        // (prevents any sort of tampering so that fgets' argument regarading buffer
                        //  size is correct)

///
/// Function: getZip
///
/// Description: Gets the zipcode from a line read in census data buffer.
///
/// @param *str  The read in line containing data on a zipcode.
/// @param *zipStr The pointer to where the zipcode is needed.
///
void getZip(char *str, char *zipStr)
{
    //zipcode is the first entry in the CSV line therefore we seek the first five characters of a line
    for(int i = 0; i < 5; i++)
    {
        zipStr[i] = str[i];
    }
}


///
/// Function: changeZip
///
/// Description: Changes the value of a zipcode from an old to a new.
///
/// @param *oldZip  The pointer to the old zip (where the new zip should go).
/// @param *newZip  The pointer to the new zip which we are copying.
///
void changeZip(char *oldZip, char *newZip)
{
    // loop until we get to the end
    for(int i = 0; oldZip[i] != '\0'; i++)
        oldZip[i] = newZip[i];
}


///
/// Function: main
///
/// Description: Performs main funcions--reading in data, analyzing and printing results.
///
/// @param argc  The parameter which contains the number of arguments given.
/// @param **argv  The arguments which were given when the program runs.
///
int main(int argc, char **argv)
{
    // uses argc and argv so we don't get -Wunused-variable warning
    (void)argc;
    (void)argv;

    // creates a buffer of size 256 (the max line size specified) for reading in data
    char buffer [BUFFER_SIZE];

    // all of these are unsigned as it would be pretty silly to have negative population
    int totalPopulation = 0;
    // the total number of zipcodes (a short since we don't need more than that)
    unsigned short totalZipCodes = 0;

    // used for the fewest population
    char fewestZip[] = "00000";
    int fewestPopulation = INT_MAX;

    // used for the largest population
    char largestZip[] = "00000";
    int largestPopulation = 0;

    // used to store information about our current population
    char currentZip[] = "00000";
    // gets our current population
    int currentPopulation;

    // DATA READ IN AND PROCESSING PARENT PROCEDURE ===============
    // we keep going until we hit the EOF character ("\0")
    while(fgets(buffer, BUFFER_SIZE, stdin) != NULL)
    {
        // skips any line which begins with 'Z' (we don't want it, it's our header line)
        if(buffer[0] == 'Z')
            continue;

        // we add one to the total number of zipcodes (as we have just read in a line)
        totalZipCodes++;

        // PARSING DATA PROCEDURE ================================
        // gets and sets our current zip (from the read in buffer)
        getZip(buffer, currentZip);

        // gets our population (in base 10) at the location of the start of our read line
        // plus OFFSET
        currentPopulation = strtol((buffer + OFFSET), NULL, 10);
        // adds to our total population
        totalPopulation += currentPopulation;

        // checks to see if we need to update our largest/fewest populations
        if(currentPopulation > largestPopulation)
        {
            largestPopulation = currentPopulation;
            changeZip(largestZip, currentZip);
        }
        else if(currentPopulation < fewestPopulation)
        {
            fewestPopulation = currentPopulation;
            changeZip(fewestZip, currentZip);
        }
    }

    // the data have been processed, we can output our results now
    printf("Total population across %d zipcodes is %d.\n", totalZipCodes, totalPopulation);
    printf("The fewest people live in %s, population %d.\n", fewestZip, fewestPopulation);
    printf("The most people live in %s, population %d.\n", largestZip, largestPopulation);

    return EXIT_SUCCESS;
}
