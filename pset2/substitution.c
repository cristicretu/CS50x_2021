#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void solve(string s);

int main(int argc, string argv[]){
    if (argc == 2){
        if (strlen(argv[1]) == 26) {
            for (int i = 0; i < strlen(argv[1]) ; i++){
                if (! isalpha(argv[1][i])) {
                    printf("Key must contain 26 characters.\n");
                    return 1;
                }
                for (int j = i + 1 ; j < strlen(argv[1]) ; j++){
                    if (toupper(argv[1][j]) == toupper(argv[1][i])) {
                        printf("Key must not contain repeated alphabets.\n");
                        return 1;
                    }
                }
            }
            
            solve(argv[1]);
            
        }
        else {
            printf("Key must contain 26 characters.\n");
            return 1;   
        }
        
    }
    else {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}

void solve(string key){
    string s = get_string("plainttext: \n");
    for (int i = 0, n = strlen(s); i < n; ++i){
        if (islower(s[i])){
             s[i] = tolower(key[(s[i] - 'a')]);
        } else if (isupper(s[i])) {
             s[i] = toupper(key[(s[i] - 'A')]);
        }
    }
    
    printf("ciphertext: %s\n", s);
}
