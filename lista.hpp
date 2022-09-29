#ifndef LIST_H
#define LIST_H

#include <iostream>
//essa primeira parte foi retirada da sugestão de struct que o próprio trabalho sugeria
using namespace std;

#define MAXTAM 5

#define INICIO 1

bool listaCriada = false;

typedef struct TipoCelula *TipoApontador;

typedef struct TipoProjeto
{
    int codigo; // codigo do projeto
    string nome; // nome do projeto
    int horas;     // numero de horas trabalhas no projeto
};

typedef struct TipoListaSequencial
{
    TipoProjeto item[MAXTAM];
    int primeiro;
    int ultimo;
    int tamanho;
};

typedef struct TipoFuncionario
{
    int id;             // codigo do funcionario
    string nome;        //nome do funcionario
    string endereco;         // endereco do funcionario
    int dependentes;           // numero de dependentes do funcionario
    TipoListaSequencial projetos; // Lista Sequencial que guarda os projetos nos quais o funcionario trabalha
} TipoFuncionario;

typedef struct TipoCelula
{
    TipoFuncionario item;
    TipoApontador prox;
};

typedef struct TipoListaEncadeada
{
    TipoApontador primeiro;
    TipoApontador ultimo;
    int tamanho=0;
};

//como nessa parte é o header estamos declarando todas as funções
void CriaListaVazia(TipoListaEncadeada *lista);
bool VerificaListaVazia(TipoListaEncadeada *lista);
void InsereListaPrimeiro(TipoListaEncadeada *lista, TipoFuncionario *item);
void InsereListaUltimo(TipoListaEncadeada *lista, TipoFuncionario *item);
TipoApontador PesquisaItem(TipoListaEncadeada *lista, int id);
void ImprimeItem(TipoListaEncadeada *lista, int id);
void RemoveItemPorId(TipoListaEncadeada *lista, int id);
void CriaListaSequencialVazia(TipoListaSequencial *lista);
bool verificaListaVazia(TipoListaSequencial *lista);
bool verificaListaCheia(TipoListaSequencial *lista);
bool InsereItemTL(TipoListaSequencial *lista, TipoProjeto item);
int LocalizaItemTL(TipoListaSequencial *lista, int id);
int RemoveItemTL(TipoListaSequencial *lista, int id);
void ImprimeListaTL(TipoListaSequencial lista);
bool AbrirArquivo(TipoListaEncadeada *ListaFuncionario);
bool SalvarArquivo(TipoListaEncadeada *ListaFuncionario);
void Menu();
void Desalocar(TipoListaEncadeada *ListaFuncionario);

#endif