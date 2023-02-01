#include "graphcoloring.h"
#include "xmlparser.h"
using namespace std;

int main(int argc, char** argv)
{
    XMLParser xml_parser;
    if (argc > 1)
        xml_parser.streamFile(argv[1]);
    else
    {
        cout << "You should give path of xml file like:\n ./Assigment_2 input.xml" << endl;
        return 0;
    }

    GraphColoring graph_coloring(xml_parser.nodes, xml_parser.edges_src, xml_parser.edges_dst);

    graph_coloring.BuildGraph();

    Graph graph = graph_coloring.GetGraph();

    int NumberOfColor = graph_coloring.BFSColoring(graph, xml_parser.nodes.size());

    cout << "Number of Colors is: " << NumberOfColor << endl;

    return 0;
}
