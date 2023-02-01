#ifndef XMLPARSER_H
#define XMLPARSER_H
#include <bits/stdc++.h>
#include <libxml/xmlreader.h>
using namespace std;
class XMLParser
{
public:
    XMLParser();
    ~XMLParser();
    void processNode(xmlTextReaderPtr reader);
    void streamFile(const char* filename);
    vector<string> nodes;
    map<string, string> edges;
    vector<string> edges_src;
    vector<string> edges_dst;
};

#endif // XMLPARSER_H
