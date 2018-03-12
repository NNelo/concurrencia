#ifndef CONCURRENCY_TIMER_H
#define CONCURRENCY_TIMER_H

#include <ctime>
#include <iostream>

using namespace std;

class timer {
private:
    clock_t inicio;
    clock_t fin;
public:
    timer() : inicio(0) {}

    void begin() {
        inicio = clock();
    }

    void end() {
        fin = clock();
    }

    void show() {
        cout << double(fin - inicio) / CLOCKS_PER_SEC << endl;
    }
};

#endif //CONCURRENCY_TIMER_H