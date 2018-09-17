/* --------------------------- *
 * IAED 1o. Projeto, 2017/2018 *
 * Joao Vieira, No. 90739      *
 * --------------------------- */

#include <stdio.h>

#define TAM 10000 /* tamanho maximo da matriz */

typedef struct valor
{
  unsigned long linha, coluna;
  double num;
}Valor;

/* variaveis globais */
int cnt = 0;
unsigned long mini, maxi, minj, maxj, nelem;
double zero = 0;
char nome[80];

/* prototipos das funcoes */
void limites(Valor vetor[TAM]);
void adiciona(Valor vetor[TAM]);
void lista(Valor vetor[TAM]);
void imprime();
void linha(Valor vetor[TAM]);
void coluna(Valor vetor[TAM]);
void selection_linha(Valor a[], int l, int r);
void selection_coluna(Valor a[], int l, int r);
void ordenar(Valor vetor[TAM]);
void zerar(Valor vetor[TAM]);
void recebe(char *nome, Valor vetor[TAM]);
void ficheiro(Valor vetor[TAM]);
void densidade(Valor vetor[TAM], int conta[nelem]);
void comprimir(Valor vetor[TAM]);


int main(int argc, char *argv[])
{

  /* definicao de variaveis */
  Valor vetor[TAM];
  char opcao;

  recebe(argv[1], vetor);

  while((opcao = getchar()) != 'q')
  {
    limites(vetor); /* atualiza os limites da matriz */

    /* opcoes de selecao */
    switch(opcao)
    {
    case 'a': adiciona(vetor);
    break;

    case 'p': lista(vetor);
    break;

    case 'i': imprime();
    break;

    case 'l': linha(vetor);
    break;

    case 'c': coluna(vetor);
    break;

    case 'o': ordenar(vetor);
    break;

    case 'z': zerar(vetor);
    break;

    case 'w': ficheiro(vetor);
    break;

    case 's': comprimir(vetor);
    break;

    opcao = getchar();
    }
  }

  return 0;
}

/*  FUNCAO: LIMITES
 *
 *  calcula os limites maximo e o minimo das
 *  linhas e colunas e o numero de elementos no vetor
 *
 *  mini: limite minimo das linhas
 *  maxi: limite maximo das linhas
 *  minj: limite minimo das colunas
 *  maxj: limite maximo das colunas
 *  nelem: numero de elementos no vetor
 */
void limites(Valor vetor[TAM])
{
  int i;
  nelem = 0;

  mini = vetor[0].linha;
  maxi = vetor[0].linha;
  minj = vetor[0].coluna;
  maxj = vetor[0].coluna;
  for(i = 0; i < cnt; i++)
  {
    if(vetor[i].linha < mini)
      mini = vetor[i].linha;
    if(vetor[i].linha > maxi)
      maxi = vetor[i].linha;
    if(vetor[i].coluna < minj)
      minj = vetor[i].coluna;
    if(vetor[i].coluna > maxj)
      maxj = vetor[i].coluna;
    nelem++;
  }
}

/*  FUNCAO: ADICIONA
 *
 *  insere os elementos introduzidos pelo utilizador
 *  no vetor
 *
 *  input: variavel onde e guardado o input
 */
void adiciona(Valor vetor[TAM])
{
  Valor input;
  int i, j, iguais = 0;

  scanf("%lu%lu%lf", &input.linha, &input.coluna, &input.num);

  if(input.num == zero) /* se o numero inserido for o 'zero',
  verifica se a posicao inserida existe no
  vetor, se existe remove essa posicao do vetor */
  {
    for(i = 0; i < cnt; i++)
      if((vetor[i].linha == input.linha) &&
      (vetor[i].coluna == input.coluna))
      {
        for(j = i; j < cnt; j++)
          vetor[j] = vetor[j+1];
        cnt--;
      }
  }
  else /* caso contrario, verifica se a posicao inserida existe no vetor,
  se existe substitui o valor no vetor */
  {
    for(i = 0; i < cnt; i++)
      if((vetor[i].linha == input.linha) &&
      (vetor[i].coluna == input.coluna))
      {
        vetor[i].num = input.num;
        iguais = 1;
      }
    if(iguais != 1) /* se nao, adiciona o valor ao vetor */
    {
      vetor[cnt] = input;
      cnt++;
    }
  }
}

/*  FUNCAO: LISTA
 *
 *  imprime os elementos do vetor
 *  se este estiver vazio, imprimir 'empty matrix'
 */
void lista(Valor vetor[TAM])
{
  int i;

  if(nelem == 0)
    printf("empty matrix\n");
  else
    for(i = 0; i < cnt; i++)
      printf("[%lu;%lu]=%.3lf\n",
        vetor[i].linha, vetor[i].coluna, vetor[i].num);
}

/*  FUNCAO: IMPRIME
 *
 *  imprime os limites da matriz e calcula a sua densidade
 *  se o vetor estiver vazio, imprimir 'empty matrix'
 *
 *  size: tamanho da matriz
 *  dens: densidade da matriz
 */
void imprime()
{
  int size = ((maxi - mini)+1) * ((maxj - minj)+1);
  float dens = (nelem / (float)size) * 100;

  if(nelem == 0)
    printf("empty matrix\n");
  else
    printf("[%lu %lu] [%lu %lu] %lu / %d = %.3f%%\n",
      mini, minj, maxi, maxj, nelem, size, dens);
}

/*  FUNCAO: LINHA
 *
 *  imprime os elementos da uma linha introduzida pelo utilizador
 *  se a linha estiver vazia, imprimir 'empty line'
 *
 *  lin: variavel onde e guardada a linha
 *  conta: contador que conta o numero da elementos da linha
 */
void linha(Valor vetor[TAM])
{
  int i, j, conta = 0, imprimiu = 0;
  unsigned long lin;

  scanf("%lu", &lin);

  for(i = 0; i < cnt; i++)
    for(j = minj; j <= maxj; j++)
      if((vetor[i].coluna == j) && (vetor[i].linha == lin))
        conta++;

  if((conta == 0) || (lin < mini) || (lin > maxi))
    printf("empty line");
  else
    for(i = minj; i <= maxj; i++)
    {
      for(j = 0; j < cnt; j++)
        if((vetor[j].coluna == i) && (vetor[j].linha == lin))
        {
          printf(" %.3lf", vetor[j].num);
          imprimiu = 1; /* se imprimiu coloca a variavel a 1 */
        }
      if(imprimiu == 0) /* se nao imprimiu, o elemento
                        nao existe no vetor, imprime 'zero' */
        printf(" %.3lf", zero);
      imprimiu = 0;
    }
  printf("\n");
}

/*  FUNCAO: COLUNA
 *
 *  imprime os elementos da uma coluna introduzida pelo utilizador
 *  se a coluna estiver vazia, imprimir 'empty column'
 *
 *  col: variavel onde e guardada a coluna
 *  conta: contador que conta o numero da elementos da coluna
 */
void coluna(Valor vetor[TAM])
{
  int i, j, conta = 0, imprimiu = 0;
  unsigned long col;

  scanf("%lu", &col);

  for(i = 0; i < cnt; i++)
    if(vetor[i].coluna == col)
      conta++;

  if((conta == 0) || (col < minj) || (col > maxj))
    printf("empty column\n");
  else
    for(i = mini; i <= maxi; i++)
    {
      for(j = 0; j < cnt; j++)
        if((vetor[j].linha == i) && vetor[j].coluna == col)
        {
          printf("[%d;%lu]=%.3lf\n", i, vetor[j].coluna, vetor[j].num);
          imprimiu = 1; /* se imprimiu coloca a variavel a 1 */
        }
      if(imprimiu == 0) /* se nao imprimiu, ou seja o elemento
                        nao existe no vetor, imprime 'zero' */
        printf("[%d;%lu]=%.3lf\n", i, col, zero);
      imprimiu = 0;
    }
}

/*  FUNCAO: SELECTION_COLUNA
 *
 *  ordena o vetor, com o algoritmo selection sort,
 *  em primeiro lugar por colunas, e entre colunas, por linhas
 *
 *  l: limite esquerdo do vetor a ser ordenado
 *  r: limite direito do vetor a ser ordenado
 */
void selection_coluna(Valor a[], int l, int r)
{
  int i, j;
  Valor aux;

  for (i = l; i < r; i++)
    for (j = i; j < r; j++)
      if (a[i].coluna > a[j].coluna)
      {
        aux = a[i];
        a[i] = a[j];
        a[j] = aux;
      }

  for(i = l; i < r; i++)
    for(j = i; j < r; j++)
      if((a[i].linha > a[j].linha) && (a[i].coluna == a[j].coluna))
      {
        aux = a[i];
        a[i] = a[j];
        a[j] = aux;
      }
}

/*  FUNCAO: SELECTION_LINHA
 *
 *  ordena o vetor, com o algoritmo selection sort,
 *  em primeiro lugar por linhas, e entre linhas, por colunas
 *
 *  l: limite esquerdo do vetor a ser ordenado
 *  r: limite direito do vetor a ser ordenado
 */
void selection_linha(Valor a[], int l, int r)
{
  int i, j;
  Valor aux;

  for (i = l; i < r; i++)
    for (j = i; j < r; j++)
      if (a[i].linha > a[j].linha)
      {
        aux = a[i];
        a[i] = a[j];
        a[j] = aux;
      }

  for(i = l; i < r; i++)
    for(j = i; j < r; j++)
      if((a[i].coluna > a[j].coluna) && (a[i].linha == a[j].linha))
      {
        aux = a[i];
        a[i] = a[j];
        a[j] = aux;
      }
}

/*  FUNCAO: ORDENAR
 *
 *  verifica o input do utilizador e ordena o vetor,
 *  por linhas ou colunas, dependendo desse input
 *
 *  input: variavel onde e guardado o input
 */
void ordenar(Valor vetor[])
{
  char input[8];

  fgets(input, 8, stdin);

  if(input[0] == '\n')
    selection_linha(vetor, 0, cnt);
    /* se o utilizador nao inserir nada apos o 'o',
    ordena primeiro por linhas e depois por colunas */
  else
    selection_coluna(vetor, 0, cnt);
    /* caso contrario (i.e. o utilizador insere 'column'
    apos o 'o'), ordena primeiro por colunas e depois
    por linhas */
}

/*  FUNCAO: ZERAR
 *
 *  altera o 'zero' da matriz, e remove as entradas
 *  desta que tem o novo 'zero' como valor
 *
 *  zero: variavel onde e guardado o novo zero
 */
void zerar(Valor vetor[TAM])
{
  int i, j;

  scanf("%lf", &zero);

  /* remove do vetor, as entradas com
  cujo valor seja o do novo zero */
  for(i = 0; i < cnt; i++)
    if(vetor[i].num == zero)
    {
      for(j = i; j < cnt; j++)
        vetor[j] = vetor[j+1];
      cnt--;
    }
}

/*  FUNCAO: RECEBE
 *
 *  recebe um ficheiro, le as suas informacoes e guarda-as no vetor
 *
 *  fp: ficheiro a ser lido
 */
void recebe(char *nome, Valor vetor[TAM])
{
  FILE *fp;
  Valor recebe;

  fp = fopen(nome, "r");

  if(fp == NULL)
    return;

  while(!feof(fp)) /* enquanto ainda nao tivermos chegado ao fim do
                   ficheiro a ser lido */
  {
    fscanf(fp, "[%lu;%lu]=%lf\n",
      &recebe.linha, &recebe.coluna, &recebe.num);

    if(recebe.num != zero)
    {
      vetor[cnt] = recebe;
      cnt++;
    }
  }
  fclose(fp);
}

/*  FUNCAO: FICHEIRO
 *
 *  recebe um nome (ou nao, caso este ja tenha sido introduzido
 *  anteriormente) de um ficheiro e escreve os elementos do vetor no ficheiro
 *
 *  espaco_enter: variavel onde e guardado o primeiro carater a seguir ao 'w'
 */
void ficheiro(Valor vetor[TAM])
{
  int i;
  char espaco_enter;
  FILE *fp;

  espaco_enter = getchar();

  /* se o utilizador der um espaco apos a letra 'w'
  (i.e. escrever um nome para o ficheiro), escreve
  na variavel nome */
  if(espaco_enter == ' ')
    scanf("%s", nome);

  fp = fopen(nome, "w");

  /* se o ficheiro nao existir, retorna */
  if(fp == NULL)
    return;
  /* se existir, escreve a informacao do vetor
  no ficheiro */
  else
    for (i = 0; i < cnt; i++)
      fprintf(fp, "[%lu;%lu]=%.3lf\n",
        vetor[i].linha, vetor[i].coluna, vetor[i].num);
  fclose(fp);
}

/*  FUNCAO: DENSIDADE
 *
 *  escreve num vetor, o numero de elementos de cada uma das linhas
 *
 *  indice_linha: posicao do vetor onde se guarda o numero de elementos da linha
 */
void densidade(Valor vetor[TAM], int conta[TAM])
{
  int i, indice_linha;

  for(i = 0; i < cnt; i++)
  {
    indice_linha = vetor[i].linha;
    conta[indice_linha]++;
  }
}

/*  FUNCAO: COMPRIMIR
 *
 *  comprime a matriz, num so vetor, colocando as linhas por ordem de
 *  densidade
 *
 *  indice_mdes: indice da linha de maior densidade
 *  mais_dens: numero de elementos da linha de maior densidade
 *  offst: offset da linha a colocar
 *  maxoffset: maior offset de todas as linhas
 *  l: numero de linhas
 *  conta: vetor com o numero de elementos de cada linha
 *  value: vetor onde sao colocados os elementos das linhas, ja com offset
 *  offset: vetor com os offsets de todas as linhas
 *  index: vetor com os indices de linha dos elementos colocados no vetor value
 */
void comprimir(Valor vetor[TAM])
{
  int indice_mdens, mais_dens, offst = 0, ind_offst = 0;
  int i, l = maxi - mini + 1, maxoffset = 0;
  int conta[TAM], offset[2*cnt], index[2*cnt];
  double value[2*cnt];
  Valor aux[TAM];

  int size = ((maxi - mini)+1) * ((maxj - minj)+1);
  float dens = (nelem / (float)size) * 100;

  for(i = 0; i < cnt; i++)
    aux[i] = vetor[i];

  densidade(aux, conta);

  /* ordenar o vetor para que os elementos
  do vetor sejam colocados por ordem de coluna */
  selection_linha(aux, 0, cnt);

  for(i = 0; i < 2*nelem; i++)
  {
    value[i] = zero;
    offset[i] = 0;
    index[i] = 0;
  }

  if(dens > 50)
    printf("dense matrix\n");
  else
  {
    while(l > 0)
    {
      indice_mdens = mini;
      mais_dens = conta[indice_mdens];

      /* determinar qual a linha de maior densidade */
      for(i = mini; i <= maxi; i++)
        if(conta[i] > mais_dens)
        {
          indice_mdens = i;
          mais_dens = conta[i];
        }

      /* com linhas com densidades iguais, descobrir qual
      tem o menor indice */
      for(i = mini; i < maxi; i++)
        if((i < indice_mdens) && (conta[i] == mais_dens))
          i = indice_mdens;

      if(conta[indice_mdens] == 0);
      else
      {
        conta[indice_mdens] = 0;

        /* determinar o offset */
        for(i = 0; i < cnt; i++)
          if((aux[i].linha == indice_mdens) &&
          (value[aux[i].coluna + offst - minj] != zero) &&
          (aux[i].num != 0))
          {
            offst++;
            i = 0;
          }

        if(offset[indice_mdens - mini] > maxoffset)
          maxoffset = offst;

        /* inserir a linha com o offset no vetor value
        e o indice da linha no vetor index */
        for(i = 0; i < cnt; i++)
          if(aux[i].linha == indice_mdens)
          {
            value[aux[i].coluna + offst - minj] = aux[i].num;
            index[aux[i].coluna + offst - minj] = indice_mdens;
          }

        offset[ind_offst] = offst; /* inserir o offset no vetor offset */
      }
      ind_offst++;
      offst = 0;
      l--;
    }
    printf("value =");
    for(i = 0; i < (maxj-minj+1)+maxoffset; i++)
      printf(" %.3lf", value[i]);
    printf("\n");

    printf("index =");
    for(i = 0; i < (maxj-minj+1)+maxoffset; i++)
      printf(" %d", index[i]);
    printf("\n");

    printf("offset =");
    for(i = 0; i < ind_offst; i++)
      printf(" %d", offset[i]);
    printf("\n");
  }
}
