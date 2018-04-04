#include <stdio.h>
#include <cs50.h>

//"less" progarm

int main(void) {
    float count = 0.0;
    //note it's 'float'; not 'int'.
    //need to inintialize a number variable.
    float quarter = 0.25;
    float dime = 0.10;
    float nickel = 0.05;
    float pennie = 0.01;
    float input;

    do {
        printf("Please entre your number: ");
        input = get_float();
        //note it's 'float'; not 'int'.

        //check quater
        do {
            if (input - quarter > 0)
            {
                input = input - quarter;
                count++;
            }
        }
        while (input - quarter > 0);
        // the codes above can be better;

        //check dime
        do {
            if (input - dime > 0)
            {
                input = input - dime;
                count++;
            }
        }
        while (input - dime > 0);

        //check nickel
        do {
            if (input - nickel > 0)
            {
                input = input - nickel;
                count++;
            }
        }
        while (input - nickel > 0);

        //check pennie
        do {
            if (input - pennie > 0)
            {
                input = input - pennie;
                count++;
            }
        }
        while (input - pennie > 0);

        // return count;
        //setting the return before printf
        //cuases the function won't print 'count'
        //investigate more about how to use 'return'
        printf("%.3f", count);
        //be aware of the syntax.
        //cannot directly print varibales.
    }
    while (input < 0);
}

//**************************************************
//LEARN more how float numer is calculated***

int main(void) {
    int count = 0;
    //note it's 'float'; not 'int'.
    //need to inintialize a number variable.
    float quarter = 25;
    //instead of 0.25
    //must input * 100; convert the input to cents
    float dime = 10;
    float nickel = 5;
    float pennie = 1;
    float input;

    do {
        printf("Please entre your number: ");
        input = get_float();
        //note it's 'float'; not 'int'.

        //need to convert the dollar to cents***
        //LEARN more how float numer is calculated***
        input = input * 100;

        //check quater
        while (input >= quarter)
        {
            input = input - quarter;
            count++;
        };
        printf("step1 dollars: %.3f\n", input);
        printf("step1 coins: %i\n", count);

        //check dime
        while (input >= dime)
        {
            input = input - dime;
            count++;
        };

        printf("step2 dollars: %.3f\n", input);
        printf("step2 coins: %i\n", count);

        //check nickel
        while (input >= nickel)
        {
          input = input - nickel;
          count++;
        };
        printf("step3 dollars: %.3f\n", input);
        printf("step3 coins: %i\n", count);

        //check pennie
        while (input >= pennie)
        {
          input = input - pennie;
          count++;
        };
        printf("step4 dollars: %.3f\n", input);
        printf("step4 coins: %i\n", count);


    }
    while (input < 0);

    printf("%i\n", count);
    //be aware of the syntax.
    //cannot directly print varibales.
}
