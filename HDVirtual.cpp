#include <iostream>
#include <vector>
#include <sstream>
#include <string.h>
#include <cstdlib>
#include <stdio.h>

using namespace std;

string palavrasReservadas[] = {{"createhd"},{"selecthd"},{"create"},{"type"}};
int i = 0;
int a = 0;
int y = 0;
int w = 0;
int wi = 21;
int aa = 0;
int aux = 0;

class HDVirtual{

    public:
    char tamanho[1024][34];
    string nome;
    int linhaF;

    HDVirtual(){
		linhaF = 21;
	}

};

char populaHD(char hdVirtual[][34]){

	for (int i=0; i < 1024; i++){

	hdVirtual[i][0] = '0';
	hdVirtual[i][33] = '\n';

	}
	
    for (int i=0; i < 21; i++){

	hdVirtual[i][1] = '0';

	}
	for (int i=21; i < 1024; i++){

	hdVirtual[i][1] = '1';
	}
}

void salvaHD(char hdVirtual[1024][34], string nomeS){

    char a[100];

    //Convertendo string para char (Fopen só aceita char).
    stringstream ss;
    ss << nomeS;
    ss >> a;

    //Concatenando vetor char " a " com " .txt ".
    strcat(a,".txt");

    FILE *FP;
	FP = fopen(a,"w");
	for (int i=0;i<1024;i++)
	{
	    for (int j=0;j<32;j++){
	    fprintf (FP, "%c",hdVirtual[i][j]);
	}
    	fprintf (FP,"\n");
	}
	fclose (FP);
}
     
//Divide o input em vetores string, através do espaço.
vector<string> fragmenta(string divide, char limitador) {
   
    vector<string> internal;
    stringstream x(divide); 
    string tok;
        
    while(getline(x, tok, limitador)) {
    internal.push_back(tok);
    }
        
    return internal;
}

void imprimirEscopo(){
    puts("\n===============================================================================");
    printf("                           HD Virtual:\n");
    puts("===============================================================================");
    printf("\n Comandos:    Exemplos:                   Descricao:\n");
    printf("\n createhd     createhd HDTeste            Cria um HD virtual");
    printf("\n selecthd     selecthd HDTeste            Seleciona o HD virtual existem");
    printf("\n create       create arquivo_nomes        Cria pasta ou arquivo");  
    printf("\n remove       remove arquivo_nomes        Remove pasta ou arquivo");
    printf("\n type         type arquivo_nomes          Nao implementado");
    printf("\n sair         sair                        Na tela principal encerra o programa \n\n# ");
}
     
int main(int argc, char **argv) {

    //Criando vetor com classes HDVirtual.
    vector<HDVirtual> varioshds;
    string divide, divideSelect;
    char digitado[50] = {0};

    imprimirEscopo();

    while(true){

    while(getline(cin, divide)){
    cout << "# ";
    if (divide != ""){
        break;}
    }
    vector<string> sep = fragmenta(divide, ' ');

    if( divide == "sair" ) {
        exit(0);
    }

    // Ativando comando para criar HD.
    if(sep[0] == "createhd"){
        
        HDVirtual hd;
        hd.nome = sep[1];
        varioshds.push_back(hd);

        populaHD(varioshds[i].tamanho);
        salvaHD(varioshds[i].tamanho, varioshds[i].nome);
        cout << "HD: " << varioshds[i].nome << " criado.\n# ";
        i++;
    }

   // Ativando comando para selecionar HD.
    if(sep[0] == "selecthd"){
        
        
        // Procura no vector de HD's o HD com o nome que a pessoa digitou.
        for(a = 0; a < i; a++){
            if(sep[1] == varioshds[a].nome){
                cout << "HD: " << varioshds[a].nome << " selecionado.\n# " << varioshds[a].nome << "> ";
                while(getline(cin, divideSelect)){
                    cout << "# " << varioshds[a].nome << ">";
                    if (divideSelect != ""){
                        break;}
                }
               

                vector<string> sepSelect = fragmenta(divideSelect, ' ');
                
                // Ativando comando para criar arquivo.
                if(sepSelect[0] == "create"){

                    int x = 0;
                    char ystr[4];
                    aux = 0;
                    char digitado1[100] = {0};

                    vector<string> arquivoPasta = fragmenta(sepSelect[1], '_');
                    

                    if(arquivoPasta[0] == "arquivo"){
                        cout << " Digite o conteudo do arquivo: \n# " << varioshds[a].nome << "> ";
                        std::cin.getline (digitado1, 100);
                        cout << "# ";
                    }
                    if(arquivoPasta[0] == "pasta" ){
                        *digitado1 = ' ';
                    }

                    /*

                     ======================= Bloco de Diretório =======================
                    
                    */

                    // Byte 1: Função procura nos blocos de 0 até 20 um vazio.
                    for(x = 0; x < 20; x++){

                        if(varioshds[a].tamanho[x][0] == '0') {
                            varioshds[a].tamanho[x][0] = '1';
                            break;
                        }
                    }
                   
                
                    // Byte 2: 0 até 20 é diretorio (valor 0), do 20 até o fim é arquivo (valor 1). Feito préviamente ao criar HD(txt).

                    // Byte 3: Arquivo == 0    //    Pasta == 1.
                    if(arquivoPasta[0] == "arquivo"){
                    varioshds[a].tamanho[x][2] = '0';
                    }
                    if(arquivoPasta[0] == "pasta"){
                    varioshds[a].tamanho[x][2] = '1'; 
                    }

                    // Byte 4: Reservado.
                    varioshds[a].tamanho[x][3] = 'R'; 

                    // Byte 5 até 8: Numero da pasta onde estará o arquivo. Se for na Root = 0 0 0 0.
                    varioshds[a].tamanho[x][4] = '0';
                    varioshds[a].tamanho[x][5] = '0';
                    varioshds[a].tamanho[x][6] = '0';
                    varioshds[a].tamanho[x][7] = '0';

                    // Byte 9 até 12: Arquivo começa na linha 21. Número no blocos de arquivos onde começa o arquivo.
                    for(y = 21; y < 1024; y++){

                        if(varioshds[a].tamanho[y][0] == '0') {

                           // varioshds[a].tamanho[y][0] = '1'; // Linha y = 1 // Ocupada.
                       
                            sprintf(ystr, "%i", y+1); //Transforma int em string. Resultado: 22.

                            if(y < 100){
                                varioshds[a].tamanho[x][8] = '0';
                                varioshds[a].tamanho[x][9] = '0';
                                varioshds[a].tamanho[x][10] = ystr[0];
                                varioshds[a].tamanho[x][11] = ystr[1];  
                            }
                            if(y >= 100 && y < 1000){
                                varioshds[a].tamanho[x][8] = '0';
                                varioshds[a].tamanho[x][9] = ystr[0];
                                varioshds[a].tamanho[x][10] = ystr[1];
                                varioshds[a].tamanho[x][11] = ystr[2];  
                            }
                            if(y >= 1000){
                                varioshds[a].tamanho[x][8] = ystr[0];
                                varioshds[a].tamanho[x][9] = ystr[1];
                                varioshds[a].tamanho[x][10] = ystr[2];
                                varioshds[a].tamanho[x][11] = ystr[3];  
                            }

                            break;
                        }
                    }
                     

                    // Byte 13 até 16: Quantidades de bytes do arquivo.

                    if(arquivoPasta[0] == "pasta"){
                    varioshds[a].tamanho[x][12] = '0';
                    varioshds[a].tamanho[x][13] = '0';
                    varioshds[a].tamanho[x][14] = '0';
                    varioshds[a].tamanho[x][15] = '0'; 
                    }
                    else{

                    int contaLetra = 0;
                    char letraContada[4] = {0};
                    for(int s = 0; s < 100; s++){
                    contaLetra++;
                    if(digitado1[s] == '\0'){
                        break;
                    }
                    }

                    sprintf(letraContada, "%i", contaLetra-1); //Transforma int em string.
                    
                            if(contaLetra < 100){
                                varioshds[a].tamanho[x][12] = '0';
                                varioshds[a].tamanho[x][13] = '0';
                                varioshds[a].tamanho[x][14] = letraContada[0];
                                varioshds[a].tamanho[x][15] = letraContada[1];  
                            }
                            if(contaLetra >= 100 && y < 1000){
                                varioshds[a].tamanho[x][12] = '0';
                                varioshds[a].tamanho[x][13] = letraContada[0];
                                varioshds[a].tamanho[x][14] = letraContada[1];
                                varioshds[a].tamanho[x][15] = letraContada[2];  
                            }
                            if(contaLetra >= 1000){
                                varioshds[a].tamanho[x][12] = letraContada[0];
                                varioshds[a].tamanho[x][13] = letraContada[1];
                                varioshds[a].tamanho[x][14] = letraContada[2];
                                varioshds[a].tamanho[x][15] = letraContada[3];  
                            }
                    }

                    // Byte 17 até 32: Nome da pasta ou arquivo.
                    char nomeArquivoPasta[15] = {0};
                    //Convertendo string para char (Fopen só aceita char).
                    stringstream ss;
                    ss << sepSelect[1];
                    ss >> nomeArquivoPasta;                    

                    for(int z = 16; z < 31; z++){
                    varioshds[a].tamanho[x][z] = nomeArquivoPasta[z-16];
                    }

                    /*

                     ======================= Bloco de Arquivo =======================
                    
                    */

                    // Byte 1: Previamente colocado na parte do Bye 9 até 12 do diretório.
                    
                                        // Byte 1: Função procura nos blocos de 0 até 20 um vazio.
                    for(w = 0; w < 20; w++){

                        if(varioshds[a].tamanho[w][0] == '0') {
                            varioshds[a].tamanho[w][0] = '1';
                            break;
                        }
                    }

                    // Byte 2: Previamente colocado ao criar HD(txt).

                    // Byte 3 e 4: Reservado.

                    varioshds[a].tamanho[y][2] = 'R';
                    varioshds[a].tamanho[y][3] = 'R';  

                    // Byte 5 até 8: Numero do próximo bloco caso não coube o arquivo.
                    
                    char digitado[100];

                    strcpy (digitado, digitado1);

                        for(w = varioshds[a].linhaF; w < 1024; w++){
                                varioshds[a].tamanho[w][2] = 'R';
                                varioshds[a].tamanho[w][3] = 'R';  
                            for(int g = 8; g < 31; g++){

                                varioshds[a].tamanho[w][g] = digitado[aux];
                                aux++;
                                if(digitado[aux] == '\0'){
                                break;}
                            }
                                                
                        if( w == varioshds[a].linhaF &&  strlen(digitado) < 24  ) {
                        varioshds[a].tamanho[y][4] = '0';
                        varioshds[a].tamanho[y][5] = '0';
                        varioshds[a].tamanho[y][6] = '0';
                        varioshds[a].tamanho[y][7] = '0';
                        varioshds[a].tamanho[y][0] = '1'; // Linha y = 1 // Ocupada.
                        y++;
                        varioshds[a].linhaF++;
                        }
                        
                        if(digitado[aux] == '\0' &&  strlen(digitado) < 24  ){
                                                
                        break;}

                        if(w > varioshds[a].linhaF){
                        
                        char numstr[1];
                        
                        sprintf(numstr, "%i", w+1);

                        varioshds[a].tamanho[y][4] = '0';
                        varioshds[a].tamanho[y][5] = '0';
                        varioshds[a].tamanho[y][6] = numstr[0];
                        varioshds[a].tamanho[y][7] = numstr[1];
                        varioshds[a].tamanho[y][0] = '1'; // Linha y = 1 // Ocupada.
                        y++;
                        varioshds[a].linhaF++;
                        }

                        if(digitado[aux] == '\0' &&  strlen(digitado) >= 24  ){
                        varioshds[a].tamanho[y][4] = '0';
                        varioshds[a].tamanho[y][5] = '0';
                        varioshds[a].tamanho[y][6] = '0';
                        varioshds[a].tamanho[y][7] = '0';
                        varioshds[a].tamanho[y][0] = '1'; // Linha y = 1 // Ocupada.
                        y++;
                        varioshds[a].linhaF++;                      
                        break;
                        }
                        }

                    salvaHD(varioshds[a].tamanho, varioshds[a].nome);
                    cout << "[Arquivo de nome: " << sepSelect[1] << " criado com sucesso!]\n# ";
                }

                if(sepSelect[0] == "remove"){

                    char paraRemover[23] = {0};
                    int achou = 0;
                    int q1, q2;
                    int varia = 0;
                    //Convertendo string para char (Fopen só aceita char).
                    stringstream ss;
                    ss << sepSelect[1];
                    ss >> paraRemover;

                    char posicaoDel[4];


                    for(q1 = 0; q1 < 1024; q1++){
						varia = 0;
                        for(q2 = 16; q2 < 32; q2++){
     					

						//	cout << varioshds[a].tamanho[q1][q2] << " " << paraRemover[varia];

                            if(varioshds[a].tamanho[q1][q2] != paraRemover[varia]){

								break;
                            }

                            if( q2 == 31 ){

                                    //Concatenando tudo em um unico vetor char para transformar em int.
                                    posicaoDel[0] = varioshds[a].tamanho[q1][8];
                                    posicaoDel[1] = varioshds[a].tamanho[q1][9];
                                    posicaoDel[2] = varioshds[a].tamanho[q1][10];
                                    posicaoDel[3] = varioshds[a].tamanho[q1][11];
                                    posicaoDel[4] = '\0';

                                    // Removendo linha;
                                    varioshds[a].tamanho[q1][0] = '0';
                                    // Atoi transforma char para int.
                                    varioshds[a].tamanho[atoi(posicaoDel)-1][0] = '0';
                                    
                                    cout << atoi(posicaoDel);

                                    achou = 1;
                                    break;

                        }

                        varia++;
                        }
                        if(achou == 1){

                            achou = 0;
                            break;
                        }
                    }

                    salvaHD(varioshds[a].tamanho, varioshds[a].nome);
                    cout << " [Arquivo de nome: " << sepSelect[1] << " removido com sucesso!]\n# ";
                }

            }
        }
    }
}

}
