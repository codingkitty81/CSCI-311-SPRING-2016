/*
 * @file hash_function.cpp  Calculates the value of a string for a hash table.
 *
 * @author Katherine Jouzapaitis
 * @date 3/30/2016
 *
 * Resources:
 * https://www.daniweb.com/programming/software-development/threads/231987/string-hash-function
 * https://www.strchr.com/hash_functions
 *
 * After reading Cormen's chapter on Hash functions, and looking at a hash
 * function comparison chart. I decided to go with the Multiplicative Hash
 * Function approach. Though it isn't the best, it doesn't require additional
 * header files to be loaded into the program, like the FNV hash does. It
 * also tends to put the output in order when the last letter is the next
 * one in the alphabet, which to me makes since. I found the function on
 * daniweb and played with the number that the hashVal is multiplied by. By
 * the recommendation of a comment I tried 33, and it produced shorter lists
 * than the initial 37. I left out the test of whether the hashVal is less
 * than 0, since all characters have a positive value and we are working with
 * such short strings, overflow is highly unlikely.
 */

#include "hash.h"
#include <string>

int Hash::hf(string word) {
    int hashVal = 0;
    for(unsigned int i = 0; i < word.length(); i++) {
        hashVal = 33 * hashVal + word[i];
        hashVal %= HASH_TABLE_SIZE;
    }
    return hashVal;
}