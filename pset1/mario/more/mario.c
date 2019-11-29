#include <stdio.h>
#include <cs50.h>
#define MAX_HEIGHT 23

//"more" program

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
            for (int j = height - i; j > 1; j--)
            {
                printf(" ");
            };

            for (int k = 0; k < 1 + i; k++)
            {
                printf("#");
            };

            printf("  ");

            for (int k = 0; k < 1 + i; k++)
            {
                printf("#");
            };

            printf("\n");
        };
    }
}
