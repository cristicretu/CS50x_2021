#include <cs50.h>
#include <stdio.h>
#include <limits.h>

bool is_visa(int n){
    if (n == 4) return true;
    return false;
}

bool is_master(int n){
    if (n == 51 || n == 52 || n == 53 || n == 54 || n == 55) return true;
    return false;
}

bool is_american(int n){
    if (n == 34 || n == 37) return true;
    return false;
}

int sum(int n){
    if (n < 10) return n;
    int s = 0;
    while (n){
        s += n % 10;
        n /=10;
    }
    return s;
}

int myabs(int a){
    if (a < 0) return -a;
    return a;
}

void check(long long n){
    int sum1 = 0, sum2 = 0;
    bool turn = 0;
    long long aux = n;
    int count = 0;
    while (aux > 0){
        if (turn == 0){
            sum2 +=  aux % 10;
        } else {
            int db = aux % 10;
            sum1 += sum(db * 2);
        }
        
        aux /= 10;
        turn = !turn;
        count++;
    }

    // printf("%d %d \n", sum1, sum2);

    if ((sum1 + sum2) % 10 != 0){
        printf("%d %d", sum1 ,sum2);
        printf("INVALID\n");
        return;
    }
    
    while (n > 0){
        if (n < 100){
            if (is_master(n) == true && count == 16){
                printf("MASTERCARD\n");
                return;
            } else if (is_american(n) == true && count == 15){
                printf("AMEX\n");
                return;
            } else if (is_visa(n) == true && (count == 13 || count == 16)){
                printf("VISA\n");
                return;
            }
        }
        
        n /= 10;
    }
    
    printf("INVALID\n");
}

bool is_good_number(long long x){
    if (!x) return false;
    if (x < 0) return false;
    if (x > 0 && x < 9999999999999999) return true;
    return false;
}

int main(void){
    long long x = get_long("Number: \n");
    
    if (is_good_number(x) == false){
        do{
            x = get_long("Number: \n");
        } while (is_good_number(x) == false);
    }
    
    check(x);
}
