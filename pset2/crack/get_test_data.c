//this application is to encrypt messages - Caesar
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>
#define _XOPEN_SOURCE       /* See feature_test_macros(7) */
#include <unistd.h>

char *crypt(const char *key, const char *salt);

int main (void)
{
    string input = get_string ("Please enter something here: ");
    string salt = get_string ("Please enter your salt: ");
    string hashed_input = crypt(input, salt);

    printf("Output %s\n", hashed_input);
}
