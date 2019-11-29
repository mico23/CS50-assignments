//this application is to encrypt messages
//Vigenere
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>
#define SIZE 26

bool varify_no_symbol(string input);

int main(int argc, string argv[])
{
    string arg_holder = argv[1];
    //cannot pass a string to isalpha().

    //to varify user input
    if (argc == 2 &&
        (atoi(arg_holder) > 0 ||
         varify_no_symbol(arg_holder)))
    {
        int arg_length = strlen(arg_holder);
        int screct_key_controler = 0;

        string user_input = get_string("plaintext: ");
        string encrypted_message = user_input;

        for (int i = 0, n = strlen(user_input); i < n; i ++)
        {
            //when the i th char in the message is not an alphabet,
            //we need to preserve the j char in the key
            //for the next alphabet in the message!

            //the logoic here can be written in a different way.
            //set index = 0; when isalpha == true; index ++; index mod key_length
            int secrect_index = (i - screct_key_controler) % arg_length;
            int secrect_char = arg_holder[secrect_index];
            int secret_key;

            int char_holder = user_input[i];

            //to check whether the char in the message is an alphabet
            if (isalpha(char_holder))
            {
                //to check whehter the char in the key is upper case or lower case.
                if (isupper(secrect_char))
                {
                    secret_key = secrect_char - 'A';
                }

                else
                {
                    secret_key = secrect_char - 'a';
                }

                //to encrypt the char in the message
                if (isupper(char_holder))
                {
                    int char_converter = (char_holder - 'A' + secret_key) % SIZE; //double check this line
                    int encrypted_char = char_converter + 'A';
                    encrypted_message[i] = toupper(encrypted_char);
                }

                else
                {
                    int char_converter = (char_holder - 'a' + secret_key) % SIZE;
                    int encrypted_char = char_converter + 'a';
                    encrypted_message[i] = tolower(encrypted_char);
                }
            }

            //to offset the secret key index by one
            //when the char is a symbol.
            else
            {
                screct_key_controler ++;
            }

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

bool varify_no_symbol(string input)
{
    //need to set 'checker' to be 'true' first.
    bool checker = true;

    for (int i = 0, len = strlen(input); i < len; i ++)
    {
        if (!isalpha(input[i]))
        {
            checker = false;
        }
    }

    return checker;
};
