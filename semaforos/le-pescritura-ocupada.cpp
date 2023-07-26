#include <iostream>
#include <thread>
#include <semaphore.h>
using namespace std;

//SEGUNDO CASO : PRIORIDAD EN LA ESCRITURA (CON ESPERA OCUPADA)

sem_t mutex;
int lec, nee;
bool writing;

void lector(){
    //while(true){
        //PROTOCOLO DE ENTRADA
        sem_wait(&mutex);
        //MIENTRAS EXISTEN ESCRITORES EN ESPERA O ALGUN ESCRITOR
        //ESTE ESCRIBIENDO ESPERAR
        while (writing == true || nee > 0 ){
            sem_post(&mutex);
            sem_wait(&mutex);
        }

        lec = lec + 1;
        sem_post(&mutex);
        cout << "\nLEER DEL RECURSO";
        //PROTOCOLO DE SALIDA
        sem_wait(&mutex);
        lec = lec - 1;
        sem_post(&mutex);
    //}
}

void escritor(){
    //while(true){
        sem_wait(&mutex);
        //MIENTRAS ALGUN ESCRITOR ESTE ACCEDIENDO AL RECURSO
        //O EXISTAN LECTORES LEYENDO HAY QUE ESPERAR
        nee = nee + 1;
        while (writing == true || lec > 0 ){
            sem_post(&mutex);
            sem_wait(&mutex);
        }

        writing = true;
        nee = nee - 1;
        sem_post(&mutex);
        cout << "\nESCRIBIR RECURSO";
        sem_wait(&mutex);
        writing = false;
        sem_post(&mutex);
    //}
}

int main()
{
    int n = 10;
    thread LE[n];
    thread ES[n];

    sem_init(&mutex, 0, 1);
    writing = false;
    lec = 0;
    nee = 0;

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