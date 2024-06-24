#include <stdio.h>

int main() {
    
    int num, valorQuadrado, quadrado;

	valorQuadrado = 1;

	/*O laço continua enquanto n != 0 */
	while (1) {
	
		/*Le o primeiro numero e verifica se nao e zero*/
		scanf("%d", &num);
     		if (num == 0)
	       		break;
        /*Le o segundo numero e verifica se nao e zero*/
		scanf("%d", &quadrado);
		if (quadrado == 0)
			break;

		/*So atribui valor se o o segundo nao for o quadrado do primeiro*/
		if ((num*num) != quadrado)
			valorQuadrado = 0;
        	        	
	}
	printf("%d\n", valorQuadrado);

	return 0;
}
