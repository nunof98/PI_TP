#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <math.h>

//Estrutura
typedef struct
{
	char tipoElemento;
	char nomeElemento[50];
	int noMaiorPotencial;
	int noMenorPotencial;
	float valor;
	int malha;
}componente;


int main()
{
	//Declaração de variaveis
	float i1, i2, i3;
	char titulo[100];
	char ficheiro[50];
	char opcao;

	//Variáveis para somar todas as tensoes/resistencias de uma malha
	float tensaoMalha1;
	float tensaoMalha2;
	float resistenciaMalha1;
	float resistenciaMalha2;
	float resistenciaPartilhada;

	//Array da struct componente
	componente circt[10];

	do
	{
		//Limpa consola
		system("cls");

		//Reseta tensoes e resistencias
		tensaoMalha1 = 0;
		tensaoMalha2 = 0;
		resistenciaMalha1 = 0;
		resistenciaMalha2 = 0;
		resistenciaPartilhada = 0;

		//Imprimir titulo
		puts("  _____  _____ _______  _____       _______ __   __      _______ _____  ______ _______ _     _ _____ _______");
		puts(" |_____]   |   |  |  | |_____]      |  |  |   \\_/        |         |   |_____/ |       |     |   |      |   ");
		puts(" |       __|__ |  |  | |            |  |  |    |         |_____  __|__ |    \\_ |_____  |_____| __|__    |   ");
		puts("");

		//Selecionar ficheiro
		printf("Escreva o nome do ficheiro que quer abrir: ");
		scanf("%s", ficheiro);
		strcat(ficheiro, ".cir");

		//Abre o ficheiro para leitura
		FILE* circuito;
		circuito = fopen(ficheiro, "r");

		//Ficheiro aberto corretamente
		int countComponentes = 0;
		if (circuito != NULL)
		{
			//Lê o titulo
			//%[^\n] -> ler até \n
			//%*c ignorar caracter (\n)
			fscanf(circuito, "%[^\n]%*c", titulo);

			//Ler ficheiro até ao fim
			while (fscanf(circuito, "%c%s %d %d %f%*c",
				&circt[countComponentes].tipoElemento,
				circt[countComponentes].nomeElemento,
				&circt[countComponentes].noMaiorPotencial,
				&circt[countComponentes].noMenorPotencial,
				&circt[countComponentes].valor) != EOF)
			{
				//Se tiver lido o .END
				if (circt[countComponentes].tipoElemento == '.' && (strcmp(circt[countComponentes].nomeElemento, "END") == 0 || strcmp(circt[countComponentes].nomeElemento, "end") == 0))
				{
					//Decrementar o indice da lista de componentes para ignorar o .END
					countComponentes--;
					//Sair do while
					break;
				}

				//Incrementar o indice da lista dos componentes
				countComponentes++;
			}

			//Fechar o ficheiro
			fclose(circuito);
		}
		else
			//Erro ao abrir ficheiro
			printf("Ocorreu um erro ao abrir o ficheiro!");


		//Contadores
		int countTensoesMalha1 = 0;
		int countTensoesMalha2 = 0;
		int countResistenciasMalha1 = 0;
		int countResistenciasMalha2 = 0;
		int countResistenciasPartilhadas = 0;

		//Percorre struct
		for (int i = 0; i <= countComponentes; i++)
		{
			//Encontra componentes da malha 1
			if ((circt[i].noMaiorPotencial == 1 && (circt[i].noMenorPotencial == 2 || circt[i].noMenorPotencial == 0)) || (circt[i].noMenorPotencial == 1 && (circt[i].noMaiorPotencial == 2 || circt[i].noMaiorPotencial == 0)))
			{
				//Se o componente for uma resistencia
				if (circt[i].tipoElemento == 'R' || circt[i].tipoElemento == 'r')
				{
					//Soma a resistencia equivalente da malha 1
					resistenciaMalha1 += circt[i].valor;
					//Atribuir a malha ao componente
					circt[i].malha = 1;
					//Incrementar contador
					countResistenciasMalha1++;
				}
				else
				{
					//Soma a tensão equivalente da malha 1
					tensaoMalha1 += circt[i].valor;
					//Atribuir a malha ao componente
					circt[i].malha = 1;
					//Incrementar contador
					countTensoesMalha1++;
				}
			}
			//Encontra componentes da malha 2
			else if ((circt[i].noMaiorPotencial == 2 && circt[i].noMenorPotencial == 3) || (circt[i].noMaiorPotencial == 3 && (circt[i].noMenorPotencial == 0 || circt[i].noMenorPotencial == 2)) || (circt[i].noMaiorPotencial == 0 && circt[i].noMenorPotencial == 3))
			{
				//Se o componente for uma resistencia
				if (circt[i].tipoElemento == 'R' || circt[i].tipoElemento == 'r')
				{
					//Soma a resistencia equivalente da malha 2
					resistenciaMalha2 += circt[i].valor;
					//Atribuir a malha ao componente
					circt[i].malha = 2;
					//Incrementar contador
					countResistenciasMalha2++;
				}
				else
				{
					//Soma a tensão equivalente da malha 2
					tensaoMalha2 += circt[i].valor;
					//Atribuir a malha ao componente
					circt[i].malha = 2;
					//Incrementar contador
					countTensoesMalha2++;
				}
			}
			//Encontra componentes partilhados por ambas as malhas
			else if ((circt[i].noMaiorPotencial == 2 && circt[i].noMenorPotencial == 0) || (circt[i].noMaiorPotencial == 0 && circt[i].noMenorPotencial == 2))
			{
				//Se o componente for uma resistencia
				if (circt[i].tipoElemento == 'R' || circt[i].tipoElemento == 'r')
				{
					//Soma a resistencia equivalente do ramo partilhado
					resistenciaPartilhada += circt[i].valor;
					//Atribuir a malha ao componente
					circt[i].malha = 0;
					//Incrementar contador
					countResistenciasPartilhadas++;
				}
			}
			//Componente não se encontra em nenhuma malha (Nós errados!)
			else
				//Imprime mensagem de erro
				printf("Erro em %c%s!! Verifique os nos no ficheiro!\n", circt[i].tipoElemento, circt[i].nomeElemento);
		}

		//Calcular correntes (através de sistema de equações)
		//Multiplicadores para as equações
		int multiplicador1 = resistenciaMalha1 + resistenciaPartilhada;
		int multiplicador2 = resistenciaPartilhada;

		//Calcular I3
		i3 = ((tensaoMalha1 * multiplicador2) - (tensaoMalha2 * multiplicador1)) / ((resistenciaPartilhada * multiplicador2) - ((resistenciaPartilhada + resistenciaMalha2) * multiplicador1));

		//Calcular I1
		i1 = (tensaoMalha1 - (resistenciaPartilhada * i3)) / (resistenciaMalha1 + resistenciaPartilhada);

		//Calcular I2
		i2 = i1 + i3;


		//Cria ficheiro de escrita e leitura
		FILE* resultado;
		resultado = fopen("resultados.out", "w+");
		if (resultado != NULL)
		{
			//Imprimir valores
			printf("\nResultados:\n\n");
			puts("Quedas de tensao: \t\tPotencia: ");
			fprintf(resultado, "Resultados:\n\n");
			fprintf(resultado, "Quedas de tensao: \t\tPotencia: \n");

			//Percorre a struct
			for (int i = 0; i <= countComponentes; i++)
			{
				//Procura resistencias
				if (circt[i].tipoElemento == 'R' || circt[i].tipoElemento == 'r')
				{
					//Calcula quedas de tensao e potencias da Malha1
					if (circt[i].malha == 1)
					{
						//Quedas de tensao
						printf("\tVR%s = %.3f V", circt[i].nomeElemento, circt[i].valor * i1);
						fprintf(resultado, "\tVR%s = %.3f V", circt[i].nomeElemento, circt[i].valor * i1);

						//Potencia
						printf("\t\t\tPR%s = %.3f W\n", circt[i].nomeElemento, circt[i].valor * (i1 * i1));
						fprintf(resultado, "\t\t\tPR%s = %.3f W\n", circt[i].nomeElemento, circt[i].valor * (i1* i1));
					}

					//Calcula quedas de tensao e potencias do ramo partilhado
					if (circt[i].malha == 0)
					{
						//Quedas de tensao
						printf("\tVR%s = %.3f V", circt[i].nomeElemento, circt[i].valor * i2);
						fprintf(resultado, "\tVR%s = %.3f V", circt[i].nomeElemento, circt[i].valor * i2);

						//Potencia
						printf("\t\t\tPR%s = %.3f W\n", circt[i].nomeElemento, circt[i].valor* (i2* i2));
						fprintf(resultado, "\t\t\tPR%s = %.3f W\n", circt[i].nomeElemento, circt[i].valor* (i2* i2));
					}

					//Calcula quedas de tensao e potencias da Malha2
					if (circt[i].malha == 2)
					{
						//Quedas de tensao
						printf("\tVR%s = %.3f V", circt[i].nomeElemento, circt[i].valor * i3);
						fprintf(resultado, "\tVR%s = %.3f V", circt[i].nomeElemento, circt[i].valor * i3);

						//Potencia
						printf("\t\t\tPR%s = %.3f W\n", circt[i].nomeElemento, circt[i].valor* (i3* i3));
						fprintf(resultado, "\t\t\tPR%s = %.3f W\n", circt[i].nomeElemento, circt[i].valor* (i3* i3));
					}
				}
			}

			//Imprimir correntes em mA (na consola e ficheiro)
			puts("\nCorrentes:");
			fprintf(resultado, "\nCorrentes:\n");
			//I1
			printf("\tI1 = %.2f mA\n", i1 * 1000);
			fprintf(resultado, "\tI1 = %.2f mA\n", i1 * 1000);
			//I2
			printf("\tI2 = %.2f mA\n", i2 * 1000);
			fprintf(resultado, "\tI2 = %.2f mA\n", i2 * 1000);
			//I3
			printf("\tI3 = %.2f mA\n\n", i3 * 1000);
			fprintf(resultado, "\tI3 = %.2f mA\n", i3 * 1000);

			//Imprimir ".OUT" no ficheiro
			fprintf(resultado, ".OUT");
			//Fechar ficheiro
			fclose(resultado);
		}

		//Perguntar ao utilizador se pretende abrir outro ficheiro
		printf("Quer abrir outro ficheiro (y/n): ");
		scanf(" %c", &opcao);

	} while (opcao == 'y' || opcao == 'Y');
	
	//Pausa
	system("pause");
	return 0;
}