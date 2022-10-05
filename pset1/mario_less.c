#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Positive number: ");
    }
    while (height <= 0 || height > 8);

    int block = 1;

    for (int i = 0; i < height; i++)
    {
        for (int space = 0; space < height - block; space++)
        {
            printf(" ");
        }
        for (int j = 0; j < block; j++)
        {
            printf("#");
        }
        block++;
        printf("\n");
    }
}