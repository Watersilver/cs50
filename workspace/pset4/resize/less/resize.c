// Resizes bmp by int factor resizeFactor

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize resizeFactor infile outfile\nresizeFactor is integer in (0, 100]\n");
        return 1;
    }

    // Store resize factor
    int resizeFactor = atoi(argv[1]);

    // Ensure resizeFactor has legal values
    if (resizeFactor <= 0 || resizeFactor > 100)
    {
        fprintf(stderr, "Usage: ./resize resizeFactor infile outfile\nresizeFactor is integer in (0, 100]\n");
        return 1;
    }

    // Store infile and outfile
    char *infile = argv[2];
    char *outfile = argv[3];

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

    // Determine padding of scanlines of infile
    int inPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Determine padding of scanlines of outfile
    int outPadding = (4 - (resizeFactor * bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Remember infile's width for iteration through its scanlines
    LONG inWidth = bi.biWidth;

    // Change BITMAPINFOHEADER appropriately for resized file
    bi.biWidth *= resizeFactor;
    bi.biHeight *= resizeFactor;
    bi.biSizeImage = (sizeof(RGBTRIPLE) * bi.biWidth + outPadding) * abs(bi.biHeight);

    // Change BITMAPFILEHEADER appropriately for resized file
    bf.bfSize = sizeof bf + sizeof bi + bi.biSizeImage;

    // Write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof bf, 1, outptr);

    // Write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof bi, 1, outptr);

    // Iterate over outfile's number of scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // Iterate over infile's number of pixels in single scanline
        for (int j = 0; j < inWidth; j++)
        {
            // Buffer to hold and change pixel
            RGBTRIPLE triple;

            // Read pixel from infile
            fread(&triple, sizeof triple, 1, inptr);

            // Write pixel to outfile
            for (int k = 0; k < resizeFactor; k++)
            {
                fwrite(&triple, sizeof triple, 1, outptr);
            }
        }

        // Check if we need to go through scanline again. If yes go back to start of scanline. If not skip padding.
        if (i % resizeFactor == resizeFactor - 1)
        {
            // Skip over padding of infile, if any
            fseek(inptr, inPadding, SEEK_CUR);
        }
        else
        {
            // Go back to beginning of scanline
            fseek(inptr, -inWidth * sizeof(RGBTRIPLE), SEEK_CUR);
        }

        // Add padding to outfile as necessary
        for (int j = 0; j < outPadding; j++)
        {
            fputc(0x00, outptr);
        }
    }

    fclose(inptr);
    fclose(outptr);
    printf("Done!\n");
}