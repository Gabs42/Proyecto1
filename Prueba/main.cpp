#include <iostream>
#include "library.h"
#include "library.cpp"

int main(){
    int port=1500;
    char* ip="127.0.0.1";
    rm_init(port,ip);
    char* x="papas";
    int x2=480;
    char* y="pipas";
    int y2=5780;
    rm_new(y,&y2,sizeof(y2));
    rm_new(x,&x2,sizeof(x2));
    ptrmemoria mem = rm_get(x);
    ptrmemoria mem2 = rm_get(y);
    bool resultado = *mem==*mem2;
    cout<<resultado<<endl;
    resultado = *mem!=*mem2;
    cout<<resultado<<endl;
    *mem=*mem2;
    cout<<*static_cast<int*>(mem->memoria_real)<<endl;
    rm_delete(mem);
    ptrmemoria prueba = rm_get(x);
}