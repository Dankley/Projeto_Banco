#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_CONTAS 100
#define TAM_NOME 100
#define TAM_CPF 15
#define TAM_AGENCIA 10
#define TAM_TELEFONE 20
#define ATIVA 1
#define ENCERRADA 0

typedef struct {
    int numero;                 /* número único da conta */
    char nome[TAM_NOME];
    char cpf[TAM_CPF];
    char agencia[TAM_AGENCIA];
    char telefone[TAM_TELEFONE];
    double saldo;
    int status;                 /* ATIVA ou ENCERRADA */
} Conta;

// Funções de validação
int validar_nome(const char* nome) {
	int has_alpha = 0;
	if (nome == NULL || nome[0] == '\0') return 0;
	for (size_t i = 0; nome[i] != '\0'; i++) {
		if (isdigit((unsigned char)nome[i])) return 0; // não permite dígitos no nome
		if (isalpha((unsigned char)nome[i])) has_alpha = 1;
	}
	return has_alpha; // válido se tiver pelo menos uma letra e nenhum dígito
}

int validar_cpf(const char* cpf) {
	if (cpf == NULL) return 0;
	int len = 0;
	for (size_t i = 0; cpf[i] != '\0'; i++) {
		if (!isdigit((unsigned char)cpf[i])) return 0; // não permite letras ou outros símbolos
		len++;
	}
	return (len == 11); // CPF brasileiro tem 11 dígitos
}

int validar_telefone(const char* telefone) {
	if (telefone == NULL) return 0;
	int len = 0;
	for (size_t i = 0; telefone[i] != '\0'; i++) {
		if (!isdigit((unsigned char)telefone[i])) return 0; // não permite letras
		len++;
	}
	return (len >= 8 && len <= 15); // aceita telefones com 8 a 15 dígitos
}

int BuscarPorCPF (Conta contas[], int qtd, char cpf[])
	{
	 for (int i = 0 ; i < qtd; i++)
	 	{
	 		if  (strcmp(contas[i].cpf, cpf) == 0)
			 	{
	 		 		return i;
				}
	 	}
	 	return -1; //não encontrou conta
	}	
	int buscarConta (Conta contas[], int qtd, int numero, char agencia[])
	{
	 for (int i = 0 ; i < qtd; i++)
	 	{
	 		if  (contas[i].numero == numero &&
			 strcmp(contas[i].agencia, agencia) == 0) //A agência digitada pelo usuário é exatamente igual à agência armazenada no vetor?
			 	{
	 		 		return i;
				}
	 	}
	 	return -1; //não encontrou conta
	}	
void abrirConta(Conta contas[], int *qtd)
	{
		if (*qtd >= MAX_CONTAS)
			{
				printf ("Limite de contas excedido!\n");
				return;
			}
		int novo_num = *qtd +1;	
		contas[*qtd].numero = novo_num;
		snprintf(contas[*qtd].agencia,TAM_AGENCIA, "%03d", novo_num);	 
		printf ("O numero da sua conta sera: %d\n", contas[*qtd].numero);
		printf ("A sua agencia sera: %s \n", contas[*qtd].agencia);
		printf("Digite o nome completo: ");
		fgets(contas[*qtd].nome,TAM_NOME,stdin);
		contas[*qtd].nome[strcspn(contas[*qtd].nome, "\n")] = '\0';

		// Valida nome: não pode conter números
		if (!validar_nome(contas[*qtd].nome)) {
			printf("nome invalido\n");
			return;
		}
		
		printf("Digite o seu CPF: ");
		fgets (contas[*qtd].cpf,TAM_CPF,stdin);
		contas[*qtd].cpf[strcspn(contas[*qtd].cpf, "\n")] = '\0';

		// Valida CPF: somente dígitos, 11 caracteres
		if (!validar_cpf(contas[*qtd].cpf)) {
			printf("cpf invalido\n");
			return;
		}
		
		int idx = BuscarPorCPF (contas, *qtd, contas[*qtd].cpf); //valida se nao esta usando o cpf duas vezes
		if (idx != -1 && contas[idx].status == ATIVA)
			{
				printf ("CPF ja possui conta ativa cadastrada\n");
				return;
			}
		printf("Digite seu telefone: ");
		fgets(contas[*qtd].telefone,TAM_TELEFONE,stdin);
		contas[*qtd].telefone[strcspn(contas[*qtd].telefone, "\n")] = '\0';

		// Valida telefone: somente dígitos e tamanho razoavel
		if (!validar_telefone(contas[*qtd].telefone)) {
			printf("numero invalido\n");
			return;
		}
		
		contas[*qtd].saldo = 0;
		
		contas[*qtd].status = ATIVA;
		
		(*qtd)++;
		
		printf ("Parabens, conta criada com sucesso!\n");	
	}

void depositar(Conta contas[], int qtd) // Nesse caso o ponteiro não é necessário pois, na função depositar o valor "qtd" só é consultado
	{
	int numero;
	char agencia[TAM_AGENCIA];
	double valor;
	
	printf ("Digite o numero da sua conta bancaria:\n");
	scanf ("%d", &numero);
	getchar();
	
	printf ("Digite o numero da sua agencia:\n");
	fgets(agencia, TAM_AGENCIA, stdin);
	agencia[strcspn(agencia, "\n")] = '\0'; //apenas para remover o \n
	
	int idx = buscarConta(contas, qtd, numero, agencia); //posição da conta no array
	if (idx == -1)
		{
			printf ("Conta nao encontrada!");
			return;
		}
	if (contas[idx].status == ENCERRADA) 
	{
    printf("Conta encerrada nao permite operacoes.\n");
    return;
	}
		
	printf ("Digite o valor do deposito:");
	if (scanf("%lf", &valor) != 1)
	{
		printf ("Entrada invalida.\n");
		return;
	}
	
	if (valor <= 0)
		{
			printf ("Valor invalido!\n");
			return;
		}	
		
	contas[idx].saldo += valor;
	
	printf ("Deposito feito com sucesso!\n");	
	}
	
void sacar(Conta contas[], int qtd)
{
	int numero;
	char agencia[TAM_AGENCIA];
	double valor;
	
	printf ("Digite o numero da sua conta bancaria:\n");
	scanf ("%d", &numero);
	getchar ();
	
	printf ("Digite o numero da sua agencia:\n");
	fgets(agencia, TAM_AGENCIA, stdin);
	agencia[strcspn(agencia, "\n")] = '\0';
	
	int idx = buscarConta(contas, qtd, numero, agencia);
	if (idx == -1)
	{
		printf ("Conta nao encontrada!");
		return;
	}
	if (contas[idx].status == ENCERRADA) 
	{
    printf("Conta encerrada nao permite operacoes.\n");
    return;
	}
	printf ("Digite o valor que deseja sacar:");
	if (scanf("%lf", &valor) !=1) 
	{
		printf ("Entrada invalida.\n");
		return;
	}
	if (valor <=0)
		{
		printf ("Valor invalido!\n");
		return;
		}
		
	if (valor > contas[idx].saldo)
	{
		printf ("Valor indisponivel para retirada");
		return;
	}
	
	contas [idx].saldo -= valor;
	printf ("Saque efetuado com exito\n");
}

void transferencias(Conta contas[], int qtd)
{
	int numero1, numero2;
	char agencia1[TAM_AGENCIA], agencia2[TAM_AGENCIA];
	double valor;
	
	printf ("Digite o numero da sua conta bancaria: ");
	scanf ("%d", &numero1);
	getchar();
	
	printf ("Digite o numero da sua agencia: ");
	fgets (agencia1, TAM_AGENCIA, stdin);
	agencia1 [strcspn (agencia1, "\n")] = '\0';
	
	int idx1= buscarConta(contas, qtd, numero1, agencia1);
	if (idx1 == -1)
			{
				printf ("Conta nao encontrada!\n");
				return;
			}
	if (contas[idx1].status == ENCERRADA)
	{
    printf("Conta encerrada nao permite operacoes.\n");
    return;
	}
	
	printf ("Digite o numero da conta destino:");
	scanf ("%d", &numero2);
	getchar();
	
	printf ("Digite o numero da agencia destino:");
	fgets(agencia2, TAM_AGENCIA, stdin);
	agencia2 [strcspn (agencia2, "\n")] = '\0';
	
	int idx2= buscarConta(contas, qtd, numero2, agencia2);
	
	if (idx2 == -1)
			{
				printf ("Conta destino nao foi encontrada!\n");
				return;
			}
			
	if (contas[idx2].status == ENCERRADA) 
	{
    printf("Conta encerrada nao permite operacoes.\n");
    return;
	}
	
	printf ("Digite o valor da transferencia:");
	if (scanf("%lf", &valor) !=1) 
	{
		printf ("Entrada invalida\n");
		return;
	}
	
	if (valor <= 0)
		{
			printf ("valor invalido!");
			return;
		}
	if (valor>contas[idx1].saldo)
		{
			printf ("Saldo insuficiente.\n");
			return;
		}
		
	contas [idx1].saldo -=valor;
	contas [idx2].saldo +=valor;
	printf ("Transacao feita com exito\n");
	}
void consultar(Conta contas[], int qtd)
	{
	int numero, op;
	char agencia[TAM_AGENCIA], cpf[TAM_CPF];
	
	printf ("Consultar por:\n 1) Numero + Agencia\n 2)CPF\nEscolha:");
	if (scanf ("%d", &op) !=1)
	{
		printf ("Entrada invalida.\n");
		return;
	}
	getchar();
	
	int idx = -1;
	 if(op == 1)
	{
	printf ("Digite o numero da sua conta bancaria:");
	if (scanf("%d", &numero) != 1)
	{
		printf ("Entrada invalida.!\n");
		return;
	}
	getchar();	
		
	printf ("Digite o numero da sua agencia:");
	fgets (agencia, TAM_AGENCIA, stdin);
	agencia [strcspn (agencia, "\n")] = '\0';
	
	idx = buscarConta (contas, qtd, numero, agencia);
	} 
	else if (op == 2)
	{
	printf ("digite o CPF: ");
	fgets (cpf, TAM_CPF,stdin);
	cpf[strcspn(cpf, "\n")] = '\0';

	// valida CPF antes de buscar
	if (!validar_cpf(cpf)) {
		printf("cpf invalido\n");
		return;
	}

	idx = BuscarPorCPF (contas, qtd, cpf);
	}
	 else 
	{
	printf ("Opcao invalida\n");
	return;
	}
		
	if (idx == -1)
		{
			printf ("Conta nao encontrada!\n");
			return;
		}
	printf ("\n Dados da conta \n");
	printf("Conta: %d\n", contas[idx].numero);
	printf("Nome: %s\n", contas[idx].nome);
	printf("CPF: %s\n", contas[idx].cpf);
	printf("Agencia: %s\n", contas[idx].agencia);
	printf("Telefone: %s\n", contas[idx].telefone);
	printf("Saldo: %.2lf\n", contas[idx].saldo);
	printf("Status: %s\n", contas[idx].status == ATIVA ? "Ativa" : "Encerrada"); //se for verdadeira aparece ativo e se for falso aparece encerrado
	}
void alterar(Conta contas[], int qtd)
	{
	int numero, op;
	char agencia [TAM_AGENCIA];
	
	printf ("Digite o numero da sua conta bancaria:");
	scanf ("%d", &numero);
	getchar();
	
	printf ("Digite o numero da sua agencia:");
	fgets (agencia, TAM_AGENCIA, stdin);
	agencia [strcspn (agencia, "\n")] = '\0';
	
	int idx = buscarConta (contas, qtd, numero, agencia);
	if (idx == -1)
		{
			printf ("conta não não foi encontrada!");
			return;
		}
		
	if (contas[idx].status == ENCERRADA) 
	{
    printf("Conta encerrada nao permite operacoes.\n");
    return;
	}
		while (1)
		{
			printf ("Digite o  numero de acordo com o que deseja alterar:1) Telefone\n 2) Agencia\n 0)Sair\n Escolha: ");
		if	(scanf ("%d", &op) != 1) 
		{
			printf ("Entrada invalida. \n");
			return;
		}
			getchar();
			
			if (op == 0)
				break;
			switch (op)
				{
					case 1:
					printf ("Novo telefone:");
					fgets(contas[idx].telefone,TAM_TELEFONE,stdin);
					contas[idx].telefone[strcspn(contas[idx].telefone, "\n")] = '\0';
					if (!validar_telefone(contas[idx].telefone)) {
						printf("numero invalido\n");
					} else {
						printf ("Telefone atualizado com sucesso!\n");
					}
					break;
					case 2:
					printf ("Nova agencia: ");
					fgets(contas[idx].agencia,TAM_AGENCIA,stdin);
					contas[idx].agencia[strcspn(contas[idx].agencia, "\n")] = '\0';
					printf ("Agencia atualizada com sucesso!\n");
					break;
					
					default:
					printf ("opcao invalida!\n");
				}
		}
	}
void listarContas(Conta contas[], int qtd, int filtro_status)
{
	int encontrou = 0;
    printf("Listar contas: \n");

    for (int i = 0; i < qtd; i++)
    {
        if (filtro_status == -1 || contas[i].status == filtro_status) 
        {
        	encontrou = 1;
            printf("\nConta: %d\n", contas[i].numero);
            printf("Nome: %s\n", contas[i].nome);
            printf("CPF: %s\n", contas[i].cpf);
            printf("Agencia: %s\n", contas[i].agencia);
            printf("Telefone: %s\n", contas[i].telefone);
            printf("Saldo: %.2lf\n", contas[i].saldo);
            printf("Status: %s\n", 
                contas[i].status == ATIVA ? "Ativa" : "Encerrada");
        }
    }
    if (!encontrou)
    {
    	printf ("\n Nenhuma conta encontrada com esse filtro. \n");
	}

    printf("Fim da Lista\n");
}
void encerrarConta (Conta contas[], int qtd)
{
	int numero;
	char agencia[TAM_AGENCIA];
	
	printf ("Digite o numero da conta que voce deseja encerrar:");
	if (scanf("%d", &numero) !=1)
	{
		printf ("Entrada invalida\n");
		return;
	}
	getchar ();
	
	printf ("Digite o numero da agencia: ");
	fgets (agencia, TAM_AGENCIA, stdin);
	agencia [strcspn (agencia, "\n")] = '\0';
	
	int idx = buscarConta(contas, qtd, numero, agencia); 
	if (idx == -1)
	{
		printf ("Conta não encontrada!\n");
		return;
	}
	if (contas[idx].status == ENCERRADA)
	{
		printf ("Conta ja esta encerrada\n");
		return;
	}
	if (contas[idx].saldo !=0.0)
	{
		printf ("Nao e possivel encerrar a conta: saldo deve estar zerado!\n");
		return;
	}
	contas[idx].status = ENCERRADA;
	printf ("Conta encerrada com sucesso!\n");
}

/*
===============================================
 INSTRUÇÕES DE COMPILAÇÃO E EXECUÇÃO (LINUX/WINDOWS)
===============================================
Compile o programa usando o GCC:

    gcc banco.c -o banco

Execute o programa:

    ./banco     (Linux/Mac)
    banco.exe   (Windows)

Observação:
- Certifique-se de que o arquivo esteja salvo como "banco.c".
- O programa não usa bibliotecas externas.
- Funciona em qualquer compilador C padrão (C99+).

===============================================
VIA VSCODE (Extensões C/C++ ou Code Runner):
===============================================
Certifique-se de que a extensão C/C++ (Microsoft) e o compilador GCC
 estejam instalados no seu sistema.
 Use o atalho F5 (Iniciar Depuração) ou Ctrl+F5 (Executar sem Depuração)
 para compilar e executar o código diretamente, utilizando as configurações
 automáticas do VS Code (tasks.json e launch.json).
 
===============================================
 VIA TERMINAL INTEGRADO DO VS CODE (Comando GCC):
===============================================
 Abra o Terminal Integrado (Ctrl + `).
 Para compilar (gerar o executável):
 gcc banco_simples.c -o banco
 Para executar o programa:
 ./banco (Linux/macOS)
 banco.exe (Windows)
===============================================
*/

int main()
{
	Conta contas[MAX_CONTAS];
	int qtd_contas = 0, op;
		do
			{
				printf ("bem vindo ao banco TOP4! \n Menu:\n");
				printf (" 1) Abrir conta\n 2) Depositar\n 3) Sacar\n 4) Transferir\n 5) Consultar saldo e dados\n 6) Atualizar dados do cliente\n 7)Listar contas\n 8) Encerrar conta\n 9) Sair\n");
				printf ("Escolha: ");
				if (scanf("%d", &op) != 1)
				{
					printf ("Entrada invalida. Encerrando.\n");
					break;
				}
				getchar();
				
				switch (op)
					{
						case 1:
							//abrir conta
							abrirConta(contas, &qtd_contas);
							break;
						case 2:
							//Depositar
							 depositar(contas, qtd_contas);
							break;
						case 3:
							//Sacar
							sacar(contas, qtd_contas);
							break;
						case 4:
							//Transferir
							transferencias(contas, qtd_contas);
							break;
						case 5:
							consultar(contas, qtd_contas);
							//Consultar saldo e dados
							break;
						case 6:
							alterar(contas, qtd_contas);
							//Atualizar dados do cliente
							break;
						case 7:
						{
							int filtro;
							
							printf ("Listar:\n 1) Apenas ativas\n 2) Apenas Encerradas\n 3) Todas\n Escolha:");
							if (scanf("%d", &filtro) !=1)
							{
								printf ("Entrada invalida\n");
								getchar();
								break;
							}
							getchar();
							
							if (filtro == 1)
							listarContas(contas, qtd_contas, ATIVA);
							else if (filtro == 2)
							listarContas(contas, qtd_contas, ENCERRADA);
							else
							 listarContas(contas, qtd_contas, -1);
							//Listar contas
						}
							break;
						case 8:
							encerrarConta (contas, qtd_contas);
							//Encerrar conta
							break;
						case 9:
							//Sair
							printf ("Saindo... \n");
							break;					
						default:
						printf ("Opcao invalida!\n");				
					}
			}
		while (op!=9);

return 0;
}
