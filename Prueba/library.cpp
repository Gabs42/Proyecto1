#include "library.h"

#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <thread>
#include <unistd.h>
#include <signal.h>

using namespace std;
void copiarValor(char*key,void* t,int valueSize);
typedef class  memoria{
public:
    char key[6]="vacio";
    void *memoria_real;
    bool activo;
    bool en_uso;
    memoria *memoriaSiguiente=NULL;
    int size;
    int espacioMemoria;
    int operacion=1000;
    bool operator==(memoria mem){
        if(memcmp(this->key,mem.key,6)==0){
            return true;
        }
        else{
            return false;
        }
    }
    bool operator!=(memoria mem){
        if(memcmp(this->key,mem.key,6)!=0){
            return true;
        }
        else{
            return false;
        }
    }
    void operator=(memoria mem){
        copiarValor(this->key,mem.memoria_real,mem.size);
        this->memoria_real=mem.memoria_real;

    }
}*ptrmemoria;

ptrmemoria puntero = new(memoria);
int client;
bool salir = false;

void rm_init(int port,char* ipUsuario){
    int server;
    //int portNum = 1500;
    int portNum=port;
    bool isExit = false;
    int bufsize = 1024;
    char buffer[bufsize];
    //char *ip = "127.0.0.1";
    char *ip =ipUsuario;
    struct sockaddr_in server_addr = {};
    client = socket(AF_INET,SOCK_STREAM,0);
    if(client<0){
        cout<<"Error creando socket"<<endl;
        exit(1);
    }
    cout<<"Socket creado"<<endl;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNum);
    if(connect(client,(struct sockaddr*)&server_addr,sizeof(server_addr))==0){
        cout <<"Conectando a server"<<endl;
    }
    //recv(client,buffer,bufsize,0);
    cout <<"Coneccion establecida"<<endl;
    cout<<"# para terminar coneccion";
    /*
    do{
        cout <<"Usuario: ";
        do{
            cin>> buffer;
            send(client,puntero,40,0);
            if(*buffer=='#'){
                send(client,puntero,bufsize,0);
                *buffer = '*';
                isExit = true;
            }
        }while(*buffer != 42);
        cout<<"Server: ";
        do{
            recv(client,buffer,bufsize,0);
            cout<<buffer<<" ";
            if(*buffer == '#'){
                *buffer = '*';
                isExit = true;
            }
        }while(*buffer!=42);
        cout <<endl;
    }while(!isExit);
    cout<<"Coneccion terminada"<<endl;
    close(client);
     */

}
void rm_new(char* key,void* t,int valueSize){
    uint8_t bytes[valueSize]={0};
    puntero->memoria_real = t;
    memcpy(bytes,puntero->memoria_real,valueSize);
    strcpy(puntero->key,key);
    puntero->size = valueSize;
    puntero->activo = true;
    puntero->operacion=1000;
    send(client,puntero,48,0);
    send(client,bytes,valueSize,0);
}
void copiarValor(char*key,void* t,int valueSize){
    uint8_t bytes[valueSize]={0};
    memcpy(bytes,t,valueSize);
    strcpy(puntero->key,key);
    puntero->size = valueSize;
    puntero->operacion = 3;
    send(client,puntero,48,0);
    send(client,bytes,valueSize,0);
}
ptrmemoria rm_get(char* key){
    ptrmemoria  recivo = new(memoria);
    puntero->operacion = 1;
    strcpy(puntero->key,key);
    send(client,puntero,48,0);

    int prob=recv(client,recivo,48,0);
    if(strcmp(recivo->key,"vacio")==0){
        cout<<"No existe esa key"<<endl;
    }else{
        cout<<recivo->size<<endl;
        recivo->memoria_real = operator new(150);
        uint8_t bytes[recivo->size];
        recv(client,bytes,recivo->size,0);
        memcpy(recivo->memoria_real,bytes,recivo->size);
        cout<<*static_cast<int*>(recivo->memoria_real)<<endl;
        return recivo;
    }

}
void rm_delete(ptrmemoria  mem){
    mem->operacion=2;
    send(client,mem,48,0);
}
