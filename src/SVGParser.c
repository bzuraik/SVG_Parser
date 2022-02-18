#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#include <libxml/xmlschemastypes.h>
#include "LinkedListAPI.h"
#include "SVGParser.h"
#include "SVGHelper.h"

//This function does the parsing and allocates an SVG struct
SVG* createSVG(const char* fileName){

    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;
    LIBXML_TEST_VERSION

    // parse the file and get the DOM 
    doc = xmlReadFile(fileName, NULL, 0);

    if (doc == NULL) 
	{
		xmlFreeDoc(doc);
		xmlCleanupParser();
		return NULL;
    }
	
    root_element = xmlDocGetRootElement(doc);
	

	SVG* svg = (SVG*)malloc(sizeof(SVG));

	strcpy(svg->title, "");
	strcpy(svg->description, "");

	//init the lists inside SVG struct
	svg->rectangles = initializeList(&rectangleToString, &deleteRectangle, &compareRectangles);
    svg->circles = initializeList(&circleToString, &deleteCircle, &compareCircles);
    svg->paths = initializeList(&pathToString, &deletePath, &comparePaths);
    svg->groups = initializeList(&groupToString, &deleteGroup, &compareGroups);
    svg->otherAttributes = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);
    
    svg = print_element_names(root_element, svg);
	

    // free the document
    xmlFreeDoc(doc);
	


    //Free the global variables that may have been allocated by the parser.
     
    xmlCleanupParser();
    

    return svg;
    
}

// This function returns a humanly readable string representation of the entire vector image object
char* SVGToString(const SVG* img)
{
	
    char *str = toString(img->otherAttributes);
	
	char *str2 = toString(img->rectangles);
	
	char *str3 = toString(img->circles);
	
	char* str4 = toString(img->paths);

	char* str5 = toString(img->groups);
	
	int len;
	len = strlen(str)+strlen(str2) + strlen(str3)+ strlen(str4) + strlen(str5) +24;
	char *tmpStr = (char*)malloc(sizeof(char)*len);
	
	sprintf(tmpStr, "%s %s %s %s %s",str , str2, str3, str4, str5);
	free(str5);
	free(str4);
	free(str3);
	free(str2);
	free(str);
	
	return tmpStr;
}

void deleteSVG(SVG* img)
{
	
	if (img == NULL){
		return;
	}
	
	freeList(img->otherAttributes);
	freeList(img->rectangles);
	freeList(img->circles);
	freeList(img->paths);
	freeList(img->groups);
	free(img);
}


void deleteAttribute( void* data)
{

    Attribute* tmpName;
	
	if (data == NULL)
	{
		return;
	}
	
	tmpName = (Attribute*)data;
	
	free(tmpName->name);
	free(tmpName);
}
char* attributeToString(void* data)
{
    char* tmpStr;
	Attribute* tmpName;
	
	int len;
	
	if (data == NULL)
	{
		return NULL;
	}
	
	tmpName = (Attribute*)data;
		
	
	len = strlen(tmpName->name)+strlen(tmpName->value)+24;
	tmpStr = (char*)malloc(sizeof(char)*len);

	sprintf(tmpStr, "Name = %s Value = %s\n",tmpName->name , tmpName->value);
	return tmpStr;
}
int compareAttributes(const void *first, const void *second)
{

    return 0;
}

void deleteGroup(void* data)
{
	Group* tmpName;
	
	if (data == NULL){
		return;
	}
	
	tmpName = (Group*)data;
	freeList(tmpName->rectangles);
	freeList(tmpName->paths);
	freeList(tmpName->circles);
	freeList(tmpName->groups);
	freeList(tmpName->otherAttributes);
	free(tmpName);
}
char* groupToString(void* data)
{

	char* tmpStr;
	Group* tmpName;
	
	if (data == NULL){
		return NULL;
	}
	
	tmpName = (Group*)data;
	char *str1 = toString(tmpName->otherAttributes);
	char *str2 = toString(tmpName->circles);
	char *str3 = toString(tmpName->rectangles);
	char *str4 = toString(tmpName->paths);
	char *str5 = toString(tmpName->groups);
	int len = strlen(str2)+strlen(str4) +strlen(str3) + strlen(str1)+ strlen(str5)+24;
	tmpStr = (char*)malloc(sizeof(char)*len);

	sprintf(tmpStr, "\nGroup: %s \t%s %s %s %s",str1, str2, str4, str3, str5);
	
	free(str1);
	free(str2);
	free(str3);
	free(str4);
	free(str5);
	
	return tmpStr;    
}
int compareGroups(const void *first, const void *second)
{

    return 0;
}

void deleteRectangle(void* data)
{
	Rectangle* tmpName;
	
	if (data == NULL){
		return;
	}
	
	tmpName = (Rectangle*)data;
	
	freeList(tmpName->otherAttributes);
	free(tmpName);
}
char* rectangleToString(void* data)
{
   	char* tmpStr;
	Rectangle* tmpName;
	
	if (data == NULL){
		return NULL;
	}
	
	tmpName = (Rectangle*)data;
		
	int len = snprintf(NULL, 0, "%f %f %f %f", tmpName->x, tmpName->y, tmpName->width, tmpName->height);
	
	char *str3 = toString(tmpName->otherAttributes);
	
	tmpStr = malloc(sizeof(str3) * len + 24);

	sprintf(tmpStr, "\nRect\nx = %f y = %f Widtth = %f = Height = %f units =%s\n", tmpName->x, tmpName->y, tmpName->width, tmpName->height, tmpName->units);
	strcat(tmpStr, str3);


	free(str3);
	return tmpStr;
}
int compareRectangles(const void *first, const void *second)
{

    return 0;
}

void deleteCircle(void* data)
{
	Circle* tmpName;
	
	if (data == NULL){
		return;
	}
	
	tmpName = (Circle*)data;
	
	freeList(tmpName->otherAttributes);
	free(tmpName);
}
char* circleToString(void* data)
{
   	char* tmpStr;
	Circle* tmpName;
	
	if (data == NULL){
		return NULL;
	}
	
	tmpName = (Circle*)data;
			
	int len = snprintf(NULL, 0, "%f %f %f", tmpName->cx, tmpName->cy, tmpName->r);
	char *str3 = toString(tmpName->otherAttributes);
	
	tmpStr = malloc(sizeof(str3) * len + 24);
	sprintf(tmpStr, "\nCirc\ncx = %f cy = %f r = %f units =%s", tmpName->cx, tmpName->cy, tmpName->r, tmpName->units);
	strcat(tmpStr, str3);


	free(str3);
	return tmpStr;
}
int compareCircles(const void *first, const void *second)
{

    return 0;
}

void deletePath(void* data)
{

	Path* tmpName;
	
	if (data == NULL){
		return;
	}
	
	tmpName = (Path*)data;
	
	freeList(tmpName->otherAttributes);
	free(tmpName);
}
char* pathToString(void* data)
{
   	char* tmpStr;
	Path* tmpName;
	
	if (data == NULL){
		return NULL;
	}
	
	tmpName = (Path*)data;
		
	int len = strlen(tmpName->data);
	char *str3 = toString(tmpName->otherAttributes);
	
	tmpStr = malloc(sizeof(str3) * len + 24);

	sprintf(tmpStr, "\npath\ndata = %s", tmpName->data);
	strcat(tmpStr, str3);

	free(str3);
	return tmpStr;
}
int comparePaths(const void *first, const void *second)
{

    return 0;
}

void deleteRectangleList(void* data)
{


}

char* rectangleToStringList(void* data)
{

	return(rectangleToString(data));
}

List* getRects(const SVG* img)
{
	if(img == NULL)
	{
		return NULL;
	}
	List * list = initializeList(&rectangleToStringList, &deleteRectangleList, &compareRectangles);
	ListIterator iter = createIterator(img->rectangles);

	ListIterator iter1 = createIterator(img->groups);

	void* elem1;
	while((elem1 = nextElement(&iter1)) != NULL)
	{
		Group* tmpName = (Group*)elem1;
		ListIterator iter = createIterator(tmpName->rectangles);

		void* elem;
		while((elem = nextElement(&iter)) != NULL)
		{
			Rectangle* tmpName = (Rectangle*)elem;
			
				insertBack(list, tmpName);
			
			}
	}
	
	void* elem;
	while((elem = nextElement(&iter)) != NULL){
		Rectangle* tmpName = (Rectangle*)elem;
		insertBack(list, tmpName);

	}
	
	return list;
}


// Function that returns a list of all circles in the struct.

void deleteCircleList(void* data)
{


}

char* CircleToStringList(void* data)
{

	return(circleToString(data));
}

Rectangle * getGroupRect(Group *group)
{

	ListIterator iter = createIterator(group->rectangles);
	void* elem;
	while((elem = nextElement(&iter)) != NULL){
		Rectangle* tmpName = (Rectangle*)elem;
		
		return (tmpName);
		
	}
	return NULL;
}
List* getCircles(const SVG* img)
{
	if(img == NULL)
	{
		return NULL;
	}
	List *list = initializeList(&CircleToStringList, &deleteCircleList, &compareCircles);

	ListIterator iter = createIterator(img->circles);
	ListIterator iter1 = createIterator(img->groups);

	void* elem1;
	while((elem1 = nextElement(&iter1)) != NULL){
		Group* tmpName = (Group*)elem1;
		ListIterator iter = createIterator(tmpName->circles);

		void* elem;
		while((elem = nextElement(&iter)) != NULL){
			Circle* tmpName = (Circle*)elem;
			
				insertBack(list, tmpName);
			
			}
	}
	
	void* elem;
	while((elem = nextElement(&iter)) != NULL){
		Circle* tmpName = (Circle*)elem;
		insertBack(list, tmpName);
		
	}
	return list;
}
// Function that returns a list of all groups in the struct.

char * groupToStringList(void *data)
{

	return(groupToString(data));

}
void deleteGroupList(void *data)
{

}
List* getGroups(const SVG* img)
{
	if(img == NULL)
	{
		return NULL;
	}
	List *list = initializeList(&groupToStringList, &deleteGroupList, &compareGroups);
	ListIterator iter = createIterator(img->groups);
	
	void* elem;
	while((elem = nextElement(&iter)) != NULL){
		Group* tmpName = (Group*)elem;
		insertBack(list, tmpName);
		
		
	}
	return list;
}

char * pathToStringList(void *data)
{

	return(pathToString(data));

}
void deletePathList(void *data)
{

}
// Function that returns a list of all paths in the struct.  
List* getPaths(const SVG* img)
{
	if(img == NULL)
	{
		return NULL;
	}
	List *list = initializeList(&pathToStringList, &deletePathList, &compareCircles);
	ListIterator iter = createIterator(img->paths);
	ListIterator iter1 = createIterator(img->groups);

	void* elem1;
	while((elem1 = nextElement(&iter1)) != NULL){
		Group* tmpName = (Group*)elem1;
		ListIterator iter = createIterator(tmpName->paths);

		void* elem;
		while((elem = nextElement(&iter)) != NULL){
			Path* tmpName = (Path*)elem;
			
				insertBack(list, tmpName);
			
			}
	}

	void* elem;
	while((elem = nextElement(&iter)) != NULL){
		Path* tmpName = (Path*)elem;
		insertBack(list, tmpName);
	}
	return list;
}

int numRectsWithArea(const SVG* img, float area)
{
	if(area < 0 || img == NULL)
	{
		return 0;
	}

	int count = 0;
	double match = ceil(area);

	List *list = getRects(img);
	ListIterator iter1 = createIterator(list);

	void* elem1;
	while((elem1 = nextElement(&iter1)) != NULL){
		Rectangle* tmpName = (Rectangle*)elem1;
		float v1 = tmpName->width;
		float v2 = tmpName->height;
		double match2 = ceil(v1 * v2);
		if(match2 == match)
		{
			count++;
		}
		
	}
	
	freeList(list);
	return count; 
}
// Function that returns the number of all circles with the specified area
int numCirclesWithArea(const SVG* img, float area)
{
	if(area < 0 || img == NULL)
	{
		return 0;
	}
	int count = 0;
	double match = ceil(area);

	List *list = getCircles(img);
	ListIterator iter1 = createIterator(list);
	
	void* elem1;
	while((elem1 = nextElement(&iter1)) != NULL){
		Circle* tmpName = (Circle*)elem1;
		float v1 = tmpName->r;
		double match2 = ceil(M_PI* (v1*v1));
		if(match2 == match)
		{
			count++;
		}
		
	}
	
	freeList(list);
	return count;  
}
// Function that returns the number of all paths with the specified data - i.e. Path.data field
int numPathsWithdata(const SVG* img, const char* data)
{
	if(data == NULL || img == NULL)
	{
		return 0;
	}

	int count = 0;
	
	List *list = getPaths(img);
	ListIterator iter1 = createIterator(list);

	void* elem1;
	while((elem1 = nextElement(&iter1)) != NULL){
		Path* tmpName = (Path*)elem1;
		
		char * str = malloc(sizeof(char)* strlen(tmpName->data) + 2);
		strcpy(str, tmpName->data);
		
		if(strcmp(str, data) == 0)
		{
			count++;
		}
		free(str);
		
	}

	freeList(list);
	return count;  
}
// Function that returns the number of all groups with the specified length 
int numGroupsWithLen(const SVG* img, int len)
{
	if(len < 0 || img == NULL)
	{
		return 0;
	}
	int total = 0;
	int count = 0;

	List *list = getGroups(img);
	ListIterator iter1 = createIterator(list);

	void* elem1;
	while((elem1 = nextElement(&iter1)) != NULL){
		Group* tmpName = (Group*)elem1;

		int circL = getLength(tmpName->circles);
		int rectL = getLength(tmpName->rectangles);
		int pathL = getLength(tmpName->paths);
		int groupL = getLength(tmpName->groups);
		
		total = circL + rectL + pathL +groupL;
		if(total == len)
		{
			count++;
		}
		
	}
	freeList(list);
	return count; 
}
int numAttr(const SVG* img)
{
	int count = 0;
	if(img == NULL)
	{
		return 0;
	}
	ListIterator iter = createIterator(img->otherAttributes);
	ListIterator iter1 = createIterator(img->groups);
	ListIterator iter2 = createIterator(img->circles);
	ListIterator iter3 = createIterator(img->rectangles);
	ListIterator iter4 = createIterator(img->paths);
	
	void* elem1;
	while((elem1 = nextElement(&iter1)) != NULL)
	{
		Group* tmpName = (Group*)elem1;
		ListIterator iter = createIterator(tmpName->otherAttributes);
		void* elem;
		while((elem = nextElement(&iter)) != NULL)
		{
			count++;
		}

		ListIterator iterR = createIterator(tmpName->rectangles);
		void* elemR;
		while((elemR = nextElement(&iterR)) != NULL)
		{
			Rectangle* tmpName = (Rectangle*)elemR;
			ListIterator iter = createIterator(tmpName->otherAttributes);
			void* elem;
			while((elem = nextElement(&iter)) != NULL)
			{
				count++;
			}	
		}

		ListIterator iterC = createIterator(tmpName->circles);
		void* elemC;
		while((elemC = nextElement(&iterC)) != NULL)
		{
			Circle* tmpName = (Circle*)elemC;
			ListIterator iter = createIterator(tmpName->otherAttributes);
			void* elem;
			while((elem = nextElement(&iter)) != NULL)
			{
				count++;
			}	
		}
		
		ListIterator iterP = createIterator(tmpName->paths);
		void* elemP;
		while((elemP = nextElement(&iterP)) != NULL)
		{
			Path* tmpName = (Path*)elemP;
			ListIterator iter = createIterator(tmpName->otherAttributes);
			void* elem;
			while((elem = nextElement(&iter)) != NULL)
			{
				count++;
			}	
		}

	}

	void* elem2;
	while((elem2 = nextElement(&iter2)) != NULL){
		Circle* tmpName = (Circle*)elem2;
		ListIterator iter = createIterator(tmpName->otherAttributes);
		void* elem;
		while((elem = nextElement(&iter)) != NULL){
			count++;
		}
	}

	void* elem3;
	while((elem3 = nextElement(&iter3)) != NULL){
		Rectangle* tmpName = (Rectangle*)elem3;
		ListIterator iter = createIterator(tmpName->otherAttributes);
		void* elem;
		while((elem = nextElement(&iter)) != NULL){
			count++;
		}
	}

	void* elem4;
	while((elem4 = nextElement(&iter4)) != NULL){
		Path* tmpName = (Path*)elem4;
		ListIterator iter = createIterator(tmpName->otherAttributes);
		void* elem;
		while((elem = nextElement(&iter)) != NULL){
			count++;
		}
	}
	void* elem0;
	while((elem0 = nextElement(&iter)) != NULL){
		count++;
	}

	
	return count; 
}

int main()
{

	SVG *svg;
	svg = createSVG("test.svg"); // This is a test file, you can find it /bin 

	char *str = SVGToString(svg);

	printf(" \n --------------------------------------- SVG: --------------------------------------- \n%s\n", str);


	//uncomment this to get details about the groups only
	/*
	List *list = getGroups(svg);
	char *str1 = toString(list);

	printf("+++++++++++++++++++++++++ Groups +++++++++++++++++++++++++\n %s\n", str1);

	// uncomment this to search for groups lists with certain length
	// int test = 4;
	// int num = numGroupsWithLen(svg, test);
	// printf("NUM G = %d\n", num);
	*/


	//uncomment this to get details about the groups only
	/*
	List *list = getCircles(svg);
	char *str1 = toString(list);

	printf("+++++++++++++++++++++++++ Circles +++++++++++++++++++++++++\n %s\n", str1);

	// uncomment this to search for Circles lists with certain length
	// int test = 4;
	// int num = numCirclesWithLen(svg, test);
	// printf("NUM C = %d\n", num);
	*/


	//uncomment this to get details about the Rects only
	/*
	List *list = getRects(svg);
	char *str1 = toString(list);

	printf("+++++++++++++++++++++++++ Rects +++++++++++++++++++++++++\n %s\n", str1);

	// uncomment this to search for Circles lists with certain length
	// int test = 4;
	// int num = numRectsWithLen(svg, test);
	// printf("NUM R = %d\n", num);
	*/

	//uncomment this to get details about the Paths only
	/*
	List *list = getPaths(svg);
	char *str1 = toString(list);

	printf("+++++++++++++++++++++++++ Paths +++++++++++++++++++++++++\n %s\n", str1);

	// uncomment this to search for Paths lists with certain length
	// int test = 4;
	// int num = numPathsWithLen(svg, test);
	// printf("NUM P = %d\n", num);
	*/


	//uncomment these if any calls of the hlepers functions were done
	free(str);
	// free(str1);
	// freeList(list);


	deleteSVG(svg);

	return 0;
}