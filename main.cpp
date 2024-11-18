#include<bits/stdc++.h>
#define nl std::cout<<"\n";

//endereço fisico = 0ex00FF
//endereço virtual = 0vx000FF


// inicializados com -1 para indicar que não foram modificados
typedef struct{
    std::string tag = "-1"; //virtual page number
    std::string PPN = "-1"; //physical page number
} TLB;


std::vector<TLB> itensTLB(1);

std::vector<std::string> enderecoFisico(256);
std::vector<std::string> enderecoVirtual(4096);


std::string checkTLB(std::string endereco, char tipo){
    tipo = toupper(tipo);

    //para virtual
    if(tipo == 'V'){
        for(int i=0; i<itensTLB.size(); i++){
            if(itensTLB[i].PPN == endereco){
                std::cout << "endereco encontrado pela TLB.(hit)";nl
                return itensTLB[i].tag;
            }
        }
    }
    
    //para fisico
    else if(tipo == 'P'){
        for(int i=0; i<itensTLB.size(); i++){
            if(itensTLB[i].tag == endereco){
                std::cout << "endereco encontrado pela TLB.(hit)";nl
                return itensTLB[i].PPN;
            }
        }
    }

    std::cout << "endereco não encontrado pela TLB.(miss)";nl
    return "-1"; // TLB miss

}

int freePositionTLB(){
    //checar se tem espaço na TLB
    for(int i=0; i < itensTLB.size(); i++){
        if(itensTLB[i].tag == "-1"){
            return i;
        }
    }
    return -1; //sem espaço
}

void TLBwrite(std::string tag, std::string enderecoFisico){
    int posicao = freePositionTLB(); 
    if(posicao == -1){ //sem espaço
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<>dist(0,9);
        int posicaoAleatoria = dist(gen);
        std::cout << "TLB cheia, retirando item " << posicaoAleatoria;nl
        itensTLB[posicaoAleatoria] = {tag, enderecoFisico};
        std::cout << "tag nova: " << itensTLB[posicaoAleatoria].tag;nl
        std::cout << "PPN nova: " << itensTLB[posicaoAleatoria].PPN;nl
    }
    else{
        std::cout << "Gravado na posicao " << posicao << " da TLB.";nl
        itensTLB[posicao] = {tag, enderecoFisico};
        std::cout << "tag nova: " << itensTLB[posicao].tag;nl
        std::cout << "PPN nova: " << itensTLB[posicao].PPN;nl
    }
}

//terminar essa função
std::string toVirtual(std::string endereco){
    std::string pagina = endereco.substr(0,4);//0003204
    std::cout << "endereco em toVirtual: " << endereco;nl
    std::cout << "pagina em toVirtual: " << pagina;nl
    std::string outputTLB = checkTLB(pagina, 'V');
    if(outputTLB == "-1"){
        std::cout << "Traduzindo manualmente o endereço físico para virtual...";nl
        //traduz manualmente
        int paginaInt = std::stoi(pagina, nullptr, 16);
        std::cout << "paginaInt: " << paginaInt;nl
        if(paginaInt < enderecoVirtual.size() and paginaInt > 0){
            std::string novoEnderecoVirtual = "0" + enderecoFisico[paginaInt];
            // Atualiza a TLB
            std::string novaPagina = "0" + pagina;
            TLBwrite(novoEnderecoVirtual, novaPagina);//grava na TLB
            std::cout << "Endereco gravado na TLB.";nl
            return novoEnderecoVirtual;//retorna a tradução
        }
        else{
            std::cout << "Endereço virtual não encontrado.";nl
            return "-1"; // Não foi possível traduzir
        }
    }
    else{
        return outputTLB;
    }
}

//terminar essa função
std::string toPhisic(std::string endereco){
    std::string pagina = endereco.substr(0,5);//00003204
    std::cout << "endereco em toPhisic: " << endereco;nl
    std::cout << "pagina em toPhisic: " << pagina;nl
    std::string outputTLB = checkTLB(pagina, 'P');
    if(outputTLB == "-1"){
        std::cout << "Traduzindo manualmente o endereço virtual para físico...";nl
        //traduz manualmente
        int paginaInt = std::stoi(pagina);
        std::cout << "paginaInt: " << paginaInt;nl
        if(paginaInt < enderecoFisico.size() and paginaInt > 0){
            std::string novoEnderecoFisico = enderecoFisico[paginaInt];
            // Atualiza a TLB
            TLBwrite(pagina, novoEnderecoFisico);//grava na TLB
            std::cout << "Endereco gravado na TLB.";nl
            return novoEnderecoFisico;//retorna a tradução
        }
        else{
            std::cout << "Endereço virtual não encontrado.";nl
            return "-1"; // Não foi possível traduzir
        }
    }
    else{
        return outputTLB;
    }
}

int main(){
    //inicializar vetor enderecoVirtual
    for (int i = 0x00100; i <= 0x00FFF; i++){
        std::stringstream ss;
        ss << std::hex << std::setfill('0') << std::setw(5) << i;
        enderecoVirtual[i] = ss.str();
    }

    //inicializar vetor enderecoFisico
    for (int i = 0x0000; i <= 0x00FF; i++){
        std::stringstream ss;
        ss << std::hex << std::setfill('0') << std::setw(4) << i;
        enderecoFisico[i] = ss.str();
    }
    
    std::string input;
    do{
        std::cout << "---------------------------------------------------------------------------------------------------";nl
        std::cout << "Traducao de enderecos fisico para virtual e vice-versa.";nl
        std::cout << "Use 0ex = memoria fisica, 0vx = memoria virtual. Digite \"exit\" para sair.";nl
        std::cout << "Digite o endereco a ser traduzido: ";
        std::cin >> input;
        //input = 0vx00003204
        //prefixo = 0vx
        //pagina = 00003
        //offset = 204
        
        std::string prefixo = input.substr(0, 3);
        std::string endereco = input.substr(3);
        std::string paginaVirtual;
        std::string paginaFisica;
    
        if (input.length() < 4) {
            prefixo = "-1";
        }
    
        if(prefixo == "0ex"){
            std::string offset = endereco.substr(4);
            std::cout << "offset: " << offset;nl
            paginaVirtual = toVirtual(endereco);
            if(paginaVirtual != "-1"){
                std::cout << "Endereco fisico original: " << input;nl
                std::cout << "Endereco traduzido para virtual: " << "0vx" << paginaVirtual << offset;nl
            }
        }
        else if(prefixo == "0vx"){
            std::string offset = endereco.substr(5); //0vx00003204
            std::cout << "offset: " << offset;nl
            paginaFisica = toPhisic(endereco);
            if(paginaFisica != "-1"){
                std::cout << "Endereco virtual original: " << input;nl
                std::cout << "Endereco traduzido para fisico: " << "0ex" << paginaFisica<< offset;nl
            }
        }
        else{
            std::cout << "Endereco invalido.";nl
        }
    }while(input != "exit");
    
    return 0;
}