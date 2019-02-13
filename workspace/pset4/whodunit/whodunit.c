// Finds whodunit!

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        fprintf(stderr, "Usage: ./whodunit infile outfile\n");
        return 1;
    }

    // Make my life easier
    char *infile = argv[1];
    char *outfile = argv[2];

    // Open input file
    FILE *inptr = fopen(infile, "r");
    if (!inptr)
    {
        fprintf(stderr, "Could not open %s for reading\n", infile);
        return 2;
    }

    // Open output file
    FILE *outptr = fopen(outfile, "w");
    if (!outptr)
    {
        fclose(inptr);
        fprintf(stderr, "Could not open %s for writing\n", outfile);
        return 3;
    }

    // Read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof bf, 1, inptr);

    // Read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof bi, 1, inptr);

    // Check if format looks right
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 ||
        bi.biSize != 40 || bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(inptr);
        fclose(outptr);
        fprintf(stderr, "Unsupported file format\n");
        return 4;
    }

    // Write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof bf, 1, outptr);

    // Write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof bi, 1, outptr);

    // Determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // Iterate over infile's pixels in single scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // Buffer to hold and change pixel
            RGBTRIPLE triple;

            // Read pixel from infile
            fread(&triple, sizeof triple, 1, inptr);

            // Change pixels to find hidden image
            // If pixel has same amount of all colours (approaches or is white), make it red
            if (triple.rgbtRed == triple.rgbtBlue && triple.rgbtRed == triple.rgbtGreen)
            {
                triple.rgbtRed = 0xff;
                triple.rgbtBlue = 0x00;
                triple.rgbtGreen = 0x00;
            }

            // Write pixel to outfile
            fwrite(&triple, sizeof triple, 1, outptr);
        }

        for (int k = 0; k < padding; k++)
        {
            BYTE padByte;
            fread(&padByte, 1, 1, inptr);
            fwrite(&padByte, 1, 1, outptr);
        }
    }

    fclose(inptr);
    fclose(outptr);
    printf("Done!\n");
}