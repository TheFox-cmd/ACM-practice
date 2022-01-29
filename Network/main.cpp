//
//  main.cpp
//  Network
//
//  Created by Ryuki Koda on 1/25/22.
//
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

#define maxNumVertex 1001
#define maxNumEdge 15001

int numVertex, numEdge;
int parent[maxNumVertex];
int usedEdge, maxEdge;
int ans[maxNumVertex], ansIdx;
struct edge{
    int vertex1, vertex2, weight;
}edges[maxNumVertex];

void UFset(){
    for(int i = 1; i <= numVertex; i++) parent[i] = -1;
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
    return aa.weight - bb.weight;
}

void kruskal(){
    ansIdx = 0;
    int vertVal1, vertVal2;
    UFset();
    for(int i = 0; i < numEdge; i++){
        vertVal1 = edges[i].vertex1;
        vertVal2 = edges[i].vertex2;
        if(findRoot(vertVal1) != findRoot(vertVal2)){
            ans[ansIdx] = i;
            ansIdx++;
            if(edges[i].weight > maxEdge){
                maxEdge = edges[i].weight;
            }
            usedEdge++;
            unify(vertVal1, vertVal2);
        }
        if(usedEdge >= numVertex - 1) break;
    }
}

int main(int argc, const char * argv[]) {
    cin >> numVertex >> numEdge;
    for(int i = 0; i < numEdge; i++){
        cin >> edges[i].vertex1 >> edges[i].vertex2 >> edges[i].weight;
    }
    
    qsort(edges, numEdge, sizeof(edges[0]), cmp);
    maxEdge = 0;
    usedEdge = 0;
    cout << endl;
    cout << endl;
    kruskal();
    cout << endl;
    cout << maxEdge << endl;
    cout << usedEdge << endl;
    for(int i = 0; i < usedEdge; i++){
        cout << edges[ans[i]].vertex1 << " " << edges[ans[i]].vertex2 << endl;
    }
    return 0;
}

/*
Input: 
5 8
1 2 5
1 4 2
1 5 1
2 3 6
2 4 3
3 4 5
3 5 4
4 5 6
 
Output:
4
4
1 5
1 4
2 4
3 5
*/
