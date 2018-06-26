#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

// Constante Global
#define MAX 100

// Tipos de Dados
typedef struct{
    int nColunas,
        nLinhas,
        nPalavras,
        nLeituras,
        acompanha,
        contagem,
        cFaltam,
        binM[MAX][MAX],
        binL[MAX];
    char nomesArq[MAX][MAX],
         matriz[MAX][MAX],
         lista[MAX][MAX],
         faltam[MAX][MAX],
         generate[MAX*10][2*MAX];
} infos;

// Prototipos
int subStart();
void subDimencoes(infos *);
void subAleat(infos *);
void subLinear(infos *);
void subPalavras(infos *);
void subLerMatriz(infos *);
void subNumberListas(infos *);
void subLerListas(infos *);
void subManual(infos *);
void subBase(infos *);
void subAchar(infos *);
void subEnfim(infos *);
void subCor(infos *);
void subConsertar(infos *);


// Programa Principal
int main (int argc, char *argv[]){

    infos all;
    int i;
    int op = subStart();

    if(op==0){
        subDimencoes(&all);
        subAleat(&all);
        subLinear(&all);
        subCor(&all);
        subPalavras(&all);
    }
    else if(op==1){
        subLerMatriz(&all);
        subNumberListas(&all);
        for(all.acompanha=0; all.acompanha<all.nLeituras; all.acompanha++){
            subLerListas(&all);
            subBase(&all);
            subAchar(&all);
            subEnfim(&all);
            subCor(&all);
            printf("\n\n");
            subConsertar(&all);
            subCor(&all);
        }
    }
    else if(op==2){
        subDimencoes(&all);
        subManual(&all);
        subBase(&all);
        subAchar(&all);
        subEnfim(&all);
        subCor(&all);
    }
    else printf("opcao NAO valida!!!!\n");

    return 0;
}





// Objetivo: Definição de como o programa realizará o caça palavras
// Parâmetros formais
// - não há (parâmetro de saída de dados)
// Valor de Retorno:
// - opcao: opção escolhida pelo usuário
int subStart(){

    // Variáveis Locais
    int opcao;

    // Impressão das possíveis opções do caça palavras
    printf("Escolha o modo de criacao do caca palavras:\n");
    printf("\t - Criar matriz e palavras aleatorias (0)\n");
    printf("\t - Abrir arquivos de matriz e palavras (1)\n");
    printf("\t - Inserir dados manualmente (2)\n\n");

    // Análise da escolha do usuário
    scanf("%d", &opcao);

    return opcao;
}



// Objetivo: Definir dimenções do caça palavras
// Parâmetros formais
// - p: conjunto de dados (parâmentro de saída de dados)
// Valor de Retorno:
// - não há (procedimento)
void subDimencoes(infos *p){

    // Ler tamanho da matriz
    printf("Informe o numero de linhas: ");
    scanf("%d", &p->nLinhas);
    printf("Informe o numero de colunas: ");
    scanf("%d", &p->nColunas);

    // Ler número de palavras
    printf("Informe o numero de palavras: ");
    scanf("%d", &p->nPalavras);
    printf("\n");

    return;
}



// Objetivo: Criar uma matriz totalmente aleatória
// Parâmetros formais
// - p: conjunto de dados (parâmentro de saída de dados)
// Valor de Retorno:
// - não há (procedimento)
void subAleat(infos *p){

    // Inicializar gerador de números aleatórios
    srand(time(NULL));

    // Contadores
    int i, j;

    // Criação da matriz de inteiros correspondentes às letras maiúsculas da tabela ASCII
    for(i=0; i<p->nLinhas; i++){
        for(j=0; j<p->nColunas; j++){
            p->matriz[i][j]=(rand()%26)+(65);
        }
    }

    return;
}


// Objetivo:
// Parâmetros formais
// - p: conjunto de dados (parâmentro de saída de dados)
// Valor de Retorno:
// - não há (procedimento)
void subPalavras(infos *p){
    int i,
        j=0,
        c;
    //


    // Se a palavra tem tamanho minimo
    for(i=0; i<p->contagem; i++){
        int k=strlen(p->generate[i]);
        if(k>3){
            memcpy(p->lista[j], p->generate[i], k/2);
            j++;
        }
        if(j==p->nPalavras) break;    
    }
    
    // Impressao de lista aleatoria
    printf("LISTA ALEATORIA\n\n");
    for(i=0; i<p->nPalavras; i++){
        printf("%s\n", p->lista[i]);
    }
}


// Objetivo: Ler os arquivos que contém a matriz do caça palavras
// Parâmetros formais
// - p: conjunto de dados (parâmentro de saída de dados)
// Valor de Retorno:
// - não há (procedimento)
void subLerMatriz(infos *p){

    // Contadores
    int i, j;

    // Variável Local
    char nome[1][MAX];

    // Armazenamento do nome dos arquivos
    fflush(stdin);
    printf("Insira o NOME do arquivo da matriz (sem extensao):\n");
    gets(nome[0]);
    fflush(stdin);

    strcat(nome[0], ".txt");

    // Leitura arquivo da matriz
    FILE *arquivoX;
    arquivoX = fopen(nome[0], "r");

    fscanf(arquivoX, "%d", &p->nLinhas);
    fscanf(arquivoX, "%d", &p->nColunas);
    fgetc(arquivoX);

    for(i=0; i<p->nLinhas; i++){
        for(j=0; j<p->nColunas; j++){
            fscanf(arquivoX ,"%c ", &p->matriz[i][j]);
        }
    }
    fclose(arquivoX);

    printf("\n");

    return;
}


// Objetivo: Ler os a quantidade e o nome das listas com as palavras do caça palavras
// Parâmetros formais
// - p: conjunto de dados (parâmentro de saída de dados)
// Valor de Retorno:
// - não há (procedimento)
void subNumberListas(infos *p){
    
    // Contadores
    int i,
        j;
    //

    // Armazenamento do numero de listas dos arquivos
    fflush(stdin);
    printf("Insira o NUMERO DE LISTAS a serem lidas: ");
    scanf("%d", &p->nLeituras);
    fflush(stdin);

    printf("\n");

    // Armazenamento do nome das listas
    for(i=0; i<p->nLeituras; i++){
        printf("Insira o nome do arquivo da %da lista de palavras (sem extensao):\n", i+1);
        gets(p->nomesArq[i]);
        strcat(p->nomesArq[i], ".txt");
        fflush(stdin);
    }

    printf("\n\n\n");
}



// Objetivo: Ler os arquivos que contém a lista do caça palavras completo
// Parâmetros formais
// - p: conjunto de dados (parâmentro de saída de dados)
// Valor de Retorno:
// - não há (procedimento)
void subLerListas(infos *p){

    int i;

    // Leitura arquivo de palavras
    FILE *arquivoX;
    arquivoX = fopen(p->nomesArq[p->acompanha], "r");

    fscanf(arquivoX, "%d", &p->nPalavras);

    for(i=0; i<p->nPalavras; i++){
        fscanf(arquivoX, "%s", &p->lista[i]);
    }
    fclose(arquivoX);

    return;
}



// Objetivo: Inserir a matriz do caça palaras e suas palavras manualmente
// Parâmetros formais
// - p: conjunto de dados (parâmentro de saída de dados)
// Valor de Retorno:
// - não há (procedimento)
void subManual(infos *p){

    // Contadores
    int i, j;

    // Inserção da matriz
    for (i=0; i<p->nLinhas; i++) {
        printf("Digite as letras da %da linha\n", i+1);
        for (j=0; j <p->nColunas; j++) {
        scanf(" %c", &p->matriz[i][j]);
        }
    }

    // Quebra de linha estética
    printf("\n");

    // Inserção das palavras
    for (i=0; i<p->nPalavras; i++){
		printf("Digite a %da palavra: ", i+1);
		fflush (stdin);
		gets(p->lista[i]);
		fflush (stdin);
	}

    return;
}



// Objetivo: zerar a matriz e a lista binaria
// Parâmetros formais
// - p: conjunto de dados (parâmentro de saída de dados)
// Valor de Retorno:
// - não há (procedimento)
void subBase(infos *p){

    int i, j;

    // zerando matriz binária
    for(i=0; i<p->nLinhas; i++){
        for(j=0; j<p->nColunas; j++){
            p->binM[i][j]=0;
        }
    }

    // zerando lista binária
    for(i=0; i<p->nPalavras; i++){
        p->binL[i]=0;
    }

    return;
}



// Objetivo: Achar as palavras e indicar na matriz binária
// Parâmetros formais
// - p: conjunto de dados (parâmentro de saída de dados)
// Valor de Retorno:
// - não há (procedimento)
void subAchar(infos *p){

    // Contadores
    int i,
        j,
        k,
        l,
        m,
        ct,
        intervalo,
        temp,
        contador=0;
    char *chave;
    

    // Linhas
    for(i=0; i<p->nLinhas; i++){
        char hype[2*MAX];
        for(j=0; j<p->nColunas; j++){
            hype [contador] = p->matriz[i][j];          // vetor temporario recebe parte da matriz
            contador++;
        }
        hype[contador]='\0';

        for(k=0; k<p->nPalavras; k++){
            chave=strstr(hype, p->lista[k]);
            if(chave!=NULL){                            // se achou a palavra
                p->binL[k]=1;
                ct=0;
                for (char *aux=hype; aux<chave; ++aux){
                    ct++; 
                }
                for(l=ct; l<strlen(p->lista[k])+ct; l++){
                    p->binM[i][l]=1;
                }
            }
        }
        contador=0;
    }
        
    
    // Linhas Opostas
    contador=0;
    for(i=0; i<p->nLinhas; i++){
        char hype[2*MAX];

        for(j=p->nColunas-1; j>=0; j--){
            hype[contador] = p->matriz[i][j];           // vetor temporario recebe parte da matriz
            contador++;
        }
        hype[contador]='\0';
        
        for(k=0; k<p->nPalavras; k++){
            chave=strstr(hype, p->lista[k]);
            if(chave!=NULL){                            // se achou a palavra
                p->binL[k]=1;
                int tamPlv = strlen(p->lista[k]);               //tamanho palavra achada
                ct=0;
                for (char *aux=hype; aux<chave; ++aux){
                    ct++; 
                }
                int inicPlv = p->nColunas-1-ct;

                for(j=inicPlv; j>inicPlv-tamPlv; j--){
                    p->binM[i][j]=1;
                } 
            }
        }
        contador=0;
    }
    

    // Colunas    
    contador=0;
    for(j=0; j<p->nColunas; j++){
        char hype[2*MAX];

        for(i=0; i<p->nLinhas; i++){
            hype[contador] = p->matriz[i][j];           // vetor temporario recebe parte da matriz
            contador++;
        }
        hype[contador]='\0';

        for(k=0; k<p->nPalavras; k++){
            chave=strstr(hype, p->lista[k]);

            if(chave!=NULL){                            // se achou a palavra
                p->binL[k]=1;

                int tamPlv = strlen(p->lista[k]); 

                ct=0;
                for (char *aux=hype; aux<chave; ++aux){
                    ct++; 
                }

                for(l=ct; l<tamPlv+ct; l++){
                    p->binM[l][j]=1;
                }
            }
        }
        contador=0;

    }


    // Colunas Opostas
    contador=0;
    for(j=0; j<p->nColunas; j++){
        char hype[2*MAX];

        for(i=p->nLinhas-1; i>=0; i--){
            hype[contador] = p->matriz[i][j];           // vetor temporario recebe parte da matriz
            contador++;
        }
        hype[contador]='\0';

        for(k=0; k<p->nPalavras; k++){
            chave=strstr(hype, p->lista[k]);

            if(chave!=NULL){                            // se achou a palavra
                p->binL[k]=1;
                ct=0;
                for (char *aux=hype; aux<chave; ++aux){
                    ct++; 
                }

                int tamPlv = strlen(p->lista[k]);
                int inicPlv = p->nLinhas-1-ct;

                for(l=inicPlv; l>inicPlv-tamPlv; l--){
                    p->binM[l][j]=1;
                }                
            }
        }
        contador=0;

    }


    // Diagonal Direita
    contador=0;
    intervalo=0;
    temp=p->nColunas-1;
    for(m=0; m<p->nLinhas+p->nColunas-1; m++){
        char hype[2*MAX];

        for(i=0; i<p->nLinhas; i++){
            for(j=p->nColunas-1; j>=0; j--){
                if(j-i==temp){
                    hype[contador] = p->matriz[i][j];   // vetor temporario recebe parte da matriz
                    contador++;
                }
            }
        }
        hype[contador]='\0';

        for(k=0; k<p->nPalavras; k++){
            chave=strstr(hype, p->lista[k]);

            if(chave!=NULL){                            // se achou a palavra
                p->binL[k]=1;

                int tamPlv = strlen(p->lista[k]); 

                ct=0;
                for (char *aux=hype; aux<chave; ++aux){
                    ct++;
                }

                for(i=0; i<p->nLinhas; i++){
                    for(j=p->nColunas-1; j>=0; j--){
                        if(j-i==temp){
                            if(intervalo>=ct && intervalo<ct+tamPlv){
                                p->binM[i][j]=1;
                            }
                            intervalo++;
                        }
                    }
                }
            }
        }
        intervalo=0;
        contador=0;
        temp--;
    }
   
    
    // Diagonal Direita Oposta
    contador=0;
    intervalo=0;
    temp=p->nColunas-1;
    for(m=0; m<p->nLinhas+p->nColunas-1; m++){
        char hype[2*MAX];

        for(j=p->nColunas-1; j>=0; j--){
            for(i=0; i<p->nLinhas; i++){
                if(j-i==temp){
                    hype[contador] = p->matriz[i][j];   // vetor temporario recebe parte da matriz
                    contador++;
                }
            }
        }
        hype[contador]='\0';

        for(k=0; k<p->nPalavras; k++){
            chave=strstr(hype, p->lista[k]);

            if(chave!=NULL){                            // se achou a palavra
                p->binL[k]=1;

                int tamPlv = strlen(p->lista[k]); 
                
                ct=0;
                for (char *aux=hype; aux<chave; ++aux){
                    ct++;
                }

                for(j=p->nColunas-1; j>=0; j--){
                    for(i=0; i<p->nLinhas; i++){
                        if(j-i==temp){
                            if(intervalo>=ct && intervalo<ct+tamPlv){
                                p->binM[i][j]=1;
                            }
                            intervalo++;
                        }
                    }
                }
            }
        }
        intervalo=0;
        contador=0;
        temp--;
    }
    

    // Diagonal Esquerda
    contador=0;
    intervalo=0;
    for(m=0; m<p->nLinhas+p->nColunas-1; m++){
        char hype[2*MAX];

        for(i=0; i<p->nLinhas; i++){
            for(j=0; j<p->nColunas; j++){
                if(j+i==m){
                    hype[contador] = p->matriz[i][j];   // vetor temporario recebe parte da matriz
                    contador++;
                }
            }
        }
        hype[contador]='\0';

        for(k=0; k<p->nPalavras; k++){
            chave=strstr(hype, p->lista[k]);

            if(chave!=NULL){                            // se achou a palavra
                p->binL[k]=1;

                int tamPlv = strlen(p->lista[k]); 

                ct=0;
                for (char *aux=hype; aux<chave; ++aux){
                    ct++;
                }

                for(i=0; i<p->nLinhas; i++){
                    for(j=0; j<p->nColunas; j++){
                        if(j+i==m){
                            if(intervalo>=ct && intervalo<ct+tamPlv){
                                p->binM[i][j]=1;
                            }
                            intervalo++;
                        }
                    }
                }
            }
        }
        intervalo=0;
        contador=0;
    }
    

    // Diagonal Esquerda Oposta
    contador=0;
    intervalo=0;
    for(m=0; m<p->nLinhas+p->nColunas-1; m++){
        char hype[2*MAX];

        for(j=0; j<p->nColunas; j++){
            for(i=0; i<p->nLinhas; i++){
                if(j+i==m){
                    hype[contador] = p->matriz[i][j];   // vetor temporario recebe parte da matriz
                    contador++;
                }
            }
        }
        hype[contador]='\0';

        for(k=0; k<p->nPalavras; k++){
            chave=strstr(hype, p->lista[k]);

            if(chave!=NULL){                            // se achou a palavra
                p->binL[k]=1;

                int tamPlv = strlen(p->lista[k]); 

                ct=0;
                for (char *aux=hype; aux<chave; ++aux){
                    ct++;
                }

                for(j=0; j<p->nColunas; j++){
                    for(i=0; i<p->nLinhas; i++){
                        if(j+i==m){
                            if(intervalo>=ct && intervalo<ct+tamPlv){
                                p->binM[i][j]=1;
                            }
                            intervalo++;
                        }
                    }
                }
            }
        }
        intervalo=0;
        contador=0;
    }


    return;
}



// Objetivo: Indicar a completude ou não do caça palavras e as estatisticas
// Parâmetros formais
// - p: conjunto de dados (parâmentro de saída de dados)
// Valor de Retorno:
// - não há (procedimento)
void subEnfim(infos *p){
    
    // variáveis Locais
    int i,
        flag=1;
    //

    p->cFaltam=0;

    for(i=0; i<p->nPalavras; i++){
        if(p->binL[i]!=1){
            flag=0;
            strcpy(p->faltam[p->cFaltam++], p->lista[i]);   // formação da lista das palavras que faltam
        }
    }
        
    printf("\nLISTA DE PALAVRAS %d\n", p->acompanha+1);
    
    // Imprimir a existência ou não do caça palavras
    if(flag==1){
        printf("Caca palavras contem todas as palavras!!\n");
        printf("100%% das palavras achadas!!!!\n");
    }
    else if (flag==0){      // Caso não esteja completo
        double prob = (double)100*(p->nPalavras - p->cFaltam)/p->nPalavras;
        printf("Caca palavras NAO contem todas as palavras!!\n\n%.2lf %% achadas\n%.2lf %% nao achadas\n\n\nPalavras nao achadas:\n", prob, 100-prob);
        for(i=0; i<p->cFaltam; i++){
            printf("%s\n", p->faltam[i]);
        }
    }
}




// Objetivo: Imprimar o caça palavras com cor
// Parâmetros formais
// - p: conjunto de dados (parâmentro de saída de dados)
// Valor de Retorno:
// - não há (procedimento)
void subCor(infos *p){

    // Contadores
    int i, j;
    
    // Inicializa/Cria variaveis
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    // Salva a cor atual da tela
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    printf("\n\n");
    for(i=0; i<p->nLinhas; i++){
        for(j=0; j<p->nColunas; j++){
            if(p->binM[i][j]==1){           // se letra foi mafrcada como achada
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                printf("%c%c", p->matriz[i][j], j==p->nColunas-1?'\n':' ');
                SetConsoleTextAttribute(hConsole, saved_attributes);
            }
            else    printf("%c%c", p->matriz[i][j], j==p->nColunas-1?'\n':' ');
        }
    }


    // Volta a cor ao normal, caso haja algum erro
    SetConsoleTextAttribute(hConsole, saved_attributes);
}




// Objetivo: Linearizar a matriz principal em um vetor em todos os sentidos
// Parâmetros formais
// - p: conjunto de dados (parâmentro de saída de dados)
// Valor de Retorno:
// - não há (procedimento)
void subLinear(infos *p){

    // Variável Local
    int i,
        j,
        k,
        x, 
        temp=p->nColunas-1;
    //

    p->contagem=0;

    // Linearização em linhas
    for(i=0; i<p->nLinhas; i++){
        x=0;
        for(j=0; j<p->nColunas; j++){
            p->generate[p->contagem][x] = p->matriz[i][j];
            x++;
        }
        p->generate[p->contagem][x] = '\0';
        p->contagem++;
    }
    

    // Linearização em colunas
    for(j=0; j<p->nColunas; j++){
        x=0;
        for(i=0; i<p->nLinhas; i++){
            p->generate[p->contagem][x] = p->matriz[i][j];
            x++;
        }
        p->generate[p->contagem][x] = '\0';
        p->contagem++;
    }   


    //Linearização Oposta em Linhas
    for(i=0; i<p->nLinhas; i++){
        x=0;
        for(j=p->nColunas-1; j>=0; j--){
            p->generate[p->contagem][x] = p->matriz[i][j];
            x++;
        }
        p->generate[p->contagem][x] = '\0';
        p->contagem++;
    }
    


    //Linearização Oposta em Colunas
    for(i=0; i<p->nColunas; i++){
        x=0;
        for(j=p->nLinhas-1; j>=0; j--){
            p->generate[p->contagem][x] = p->matriz[j][i];
            x++;
        }
        p->generate[p->contagem][x] = '\0';
        p->contagem++;
    }
    


    //Linearização em Diagonal direita
    for(i=0; i<p->nLinhas+p->nColunas-1; i++){ 
        x=0;       
        for(j=0; j<p->nLinhas; j++){
            for(k=p->nColunas-1; k>=0; k--){
                if(k-j==temp){
                    p->generate[p->contagem][x] = p->matriz[j][k];
                    x++;
                }
            }
        }
        p->generate[p->contagem][x] = '\0';        
        temp--;
        p->contagem++;
    }
    
    

    //Linearização Oposta em Diagonal direita
    temp=p->nColunas-1;

    for(i=0; i<p->nLinhas+p->nColunas-1; i++){
        x=0;
        for(k=p->nColunas-1; k>=0; k--){
            for(j=0; j<p->nLinhas; j++){
                if(k-j==temp){
                    p->generate[p->contagem][x] = p->matriz[j][k];
                    x++;
                }
            }
        } 
        p->generate[p->contagem][x] = '\0';       
        temp--;
        p->contagem++;
    }
    


    //Linearização em Diagonal esquerda
    for(i=0; i<p->nLinhas+p->nColunas-1; i++){
        x=0;
        for(j=0; j<p->nLinhas; j++){
            for(k=0; k<p->nColunas; k++){
                if(k+j==i){
                    p->generate[p->contagem][x] = p->matriz[j][k];
                    x++;
                }
            }
        }
        p->generate[p->contagem][x] = '\0';
        p->contagem++;
    }
    

    // Linearização Oposta em Diagonal esquerda
    for(i=0; i<p->nLinhas+p->nColunas-1; i++){
        x=0;
        for(k=0; k<p->nColunas; k++){
            for(j=0; j<p->nLinhas; j++){
                if(k+j==i){
                    p->generate[p->contagem][x] = p->matriz[j][k];
                    x++;
                }
            }
        }
        p->generate[p->contagem][x] = '\0';
        p->contagem++;
    }

    return;
}




// Objetivos: consertar a matriz com as palavras que faltam
// Parâmetros formais
// - p: conjunto de dados (parâmentro de saída de dados)
// Valor de Retorno:
// - não há (procedimento)
void subConsertar(infos *p){
    
    // Variãveis Locais
    int i,
        j,
        m,
        posX,
        posY;
    char name[1];

    srand(time(NULL));
    fflush(stdin);
    printf("Deseja arrumar a matriz?? (y to yes//n to no)\t");
    scanf("%d", &name[0]);
    fflush(stdin);

    // Se não é pra arrumar:
    if(name[0]=='n') return;


    // Caso seja necessário concertar
    for(i=0; i<p->cFaltam; i++){
        m=0;
        while(m<strlen(p->faltam[i])){
            posX = rand() % p->nLinhas;
            posY = rand() % p->nColunas;

            while(posY+strlen(p->faltam[i])>p->nColunas) posY = rand() % p->nColunas;

            for(j=0; j<strlen(p->faltam[i]); j++){
                if(p->binM[posX][posY+j]==1){
                    m=0;
                    break;
                }
                else if(p->binM[posX][posY+j]==0) m++;
            }

            for(j=0; j<strlen(p->faltam[i]); j++){
                p->matriz[posX][posY+j]=p->faltam[i][j];
                p->binL[i]=1;
                p->binM[posX][posY+j]=1;
            }
        }
    }



    return;
}