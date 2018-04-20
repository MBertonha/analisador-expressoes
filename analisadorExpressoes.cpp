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

int main(){
    string expressao;
    cout << "Expressao:  ";
    getline(cin,expressao);
    string pos_fix = posFixa(expressao);
    string comeco = separaExpressao(expressao);
    int resposta = calcula(pos_fix);
    cout << "\nSaida:  "<< comeco << resposta << "\n";
return 0;
}
