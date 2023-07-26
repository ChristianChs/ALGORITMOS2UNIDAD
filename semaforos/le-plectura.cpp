#include <iostream>
#include <thread>
#include <semaphore.h>
using namespace std;

//PRIMER CASO : PRIORIDAD EN LA LECTURA

sem_t mutex, wrt;
int lec;

void lector(){
    //while(true){
        //PROTOCOLO DE ENTRADA
        sem_wait(&mutex);
        lec = lec + 1;
        if (lec == 1) { sem_wait(&wrt); }
        sem_post(&mutex);
        cout << "LEER DEL RECURSO\n";
        sem_wait(&mutex);
        lec = lec - 1;
        //PROTOCOLO DE SALIDA
        if ( lec == 0 ) { sem_post(&wrt); }
        sem_post(&mutex);
    //}
}

void escritor(){
    //while(true){
        //PROTOCOLO DE ENTRADA
        sem_wait(&wrt);
        cout << "ESCRIBIR RECURSO\n";
        //PROTOCOLO DE SALIDA
        sem_post(&wrt);
    //}
}

int main()
{
    int n = 10;
    thread LE[n];
    thread ES[n];

    sem_init(&wrt, 0, 1);
    sem_init(&mutex, 0, 1);
    lec = 0;

    for(int i = 0; i < n; i++){
        LE[i] = thread(lector);
        ES[i] = thread(escritor);
    }

    for(int i = 0; i < n; i++){
        LE[i].join();
        ES[i].join();
    }


    return 0;
}