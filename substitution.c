#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

 int main(int argc, string argv[])
 {
if (argc==1){
     printf("%i",argc);
     printf("lack of input!");
     return 1;
 }
 if (strlen(argv[1]) != 26 )
 {
 printf("Key must contain 26 characters.");
 return 1;
 }

for (int i = 0 ,n=strlen(argv[1]); i < n; i++){
    if (isalpha(argv[1][i])==0){
         printf("Key must contain characters.");
         return 1;
    }
}
int numbers[26]= {0};
for (int i = 0 ,n=strlen(argv[1]); i < n; i++){

    if (islower(argv[1][i])){
    int index =argv[1][i]-97;
    numbers[index]+=1;
    if (numbers[index]>=2){
        printf("No duplicate characters!");
        return 1;
    }
    }
    else{
    int index =argv[1][i]-65;
    numbers[index]+=1;
    if (numbers[index]>=2){
        printf("No duplicate characters!");
        return 1;
    }
    }


}

string text=get_string("plaintext: ");
printf("ciphertext: ");
for (int i = 0 ,n=strlen(text); i < n; i++){
    if (isalpha(text[i])){
        if (islower(text[i])){
            int temp=  text[i]-97;
            char ans = argv[1][temp];
            printf("%c",tolower(ans));
        }
        else{
            int temp1=  text[i]-65;
            char ans = argv[1][temp1];
             printf("%c",toupper(ans));
        }

    }

    else{
        printf("%c",text[i]);
    }

}
printf("\n");
 }