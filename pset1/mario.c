#include <stdio.h>
#include <cs50.h>
#include <limits.h>

bool is_good_number(int x){
    if (!x) return false;
    if (x < 0) return false;
    if (x > 0 && x < 9) return true;
    return false;
}

int main(void){
    int x = get_int("Height: \n");
    
    if (is_good_number(x) == false){
        do{
            x = get_int("Height: \n");
        } while (is_good_number(x) == false);
    }
    
    for (int i = 1; i <= x; ++i){
        for (int j = 1; j <= x - i; ++j){
            printf(" ");
        }
        for (int j = 1; j <= i; ++j){
            printf("#");
        }
        printf("  ");
        for (int j = 1; j <= i; ++j){
            printf("#");
        }
        
        printf("\n");
    }
}
