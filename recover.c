#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t BYTE;
int main(int argc, char *argv[])
{
    // Check usage
    if (argc != 2)
    {
        return 1;
    }
    // Open file
    FILE *file = fopen(argv[1], "r");
   if (!file)
    {
        return 1;
    }
   BYTE bytes[512];
   int start=0;
   char str[8];
   str[0]='e';
   while(fread(bytes, sizeof(BYTE), 512, file)){
   if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3]& 0xf0)== 0xe0)
   {
       FILE *fp= NULL;
       sprintf(str, "%03d", start);
       str[3]='.';
       str[4]='j';
       str[5]='p';
       str[6]='g';
       fp=fopen(str,"w");
       start+=1;
       fwrite(bytes, sizeof(BYTE), 512, fp);
       fclose(fp);
   }
    else {
          if (str[0]!='e' )
          {
          FILE *fp;
          fp=fopen(str,"a");
          fwrite(bytes, sizeof(BYTE), 512, fp);
          fclose(fp);
          }
     }
}
}