//
//  main.cpp
//  Kruskal Algorithm
//
//  Created by Ryuki Koda on 1/11/22.
//
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

#define maxNumVertex 10
#define maxNumEdge 20

int numVertex, numEdge;
int parent[maxNumVertex];
struct edge{
    int vertex1, vertex2, weight;
}edges[maxNumEdge];

void UFSet(){
    for(int i = 1; i <= numVertex; i++) parent[i] = -1;
}

int findRoot(int x){
    int root;
    for(root = x; parent[root] >= 0; root = parent[root]);
    while(root != x){
        int tmp = parent[x];
        parent[x] = root;
        x = tmp;
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
    return aa.weight - bb.weight;
}

void kruskal(){
    int weightSum = 0;
    int num = 0;
    int vertVal1, vertVal2;
    UFSet();
    for(int i = 0; i < numEdge; i++){
        vertVal1 = edges[i].vertex1;
        vertVal2 = edges[i].vertex2;
        if(findRoot(vertVal1) != findRoot(vertVal2)){
            cout << vertVal1 << " " << vertVal2 << " " << edges[i].weight << endl;
            weightSum += edges[i].weight;
            num++;
            unify(vertVal1, vertVal2);
        }
        if(num >= numVertex - 1) break;
    }
    cout << "Weight of MST is " << weightSum << endl;
}

int main(int argc, const char * argv[]) {
    int vertexA, vertexB, weightAB;
    cin >> numVertex >> numEdge;
    for(int i = 0; i < numEdge; i++){
        cin >> vertexA >> vertexB >> weightAB;
        edges[i].vertex1 = vertexA;
        edges[i].vertex2 = vertexB;
        edges[i].weight = weightAB;
    }
    qsort(edges, numEdge, sizeof(edges[0]), cmp);
    cout << endl;
    cout << "Output:" << endl;
    kruskal();
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
