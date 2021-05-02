#include <stdio.h>
#include <cs50.h>

int main(void){
    int startp, endp, years = 0;
    do{
        startp = get_int("Start size: \n");
    }while (startp < 9);
    
    do{
         endp = get_int("End size: \n");
    }while (endp < startp);
    
    int aux = startp;
    int gain = 0;
    int lose = 0;

    while (aux < endp)
    {
        gain = aux / 3;
        lose = aux / 4;
        aux = aux + gain - lose;
        years++;
    }

    // Print number of years
    printf("Years: %d\n", years);
}