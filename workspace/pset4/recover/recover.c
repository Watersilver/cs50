// Recovers JPEGS from inputed file

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int recover_photo(FILE *fptr);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover file\n");
        return 1;
    }

    // Open input file for reading
    FILE *raw = fopen(argv[1], "r");
    if (!raw)
    {
        fprintf(stderr, "Could not open file\n");
        return 2;
    }

    // Will store which JPEG we are currently writting on
    int jpegNumber = 0;

    // Will store pointer to output files
    FILE *jpg = NULL;

    // Will store a block of read data
    BYTE *block = malloc(512);

    // Go through inputed file until its end
    while (fread(block, 1, 512, raw) == 512)
    {
        // Check if encountered something that looks like JPEG signature
        if (block[0] == 0xff &&
            block[1] == 0xd8 &&
            block[2] == 0xff &&
            (block[3] & 0xf0) == 0xe0)
        {
            // Close previous JPEG if exists. Photo recovered
            if (jpg)
            {
                fclose(jpg);
            }

            // Name and open next JPEG
            char filename[8];
            sprintf(filename, "%03i.jpg", jpegNumber);
            jpg = fopen(filename, "w");
            if (!jpg)
            {
                fprintf(stderr, "Could not make outfile\n");
                return 3;
            }

            // Prepare jpegNumber for next file
            jpegNumber += 1;
        }

        // Write to jpg file if we've encountered at least one signature
        if (jpg)
        {
            fwrite(block, 1, 512, jpg);
        }
    }

    free(block);
    fclose(jpg);
    fclose(raw);
    printf("Done! Number of JPEGs = %03i\n", jpegNumber);
}