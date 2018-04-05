#include <stdio.h>
#include <cs50.h>
#include <math.h>
#define QUARTER 25 //instead of 0.25; input * 100 (see below)
#define DIME 10
#define NICKEL 5
#define PENNIE 1

//cash application

int main(void) {
    int count = 0;
    //note it's 'float'; not 'int'.
    //must input * 100; convert the input to cents
    float input;

    do {
        printf("Please entre your number: ");
        input = get_float();
        //note it's 'float'; not 'int'.

        //need to convert the dollar to cents***
        //LEARN more how float numer is calculated***
        //round up the number 419.999... to 420
        input = round(input * 100);

        //check quater
        while (input >= QUARTER)
        {
            input = input - QUARTER;
            count++;
        };
        //eprintf("step1 dollars: %.3f\n", input);
        //eprintf("step1 coins: %i\n", count);

        //check dime
        while (input >= DIME)
        {
            input = input - DIME;
            count++;
        };

        //eprintf("step2 dollars: %.3f\n", input);
        //eprintf("step2 coins: %i\n", count);

        //check nickel
        while (input >= NICKEL)
        {
          input = input - NICKEL;
          count++;
        };
        //eprintf("step3 dollars: %.3f\n", input);
        //eprintf("step3 coins: %i\n", count);

        //check pennie
        while (input >= PENNIE)
        {
          input = input - PENNIE;
          count++;
        };
        //eprintf("step4 dollars: %.3f\n", input);
        //eprintf("step4 coins: %i\n", count);


    }
    while (input < 0);

    printf("%i\n", count);
    //be aware of the syntax.
    //cannot directly print varibales.
}
