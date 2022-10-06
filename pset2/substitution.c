#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool only_digits(string key);
bool is_duplicate(string key);

int main(int argc, string argv[])
{
    string key = "";
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    if (argc == 2)
    {
        key = argv[1];
        if (strlen(key) < 26 || strlen(key) > 26)
        {
            printf("Key must contain 26 characters.");
            return 1;
        }
        else if (is_duplicate(key))
        {
            printf("Characters must be unique");
            return 1;
        }
    }
    else if (only_digits(key))
    {
        printf("Usage: ./substitution key");
        return 1;
    }
    else
    {
        printf("Usage: ./substitution key");
        return 1;
    }

    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");

    for (int i=0; i<strlen(plaintext); i++)
    {
        for(int j=0; j<strlen(alphabet); j++)
        {
            // compare the same ASCII value, uppercase or lowercase doesn’t matter for the cypher
            if(tolower(plaintext[i]) == tolower(alphabet[j]))
            {
                printf("%c", key[j]);
            }
        }
    }

    /*
    substitution/ $ ./substitution VCHPRZGJNTLSKFBDQWAXEUYMOI
    plaintext: hello
    ciphertext: JRSSB
*/

    printf("\n");
    return 0;
}

bool only_digits(string key)
{
    for (int i = 0, input_len = strlen(key); i < input_len; i++)
    {
        if (!isdigit(key[i]))
        {
            return false;
        }
    }
    return true;
}

bool is_duplicate(string key)
{
    int length = strlen(key);

    char current = key[0];
    for (int i = 0; i < length; i++)
    {
        current = key[i];
        for (int j = 0; j < length; j++)
        {
            if (i != j && current == key[j])
            {
                return true;
            }
        }
    }
    return false;
}
