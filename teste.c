#include <stdlib.h>
#include <stdio.h>

/* Retorna um inteiro aleatorio entre min e max*/
int aleat(int min, int max)
{
    return min + rand() % (max - min + 1);
}

int main(){
    int i;

    for( i = 0; i < 100; i++){
        printf("%d\n", aleat(0, 10));
    }
    return 1;

}