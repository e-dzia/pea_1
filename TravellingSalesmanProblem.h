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
    long long int npow;
    int **subproblems, **path;
    std::vector<int> arrayOfResults;

    int dp_func(int start, long long int visited);
    void dp_getPath(int start, int set);

public:
    TravellingSalesmanProblem();

    std::string bruteForce();

    std::string greedyAlgorithm();

    std::string localSearch();

    std::string dynamicProgramming();

    void loadFromFile(std::string filename);

    void generateRandom(int size);

    bool allVisited(bool pBoolean[]);

    void permute(int *permutation, int left, int right, int &min, std::string &result);

    void swap(int *pInt, int *pInt1);

    std::string countPath(int *permutation, int &min);

    double testTime(int algorithmType);

    void saveToFile(std::string filename);

    void menu();
};


#endif //SDIZO_3_TRAVELLINGSALESMANPROBLEM_H
