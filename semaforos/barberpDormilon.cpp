#include <iostream>
#include <thread>
#include <semaphore.h>
using namespace std;

sem_t mutex, clientes, barber;
int enespera, n;
sem_t pantalla; //controla impresion en pantalla

void barbero(int i){
    while (true){
        do{
            sem_wait(&clientes);
            sem_wait(&mutex);
            enespera = enespera - 1;
            sem_post(&barber);
            sem_post(&mutex);
            sem_wait(&pantalla); //controla impresion en pantalla
            cout << "BARBERO " << i <<  " :CORTANDO EL CABELLO\n";
            sem_post(&pantalla); //controla impresion en pantalla
        } while (enespera != 0);
    }
}

void clientela(int i){
    while (true){
        sem_wait(&mutex);
        if (enespera < n){
            enespera =  enespera + 1;
            sem_wait(&pantalla); //controla impresion en pantalla
            cout << "CLIENTE " << i <<" :ESPERANDO\n";
            sem_post(&pantalla); //controla impresion en pantalla
            sem_post(&clientes);
            sem_post(&mutex);
            sem_wait(&barber);
        }
        else{
            sem_post(&mutex);
        }
    }
}

int main()
{
    sem_init(&mutex, 0, 1);
    sem_init(&clientes, 0, 0);
    sem_init(&barber, 0, 0);
    sem_init(&pantalla, 0, 1); //controla impresion en pantalla
    n = 5;
    enespera = 0;

    int clientess = 5;
    int barberos = 1;

    thread BR[barberos];
    thread C[clientess];

    for (int i = 0; i < clientess; i++){
        C[i] = thread(clientela, i + 1);
    }
    for (int i = 0; i < barberos; i++){
        BR[i] = thread(barbero, i + 1);
    }

    for (int i = 0; i < clientess; i++){
        C[i].join();
    }
    for (int i = 0; i < barberos; i++){
        BR[i].join();
    }

    return 0;
}