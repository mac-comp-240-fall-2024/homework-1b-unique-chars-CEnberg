/*
 * hasUniqueChars.c
 * 
 * Contains functions that check if a string has invalid characters,
 * and if an inputted string contains only unique characters
 * 
 * Author: Christopher Enberg
 */

#include <stdio.h>  // fprintf, printf
#include <stdlib.h> // exit() defined here
#include <string.h> // useful string operations
#include <ctype.h>  //useful character operations
#include <stdbool.h>  // to define a boolean type and true, false
                      // see https://en.wikibooks.org/wiki/C_Programming/stdbool.h

#include "binary_convert.h"


/*
 * This function is for debugging by printing out the value
 * of an input insigned long as a binary string.
 */
void seeBits(unsigned long value, char *debug_text) {
  
  // string to represent binary value of variable value
  char *bin_str;

  bin_str = ulong_to_bin_str(value);
  printf("%s%s\n", debug_text, bin_str);
  free(bin_str);
  
}


/*
 * Given an input string of chars, check for any non-printing
 * characters and print an error and exit if the string has any.
 */
void checkInvalid(char * inputStr) {
  char nextChar;
  int i;
  
  for(i = 0; i < strlen(inputStr); i++) {
    nextChar = inputStr[i];

    // if nextChar is invalid (31 or less or 127 as an ascii char code), then bail out
    if ((nextChar <= 31 ) || (nextChar == 127)) {
      fprintf(stderr, "invalid character in string\n");
      exit(EXIT_FAILURE);
    }
  }
}


/* 
 * Given an input string of chars, checks if that string consists 
 * of only unique characters, and returns a bool indicating if that condition is met.
 * 
 * If the  input string contains invalid characters, this function will exit with failure 
 * and print an error message.
 */
bool hasUniqueChars(char * inputStr) {
  // bail out quickly if any invalid characters
  checkInvalid(inputStr);
  
  int i;   // loop counter
  
  // unsigned long can handle 64 different chars in a string
  // if a bit at a position is 1, then we have seen that character
  unsigned long checkBitsA_z = 0;   // for checking A through z and {|}~
  unsigned long checkBitsexcl_amp =0;  // for checking ! though @ 

  char nextChar;         // next character in string to check

  unsigned long nextCharBit = 1; //initialize to 1st position

  for(i = 0; i < strlen(inputStr); i++) {
    nextChar = inputStr[i];

    if (nextChar > 64) {  // nextChar must always between 32 and 126 inclusive due to checkInvalid
      nextCharBit = nextCharBit << (nextChar - 65); 

      if ((checkBitsA_z & nextCharBit) == nextCharBit) {
        // If a character has already been seen, then both nextCharBit and checkBitsA_z binary strings 
        // will contain a 1 at exactly one place: where the 1 is located in nextCharBit
        return false;
      }
      checkBitsA_z |= nextCharBit; // same as checkBitsA_z = checkBitsA_z | nextCharBit
    }
    else if (nextChar > 32) { // ignore spaces
      nextCharBit = nextCharBit << (nextChar - 33);

      if ((checkBitsexcl_amp & nextCharBit) == nextCharBit) {
        return false;
      }
      checkBitsexcl_amp |= nextCharBit; 
    }

    nextCharBit = 1; //reset char bit vector for next char
  }

  // if through all the characters, then no duplicates found
  return true;
  
}
