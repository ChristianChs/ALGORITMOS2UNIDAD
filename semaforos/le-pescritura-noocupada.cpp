#include <iostream>
#include <thread>
#include <semaphore.h>
using namespace std;

//TERCER CASO : PRIORIDAD EN LA ESCRITURA (SIN ESPERA OCUPADA)

sem_t mutex, writer, reader;
int lec, nee, nle;
bool writing;

void lector(){
    //while(true){

        sem_wait(&mutex);

        if ( writing == true || nee > 0 ){
            nle = nle + 1;
            sem_post(&mutex);
            sem_wait(&reader);
            nle = nle - 1;
        }

        lec = lec + 1;

        if ( nle > 0 ) { sem_post(&reader); }
        else { sem_post(&mutex); }

        cout << "\nLEER DEL RECURSO";
        sem_wait(&mutex);
        lec = lec - 1;

        if (lec == 0 && nee > 0) { sem_post(&writer); }
        else { sem_post(&mutex); }
    //}
}

void escritor(){
    //while(true){
        sem_wait(&mutex);

        if ( writing == true || lec > 0 ){
            nee = nee + 1;
            sem_post(&mutex);
            sem_wait(&writer);
            nee = nee - 1;
        }

        writing = true;
        sem_post(&mutex);
        cout << "\nESCRIBIR RECURSO";
        sem_wait(&mutex);

        writing = false;

        if ( nee > 0 ) { sem_post(&writer); }
        else{
            if ( nle > 0 ) { sem_post(&reader); }
            else { sem_post(&mutex); }
        }
    //}
}

int main()
{
    int n = 10;
    thread LE[n];
    thread ES[n];

    sem_init(&mutex, 0, 1);
    sem_init(&writer, 0, 0);
    sem_init(&reader, 0, 0);
    writing = false;
    lec = 0;
    nee = 0;
    nle = 0;

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