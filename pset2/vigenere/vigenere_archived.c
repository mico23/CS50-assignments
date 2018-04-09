//this application is to encrypt messages
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>
#define SIZE 26

bool varify_user_input(string input);

int main (int argc, string argv[])
{
    string arg_holder = argv[1];
    eprintf("%d\n", varify_user_input(arg_holder));
    /* eprintf("%i\n", argc);
    eprintf("%i\n", atoi(arg_holder));
    eprintf("%d\n", isalpha(arg_holder)); */

    //cannot pass a string to isalpha().

    if (argc == 2 &&
        (atoi(arg_holder) > 0 ||
            varify_user_input(arg_holder)))
    {

        int screct_key = atoi(argv[1]);

        string user_input = get_string("plaintext: ");
        string encrypted_message = user_input;

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
};

bool varify_user_input(string input)
{
    //need to set 'checker' to be 'true' first.
    bool checker = true;

    for (int i = 0, len = strlen(input); i < len; i ++ )
    {
        if(!isalpha(input[i]))
        {
            checker = false;
        }
    }

    return checker;
};
