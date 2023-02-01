#include "graphcoloring.h"

GraphColoring::GraphColoring(vector<string> nodes, vector<string> edges_src, vector<string> edges_dst)
{
    Nodes = nodes;
    EdgesSrc = edges_src;
    EdgesDst = edges_dst;
    //    Edges = edges;
    NodesNumber = nodes.size();

    Edges_Number = edges_src.size() == edges_dst.size() ? edges_src.size() : -1;
}

void GraphColoring::BuildGraph()
{
    graph = Graph(NodesNumber, vector<bool>(NodesNumber, false));

    int iter = 0;
    for (auto it : Nodes)
    {
        NodesMap.insert({it, iter});
        iter++;
    }

    for (int i = 0; i < Edges_Number; ++i)
    {
        graph[NodesMap.find(EdgesSrc.at(i))->second][NodesMap.find(EdgesDst.at(i))->second] = true;
        graph[NodesMap.find(EdgesDst.at(i))->second][NodesMap.find(EdgesSrc.at(i))->second] = true;
    }
}

Graph GraphColoring::GetGraph()
{
    return graph;
}

int GraphColoring::BFSColoring(Graph graph, int n)
{
    vector<node> nodes(n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (graph[i][j])
            {
                nodes[i].edges.insert(j);
                nodes[j].edges.insert(i);
            }
        }
    }

    vector<int> visited(n, 0);

    int maxColors = 1;

    for (int sv = 0; sv < n; sv++)
    {

        if (visited[sv]) continue;

        visited[sv] = 1;
        queue<int> q;
        q.push(sv);

        while (!q.empty())
        {

            int top = q.front();
            q.pop();

            for (auto it : nodes[top].edges)
            {

                while (nodes[top].color == nodes[it].color)
                    nodes[it].color += 1;

                maxColors = max(maxColors, max(nodes[top].color, nodes[it].color));

                if (!visited[it])
                {
                    visited[it] = 1;
                    q.push(it);
                }
            }
        }
    }

    cout << "color assignment for each node is:\n";
    for (auto it : nodes)
    {
        cout << it.color << " ";
    }
    cout << endl;
    return maxColors;
}
