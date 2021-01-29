#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    char* filename=argv[1];
    FILE *inFile=fopen(filename,"r");
    if(!inFile){
        printf("Usage: ./recover image\n");
        return 1;
    }
    BYTE buffer[512];
    int c_=0;
    sprintf(filename,"%03i.jpg",c_);
    FILE *outFile=outFile=fopen(filename,"w");
    while(fread(&buffer,512,1,inFile)){
        if((int)buffer[0]==255 && (int)buffer[1]==216 && (int)buffer[2]==255 && (int)buffer[3]>=224 && (int)buffer[3]<=239){
            fclose(outFile);
            sprintf(filename,"%03i.jpg",c_++);
            outFile=fopen(filename,"w");
            fwrite(buffer,512,1,outFile);
        }
        else if(c_>0){
            fwrite(&buffer,512,1,outFile);
        }
    }
    fclose(inFile);
    fclose(outFile);
    return 0;
}
