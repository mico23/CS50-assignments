// Helper functions for music
// mistakes made
// atoi(char) is will not work
// in if, the data type must be the same
// strcmp only accept string, not char
// string[x] return a char, not string
// BE AWARE data type
// if int x = 1; x/2 is equal to 0.
// if double x = 1; x/2 is equal to 0.5
// round(x) is float type.

#include <cs50.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    // TODO
    int numerator;
    switch (fraction[2])
    {
        case '8' :
            numerator = fraction[0] - '0';
            break;

        case '4' :
            numerator = (fraction[0] - '0') * 2;
            break;

        case '2' :
            numerator = (fraction[0] - '0') * 4;
            break;
    }
    return numerator;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    // TODO
    // A4 is the mid point
    // hz = 440 * note_parameter * octave_parameter * accidental
    double hz = 440;
    int octave_parameter;
    double count_note;
    double note_parameter;

    // first, find the octave
    int octave = (note[strlen(note) - 1] - '0');
    if (octave >= 0 && octave <= 8)
    {
        octave_parameter = (octave - 4) * 2;
        if (octave_parameter > 0)
        {
            hz = octave_parameter * hz;
        }
        else if (octave_parameter < 0)
        {
            hz = hz / abs(octave_parameter);
        }
    }

    // second find the note
    if (isalpha(note[0]) && note[0] != 'A')
    {
        if (note[0] == 'C')
        {
            count_note = 9;
            note_parameter = pow(2, (count_note / 12));
            hz = hz / note_parameter;
        }
        else if (note[0] == 'D')
        {
            count_note = 7;
            note_parameter = pow(2, (count_note / 12));
            hz = hz / note_parameter;
        }
        else if (note[0] == 'E')
        {
            count_note = 5;
            note_parameter = pow(2, (count_note / 12));
            hz = hz / note_parameter;
        }
        else if (note[0] == 'F')
        {
            count_note = 4;
            note_parameter = pow(2, (count_note / 12));
            hz = hz / note_parameter;
        }
        else if (note[0] == 'G')
        {
            count_note = 2;
            note_parameter = pow(2, (count_note / 12));
            hz = hz / note_parameter;
        }
        else if (note[0] == 'B')
        {
            count_note = 2;
            note_parameter = pow(2, (count_note / 12));
            hz = hz * note_parameter;
        }
    }

    // third find whether there is an accidental
    if (note[1] == '#')
    {
        count_note = 1;
        note_parameter = pow(2, (count_note / 12));
        hz = hz * note_parameter;
    }
    else if (note[1] == 'b')
    {
        count_note = 1;
        note_parameter = pow(2, (count_note / 12));
        hz = hz / note_parameter;
    }

    return round(hz);
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    // TODO
    if (strcmp(s, "") == 0) // double check this log and the cs50 libr.
    {
        return true;
    }
    else
    {
        return false;
    }
}
