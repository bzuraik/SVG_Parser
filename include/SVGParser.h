#ifndef SVGPARSER_H
#define SVGPARSER_H

#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#include <libxml/xmlschemastypes.h>
#include "LinkedListAPI.h"

typedef enum COMP{
    SVG_IMG, CIRC, RECT, PATH, GROUP
} elementType;

//Represents a generic SVG element/XML node Attribute
typedef struct  {
    //Attribute name.  
	char* 	name;
    //Attribute value.  
	char	value[]; 
} Attribute;

//Represents a group of objects in an SVG file
typedef struct {
    
	//All objects in the list will be of type Rectangle.  
    List*   rectangles;
    //All objects in the list will be of type Circle.  
    List*   circles;
    //All objects in the list will be of type Path.  
    List*   paths;
    //All objects in the list will be of type Group.  
    List*   groups;


	 //Additional circle attributes
    List* otherAttributes;
} Group;

//Represents a rectangle primitive 
typedef struct {
    //The X coordinate of the "starting" corner of the rectangle
    float x;
    //The Y coordinate of the "starting" corner of the rectangle
    float y;
    //Rectangle width.  
    float width;
    //Rectangle height. 
    float height;

    //Units for the rectable coordinates and size.  
    char units[50];

	 //Additional circle attributes
    List* otherAttributes;

} Rectangle;

//Represents a circle primitive 
typedef struct {
    //The X coordinate of circle centre
    float cx;
    //The Y coordinate of circle centre
    float cy;
    //Circle radius. 
    float r;

    //Units for the circle coordinates and size. 
    char units[50];

    //Additional circle attributes  
    List* otherAttributes;

} Circle;

//Represents a path primitive
typedef struct {
    
    //Additional path attributes  
    List* otherAttributes;

    //Path data.  Must not be NULL
    char data[];

} Path;

// The main struct, representing an svg elemnt of the format
typedef struct {

    //Namespace associated with our SVG struct. 
    char namespace[256];

    //Title of our SVG struct 
    char title[256];

    //Decription of our SVG struct
    char description[256];

    //All objects in the list will be of type Rectangle.  
    List* rectangles;
    //All objects in the list will be of type Circle.  
    List* circles;
    //All objects in the list will be of type Path.  
    List* paths;
    //All objects in the list will be of type Group.  
    List* groups;  
   
    //Additional SVG attributes
    List* otherAttributes;
} SVG;

/** Function to create an SVG struct based on the contents of an SVG file.
 *@pre File name cannot be an empty string or NULL.
       File represented by this name must exist and must be readable.
 *@post Either:
        A valid SVG struct has been created and its address was returned
		or 
		An error occurred, and NULL was returned
 *@return the pinter to the new struct or NULL
 *@param fileName - a string containing the name of the SVG file
**/

SVG* createSVG(const char* fileName);

/** Function to create a string representation of an SVG struct.
 *@pre SVG struct exists, is not null, and is valid
 *@post SVG struct has not been modified in any way, and a string representing the SVG contents has been created
 *@return a string contaning a humanly readable representation of an SVG struct
 *@param obj - a pointer to an SVG struct
**/

char* SVGToString(const SVG* img);

/** Function to delete struct content and free all the memory.
 *@pre SVG struct exists, is not null, and has not been freed
 *@post SVG struct had been freed
 *@return none
 *@param obj - a pointer to an SVG struct
**/

void deleteSVG(SVG* img);

/* 
 *@pre SVG struct exists, is not null, and has not been freed
 *@return a newly allocated List of components.  
 *@param obj - a pointer to an SVG struct
 */

// Function that returns a list of all rectangles in the struct.  
List* getRects(const SVG* img);
// Function that returns a list of all circles in the struct.  
List* getCircles(const SVG* img);
// Function that returns a list of all groups in the struct.  
List* getGroups(const SVG* img);
// Function that returns a list of all paths in the struct.  
List* getPaths(const SVG* img);


/*
 *@pre SVG struct exists
 *@return an int indicating how many objects matching the criterion are contained in the struct
 *@param obj - a pointer to an SVG struct
 *@param 2nd - the second param depends on the function.
 */   

// Function that returns the number of all rectangles with the specified area
int numRectsWithArea(const SVG* img, float area);
// Function that returns the number of all circles with the specified area
int numCirclesWithArea(const SVG* img, float area);
// Function that returns the number of all paths with the specified data
int numPathsWithdata(const SVG* img, const char* data);
// Function that returns the number of all groups with the specified length
int numGroupsWithLen(const SVG* img, int len);

/*  Function that returns the total number of Attribute structs in the SVG struct
    *@pre SVG struct  exists, is not null, and has not been freed.  
    *@return the total length of all attribute structs in the SVG
    *@param obj - a pointer to an SVG struct
*/
int numAttr(const SVG* img);

/* helper functions for initializeList() */

void deleteAttribute( void* data);
char* attributeToString(void* data);
int compareAttributes(const void *first, const void *second);

void deleteGroup(void* data);
char* groupToString(void* data);
int compareGroups(const void *first, const void *second);

void deleteRectangle(void* data);
char* rectangleToString(void* data);
int compareRectangles(const void *first, const void *second);

void deleteCircle(void* data);
char* circleToString(void* data);
int compareCircles(const void *first, const void *second);

void deletePath(void* data);
char* pathToString(void* data);
int comparePaths(const void *first, const void *second);

#endif
