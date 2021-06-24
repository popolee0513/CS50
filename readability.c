#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

int main(void){
    int sent=0;
    int letter=0;
    int word=1;
    string text=get_string("Text: ");
    for (int i = 0; i < strlen(text); i++)
    {
    if (text[i]=='!' || text[i]=='.' || text[i]=='?')
    {
        sent+=1;
    }
    if (isalpha(text[i]))
    {
        letter+=1;
    }
    if (isspace(text[i]))
    {
        word+=1;
    }
    }
    printf("%i\n", sent);
    printf("%i\n", letter);
    printf("%i\n", word);

    float index = 0.0588 * (letter*100/ (float) word) - 0.296 * (sent*100/ (float) word) - 15.8;
    int ans= round(index);
    if (ans>=16){
        printf("Grade 16+\n");
    }
    else if (ans<1){
        printf("Before Grade 1\n");
    }
    else {
        printf("Grade %i\n",ans);
    }

}