#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;
 
int main(int argc, char *argv[])
{
    // Invalid usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    
    FILE *source = fopen(argv[1], "r");
    // Invalid file
    if (source == NULL)
    {
        printf("Error: the file cannot be opened\n");
        return 1;
    }
    
    // We use a buffer to store the date temp.
    unsigned char buffer[512];
    int img_count = 0;
    bool found = 0;
    
    FILE *destination = NULL;
    
    // We read the data in 512 chunks
    while (fread(&buffer, 512, 1, source) == 1)
    {
        // Look for JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (found == 1)
            {
                fclose(destination);
            }
            else 
            {
                found = 1;
            }
            
            char filename[8];
            sprintf(filename, "%03i.jpg", img_count);
            destination = fopen(filename, "w");
            
            img_count++;
        }
        
        if (found == 1)
        {
            fwrite(&buffer, 512, 1, destination);
        }
    }
    
    fclose(source);
    fclose(destination);
    return 0;
}
