//
// Created by Edzia on 2017-05-21.
//

#ifndef SDIZO_3_TRAVELLINGSALESMANPROBLEM_H
#define SDIZO_3_TRAVELLINGSALESMANPROBLEM_H


#include "GraphMatrix.h"
#include <fstream>
#include <vector>

class TravellingSalesmanProblem{
private:
    GraphMatrix gm;
    int numberOfCities;
    int npow;
    int **g, **p;
    std::vector<int> arrayOfResults;

    int tsp_dp(int start, int set);
    void getPath(int start, int set);

public:
    TravellingSalesmanProblem();

    std::string bruteForce();

    std::string greedyAlgorithm();

    std::string localSearch();

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
