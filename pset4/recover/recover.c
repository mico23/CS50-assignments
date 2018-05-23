// Recover JPEGs files

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//define new data type
typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[1];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // it should be int* instead of char*; contstant char* cannot compare with 0x values.
    BYTE *JPEG_block = malloc(sizeof(BYTE) * 512);
    if (JPEG_block == NULL)
    {
        fclose(inptr);
        free(JPEG_block);
        fprintf(stderr, "Run out of memory.\n");
        return 3;
    }

    int JPEG_found = -1;

    // need to fully understand what is being written to JPEG_block
    while (fread(JPEG_block, sizeof(BYTE) * 512, 1, inptr) == 1)
    {
        // ensure the block is the header of a JPEG file
        if (JPEG_block [0] == 0xff &&
            JPEG_block[1] == 0xd8 &&
            JPEG_block[2] == 0xff &&
            (JPEG_block[3] & 0xf0) == 0xe0)
        {
            //count how many JPEG found
            JPEG_found ++;

            // create a new file for writing JPEG blocks
            //generate file name
            char outfile[8];
            sprintf(outfile, "%03i.jpg", JPEG_found);
            //"% + flag 0 + width 3(minimum 3 char to be printed + .jpg"

            //create a file to write
            FILE *outptr = fopen(outfile, "w");
            if (outptr == NULL)
            {
                fclose(inptr);
                fclose(outptr);
                free(JPEG_block);
                fprintf(stderr, "Cannot open output file.\n");
                return 4;
            }

            // write the header to the output file.
            fwrite(JPEG_block, sizeof(BYTE) * 512, 1, outptr);

            // the cuser moves to the next position
            //fread(JPEG_block, sizeof(BYTE) * 512, 1, inptr);

            while (fread(JPEG_block, sizeof(BYTE) * 512, 1, inptr) == 1)
            {
                if (!(JPEG_block [0] == 0xff &&
                      JPEG_block[1] == 0xd8 &&
                      JPEG_block[2] == 0xff &&
                      (JPEG_block[3] & 0xf0) == 0xe0))
                {
                    fwrite(JPEG_block, sizeof(BYTE) * 512, 1, outptr);
                }

                //break the loop when the block is a header of a JPEG file
                else
                {
                    break;
                }
            }

            // close the JPEG file
            fclose(outptr);

            // move the curser one block backwards
            fseek(inptr, (sizeof(BYTE) * 512) * -1, SEEK_CUR);
        }
    }

    // close any temporary memory
    free(JPEG_block);

    // close infile
    fclose(inptr);
    // close outfile
    //fclose(outptr);

    // success
    return 0;
}
