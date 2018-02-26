#include "hw1.h"

void populateTable(int rows, int cols){
    // we have the key from the variable *key in const.c
    // first fill the table with the key
    // copy it since its not possible to iterate over the key itself.
    char* keyCopy = (char*)key;
    int keyCopySize = specialStrLen(key);

    int endOfKey = 0;
    bool inKey = false;

    char *polybius_table_copy = polybius_table;

    for (endOfKey = 0; endOfKey < keyCopySize; endOfKey++){
        // for each of the charactes in the key, copy it to the array
        *polybius_table_copy = *keyCopy;
        polybius_table_copy++;
        keyCopy++;
    }

    // copy the polybius alphabet
    char* polybiusCopy = (char*)polybius_alphabet;
    int alphabetLength = arraySize(polybiusCopy);

    // now the key has been added. Now go through the entire alphabet and add it to the table.
    // make sure to filter out characters that already appeared in the key
    for (endOfKey = endOfKey; endOfKey < rows * cols; endOfKey++){

        if (alphabetLength <= 0){
            while (endOfKey < rows * cols){
            *polybius_table_copy = '\0';
            polybius_table_copy++;
            endOfKey++;
            }
        }

        // reset the copy of the key
        keyCopy = (char*)key;
        inKey = false;

        for (int i = 0; i < keyCopySize; i++){
            // if the current char is in the key, set inKey to true
            if (*polybiusCopy == *keyCopy){
                inKey = true;
                endOfKey--;
            }
            keyCopy++;
        }

        // if its not in the key, then add it to the table
        if (inKey == false){
            *polybius_table_copy = *polybiusCopy;
            polybius_table_copy++;
        }

        // increment polybius alphabet copy
        polybiusCopy++;

        alphabetLength--;
    }
}


int encrypted(int rows, int cols, char c){
    // look up the charcter in the table to see if it exists
    // returns 0 if it doesn't.
    char *copy = polybius_table;

    for (int i = 0; i < rows * cols; i++){
        if (*copy == c){
            // return value here. Need to return 2D value
            return i;
        }
        copy++;
    }
    return -1;
}

char getRow(int rows, int cols, int value){
    int x =  value / cols;

    if (x == 10){
        return 'A';
    }

    if (x == 11){
        return 'B';
    }

    if (x == 12){
        return 'C';
    }

    if (x == 13){
        return 'D';
    }

    if (x == 14){
        return 'E';
    }

    if (x == 15){
        return 'F';
    }

    else{
        return x + 48;
    }
}

char getCol(int rows, int cols, int value){
    int y = value % cols;

    if (y == 10){
        return 'A';
    }

    if (y == 11){
        return 'B';
    }

    if (y == 12){
        return 'C';
    }

    if (y == 13){
        return 'D';
    }

    if (y == 14){
        return 'E';
    }

    if (y == 15){
        return 'F';
    }

    else{
        return y + 48;
    }
}

/* polybiusEncryption()
 *
 * takes num rows and cols as argument.
 */
int polybiusEncryption(int rows, int cols){
    populateTable(rows, cols);

    // now that the table is populated with the key, we must read input and write the encrypted line back
    char c = 0;

    while (true){
        c = getchar();

        if (c == EOF){
            break;
        }

        // take care of whitespace characters
        else if (c == '\n'){
            printf("\n");
        }

        else if (c == '\t'){
            printf("\t");
        }

        else if (c == ' '){
            printf(" ");
        }

        else{
            int indexOfChar = encrypted(rows, cols, c);

            if (indexOfChar == -1){
                // character was not in the table, throw an error
                return EXIT_FAILURE;
            }

            // if its not an error, get the first part of the location
            printf("%c", getRow(rows, cols, indexOfChar));

            // then get second
            printf("%c", getCol(rows, cols, indexOfChar));
        }
    }
    return EXIT_SUCCESS;
}

char findInTable(int rows, int cols, int x, int y){
    // given the X and Y, we can convert it to a 1d index
    return *polybius_table + (x * cols + y);
}

int polybiusDecryption(int rows, int cols){
    // the table populating is done the same way as encyption
    populateTable(rows, cols);

    char c = 0;

    while(true){
        c = getchar();

        if (c == EOF){
            break;
        }

        // take care of whitespace characters
        else if (c == '\n'){
            printf("\n");
        }

        else if (c == '\t'){
            printf("\t");
        }

        else if (c == ' '){
            printf(" ");
        }

        else{
            // we need to read the next char as well
            char c2 = 0;
            c2 = getchar();

            int findrow = 0, findcol = 0;

            if (c == 'A'){
                findrow = 10;
            }
            else if (c == 'B'){
                findrow = 11;
            }
            else if (c == 'C'){
                findrow = 12;
            }
            else if (c == 'D'){
                findrow = 13;
            }
            else if (c == 'E'){
                findrow = 14;
            }
            else if (c == 'F'){
                findrow = 15;
            }
            else{
                // get integer representations of the characters
                findrow = c -48;
            }

            if (c2 == 'A'){
                findcol = 10;
            }
            else if (c2 == 'B'){
                findcol = 11;
            }
            else if (c2 == 'C'){

                findcol = 12;
            }
            else if (c2 == 'D'){
                findcol = 13;
            }
            else if (c2 == 'E'){
                findcol = 14;
            }
            else if (c2 == 'F'){
                findcol = 15;
            }
            else{
                findcol = c2 - 48;
            }


            printf("%c", findInTable(rows, cols, findrow, findcol));

        }
    }
    return EXIT_SUCCESS;
}