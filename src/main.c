#include "hw1.h"
#include "debug.h"

#ifdef _STRING_H
#error "Do not #include <string.h>. You will get a ZERO."
#endif

#ifdef _STRINGS_H
#error "Do not #include <strings.h>. You will get a ZERO."
#endif

#ifdef _CTYPE_H
#error "Do not #include <ctype.h>. You will get a ZERO."
#endif


int main(int argc, char **argv)
{
    unsigned short mode;

    mode = validargs(argc, argv);

    if (mode == 0){
        USAGE(*argv, EXIT_FAILURE);
    }

    else if (mode == 0x8000){
        USAGE(*argv, EXIT_SUCCESS);
    }

    else{
        // here we run the cipher according to the mode that was returned
        // first, copy the mode since it will be changed around
        unsigned short encrptionType = mode;

        encrptionType = encrptionType << 1;
        encrptionType = encrptionType >> 15;\

        unsigned short encOrDec = mode;
        encOrDec = encOrDec << 2;
        encOrDec = encOrDec >> 15;

        // now get rows and cols
        unsigned short rows = mode;
        rows = rows & 0x00F0;
        rows = rows >> 4;

        unsigned short cols = mode;
        cols = cols & 0x000F;


        // modecopy is currently the type of encryption
        if (encrptionType == 0){
            // if its 0, then polybius
            if (encOrDec == 0){
                // we need to encrypt
                if(polybiusEncryption(rows, cols) == EXIT_FAILURE){
                    return EXIT_FAILURE;
                }
            }
            else{
                // decrypt
                polybiusDecryption(rows, cols);
            }

        }

        else {
            // encryption mode was 1, which means fractioned cipher
            // if 0, then do encryption
            if (encOrDec == 0){
                // need to encrypt
                if (fractionedEncryption() == EXIT_FAILURE){
                    return EXIT_FAILURE;
                }
            }
            else{
                // decrypt
                fractionedDecryption();
            }

        }

    }
    /*debug("Mode: 0x%X", mode);

    if(mode & 0x8000) {
        USAGE(*argv, EXIT_SUCCESS);
    }*/

    return EXIT_SUCCESS;
}

/*
 * Just a reminder: All non-main functions should
 * be in another file not named main.c
 */