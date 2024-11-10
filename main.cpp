#include<bits/stdc++.h>
#define nl std::cout<<"\n";

//endereço fisico = 0exFFFF
//endereço virtual = 0vx0001

std::vector<int> memoriaFisica(1024, -1);
std::vector<int> memoriaVirtual(2048, -1);
std::vector<int> TLB(10, -1);

int checkTLB(int endereco){
    for(int i=0; i<TLB.size()-1; i++){
        if(TLB[i] == endereco){
            std::cout << "endereco encontrado pela TLB.(hit)";nl
            return TLB[i];
        }
    }

    std::cout << "endereco não encontrado pela TLB.(miss)";nl
    return -1;

}


int toVirtual(int endereco){
    
}

int toPhisic(int endereco){

}


int main(){

    std::cout << "traducao de enderecos fisico para virtual e vice-versa.\nDigite o endereco a ser traduzido: ";
    std::string input;
    std::cin >> input;
    

    if (input.length() < 4) {
        std::cout << "Endereco inválido.";nl
        return 1;
    }

    std::string prefixo = input.substr(0, 3);
    std::string endereco = input.substr(3);
    int enderecoInt = std::stoi(endereco);

    if(prefixo == "0ex"){
        int enderecoVirtual = toVirtual(enderecoInt);
    }
    else if(prefixo == "0vx"){
        int enderecoFisico = toPhisic(enderecoInt);
    }
    else{
        std::cout << "Endereco inválido.";nl
    }

}