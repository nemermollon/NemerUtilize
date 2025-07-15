/*
	Para compilar : gcc xor_arquivo.c -o xor_arquivo
	Executando: ./xor_arquivo arquivo_entrada arquivo_saida <chave> 
*/

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	FILE *entrada;
	FILE *saida;
	char byte_entrada;
	char byte_saida;
	
	if (argc < 3) {
		puts("Informe os nomes dos arquivos");
		return 1;
	}
	
	if (!(entrada = fopen(argv[1], "rb"))) {
		perror("Entrada");
		return 2;
	}
	
	if (!(saida = fopen(argv[2], "wb"))) {
		perror("Saida");
		return 2;
	}
	
	/* Caso não passe a chave, aplica o XOR bit a bit com o valor 255 */
	if (argc < 4) {
		while(fread(&byte_entrada, 1, 1, entrada)) {
			byte_saida = byte_entrada ^ 0xFF;
			fwrite(&byte_saida, 1, 1, saida);
			#ifdef DEBUG
			printf("\\x%x", (unsigned char)byte_saida);
			#endif
		}
		#ifdef DEBUG
		puts("");
		#endif
	} else {
		int comprimento = strlen(argv[3]);
		int indice = 0;
		
		printf("Chave: "); puts(argv[3]);
		printf("Comprimento: %d\n", comprimento);
		
		/* Aplica a chave passada como argumento de forma circular */
		while(fread(&byte_entrada, 1, 1, entrada)) {
			byte_saida = byte_entrada ^ ((indice == comprimento)? argv[3][indice=0] : argv[3][indice++]);
			fwrite(&byte_saida, 1, 1, saida);
			#ifdef DEBUG
			printf("\\x%x", (unsigned char)byte_saida);
			#endif
		}
		#ifdef DEBUG
		puts("");
		#endif
	}
	fflush(saida);
	
	fclose(entrada);
	fclose(saida);
	
	return 0;
}

