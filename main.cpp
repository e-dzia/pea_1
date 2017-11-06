#include <iostream>
#include <ctime>
#include <Windows.h>
#include "TravellingSalesmanProblem.h"

void test();
void test_both();
double GetCounter();
void StartCounter();

double PCFreq = 0.0;
__int64 CounterStart = 0;

int main() {
    srand(time(NULL));

  /* TravellingSalesmanProblem * tsp = new TravellingSalesmanProblem;
    tsp->loadFromFile("dane.txt");

    tsp->menu();
    //tsp->generateRandom(4);
    //tsp->saveToFile("data_salesman.txt");
    //std::cout << tsp->testTime(3);
    //tsp->loadFromFile("dane.txt");
    //std::cout << tsp->localSearch();
    delete tsp;*/


    test_both();

    return 0;
}


void test(){
    TravellingSalesmanProblem *tsp = new TravellingSalesmanProblem();
    std::ofstream fout;
    fout.open("results_dponly.txt");
    int size[] = {8, 10, 12, 14, 16, 18, 20, 22};
    for (int i = 0; i < 8; i++){ //rozmiar
        for (int j = 0; j < 100; j++){
            tsp->generateRandom(size[i]);
            fout << size[i] << " " << tsp->testTime(3)<< std::endl;
        }
    }

    fout.close();
    delete tsp;
}

void test_both(){
    TravellingSalesmanProblem *tsp = new TravellingSalesmanProblem();
    std::ofstream fout;
    fout.open("results_both.txt");
    int size[] = {8,9,10,11,12};
    for (int i = 0; i < 5; i++){ //rozmiar
        for (int j = 0; j < 100; j++){
            tsp->generateRandom(size[i]);
            fout << size[i] << " " << tsp->testTime(0) << " " << tsp->testTime(3)<< std::endl;
        }
    }

    fout.close();
    delete tsp;
}

void StartCounter()
{
    LARGE_INTEGER li;
    if (!QueryPerformanceFrequency(&li))
        std::cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart) / 1000.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}

double GetCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart - CounterStart) / PCFreq;
}