#include <stdio.h>

int main()
{
	int n;
	scanf("%d", &n);
	
	/*i vai ate n/3 para reduzir a quantidade de comparacoes */
	for (int i = 0; i < n/3 ; i++)
	{
		if (i * (i + 1) * (i + 2) == n) /* maior valor possivel de i eh n/3*/
		{
			printf ("%d\n" , 1);
			return 0;
		}
	}
	printf("%d\n" , 0);
	return 0;
}

