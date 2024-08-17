#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n"); // ./recover card.raw
        return 1;
    }

    // open memory card
    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    // Create buffer - pointer to where to store the read data
    typedef uint8_t BYTE;
    BYTE buffer[BLOCK_SIZE];

    int filecount = 0;

    // Output file
    FILE *output = NULL;

    while (fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        // the start of a JPEG image
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xe0) == 0xe0)
        {
            if (filecount == 0)
            {
                char filename[8];
                sprintf(filename, "%03d.jpg", filecount);
                output = fopen(filename, "w");
                fwrite(buffer, 1, BLOCK_SIZE, output);
                filecount++;
            }
            else
            {
                fclose(output);
                char filename[8];
                sprintf(filename, "%03d.jpg", filecount);
                output = fopen(filename, "w");
                fwrite(buffer, 1, BLOCK_SIZE, output);
                filecount++;
            }
        }

        // If it's not the start of a new JPEG
        else if (filecount > 0)
        {
            // Keep writing to it because it's the next 512 bytes block of the current JPEG
            fwrite(buffer, 1, BLOCK_SIZE, output);
        }
    }
    fclose(file);
    fclose(output);
}

