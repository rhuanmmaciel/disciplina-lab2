#define CATCH_CONFIG_MAIN // O Catch fornece uma main()
#include "catch.hpp"

#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <functional>
#include <queue>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

template<typename T>
struct Arvore {

    T dado;
    Arvore<T>* esq;
    Arvore<T>* dir;
    bool possuiDados = false;

    void inicia(list<T> entrada){

      if(!entrada.empty()){
        
        possuiDados = true;
        Arvore<T>* no;

        dado = entrada.front();
        esq = nullptr;
        dir = nullptr;

        entrada.pop_front();

        while(!entrada.empty()){

          no = new Arvore<T>;
          no->inicializacao(entrada.front());
          entrada.pop_front();
          insere( no );

        }
  
      }    
    }

    void inicializacao(T v){

      dado = v;
      esq = nullptr;
      dir = nullptr;

    }

    void insere( Arvore<T>* no ){

        if( no->dado < dado ){

            if( esq == nullptr ){

                esq = no;

            }else{

                esq->insere( no );
            
            }

        }else {

            if( dir == nullptr ){

                dir = no;
            
            }else{

                dir->insere( no );
            
            }
        }
    }

    void posOrdem(list<T>& saida){

       if(esq != nullptr){

              esq->posOrdem(saida);

        }

        if(dir != nullptr){

              dir->posOrdem(saida);

        }

        saida.push_back(dado);

    } 

    bool vazio(){

      return !possuiDados;

    }  

    void destroi(void){

        if(possuiDados){

          destruir();

        }

    }

    void destruir(){

      if( esq != nullptr ){

        esq->destruir();
        delete esq;

        }

      if( dir != nullptr ){

        dir->destruir();
        delete dir;

      }

    }
};

TEST_CASE("Teste vazio") {
    Arvore<int> a;
    std::list<int> entrada {};
    a.inicia(entrada);
    REQUIRE(a.vazio() == true);
    a.destroi();
}

TEST_CASE("Teste nao vazio") {
    Arvore<int> a;
    std::list<int> entrada {1};
    a.inicia(entrada);
    REQUIRE(a.vazio() == false);
    a.destroi();
}

TEST_CASE("Caso 1") {
    Arvore<int> a;
    std::list<int> entrada {5, 3, 7};
    std::list<int> saida;
    std::list<int> resultado {3, 7, 5};
    a.inicia(entrada);
    a.posOrdem(saida);
    REQUIRE(saida == resultado);
    a.destroi();
}

TEST_CASE("Caso 3") {
    Arvore<char> a;
    std::list<char> entrada {'F', 'C', 'A', 'D', 'J', 'H', 'I', 'K'};
    std::list<char> saida;
    std::list<char> resultado {'A', 'D', 'C', 'I', 'H', 'K', 'J', 'F'};
    a.inicia(entrada);
    a.posOrdem(saida);
    REQUIRE(saida == resultado);
    a.destroi();
}

TEST_CASE("Caso N") {
    Arvore<int> a;
    std::list<int> entrada {50, 30, 24, 5, 28, 45, 98, 52, 60};
    std::list<int> saida;
    std::list<int> resultado {5, 28, 24, 45, 30, 60, 52, 98, 50};
    a.inicia(entrada);
    a.posOrdem(saida);
    REQUIRE(saida == resultado);
    a.destroi();
}