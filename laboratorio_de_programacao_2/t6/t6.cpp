#define CATCH_CONFIG_MAIN
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
struct Abb {
    T dado;
    Abb<T>* esq;
    Abb<T>* dir;
    int altura;
};

template<typename T>
bool abb_vazio(Abb<T>* no){

    return (no == nullptr);

}

template<typename T>
int abb_altura(Abb<T>* no){

    if( abb_vazio(no) ){

        return 0;
    
    }
    return no->altura;

}

template<typename T>
int abb_get_fb(Abb<T>* no){

    if( abb_vazio(no) ){

        return 0;
    
    }
    return (abb_altura(no->esq) - abb_altura(no->dir));

}

template<typename T>
Abb<T>* abb_inicia(T v){

    Abb<T>* no = new Abb<T>;
    no->dado = v;
    no->altura = 1;
    no->esq = nullptr;
    no->dir = nullptr;

    return no;
}

template<typename T>
Abb<T>* abb_inicia(std::list<T>& entrada){

    Abb<T>* no = nullptr;
    if(entrada.empty() == true){

      return nullptr;
    
    }

    for(auto it = entrada.begin(); it != entrada.end(); it++){
      no = abb_insere( no, *it );
    }
    return no;

}  

template<typename T>
Abb<T>* abb_cria(T v){

    Abb<T>* no = new Abb<T>;
    no->dado = v;
    no->altura = 1;
    no->esq = nullptr;
    no->dir = nullptr;

    return no;

}

template<typename T>
Abb<T>* abb_rot_dir(Abb<T>* &no){

    Abb<T>* aux = no->esq;
    no->esq = aux->dir;
    aux->dir = no;
    no->altura = max(abb_altura(no->esq), abb_altura(no->dir)) + 1;
    aux->altura = max(abb_altura(aux->esq), no->altura) + 1;
    return aux;

}

template<typename T>
Abb<T>* abb_rot_esq(Abb<T>* &no){

    Abb<T>* aux = no->dir;
    no->dir = aux->esq;
    aux->esq = no;
    no->altura = max(abb_altura(no->esq), abb_altura(no->dir)) + 1;
    aux->altura = max(abb_altura(no->dir), no->altura) + 1;
    return aux;

}

template<typename T>
Abb<T>* abb_rot_esq_2(Abb<T>* &no){

    no->dir = abb_rot_dir(no->dir);
    return abb_rot_esq(no);

}

template<typename T>
Abb<T>* abb_rot_dir_2(Abb<T>* &no){

    no->esq = abb_rot_esq(no->esq);
    return abb_rot_dir(no);

}

template<typename T>
Abb<T>* abb_insere(Abb<T>* no, T v){

    if(no == nullptr){

        no = new Abb<T>;
        no->dado = v;
        no->altura = 0;
        no->esq = no->dir = nullptr;
    
    }else if(v < no->dado){

        no->esq = abb_insere(no->esq, v);
        if(abb_altura(no->esq) - abb_altura(no->dir) == 2){

            if(v < no->esq->dado)
                no = abb_rot_dir(no);
            else
                no = abb_rot_dir_2 (no);
        
        }

    }else if(v > no->dado){

        no->dir = abb_insere(no->dir, v);
        if(abb_altura(no->dir) - abb_altura(no->esq) == 2){

            if(v > no->dir->dado){

                no = abb_rot_esq(no);
            
            }else{

                no = abb_rot_esq_2(no);
            
            }
        }

    }

    no->altura = max(abb_altura(no->esq), abb_altura(no->dir)) + 1;

    return no;

}

template<typename T>
Abb<T>* abb_no_minimo( Abb<T>* no ){

    Abb<T>* curr = no;
    while( curr->esq != nullptr )
        curr = curr->esq;
    return curr;

}

template<typename T>
Abb<T>* abb_remove(Abb<T>* no, T v){

    Abb<T>* aux;

    if(no == nullptr){

        return nullptr;
    
    }else if(v < no->dado){
     
        no->esq = abb_remove(no->esq, v);
    
    }else if(v > no->dado){

        no->dir = abb_remove(no->dir, v);
    
    }else if(no->esq && no->dir){

        aux = abb_no_minimo(no->dir);
        no->dado = aux->dado;
        no->dir = abb_remove(no->dir, no->dado);
    
    }else{

        aux = no;
        if(no->esq == nullptr){

            no = no->dir;
        
        }else if(no->dir == nullptr){

            no = no->esq;
        
        }
        delete aux;
    
    }

    if(no == nullptr){

        return no;
    
    }

    no->altura = max(abb_altura(no->esq), abb_altura(no->dir)) + 1;

    if(abb_altura(no->esq) - abb_altura(no->dir) == -2){

        if(abb_altura(no->dir->dir) - abb_altura(no->dir->esq) == 1){

            return abb_rot_esq(no);
        
        }else{

            return abb_rot_esq_2(no);
        
        }

    }else if(abb_altura(no->dir) - abb_altura(no->esq) == 2){

        if(abb_altura(no->esq->esq) - abb_altura(no->esq->dir) == 1){

            return abb_rot_dir(no);
        
        }else{

            return abb_rot_dir_2(no);
        
        }
    }
    return no;

}

template<typename T>
void abb_preOrdem(Abb<T>* a, std::list<T>& saida){

    if( !abb_vazio(a) ){
    
        saida.push_back( a->dado );
        abb_preOrdem(a->esq, saida);
        abb_preOrdem(a->dir, saida);
    
    }

}   

template<typename T>
void abb_destroi(Abb<T>* a){

    if( !abb_vazio(a) ){
    
        abb_destroi(a->esq);
        abb_destroi(a->dir);
        delete a;
    
    }

}

TEST_CASE("Teste vazio") {
    Abb<int>* a;
    std::list<int> entrada {};
    a= abb_inicia(entrada);
    REQUIRE(abb_vazio(a) == true);
    abb_destroi(a);
}

TEST_CASE("Teste nao vazio") {
    Abb<int>* a;
    std::list<int> entrada {1};
    a= abb_inicia(entrada);
    REQUIRE(abb_vazio(a) == false);
    abb_destroi(a);
}


TEST_CASE("Caso 0") {
    Abb<int>* a;
    std::list<int> entrada {5, 3, 7};
    std::list<int> saida;
    std::list<int> resultado {5, 3, 7};
    a = abb_inicia(entrada);
    abb_preOrdem(a, saida);
    REQUIRE(saida == resultado);
    abb_destroi(a);
}

TEST_CASE("Caso ER") {
    Abb<int>* a;
    std::list<int> entrada {1, 2, 3};
    std::list<int> saida;
    std::list<int> resultado {2, 1, 3};
    a = abb_inicia(entrada);
    abb_preOrdem(a, saida);
    REQUIRE(saida == resultado);
    abb_destroi(a);
}

TEST_CASE("Caso DR") {
    Abb<int>* a;
    std::list<int> entrada {3, 2, 1};
    std::list<int> saida;
    std::list<int> resultado {2, 1, 3};
    a = abb_inicia(entrada);
    abb_preOrdem(a, saida);
    REQUIRE(saida == resultado);
    abb_destroi(a);
}

TEST_CASE("Caso DR-ER") {
    Abb<int>* a;
    std::list<int> entrada {5, 10, 7};
    std::list<int> saida;
    std::list<int> resultado {7, 5, 10};
    a = abb_inicia(entrada);
    abb_preOrdem(a, saida);
    REQUIRE(saida == resultado);
    abb_destroi(a);
}

TEST_CASE("Caso ER-DR") {
    Abb<int>* a;
    std::list<int> entrada {5, 1, 3};
    std::list<int> saida;
    std::list<int> resultado {3, 1, 5};
    a = abb_inicia(entrada);
    abb_preOrdem(a, saida);
    REQUIRE(saida == resultado);
    abb_destroi(a);
}

TEST_CASE("Caso DEL 0") {
    Abb<int>* a;
    std::list<int> entrada {5};
    a = abb_inicia(entrada);
    a = abb_remove( a, 5 );
    REQUIRE(abb_vazio(a) == true);
    abb_destroi(a);
}

TEST_CASE("Caso DEL 1") {
    Abb<int>* a;
    std::list<int> entrada {4, 2, 6, 7};
    std::list<int> saida;
    std::list<int> resultado {6, 4, 7};
    a = abb_inicia(entrada);
    a = abb_remove( a, 2 );
    abb_preOrdem(a, saida);
    REQUIRE(saida == resultado);
    abb_destroi(a);
}

TEST_CASE("Caso simples sequencial") {
    Abb<int>* a;
    std::list<int> entrada {1, 2, 3, 4, 5, 6, 7};
    std::list<int> saida;
    std::list<int> resultado {4, 2, 1, 3, 6, 5, 7};
    a = abb_inicia(entrada);
    abb_preOrdem(a, saida);
    REQUIRE(saida == resultado);
    abb_destroi(a);
}

TEST_CASE("Caso Notas MIT 2008") {
    Abb<int>* a;
    std::list<int> entrada {41, 20, 65, 11, 29, 50, 26, 23, 55};
    std::list<int> saida;
    std::list<int> resultado {41, 20, 11, 26, 23, 29, 55, 50, 65};
    a = abb_inicia(entrada);
    abb_preOrdem(a, saida);
    REQUIRE(saida == resultado);
    abb_destroi(a);
}

TEST_CASE("Caso N") {
    Abb<int>* a;
    std::list<int> entrada {50, 30, 24, 5, 28, 45, 98, 52, 60};
    std::list<int> saida;
    std::list<int> resultado {30, 26, 24, 28, 52, 50, 60};
    a = abb_inicia(entrada);
    a = abb_remove( a, 98 );
    a = abb_remove( a, 45 );
    a = abb_remove( a, 5 );
    a = abb_insere( a, 26 );
    abb_preOrdem(a, saida);
    REQUIRE(saida == resultado);
    abb_destroi(a);
}

TEST_CASE("Caso remove todos") {
    Abb<int>* a;
    std::list<int> entrada {41, 20, 65, 11, 29, 50, 26};
    std::list<int> saida;
    std::list<int> resultado {};
    a = abb_inicia(entrada);
    a = abb_remove(a, 41);
    a = abb_remove(a, 29);
    a = abb_remove(a, 50);
    a = abb_remove(a, 20);
    a = abb_remove(a, 26);
    a = abb_remove(a, 65);
    a = abb_remove(a, 11);
    abb_preOrdem(a, saida);
    REQUIRE(saida == resultado);
    abb_destroi(a);
}