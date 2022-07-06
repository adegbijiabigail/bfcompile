#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MEMSIZE 30000

int main(int argc, char* argv[])
{
    //load file contents 
    FILE* f;
    f = fopen(argv[1], "r");
    fseek(f, 0L, SEEK_END);
    long flen = ftell(f);
    rewind(f); 
    char c;
    int i;
    char* bfcode = malloc(flen*sizeof(char));
    do {
        c = fgetc(f);
        bfcode[i] = c;
        i++;
    } while (c != EOF);
    fclose(f);

    //interpretation
    uint8_t memory[MEMSIZE] = {0}; //uint8_t --> 1 byte int
    int mem_addr = 0;
    int loopindex = 0;
    int charindex = 0;

    while (charindex < (flen / sizeof(char)))
    {
        char bfchar = bfcode[charindex];
        
        switch (bfchar)
        {
            case '>':
                mem_addr += 1;
                break;
            case '<':
                mem_addr -= 1;
                break;
            case '+':
                memory[mem_addr] += 1;
                break;
            case '-':
                memory[mem_addr] -= 1;
                break;
            case '.':
                printf("%c", memory[mem_addr]);
                break;
            case ',':
                ;
                int input = getchar();
                memory[mem_addr] = input;
                break;
            case '[':
                if (memory[mem_addr] != 0)
                {
                    loopindex = charindex;
                }
                break;
            case ']':
                if (memory[mem_addr] != 0)
                {
                    charindex = loopindex;
                }
                break;
        }   

        charindex++;
    }
}