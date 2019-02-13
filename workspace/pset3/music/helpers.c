// Helper functions for music

#include <cs50.h>
#include <string.h>
#include <math.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int X = atoi(strtok(fraction, "/"));
    int Y = atoi(strtok(NULL, "/"));
    return  8 * X / Y;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    // Number of semitones from this note to A4
    int n;
    // Split note to a letter octave and accidental
    char letter;
    int octave;
    char accidental;
    if (note[1] >= '0' && note[1] <= '9')
    {
        letter = note[0];
        octave = note[1] - '0';
        accidental = '\0';
    }
    else
    {
        letter = note[0];
        octave = note[2] - '0';
        accidental = note[1];
    }
    // Change n because of letter
    switch (letter)
    {
        case 'A' :
            n = 0;
            break;

        case 'B' :
            n = 2;
            break;

        case 'C' :
            n = -9;
            break;

        case 'D' :
            n = -7;
            break;

        case 'E' :
            n = -5;
            break;

        case 'F' :
            n = -4;
            break;

        case 'G' :
            n = -2;
            break;
    }
    // Change n because of octave
    n += (octave - 4) * 12;
    // Change n because of accidental
    n += accidental == '#' ? 1 : accidental == 'b' ? -1 : 0;

    int f = round(pow(2, (double) n / 12) * 440);
    return f;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (strlen(s) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
