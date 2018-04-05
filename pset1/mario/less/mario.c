#include <stdio.h>
#include <cs50.h>
#define MAX_HEIGHT 23

//"less" program

int main(void)
{
    int height;
    do
    {
        printf("Please enter the height: ");
        height = get_int();
    }

    while (height < 0 || height > MAX_HEIGHT);

    if (height >= 0 && height <= MAX_HEIGHT)
    {
        for (int i = 0; i < height; i++)
        {
            //instead of (int j = heightight -1 ; j > 0; j--)
            //should take the advantage of i
            //after every loop, the value of height in the subloop is unchanged
            //thus, it prints the same spaces everytime.
            for (int j = height - i; j > 1; j--)
            {
                printf(" ");
            };
            for (int k = 0; k < 2 + i; k++)
            {
                printf("#");
            };

            printf("\n");
        };
    }
}
