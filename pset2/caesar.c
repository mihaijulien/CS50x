#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

bool only_digits(string input);

int main(int argc, string argv[])
{
    int key = 0;
    string input = "";

    if (argc == 2)
    {
        input = argv[1];
        if (!only_digits(input))
        {
            printf("Usage: ./caesar key");
            return 1;
        }
        key = atoi(argv[1]);
    }
    else
    {
        printf("Usage: ./caesar key");
        return 1;
    }

    string plaintext = get_string("plaintext: ");

    printf("plaintext: %s\n", plaintext);
    printf("cyphertext: ");

    for (int i=0; i < strlen(plaintext); i++)
    {
        // only rotate alphabetical characters
        if(isalpha(plaintext[i]))
        {
            if (isupper(plaintext[i]))
            {
                printf("%c",65 + ((plaintext[i] % 65) + key) % 26);
            }
             else if (islower(plaintext[i]))
            {
                printf("%c", 97 + ((plaintext[i] % 97) + key) % 26);
            }
        }
        else
        {
            printf("%c",plaintext[i]);
        }
    }
    printf("\n");
}

bool only_digits(string input)
{
    for (int i = 0, input_len = strlen(input); i < input_len; i++)
    {
        if (!isdigit(input[i]))
        {
            return false;
        }
    }
    return true;
}
