#include <stdio.h>
#include <cs50.h>
#include <math.h>

//this application is to check whether a credit card number is legit.
int main(void)
{
    long input;
    //long counterAmex = 0;
    //long counterVisa = 0;

    do
    {
        printf("Please entre your credit card number: ");
        input = get_long_long();

        //AMEX
        if (floor(log10(input)) + 1 == 15)
        {
            // to get the first digit, it should be power to 14 instead of 15.
            //long vs double vs int
            //long num = (input/pow(10, 14))%10;
            //printf("%li\n", num);
            //varify the input is a master card.
            //there isn't a '^' exponential operator in C.
            long counterMaster = 0;
            long num1 = pow(10, 14);
            long num2 = pow(10, 13);
            if (((input / num1) % 10 == 3) &&
                (((input / num2) % 10 == 4) ||
                 ((input / num2) % 10 == 7)))
            {
                //extract digits from the input
                for (long i = 1; i < 14; i += 2)
                {
                    //cannot write "long digit = (input/pow(factor))%10";
                    //it gives an operational error.
                    long factor = pow(10, i);
                    long digit = (input / factor) % 10;
                    long checkDigit = (digit) * 2;

                    //cannot log 0!!!
                    //long digitLength = floor(log10(checkDigit)) + 1;

                    if (checkDigit >= 10)
                    {
                        long multipDigit = checkDigit;
                        //be aware of scope - variables defined within function cannot be accessed from outside.
                        long digitLength = floor(log10(multipDigit)) + 1;
                        checkDigit = 0;

                        for (int i2 = 0; i2 < digitLength; i2++)
                        {
                            long factor2 = pow(10, i2);
                            long singleDigit = (multipDigit / factor2) % 10;
                            checkDigit = checkDigit + singleDigit;
                        }
                    }

                    counterMaster = counterMaster + checkDigit;
                }

                for (long i3 = 0; i3 <= 14; i3 += 2)
                {
                    long factor = pow(10, i3);
                    long digit = (input / factor) % 10;
                    counterMaster = counterMaster + digit;
                }

                if (counterMaster % 10 == 0)
                {
                    printf("AMEX\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
            //add adtion else logic here.
            //a series of numbers can be 15 digits long
            //yet the first digit can also be other numbers, instead of 34 or 37
            else
            {
                printf("INVALID\n");
            }
        }

        //VISA or MASTER
        else if (floor(log10(input)) + 1 == 16)
        {
            long counterMaster = 0;
            long num1 = pow(10, 15);
            long num2 = pow(10, 14);

            for (long i = 1; i < 16; i += 2)
            {
                long factor = pow(10, i);
                long digit = (input / factor) % 10;
                long checkDigit = (digit) * 2;

                if (checkDigit >= 10)
                {
                    long digitHolder = checkDigit;
                    long digitLength = floor(log10(digitHolder)) + 1;
                    checkDigit = 0;

                    for (int i2 = 0; i2 < digitLength; i2++)
                    {
                        long factor2 = pow(10, i2);
                        long singleDigit = (digitHolder / factor2) % 10;
                        checkDigit = checkDigit + singleDigit;
                    }
                }

                counterMaster = counterMaster + checkDigit;
            }

            for (long i3 = 0; i3 <= 15; i3 += 2)
            {
                long factor = pow(10, i3);
                long digit = (input / factor) % 10;
                counterMaster = counterMaster + digit;
            }

            if (counterMaster % 10 == 0)
            {
                if (((input / num1) % 10 == 4))
                {
                    printf("VISA\n");
                }
                else if (((input / num1) % 10 == 5) &&
                         (((input / num2) % 10 == 1) ||
                          ((input / num2) % 10 == 2) ||
                          ((input / num2) % 10 == 3) ||
                          ((input / num2) % 10 == 4) ||
                          ((input / num2) % 10 == 5)))
                {
                    printf("MASTERCARD\n");
                }
                //to exclude the series of numbers
                //that do not satisfy the above criteria.
                else
                {
                    printf("INVALID\n");
                }
            }
            else
            {
                printf("INVALID\n");
            }
        }

        //VISA
        else if (floor(log10(input)) + 1 == 13)
        {
            long counterMaster = 0;
            long num1 = pow(10, 12);
            if (((input / num1) % 10 == 4))
            {
                for (long i = 1; i < 13; i += 2)
                {
                    long factor = pow(10, i);
                    long digit = (input / factor) % 10;
                    long checkDigit = (digit) * 2;

                    if (checkDigit >= 10)
                    {
                        long multipDigit = checkDigit;
                        long digitLength = floor(log10(multipDigit)) + 1;
                        checkDigit = 0;

                        for (int i2 = 0; i2 < digitLength; i2++)
                        {
                            long factor2 = pow(10, i2);
                            long singleDigit = (multipDigit / factor2) % 10;
                            checkDigit = checkDigit + singleDigit;
                        }
                    }

                    counterMaster = counterMaster + checkDigit;
                }

                for (long i3 = 0; i3 <= 12; i3 += 2)
                {
                    long factor = pow(10, i3);
                    long digit = (input / factor) % 10;
                    counterMaster = counterMaster + digit;
                }

                if (counterMaster % 10 == 0)
                {
                    printf("VISA\n");
                }
                //double check here
                else
                {
                    printf("INVALID\n");
                }
            }
            //add adtion else logic here.
            //a series of numbers can be 13 digits long
            //yet the first digit can also be other numbers, instead of 4
            else
            {
                printf("INVALID\n");
            }
        }

        else
        {
            printf("INVALID\n");
        }
    }
    while (input <= 0);
};
