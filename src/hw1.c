#include "hw1.h"

#ifdef _STRING_H
#error "Do not #include <string.h>. You will get a ZERO."
#endif

#ifdef _STRINGS_H
#error "Do not #include <strings.h>. You will get a ZERO."
#endif

#ifdef _CTYPE_H
#error "Do not #include <ctype.h>. You will get a ZERO."
#endif


/**
 * @brief Validates command line arguments passed to the program.
 * @details This function will validate all the arguments passed to the program
 * and will return a unsigned short (2 bytes) that will contain the
 * information necessary for the proper execution of the program.
 *
 * IF -p is given but no (-r) ROWS or (-c) COLUMNS are specified this function
 * MUST set the lower bits to the default value of 10. If one or the other
 * (rows/columns) is specified then you MUST keep that value rather than assigning the default.
 *
 * @param argc The number of arguments passed to the program from the CLI.
 * @param argv The argument strings passed to the program from the CLI.
 * @return Refer to homework document for the return value of this function.
 */
unsigned short validargs(int argc, char **argv) {
    unsigned short mode = 0;

    // booleans to keep track of which 3 optional arguments have been found already
    bool foundKey = false;
    bool foundRows = false;
    bool foundCols = false;

    // integer to hold rows and columns for after the loop
    int numRows = 0;
    int numCols = 0;

    char *myKey = 0;

    // this int keeps track of which form of cipher we want.
    int polybius = 0;

    // also cannot have 4 arguments
    argv = argv + 1;

    // if more than 1 argument, check to see if -h is the next in line.
    // else, we will parse the argument manually for each piece.
    if (argc > 1){
        // size = 2.. Valid argument, check if -h
        if (strEquality(*argv, "-h") == 0){
            // argument is '-h', so return the max
            return 0x8000;
        }
    }

    // reset argv
    argv = argv - 1;


    // first check # of arguments. If num > 9, error
    if (argc > 9){
        return 0;
    }

    // at this point, we know a couple of things
    // 1. -h flag is not the first argument (so it shouldnt appear anywhere else)
    // 2. there is at least 1 other argument, whether its valid or not, idk yet

    // well we need to make sure that there are at least 3 arguments (the bin/hw1, type of cipher and encryption/decryption)
    if (argc < 3){
        return 0;
    }


    // we have at least the cipher and request, so check the validity of the order of arguments.
    // for each of the arguments, check their validity
    for (int i = 0; i < argc; i++){
        // copy the pointer to the arguments here
        char **loopArgs = argv;
        // iterate the arguments to be in line with the current loop iteration
        loopArgs = loopArgs + i;

        // if it's the first argument, it must be either -p or -f
        if (i == 1){
            // if the argument is -f, we need to flip the second most significant bit.
            if (strEquality(*loopArgs, "-f") == 0){
                unsigned short second = 0x4000;
                mode = mode | second;

                // do not want polybius, so change our value
                polybius = 1;
            }

            // else if its -p, we don't need to do anything
            else if (strEquality(*loopArgs, "-p") == 0){
                unsigned short second = 0x0000;
                mode = mode | second;

                // want polybius, so fix it just in case
                polybius = 0;
            }

            // if this argument is anything else, error
            else{
                return 0;
            }
        }

        // second argument must be either -d or -e
        if (i == 2){
            if (strEquality(*loopArgs, "-d") == 0){
                unsigned short third = 0x2000;
                mode = mode | third;
            }

            else if (strEquality(*loopArgs, "-e") == 0){
                unsigned short third = 0x0000;
                mode = mode | third;
            }

            // else if the second argument is neither of these, its an error
            else{
                return 0;
            }
        }


        // after parsing these 2, the rest are all option arguments. Their ordering doesn't matter
        // They still have certain limitations and requirements, so check for those
        // first check to see if this is polybius or fractioned. They have a different number of optional arguments, which is why.

        // if its a fractioned cipher:
        if (i == 3 && polybius == 1){
            // check to see if there are more arguments. If there are, its an error
            if (argc > 5){
                return 0;
            }

            // key is optional, so check if there are only 3 arguments
            if (argc == 3){
                return mode;
            }

            // check if the arugment present is -k
            if (strEquality(*loopArgs, "-k") == 0){
                // increment loopArgs
                loopArgs += 1;

                // Key is present. First check if it has repeated letters
                if (checkForRepetition(*loopArgs) == 1){
                    return 0;
                }

                // then check if it shares subset
                if (checkForSubset(*loopArgs, fm_alphabet) == 1){
                    return 0;
                }

                // if it passes all of those, then return the mode and store the key
                key = *loopArgs;
                return mode;
            }

            // if its not -k, return 0
            else{
                return 0;
            }
        }

        // if its a polybius cipher, we read the next argument.
        if (i == 3 && polybius == 0){
            // we already checked to see if there are more than max arguments, so don't do it again here
            // instead, lets check which argument this is
            // if is the # columns and we haven't already done it, then get number
            if ((strEquality(*loopArgs, "-c") == 0) && (foundCols == false)){
                loopArgs++;
                i++;

                // store the number of columns in this variable
                numCols = atoi(*loopArgs);

                // set foundCols to true
                foundCols = true;
            }

            else if ((strEquality(*loopArgs, "-r") == 0) && (foundRows == false)){
                loopArgs++;
                i++;

                // store number of rows
                numRows = atoi(*loopArgs);

                // set foundRows to true
                foundRows = true;
            }

            else if ((strEquality(*loopArgs, "-k") == 0) && (foundKey == false)){
                loopArgs++;
                i++;

                // TODO: Check validity of Key.
                // Key is present. First check if it has repeated letters
                if (checkForRepetition(*loopArgs) == 1){
                    return 0;
                }

                // then check if it shares subset
                if (checkForSubset(*loopArgs, polybius_alphabet) == 1){
                    return 0;
                }

                // if both pass, then we have found a valid key.
                key = *loopArgs;
                foundKey = true;

                myKey = *loopArgs;
            }

            else{
                // something went wrong. Either the argument is something weird or we encountered a repeated arg. return 0
                return 0;
            }
        }


        if (i == 5 && polybius == 0){
            // we already checked to see if there are more than max arguments, so don't do it again here
            // instead, lets check which argument this is
            // if is the # columns and we haven't already done it, then get number
            if ((strEquality(*loopArgs, "-c") == 0) && (foundCols == false)){
                loopArgs++;
                i++;

                // store the number of columns in this variable
                numCols = atoi(*loopArgs);

                // set foundCols to true
                foundCols = true;
            }

            else if ((strEquality(*loopArgs, "-r") == 0) && (foundRows == false)){
                loopArgs++;
                i++;

                // store number of rows
                numRows = atoi(*loopArgs);

                // set foundRows to true
                foundRows = true;
            }

            else if ((strEquality(*loopArgs, "-k") == 0) && (foundKey == false)){
                loopArgs++;
                i++;

                // TODO: Check validity of Key.
                // Key is present. First check if it has repeated letters
                if (checkForRepetition(*loopArgs) == 1){
                    return 0;
                }

                // then check if it shares subset
                if (checkForSubset(*loopArgs, polybius_alphabet) == 1){
                    return 0;
                }

                // if both pass, then we have found a valid key.
                key = *loopArgs;
                foundKey = true;

                myKey = *loopArgs;
            }

            else{
                // something went wrong. Either the argument is something weird or we encountered a repeated arg. return 0
                return 0;
            }
        }


        if (i == 7 && polybius == 0){
            // we already checked to see if there are more than max arguments, so don't do it again here
            // instead, lets check which argument this is
            // if is the # columns and we haven't already done it, then get number
            if ((strEquality(*loopArgs, "-c") == 0) && (foundCols == false)){
                loopArgs++;
                i++;

                // store the number of columns in this variable
                numCols = atoi(*loopArgs);

                // set foundCols to true
                foundCols = true;
            }

            else if ((strEquality(*loopArgs, "-r") == 0) && (foundRows == false)){
                loopArgs++;
                i++;

                // store number of rows
                numRows = atoi(*loopArgs);

                // set foundRows to true
                foundRows = true;
            }

            else if ((strEquality(*loopArgs, "-k") == 0) && (foundKey == false)){
                loopArgs++;
                i++;

                // TODO: Check validity of Key.
                // Key is present. First check if it has repeated letters
                if (checkForRepetition(*loopArgs) == 1){
                    return 0;
                }

                // then check if it shares subset
                if (checkForSubset(*loopArgs, polybius_alphabet) == 1){
                    return 0;
                }

                // if both pass, then we have found a valid key.
                key = *loopArgs;
                foundKey = true;

                myKey = *loopArgs;
            }

            else{
                // something went wrong. Either the argument is something weird or we encountered a repeated arg. return 0
                return 0;
            }
        }
    }

    // default number of rows to 10
    if (numRows == 0){
        numRows = 10;
    }


    // default number of cols to 10
    if (numCols == 0){
        numCols = 10;
    }

    // at this point, we need to check if rows and columns are correct dimension
    if (numCols > 15 || numCols < 9 || numRows > 15 || numRows < 9){
        return 0;
    }

    // check against the length of the alphabet
    if (!foundKey){
        // store the key to be the alphabet itself, since the alphabet is populated first it wont make a difference
        // fractioned cipher, alphabet is different
        if (polybius == 1){
            key = fm_alphabet;
        }

        else{
            key = polybius_alphabet;
        }

        if (numCols * numRows < specialStrLen(key)){
            return 0;
        }
    }

    else{
        if (numCols * numRows < arraySize(myKey)){
            return 0;
        }
    }

    // at this point, all validation is done. arguments are fine, rows/cols are fine, key is fine and saved
    // now we need to manipulate the bits to save the rows and cols

    // upper 4 are the rows
    numRows = numRows << 4;
    mode = mode | numRows;

    // lower 4 are the cols
    mode = mode | numCols;

    return mode;
}