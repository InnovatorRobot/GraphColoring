#include "xmlparser.h"

XMLParser::XMLParser() {}

XMLParser::~XMLParser()
{
    xmlCleanupParser();
    xmlMemoryDump();
}

void XMLParser::processNode(xmlTextReaderPtr reader)
{
    const xmlChar *name, *value;
    name = xmlTextReaderConstName(reader);
    if (name == NULL) name = BAD_CAST "--";

    value = xmlTextReaderConstValue(reader);

    if (!xmlStrcmp(name, BAD_CAST "node"))
    {
        xmlNodePtr node = xmlTextReaderCurrentNode(reader);
        if (xmlTextReaderNodeType(reader) == 1 && node && node->properties)
        {
            xmlAttr* attribute = node->properties;
            xmlChar* valueAttr = xmlNodeListGetString(node->doc, attribute->children, 1);
            if (!xmlStrcmp(attribute->name, BAD_CAST "name"))
            {
                nodes.push_back((string)(char*)valueAttr);
            }
            xmlFree(valueAttr);
        }
    }
    else if (!xmlStrcmp(name, BAD_CAST "edge"))
    {
        xmlNodePtr node = xmlTextReaderCurrentNode(reader);
        if (xmlTextReaderNodeType(reader) == 1 && node && node->properties)
        {
            xmlAttr* attribute = node->properties;
            while (attribute && attribute->name && attribute->children)
            {
                xmlChar* valueAttr = xmlNodeListGetString(node->doc, attribute->children, 1);
                if (!xmlStrcmp(attribute->name, BAD_CAST "src"))
                {
                    edges_src.push_back((string)(char*)valueAttr);
                }
                else if (!xmlStrcmp(attribute->name, BAD_CAST "dst"))
                {
                    edges_dst.push_back((string)(char*)valueAttr);
                }
                xmlFree(valueAttr);
                attribute = attribute->next;
            }
        }
    }
}

/**
 * streamFile:
 * @filename: the file name to parse
 *
 * Parse, validate and print information about an XML file.
 */
void XMLParser::streamFile(const char* filename)
{
    xmlTextReaderPtr reader;
    int ret;

    reader = xmlReaderForFile(
        filename, NULL,
        XML_PARSE_DTDATTR |      /* default DTD attributes */
            XML_PARSE_NOENT |    /* substitute entities */
            XML_PARSE_DTDVALID); /* validate with the DTD */
    if (reader != NULL)
    {
        ret = xmlTextReaderRead(reader);
        while (ret == 1)
        {
            processNode(reader);
            ret = xmlTextReaderRead(reader);
        }
        xmlFreeTextReader(reader);
        if (ret != 0)
        {
            fprintf(stderr, "%s : failed to parse\n", filename);
        }
    }
    else
    {
        fprintf(stderr, "Unable to open %s\n", filename);
    }
}
