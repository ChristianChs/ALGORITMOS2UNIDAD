#include <iostream>
#include <semaphore.h>
#include <thread>
using namespace std;

/*  TERCERA SOLUCION    */

int palillo[5];
sem_t mutex;
sem_t pantalla; //CONTROLA IMPRESION EN PANTALLA

void filosofo(int i){
    while(true){
        sem_wait(&pantalla);
        cout << "FILOSOFO " << i << " :> PIENSA\n";
        sem_post(&pantalla);
        sem_wait(&mutex);
        while ( (palillo[i] == 0) || (palillo[(i+1) % 5] == 0) ){
            sem_post(&mutex);
            sem_wait(&mutex);
        }
        palillo[i] = 0;
        palillo[(i+1) % 5] = 0;
        sem_post(&mutex);
        sem_wait(&pantalla);
        cout << "FILOSOFO " << i << " :> COME\n";
        //cout << "\tpalillos usados : " << i << " y " << (i+1) % 5 << "\n\n";
        sem_post(&pantalla);
        sem_wait(&mutex);
        palillo[i] = 1;
        palillo[(i+1) % 5] = 1;
        sem_post(&mutex);
    }
}

int main()
{
    sem_init(&mutex,0,1);
    sem_init(&pantalla,0,1);
    thread F[5];

    for (int i = 0; i < 5; i++){
        palillo[i] = 1;
        F[i] = thread(filosofo,i);
    }

    for (int i = 0; i < 5; i++){
        F[i].join();
    }

    return 0;
}