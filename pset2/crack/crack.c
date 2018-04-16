//this application is to decrypt messages
//brute force
//the codes are to exhaust all possible combination of a-z and A-Z characters
//for a 5 digits long password.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>
#define _XOPEN_SOURCE       /* See feature_test_macros(7) */
#include <unistd.h>
#define PW_SIZE 6
#define WORDS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"

char *crypt(const char *key, const char *salt);

int main(int argc, string argv[])
{
    string arg_holder = argv[1];
    int words_size = strlen(WORDS);
    //eprintf("%i\n", words_size);

    char cracked_password[PW_SIZE];
    string hashed_password;

    if (argc == 2)
    {
        char salt_holder[2] = {arg_holder[0], arg_holder[1]};

        //searching for a-z char;
        for (int i = 0; i < words_size; i ++)
        {
            cracked_password[0] = WORDS[i];
            cracked_password[1] = '\0';
            //eprintf("the tested char: %s\n", cracked_password);
            hashed_password = crypt(cracked_password, salt_holder);
            //eprintf("the hashed data: %s\n", hashed_password);

            if (strcmp(hashed_password, arg_holder) == 0)
            {
                //use break here; it does not end the outside for loop.
                //use 'goto' instead.
                goto result;
            }
        }

        //searching for a/A_-z/Z_  char;
        for (int i = 0; i < words_size; i ++)
        {
            cracked_password[0] = WORDS[i];

            for (int i2 = 0; i2 < words_size; i2 ++)
            {
                cracked_password[1] = WORDS[i2];
                cracked_password[2] = '\0';
                hashed_password = crypt(cracked_password, salt_holder);

                if (strcmp(hashed_password, arg_holder) == 0)
                {
                    goto result;
                }
            }
        }

        //searching for a/A__-z/Z__  char;
        for (int i = 0; i < words_size; i ++)
        {
            cracked_password[0] = WORDS[i];

            for (int i2 = 0; i2 < words_size; i2 ++)
            {
                cracked_password[1] = WORDS[i2];

                for (int i3 = 0; i3 < words_size; i3 ++)
                {
                    cracked_password[2] = WORDS[i3];
                    cracked_password[3] = '\0';
                    hashed_password = crypt(cracked_password, salt_holder);

                    if (strcmp(hashed_password, arg_holder) == 0)
                    {
                        goto result;
                    }
                }
            }
        }

        //searching for a/A___-z/Z___  char;
        for (int i = 0; i < words_size; i ++)
        {
            cracked_password[0] = WORDS[i];

            for (int i2 = 0; i2 < words_size; i2 ++)
            {
                cracked_password[1] = WORDS[i2];

                for (int i3 = 0; i3 < words_size; i3 ++)
                {
                    cracked_password[2] = WORDS[i3];

                    for (int i4 = 0; i4 < words_size; i4 ++)
                    {
                        cracked_password[3] = WORDS[i4];
                        cracked_password[4] = '\0';
                        hashed_password = crypt(cracked_password, salt_holder);

                        if (strcmp(hashed_password, arg_holder) == 0)
                        {
                            goto result;
                        }
                    }
                }
            }
        }

        //searching for a/A____-z/Z____  char;
        for (int i = 0; i < words_size; i ++)
        {
            cracked_password[0] = WORDS[i];

            for (int i2 = 0; i2 < words_size; i2 ++)
            {
                cracked_password[1] = WORDS[i2];

                for (int i3 = 0; i3 < words_size; i3 ++)
                {
                    cracked_password[2] = WORDS[i3];

                    for (int i4 = 0; i4 < words_size; i4 ++)
                    {
                        cracked_password[3] = WORDS[i4];

                        for (int i5 = 0; i5 < words_size; i5 ++)
                        {
                            cracked_password[4] = WORDS[i5];
                            cracked_password[5] = '\0';
                            hashed_password = crypt(cracked_password, salt_holder);

                            if (strcmp(hashed_password, arg_holder) == 0)
                            {
                                goto result;
                            }
                        }
                    }
                }
            }
        }

        if (strcmp(hashed_password, arg_holder) != 0)
        {
            printf("The password is not found.\n");
        }
        else
        {
            result: printf("password: %s\n", cracked_password);
        }

        return 0;
    }

    else
    {
        printf("Error!\n");
        printf("Usage: ./caesar hash\n");
        return 1;
    }
}
