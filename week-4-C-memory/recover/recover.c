#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFERSIZE 512

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage ./recover FILE\n");
        return 1;
    }
    // Open the memory card
    FILE *card = fopen(argv[1], "r");
    if (!card)
    {
        perror("Error\n");
        return 1;
    }

    // buffer of data block for memory card 512FAT fornat
    uint8_t buffer[BUFFERSIZE];
    int count = 0; 
    char filename[16];
    FILE *img = NULL;

    while (fread(buffer, 1, BUFFERSIZE, card) == BUFFERSIZE)
    {
        // if start of new jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //if it's first jpeg
            if (count == 0)
            { 
                sprintf(filename, "%03i.jpg", count);
                count++;
                img = fopen(filename, "w");
                if (!img)
                {
                    perror("Error");
                    return 2;
                }
                fwrite(buffer, 1, BUFFERSIZE, img);
            }
            else // its the end of the previous onne and start of the next one. 
            {
                if (img != NULL)
                {
                    fclose(img);
                }
                sprintf(filename,  "%03i.jpg", count);
                count++;
                img = fopen(filename, "w");
                if (!img)
                {
                    perror("Error");
                    return 2;
                }
                fwrite(buffer, 1, BUFFERSIZE, img);
            
            }
        }
        else 
        {
            if (img != NULL)
            {
                fwrite(buffer, 1, BUFFERSIZE, img);
            }
        }
    }
    if (img != NULL)
    {
        fclose(img);
    }
    fclose(card);
}