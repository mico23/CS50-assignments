//this application is to check whether a credit card number is legit.
#include <stdio.h>
#include <cs50.h>
#include <math.h>

long get_number_length(long input);
//long find_digit (long input, long num);

int main(void)
{
    long input;

    do
    {
        printf("Please entre your credit card number: ");
        input = get_long_long();
    }
    while (input <= 0);
    //the codes below should not be in the do/while loop.

    //AMEX
    if (get_number_length(input) == 15)
    {
        // to get the first digit, it should be power to 14 instead of 15.
        //data type - long vs double vs int

        //there isn't a '^' exponential operator in C.
        long num1 = pow(10, 14); //a divisor to find the first digit
        long num2 = pow(10, 13); //a divisor to find the second digit

        //store the values in a variable to avoid extra calculation in the for loop.
        long verifier1 = (input / num1) % 10;
        long verifier2 = (input / num2) % 10;

        if ((verifier1 == 3) &&
            ((verifier2 == 4) ||
             (verifier2 == 7)))
        {
            long total_digit_counter = 0;

            //extract digits from the input
            for (long i = 1; i < 14; i += 2)
            {
                //cannot write "long digit = (input/pow(divisor))%10";
                //it gives an operational error.
                long divisor = pow(10, i);
                long digit = (input / divisor) % 10;
                long double_digit = (digit) * 2;

                //cannot log 0!!!
                //long digit_length = floor(log10(double_digit)) + 1;

                if (double_digit >= 10)
                {
                    long digit_holder = double_digit;
                    //be aware of scope - variables defined within function cannot be accessed from outside.
                    long digit_length = get_number_length(digit_holder);
                    double_digit = 0;

                    for (int i2 = 0; i2 < digit_length; i2++)
                    {
                        long divisor2 = pow(10, i2);
                        long single_digit = (digit_holder / divisor2) % 10;
                        double_digit = double_digit + single_digit;
                    }
                }

                total_digit_counter = total_digit_counter + double_digit;
            }

            for (long i3 = 0; i3 <= 14; i3 += 2)
            {
                long divisor = pow(10, i3);
                long digit = (input / divisor) % 10;
                total_digit_counter = total_digit_counter + digit;
            }

            if (total_digit_counter % 10 == 0)
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
    else if (get_number_length(input) == 16)
    {
        long total_digit_counter = 0;
        long num1 = pow(10, 15);
        long num2 = pow(10, 14);
        long verifier1 = (input / num1) % 10;
        long verifier2 = (input / num2) % 10;

        for (long i = 1; i < 16; i += 2)
        {
            long divisor = pow(10, i);
            long digit = (input / divisor) % 10;
            long double_digit = (digit) * 2;

            if (double_digit >= 10)
            {
                long digit_holder = double_digit;
                long digit_length = get_number_length(digit_holder);
                double_digit = 0;

                for (int i2 = 0; i2 < digit_length; i2++)
                {
                    long divisor2 = pow(10, i2);
                    long single_digit = (digit_holder / divisor2) % 10;
                    double_digit = double_digit + single_digit;
                }
            }

            total_digit_counter = total_digit_counter + double_digit;
        }

        for (long i3 = 0; i3 <= 15; i3 += 2)
        {
            long divisor = pow(10, i3);
            long digit = (input / divisor) % 10;
            total_digit_counter = total_digit_counter + digit;
        }

        if (total_digit_counter % 10 == 0)
        {
            if (verifier1 == 4)
            {
                printf("VISA\n");
            }
            else if ((verifier1 == 5) &&
                     ((verifier2 == 1) ||
                      (verifier2 == 2) ||
                      (verifier2 == 3) ||
                      (verifier2 == 4) ||
                      (verifier2 == 5)))
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
    else if (get_number_length(input) == 13)
    {

        long num1 = pow(10, 12);
        long verifier1 = (input / num1) % 10;

        if (verifier1 == 4)
        {
            long total_digit_counter = 0;

            for (long i = 1; i < 13; i += 2)
            {
                long divisor = pow(10, i);
                long digit = (input / divisor) % 10;
                long double_digit = (digit) * 2;

                if (double_digit >= 10)
                {
                    long digit_holder = double_digit;
                    long digit_length = floor(log10(digit_holder)) + 1;
                    double_digit = 0;

                    for (int i2 = 0; i2 < digit_length; i2++)
                    {
                        long divisor2 = pow(10, i2);
                        long single_digit = (digit_holder / divisor2) % 10;
                        double_digit = double_digit + single_digit;
                    }
                }

                total_digit_counter = total_digit_counter + double_digit;
            }

            for (long i3 = 0; i3 <= 12; i3 += 2)
            {
                long divisor = pow(10, i3);
                long digit = (input / divisor) % 10;
                total_digit_counter = total_digit_counter + digit;
            }

            if (total_digit_counter % 10 == 0)
            {
                printf("VISA\n");
            }
            
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
};

//a function to identify the length of the input.
long get_number_length(long input)
{
    return floor(log10(input)) + 1;
};
