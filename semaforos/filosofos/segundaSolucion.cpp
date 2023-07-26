#include <iostream>
#include <semaphore.h>
#include <thread>
using namespace std;

/*  SEGUNDA SOLUCION    */

sem_t palillo[5];
sem_t sitio;
sem_t pantalla; //CONTROLA IMPRESION EN PANTALLA

void filosofo(int i){
    while(true){
        sem_wait(&pantalla);
        cout << "FILOSOFO " << i << " :> PIENSA\n";
        sem_post(&pantalla);
        sem_wait(&sitio);
        sem_wait(&palillo[i]);
        sem_wait(&palillo[ (i+1) % 5 ] );
        sem_wait(&pantalla);
        cout << "FILOSOFO " << i << " :> COME\n";
        //cout << "\tpalillos usados : " << i << " y " << (i+1) % 5 << "\n\n";
        sem_post(&pantalla);
        sem_post(&palillo[i]);
        sem_post(&palillo[ (i+1) % 5 ] );
        sem_post(&sitio);
    }
}

int main()
{
    sem_init(&sitio,0,4);
    sem_init(&pantalla,0,1);
    thread F[5];

    for (int i = 0; i < 5; i++){
        sem_init(&palillo[i],0,1);
        F[i] = thread(filosofo,i);
    }

    for (int i = 0; i < 5; i++){
        F[i].join();
    }

    return 0;
}