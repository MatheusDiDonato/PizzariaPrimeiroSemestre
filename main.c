#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
#define BUFFER_SIZE 1024

//Função escolhida no menu principal, função 1 = opção, função 2 = cadastro/consulta
int funcao1, funcao2;

//Structs
typedef struct bebida {
	int codBebida;
	int estoqueBebida;
	int litragemBebida;
	float precoVendaBebida;
	float precoCustaBebida;
	char *descricaoBebidaP;
	char *descricaoBebida2P;
	char *auxP;
	char aux[50];
	char descricaoBebida[50];
	char descricaoBebida2[50];
	char* marcaBebidaP;
	char marcaBebida[35];
	char* tipoBebidaP;
	char tipoBebida[20];
} TBebida;

typedef struct arquivo {
	FILE* Arq_Con;
	FILE* Arq_Cad;
} TArquivo;

typedef struct Funcionario {
	char cpf[15];
	char NomeFuncionario[50];
	char Telefone[20];
	char DataAdmissao[10];
	char* cpfP;
	char* NomeFuncionarioP;
	char* TelefoneP;
	char* DataAdmissaoP;
	float Salario;
	char Funcao[20];
	char* FuncaoP;
} TFuncionario;

typedef struct cliente {
	char cpf[15];
	char nome[50];
	char telefone[20];
	char endereco[40];
	char* cpfP;
	char* nomeP;
	char* telefoneP;
	char* enderecoP;
} TCliente;

typedef struct ingredientes {
	char descricao[30];
	char* descricaoP;
	float estoque;
	float precoVenda;
	float precoCusto;
} TIngrediente;

//Nome dos arquivos
char ArqBebidas[12] = "bebidas.csv", ArqIngredientes[17] = "Ingredientes.csv", ArqSabor[12] = "Sabores.csv",
     ArqFuncionario[15] = "Funcionario.csv", ArqCliente[13] = "clientes.csv";

//Variaveis para lidar com o arquivoo
char buf[BUFFER_SIZE], c;
int codigo = 0;

int somadeStrings(char string1[], char string2[]){
int i, j;
for (i=0; string1[i]!='\0'; ++i);
for (j=0 ;string2[j]!='\0';++j,++i){
	string1[i]=string2[j];
}
string1='\0';
return string1;
}

int main(void)
{
	system("color 80");
	setlocale(LC_ALL, "Portuguese");           //Define o idioma, para aceitar caracteres especiais
	char loginDigitado[15], senhaDigitada[10];
	int tentativas = 0,i;

	do {
		system("cls");
		if (tentativas != 0) {
			printf("Usuário ou senha incorretos, tente novamente \n");
			printf("Tentativas: %d/5 \n \n", tentativas);
		}
		printf("Digite seu login: ");
		scanf("%s", &loginDigitado);
		printf("Digite sua senha: ");
		scanf("%s", &senhaDigitada);

		if (verificalogin(loginDigitado, senhaDigitada) == 0) {
			do {
				ExibeMenu(loginDigitado);
				if (funcao1 != 0) {
					switch (funcao1) {
					case 1:
						switch (funcao2) {
						case 1:
							CadBebida();
							break;
						case 2:
							ConBebida();
							break;
						case 3:
							break;
						default:
							printf("Funcao selecionada invalida \n");
						}
						break;
					case 2:
						switch (funcao2) {
						case 1:
							CadFuncionario();
							break;
						case 2:
							ConFuncionario();
							break;
						case 3:
							break;
						default:
							printf("Funcao selecionada invalida \n");
						}
						break;
					case 3:
						switch (funcao2) {
						case 1:
							CadCliente();
							break;
						case 2:
							ConCliente();
							break;
						case 3:
							break;
						default:
							printf("Funcao selecionada invalida \n");
						}
						break;
					case 4:
						switch (funcao2) {
						case 1:
							CadIngredientes();
							break;
						case 2:
							ConIngredientes();
							break;
						case 3:
							break;
						default:
							printf("Funcao selecionada invalida \n");
						}
						break;
					case 5:
						switch (funcao2) {
						case 1:
							CadSabor();
							break;
						case 2:
							//ConSabor();
							break;
						case 3:
							break;
						default:
							printf("Funcao selecionada invalida \n");
						}
						break;
					}
				}
				else {
					return 0;
				}
			} while (funcao1 != 0);
		}
		else {
			tentativas++;
		}
	} while (tentativas < 5);
	system("pause");
	return 0;
}

int verificalogin(char loginDigitado[], char senhaDigitada[]) {
	FILE* pont_arq;                            //Define uma variavel do tipo file que serve para indicar o caminho do arquivo
	int nivel, loginValido = 1, senhaValida = 1;          //Define a variavel do tipo inteiro
	char* loginLido, * senhaLida, buf[BUFFER_SIZE], c; //Define as variaveis do tipo char (as com * sao constantes que indicam o endereco em memoria da variavel) (a com [] e considerada um array de char);

	pont_arq = fopen("pa.csv", "r");       //abre o arquivo com a funcao fopen("caminho do arquivo", "tipo de abertura"), e coloca o arquivo na variavel do tipo file
	while (((c = getc(pont_arq)) != EOF) || (loginValido == 0 && senhaValida == 0)) {
		fgets(buf, sizeof(buf), pont_arq);  //preenche a variavel buf com a primeira linha do arquivo
		loginLido = strtok(buf, ";");        //Cria uma variavel char e utiliza a funcao strtok para separar as informacoes utilizando o delimitador ";"
		senhaLida = strtok(NULL, ";");
		nivel = atoi(strtok(NULL, ";")); //Utiliza a funcao atoi para converter string em int

		if (_stricmp(loginDigitado, loginLido) == 0) {
			loginValido = 0;
			if (_stricmp(senhaDigitada, senhaLida) == 0) {
				senhaValida = 0;
				break;
			}
			else {
				senhaValida = 1;
			}
		}
		else {
			loginValido = 1;
		}
	}
	fclose(pont_arq);
	if (loginValido == 0 && senhaValida == 0) {
		return 0;
	}
	else {
		return 1;
	}
}

int ExibeMenu(char logindigitado[]) {
	system("cls");
	printf("---------------------------- Bem Vindo %s ---------------------------------\n", logindigitado);
	printf("Selecione a funcao desejada: \n");
	printf("1 - Bebidas \n");
	printf("2 - Funcionarios \n");
	printf("3 - Clientes \n");
	printf("4 - Ingredientes \n");
	printf("5 - Sabor \n");
	printf("0 - Sair \n");
	printf("-----------------------------------------------------------------------------\n");
	printf("Escolha a funcao digitando o numero: ");
	scanf("%d", &funcao1);

	if (funcao1 == 0) {
		return;
	}

	printf("\n----------------------------------------------------------------- \n");
	printf("Voce deseja realizar: \n");
	printf("1 - Cadastro \n");
	printf("2 - Consulta \n");
	printf("3 - Voltar \n");
	printf("----------------------------------------------------------------- \n");
	printf("Escolha a opcao desejada: ");
	scanf("%d", &funcao2);
}

int CadBebida(void) {
	int i;
	char confirmacao[2], ch;
	TBebida Bebida;
	TArquivo ArquivoCadBebida;

	Bebida.codBebida = 0;
	ArquivoCadBebida.Arq_Con = fopen(ArqBebidas, "r");
	if (ArquivoCadBebida.Arq_Con != NULL) {
		while ((c = getc(ArquivoCadBebida.Arq_Con)) != EOF) {
			fgets(buf, sizeof(buf), ArquivoCadBebida.Arq_Con);
			Bebida.codBebida = atoi(strtok(buf, ";"));
		}
		fclose(ArquivoCadBebida.Arq_Con);
	}
	Bebida.codBebida++;

	system("cls");
	printf("---------------------- Cadastro de Bebidas ----------------------------- \n");
	printf("Codigo da bebida: %d \n", Bebida.codBebida);
	printf("Descricao da bebida: ");
	fflush(stdin);
	scanf("%s", &Bebida.descricaoBebida);
	scanf("%s", &Bebida.descricaoBebida2);
	printf("%s", Bebida.aux);
	setbuf(stdin, NULL);
	printf("Marca da bebida: ");
	scanf("%s", Bebida.marcaBebida);
	printf("Litragem da bebida (ml): ");
	scanf("%d", &Bebida.litragemBebida);
	printf("Tipo da bebida: ");
	scanf("%s", &Bebida.tipoBebida);
	printf("Preco de venda: ");
	scanf("%f", &Bebida.precoVendaBebida);
	printf("Preco de custo: ");
	scanf("%f", &Bebida.precoCustaBebida);
	printf("Estoque: ");
	scanf("%d", &Bebida.estoqueBebida);
	printf("------------------------------------------------------------------------ \n");
	printf("Deseja realmente salvar as informacoes digitadas (S/N)?");
	scanf("%s", &confirmacao);

	if (_stricmp(confirmacao, "S") == 0) {
		ArquivoCadBebida.Arq_Cad = fopen(ArqBebidas, "a");
		if (ArquivoCadBebida.Arq_Cad == NULL)
		{
			printf("Erro na abertura do arquivo!");
			return 0;
		}
		fprintf(ArquivoCadBebida.Arq_Cad, ";%d;%s;%s;%s;%d;%s;%.2f;%.2f;%d;\n",Bebida.codBebida, Bebida.descricaoBebida,Bebida.descricaoBebida2, Bebida.marcaBebida, Bebida.litragemBebida, Bebida.tipoBebida, Bebida.precoVendaBebida, Bebida.precoCustaBebida, Bebida.estoqueBebida);
		fclose(ArquivoCadBebida.Arq_Cad);
		printf("Dados inseridos com sucesso!! \n");
		system("pause");
	}
	return 0;
}

int ConBebida(void) {
	int formaConsulta = 0, retornou = 0;
	float lucro;
	char consulta[50], outraconsulta[2] = "";
	TBebida Bebida;

	//Variaveis para leitura de arquivo
	char buf[BUFFER_SIZE], c;
	TArquivo ArquivoConBebida;

	system("cls");
	printf("---------------------- Consulta de Bebidas ----------------------------- \n");
	printf("Voce deseja consultar por: \n");
	printf("1 - Codigo da bebida \n");
	printf("2 - Descricao da bebida \n");
	printf("3 - Marca da bebida \n");
	printf("4 - Todos \n");
	printf("0 - Voltar \n");
	printf("------------------------------------------------------------------------ \n");
	printf("Selecione a forma de consulta: ");
	scanf("%d", &formaConsulta);
	printf("-------------------------------------------------------------------\n");
	if (formaConsulta > 4) {
		printf("Selecione uma forma de consulta válida!! \n");
		system("pause");
		ConBebida();
	}
	else if (formaConsulta == 0) {
		return 0;
	}
	else if (formaConsulta <= 3) {
		printf("Digite a informacao a ser consultada: ");
		scanf("%s", &consulta);
		printf("-------------------------------------------------------------------\n");
	}

	ArquivoConBebida.Arq_Con = fopen(ArqBebidas, "r");
	while ((c = getc(ArquivoConBebida.Arq_Con)) != EOF) {
		fgets(buf, sizeof(buf), ArquivoConBebida.Arq_Con);
		Bebida.codBebida = atoi(strtok(buf, ";"));
		Bebida.descricaoBebidaP = strtok(NULL,";");
		Bebida.marcaBebidaP = strtok(NULL, ";");
		Bebida.litragemBebida = atoi(strtok(NULL, ";"));
		Bebida.tipoBebidaP = strtok(NULL, ";");
		Bebida.precoVendaBebida = atof(strtok(NULL, ";"));
		Bebida.precoCustaBebida = atof(strtok(NULL, ";"));
		Bebida.estoqueBebida = atoi(strtok(NULL, ";"));

		if ((formaConsulta == 1) && (atoi(consulta) == Bebida.codBebida)) {
			lucro = (Bebida.precoVendaBebida - Bebida.precoCustaBebida);
			printf("Código da bebida: %d \n", Bebida.codBebida);
			printf("Marca da bebida: %s \n", Bebida.marcaBebidaP);
			printf("Descrição da bebida: %s \n", Bebida.descricaoBebidaP);
			printf("Litragem da bebida: %d \n", Bebida.litragemBebida);
			printf("Tipo da bebida: %s \n", Bebida.tipoBebidaP);
			printf("Preço de venda: %.2f \n", Bebida.precoVendaBebida);
			printf("Preço de custo: %.2f \n", Bebida.precoCustaBebida);
			printf("Lucro por unidade: %.2f \n", lucro);
			printf("Estoque Disponivel: %d \n", Bebida.estoqueBebida);
			printf("-------------------------------------------------------------------\n");
			retornou = 1;
		}
		else if ((formaConsulta == 2) && (_stricmp(consulta, Bebida.descricaoBebidaP)) == 0) {
			lucro = (Bebida.precoVendaBebida - Bebida.precoCustaBebida);
			printf("Código da bebida: %d \n", Bebida.codBebida);
			printf("Marca da bebida: %s \n", Bebida.marcaBebidaP);
			printf("Descrição da bebida: %s \n", Bebida.descricaoBebidaP);
			printf("Litragem da bebida: %d \n", Bebida.litragemBebida);
			printf("Tipo da bebida: %s \n", Bebida.tipoBebidaP);
			printf("Preço de venda: %.2f \n", Bebida.precoVendaBebida);
			printf("Preço de custo: %.2f \n", Bebida.precoCustaBebida);
			printf("Lucro por unidade: %.2f \n", lucro);
			printf("Estoque Disponivel: %d \n", Bebida.estoqueBebida);
			printf("-------------------------------------------------------------------\n");
			retornou = 1;
		}
		else if ((formaConsulta == 3) && (_stricmp(consulta, Bebida.marcaBebidaP)) == 0) {
			lucro = (Bebida.precoVendaBebida - Bebida.precoCustaBebida);
			printf("Código da bebida: %d \n", Bebida.codBebida);
			printf("Marca da bebida: %s \n", Bebida.marcaBebidaP);
			printf("Descrição da bebida: %s \n", Bebida.descricaoBebidaP);
			printf("Litragem da bebida: %d \n", Bebida.litragemBebida);
			printf("Tipo da bebida: %s \n", Bebida.tipoBebidaP);
			printf("Preço de venda: %.2f \n", Bebida.precoVendaBebida);
			printf("Preço de custo: %.2f \n", Bebida.precoCustaBebida);
			printf("Lucro por unidade: %.2f \n", lucro);
			printf("Estoque Disponivel: %d \n", Bebida.estoqueBebida);
			printf("-------------------------------------------------------------------\n");
			retornou = 1;
		}
		else if (formaConsulta == 4) {
			lucro = (Bebida.precoVendaBebida - Bebida.precoCustaBebida);
			printf("Código da bebida: %d \n", Bebida.codBebida);
			printf("Marca da bebida: %s \n", Bebida.marcaBebidaP);
			printf("Descrição da bebida: %s \n", Bebida.descricaoBebidaP);
			printf("Litragem da bebida: %d \n", Bebida.litragemBebida);
			printf("Tipo da bebida: %s \n", Bebida.tipoBebidaP);
			printf("Preço de venda: %.2f \n", Bebida.precoVendaBebida);
			printf("Preço de custo: %.2f \n", Bebida.precoCustaBebida);
			printf("Lucro por unidade: %.2f \n", lucro);
			printf("Estoque Disponivel: %d \n", Bebida.estoqueBebida);
			printf("-------------------------------------------------------------------\n");
			retornou = 1;
		}
	} while ((c = getc(ArquivoConBebida.Arq_Con)) != EOF);

	fclose(ArquivoConBebida.Arq_Con);
	if (retornou == 0) {
		printf("A consulta não retornou dados!");
	}

	printf("\nDeseja realizar outra consulta? (S/N) \n");
	scanf("%s", &outraconsulta);
	if (_stricmp(outraconsulta, "s") == 0) {
		ConBebida();
	}
	return 0;
}

int CadFuncionario(void) {
	TFuncionario Funcionario;
	TArquivo AquivoCadFuncionario;
	char confirmacao[2];

	system("cls");
	printf("---------------------- Cadastro de Funcionários ----------------------------- \n");
	printf("CPF: ");
	scanf("%s", &Funcionario.cpf);
	printf("Nome: ");
	scanf("%s", &Funcionario.NomeFuncionario);
	printf("Telefone: ");
	scanf("%s", &Funcionario.Telefone);
	printf("Sálario: R$");
	scanf("%f", &Funcionario.Salario);
	printf("Data de admissão: ");
	scanf("%s", &Funcionario.DataAdmissao);
	printf("Função: ");
	scanf("%s", &Funcionario.Funcao);
	printf("------------------------------------------------------------------------ \n");
	printf("Deseja realmente salvar as informacoes digitadas? (S/N)");
	scanf("%s", &confirmacao);

	if (_stricmp(confirmacao, "s") == 0) {
		AquivoCadFuncionario.Arq_Cad = fopen(ArqFuncionario, "a");
		if (AquivoCadFuncionario.Arq_Cad == NULL)
		{
			printf("Erro na abertura do arquivo!");
			return 0;
		}
		fprintf(AquivoCadFuncionario.Arq_Cad, ";%s;%s;%s;%.2f;%s;%s;\n", Funcionario.cpf, Funcionario.NomeFuncionario, Funcionario.Telefone, Funcionario.Salario, Funcionario.DataAdmissao, Funcionario.Funcao);
		fclose(AquivoCadFuncionario.Arq_Cad);
		printf("Dados inseridos com sucesso!! \n");
		system("pause");
	}
}

int ConFuncionario(void) {
	int formaConsulta = 0, retornou = 0;
	char consulta[50], outraconsulta[2];
	TArquivo ArquivoConFuncionario;
	TFuncionario Funcionario;

	system("cls");
	printf("---------------------- Consulta de Funcionarios ----------------------------- \n");
	printf("Voce deseja consultar por: \n");
	printf("1 - CPF \n");
	printf("2 - Nome \n");
	printf("3 - Salario \n");
	printf("4 - Telefone \n");
	printf("5 - Data Admissão \n");
	printf("6 - Função \n");
	printf("7 - Todos \n");
	printf("0 - Voltar \n");
	printf("------------------------------------------------------------------------ \n");
	printf("Selecione a forma de consulta: ");
	scanf("%d", &formaConsulta);
	printf("------------------------------------------------------------------------ \n");
	if (formaConsulta > 7) {
		printf("Digite uma forma de consulta válida.");
		system("pause");
		ConFuncionario();
	}
	else if (formaConsulta == 0) {
		return 0;
	}

	if (formaConsulta <= 6) {
		printf("Digite a informacao a ser consultada: ");
		scanf("%s", &consulta);
		printf("------------------------------------------------------------------------ \n");
	}

	ArquivoConFuncionario.Arq_Con = fopen(ArqFuncionario, "r");
	do {
		fgets(buf, sizeof(buf), ArquivoConFuncionario.Arq_Con);
		Funcionario.cpfP = strtok(buf, ";");
		Funcionario.NomeFuncionarioP = strtok(NULL, ";");
		Funcionario.TelefoneP = strtok(NULL, ";");
		Funcionario.Salario = atof(strtok(NULL, ";"));
		Funcionario.DataAdmissaoP = strtok(NULL, ";");
		Funcionario.FuncaoP = strtok(NULL, ";");

		if ((formaConsulta == 1) && (_stricmp(consulta, Funcionario.cpfP)) == 0) {
			printf("CPF: %s \n", Funcionario.cpfP);
			printf("Nome: %s \n", Funcionario.NomeFuncionarioP);
			printf("Telefone: %s \n", Funcionario.TelefoneP);
			printf("Sálario: R$%.2f \n", Funcionario.Salario);
			printf("Data da Admissão: %s \n", Funcionario.DataAdmissaoP);
			printf("Função: %s \n", Funcionario.FuncaoP);
			printf("-------------------------------------------------------------------\n");
			retornou = 1;
		}
		else if ((formaConsulta == 2) && (_stricmp(consulta, Funcionario.NomeFuncionarioP)) == 0) {
			printf("CPF: %s \n", Funcionario.cpfP);
			printf("Nome: %s \n", Funcionario.NomeFuncionarioP);
			printf("Telefone: %s \n", Funcionario.TelefoneP);
			printf("Sálario: R$%.2f \n", Funcionario.Salario);
			printf("Data da Admissão: %s \n", Funcionario.DataAdmissaoP);
			printf("Função: %s \n", Funcionario.FuncaoP);
			printf("-------------------------------------------------------------------\n");
			retornou = 1;
		}
		else if ((formaConsulta == 3) && (atof(consulta) == Funcionario.Salario)) {
			printf("CPF: %s \n", Funcionario.cpfP);
			printf("Nome: %s \n", Funcionario.NomeFuncionarioP);
			printf("Telefone: %s \n", Funcionario.TelefoneP);
			printf("Sálario: R$%.2f \n", Funcionario.Salario);
			printf("Data da Admissão: %s \n", Funcionario.DataAdmissaoP);
			printf("Função: %s \n", Funcionario.FuncaoP);
			printf("-------------------------------------------------------------------\n");
			retornou = 1;
		}
		else if ((formaConsulta == 4) && (_stricmp(consulta, Funcionario.TelefoneP)) == 0) {
			printf("CPF: %s \n", Funcionario.cpfP);
			printf("Nome: %s \n", Funcionario.NomeFuncionarioP);
			printf("Telefone: %s \n", Funcionario.TelefoneP);
			printf("Sálario: R$%.2f \n", Funcionario.Salario);
			printf("Data da Admissão: %s \n", Funcionario.DataAdmissaoP);
			printf("Função: %s \n", Funcionario.FuncaoP);
			printf("-------------------------------------------------------------------\n");
			retornou = 1;
		}
		else if ((formaConsulta == 5) && (_stricmp(consulta, Funcionario.DataAdmissaoP)) == 0) {
			printf("CPF: %s \n", Funcionario.cpfP);
			printf("Nome: %s \n", Funcionario.NomeFuncionarioP);
			printf("Telefone: %s \n", Funcionario.TelefoneP);
			printf("Sálario: R$%.2f \n", Funcionario.Salario);
			printf("Data da Admissão: %s \n", Funcionario.DataAdmissaoP);
			printf("Função: %s \n", Funcionario.FuncaoP);
			printf("-------------------------------------------------------------------\n");
			retornou = 1;
		}
		else if ((formaConsulta == 6) && (_stricmp(consulta, Funcionario.FuncaoP)) == 0) {
			printf("CPF: %s \n", Funcionario.cpfP);
			printf("Nome: %s \n", Funcionario.NomeFuncionarioP);
			printf("Telefone: %s \n", Funcionario.TelefoneP);
			printf("Sálario: R$%.2f \n", Funcionario.Salario);
			printf("Data da Admissão: %s \n", Funcionario.DataAdmissaoP);
			printf("Função: %s \n", Funcionario.FuncaoP);
			printf("-------------------------------------------------------------------\n");
			retornou = 1;
		}
		else if (formaConsulta == 7){
			printf("CPF: %s \n", Funcionario.cpfP);
			printf("Nome: %s \n", Funcionario.NomeFuncionarioP);
			printf("Telefone: %s \n", Funcionario.TelefoneP);
			printf("Sálario: R$%.2f \n", Funcionario.Salario);
			printf("Data da Admissão: %s \n", Funcionario.DataAdmissaoP);
			printf("Função: %s \n", Funcionario.FuncaoP);
			printf("-------------------------------------------------------------------\n");
			retornou = 1;
		}
	} while ((c = getc(ArquivoConFuncionario.Arq_Con)) != EOF);

	if (retornou == 0) {
		printf("A consulta não retornou dados!");
	}

	printf("\nDeseja realizar outra consulta? (S/N) \n");
	scanf("%s", &outraconsulta);
	if (_stricmp(outraconsulta, "s") == 0) {
		ConFuncionario();
	}

	return 0;
}

int CadCliente(void) {
	TCliente Cliente;
	TArquivo ArqCadCli;
	char confirmacao[2];

	system("cls");
	printf("---------------------- Cadastro de Clientes ----------------------------- \n");
	printf("CPF: ");
	scanf("%s", &Cliente.cpf);
	printf("Nome do cliente: ");
	scanf("%s", &Cliente.nome);
	printf("Telefone Cliente: ");
	scanf("%s", &Cliente.telefone);
	printf("Endereco: ");
	scanf("%s", &Cliente.endereco);
	printf("------------------------------------------------------------------------ \n");
	printf("Deseja realmente salvar as informacoes digitadas? (S/N)");
	scanf("%s", &confirmacao);

	if (_stricmp(confirmacao, "s") == 0) {
		ArqCadCli.Arq_Cad = fopen(ArqCliente, "a");
		if (ArqCadCli.Arq_Cad == NULL)
		{
			printf("Erro na abertura do arquivo!");
			return 0;
		}
		fprintf(ArqCadCli.Arq_Cad, ";%s;%s;%s;%s;\n", Cliente.cpf, Cliente.nome, Cliente.telefone, Cliente.endereco);
		fclose(ArqCadCli.Arq_Cad);
		printf("Dados inseridos com sucesso!! \n");
		system("pause");
	}
}

int ConCliente(void) {
	TCliente Cliente;
	TArquivo Arquivo;
	int formaConsulta = 0, retornou = 0;
	char consulta[50], outraconsulta[2];
	system("cls");
	printf("---------------------- Consulta de Clientes ----------------------------- \n");
	printf("Voce deseja consultar por: \n");
	printf("1 - CPF \n");
	printf("2 - Nome \n");
	printf("3 - Endereco \n");
	printf("4 - Telefone \n");
	printf("5 - Todos \n");
	printf("0 - Voltar \n");
	printf("------------------------------------------------------------------------ \n");
	printf("Selecione a forma de consulta: ");
	scanf("%d", &formaConsulta);
	printf("------------------------------------------------------------------------ \n");
	if (formaConsulta > 5) {
		printf("Digite uma forma de consulta válida.");
		system("pause");
		ConCliente();
	}
	else if (formaConsulta == 0) {
		return 0;
	}

	if (formaConsulta <= 4) {
		printf("Digite a informacao a ser consultada: ");
		scanf("%s", &consulta);
	}

	Arquivo.Arq_Con = fopen(ArqCliente, "r");
	do {
		fgets(buf, sizeof(buf), Arquivo.Arq_Con);
		Cliente.cpfP = strtok(buf, ";");
		Cliente.nomeP = strtok(NULL, ";");
		Cliente.telefoneP = strtok(NULL, ";");
		Cliente.enderecoP = strtok(NULL, ";");

		if ((formaConsulta == 1) && (_stricmp(consulta, Cliente.cpfP)) == 0) {
			printf("CPF: %s \n", Cliente.cpfP);
			printf("Nome: %s \n", Cliente.nomeP);
			printf("Telefone: %s \n", Cliente.telefoneP);
			printf("Endereço: %s \n", Cliente.enderecoP);
			printf("-------------------------------------------------------------------\n");
			retornou = 1;
		}
		else if ((formaConsulta == 2) && (_stricmp(consulta, Cliente.nomeP)) == 0) {
			printf("CPF: %s \n", Cliente.cpfP);
			printf("Nome: %s \n", Cliente.nomeP);
			printf("Telefone: %s \n", Cliente.telefoneP);
			printf("Endereço: %s \n", Cliente.enderecoP);
			printf("-------------------------------------------------------------------\n");
			retornou = 1;
		}
		else if ((formaConsulta == 3) && (_stricmp(consulta, Cliente.enderecoP)) == 0) {
			printf("CPF: %s \n", Cliente.cpfP);
			printf("Nome: %s \n", Cliente.nomeP);
			printf("Telefone: %s \n", Cliente.telefoneP);
			printf("Endereço: %s \n", Cliente.enderecoP);
			printf("-------------------------------------------------------------------\n");
			retornou = 1;
		}
		else if ((formaConsulta == 4) && (_stricmp(consulta, Cliente.telefoneP)) == 0) {
			printf("CPF: %s \n", Cliente.cpfP);
			printf("Nome: %s \n", Cliente.nomeP);
			printf("Telefone: %s \n", Cliente.telefoneP);
			printf("Endereço: %s \n", Cliente.enderecoP);
			printf("-------------------------------------------------------------------\n");
			retornou = 1;
		}
		else if (formaConsulta == 5){
			printf("CPF: %s \n", Cliente.cpfP);
			printf("Nome: %s \n", Cliente.nomeP);
			printf("Telefone: %s \n", Cliente.telefoneP);
			printf("Endereço: %s \n", Cliente.enderecoP);
			printf("-------------------------------------------------------------------\n");
			retornou = 1;
		}
	} while ((c = getc(Arquivo.Arq_Con)) != EOF);

	if (retornou == 0) {
		printf("A consulta não retornou dados!");
	}

	printf("\nDeseja realizar outra consulta? (S/N) \n");
	scanf("%s", &outraconsulta);
	if (_stricmp(outraconsulta, "s") == 0) {
		ConCliente();
	}

	return 0;
}

int CadIngredientes(void) {
	TIngrediente Ingrediente;
	TArquivo ArqCadIngrediente;
	char confirmacao[2];

	system("cls");
	printf("---------------------- Cadastro de Ingredientes ----------------------------- \n");
	printf("Descrição: ");
	scanf("%s", &Ingrediente.descricao);
	printf("Estoque: ");
	scanf("%f", &Ingrediente.estoque);
	printf("Preço de custo: ");
	scanf("%f", &Ingrediente.precoCusto);
	printf("Preço de venda: ");
	scanf("%f", &Ingrediente.precoVenda);
	printf("------------------------------------------------------------------------ \n");
	printf("Deseja realmente salvar as informacoes digitadas? (S/N)");
	scanf("%s", &confirmacao);

	if (_stricmp(confirmacao, "s") == 0) {
		ArqCadIngrediente.Arq_Cad = fopen(ArqIngredientes, "a");
		if (ArqCadIngrediente.Arq_Cad == NULL)
		{
			printf("Erro na abertura do arquivo!");
			return 0;
		}
		fprintf(ArqCadIngrediente.Arq_Cad, ";%s;%.2f;%.2f;%.2f;\n", Ingrediente.descricao, Ingrediente.estoque, Ingrediente.precoCusto, Ingrediente.precoVenda);
		fclose(ArqCadIngrediente.Arq_Cad);
		printf("Dados inseridos com sucesso!! \n");
		system("pause");
	}
}

int ConIngredientes(void) {
	TIngrediente Ingrediente;
	TArquivo Arquivo;
	int formaConsulta = 0, retornou = 0;
	char consulta[50], outraconsulta[2];
	float lucro = 0;

	system("cls");
	printf("---------------------- Consulta de Ingredientes ----------------------------- \n");
	printf("Voce deseja consultar por: \n");
	printf("1 - Descricao \n");
	printf("2 - Todos \n");
	printf("0 - Voltar \n");
	printf("------------------------------------------------------------------------ \n");
	printf("Selecione a forma de consulta: ");
	scanf("%d", &formaConsulta);
	printf("------------------------------------------------------------------------ \n");
	if (formaConsulta > 2) {
		printf("Digite uma forma de consulta válida.");
		system("pause");
		ConIngredientes();
	}
	else if (formaConsulta == 0) {
		return 0;
	}

	if (formaConsulta <= 1) {
		printf("Digite a informacao a ser consultada: ");
		scanf("%s", &consulta);
	}

	Arquivo.Arq_Con = fopen(ArqIngredientes, "r");
	do {
		fgets(buf, sizeof(buf), Arquivo.Arq_Con);
		Ingrediente.descricaoP = strtok(buf, ";");
		Ingrediente.estoque = atof(strtok(NULL, ";"));
		Ingrediente.precoCusto = atof(strtok(NULL, ";"));
		Ingrediente.precoVenda = atof(strtok(NULL, ";"));
		lucro = Ingrediente.precoVenda - Ingrediente.precoCusto;

		if ((formaConsulta == 1) && (_stricmp(consulta, Ingrediente.descricaoP)) == 0) {
			printf("Descrição: %s \n", Ingrediente.descricaoP);
			printf("Estoque: %.2f \n", Ingrediente.estoque);
			printf("Preço de custo: %.2f \n", Ingrediente.precoCusto);
			printf("Preço de venda: %.2f \n", Ingrediente.precoVenda);
			printf("Lucro por unidade: %.2f \n", lucro);
			printf("-------------------------------------------------------------------\n");
			retornou = 1;
		}
		else if (formaConsulta == 2){
			printf("Descrição: %s \n", Ingrediente.descricaoP);
			printf("Estoque: %.2f \n", Ingrediente.estoque);
			printf("Preço de custo: %.2f \n", Ingrediente.precoCusto);
			printf("Preço de venda: %.2f \n", Ingrediente.precoVenda);
			printf("Lucro por unidade: %.2f \n", lucro);
			printf("-------------------------------------------------------------------\n");
			retornou = 1;
		}
	} while ((c = getc(Arquivo.Arq_Con)) != EOF);

	if (retornou == 0) {
		printf("A consulta não retornou dados!");
	}

	printf("\nDeseja realizar outra consulta? (S/N) \n");
	scanf("%s", &outraconsulta);
	if (_stricmp(outraconsulta, "s") == 0) {
		ConIngredientes();
	}

	return 0;
}

int CadSabor(void) {
	TArquivo ArqCadSabor, ArqConIngrediente;
	TIngrediente Ingrediente;
	char confirmacao[2], descricaoIngrediente[30], Descricao[40];
	int quantingred, i = 0, ExisteIngrediente = 0;
	float quantutilizada;

	system("cls");
	printf("---------------------- Cadastro de Sabor ----------------------------- \n");
	printf("Descrição: ");
	scanf("%s", &Descricao);
	printf("Quantidade de ingredientes utilizados: ");
	scanf("%d", &quantingred);
	for (i = 0; i < quantingred; i++) {
		printf("Descrição do ingrediente: ");
		scanf("%s", &descricaoIngrediente);

		ArqConIngrediente.Arq_Con = fopen(ArqIngredientes, "r");
		if (ArqConIngrediente.Arq_Con != NULL) {
			while ((c = getc(ArqConIngrediente.Arq_Con)) != EOF){
				fgets(buf, sizeof(buf), ArqConIngrediente.Arq_Con);
				Ingrediente.descricaoP = strtok(buf, ";");
				if (_stricmp(Ingrediente.descricaoP, descricaoIngrediente) == 0) {
					ExisteIngrediente == 1;
				}
			}
			fclose(ArqConIngrediente.Arq_Con);
		}
		printf("Quantidade utilizada: ");
		scanf("f", &quantutilizada);
		//aqui vai abrir o arquivo dos ingrediente e comparar o nome que ele digitou
	}
	printf("------------------------------------------------------------------------ \n");
	printf("Deseja realmente salvar as informacoes digitadas? (S/N)");
	scanf("%s", &confirmacao);

	if (_stricmp(confirmacao, "s") == 0) {
		ArqCadSabor.Arq_Cad = fopen(ArqSabor, "a");
		if (ArqCadSabor.Arq_Cad == NULL)
		{
			printf("Erro na abertura do arquivo!");
			return 0;
		}
		//fprintf(ArqCadSabor.Arq_Cad, ";%s;%.2f;%.2f;%.2f;\n" );
		fclose(ArqCadSabor.Arq_Cad);
		printf("Dados inseridos com sucesso!! \n");
		system("pause");
	}
}


