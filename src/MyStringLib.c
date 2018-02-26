#include <stdbool.h>

int arraySize(char *argv){
    int size = 0;

    while (*argv != '\0'){
        argv++;
        size++;
    }

    return size;
}


int specialStrLen(const char *arg){
    int size = 0;

    while (*arg != '\0'){
        arg++;
        size++;
    }
    return size;
}
/**
* @brief Compares 2 strings for their equality
* returns 1 if they're not equal
* returns 0 if they are equal
*/
int strEquality(char *str1, char *str2){
    int size1 = arraySize(str1);
    int size2 = arraySize(str2);

    if (size1 != size2){
        return 1;
    }

    while (*str1!= '\0'){
        if (*str1 != *str2){
            return 1;
        }
        str1++;
        str2++;
    }

    // all equality tests passed (length and character matching)
    return 0;
}

int checkForRepetition(char *str){
    int size = arraySize(str);

    char *copy1 = str;
    char *copy2 = str;

    for (int i = 0; i < size; i++){

        for (int j = i; j < size; j++){

            if (j != i){
                // if the characters are the same, return failure
                if (*copy1 == *copy2){
                    return 1;
                }
            }
            copy2++;
        }
        copy1++;
        copy2 = copy1;
    }
    return 0;
}


int checkForSubset(char *str1, const char *str2){
    // starts off as 0, assuming that the char is in the set
    bool inSet = false;
    int size1 = arraySize(str1);
    int size2 = arraySize((char*)str2);

    const char *str2Copy = str2;

    for (int i = 0; i < size1; i++){

        for (int j = 0; j < size2; j++){

            // if its in the set, move on
            if (*str1 == *str2Copy){
                inSet = true;
                break;
            }

            // if its not in the set,
            else{
                inSet = false;
            }

            str2Copy++;
        }

        if (inSet == false){
            return 1;
        }

        // if it was in the set, increment str1 and reset str2
        str1++;
        str2Copy = str2;
    }

    return 0;
}