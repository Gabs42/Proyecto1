#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>


using namespace std;
struct memoria{
    std::string key;
    void *memoria_real;
    bool activo;
    bool en_uso;
    memoria *memoriaSiguiente;
    int size;
    template<typename Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & key;
        ar & activo;
        ar & en_uso;
        ar & size;
    }
};

void rm_init(){
    int client, server;
    int portNum = 1500;
    bool isExit = false;
    int bufsize = 1024;
    char buffer[bufsize];
    char *ip = "127.0.0.1";
    struct sockaddr_in server_addr;
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
    recv(client,buffer,bufsize,0);
    cout <<"Coneccion establecida"<<endl;
    cout<<"# para terminar coneccion";
    do{
        cout <<"Usuario: ";
        do{
            cin>> buffer;
            send(client,buffer,40,0);
            if(*buffer=='#'){
                send(client,buffer,bufsize,0);
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

}

template<typename T>
void rm_new(char* key,T t,int valueSize){
    //puntero = new(memoria);
    //puntero->size = valueSize;
    //puntero->key = key;
}
int main(){
    /*
    memoria mem;
    mem.key = "papas";
    cout<<mem.key;
    std::ofstream ofs("memi");
    {
        boost::archive::text_oarchive oa(ofs);
        oa & mem;
    }
    memoria mem2 = {};
    {
        std::ifstream ifs("memi");
        boost::archive::text_iarchive ia(ifs);
        ia>>mem2;
    }
    cout<<mem2.key;
    char* key="papas";
    int x=2;
    //rm_new(key,x,sizeof(x));
     */
    //rm_init();
    //rm_init(ip,port);
    //char* ip;
    //cin>>ip;
    int client, server;
    int portNum = 1500;
    bool isExit = false;
    int bufsize = 1024;
    char buffer[bufsize];
    char *ip = "127.0.0.1";
    struct sockaddr_in server_addr;
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
    recv(client,buffer,bufsize,0);
    cout <<"Coneccion establecida"<<endl;
    cout<<"# para terminar coneccion";
    do{
        cout <<"Usuario: ";
        do{
            cin>> buffer;
            send(client,buffer,bufsize,0);
            if(*buffer=='#'){
                send(client,buffer,bufsize,0);
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



    return(0);
}