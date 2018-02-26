#include "hw1.h"

void fillFractionedTable(){
    // we have the key from the variable *key in const.c
    // first fill the table with the key
    // copy it since its not possible to iterate over the key itself.
    char* keyCopy = (char*)key;
    int keyCopySize = specialStrLen(key);

    int endOfKey = 0;
    bool inKey = false;

    char *fm_key_copy = fm_key;

    for (endOfKey = 0; endOfKey < keyCopySize; endOfKey++){
        // for each of the charactes in the key, copy it to the array
        *fm_key_copy = *keyCopy;
        fm_key_copy++;
        keyCopy++;
    }

    // key has been copied. Now fill in the rest of fm_key with the alphabet - key
    int fm_size = sizeof(fm_key)/sizeof(*fm_key);

    // copy the polybius alphabet
    char* alphabetCopy = (char*)fm_alphabet;
    int alphabetLength = arraySize(alphabetCopy);


    // now the key has been added. Now go through the entire alphabet and add it to the table.
    // make sure to filter out characters that already appeared in the key
    for (endOfKey = endOfKey; endOfKey < fm_size; endOfKey++){

        if (alphabetLength <= 0){
            while (endOfKey < fm_size){
            *fm_key_copy = '\0';
            fm_key_copy++;
            endOfKey++;
            }
        }

        // reset the copy of the key
        keyCopy = (char*)key;
        inKey = false;

        for (int i = 0; i < keyCopySize; i++){
            // if the current char is in the key, set inKey to true
            if (*alphabetCopy == *keyCopy){
                inKey = true;
                endOfKey--;
            }
            keyCopy++;
        }

        // if its not in the key, then add it to the table
        if (inKey == false){
            *fm_key_copy = *alphabetCopy;
            fm_key_copy++;
        }

        // increment polybius alphabet copy
        alphabetCopy++;

        alphabetLength--;
    }


    /*for (int i = 0; i < fm_size; i++){
        printf("%c\n", *(fm_key+i));
    }*/
}
// morse_table is used for the initial conversion to morse code. It has ascii-based indexing. First element is !
// read each letter from the input, and look it up in morse_table. If the character doesn't have an encoding (ie its ""), then return error
// if it does have an encoding, return the string

int convert(){
    // size of polybius is 3. check all 3 letters to find their character encoding
    //int sizeOfTable = specialStrLen(*fractionated_table);

    //printf("\nThe tuple sent here is: %c%c%c\n", *(polybius_table + 0), *(polybius_table + 1), *(polybius_table + 2));

    for (int i = 0; i < 26; i++){

        if ( (*(polybius_table + 0) ==  *(*(fractionated_table + i) + 0))
            && (*(polybius_table + 1) ==  *(*(fractionated_table + i) + 1))
            && (*(polybius_table + 2) ==  *(*(fractionated_table + i) + 2))){

            printf("%c", *(fm_key + i));
            // return sucess code
            return EXIT_SUCCESS;

            // if they all match, then we return the letter at this index in fm_key
      /*      for (int len = 0; len < arraySize(fm_key); len++){
                if (*(fm_key + len) - 65 == i){
                    printf("%c", *(fm_key + len));;
                }
            }*/
        }
    }
    return EXIT_FAILURE;
}

int fractionedEncryption(){
    fillFractionedTable();

    // current char is what we are reading now
    // old char is one from previous run. It's used for spacing issues.
    char currentChar = 0;
    char oldChar = 0;
    int intermediateIndex = 0;
    bool wordSpace = false;


    while(true){
        oldChar = currentChar;
        currentChar = getchar();


        if (currentChar == EOF){
            if(intermediateIndex == 2){
                // 2 chars in buffer, check if they are 'x'
                if (*(polybius_table + 0) == 'x' && *(polybius_table + 1) == 'x'){
                }

                else{
                    *(polybius_table + intermediateIndex) = 'x';
                    intermediateIndex++;

                    // we have 3 chars in the buffer, so convert them to the alphabetical letter
                    if (intermediateIndex == 3){
                        if (convert() == EXIT_FAILURE){
                            return EXIT_FAILURE;
                        }
                        intermediateIndex = 0;
                    }
                }
            }

            else{
                *(polybius_table + intermediateIndex) = 'x';
                intermediateIndex++;

                // we have 3 chars in the buffer, so convert them to the alphabetical letter
                if (intermediateIndex == 3){
                    if (convert() == EXIT_FAILURE){
                        return EXIT_FAILURE;
                    }
                    intermediateIndex = 0;
                }
            }
            break;
        }

        // take care of whitespace
        // take care of whitespace characters
        else if (currentChar == '\n'){
            // at the end of each line, put another x as long as there aren't 2 x's before it
            if(intermediateIndex == 2){
                // 2 chars in buffer, check if they are 'x'
                if (*(polybius_table + 0) == 'x' && *(polybius_table + 1) == 'x'){
                }

                else{
                    *(polybius_table + intermediateIndex) = 'x';
                    intermediateIndex++;

                    // we have 3 chars in the buffer, so convert them to the alphabetical letter
                    if (intermediateIndex == 3){
                        if (convert() == EXIT_FAILURE){
                            return EXIT_FAILURE;
                        }
                        intermediateIndex = 0;
                    }
                }
            }

            else{
                *(polybius_table + intermediateIndex) = 'x';
                intermediateIndex++;

                // we have 3 chars in the buffer, so convert them to the alphabetical letter
                if (intermediateIndex == 3){
                    if (convert() == EXIT_FAILURE){
                        return EXIT_FAILURE;
                    }
                    intermediateIndex = 0;
                }
            }

            intermediateIndex = 0;
            wordSpace = false;

            printf("\n");
        }

        /***********
        The problem here is that when the else if doesn't happen, it keeps going all the way to the else statement
        that else statement shouldn't be happening

        the fix? change the loop code so that it evaluates this stuff separately or add an extra boolean
        ill know what im talking about when i wake up in the morning
        */

        else if ((currentChar == '\t' && oldChar != '\t') && (currentChar == '\t' && oldChar != ' ')){
            //printf("\t");
             // found space
            if (wordSpace == true){
                // if its a space, we put xx in the buffer
                *(polybius_table + intermediateIndex) = 'x';
                intermediateIndex++;

                // we have 3 chars in the buffer, so convert them to the alphabetical letter
                if (intermediateIndex == 3){
                    if (convert() == EXIT_FAILURE){
                        return EXIT_FAILURE;
                    }
                    intermediateIndex = 0;
                }
                wordSpace = false;
            }

            else{
                // if its a space, we put xx in the buffer
                *(polybius_table + intermediateIndex) = 'x';
                intermediateIndex++;

                // we have 3 chars in the buffer, so convert them to the alphabetical letter
                if (intermediateIndex == 3){
                    if (convert() == EXIT_FAILURE){
                        return EXIT_FAILURE;
                    }
                    intermediateIndex = 0;
                }

                *(polybius_table + intermediateIndex) = 'x';
                intermediateIndex++;
                if (intermediateIndex == 3){
                    convert();
                    intermediateIndex = 0;
                }
            }
        }

        else if ((currentChar == '\t' && oldChar == '\t') || (currentChar == '\t' && oldChar == ' ')){
        }

        else if ((currentChar == ' ' && oldChar != '\t') && (currentChar == ' ' && oldChar != ' ')){
            // found space
            if (wordSpace == true){
                // if its a space, we put xx in the buffer
                *(polybius_table + intermediateIndex) = 'x';
                intermediateIndex++;

                // we have 3 chars in the buffer, so convert them to the alphabetical letter
                if (intermediateIndex == 3){
                    convert();
                    intermediateIndex = 0;
                }
                wordSpace = false;
            }

            else{
                // if its a space, we put xx in the buffer
                *(polybius_table + intermediateIndex) = 'x';
                intermediateIndex++;

                // we have 3 chars in the buffer, so convert them to the alphabetical letter
                if (intermediateIndex == 3){
                    convert();
                    intermediateIndex = 0;
                }

                *(polybius_table + intermediateIndex) = 'x';
                intermediateIndex++;
                if (intermediateIndex == 3){
                    convert();
                    intermediateIndex = 0;
                }
            }
        }

        else if ((currentChar == ' ' && oldChar == '\t') || (currentChar == ' ' && oldChar == ' ')){
        }

        else{
            // here, we need to get the morse translation of the character.
            // morse_table[0] = !
            // ! is 33 in decimal


            // following code gets length of each string in morse table. Use it wisely, future self
            //for (int i = 0; i < 89; i++){
            //    printf("Size of %i index of morse table is: %i\n", i, specialStrLen(*(morse_table + i)));
            //}
            //-------------------------------------------------------------------------------
            // check to see if the current character falls within the range 0x21 to 0x7A
            if (currentChar < 33 || currentChar > 122){
                return EXIT_FAILURE;
            }

            // so the character is in the morse table, but it might not have an encoding.
            // check to see if there is an encoding
            int indexInMorseTable = currentChar - 33; // in this case, if its !, it maps to element 0 in the morse table

            if (*(*(morse_table + indexInMorseTable)) == '\0'){
                return EXIT_FAILURE;
            }

            //printf("special str len is : %i\n", specialStrLen(*(morse_table + indexInMorseTable)));

            for (int i = 0; i < specialStrLen(*(morse_table + indexInMorseTable)); i++){
                // for each of the characters in this slot, copy it to the buffer
                // if its null, then just return exit failure tho

                // else, if its fine, add it to the polybius table
                *(polybius_table + intermediateIndex) = *(*(morse_table + indexInMorseTable) + i);
                intermediateIndex++;

                if (intermediateIndex == 3){
                    convert();
                    intermediateIndex = 0;
                }



                //printf("%c", *(*(morse_table + intermediateIndex) + i));
            }
            // after the character is added, we need to put an 'x' for space
            *(polybius_table + intermediateIndex) = 'x';
            intermediateIndex++;
            wordSpace = true;


            if (intermediateIndex == 3){
                convert();
                intermediateIndex = 0;
            }

            /*int sized = specialStrLen(*morse_table + 0);
            printf("size of morse table 1 = %i\n", sized);

            *polybius_table = **morse_table + 2;

            for (int i = 0; i < arraySize(polybius_table); i++){
            printf("table val: %c\n", *(polybius_table + i));
        }*/
        }
    }

    /*const char *test = *fractionated_table;
    printf("%c\n", *(test + 1));*/
    return EXIT_SUCCESS;
}

bool hasSpace= false;

int ourNewMethod(int indexer){
    bool toContinue = false;
        // after it has been found, we loop through polybius table.
        for (int i = 0; i < indexer; i++){
            // if polybius at i = 'x', and i++ != indexer
            // basically, if the x isn't the last character, then look through morse_table
            // for its representation and print out the character.
            // if it is the last character, we can't do anything. load the next char
            if ((*(polybius_table + i) == 'x') && (i != indexer - 1)){
                // make a letter out of the characters up to this current index
                int lengthOfMorse = i;
                //printf("length of morse: %i\n", lengthOfMorse);

                // for each string in morse_table, check if it equals our polybius table value
                for (int j = 0; j < 90; j++){

                    if (specialStrLen(*(morse_table + j)) == lengthOfMorse){
                        //printf("Matching lengths at: %i\n", j);

                        // if the lengths match, then we have a potential match. Look at all the characters and compare
                        bool match = true;
                        for (int find = 0; find < specialStrLen(*(morse_table + j)); find++){
                            if (*(*(morse_table + j) + find) != *(polybius_table + find)){
                                // if the cars dont match, set to false and break;
                                match = false;
                                break;
                            }
                        }

                        // if we made it through with a match, then print
                        if (match == true){
                            toContinue = true;

                            if (toContinue){

                            }

                            printf("%c", j + 33);


                            for (int start = 0; start < indexer; start++){
                                // for eahch of the elements in polybius table,
                                if (start + i <= indexer){
                                    //printf("\nReplacing %c with %c\n", *(polybius_table + start), *(polybius_table + start + i));
                                    *(polybius_table + start) = *(polybius_table + start + i);
                                    *(polybius_table + start + i) = 0; // set it to null after moving
                                }
                            }


                            indexer = indexer - i;


                            // after moving the array, check if first 2 chars are xx
                            if  (indexer >= 2){
                                if (*(polybius_table) == 'x' && *(polybius_table + 1) == 'x'){
                                    // 2x in a row = space
                                     hasSpace = true;

                                    for (int start = 0; start < indexer; start++){
                                        // for eahch of the elements in polybius table,
                                        if (start + 2 <= indexer){
                                            //printf("\nReplacing %c with %c\n", *(polybius_table + start), *(polybius_table + start + 2));
                                            *(polybius_table + start) = *(polybius_table + start + 2);
                                            *(polybius_table + start + 2) = 0; // set it to null after moving
                                        }
                                    }
                                    indexer = indexer - 2;
                                }

                                else{
                                    // else it means there is only 1 x, so shift left by 1 again
                                    for (int start = 0; start < indexer; start++){
                                        // for eahch of the elements in polybius table,
                                        if (start + 1 <= indexer){
                                            //printf("\nReplacing %c with %c\n", *(polybius_table + start), *(polybius_table + start + i));
                                            *(polybius_table + start) = *(polybius_table + start + 1);
                                            *(polybius_table + start + 1) = 0; // set it to null after moving
                                        }
                                    }
                                    indexer = indexer -1 ;
                                }
                            }
                            break;
                        }
                    }
                }
            }
        }
        return indexer;
}


int newLineMethod(int indexer){
    bool toContinue = false;
        // after it has been found, we loop through polybius table.
        for (int i = 0; i < indexer; i++){
            // if polybius at i = 'x', and i++ != indexer
            // basically, if the x isn't the last character, then look through morse_table
            // for its representation and print out the character.
            // if it is the last character, we can't do anything. load the next char
            if ((*(polybius_table + i) == 'x') && (i != indexer - 1)){
                // make a letter out of the characters up to this current index
                int lengthOfMorse = i;
                //printf("length of morse: %i\n", lengthOfMorse);

                // for each string in morse_table, check if it equals our polybius table value
                for (int j = 0; j < 90; j++){

                    if (specialStrLen(*(morse_table + j)) == lengthOfMorse){
                        //printf("Matching lengths at: %i\n", j);

                        // if the lengths match, then we have a potential match. Look at all the characters and compare
                        bool match = true;
                        for (int find = 0; find < specialStrLen(*(morse_table + j)); find++){
                            if (*(*(morse_table + j) + find) != *(polybius_table + find)){
                                // if the cars dont match, set to false and break;
                                match = false;
                                break;
                            }
                        }

                        // if we made it through with a match, then print
                        if (match == true){
                            toContinue = true;

                            if (toContinue){

                            }

                            printf("%c", j + 33);


                            for (int start = 0; start < indexer; start++){
                                // for eahch of the elements in polybius table,
                                if (start + i <= indexer){
                                    //printf("\nReplacing %c with %c\n", *(polybius_table + start), *(polybius_table + start + i));
                                    *(polybius_table + start) = *(polybius_table + start + i);
                                    *(polybius_table + start + i) = 0; // set it to null after moving
                                }
                            }


                            indexer = indexer - i;


                            // after moving the array, check if first 2 chars are xx
                            if  (indexer >= 2){

                                    // else it means there is only 1 x, so shift left by 1 again
                                    for (int start = 0; start < indexer; start++){
                                        // for eahch of the elements in polybius table,
                                        if (start + 1 <= indexer){
                                            //printf("\nReplacing %c with %c\n", *(polybius_table + start), *(polybius_table + start + i));
                                            *(polybius_table + start) = *(polybius_table + start + 1);
                                            *(polybius_table + start + 1) = 0; // set it to null after moving
                                        }
                                    }
                                    indexer = indexer -1 ;

                            }
                            break;
                        }
                    }
                }
            }
        }
        return indexer;
}


void fractionedDecryption(){
    fillFractionedTable();

    // table is filled.
    // set indexer to 0
    // if the previous character was 'x' and this character is 'x', print out a space
    // if previous was newline, print newline and clear buffer. set indexer to 0
    // take the character and convert to morse. store translation in polybius_table
    // if we encounter an 'x', take the buffer and get its character from morse_table
    // after getting the value, come back to this method and clear polybius table
    // after clearing polybius, set indexer back to 0
    // continue looping

    int indexer = 0;
    char currentChar = 0;

    while (true){
        currentChar = getchar();

        if (currentChar == EOF){
            break;
        }

        if (hasSpace){
            printf(" ");
            hasSpace = false;
        }

        if (currentChar == '\n'){
           if (*(polybius_table + indexer) == 'x'){
           }

            else{
                *(polybius_table + indexer) = 'x';
            }

            indexer ++;
            newLineMethod(indexer);
            indexer = 0;
            printf("\n");
            // clean out the buffer, just in case something is left
            continue;
        }

        // get the morse translation of the character
        for (int i = 0; i < arraySize(fm_key); i++){
            if (*(fm_key + i) == currentChar){

                // the character has been found in key. It has the same index
                // in fractionated table.
                // fractionated table will give a 3 character morse thing
                // copy the morse to polybius table
                // after copying, we can loop through and check for xx or x
                *(polybius_table + indexer) = *(*(fractionated_table + i));
                *(polybius_table + indexer + 1) = *(*(fractionated_table + i) + 1);
                *(polybius_table + indexer + 2) = *(*(fractionated_table + i) + 2);
                indexer += 3;

                //printf("Idexer: %i\n", indexer);

            /*printf("%c", *(polybius_table+ indexer - 3));
            printf("%c", *(polybius_table+ indexer - 2));
            printf("%c", *(polybius_table+ indexer - 1));*/
            }
        }

        indexer = ourNewMethod(indexer);
        //printf("\n");

    }
}
