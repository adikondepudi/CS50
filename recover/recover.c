#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    //Open card.raw
    FILE *f = fopen(card.raw, "r");

    //Read first three bytes
    BYTE bytes[3];
    fread(bytes, sizeof(BYTE), 3, file);

    //Check if first four bytes match
    if(bytes[0] == 0xff, bytes[1] == 0xd8, bytes[2] == 0xff, (bytes[3] & 0xf0) == 0xe0){

    }

    while (fread(buffer, 1, BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        
    }




}