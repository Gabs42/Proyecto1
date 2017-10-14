#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;
typedef struct memoria{
    char* key;
    void *memoria_real;
    bool activo;
    bool en_uso;
    memoria *memoriaSiguiente;
    int size;
}*ptrmemoria;
ptrmemoria puntero;
void inicializarMemoria();
void verLista();
void insertarEnMemoria(ptrmemoria memoria);

int main(){
    inicializarMemoria();
    int client, server;
    int portNum = 1500;
    bool isExit = false;
    int bufsize = 1024;
    char buffer[bufsize];
    ptrmemoria recivo = new(memoria);
    struct sockaddr_in server_aadr;
    socklen_t size;
    client = socket(AF_INET, SOCK_STREAM,0);
    if(client<0){
        cout <<"Error de coneccion."<< endl;
        exit(1);
    }
    cout <<"Socket creado coneccion establecida."<< endl;
    server_aadr.sin_family = AF_INET;
    server_aadr.sin_addr.s_addr = htons(INADDR_ANY);
    server_aadr.sin_port = htons(portNum);
    if(bind(client,(struct sockaddr*)&server_aadr,sizeof(server_aadr))<0){
        cout << "Error coneccion de socket"<<endl;
        exit(1);
    }
    size = sizeof(server_aadr);
    cout<<"Buscando usuario"<<endl;
    listen(client,1);
    server = accept(client,(struct sockaddr*)&server_aadr,&size);
    if(server<0){
        cout << "Error"<<endl;
        exit(1);
    }
    while(server>0){
        strcpy(buffer,"Server conectado\n");
        send(server,buffer,bufsize,0);
        cout<<"Connectado a usuario"<<endl;
        cout << "Presion # para terminar coneccion"<<endl;
        cout <<"Usuario:" ;
        do{
            recv(server,recivo,40,0);
            insertarEnMemoria(recivo);
            cout<<puntero->size<< " ";
            cout<<recivo->size<<" ";
            *buffer = '*';
            if(*buffer == '#'){
                *buffer='*';
                isExit =true;
            }
        }while(*buffer != '*');
        do{
            cout<<"\nServer: ";
            do{
                cin>> buffer;
                send(server,buffer,bufsize,0);
                if(*buffer == '#'){
                    send(server,buffer,bufsize,0);
                    *buffer = '*';
                    isExit = true;
                }
            }while(*buffer != '*');
            cout << "Usuario: ";
            do{
                recv(server,recivo,40,0);
                insertarEnMemoria(recivo);
                cout<<puntero->size;
                cout<<recivo->size<<" ";
                if(*buffer == '#'){
                    *buffer == '*';
                    isExit = true;
                }
            }while(*buffer != '*');
        }while(!isExit);
        cout<<"Coneccion terminada"<<endl;
        isExit = false;
        exit(1);
    }
    close(client);
    return 0;
}
void inicializarMemoria(){
    puntero = new(memoria);
    puntero->memoria_real = operator new(125);
    int x = 1;
    ptrmemoria memActual = puntero;
    while(x!=33){
        ptrmemoria punteroNuevo = new(memoria);
        punteroNuevo->memoria_real = operator new(125);
        memActual->memoriaSiguiente = punteroNuevo;
        memActual = punteroNuevo;
        x = x+1;
    }
}
void insertarEnMemoria(ptrmemoria memoria){
    ptrmemoria memActual = puntero;
    while(memActual!=NULL){
        if(memoria->key==memActual->key){
            break;
        }
        else{
            if (memActual->key == nullptr){
                memActual->key = memoria->key;
                memActual->size = memoria->size;
                memActual->memoria_real = memoria->memoria_real;
                memActual->activo = memoria->activo;
                memActual->en_uso = memoria->en_uso;
            }
            memActual = memActual->memoriaSiguiente;
        }
    }
}
void verLista(){
    ptrmemoria memActual = puntero;
    while(memActual!=NULL){
        cout << memActual->key <<endl;
        memActual = memActual->memoriaSiguiente;
    }
    /*
    inicializarMemoria();
    int client, server;
    int portNum = 1500;
    bool isExit = false;
    int bufsize = 1024;
    char buffer[bufsize];
    struct sockaddr_in server_aadr;
    socklen_t size;
    client = socket(AF_INET, SOCK_STREAM,0);
    if(client<0){
        cout <<"Error de coneccion."<< endl;
        exit(1);
    }
    cout <<"Socket creado coneccion establecida."<< endl;
    server_aadr.sin_family = AF_INET;
    server_aadr.sin_addr.s_addr = htons(INADDR_ANY);
    server_aadr.sin_port = htons(portNum);
    if(bind(client,(struct sockaddr*)&server_aadr,sizeof(server_aadr))<0){
        cout << "Error coneccion de socket"<<endl;
        exit(1);
    }
    size = sizeof(server_aadr);
    cout<<"Buscando usuario"<<endl;
    listen(client,1);
    server = accept(client,(struct sockaddr*)&server_aadr,&size);
    if(server<0){
        cout << "Error"<<endl;
        exit(1);
    }
    while(server>0){
        strcpy(buffer,"Server conectado\n");
        send(server,buffer,bufsize,0);
        cout<<"Connectado a usuario"<<endl;
        cout << "Presion # para terminar coneccion"<<endl;
        cout <<"Usuario:" ;
        do{
            recv(server,buffer,bufsize,0);
            cout<<buffer<<" ";
            if(*buffer == '#'){
                *buffer='*';
                isExit =true;
            }
        }while(*buffer != '*');
        do{
            cout<<"\nServer: ";
            do{
                cin>> buffer;
                send(server,buffer,bufsize,0);
                if(*buffer == '#'){
                    send(server,buffer,bufsize,0);
                    *buffer = '*';
                    isExit = true;
                }
            }while(*buffer != '*');
            cout << "Usuario: ";
            do{
                recv(server,buffer,bufsize,0);
                cout<<buffer<<" ";
                if(*buffer == '#'){
                    *buffer == '*';
                    isExit = true;
                }
            }while(*buffer != '*');
        }while(!isExit);
        cout<<"Coneccion terminada"<<endl;
        isExit = false;
        exit(1);
    }
    close(client);
     */
}
