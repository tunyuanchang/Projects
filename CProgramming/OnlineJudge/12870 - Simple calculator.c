#include<stdio.h>
double a,b;
char opt;
int main(){
    scanf("%lf%c%lf",&a,&opt,&b);
    switch (opt) {
        case '+':
            printf("%.3f\n",a + b);
            break;
        case '-':
            printf("%.3f\n",a - b);
            break;
        case '*':
            printf("%.3f\n",a * b);
            break;
        case '/':
            if (b == 0) printf("Error\n");
            else printf("%.3f\n",a / b);
            break;
    }
}
