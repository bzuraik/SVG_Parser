#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#define M_PI 3.14159265358979323846

SVG* print_element_names(xmlNode * a_node, SVG* svg);

void findGroup(xmlNode * a_node, SVG* svg, Group *group);


// inti functions
void initRect(Rectangle *rect);

void initCirc(Circle *circ);

void initPath(Path *path);

// creating functions
Attribute * createAttribute( char* size);

Rectangle * createRect(char* size);


Rectangle * createRect(char* size);

Path * createPath(char* size);

//checking functions 
void checkCirc(Circle *circ);

void checkRect(Rectangle *rect);



// storing functions
void storeRect(char *cont, char *attrName, Rectangle *rect, SVG* svg);

int storeUnits(char * cont);

void storeCirc(char *cont, char *attrName, Circle *circ, SVG* svg);


void storePath(char *cont, char *attrName, Path *path, SVG* svg);

void storeGroup(char *cont, char *attrName, Group *group, SVG* svg);





















