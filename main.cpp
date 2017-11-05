#include <iostream>
#include <ctime>
#include "TravellingSalesmanProblem.h"

void test();
void test_both();

int main() {
    srand(time(NULL));

   TravellingSalesmanProblem * tsp = new TravellingSalesmanProblem;
    //tsp->menu();
    //tsp->loadFromFile("dane.txt");

    //tsp->generateRandom(20);
    //tsp->saveToFile("data_salesman.txt");
    //std::cout << tsp->testTime(3);
    tsp->loadFromFile("dane.txt");
    std::cout << tsp->bruteForce();
    delete tsp;


    //test();

    return 0;
}


void test(){
    TravellingSalesmanProblem *tsp = new TravellingSalesmanProblem();
    std::ofstream fout;
    fout.open("results_dp.txt");
    int size[] = {8, 10, 12, 14, 16, 18, 20, 22};
    for (int i = 0; i < 8; i++){ //rozmiar
        for (int j = 0; j < 100; j++){
            tsp->generateRandom(size[i]);
            //tsp->saveToFile("data_salesman.txt");
            fout << size[i] << " " << tsp->testTime(3)<< std::endl;
        }
    }

    fout.close();
    delete tsp;
}

void test_both(){
    TravellingSalesmanProblem *tsp = new TravellingSalesmanProblem();
    std::ofstream fout;
    fout.open("results_2.txt");
    int size[] = {8,9,10,11,12};
    for (int i = 0; i < 5; i++){ //rozmiar
        for (int j = 0; j < 100; j++){
            tsp->generateRandom(size[i]);
            tsp->saveToFile("data_salesman.txt");
            fout << size[i] << " " << tsp->testTime(0) << " " << tsp->testTime(3)<< std::endl;
        }
    }

    fout.close();
    delete tsp;
}