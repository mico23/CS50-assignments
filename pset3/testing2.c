
//round(x) is float type.
#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    // TODO
    //A4 is the mid point
    // hz = 440 * note_parameter * octave_parameter * accidental
    //operations between double and int; what will return?

    string note = get_string("Please enter your note: ");

    double hz = 440;
    int octave_parameter;
    double count_note;
    //double power = (count_note/12);
    double note_parameter;

    //eprintf("POWER: %f\n", power);
    //eprintf("%f\n", note_parameter);

    octave_parameter = (note[strlen(note) - 1] - '4') * 2;
    //eprintf("%f\n", octave_parameter);
    if (octave_parameter > 0)
    {
        hz = octave_parameter * hz; //double check data type
    }
    else if (octave_parameter < 0)
    {
        hz = hz / abs(octave_parameter);
    }
    else
    {
        //may delete this
    }

    //second find the note
    if (isalpha(note[0]) && note[0] != 'A')
    {
        if (note[0] == 'C') //should be "" instead of ''
        {
            count_note = 9;
            note_parameter = pow(2, (count_note/12));
            eprintf("%f\n", note_parameter);
            hz = hz / note_parameter;
            //eprintf("POWER: %f\n", power);
        }
        else if (note[0] == 'D')
        {
            count_note = 7;
            note_parameter = pow(2, (count_note/12));
            hz = hz / note_parameter;

            //eprintf("POWER: %f\n", power);
        }
        else if (note[0] == 'E')
        {
            count_note = 5;
            note_parameter = pow(2, (count_note/12));
            hz = hz / note_parameter;

            //eprintf("POWER: %f\n", power);
        }
        else if (note[0] == 'F')
        {
            count_note = 4;
            note_parameter = pow(2, (count_note/12));
            hz = hz / note_parameter;

            //eprintf("POWER: %f\n", power);
        }
        else if (note[0] == 'G')
        {
            count_note = 2;
            note_parameter = pow(2, (count_note/12));
            hz = hz / note_parameter;

            //eprintf("POWER: %f\n", power);
        }
        else if (note[0] == 'B')
        {
            count_note = 2;
            note_parameter = pow(2, (count_note/12));
            hz = hz * note_parameter;

            //eprintf("POWER: %f\n", power);
        }
        else
        {
            //may delete this
        }
    }

    //second find whether there is an accidental
    if (note[1] == '#')
    {
        count_note = 1;
        note_parameter = pow(2, (count_note/12));
        hz = hz * note_parameter;

        //eprintf("POWER: %f\n", power);
    }
    else if (note[1] == 'b')
    {
        count_note = 1;
        note_parameter = pow(2, (count_note/12));
        hz = hz / note_parameter;

        //eprintf("POWER: %f\n", power);
    }

    printf("%f\n", round(hz));
}
