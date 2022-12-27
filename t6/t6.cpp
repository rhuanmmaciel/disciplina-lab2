//#define CATCH_CONFIG_MAIN 
//#include "catch.hpp"

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
bool abb_vazio(Abb<T>* no)
{
    return (no == nullptr);
}

template<typename T>
int abb_altura(Abb<T>* no)
{
    if( abb_vazio(no) )
        return 0;
    return no->altura;
}

template<typename T>
int abb_get_fb(Abb<T>* no)
{
    if( abb_vazio(no) )
        return 0;
    return (abb_altura(no->esq) - abb_altura(no->dir));
}

template<typename T>
Abb<T>* abb_esq_rotate(Abb<T>* x)
{
    // TODO: completar
    return x;
}

template<typename T>
Abb<T>* abb_dir_rotate(Abb<T>* x)
{
    // TODO: completar
    return x;
}

template<typename T>
Abb<T>* abb_inicia(T v)
{
    Abb<T>* no = new Abb<T>;
    no->dado = v;
    no->altura = 1;
    no->esq = nullptr;
    no->dir = nullptr;

    return no;
}

// recebe uma lista de valores
// precisa converter para uma arvore
template<typename T>
Abb<T>* abb_inicia(std::list<T>& entrada)
{
    Abb<T>* no = nullptr;
    if(entrada.empty() == true)
      return nullptr;

    for(auto it = entrada.begin(); it != entrada.end(); it++){
      no = abb_insere( no, *it );
    }
    return no;
}  

// insere um no pre-alocado na arvore
template<typename T>
Abb<T>* abb_insere( Abb<T>* no, T v )
{
    if( abb_vazio(no) )
        return abb_inicia(v);

    Abb<T>* filho = new Abb<T>;
    filho->esq = nullptr;
    filho->dir = nullptr;

    filho->dado = v;

    if (no->dado > v){
        no->esq = filho;
    }else{
        no->dir = filho;
    }


    return no;
}

template<typename T>
Abb<T>* abb_no_minimo( Abb<T>* no )
{
    Abb<T>* curr = no;
    while( curr->esq != nullptr )
        curr = curr->esq;
    return curr;
}

// insere um no pre-alocado na arvore
template<typename T>
Abb<T>* abb_remove( Abb<T>* no, T v )
{
    if( abb_vazio(no) )
        return no;

    // TODO: completar
    return no;
}

template<typename T>
void abb_preOrdem(Abb<T>* a, std::list<T>& saida)
{
    // primeiro esquerda
    if( !abb_vazio(a) ){
        cout << a->dado << "(" << a->altura << ") ";
        saida.push_back( a->dado );
        abb_preOrdem(a->esq, saida);
        abb_preOrdem(a->dir, saida);
    }
}   

template<typename T>
void abb_destroi(Abb<T>* a)
{
    if( !abb_vazio(a) ){
        abb_destroi(a->esq);
        abb_destroi(a->dir);
        delete a;
    }
}

int main(){

    Abb<int>* a;
    list<int> entrada {1, 2, 3};
    a = abb_inicia(entrada);
    list<int> saida;
    abb_preOrdem(a, saida);

    for(auto it = saida.begin(); it != saida.end(); it++){
        
        cout << *it << endl;
    
    }

}

/*
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
}*/