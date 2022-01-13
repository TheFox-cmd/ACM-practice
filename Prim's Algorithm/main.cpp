//
//  main.cpp
//  Prim's Algorithm
//
//  Created by Ryuki Koda on 1/12/22.
//
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

#define INF 9999999
#define maxNumVertex 20

int numVertex, numEdge;
int edge[maxNumVertex][maxNumVertex];
int weight[maxNumVertex];

void prim(int start){
    int weightSum = 0;
    int preFlag = start;
    for(int i = 1; i <= numVertex; i++) weight[i] = edge[start][i];
    weight[start] = -1;
    for(int i = 1; i <= numVertex; i++){
        int flag = -1;
        int min = INF;
        for(int j = 1; j <= numVertex; j++){
            if(weight[j] != -1 && weight[j] < min){
                flag = j;
                min = weight[j];
            }
        }
        if(flag != -1){
            cout << preFlag << " " << flag << " " << weight[flag] << endl;
            preFlag = flag;
            weightSum += weight[flag];
            weight[flag] = -1;
            for(int j = 1; j <= numVertex; j++){
                if(weight[j] != -1) weight[j] = edge[flag][j];
            }
        }
    }
    cout << "Weight of MST is " << weightSum << endl;
}

int main(int argc, const char * argv[]) {
    cin >> numVertex >> numEdge;
    int vertexA, vertexB, weightAB;
    memset(edge, 0, sizeof(edge));
    for(int i = 1; i <= numEdge; i++){
        cin >> vertexA >> vertexB >> weightAB;
        edge[vertexA][vertexB] = edge[vertexB][vertexA] = weightAB;
    }
    for(int i = 1; i <= numVertex; i++){
        for(int j = 1; j <= numVertex; j++){
            if(i == j) edge[i][j] = 0;
            else if(edge[i][j] == 0) edge[i][j] = INF;
        }
    }
    cout << endl; 
    cout << "Output: " << endl;
    prim(1);
    return 0;
}

/*
Input:
7 9
1 2 28
1 6 10
2 3 16
2 7 14
3 4 12
4 5 22
4 7 18
5 6 25
5 7 24
 
Output:
1 6 10
3 4 12
2 7 14
2 3 16
4 5 22
5 6 25
Weight of MST is 99
*/
