#include <iostream>
#include <windows.h>
#include "lista.hpp"
using namespace std;

#define MAXTAM 5

#define INICIO 1
//essa foi uma tad de criar uma lista encadeada vazia
void CriaListaVazia(TipoListaEncadeada *lista)
{
    if (!listaCriada)
    {
        lista->primeiro = new TipoCelula;
        lista->ultimo = lista->primeiro;
        lista->ultimo->prox = NULL;
        cout << "Lista criada com sucesso!";
        listaCriada = true;
    }
    else
    {
        cout << "Lista já existe!";
    }
    Sleep(1500);
}

//tad de verificação de lista vazia
bool VerificaListaVazia(TipoListaEncadeada *lista)
{
    return (lista->primeiro == lista->ultimo);
}

//tad de inserir ultimo item na lista
void InsereListaUltimo(TipoListaEncadeada *lista, TipoFuncionario *item)
{
    lista->ultimo->prox = new TipoCelula;
    lista->ultimo = lista->ultimo->prox;
    lista->ultimo->item = *item;
    lista->ultimo->prox = NULL;
    lista->tamanho++;
}

//tad de pesquisa de item porem passando o apontador como parâmetro
TipoApontador PesquisaItem(TipoListaEncadeada *lista, int id)
{
    TipoApontador aux;
    aux = lista->primeiro->prox;
    while (aux != NULL)
    {
        if (id == aux->item.id)
        {
            return aux;
        }
        aux = aux->prox;
    }
    return NULL;
}
//aqui fazemos o mesmo processo de percorrer a lista inteira e em seguida imprimindo os dados desejados
void ImprimeItem(TipoListaEncadeada *lista, int id)
{
    TipoApontador aux;
    aux = lista->primeiro->prox;
    while (aux != NULL)
    {
        if (aux->item.id == id)
        {
            cout << "ID: " << aux->item.id << endl;
            cout << "Nome: " << aux->item.nome << endl;
            cout<< "Endereco: "<<aux->item.endereco<<endl;
            break;
        }
        aux = aux->prox;
    }
}

//primeiro ele verifica se está vazia a lista se não estiver procura o id e coloca os ponteiros para apontarem para os proximos itens para que possa fazer a remoção sem erro
void RemoveItemPorId(TipoListaEncadeada *lista, int id)
{
    if (VerificaListaVazia(lista))
    {
        return;
    }

    TipoApontador aux, anterior, x;

    x = lista->primeiro;

    while (x != NULL)
    {
        if (x->prox->item.id == id)
        {
            anterior = x;
            break;
        }
        x = x->prox;
    }
    aux = anterior->prox;
    anterior->prox = aux->prox;
    delete aux;
    lista->tamanho--;
}
//tad de criação de lista com arranjo vazia
void CriaListaSequencialVazia(TipoListaSequencial *lista)
{
    lista->tamanho = 0;
}
//tad de verificação de lista com arranjo vazia

bool verificaListaVazia(TipoListaSequencial *lista)
{
    if (lista->tamanho == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
//tad de verificação de lista com arranjo cheia
bool verificaListaCheia(TipoListaSequencial *lista)
{
    if (lista->tamanho == MAXTAM)
    {
        return true;
    }
    else
    {
        return false;
    }
}
////tad de inserção na lista com arranjo e logo em seguida aumentar seu tamanho
bool InsereItemTL(TipoListaSequencial *lista, TipoProjeto item)
{
    if (!verificaListaCheia(lista))
    {
        lista->item[lista->tamanho] = item;
        lista->tamanho++;

        return true;
    }
    else
    {
        return false;
    }
}
//aqui ele procura na lista de projetos se o id passado é o mesmo do código
int LocalizaItemTL(TipoListaSequencial *lista, int id)
{
    for (int i = 0; i < lista->tamanho; i++)
    {
        if (lista->item[i].codigo == id)
        {
            return i;
        }
    }
    return -1;
}
//primeiro ele localiza o funcionário que possui esse projeto em seguida ele remove o projeto e diminui o tamanho da lista
int RemoveItemTL(TipoListaSequencial *lista, int id)
{
    int posicao = LocalizaItemTL(lista, id);
    for (int i = posicao; i < lista->tamanho; i++)
    {
        lista->item[i] = lista->item[i + 1];
    }
    lista->tamanho--;
}
//aqui imprimi todos os projetos que um funcionário possui
void ImprimeListaTL(TipoListaSequencial lista)
{
    for (int i = 0; i < lista.tamanho; i++)
    {
        cout << "Código do projeto: " << lista.item[i].codigo << endl;
        cout << "Nome do projeto: " << lista.item[i].nome << endl;
        cout << "Total de horas: " << lista.item[i].horas << endl;
    }
}

//aqui o programa tenta abrir o funcionarios.bin se não achar ele cria o arquivo ao final do programa, foi utilizado funções da biblioteca fstream para realizar essa tarefa
bool AbrirArquivo(TipoListaEncadeada *ListaFuncionario)
{
    ifstream file;
    file.open("funcionarios.bin", fstream::binary);

    if (file.fail())
    {
        file.clear();
        return false;
    }

    bool primeiraLinha = true;

    while (file.peek() != ifstream::traits_type::eof())
    {
        if (primeiraLinha)
        {
            unsigned int id;
            file >> id;
            primeiraLinha = false;
        }
        else
        {
            TipoFuncionario *funcionario = new TipoFuncionario();
            file.read((char *)funcionario, sizeof(funcionario));

            InsereListaUltimo(ListaFuncionario, funcionario);
        }
    }

    file.clear();
    return true;
}

//aqui ele passa os dados digitados do usuário para o arquivo
bool SalvarArquivo(TipoListaEncadeada *ListaFuncionario)
{
    ofstream file;
    file.open("funcionarios.bin", ofstream::trunc | fstream::binary);

    if (file.fail())
    {
        file.clear();
        return false;
    }

    TipoApontador temp = ListaFuncionario->primeiro;
    while (temp != NULL)
    {
        TipoFuncionario funcionario = temp->item;
        file.write((char *)&funcionario, sizeof(funcionario));

        TipoApontador aux = temp;
        temp = temp->prox;
        delete aux;
    }
    return true;
}

//menu para realizar as tarefas desejadas
void Menu()
{
    system("cls");
    cout << "--------------------------------\n";
    cout << "    Departamento Empresarial    \n";
    cout << "--------------------------------\n";
    cout << "1. Cadastrar Funcionário\n";
    cout << "2. Cadastrar Projeto\n";
    cout << "3. Excluir Projeto\n";
    cout << "4. Excluir Funcionário sem projeto\n";
    cout << "5. Consultar Funcionário\n";
    cout << "6. Imprimir contracheque\n";
    cout << "7. Sair\n\n";
}

//aqui o programa desaloca a memória de funcionários já excluídos
void Desalocar(TipoListaEncadeada *ListaFuncionario)
{
    
    TipoApontador aux, remove;
    aux = ListaFuncionario->primeiro->prox;
    while( aux != NULL )
    {
        remove = aux;
        aux = aux->prox;
        delete remove;
    }
    delete aux;
}
