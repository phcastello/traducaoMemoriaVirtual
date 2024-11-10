#include<bits/stdc++.h>
#define nl std::cout<<"\n";

//endereço fisico = 0exFFFF
//endereço virtual = 0vx0001

std::string toVirtual(std::string endereco){
    
}

std::string toPhisic(std::string endereco){

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

    if(prefixo == "0ex"){
        std::string enderecoVirtual = toVirtual(endereco);
    }
    else if(prefixo == "0vx"){
        std::string enderecoFisico = toPhisic(endereco);
    }
    else{
        std::cout << "Endereco inválido.";nl
    }

}