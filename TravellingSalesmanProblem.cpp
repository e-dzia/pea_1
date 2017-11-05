//
// Created by Edzia on 2017-05-21.
//

#include "TravellingSalesmanProblem.h"
#include <sstream>
#include <chrono>
#include <cmath>

std::string TravellingSalesmanProblem::bruteForce() {
    int start = 0;
    int *permutation = new int[numberOfCities];
    for (int i = 0; i < numberOfCities; i++){
        permutation[i] = i;
    }

    int min = INT32_MAX;
    std::string result = "";
    permute(permutation, 1, numberOfCities - 1, min, result);
    std::stringstream ss;
    ss << "Przeglad zupelny.\nWynik: " << std::endl;
    ss << result;

    ss << ": " << min << std::endl;
    return ss.str();
}

std::string TravellingSalesmanProblem::greedyAlgorithm() {
    bool visited[numberOfCities];
    int path[numberOfCities];
    int length = 0;

    for (int i = 0; i < numberOfCities; i++){
        visited[i] = false;
        path[i] = -1;
    }
    int start = 0;
    int i = start;

    while(!allVisited(visited)){
        visited[i] = true;
        int min = INT32_MAX;
        int position = -1;
        for (int j = 0; j < numberOfCities; j++){
            if (!visited[j] && gm.getEdgeLength(i,j) != -1 && gm.getEdgeLength(i,j)  < min){
                min = gm.getEdgeLength(i,j);
                position = j;
            }
        }
        if (min != INT32_MAX)
            length += min;
        else {
            length += gm.getEdgeLength(i,start);
        }
        path[i] = position;
        i = position;
    }


    std::stringstream ss;
    ss << "Algorytm zachlanny.\nWynik: " << std::endl;
    int j = start;
    ss << j << " ";
    while (path[j] != -1) {
        ss << path[j] << " ";
        j = path[j];
    }
    ss << ": " << length << std::endl;
    return ss.str();
}

std::string TravellingSalesmanProblem::localSearch() {
    bool visited[numberOfCities];
    int path[numberOfCities];
    int length = 0;

    for (int i = 0; i < numberOfCities; i++){
        visited[i] = false;
        path[i] = -1;
    }
    int start = 0;
    int i = start;

    while(!allVisited(visited)){
        visited[i] = true;
        int min = INT32_MAX;
        int position = -1;
        for (int j = 0; j < numberOfCities; j++){
            if (!visited[j] && gm.getEdgeLength(i,j) != -1 && gm.getEdgeLength(i,j)  < min){
                min = gm.getEdgeLength(i,j);
                position = j;
            }
        }
        if (min != INT32_MAX)
            length += min;
        else {
            length += gm.getEdgeLength(i,start);
        }
        path[i] = position;
        i = position;
    }
    int *permutation = new int[numberOfCities];
    int j = start;
    permutation[0] = start;
    std::string result = "";
    for (int i = 0; i < numberOfCities-1; i++){
        permutation[i+1] = path[j];
        j = path[j];
        int temp = permutation[i];
        std::string tmp = "";
        do {
            char ch = temp%10 + '0';
            temp /= 10;
            tmp += ch;
        }while(temp>0);
        for (int j = tmp.size()-1; j >= 0; j--){
            result += tmp[j];
        }
        result += " ";
    }
    result += (permutation[numberOfCities-1]+'0');

    for (int i = 1; i < numberOfCities-1; i++){
        swap(permutation+i,permutation+i+1);
        std::string result_tmp = countPath(permutation,length);
        if (result_tmp != ""){
            result = result_tmp;
        }
        else{
            swap(permutation+i,permutation+i+1);
        }
    }

    std::stringstream ss;
    ss << "Algorytm przeszukiwania lokalnego.\nWynik: " << std::endl;
    ss << result << " ";
    ss << ": " << length << std::endl;
    return ss.str();
}

std::string TravellingSalesmanProblem::dynamicProgramming() {
    npow2 = (long long int) pow(2, numberOfCities-1); //2^(numberOfCities-1)

    subproblems = new int*[numberOfCities]; //tabela dwuwymiarowa
    path = new int*[numberOfCities]; //tabela dwuwymiarowa
    for (int i = 0; i < numberOfCities; i++) {
        subproblems[i] = new int[npow2];
        path[i] = new int[npow2];

        for (int j = 0; j < npow2; j++) {
            subproblems[i][j] = -1;
            path[i][j] = -1;
        }
    }

    for (int i = 1; i < numberOfCities; i++) {
        subproblems[i][0] = gm.getEdgeLength(i,0);
    } //pierwsza kolumna - dane wejściowe, reszta -1
    int result = dp_func(0, npow2 - 1); //uruchom dp_func start = 0, set = npow2 - 1

    /*std::cout<<"\nsubproblems:";

    for(int i=0;i < npow2;i++)
    {
        std::cout<<"\n";
        for(int j=0;j < numberOfCities;j++)
            std::cout<<"\t"<<subproblems[j][i];
    }
    std::cout<<"\n\n";*/

    arrayOfResults.push_back(0); //wyjscie - dodaj 0 - początkowy element
    dp_getPath(0, npow2 - 1); //dp_getPath, start = 0, set = 2^numberOfCities - 2

    std::stringstream ss;
    ss << "Algorytm programowania dynamicznego.\nWynik: " << std::endl;
    for (auto &&item : arrayOfResults) {
        ss << item << " ";
    }
    ss << " : " << result << std::endl;


    for (int i = 0; i < numberOfCities; i++) {
        delete[] subproblems[i];
        delete[] path[i];

    }
    delete[] subproblems;
    delete[] path;

    return ss.str();
}

int TravellingSalesmanProblem::dp_func(int start, long long int visited) {
    long long int masked, mask;
    int result = -1, temp;

    if (subproblems[start][visited] != -1) {
        return subproblems[start][visited];
    } else {
        for (int i = 0; i < numberOfCities-1; i++) {
            mask = npow2 - 1 - (int) pow(2, i); //mask = 2^numberOfCities - 1 - 2^i
            masked = visited & mask; //maska binarna AND
            if (masked != visited) {
                temp = gm.getEdgeLength(start,i+1) + dp_func(i+1, masked); //droga od start do i + dp_func(i,masked)
                if (result == -1 || result > temp) {
                    result = temp;
                    path[start][visited] = i+1;
                }
            }
        }
        subproblems[start][visited] = result;
        return result;
    }
}

void TravellingSalesmanProblem::dp_getPath(int start, int visited) { //tu tylko znajduje trasę
    if (path[start][visited] == -1) {
        return;
    }
    int i = path[start][visited];
    int mask = npow2 - 1 - (int) pow(2, i-1);
    int masked = visited & mask;
    arrayOfResults.push_back(i);
    dp_getPath(i, masked);
}

void TravellingSalesmanProblem::permute(int *permutation, int left, int right, int &min, std::string &result) {
    int i;
    if (left == right){
        std::string result_tmp = countPath(permutation, min);
        if (result_tmp != ""){
            result = result_tmp;
        }
    }
    else
    {
        for (i = left; i <= right; i++)
        {
            swap((permutation+left), (permutation+i));
            permute(permutation, left + 1, right, min, result);
            swap((permutation+left), (permutation+i)); //powrót do poprzedniego
        }
    }

}

void TravellingSalesmanProblem::swap(int *pInt, int *pInt1) {
    int tmp = *pInt;
    *pInt = *pInt1;
    *pInt1 = tmp;
}

std::string TravellingSalesmanProblem::countPath(int *permutation, int &min) {
    int length = 0;
    int end;
    /* for (int i = 0; i < numberOfCities; i++){
         std:: cout << permutation[i];
     }
     std::cout << std::endl;*/
    for (int i = 1; i < numberOfCities; i++){
        length += gm.getEdgeLength(permutation[i-1],permutation[i]);
        end = i;
    }
    length += gm.getEdgeLength(permutation[end],permutation[0]);

    if (length < min){
        min = length;
        std::stringstream ss;
        for (int i = 0; i < numberOfCities; i++){
            ss << permutation[i] << " ";
        }
        return ss.str();
    }
    return "";
}

void TravellingSalesmanProblem::saveToFile(std::string filename) {
    std::ofstream fout;
    fout.open(filename.c_str());
    fout << numberOfCities << std::endl;
    for (int i = 0; i < numberOfCities; i++){
        for (int j = 0; j < numberOfCities; j++){
            int length = gm.getEdgeLength(i,j);
            fout << length << " ";
        }
        fout << std::endl;
    }
}

void TravellingSalesmanProblem::loadFromFile(std::string filename) {
    std::ifstream fin;
    fin.open(filename.c_str());
    fin >> numberOfCities;
    gm.createMatrix(numberOfCities);
    for (int i = 0; i < numberOfCities; i++){
        for (int j = 0; j < numberOfCities; j++){
            int length;
            fin >> length;
            if (length == -1) length = 0;
            gm.setEdge(i,j,length);
        }
    }
}

void TravellingSalesmanProblem::generateRandom(int size) {
    numberOfCities = size;
    gm.createRandom(numberOfCities,100);
    //gm.makeBothWaysEqual();
}

bool TravellingSalesmanProblem::allVisited(bool *visited) {
    for (int i = 0; i < numberOfCities; i++){
        if (!visited[i]) return false;
    }
    return true;
}

void TravellingSalesmanProblem::menu() {
    std::cout << "MENU - Problem komiwojazera\n"
            "1. Wczytaj z pliku \"dane.txt\".\n"
            "2. Generuj losowo.\n"
            "3. Przeglad zupelny.\n"
            "4. Algorytm zachlanny.\n"
            "5. Przeszukiwanie lokalne.\n"
            "6. Programowanie dynamiczne.\n"
            "7. Wyjdz.\n"
            "Prosze wpisac odpowiednia liczbe.\n";
    int chosen;
    std::cin >> chosen;
    switch(chosen){
        case 1:
            this->loadFromFile("dane.txt");
            break;
        case 2:
            std::cout << "Prosze podac liczbe miast.\n";
            int v;
            std::cin >> v;
            this->generateRandom(v);
            break;
        case 3:
            std::cout << "\n########################################\n" << this->bruteForce();
            break;
        case 4:
            std::cout << "\n########################################\n" << this->greedyAlgorithm();
            break;
        case 5:
            std::cout << "\n########################################\n" << this->localSearch();
            break;
        case 6:
            std::cout << "\n########################################\n" << this->dynamicProgramming();
            break;
        case 7:
            return;
        default:
            std::cout  << "Prosze podac poprawna liczbe.\n";
            std::cin.clear();
            std::cin.sync();
            break;
    }
    this->menu();
}

double TravellingSalesmanProblem::testTime(int algorithmType) {
    /*algorithmType:
     * 0 - bruteforce
     * 1 - zachłanny
     * 2 - przeszukiwanie lokalne
     * 3 - programowanie dynamiczne
     * */
    std::chrono::nanoseconds time_start;
    std::chrono::nanoseconds time_end;
    //double time_duration;

    //this->loadFromFile("data_salesman.txt");
    switch (algorithmType){
        case 0:
            time_start = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now().time_since_epoch());
            this->bruteForce();
            time_end = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now().time_since_epoch());
            break;
        case 1:
            time_start = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now().time_since_epoch());
            this->greedyAlgorithm();
            time_end = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now().time_since_epoch());
            break;
        case 2:
            time_start = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now().time_since_epoch());
            this->localSearch();
            time_end = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now().time_since_epoch());
            break;
        case 3:
            time_start = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now().time_since_epoch());
            this->dynamicProgramming();
            time_end = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now().time_since_epoch());
            break;
    }


    return (time_end - time_start) / std::chrono::nanoseconds(1);
}

TravellingSalesmanProblem::TravellingSalesmanProblem() {
    subproblems = NULL;
    path = NULL;
}
