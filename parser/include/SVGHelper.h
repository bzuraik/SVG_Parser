#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#define M_PI 3.14159265358979323846

SVG* print_element_names(xmlNode * a_node, SVG* svg);

Attribute * createAttribute( char* size);

void storeRect(char *cont, char *attrName, Rectangle *rect, SVG* svg);

