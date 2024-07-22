// Tema: ACADEMIA
// Feito por Felipe Uemura
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define tam 1 // -> tamanho da alocacao dinamica
// Registro de dados a pedir ao usuario
struct usuarios{
    char cpf[12];
    char nome[50];
    char email[50];
    char telefone[12];
    char cep[9];
    char plano[20];
};
// Funcao para validar CPF
int validacaoCpf(char *cpf) {

    int i, d1 = 0, d2 = 0;
    // verifica a quantia e caracteres
    if(strlen(cpf) != 11){
        return 1;
    }

    for(i = 0; i < 9; i++){
        d1 += (cpf[i] - 48) * (10 - i);
    }
    for(i = 0; i < 10; i++){
        d2 += (cpf[i] - 48) * (11 - i);
    }

    d1 = (d1 * 10) % 11;
    d2 = (d2 * 10) % 11;

    if(d1 == 10){
        d1 = 0;
    }

    if(d1 == (cpf[9] - 48)){
        if(d2 == (cpf[10] - 48)){
            return 0; 
        }
    }
    return 1;
}
// Funcao para criar conta, ponteiro em nUsuarios para funcao possa modificar o valor nUsuarios
int criarConta(struct usuarios *vetUsuario, int *nUsuarios){
    // Aumenta o tamanho do vetor de structs conforme adiciona nUsuarios, realocando vetUsuario em vetNovoUsuario
    struct usuarios *vetNovoUsuario = (struct usuarios*)realloc(vetUsuario, (*nUsuarios + 1)* sizeof(struct usuarios));
    // Abertura do arquivo para armazenamento do cadastro
    FILE *cadastros = fopen("cadastros.txt", "a+");
    char cpfAUX[12];

    if(cadastros == NULL){
        printf("Erro na abertura do arquivo!\n");
        return -1;
    }
    // validacao do cpf na criacao do cadastro
    printf("Informe seu CPF: \n");
    scanf("%s", cpfAUX);

    while(validacaoCpf(cpfAUX) != 0){
        printf("\nErro, informe um cpf válida: ");
        scanf("%s", cpfAUX);
    }

    strcpy(vetUsuario[*nUsuarios].cpf, cpfAUX);

    fprintf(cadastros, "Cpf: %s\n", vetUsuario[*nUsuarios].cpf);

    // Nome do usuario
    printf("Informe o seu nome: \n");
    scanf(" %[^\n]", vetUsuario[*nUsuarios].nome);
    fprintf(cadastros, "Nome: %s\n", vetUsuario[*nUsuarios].nome);
    // E-mail do usuario
    printf("Informe o seu e-mail: \n");
    scanf(" %[^\n]", vetUsuario[*nUsuarios].email);
    fprintf(cadastros, "E-mail: %s\n", vetUsuario[*nUsuarios].email);
    // Telefone do usuario
    printf("Informe o seu telefone: \n");
    scanf(" %[^\n]", vetUsuario[*nUsuarios].telefone);
    fprintf(cadastros, "Telefone: %s\n", vetUsuario[*nUsuarios].telefone);
    // Cep do usuario
    printf("Informe o seu CEP: \n");
    scanf(" %[^\n]", vetUsuario[*nUsuarios].cep);
    fprintf(cadastros, "CEP: %s\n", vetUsuario[*nUsuarios].cep);
    fprintf(cadastros, "\n");
    // adiciona o proximo cadastro na proxima posicao do vetor
    *nUsuarios = *nUsuarios + 1;

    if(fclose(cadastros) == 0){
        return 0;
    }
}
// Funcao para verificacao de conta
void consultarConta(struct usuarios *vetUsuario, int *nUsuarios){

    char buscaCpf[12];
    int i;
    // Verificar se tem usuarios para consultar
    if(*nUsuarios > 0){
        // Repeticao ate o usuario informar um cpf valido
        printf("\n--->Informe o cpf da conta que deseje localizar: \n");
        scanf("%s", buscaCpf);

        while(validacaoCpf(buscaCpf) != 0){
            printf("Erro, informe um cpf válida: ");
            scanf("%s", buscaCpf);
        }
        for(i = 0; i < *nUsuarios; i++){
            if(strcmp(buscaCpf, vetUsuario[i].cpf) == 0){
                printf("Cpf: %s\n", vetUsuario[i].cpf);
                printf("Nome: %s\n", vetUsuario[i].nome);
                printf("E-mail: %s\n", vetUsuario[i].email);
                printf("Telefone: %s\n", vetUsuario[i].telefone);
                printf("Cep: %s\n", vetUsuario[i].cep);
                break;
            }
        }
    }else{
        printf("\nNao ha usuarios cadastrados.\n");
    }
}
// Funcao para excluir conta
void excluirConta(struct usuarios *vetUsuario, int *nUsuarios){

    char excluirCpf[12];
    int i, j;
    // Verificar se tem usuarios para consultar
    if(*nUsuarios > 1){
        // Informe e valida o cpf
        printf("\n--->Informe o cpf da conta que deseje excluir: \n");
        scanf("%s", excluirCpf);

        while(validacaoCpf(excluirCpf) != 0){
            printf("Erro, Informe um cpf válida: ");
            scanf("%s", excluirCpf);
        }
            for(i = 0; i < *nUsuarios; i++){
                if(strcmp(excluirCpf, vetUsuario[i].cpf) == 0){
                    for (j = i + 1; j < *nUsuarios; j++){ 
                        vetUsuario[j - 1] = vetUsuario[j];
                    }
                }
            }
    }else{
        *nUsuarios = 0;
    }
    *nUsuarios = *nUsuarios - 1;
    printf("A conta foi excluida!\n");
}
// Funcao para desativar conta
void desativarConta(struct usuarios *vetUsuario, int *nUsuarios){
    // Abre arquivo para armazenar contas desativadas
    FILE *desativados = fopen("desativados.txt", "a+");
    char desativarCpf[12];
    int i, j;

    if(desativados == NULL){
        printf("ERRO : arquivo nao foi aberto!\n");
        exit(1);
    }
    // Verificar se tem usuarios para consultar
    if(*nUsuarios > 1){
        // Informa e valida o cpf
        printf("Informe o cpf da conta que deseje desativar: ");
        scanf("%s", desativarCpf);

        while(validacaoCpf(desativarCpf) != 0){
            printf("Erro, informe um cpf valido: ");
            scanf("%s", desativarCpf);
        }
        for(i = 0; i < *nUsuarios; i++){
            if(strcmp(desativarCpf, vetUsuario[i].cpf) == 0){
                fprintf(desativados, vetUsuario[i].cpf);
                fprintf(desativados, "\n");
                fprintf(desativados, vetUsuario[i].nome);
                fprintf(desativados, "\n");
                fprintf(desativados, vetUsuario[i].email);
                fprintf(desativados, "\n");
                fprintf(desativados, vetUsuario[i].telefone);
                fprintf(desativados, "\n");
                fprintf(desativados, vetUsuario[i].cep);
                fprintf(desativados, "\n");
                fprintf(desativados, vetUsuario[i].plano);
                fprintf(desativados, "\n");
                fprintf(desativados, "\n");
            }
        }
        for(i = 0; i < *nUsuarios; i++){
            if(strcmp(desativarCpf, vetUsuario[i].cpf) == 0){
                for (j = i + 1; j < *nUsuarios; j++){ 
                    vetUsuario[j - 1] = vetUsuario[j];
                }
            }
        }
    }else{
        *nUsuarios = 0;
    }
    *nUsuarios--;
    printf("A conta foi desativada!\n");

    fclose(desativados);
} 
// Funcao para listar e orndenar as contas cadastradas
void listaConta(struct usuarios *vetUsuario, int *nUsuarios){

    int i, j;
    struct usuarios temp;

    if(*nUsuarios > 0){
        printf("===================================================================\n");
        printf("                                                                   \n");
        printf("                       LISTA DE CONTAS                             \n");
        printf("                                                                   \n");
        printf("===================================================================\n");
        printf("\n");
        // Metodo de ordenacao >Bobble Sort< - le de 2 em 2 fazendo a troca se necessario
        for(i = *nUsuarios - 1; i > 0; i--){
            for(j = 0; j < i; j++){
                if(strcmp(vetUsuario[j].nome, vetUsuario[j + 1].nome) > 0){
                    temp = vetUsuario[j];
                    vetUsuario[j] = vetUsuario[j + 1];
                    vetUsuario[j + 1] = temp;
                }
            }
        }
        for(i = 0; i < *nUsuarios; i++){
            printf("%d - %s\n", i + 1, vetUsuario[i].nome);
        }
        printf("\n");
    }else{
        printf("\nNao ha usuarios cadastrados.\n");
    }
}
void planos(struct usuarios *vetUsuario, int *nUsuarios){

    int plano, op_diario, op_mensal, op_anual, i;
    char cpf[12], diario[7] = "Diario", mensal[7] = "Mensal", anual[6] = "Anual";

    printf("===================================================================\n");
    printf("                                                                   \n");
    printf("                       PLANOS DA ACADEMIA                          \n");
    printf("                                                                   \n");
    printf("===================================================================\n");
    printf("                     [1] - DIARIO                                  \n");
    printf("                     [2] - MENSAL                                  \n");
    printf("                     [3] - ANUAL                                   \n");
    printf("                                                                   \n");
    printf("                     [0] - SAIR                                    \n");
    printf("===================================================================\n");

    printf("\n--->Selecione uma das opcoes: ");
    scanf("%d", &plano);

    switch(plano){
        case 1:
            printf("\n--->DIARIO: Custo: R$25 por Dia<---\n");
            printf("\nDigite '1' caso queira o plano diario, caso queira cancelar, digite '2': \n");
            scanf("%d", &op_diario);

            if(op_diario == 1){
                printf("\nInforme seu cpf: ");
                scanf("%s", cpf);
                while(validacaoCpf(cpf) != 0){
                    printf("\nInforme um cpf valido: ");
                    scanf("%s", cpf);
                }
                for(i = 0; i < *nUsuarios; i++){
                    if(strcmp(vetUsuario[i].cpf, cpf)){
                        strcpy(vetUsuario[i].plano, diario);
                    }
                }
                printf("\n!!!Parabens pela sua escolha!!!\n");
                break;
            }else{
                printf("\nPedido cancelado!\n");
            }
        case 2:
            printf("\n--->MENSAL: Custo: R$80 por Mes<---\n");
            printf("\nDigite '1' caso queira o plano mensal, caso queira cancelar, digite '2': \n");
            scanf("%d", &op_mensal);

            if(op_mensal == 1){
                printf("\nInforme seu cpf: ");
                scanf("%s", cpf);
                while(validacaoCpf(cpf) != 0){
                    printf("\nInforme um cpf valido: ");
                    scanf("%s", cpf);
                }
                for(i = 0; i < *nUsuarios; i++){
                    if(strcmp(vetUsuario[i].cpf, cpf)){
                        strcpy(vetUsuario[i].plano, mensal);
                    }
                }
                printf("\n!!!Parabens pela sua escolha!!!\n");
                break;
            }else{
                printf("\nPedido cancelado!\n");
            }
        case 3:
            printf("\n--->Anual: Custo: R$65 por mes ate final do ano<---\n");
            printf("\nDigite '1' caso queira o plano anual, caso queira cancelar, digite '2': \n");
            scanf("%d", &op_anual);

            if(op_anual == 1){
                printf("\nInforme seu cpf: ");
                scanf("%s", cpf);
                while(validacaoCpf(cpf) != 0){
                    printf("\nInforme um cpf valido: ");
                    scanf("%s", cpf);
                }
                for(i = 0; i < *nUsuarios; i++){
                    if(strcmp(vetUsuario[i].cpf, cpf)){
                        strcpy(vetUsuario[i].plano, anual);
                    }
                }
                printf("\n!!!Parabens pela sua escolha!!!\n");
                break;
            }else{
                printf("\nPedido cancelado!\n");
            }
    }
}
int main(){
    // alocando na memoria o vetor de structs(usuarios)
    struct usuarios *vetUsuario = (struct usuarios*)malloc(tam * sizeof(struct usuarios));

    if(vetUsuario == NULL){
        printf("ERRO : memoria insuficiente!\n");
        return 1;
    }

    int opcao, opcaoSR, opcaoExDes, nUsuarios = 0;

    do{
        printf("===================================================================\n");
        printf("      TTTTTTTTTTTTT     IIIIIIIIIII                                \n");
        printf("            T                I                                     \n");
        printf("            T                I                ACADEMY              \n");
        printf("            T                I                                     \n");
        printf("            T                I                                     \n");
        printf("            T           IIIIIIIIIII                                \n");
        printf("===================================================================\n");
        printf("                     [1] - CADASTRO DA CONTA                       \n");
        printf("                     [2] - LISTA DE CLIENTES                       \n");
        printf("                     [3] - PLANOS                                  \n");
        printf("                                                                   \n");
        printf("                     [0] - SAIR                                    \n");
        printf("===================================================================\n");

        printf("\n--->Selecione uma das opcoes a seguir: ");
        scanf("%d", &opcao);

        if(opcao == 1){
            printf("===================================================================\n");
            printf("                                                                   \n");
            printf("                       CADASTRO DA CONTA                           \n");
            printf("                                                                   \n");
            printf("===================================================================\n");
            printf("                     [1] - CRIAR NOVA CONTA                        \n");
            printf("                     [2] - CONSULTAR CONTA                         \n");
            printf("                     [3] - EXCLUIR/DESATIVAR CONTA                 \n");
            printf("                                                                   \n");
            printf("                     [0] - SAIR                                    \n");
            printf("===================================================================\n");
            
            printf("\n--->Selecione uma das opcoes a seguir: ");
            scanf("%d", &opcaoSR);

            switch(opcaoSR){
                case 1:
                    // Funcao para cadastrar, &nUsuarios atualiza o numero de usuarios criados
                    criarConta(vetUsuario, &nUsuarios);
                    break;
                case 2:
                    // Funcao para verificar conta
                    consultarConta(vetUsuario, &nUsuarios);
                    break;
                case 3:
                    // Funcao para desativar/excluir conta
                    printf("--->Para excluir uma conta digite '1', para desativar uma conta digite '2'.\n");
                    scanf("%d", &opcaoExDes);

                    if(opcaoExDes == 1){
                        excluirConta(vetUsuario, &nUsuarios);
                        break;
                    }else{
                        desativarConta(vetUsuario, &nUsuarios);
                        break;
                    }
                case 0:
                    break;
                default:
                    printf("\nEscolha uma opção válida!\n");
                    break;
                }
        }else if(opcao == 2){
                    listaConta(vetUsuario, &nUsuarios);
        }else if(opcao == 3){
                    planos(vetUsuario, &nUsuarios);
        }else{
            printf("\nEncerrando o programa...");
            exit(0);
        }
    }while(opcao != 0);

    free(vetUsuario);
    
    return 0;
}