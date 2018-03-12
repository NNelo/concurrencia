#include <iostream>
#include <thread>
#include <mutex>
#include "timer.h"
#include "msg_queue.h"

using namespace std;

mutex pantalla;

typedef struct {
    int inicio;
    int fin;
} par;

msg_queue<par> sms;

void tarea();

//void sleep(int s) {
//    clock_t begin;
//    begin = clock();
//    double elapsed_secs = 0;
//
//    while (elapsed_secs < s) {
//        elapsed_secs = double(clock() - begin) / CLOCKS_PER_SEC;
//    }
//}

//void hola() {
//
//    for (int i = 0; i < 5; i++) {
//        std::cout << "Hola " << i << std::endl;
//        sleep(2);
//    }
//}

bool esPrimo(unsigned int num) {
    for (unsigned int i = 2; i <= (num / 2); i++)
        if (num % i == 0)
            return false;


    return true;
}

#define CANT_HILOS 8
#define INTERVALO 500

int main() {
    thread *h[CANT_HILOS];
    timer temporizador;
//    par dato;
    unsigned int inicio = 2;
    unsigned int fin = 300000;
    unsigned int intervalo = (fin - inicio) / CANT_HILOS;

    temporizador.begin();

    for (int j = 0; j < CANT_HILOS; j++) {
        h[j] = new thread(tarea);
    }
    for (int i = 2; i < CANT_HILOS; i = i + INTERVALO) {
//        dato.inicio = i;
//        dato.fin = i + INTERVALO - 1;
//        sms.enqueue(dato);
        sms.enqueue({i, i + INTERVALO - 1});
    }

    for (auto &actual : h)
        actual->join();

    temporizador.end();
    cout << "tiempo ";
    temporizador.show();

    return 0;
}

void tarea() {
    par dato;
    dato = sms.dequeue();

    for (int i = dato.inicio; i < dato.fin; i++)
        if (esPrimo(i)) {
            pantalla.lock();
            std::cout << i << std::endl;
            pantalla.unlock();
        }
}