//
//  main.cpp
//  Swordfish
//
//  Created by Ryuki Koda on 1/13/22.
//

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <math.h>
using namespace std;

#define maxNumVertex 100
#define maxNumEdge 10000

int numVertex, numEdge;
int parent[maxNumVertex];
double x[maxNumEdge], y[maxNumEdge], weightSum = 0.0;
struct edge{
    int vertex1, vertex2;
    double weight;
}edges[maxNumEdge];

void UFSet(){
    for(int i = 0; i < numVertex; i++) parent[i] = -1;
}

int findRoot(int start){
    int root;
    for(root = start; parent[root] >= 0; root = parent[root]);
    while(root != start){
        int tmp = parent[start];
        parent[start] = root;
        start = tmp;
    }
    return root;
}

void unify(int value1, int value2){
    int root1 = findRoot(value1);
    int root2 = findRoot(value2);
    int setTotal = parent[root1] + parent[root2];
    if(parent[root1] > parent[root2]){
        parent[root1] = root2;
        parent[root2] = setTotal;
    }else{
        parent[root2] = root1;
        parent[root1] = setTotal;
    }
}

int cmp(const void *a, const void *b){
    edge aa = *(const edge *)a;
    edge bb = *(const edge *)b;
    if(aa.weight > bb.weight) return 1;
    else return -1;
}

void kruskal(){
    int num = 0;
    int vertVal1, vertVal2;
    UFSet();
    for(int i = 0; i < numVertex; i++){
        vertVal1 = edges[i].vertex1;
        vertVal2 = edges[i].vertex2;
        if(findRoot(vertVal1) != findRoot(vertVal2)){
            weightSum += edges[i].weight;
            num++;
            unify(vertVal1, vertVal2);
        }
        if(num >= numVertex - 1) break;
    }
}

int main(int argc, const char * argv[]) {
    double distance;
    int situation = 1;
    while(1){
        cin >> numVertex;
        if(numVertex == 0) break;
        for(int i = 0; i < numVertex; i++) cin >> x[i] >> y[i];
        int edgeIndex = 0;
        for(int i = 0; i < numVertex; i++){
            for(int j = i + 1; j < numVertex; j++){
                distance = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
                edges[edgeIndex].vertex1 = i;
                edges[edgeIndex].vertex2 = j;
                edges[edgeIndex].weight = distance;
                edgeIndex++;
            }
        }
        numEdge = edgeIndex;
        qsort(edges, numEdge, sizeof(edges[0]), cmp);
        kruskal();
        cout << endl;
        cout << "Case: " << situation << endl;
        cout << "The minimal distance is " << round(weightSum * 100) / 100.0 << endl;
        situation++;
    }
    return 0;
}

/*
Input:
5
0 0
0 1
1 0
1 1
0.5 0.5
0
 
Output:
Case: 1
The minimal distance is 2.83
*/
