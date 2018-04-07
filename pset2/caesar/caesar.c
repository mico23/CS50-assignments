//this application is to encrypt messages
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>
#define SIZE 26

int main (int argc, string argv[])
{
    if (argc == 2 && atoi(argv[1]) >= 0)
    {
        //get the key from user entred
        //double check what will return if the value passed by is not a string
        //make sure the size of the key is ok
        //actually 'atoi' is a hint in the video!!!
        int screct_key = atoi(argv[1]);

        string user_input = get_string("plaintext: ");
        string encrypted_message = user_input;
        //change char by setting user_input[i] = something

        for (int i = 0, n = strlen(user_input); i < n; i ++)
        {
            int char_holder = user_input[i];

            if (isalpha(char_holder))
            {
                if (isupper(char_holder))
                {
                    int char_converter = (char_holder - 'A' + screct_key) % SIZE;
                    int encrypted_char = char_converter + 'A';
                    encrypted_message[i] = toupper(encrypted_char);
                }

                else
                {
                    int char_converter = (char_holder - 'a' + screct_key) % SIZE;
                    int encrypted_char = char_converter + 'a';
                    encrypted_message[i] = tolower(encrypted_char);
                }
            }
            /* else
            {

            } */

        }

        printf("ciphertext: %s\n", encrypted_message);

        return 0;

    }

    else
    {
        printf("Error!\n");
        printf("Usage: ./caesar k\n");
        return 1;
    }
}
