#include <iostream>
#include <semaphore.h>
#include <thread>
using namespace std;

/*  PRIMERA SOLUCION    */

sem_t palillo[5];
sem_t pantalla; //CONTROLA IMPRESION EN PANTALLA

void filosofo(int i){
    while(true){
        sem_wait(&pantalla);
        cout << "FILOSOFO " << i << " :> PIENSA\n";
        sem_post(&pantalla);
        sem_wait(&palillo[i]);
        sem_wait(&palillo[ (i+1) % 5 ] );
        sem_wait(&pantalla);
        cout << "FILOSOFO " << i << " :> COME\n";
        //cout << "\tpalillos usados : " << i << " y " << (i+1) % 5 << "\n\n";
        sem_post(&pantalla);
        sem_post(&palillo[i]);
        sem_post(&palillo[ (i+1) % 5 ] );
    }
}

int main()
{

    thread F[5];
    sem_init(&pantalla,0,1);

    for (int i = 0; i < 5; i++){
        sem_init(&palillo[i],0,1);
        F[i] = thread(filosofo,i);
    }

    for (int i = 0; i < 5; i++){
            F[i].join();
    }

    return 0;
}