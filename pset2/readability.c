#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <math.h>
#include <string.h>


int main(void){
    string s = get_string("Text: \n");
    int letters = 0, sentance = 0, words = 1;
    
    for (int i = 0, n = strlen(s); i < n; ++i){
        if (s[i] == ' '){
            words++;
        }
        else if (s[i] == '!' || s[i] == '?' || s[i] == '.'){
            sentance++;
        } else if (islower(s[i]) || isupper(s[i])){
            letters++;
        }
    }
    
    float answer = 0.0588 * (100 * (float) letters / (float) words) - 0.296 * (100 * (float) sentance / (float) words) - 15.8;
    if (answer < 16 && answer >= 0){
        printf("Grade %d\n", (int) round(answer));
    } else if (answer >= 16){
        printf("Grade 16+\n");
    } else {
        printf("Before Grade 1\n");
    }
    
}
