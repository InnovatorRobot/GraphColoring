#ifndef GRAPHCOLORING_H
#define GRAPHCOLORING_H
#include <bits/stdc++.h>

using namespace std;
using Graph = vector<std::vector<bool>>;

struct node
{
    int color = 1;
    set<int> edges;
};

class GraphColoring
{

public:
    GraphColoring(vector<string> nodes, vector<string> edges_src, vector<string> edges_dst);
    void GreedyAlgorithm();
    void BuildGraph();
    Graph GetGraph();
    int BFSColoring(Graph graph, int n);

private:
    vector<string> Nodes;
    vector<string> EdgesSrc;
    vector<string> EdgesDst;

    map<string, int> NodesMap;
    int NodesNumber;
    int Edges_Number;
    Graph graph;
};

#endif // GRAPHCOLORING_H
