#include <cs50.h>
#include <stdio.h>

int main(void)
{
int height ;
do{

height= get_int("Height: ");
}
while (height<1 || height>8);

for (int i = 1; i <= height; i++)
{
for (int j=0; j< height-i; j++){
    printf("%c",' ');
}
for (int j=0 ; j<i ;j++){
    printf("%c",'#');
}
printf("%s","  " );
for (int j=0 ; j<i ;j++){
    printf("%c",'#');
}
printf("\n");
}
}