#include <iostream>
#include <windows.h>
#include <fstream>
#include "lista.cpp"

using namespace std;
//chamando o projeto e funcionario
TipoProjeto projeto;
TipoFuncionario funcionario;

int main()
{
    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    SetConsoleOutputCP(CPAGE_UTF8);

    //criando a variávei para fazer com que o menu funcione
    int opcao;
    //Criando dando um nome para a lista encadeada
    TipoListaEncadeada ListaFuncionario;
    //Criando a lista encadeada de funcionários
    CriaListaVazia(&ListaFuncionario);
    //aqui o programa tenta abrir o arquivo se não achar ele cria o arquivo após salvar-lo
    AbrirArquivo(&ListaFuncionario);
    //dando um nome para o apontador
    TipoApontador apontador;
    //aqui o programa irá repetir o menu até o usuário digitar para sair dele
    do
    {
        system("cls");
        //chamando o menu
        Menu();
        cout << "Opção: ";
        cin >> opcao;
        cin.ignore();
        //switch case para receber a opção e assim fazer oque o usuário deseja
        switch (opcao)
        {
        case 1:
        {
            //aqui o programa vai cadastrar um funcionário
            int resp;
            TipoFuncionario funcionario;
            cout << endl
                 << "Cadastrando funcionário: \n";
            cout << "Id: ";
            cin >> funcionario.id;
            cin.ignore();
            cout << "Nome: \n";
            getline(cin, funcionario.nome);
            cout << "Endereco: \n";
            getline(cin, funcionario.endereco);
            cout << "Numero de dependentes: \n";
            cin >> funcionario.dependentes;

            //criando a lista com arranjo de projetos para esse funcionário
            CriaListaSequencialVazia(&funcionario.projetos);

            //inserindo ele no ultimo lugar da lista
            InsereListaUltimo(&ListaFuncionario, &funcionario);

            cout << "\nFuncionário cadastrado com sucesso.\n";

            //aqui é um atalho da opção dois para tornar o programa mais prático
            cout << "Voce deseja cadastrar um projeto a esse funcionario? ";
            cout << "\n1.Sim ou 2.Não\n";
            cin >> resp;

            if (resp == 1)
            {
                //aqui iremos fazer a mesma coisa que será feito no case 2
                TipoProjeto projeto;
                int IdFuncionarioDesejado, IdRemover;
                cout << endl
                     << "Cadastrando projeto: \n";
                cout << "Codigo: \n";
                cin >> projeto.codigo;
                cin.ignore();
                cout << "Nome: \n";
                getline(cin, projeto.nome);
                cout << "Total de horas: \n";
                cin >> projeto.horas;

                //escolhendo em qual funcionário será incluido o projeto
                cout << "\nEm qual funcionario voce deseja cadastrar esse projeto?\n";
                cin >> IdFuncionarioDesejado;

                //verificando se esse funcionário existe
                apontador = PesquisaItem(&ListaFuncionario, IdFuncionarioDesejado);

                if (apontador == NULL)
                {
                    cerr << "Erro";
                }
                else
                {
                    //como ele existe ele irá adiocionar o programa a ele
                    InsereItemTL(&apontador->item.projetos, projeto);
                }

                cout << "\n\nProjeto cadastrado com sucesso no id desse funcionário: " << IdFuncionarioDesejado << ".\n\n";
                system("pause");
            }
            else
            {
                break;
            }

            break;
        }
        case 2:
        {
            //mesmo processo que foi feito acima
            int IdFuncionarioDesejado, IdRemover;
            cout << endl
                 << "Cadastrando projeto: \n";
            cout << "Codigo: \n";
            cin >> projeto.codigo;
            cin.ignore();
            cout << "Nome: \n";
            getline(cin, projeto.nome);
            cout << "Total de horas: \n";
            cin >> projeto.horas;

            cout << "\nA qual funcionário deseja designar o projeto?\n";
            cin >> IdFuncionarioDesejado;

            apontador = PesquisaItem(&ListaFuncionario, IdFuncionarioDesejado);

            if (apontador == NULL)
            {
                do
                {
                    cout << "Id nao encontrado, digite novamente: ";
                    cout << endl
                         << "Cadastrando projeto: \n";
                    cout << "Nome: \n";
                    getline(cin, projeto.nome);
                    cout << "Total de horas: \n";
                    cin >> projeto.horas;

                    cout << "\nA qual funcionário deseja designar o projeto?\n";
                    cin >> IdFuncionarioDesejado;

                    apontador = PesquisaItem(&ListaFuncionario, IdFuncionarioDesejado);

                } while (apontador == NULL);
            }
            else
            {
                InsereItemTL(&apontador->item.projetos, projeto);
            }

            cout << "\n\nProjeto cadastrado com sucesso no funcionário de ID " << IdFuncionarioDesejado << ".\n\n";
            system("pause");
        }
        break;
        case 3:
            //recebendo o id do funcionario que tem o projeto que quer excluir
            int IdRemover;
            cout << "\nColoque o id do funcionário que tem o projeto que deseja excluir: .\n";
            cin >> IdRemover;

            //procurando para ver se esse funcionário existe na lista
            apontador = PesquisaItem(&ListaFuncionario, IdRemover);
            //mostra os projetos que esse funcionário possui
            ImprimeListaTL(apontador->item.projetos);


            cout<<"Agora digite o id do projeto que deseja excluir: ";
            cin >> IdRemover;

            //removendo o projeto
            RemoveItemTL(&apontador->item.projetos, IdRemover);
            cout << "\nProjeto removido com sucesso.\n";
            system("pause");
            break;
        case 4:
            //aqui o apontador irá para o primeiro da lista e irá percorrer a lsita enquanto o prox não for NULL que será quando ele for o ultimo da lista
            apontador = ListaFuncionario.primeiro->prox;
            //aqui está sendo feito o processo citado acima
            while (apontador != NULL)
            {
                //como tem que remover apenas os funcionarios sem projeto se o tamanho for igual a 0 ele não possui projetos
                if (apontador->item.projetos.tamanho == 0)
                {
                    //removendo o funcionario
                    RemoveItemPorId(&ListaFuncionario, apontador->item.id);
                }
                apontador = apontador->prox;
            }

            cout << "\nFoi removido o funcionario que nao possui projeto.\n";
            system("pause");
            break;
        case 5:
            cout << "\nDigite o id do funcionario que queira fazer a consulta: \n";
            int IdFuncionarioDesejado;
            cin >> IdFuncionarioDesejado;
            //aqui o programa procura o id desejado e se for null ele não existe
            apontador = PesquisaItem(&ListaFuncionario, IdFuncionarioDesejado);
            if (apontador != NULL)
            {
                //se existir ele mostra os dados do funcionário e todos os seus projetos
                ImprimeItem(&ListaFuncionario, IdFuncionarioDesejado);

                ImprimeListaTL(apontador->item.projetos);
                system("pause");
            }
            else
            {
                cerr << "Esse funcionário não existe\n";
                system("pause");
            }

            break;
        case 6:
            float SB, SL;
            float INSS, IR;

            apontador = ListaFuncionario.primeiro->prox;
            //aqui o mesmo processo feito acima de percorrer toda a lista
            while (apontador != NULL)
            {
                int horas = 0;
                //calculando todas as horas trabalhadas por ele
                for (int i = 0; i < apontador->item.projetos.tamanho; i++)
                {
                    horas += apontador->item.projetos.item[i].horas;
                }
                //fazendo o cálculo do salário bruto, salário líquido , INSS e imposto de renda de acordo com o que foi pedido no trabalho
                SB = (horas * 45) + (apontador->item.dependentes * 35);
                INSS = SB * 0.085;
                IR = SB * 0.15;
                SL = SB - INSS - IR;

                //imprimindo o contracheque de todos os funcionários 
                cout<<"\n-----------------------\n";
                cout<<"\tCONTRACHEQUE\n";
                cout<<"Nome do funcionário: "<<apontador->item.nome;
                cout<<"\nId do funcionário: "<<apontador->item.id;
                cout<<"\nNúmero de dependentes do funcionário: "<<apontador->item.dependentes;
                cout<<"\nNúmero de horas trabalhadas semanalmente: "<<horas;
                cout<<"\n\nSalário Bruto: "<<SB;
                cout<<"\nQuantidade do desconto do INSS: "<<INSS;
                cout<<"\nQuantidade do desconto do Imposto de renda: "<<IR;
                cout<<"\nSalário Líquido: "<<SL<<endl;
                apontador=apontador->prox;
                
            }
            system("pause");
            break;
        }

    } while (opcao != 7);
    //após sair da repetição o programa salva os dados no arquivo
    SalvarArquivo(&ListaFuncionario);
    //em seguida realoca a memória
    Desalocar(&ListaFuncionario);
}
