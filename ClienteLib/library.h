#ifndef CLIENTELIB_LIBRARY_H
#define CLIENTELIB_LIBRARY_H

typedef class  memoria *ptrmemoria;
void rm_init(int port,char* ipUsuario);
void rm_new(char* key,void* t,int valueSize);
ptrmemoria rm_get(char* key);
void rm_delete(ptrmemoria  mem);
void copiarValor(char*key,void* t,int valueSize);
#endif