#include<ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<stack>

int isOperador(char ch);
int isNumber(char ch);
int isVariaveis(char ch);
int isAtt(char ch);

int isNumber(char ch){
    int i,retorno = 0;
    for(i=0; i<10; i++){
        if(ch >= '0' && ch <= '9'){
           retorno = 1;
        }
    }
    return retorno;
}

int isOperador(char ch){
    int i,retorno = 0;
    for(i=0; i<5; i++){
        if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%'){
           retorno = 2;
        }
    }
    return retorno;
}

int isAtt(char ch){
    int i,retorno = 0;
    for(i=0; i<5; i++){
        if(ch == '='){
           retorno = 4;
        }
    }
    return retorno;
}

int isVariaveis(char ch){
    int i,retorno = 0;
    for(i=0; i<3; i++){
        if(ch >= 'a' && ch <= 'z'){
           retorno = 3;
        }
        if(ch >= 'A' && ch <= 'Z'){
           retorno = 3;
        }
    }
    return retorno;
}
