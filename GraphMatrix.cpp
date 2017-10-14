//
// Created by Edzia on 2017-04-29.
//

#include "GraphMatrix.h"
#include <fstream>

GraphMatrix::GraphMatrix() {
    vertexes = 0;
    edges = 0;
    density = 0;
    matrix = NULL;
}

/*GraphMatrix::GraphMatrix(int size) {
    matrix = new int *[size];
    for (int i = 0; i < size; i++){
        matrix[i] = new int[size];
    };
    vertexes = size;
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if (i==j) matrix[i][j] = -1;
            else
                matrix[i][j] = rand()%10;
        }
    }
}*/

GraphMatrix::~GraphMatrix() {
    if (matrix != NULL){
        for (int i = 0; i < vertexes; i++){
            if (matrix[i] != NULL) delete[] matrix[i];
        }
        delete[] matrix;
    }
}

void GraphMatrix::loadFromFile(std::string filename) {
    std::ifstream fin;
    fin.open(filename.c_str());
    fin >> edges;
    fin >> vertexes;
    this->countDensity();

    this->createMatrix(vertexes);

    int startVertex;
    int endVertex;
    int length;
    for (int i = 0; i < edges; i++){
        fin >> startVertex;
        fin >> endVertex;
        fin >> length;
        if (matrix[startVertex][endVertex] == 0)
            matrix[startVertex][endVertex] = length;
    }

    this->countEdges();
}

void GraphMatrix::print(std::ostream &str) const {
    str.flags ( std::ios::right);
    str.width (4);
    str << "    ";
    for (int i = 0; i < vertexes; i++){
        str.width (4);
        str << i << " ";
    }
    str << std::endl;
    for (int i = 0; i < vertexes; i++){
        str.width (4);
        str << i << "  ";
        for (int j = 0; j < vertexes; j++){
            str.width (4);
            str << matrix[i][j] << " ";
        }
        str << std::endl;
    }
}

void GraphMatrix::createMatrix(int v) {
    if (matrix != NULL) {
        for (int i = 0; i < vertexes; i++){
            if (matrix[i] != NULL) delete[] matrix[i];
        }
        delete[] matrix;
    }

    this->vertexes = v;
    matrix = new int *[v];
    for (int i = 0; i < v; i++){
        matrix[i] = new int[v];
    };
    for (int i = 0; i < v; i++){
        for (int j = 0; j < v; j++){
            matrix[i][j] = 0;
        }
    }
}

void GraphMatrix::countEdges() {
    edges = 0;
    for (int i = 0; i < vertexes; i++){
        for (int j = 0; j < vertexes; j++){
            if (matrix[i][j] != 0)
                edges++;
        }
    }
}

void GraphMatrix::createRandom(int vertexes, int density) {
    createMatrix(vertexes);
    this->vertexes = vertexes;
    this->density = density;
    this->edges = ((vertexes*vertexes - vertexes) * density)/100;

    int startVertex;
    int endVertex;
    int length;
    bool again;
    for (int i = 0; i < edges; i++){
        do {
            again = true;
            startVertex = i%vertexes;
            endVertex = rand()%vertexes;
            length = rand()%10+1;
            if (startVertex != endVertex){
                if (matrix[startVertex][endVertex] == 0){
                    matrix[startVertex][endVertex] = length;
                    again = false;
                }
            }

        }while (again);
    }
}

int **GraphMatrix::toSortedArray() {
    int **result = new int*[edges];
    for (int i = 0; i < edges; i++){
        result[i] = new int[3]; // 0 - od, 1 - do, 2 - dlugosc
    }

    int index = 0;
    for (int i = 0; i < vertexes; i++){
        for (int j = 0; j < vertexes; j++){
            if (matrix[i][j] > 0){
                result[index][0] = i;
                result[index][1] = j;
                result[index][2] = matrix[i][j];
                index++;
            }
        }
    }

    //sortowanie babelkowe
    for (int i = 0; i < index; i++){
        for (int j = 0; j < index-1; j++){
            if (result[i][2] < result[j][2]){
                for (int w = 0; w <3; w++){
                    int tmp = result[i][w];
                    result[i][w] = result[j][w];
                    result[j][w] = tmp;
                }

            }
        }
    }

    return result;
}

/*Array2 * GraphMatrix::getNeighbours(int index) {
    Array2 *result = new Array2[3]; //1 -sasiad, 2 - dlugosc, 0-obecny wierzcholek

    for (int i = 0; i < this->getNumberOfVertexes(); i++){
            if (matrix[index][i] != 0 && result[1].findElement(i) == -1){
                result[0].addElement(index,0);
                result[1].addElement(i,0);
                result[2].addElement(matrix[index][i],0);
            }
    }

    return result;
}*/

void GraphMatrix::makeBothWays() {
    for (int i = 0; i < this->vertexes; i++){
        for (int j = 0; j < this->vertexes; j++){
            if (this->matrix[i][j] != 0){
                this->matrix[j][i] = this->matrix[i][j];
            }
        }
    }
    this->countEdges();
}

/*Array2 * GraphMatrix::toArray() {
    Array2 *l = new Array2[3];

    for (int i = 0; i < vertexes; i++){
        for (int j = 0; j < vertexes; j++){
            if (matrix[i][j] != 0){
                l[0].addElement(i,0);
                l[1].addElement(j,0);
                l[2].addElement(matrix[i][j],0);
            }
        }
    }
    return l;
}*/

void GraphMatrix::setEdge(int start, int end, int length) {
    matrix[start][end] = length;
}

int GraphMatrix::getEdgeLength(int start, int end) {
    return matrix[start][end];
}



