#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
int main (void)
{
    string input = get_string("Please enter your fraction: ");

    printf("%c\n", input[0]);

    string first = strtok(input, "#");
    printf("%s\n", first);

    string second = strtok(NULL, "#");
    printf("%s\n", second);


    int to_int = atoi(input);

    printf("%i\n", to_int);
}
