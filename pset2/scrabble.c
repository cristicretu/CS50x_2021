#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void){
    int v[30] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    
    string a = get_string("Player 1: \n");
    string b = get_string("Player 2: \n");
    
    int a_score = 0, b_score = 0;
    
    for (int i = 0, n = strlen(a); i < n; ++i){
        if (isupper(a[i])){
            a_score += v[(a[i]) - 'A'];
        } else if (islower(a[i])) {
            a_score += v[(a[i]) - 'a'];
        }
    }
    
    for (int i = 0, n = strlen(b); i < n; ++i){
        if (isupper(b[i])){
            b_score += v[(b[i]) - 'A'];
        } else if (islower(b[i])) {
            b_score += v[(b[i]) - 'a'];
        }
    }
    
    if (a_score == b_score){
        printf("Tie!");
    } else if (a_score > b_score){
        printf("Player 1 wins!");
    } else {
        printf("Player 2 wins!");
    }
}
