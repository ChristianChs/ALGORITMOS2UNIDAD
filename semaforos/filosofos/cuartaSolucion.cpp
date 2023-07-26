#include <iostream>
#include <semaphore.h>
#include <thread>
using namespace std;

/*  CUARTA SOLUCION    */

sem_t palillo[5];
sem_t pantalla; //CONTROLA IMPRESION EN PANTALLA

void filosofoPar(int i){
    while(true){
        sem_wait(&pantalla);
        cout << "FILOSOFO " << i << " :> PIENSA\n";
        sem_post(&pantalla);
        sem_wait(&palillo[ (i+1) % 5 ] );
        sem_wait(&palillo[i]);
        sem_wait(&pantalla);
        cout << "FILOSOFO " << i << " :> COME\n";
        //cout << "\tpalillos usados : " << i << " y " << (i+1) % 5 << "\n\n";
        sem_post(&pantalla);
        sem_post(&palillo[i]);
        sem_post(&palillo[ (i+1) % 5 ] );
    }
}

void filosofoImpar(int i){
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
    thread FP[5];
    thread FI[5];
    sem_init(&pantalla,0,1);

    /*  IMPARES: F0, F1    PARES: F2, F3, F4 */
    for (int i = 0; i < 5; i++){
        sem_init(&palillo[i],0,1);
        if(i == 0 || i == 1){
            FI[i] = thread(filosofoImpar,i);
        }
        else{
            FP[i] = thread(filosofoPar,i);
        }
    }

    for (int i = 0; i < 5; i++){
        if(i == 0 || i == 1){
            FI[i].join();
        }
        else{
            FP[i].join();
        }
    }

    return 0;
}