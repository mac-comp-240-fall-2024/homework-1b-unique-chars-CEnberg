/*
 * Tests the hasUniqueChars function from hasUniqueChars.c 
 */

#include <stdio.h>    // printf
#include <stdbool.h>  // to define a boolean type and true, false
#include <string.h>   // strcpy  to copy a string
#include <assert.h>


// declaration of function from hasUniqueChars.c
bool hasUniqueChars(char * inputStr);


int main() {

  // ------------------------------------------------------------
  // Examples of declaring string constants
  /* Example 1 */
  char string1[] = "A string declared as an array.\n";

  /* Example 2 */
  char *string2 = "A string declared as a pointer.\n";

  /* Example 3 */
  char string3[128];   // can copy in up to 127 characters
                       // chose 128 because it is a multiple of 8 bytes
  strcpy(string3, "A string constant copied in.\n");

  // You can uncomment these to see how the strings were initialized above.
  // Then you can comment these out again once you see that the 
  // strings were created correctly
  // printf ("%s", string1);
  // printf ("%s", string2);
  // printf ("%s", string3);

  // -------------------------------------------------------------
  // Thorough and exhaustive tests of hasUniqueChars()  
  bool ok;    // holds the result of hasUniqueChars(); used in asserts
  
  // Test 1: a test case that should return false because characters are duplicated
  strcpy(string3, "This should fail (l and s and i and h)");
  ok = hasUniqueChars(string3);
  assert(!(ok));
  
  // Test 2: This should be true and not fail, but won't work until you
  // complete the hasUniqueChars() function
  strcpy(string3, "abcdefghij");
  ok = hasUniqueChars(string3);
  assert(ok);
  
  // Test 3: Check that spaces don't affect unique character count
  strcpy(string3, "o  k a            y");
  ok = hasUniqueChars(string3);
  assert(ok);

  // Test 4: All possible chars with values 65-126 work as expected (A to ~)
  strcpy(string3, "ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~");
  ok = hasUniqueChars(string3);
  assert(ok);

  // Test 5-1: overlapping chars within values 65-126 works
  strcpy(string3, "The quick brown fox jumps over the lazy dog");
  ok = hasUniqueChars(string3);
  assert (!ok);

  // Test 5-2: overlapping chars within values 65-126 works
  strcpy(string3, "def main(){ int[] X = [Tau, perc, 23]; }");
  ok = hasUniqueChars(string3);
  assert (!ok);

  // Test 6: All possible chars with values 33-64 work as expected (! to @)
  strcpy(string3, "!\"#$\%^&\'()*+-./0123456789:;<=>?@");
  ok = hasUniqueChars(string3);
  assert(ok);

  // Test 7-1: Duplicate chars with values 33-64
  strcpy(string3, "(3 * 584) - 12 != 467 // 9");
  ok = hasUniqueChars(string3);
  assert(!ok);

  // Test 7-2: Duplicate chars with values 33-64
  strcpy(string3, "(!@#$\%^&*)@macalester.edu");
  ok = hasUniqueChars(string3);
  assert(!ok);

  // Test 8: Chars with equivalent indices shouldn't affect each other's count 
  strcpy(string3, "A!B\"C#D$E\%F&G\'H(I)J*K+L,M-N.O/P0Q1R2S3T4U5V6W7X8Y9Z:[;\\<]=^>_?`@");
  ok = hasUniqueChars(string3);
  assert(ok);

  //Test 9: An empty string should return true, as every character in it is unique 
  strcpy(string3, "");
  ok = hasUniqueChars(string3);
  assert(ok);


  printf("Passed all current tests\n");
  // NOTE: if you add a \n to any tests, this should cause the
  //       exit failure given. Keep this test last so you can check 
  //       that others pass or fail as you expect them to.
  strcpy(string3, "a b cc\n");
  ok = hasUniqueChars(string3);
  // other examples that should fail that you can place in strings
  // are \0 or \t or \r
  // See problem description for more details about escape sequences
  
  return 0;
}