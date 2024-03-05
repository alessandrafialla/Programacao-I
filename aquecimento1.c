#include <stdio.h>

int main()
{
	int n;

	scanf("%d", &n);
	
	/*i vai ate n/2 para reduzir a quantidade de comparacoes */
	for (int i = 0; i < n/2 ; i++){
		if (i * (i + 1) * (i + 2) == n){
			printf ("%d\n" , 1);
			return 0;
		}
	}
	printf("%d\n" , 0);
	return 0;
}

