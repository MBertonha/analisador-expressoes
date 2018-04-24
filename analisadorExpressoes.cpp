/*
*************************************************
Tradutor de expressões                          *
Matheus Martins Bertonha      Nº120116          *
*************************************************
*/

#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<stack>
#include "tokens.h"

using namespace std;

string posFixa(string expressao);
string separaExpressao(string expressao);
int calcula(string expressao);

int calcula(string expressao){
    int resposta = 0;
    int aux = 0;
    int atual;
    char c;
    stack<int> P;

    for(int i=0; i<expressao.length(); i++){  //passando os caracteres na pilha
        c = expressao[i];
        if(isNumber(expressao[i])){
            aux = c - 48;
            P.push(aux);   //coloca o aux no top da pilha
        }
        else if(isOperador(expressao[i])){
            if(expressao[i] == '+'){
                resposta += P.top();
                P.pop();
                while(!P.empty()){         //Enquanto a pilha não estiver vazia
                    resposta += P.top();   //acessa o 1 elemento do topo na resposta
                    P.pop();               //limpa o topo da pilha
                }
                P.push(resposta);
            }
            else if(expressao[i] == '-'){
                aux = P.top();
                P.pop();
                resposta += P.top();
                P.pop();
                resposta -= aux;
            }
            else if(expressao[i] == '*'){
                resposta += P.top();
                P.pop();
                while(!P.empty()){                   //Enquanto a pilha não estiver vazia
                    resposta = resposta * P.top();   //acessa o 1 elemento do topo na resposta
                    P.pop();                         //limpa o topo da pilha
                }
                P.push(resposta);
            }
            else if(expressao[i] == '/'){
                aux = P.top();
                P.pop();
                resposta += P.top();
                P.pop();
                resposta = resposta/aux;
            }
             else if(expressao[i] == '%'){
                aux = P.top();
                P.pop();
                resposta += P.top();
                P.pop();
                resposta = resposta%aux;
            }
        }
    }
    resposta = P.top();
    return resposta;
}

string posFixa(string expressao){              // Função que avalia a expressão
	stack<char> S;                             //Inicialização de uma pilha vazia para os operadores
	string pos_fix = "";
	for(int i = 0; i< expressao.length();i++){
		if(expressao[i] == ' ' || isAtt(expressao[i] || isVariaveis(expressao[i]))){  //ignora espaço, " = " e variaveis
            continue;
		}
		else if(isOperador(expressao[i])){     //Se o caracter for um operador irá inserir dois elementos na pilha
			while(!S.empty()){                 //Enquanto a pilha não estiver vazia
				pos_fix += S.top();            // Adiciona ao 'posfix' o elemento do topo
				S.pop();                       //Remove o elemento do topo
			}
			S.push(expressao[i]);              //Insere o elemento atual na pilha
		}
		else if(isNumber(expressao[i])){       //Caso seja um operando
			pos_fix += expressao[i];
		}
	}
	while(!S.empty()){
		pos_fix += S.top();
		S.pop();
	}
	return pos_fix;
}

string separaExpressao(string expressao){
    string saida = "";
    for(int i=0; i <expressao.length(); i++){
        if(isVariaveis(expressao[i]) || isAtt(expressao[i])){
            saida += expressao[i];
        }
        else{
            break;
        }
    }
    return saida;
}

int definePilha(string expressao, int valida){
    for(int i=0; i <expressao.length(); i++){
        if(expressao[i] == 'x' || expressao[i] == 'X'){
            valida = 1;
        }
        else if(expressao[i] == 'y' || expressao[i] == 'Y'){
            valida = 2;
        }
    }
    return valida;
}

void saidaUsuario(stack<char> Z, stack<char> Y, stack<char> X, int saida){
    saida += X.top();
    saida += Y.top();
    Z.push(saida);
    cout<< saida << endl;
}

int analisaExpressao(string expressao){
    int analisador = 0;
    if(expressao[0] == 'z' || expressao[0] == 'Z'){
        //é sinal que vai ser a atribuição
        analisador = 1;
    }
    return analisador;
}
int main(){
    int i=1;
    int valida = 0;
    int saida = 0;
    int analisador = 0;
    stack<char> Z;
    stack<char> X;
    stack<char> Y;
    while(i!=0){
        string armazenamento = "";
        string expressao;
        FILE *arq;
        getline(cin,expressao);
        analisador = analisaExpressao(expressao);
        if(analisador != 1){
            string pos_fix = posFixa(expressao);
            string comeco = separaExpressao(expressao);
            valida = definePilha(comeco, valida);
            int resposta = calcula(pos_fix);
            cout << "\n"<< comeco << resposta << "\n";
            if(valida == 1){
                if(!X.empty()){
                    X.pop();
                }
                X.push(resposta);
            }
            else if(valida == 2){
                if(!Y.empty()){
                    Y.pop();
                }
                Y.push(resposta);
            }

        }
        else if(analisador == 1){
            saidaUsuario(Z,Y,X,saida);
        }
    }
return 0;
}
