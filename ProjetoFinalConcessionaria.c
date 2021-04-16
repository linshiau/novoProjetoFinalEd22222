#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include <stdlib.h>
#include<string.h>                  //contem strcmp(),strcpy(),strlen(),etc
#include<ctype.h>                   //contem toupper(), tolower(),etc
#include<dos.h>                     //contem _dos_getdate
#include<time.h>


#define RETURNTIME 15

char categorias[][15]= {"Hatch","Sedan","Van","Esportivo","MicroOnibus","Caminhonete"};

//lista de arquivos globais que podem ser acessados em qualquer lugar do programa
FILE *fp,*ft,*fs;

void funcaoRetorno(void);
void adicionaCarros(void);
void excluiCarros(void);
void editaCarros(void);
void procuraCarros(void);
void alugaCarros(void);
void mostraCarros(void);
int  getDados();
int  checaPlaca(int);
int t(void);
void protegidoPorSenha();
void informacoesAlugado();

COORD coord = {0, 0};
int s;
char procurCarro;
char senha[10]= {"senha1234"};

void gotoxy (int x, int y)
{
    coord.X = x;
    coord.Y = y; // cordenadas x e y
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

struct dataMero
{
    int mm,dd,yy;
};
struct carros
{
    int placa;
    char nomeLocatario[20];
    char modelo[20];
    char Marca[20];
    int quantidade;
    float Preco;
    int contagem;
    int anoModelo;
    char *cat;
    struct dataMero dataAlugado;
    struct dataMero dataDevolucao;
};
struct carros a;

void main()
{
    system("cls");
    int i;
    gotoxy(20,3);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(20,5);
    printf("\xDB\xDB\xDB\xDB\xB2 1. COMPRA DE CARROS   ");
    gotoxy(20,7);
    printf("\xDB\xDB\xDB\xDB\xB2 2. VENDA DE CARROS");
    gotoxy(20,9);
    printf("\xDB\xDB\xDB\xDB\xB2 3. PESQUISA DE CARROS");
    gotoxy(20,11);
    printf("\xDB\xDB\xDB\xDB\xB2 4. ALUGUEL DE CARROS");
    gotoxy(20,13);
    printf("\xDB\xDB\xDB\xDB\xB2 5. VER CARROS DISPONIVEIS");
    gotoxy(20,15);
    printf("\xDB\xDB\xDB\xDB\xB2 6. EDITAR VEICULO NO SISTEMA");
    gotoxy(20,17);
    printf("\xDB\xDB\xDB\xDB\xB2 7. FECHAR O SISTEMA");
    gotoxy(20,19);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(20,20);
    t();
    gotoxy(20,21);
    printf("Digite sua opcao:");
    switch(getch())
    {
    case '1':
        adicionaCarros();
        break;
    case '2':
        excluiCarros();
        break;
    case '3':
        procuraCarros();
        break;
    case '4':
        alugaCarros();
        break;
    case '5':
        verCarros();
        break;
    case '6':
        editaCarros();
        break;
    case '7':
    {
        system("cls");
        gotoxy(16,3);
        printf("\tSistema de concessionaria");
        gotoxy(16,4);
        printf("\tProjeto de estrutura de dados 2");
        gotoxy(16,5);
        printf("\tDesenvolvido por");
        gotoxy(16,7);
        printf("\tLin Shiau Lon Rocha e Gabriel de Freitas");
        gotoxy(24,17);
        printf("Saindo em 3 segundos...........>");
        Sleep(3000);
        exit(0);
    }
    default:
    {
        gotoxy(10,23);
        printf("\aENTRADA INVALIDA! Por favor entre com uma opcao valida");
        if(getch())
            main();
    }

    }
}
void adicionaCarros(void)    //funcao que adiciona carros
{
    system("cls");
    int i;
    gotoxy(20,5);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2SELECT CATEGOIES\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(20,7);
    printf("\xDB\xDB\xDB\xDB\xB2 1. Hatch");
    gotoxy(20,9);
    printf("\xDB\xDB\xDB\xDB\xB2 2. Sedan");
    gotoxy(20,11);
    printf("\xDB\xDB\xDB\xDB\xB2 3. Van");
    gotoxy(20,13);
    printf("\xDB\xDB\xDB\xDB\xB2 4. Esportivo");
    gotoxy(20,15);
    printf("\xDB\xDB\xDB\xDB\xB2 5. MicroOnibus");
    gotoxy(20,17);
    printf("\xDB\xDB\xDB\xDB\xB2 6. Caminhonete");
    gotoxy(20,19);
    printf("\xDB\xDB\xDB\xDB\xB2 7. Voltar ao menu principal");
    gotoxy(20,21);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(20,22);
    printf("Digite sua escolha:");
    scanf("%d",&s);
    if(s==7)

        main() ;
    system("cls");
    fp=fopen("Concessionaria.dat","ab+");
    if(getDados()==1)
    {
        a.cat=categorias[s-1];
        fseek(fp,0,SEEK_END);
        fwrite(&a,sizeof(a),1,fp);
        fclose(fp);
        gotoxy(21,14);
        printf("Os dados do veiculo foram salvos no sitema com sucesso!");
        gotoxy(21,15);
        printf("adicionar mais veiculos ao banco de dados?(S / N):");
        if(getch()=='n')
            main();
        else
            system("cls");
        adicionaCarros();
    }
}
void excluiCarros()    //funcao que deleta itens do arquivo fp
{
    system("cls");
    int d;
    char outro='s';
    while(outro=='s')  //loop infinito
    {
        system("cls");
        gotoxy(10,5);
        printf("Digite a Placa do carro que deseja excluir:");
        scanf("%d",&d);
        fp=fopen("Concessionaria.dat","rb+");
        rewind(fp);
        while(fread(&a,sizeof(a),1,fp)==1)
        {
            if(a.placa==d)
            {

                gotoxy(10,7);
                printf("O carro esta disponivel");
                gotoxy(10,8);
                printf("Modelo do carro: %s",a.modelo);
                gotoxy(10,9);
                printf("Marca do carro: %s",a.Marca);
                gotoxy(10,10);
                printf("Ano modelo eh %d",a.anoModelo);
                procurCarro='t';
            }
        }
        if(procurCarro!='t')
        {
            gotoxy(10,10);
            printf("Nenhum registro foi encontrado");
            if(getch())
                main();
        }
        if(procurCarro=='t' )
        {
            gotoxy(10,12);
            printf("Voce realmente deseja exclui-lo?(S/N):");
            if(getch()=='s')
            {
                ft=fopen("teste.dat","wb+");  //arquivo temporario para deletar
                rewind(fp);
                while(fread(&a,sizeof(a),1,fp)==1)
                {
                    if(a.placa!=d)
                    {
                        fseek(ft,0,SEEK_CUR);
                        fwrite(&a,sizeof(a),1,ft); //escreve tudo em arquivo temporario exceto
                    }                              //o que queremos excluir
                }
                fclose(ft);
                fclose(fp);
                remove("Concessionaria.dat");
                rename("teste.dat","Concessionaria.dat"); //copia todos os itens do arquivo temporario para fp exceto
                fp=fopen("Concessionaria.dat","rb+");    //o que queremos excluir
                if(procurCarro=='t')
                {
                    gotoxy(10,14);
                    printf("As informacoes do veiculo foram excluidas do sistema com sucesso!");
                    gotoxy(10,15);
                    printf("Deseja excluir outro veiculo?(S/N)");
                }
            }
            else
                main();
            fflush(stdin);
            outro=getch();
        }
    }
    gotoxy(10,15);
    main();
}
void procuraCarros()
{
    system("cls");
    int d;
    printf("*****************************Procurar carros*********************************");
    gotoxy(20,10);
    printf("\xDB\xDB\xDB\xB2 1. Procurar por placa");
    gotoxy(20,14);
    printf("\xDB\xDB\xDB\xB2 2. Procurar por Nome");
    gotoxy( 15,20);
    printf("Digite sua opcao:");
    fp=fopen("Concessionaria.dat","rb+"); //abre o arquivo para fins de leitura
    rewind(fp);   //move o ponteiro para o comeco do arquivo
    switch(getch())
    {
    case '1':
    {
        system("cls");
        gotoxy(25,4);
        printf("****Procura de carros por ID****");
        gotoxy(20,5);
        printf("Digite a placa do carro:");//ID
        scanf("%d",&d);
        gotoxy(20,7);
        printf("Procurando........");
        while(fread(&a,sizeof(a),1,fp)==1)
        {
            if(a.placa==d)
            {
                Sleep(2);
                gotoxy(20,7);
                printf("O carro esta disponivel");
                gotoxy(20,8);
                printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
                gotoxy(20,9);
                printf("\xB2 Placa:%d",a.placa);
                gotoxy(47,9);
                printf("\xB2");
                gotoxy(20,10);
                printf("\xB2 Modelo:%s",a.modelo);
                gotoxy(47,10);
                printf("\xB2");
                gotoxy(20,11);
                printf("\xB2 Marca:%s ",a.Marca);
                gotoxy(47,11);
                printf("\xB2");
                gotoxy(20,12);
                printf("\xB2 Qantidade:%d ",a.quantidade);
                gotoxy(47,12);
                printf("\xB2");
                gotoxy(47,11);
                printf("\xB2");
                gotoxy(20,13);
                printf("\xB2 Preco:Rs.%.2f",a.Preco);
                gotoxy(47,13);
                printf("\xB2");
                gotoxy(20,14);
                printf("\xB2 Ano modelo:%d ",a.anoModelo);
                gotoxy(47,14);
                printf("\xB2");
                gotoxy(20,15);
                printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
                procurCarro='t';
            }

        }
        if(procurCarro!='t')  //checa se a condicao entra ou nao no loop
        {
            gotoxy(20,8);
            printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
            gotoxy(20,9);
            printf("\xB2");
            gotoxy(38,9);
            printf("\xB2");
            gotoxy(20,10);
            printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
            gotoxy(22,9);
            printf("\aNenhum registro encontrado");
        }
        gotoxy(20,17);
        printf("Deseja procurar novamente?(S/N)");
        if(getch()=='s')
            procuraCarros();
        else
            main();
        break;
    }
    case '2':
    {
        char s[15];
        system("cls");
        gotoxy(25,4);
        printf("****Procura de carros por nome****");
        gotoxy(20,5);
        printf("Digite o nome do carro:");
        scanf("%s",s);
        int d=0;
        while(fread(&a,sizeof(a),1,fp)==1)
        {
            if(strcmp(a.modelo,(s))==0) //checa se a.nome é igual ou nao a 's'
            {
                gotoxy(20,7);
                printf("O carro esta disponivel");
                gotoxy(20,8);
                printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
                gotoxy(20,9);
                printf("\xB2 Placa:%d",a.placa);
                gotoxy(47,9);
                printf("\xB2");
                gotoxy(20,10);
                printf("\xB2 Modelo:%s",a.modelo);
                gotoxy(47,10);
                printf("\xB2");
                gotoxy(20,11);
                printf("\xB2 Marca:%s",a.Marca);
                gotoxy(47,11);
                printf("\xB2");
                gotoxy(20,12);
                printf("\xB2 Qantidade:%d",a.quantidade);
                gotoxy(47,12);
                printf("\xB2");
                gotoxy(20,13);
                printf("\xB2 Preco:Rs.%.2f",a.Preco);
                gotoxy(47,13);
                printf("\xB2");
                gotoxy(20,14);
                printf("\xB2 Ano modelo:%d ",a.anoModelo);
                gotoxy(47,14);
                printf("\xB2");
                gotoxy(20,15);
                printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
                d++;
            }

        }
        if(d==0)
        {
            gotoxy(20,8);
            printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
            gotoxy(20,9);
            printf("\xB2");
            gotoxy(38,9);
            printf("\xB2");
            gotoxy(20,10);
            printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
            gotoxy(22,9);
            printf("\aNenhum registro encontrado");
        }
        gotoxy(20,17);
        printf("Deseja procurar novamente?(S/N)");
        if(getch()=='s')
            procuraCarros();
        else
            main();
        break;
    }
    default :
        getch();
        procuraCarros();
    }
    fclose(fp);
}
void alugaCarros(void)  //funcao que aluga carros da concessionaria
{
    int t;

    system("cls");
    printf("********************************ALUGUEL DE CARROS**************************");
    gotoxy(10,5);
    printf("\xDB\xDB\xDB\xDb\xB2 1. Alugar um carro");
    gotoxy(10,7);
    printf("\xDB\xDB\xDB\xDb\xB2 2. Ver carros alugados");
    gotoxy(10,9);
    printf("\xDB\xDB\xDB\xDb\xB2 3. Procurar carros alugados");
    gotoxy(10,11);
    printf("\xDB\xDB\xDB\xDb\xB2 4. Devolucao de carros alugados");
    gotoxy(10,14);
    printf("Digite uma opcao:");
    switch(getch())
    {
    case '1':  //alugar carro
    {
        system("cls");
        int c=0;
        char outro='s';
        while(outro=='s')
        {
            system("cls");
            gotoxy(15,4);
            printf("***Secao de carros alugados***");
            gotoxy(10,6);
            printf("Digite a placa do carro:");
            scanf("%d",&t);
            fp=fopen("Concessionaria.dat","rb");
            fs=fopen("Alugados.dat","ab+");
            if(checaPlaca(t)==0) //aluga aqueles que estao presentes na concessionaria
            {
                gotoxy(10,8);
                printf("O carro esta disonivel");
                gotoxy(10,9);
                printf("Existem %d carros disponiveis para aluguel na concessionaria ",a.quantidade);
                gotoxy(10,10);
                printf("O nome do carro e %s",a.modelo);
                gotoxy(10,11);
                printf("Digite o nome do locatario:");
                scanf("%s",a.nomeLocatario);

                gotoxy(10,12);
                //printf("dataAlugado date=%d-%d-%d",a.dataAlugado.dd,a.dataAlugado.mm,a.dataAlugado.yy);
                tLocacao();

                gotoxy(10,13);
                printf("O carro de Placa %d foi alugado",a.placa);
                a.dataDevolucao.dd=a.dataAlugado.dd+RETURNTIME;   //para data de devolucao
                a.dataDevolucao.mm=a.dataAlugado.mm;
                a.dataDevolucao.yy=a.dataAlugado.yy;
                if(a.dataDevolucao.dd>30)
                {
                    a.dataDevolucao.mm+=a.dataDevolucao.dd/30;
                    a.dataDevolucao.dd-=30;

                }
                if(a.dataDevolucao.mm>12)
                {
                    a.dataDevolucao.yy+=a.dataDevolucao.mm/12;
                    a.dataDevolucao.mm-=12;

                }
                gotoxy(10,14);
                printf("Para ser devolvido em:%d-%d-%d",a.dataDevolucao.dd,a.dataDevolucao.mm,a.dataDevolucao.yy);
                fseek(fs,sizeof(a),SEEK_END);
                fwrite(&a,sizeof(a),1,fs);
                fclose(fs);
                c=1;
            }
            if(c==0)
            {
                gotoxy(10,11);
                printf("Nenhum registro encontrado");
            }
            gotoxy(10,15);
            printf("Deseja alugar mais carros?(S/N):");
            fflush(stdin);
            outro=getche();
            fclose(fp);
        }

        break;
    }
    case '2':  //mostra lista de carros alugados
    {
        system("cls");
        int j=4;
        printf("*******************************Lista de carros alugados*******************************\n");
        gotoxy(2,2);
        printf("NOME LOCATARIO    CATEGORIA    PLACA    MODELO    DATA LOCACAO   DATA DEVOLUCAO");
        fs=fopen("Alugados.dat","rb");
        while(fread(&a,sizeof(a),1,fs)==1)
        {

            gotoxy(2,j);
            printf("%s",a.nomeLocatario);
            gotoxy(20,j);
            printf("%s",a.cat);
            gotoxy(33,j);
            printf("%d",a.placa);
            gotoxy(42,j);
            printf("%s",a.modelo);
            gotoxy(52,j);
            printf("%d-%d-%d",a.dataAlugado.dd,a.dataAlugado.mm,a.dataAlugado.yy );
            gotoxy(67,j);
            printf("%d-%d-%d",a.dataDevolucao.dd,a.dataDevolucao.mm,a.dataDevolucao.yy);
//struct dosdate_t d;
//_dos_getdate(&d);
            gotoxy(52,25);
//            printf("data atual=%d-%d-%d",d.day,d.month,d.year);
            j++;

        }
        fclose(fs);
        gotoxy(1,25);
        funcaoRetorno();
    }
    break;
    case '3':   //procura carros alugados por placa(id)
    {
        system("cls");
        gotoxy(10,6);
        printf("Digite a Placa do carro:");
        int p,c=0;
        char outro='s';
        while(outro=='s')
        {

            scanf("%d",&p);
            fs=fopen("Alugados.dat","rb");
            while(fread(&a,sizeof(a),1,fs)==1)
            {
                if(a.placa==p)
                {
                    informacoesAlugado();
                    gotoxy(10,12);
                    printf("Pressione qualquer tecla.......");
                    getch();
                    informacoesAlugado();
                    c=1;
                }

            }
            fflush(stdin);
            fclose(fs);
            if(c==0)
            {
                gotoxy(10,8);
                printf("Nenhum registro encontrado");
            }
            gotoxy(10,13);
            printf("Deseja procurar novamente?(S/N)");
            outro=getch();
        }
    }
    break;
    case '4':  //remove carros alugados da lista
    {
        system("cls");
        int b;
        FILE *fg;  //declaracao de arquivo temporario para exclusao
        char outro='s';
        while(outro=='s')
        {
            gotoxy(10,5);
            printf("Digite a Placa do carro que deseja remover da lista:");
            scanf("%d",&b);
            fs=fopen("Alugados.dat","rb+");
            while(fread(&a,sizeof(a),1,fs)==1)
            {
                if(a.placa==b)
                {
                    informacoesAlugado();
                    procurCarro='t';
                }
                if(procurCarro=='t')
                {
                    gotoxy(10,12);
                    printf("Voce realmente deseja remove-lo?(S/N)");
                    if(getch()=='s')
                    {
                        fg=fopen("registro.dat","wb+");
                        rewind(fs);
                        while(fread(&a,sizeof(a),1,fs)==1)
                        {
                            if(a.placa!=b)
                            {
                                fseek(fs,0,SEEK_CUR);
                                fwrite(&a,sizeof(a),1,fg);
                            }
                        }
                        fclose(fs);
                        fclose(fg);
                        remove("Alugados.dat");
                        rename("registro.dat","Alugados.dat");
                        gotoxy(10,14);
                        printf("O carro alugado foi removido da lista");

                    }

                }
                if(procurCarro!='t')
                {
                    gotoxy(10,15);
                    printf("Nenhum registro encontrado");
                }
            }
            gotoxy(10,16);
            printf("Deseja excluir mais carros da lista de alugados?(S/N)");
            outro=getch();
        }
    }
    default:
        gotoxy(10,18);
        printf("\aEntrada invalida!!");
        getch();
        alugaCarros();
        break;
    }
    gotoxy(1,30);
    funcaoRetorno();
}
void verCarros(void)  //mostra lista de carros presentes na concessionaria
{
    int i=0,j;
    system("cls");
    gotoxy(1,1);
    printf("***********************************Lista de Carros*******************************");
    gotoxy(2,2);
    printf(" CATEGORIA     PLACA    MODELO     MARCA       QTD     PRECO       ANO MODELO ");
    j=4;
    fp=fopen("Concessionaria.dat","rb");
    while(fread(&a,sizeof(a),1,fp)==1)
    {
        gotoxy(3,j);
        printf("%s",a.cat);
        gotoxy(17,j);
        printf("%d",a.placa);
        gotoxy(26,j);
        printf("%s",a.modelo);
        gotoxy(37,j);
        printf("%s",a.Marca);
        gotoxy(49,j);
        printf("%d",a.quantidade);
        gotoxy(57,j);
        printf("%.2f",a.Preco);
        gotoxy(69,j);
        printf("%d",a.anoModelo);
        printf("\n\n");
        j++;
        i=i+a.quantidade;
    }
    gotoxy(3,25);
    printf("Total de carros =%d",i);
    fclose(fp);
    gotoxy(35,25);
    funcaoRetorno();
}
void editaCarros(void)  //edita informaçoes sobre veiculos
{
    system("cls");
    int c=0;
    int d,e;
    gotoxy(20,4);
    printf("****Secao de edicao de veiculos****");
    char outro='s';
    while(outro=='s')
    {
        system("cls");
        gotoxy(15,6);
        printf("Entre a placa do carro a ser editado:");
        scanf("%d",&d);
        fp=fopen("Concessionaria.dat","rb+");
        while(fread(&a,sizeof(a),1,fp)==1)
        {
            if(checaPlaca(d)==0)
            {
                gotoxy(15,7);
                printf("O carro esta disponivel");
                gotoxy(15,8);
                printf("Placa do carro:%d",a.placa);
                gotoxy(15,9);
                printf("Digite o novo modelo:");
                scanf("%s",a.modelo);
                gotoxy(15,10);
                printf("Digite a nova marca:");
                scanf("%s",a.Marca);
                gotoxy(15,11);
                printf("Digite a nova quantidade:");
                scanf("%d",&a.quantidade);
                gotoxy(15,12);
                printf("Digite o novo preco:");
                scanf("%f",&a.Preco);
                gotoxy(15,13);
                printf("Digite o novo ano do modelo:");
                scanf("%d",&a.anoModelo);
                gotoxy(15,14);
                printf("Os dados foram modificados");
                fseek(fp,ftell(fp)-sizeof(a),0);
                fwrite(&a,sizeof(a),1,fp);
                fclose(fp);
                c=1;
            }
            else
            {
                gotoxy(15,9);
                printf("Nenhum registro encontrado");
            }
        }
        gotoxy(15,16);
        printf("Editar outro registro?(S/N)");
        fflush(stdin);
        outro=getch() ;
    }
    funcaoRetorno();
}

void funcaoRetorno(void)
{
    {
        printf(" Pressione ENTER para voltar ao menu principal");
    }
a:
    if(getch()==13) //permite apenas o uso do ENTER
        main();
    else
        goto a;
}
int getDados()
{
    int t;
    gotoxy(20,3);
    printf("Digite a informacao abaixo");
    gotoxy(20,4);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(20,5);
    printf("\xB2");
    gotoxy(46,5);
    printf("\xB2");
    gotoxy(20,6);
    printf("\xB2");
    gotoxy(46,6);
    printf("\xB2");
    gotoxy(20,7);
    printf("\xB2");
    gotoxy(46,7);
    printf("\xB2");
    gotoxy(20,8);
    printf("\xB2");
    gotoxy(46,8);
    printf("\xB2");
    gotoxy(20,9);
    printf("\xB2");
    gotoxy(46,9);
    printf("\xB2");
    gotoxy(20,10);
    printf("\xB2");
    gotoxy(46,10);
    printf("\xB2");
    gotoxy(20,11);
    printf("\xB2");
    gotoxy(46,11);
    printf("\xB2");
    gotoxy(20,12);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(21,5);
    printf("Categoria:");
    gotoxy(32,5);
    printf("%s",categorias[s-1]);
    gotoxy(21,6);
    printf("Placa do carro:\t");
    gotoxy(37,6);
    scanf("%d",&t);
    if(checaPlaca(t) == 0)
    {
        gotoxy(21,13);
        printf("\aA Placa digitada ja existe no sitema\a");
        getch();
        main();
        return 0;
    }
    a.placa=t;
    gotoxy(21,7);
    printf("Modelo do carro:");
    gotoxy(38,7);
    scanf("%s",a.modelo);
    gotoxy(21,8);
    printf("Marca:");
    gotoxy(28,8);
    scanf("%s",a.Marca);
    gotoxy(21,9);
    printf("Quantidade:");
    gotoxy(33,9);
    scanf("%d",&a.quantidade);
    gotoxy(21,10);
    printf("Preco:");
    gotoxy(28,10);
    scanf("%f",&a.Preco);
    gotoxy(21,11);
    printf("Ano modelo:");
    gotoxy(33,11);
    scanf("%d",&a.anoModelo);
    return 1;
}
int checaPlaca(int t)  //checa se o carro existe na concessionaria ou nao
{
    rewind(fp);
    while(fread(&a,sizeof(a),1,fp)==1)
        if(a.placa==t)
            return 0;  //retorna 0 se o carro existir
    return 1; //retorna 1 caso nao exista
}
int t(void) //para o tempo
{
    time_t t;
    time(&t);
    printf("Data e Hora:%s\n",ctime(&t));

    return 0 ;
}

int tDevolucao(void)
{
    time_t dataDevolucao;
    time(&dataDevolucao);

    struct tm *meuTempo = localtime(&dataDevolucao);
    printf("Deve ser devolvido em %i/%i/%i\n", meuTempo->tm_mday+RETURNTIME, meuTempo->tm_mon+1, meuTempo->tm_year+1900);
}

int tLocacao(void)
{
    time_t dataLocacao;
    time(&dataLocacao);

    struct tm *meuTempo = localtime(&dataLocacao);
    printf("Foi alugado em %i/%i/%i\n", meuTempo->tm_mday, meuTempo->tm_mon+1, meuTempo->tm_year+1900);
}

void protegidoPorSenha(void) //para a parte protegida por senha
{

    system("cls");
    char d[25]="Protegido por senha";
    char ch,pass[10];
    int i=0,j;
    gotoxy(10,4);
    for(j=0; j<20; j++)
    {
        Sleep(50);
        printf("*");
    }
    for(j=0; j<20; j++)
    {
        Sleep(50);
        printf("%c",d[j]);
    }
    for(j=0; j<20; j++)
    {
        Sleep(50);
        printf("*");
    }
    gotoxy(10,10);
    gotoxy(15,7);
    printf("Digite a senha:");

    while(ch!=13)
    {
        ch=getch();

        if(ch!=13 && ch!=8)
        {
            putch('*');
            pass[i] = ch;
            i++;
        }
    }
    pass[i] = '\0';
    if(strcmp(pass,senha)==0)
    {

        gotoxy(15,9);
        printf("Senha correta");
        gotoxy(17,10);
        printf("Pressione qualquer tecla para continuar.....");
        getch();
        main();
    }
    else
    {
        gotoxy(15,16);
        printf("\aAVISO! Senha incorreta");
        getch();
        protegidoPorSenha();
    }
}
void informacoesAlugado()  //mostra infromaçoes sobre o carro alugado
{
    system("cls");
    gotoxy(10,8);
    printf("O carro foi alugado por %s",a.nomeLocatario);
    gotoxy(10,9);
    printf("Data de locacao:%d-%d-%d",a.dataAlugado.dd,a.dataAlugado.mm,a.dataAlugado.yy);
    gotoxy(10,10);
    printf("Data de devolucao:%d-%d-%d",a.dataDevolucao.dd,a.dataDevolucao.mm,a.dataDevolucao.yy);
}
