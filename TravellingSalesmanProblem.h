//
// Created by Edzia on 2017-05-21.
//

#ifndef SDIZO_3_TRAVELLINGSALESMANPROBLEM_H
#define SDIZO_3_TRAVELLINGSALESMANPROBLEM_H


#include "GraphMatrix.h"
#include <fstream>

class TravellingSalesmanProblem{
private:
    GraphMatrix gm;
    int numberOfCities;

public:
    std::string bruteForce();

    std::string greedyAlgorithm();

    std::string dynamicProgramming();

    void loadFromFile(std::string filename);

    void generateRandom(int number, int size);

    bool allVisited(bool pBoolean[]);

    void permute(int *permutation, int left, int right, int &min, std::string &result);

    void swap(int *pInt, int *pInt1);

    std::string countPath(int *permutation, int &min);

    double testTime(int algorithmType);

    void saveToFile(std::string filename);

    void menu();
};


#endif //SDIZO_3_TRAVELLINGSALESMANPROBLEM_H
