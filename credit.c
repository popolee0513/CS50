#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
int a=0;
int add=0;
int record;
int temp;
int temp1;
long n = get_long("Number: ");

do{
    int ans =n%10;
    n=(n/10);
    a+=1;
    if (n>10 && n<100)
    {
        record=n;
    }
    if (a%2==0){
        ans*=2;
        if (ans>=10)
        {
            temp=ans%10;
            temp1=ans/10;
            ans=temp1+temp;
        }
    }
    add+=ans;


}
while (n>=1);

if (add%10!=0){
        printf("INVALID\n");}
else{
if (record/10==4 && (a==13 || a==16  ) ){
            printf("VISA\n");
        }
else if ((record==34 || record==37) && a==15){
            printf("AMEX\n");
        }
else if (a==16){
        printf("MASTERCARD\n");
        }
else{
    printf("INVALID\n");
}

}

}
