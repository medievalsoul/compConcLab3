/*
Programa que tem como objetivo retornar o menor e maior valores
de um dado vetor, utilizando programação concorrente
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "timer.h"

//variáveis globais
long long int num;    //número de elementos do vetor
int nthreads;         //número de threads
float *vetor;         //vetor que será avaliado

//struct que passa os valores maior e menor na pthread_exit
typedef struct{
  float menor;
  float maior;
} valores;

//função executada pelas threads
void * tarefa(void * arg){
  int inicio = *((int *) arg);
  valores * p_valores = (valores *) malloc(sizeof(valores));
  p_valores->menor = *(vetor+inicio);
  p_valores->maior = *(vetor+inicio);
  for(long long int i=inicio ; i<num ; i+=nthreads){
    if(*(vetor+i) < p_valores->menor) p_valores->menor = *(vetor+i);
    if(*(vetor+i) > p_valores->maior) p_valores->maior = *(vetor+i);
  }
  pthread_exit((void *) p_valores);
}

//fluxo principal
int main(int argc, char *argv[]){

  //variáveis para medida de tempo de execução (i_ =início, f_ =fim)
  double i_inicializacao, f_inicializacao;
  double i_concorrente, f_concorrente;
  double i_sequencial, f_sequencial;
  double i_finalizacao, f_finalizacao;

  GET_TIME(i_inicializacao);

  //validação dos parâmetros de entrada
  if(argc < 3) {
    printf("Inicie o programa no formato:\n %s <dimensao do vetor> <numero de threads>\n",argv[0]);
    return 1;
  }

  //atribuição dos valores de entrada às variáveis
  num =  atoll(argv[1]);
  nthreads = atoi(argv[2]);

  //inicialização do vetor
  vetor = (float*) malloc(sizeof(float)*num);
  if (vetor == NULL) {
    fprintf(stderr,"ERRO--malloc()\n");
    return 2;
  }
  for(long long int i=0 ; i<num ; i++){
    *(vetor+i) = rand();
  }

  GET_TIME(f_inicializacao);

  GET_TIME(i_concorrente);

  //identificador das threads
  pthread_t *tid = (pthread_t *) malloc(sizeof(pthread_t)*nthreads);
  if (tid == NULL) {
    fprintf(stderr,"ERRO--malloc()\n");
    return 2;
  }
  //criação das threads
  int thread[nthreads]; //vetor que vai numerar as threads
  for(int i=0 ; i<nthreads ; i++){
    thread[i]=i;
    if (pthread_create(tid+i, NULL, tarefa, (void*) &thread[i])) {
      fprintf(stderr,"ERRO--pthread_create()\n");
      return 3;
    }
  }

  //espera as threads acabarem
  float result_menor[nthreads];  //variáveis que armazenam os resultados das threads
  float result_maior[nthreads];
  for (int i=0; i<nthreads; i++) {
    valores * p_valores;
    if (pthread_join(*(tid+i), (void**)&p_valores)) {
       fprintf(stderr,"ERRO--pthread_join() \n");
       return 4;
     }
     result_menor[i] = p_valores->menor;
     result_maior[i] = p_valores->maior;
     free(p_valores);
  }

  //avalia resultado retornados pelas threads
  float menor=result_menor[0];
  float maior=result_menor[0];
  for(int i=0; i<nthreads; i++){
    if(result_menor[i] < menor) menor = result_menor[i];
    if(result_maior[i] > maior) maior = result_maior[i];
  }

  GET_TIME(f_concorrente);

/*
  GET_TIME(i_sequencial);

  //versão sequencial
  float menor_seq;
  float maior_seq;
  for(long long int i=0 ; i<num ; i++){
    if(*(vetor+i) < menor_seq) menor_seq = *(vetor+i);
    if(*(vetor+i) > maior_seq) maior_seq = *(vetor+i);
  }

  GET_TIME(f_sequencial);


  //testa versão concorrente
  if(menor==menor_seq && maior==maior_seq) printf("Teste bem sucedido\n");
  else printf("Teste bem sucedido\n");
*/

  GET_TIME(i_finalizacao);

  //libera memória
  free(vetor);

  GET_TIME(f_finalizacao);

  printf("tempo inicialização = %f\n",f_inicializacao-i_inicializacao);
  printf("tempo concorrente = %f\n",f_concorrente-i_concorrente);
//  printf("tempo sequencial = %f\n",f_sequencial-i_sequencial);
  printf("tempo finalizção = %f\n",f_finalizacao-i_finalizacao);

  return 0;
}
