// Resizes bmp by int factor resizeFactor

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize resizeFactor infile outfile\nresizeFactor is float in (0, 100]\n");
        return 1;
    }

    // Store resize factor
    double resizeFactor = atof(argv[1]);

    // Ensure resizeFactor has legal values
    if (resizeFactor <= 0.0 || resizeFactor > 100.0)
    {
        fprintf(stderr, "Usage: ./resize resizeFactor infile outfile\nresizeFactor is float in (0, 100]\n");
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

    // Remember infile's width and height for iteration
    LONG inWidth = bi.biWidth;
    LONG inHeight = abs(bi.biHeight);

    // Change BITMAPINFOHEADER appropriately for resized file
    bi.biWidth = round(resizeFactor * bi.biWidth);
    bi.biHeight = round(resizeFactor * bi.biHeight);

    // Determine padding of scanlines of outfile
    int outPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Change last BITMAPINFOHEADER field appropriately for resized file
    bi.biSizeImage = (sizeof(RGBTRIPLE) * bi.biWidth + outPadding) * abs(bi.biHeight);

    // Change BITMAPFILEHEADER appropriately for resized file
    bf.bfSize = sizeof bf + sizeof bi + bi.biSizeImage;

    // Write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof bf, 1, outptr);

    // Write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof bi, 1, outptr);

    // heightCheck will be used to compare the written height to the expected height
    int heightCheck = 0;

    // writePixel is the number of scanlines that will be written. Works for < 1.
    double writeScanline = resizeFactor;

    // Iterate infile's number of scanlines
    for (int i = 0; i < inHeight; i++)
    {
        // Scanline temporary storage
        RGBTRIPLE *triples = malloc(inWidth * sizeof * triples);

        // Store scanline
        for (int j = 0; j < inWidth; j++)
        {
            fread(triples + j, sizeof * triples, 1, inptr);
        }

        // Skip over padding, if any. Now inptr is at the beginning of next scanline
        fseek(inptr, inPadding, SEEK_CUR);

        // Scaling happens from here on
        while ((int) writeScanline > 0 && heightCheck < abs(bi.biHeight))
        {
            // widthCheck will be used to compare the written width to the expected width
            int widthCheck = 0;

            // writePixel is the number of pixels that will be written. Works for < 1.
            double writePixel = resizeFactor;

            // Loop inWidth times to write scanlines to outfile, scaling them
            for (int j = 0; j < inWidth; j++)
            {
                // This scales scanlines. If writePixel < 0 pixels will be skipped
                while ((int) writePixel > 0)
                {
                    writePixel -= 1.0;
                    widthCheck += 1;
                    fwrite(triples + j, sizeof * triples, 1, outptr);
                }
                writePixel += resizeFactor;
            }

            // Make sure to make adjustments if the current outfile width isn't the one expected
            // If bigger, go back as many pixels as necessary in our outfile position
            while (widthCheck > bi.biWidth)
            {
                fseek(outptr, - sizeof * triples, SEEK_CUR);
                widthCheck -= 1;
            }
            // If smaller, write as many pixels as necessary in our outfile
            while (widthCheck < bi.biWidth)
            {
                fwrite(triples, sizeof * triples, 1, outptr);
                widthCheck += 1;
            }

            for (int k = 0; k < outPadding; k++)
            {
                fputc(0x00, outptr);
            }

            writeScanline -= 1.0;
            heightCheck += 1;
        }
        writeScanline += resizeFactor;

        free(triples);
    }

    fclose(inptr);
    fclose(outptr);
    printf("Done!\n");
}