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
char floats[50];
char units[10];
int storeUnits(char * cont)
{

    int j = 0;
    int unitExist = 0;
    for (int i =0; i < strlen(cont); i++)
        {
            
           if( (cont[i] >= '0' && cont[i] <= '9') && (!( cont[i+1] >= '0' && cont[i+1] <= '9') && cont[i+1] != '.'))
           {
                
                
               for(int x = 0; x <= i; x++)
               {
                   
                   floats[x] = cont[x];
                   
               }
               for(int x = i+1; x < strlen(cont); x++)
               {
                   
                   unitExist++;
                   units[j] = cont[x];
                   j++;
               }
               
           }
        }
        
        units[strlen(units)] = '\0';

    return unitExist;  
}

Attribute * createAttribute(char* size)
{

    Attribute* structPtr = (Attribute*)malloc(sizeof(Attribute)+strlen(size)+2);

    return structPtr;
}

Rectangle * createRect(char* size)
{

    Rectangle* structPtr = (Rectangle*)malloc(sizeof(Rectangle)+strlen(size)+2);

    return structPtr;
}

Circle * createCirc(char* size)
{

    Circle* structPtr = (Circle*)malloc(sizeof(Circle)+strlen(size)+2);

    return structPtr;
}

Path * createPath(char* size)
{
    
    Path* structPtr = malloc(sizeof(Path) + sizeof(char) *1000000);

    return structPtr;
}
void initRect(Rectangle *rect)
{
    rect->x = 0.0;
    rect->y = 0.0;
    rect->height = 0.0;
    rect->width = 0.0;
    strcpy(rect->units, "");
}
void checkRect(Rectangle *rect)
{
    if(rect->width < 0)
    {
        rect->width = 0.0;
    }
    if(rect->height < 0)
    {
        rect->height = 0.0;
    }

}
void storeRect(char *cont, char *attrName, Rectangle *rect, SVG* svg)
{
    int memLen;
    
    
    if(strcmp(attrName, "x") == 0)
    {
        
        
        int unitsCheck = storeUnits(cont);
        
        if(unitsCheck > 0)
        {
           
            rect->x = atof(floats);
            int length  = strlen(units)+1;
            strncpy(rect->units, units, length);
            memset(floats, 0, 50);
            
        }
        else
        {
            
            rect->x = atof(cont);
            #pragma GCC diagnostic push
            #pragma GCC diagnostic ignored "-Wstringop-truncation"
                strncpy(rect->units, " ", 0);
            #pragma GCC diagnostic pop
            
            
        }
         
                     
    }
    else if(strcmp(attrName, "y") == 0)
    {
        
        int unitsCheck = storeUnits(cont);
        
        if(unitsCheck > 0)
        {
            
            rect->y = atof(floats);
            int length  = strlen(units) + 1;
            strncpy(rect->units, units, length);
            memset(floats, 0, 50);
            
        }
        else
        {
            
            rect->y = atof(cont);
            strncpy(rect->units, "", 1);
            
        }
        
    }
    else if(strcmp(attrName, "width") == 0)
    {
        
        int unitsCheck = storeUnits(cont);
        
        if(unitsCheck > 0)
        {
            
            rect->width = atof(floats);
            int length  = strlen(units) + 1;
            strncpy(rect->units, units, length);
            memset(floats, 0, 50);
            
        }
        else
        {
            
            rect->width = atof(cont);
            strncpy(rect->units, "", 1);
        }
        
    }
    else if(strcmp(attrName, "height") == 0)
    {
        
        int unitsCheck = storeUnits(cont);
        
        if(unitsCheck > 0)
        {
            
            rect->height = atof(floats);
            int length  = strlen(units) + 1;
            strncpy(rect->units, units, length);
            memset(floats, 0, 50);
            
        }
        else
        {
            
            rect->height = atof(cont);
            strncpy(rect->units, "", 1);
            // free(floats);
        }
        //   printf(" X = %d Y = atof(cont)%d, width = %d, Height =%d RECT = %d\n", xFlag, yFlag, widthFlag, heightFlag, rectFlag );
        
    }
    else
    {
        Attribute* structAtt2 = createAttribute(cont);
        memLen = strlen(attrName)+2;
        structAtt2->name = malloc(sizeof(char) *memLen);
        strcpy(structAtt2->name, attrName);
        strcpy(structAtt2->value, cont);
        
        insertBack(rect->otherAttributes, (void*)structAtt2);
        
    }

    

}

void initCirc(Circle *circ)
{
    circ->cx = 0.0;
    circ->cy = 0.0;
    circ->r = 0.0;
}
void checkCirc(Circle *circ)
{
    if(circ->r < 0)
    {
        circ->cy = 0.0;
    }
}
void storeCirc(char *cont, char *attrName, Circle *circ, SVG* svg)
{
    int memLen;
    
    
    if(strcmp(attrName, "cx") == 0)
    {
        
        
        int unitsCheck = storeUnits(cont);
        
        if(unitsCheck > 0)
        {
            circ->cx = atof(floats);
            int length  = strlen(units)+1;
            strncpy(circ->units, units, length);
            
        }
        else
        {
           
            circ->cx = atof(cont);
            strncpy(circ->units, "", 1);
            
        }
         
                     
    }
    else if(strcmp(attrName, "cy") == 0)
    {
        
        int unitsCheck = storeUnits(cont);
        
        if(unitsCheck > 0)
        {
            
            circ->cy = atof(floats);
            int length  = strlen(units) + 1;
            strncpy(circ->units, units, length);
            memset(floats, 0, 50);
            
        }
        else
        {
           
            circ->cy  = atof(cont);
            strncpy(circ->units, "", 1);
            
        }
        
    }
    else if(strcmp(attrName, "r") == 0)
    {
        
        int unitsCheck = storeUnits(cont);
        
        if(unitsCheck > 0)
        {
            
            circ->r = atof(floats);
            int length  = strlen(units) + 1;
            strncpy(circ->units, units, length);
            memset(floats, 0, 50);
            
        }
        else
        {
            
            circ->r = atof(cont);
            strncpy(circ->units, "", 1);
        }
        
    }
    else
    {
        Attribute* structAtt2 = createAttribute(cont);
        memLen = strlen(attrName)+2;
        structAtt2->name = malloc(sizeof(char) *memLen);
        strcpy(structAtt2->name, attrName);
        strcpy(structAtt2->value, cont);
        
        insertBack(circ->otherAttributes, (void*)structAtt2);
        
    }

    

}
void initPath(Path *path)
{
    strcpy(path->data, " ");
   
}
void storePath(char *cont, char *attrName, Path *path, SVG* svg)
{
    int memLen;
    
    
    if(strcmp(attrName, "d") == 0)
    {

            int length  = strlen(cont)+1; 
            strncpy(path->data, cont, length);
            
                     
    }
    else
    {
        Attribute* structAtt2 = createAttribute(cont);
        memLen = strlen(attrName)+2;
        structAtt2->name = malloc(sizeof(char) *memLen);
        strcpy(structAtt2->name, attrName);
        strcpy(structAtt2->value, cont);
        
        insertBack(path->otherAttributes, (void*)structAtt2);
        
    }

}

void storeGroup(char *cont, char *attrName, Group *group, SVG* svg)
{
        int memLen;
        Attribute* structAtt2 = createAttribute(cont);
        memLen = strlen(attrName)+2;
        structAtt2->name = malloc(sizeof(char) *memLen);
        strcpy(structAtt2->name, attrName);
        strcpy(structAtt2->value, cont);
        
        insertBack(group->otherAttributes, (void*)structAtt2);

}

void findGroup(xmlNode * a_node, SVG* svg, Group *group)
{
    xmlNode *cur_node = NULL;
    for (cur_node = a_node; cur_node != NULL; cur_node = cur_node->next)
    {

        if (cur_node->type == XML_ELEMENT_NODE)
        {
            
           
            // printf("Group Node type: Element, \nname: %s\n", cur_node->name);

             if(strcmp((char*)cur_node->name, "rect") == 0)
            {
                
                
                Rectangle* rect = (Rectangle*)malloc(sizeof(Rectangle));
                rect->otherAttributes = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);
                xmlAttr *attr;
                for (attr = cur_node->properties; attr != NULL; attr = attr->next)
                {
                    xmlNode *value = attr->children;
                    char *attrName = (char *)attr->name;
                    char *cont = (char *)(value->content);
                    
                    storeRect(cont, attrName, rect, svg);

                }
                // checkRect(rect);
                insertBack(group->rectangles, (void*)rect);
            }
            if(strcmp((char*)cur_node->name, "circle") == 0)
            {
                
                
                Circle* circ = (Circle*)malloc(sizeof(Circle));
                circ->otherAttributes = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);
                xmlAttr *attr;
                for (attr = cur_node->properties; attr != NULL; attr = attr->next)
                {
                    xmlNode *value = attr->children;
                    char *attrName = (char *)attr->name;
                    char *cont = (char *)(value->content);
                    
                    storeCirc(cont, attrName, circ, svg);

                }
                // checkCirc(circ);
                insertBack(group->circles, (void*)circ);
            }
            else if(strcmp((char*)cur_node->name, "path") == 0)
            {
                
               
                char *size = "path";
                Path* path = createPath(size);
                initPath(path);
                path->otherAttributes = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);
                xmlAttr *attr;
                for (attr = cur_node->properties; attr != NULL; attr = attr->next)
                {
                    xmlNode *value = attr->children;
                    char *attrName = (char *)attr->name;
                    char *cont = (char *)(value->content);
                    
                    storePath(cont, attrName, path, svg);

                }
                insertBack(group->paths, (void*)path);
            }
            else if(strcmp((char*)cur_node->name, "g") == 0)
            {
                
                Group* group1 = (Group*)malloc(sizeof(Group));
                group1->groups = initializeList(&groupToString, &deleteGroup, &compareGroups);
                group1->rectangles = initializeList(&rectangleToString, &deleteRectangle, &compareRectangles);
                group1->circles = initializeList(&circleToString, &deleteCircle, &compareCircles);
                group1->paths = initializeList(&pathToString, &deletePath, &comparePaths);
                group1->otherAttributes = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);
                findGroup(cur_node->children, svg, group1);
                xmlAttr *attr;
                for (attr = cur_node->properties; attr != NULL; attr = attr->next)
                {
                     xmlNode *value = attr->children;
                    char *attrName = (char *)attr->name;
                    char *cont = (char *)(value->content);
                    storeGroup(cont, attrName, group1, svg);

                }
                insertBack(group->groups, (void*)group1);
                cur_node = cur_node->next;
                
                
            }  
        }
        // findGroup(cur_node->children, svg, group);
    }

}
SVG* print_element_names(xmlNode * a_node, SVG* svg)
{
    xmlNode *cur_node = NULL;
    

    // printf("NYAHH EH \n %s\n", a_node->ns->href);
    for (cur_node = a_node; cur_node != NULL; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {

            // printf("Group Node type: Element, \nname: %s\n", cur_node->name);

            if(strcmp((char*)cur_node->name, "title") == 0)
            {
                
                strcpy(svg->title, (char*)cur_node->children->content);
            }
             if(strcmp((char*)cur_node->name, "desc") == 0)
            {
               
                strcpy(svg->description, (char*)cur_node->children->content);
            }
            

             if(strcmp((char*)cur_node->name, "rect") == 0 )
            {
                
                Rectangle* rect = (Rectangle*)malloc(sizeof(Rectangle));
                initRect(rect);
                rect->otherAttributes = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);
                xmlAttr *attr;
                for (attr = cur_node->properties; attr != NULL; attr = attr->next)
                {
                    xmlNode *value = attr->children;
                    char *attrName = (char *)attr->name;
                    char *cont = (char *)(value->content);
                    
                    storeRect(cont, attrName, rect, svg);

                }
                // checkRect(rect);
                insertBack(svg->rectangles, (void*)rect);    
            }
            else if(strcmp((char*)cur_node->name, "circle") == 0 )
            {
                // printf("Parent%s\n", (char*)a_node);
                Circle* circ = (Circle*)malloc(sizeof(Circle));
                initCirc(circ);
                circ->otherAttributes = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);
                xmlAttr *attr;
                for (attr = cur_node->properties; attr != NULL; attr = attr->next)
                {
                    xmlNode *value = attr->children;
                    char *attrName = (char *)attr->name;
                    char *cont = (char *)(value->content);
                    
                    storeCirc(cont, attrName, circ, svg);

                }
                // checkCirc(circ);
                insertBack(svg->circles, (void*)circ);    
            }
            else if(strcmp((char*)cur_node->name, "path") == 0)
            {
                char *size = "path";
                Path* path = createPath(size);
                path->otherAttributes = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);
                xmlAttr *attr;
                for (attr = cur_node->properties; attr != NULL; attr = attr->next)
                {
                    xmlNode *value = attr->children;
                    char *attrName = (char *)attr->name;
                    char *cont = (char *)(value->content);
                    
                    storePath(cont, attrName, path, svg);
                    
                }
                insertBack(svg->paths, (void*)path);    
            }
            else if(strcmp((char*)cur_node->name, "g") == 0)
            {
            
                
                Group* group = (Group*)malloc(sizeof(Group));
                group->rectangles = initializeList(&rectangleToString, &deleteRectangle, &compareRectangles);
                group->circles = initializeList(&circleToString, &deleteCircle, &compareCircles);
                group->paths = initializeList(&pathToString, &deletePath, &comparePaths);
                group->groups = initializeList(&groupToString, &deleteGroup, &compareGroups);
                group->otherAttributes = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);
                findGroup(cur_node->children, svg, group);
                xmlAttr *attr;
                for (attr = cur_node->properties; attr != NULL; attr = attr->next)
                {
                     xmlNode *value = attr->children;
                    char *attrName = (char *)attr->name;
                    char *cont = (char *)(value->content);
                    storeGroup(cont, attrName, group, svg);

                }
                insertBack(svg->groups, (void*)group);
                cur_node = cur_node->next;
                
            }
        
        }
        // Uncomment the code below if you want to see the content of every node.

        // if (cur_node->content != NULL ){
        //     printf("  content: %s\n", cur_node->content);
            
            
        // }

        // Iterate through every attribute of the current node
        xmlAttr *attr;
        for (attr = cur_node->properties; attr != NULL; attr = attr->next)
        {
            xmlNode *value = attr->children;
            char *attrName = (char *)attr->name;
            char *cont = (char *)(value->content);

            if(strcmp((char*)cur_node->name, "svg") == 0)
            {
                
                strcpy(svg->namespace, (char*)cur_node->ns->href);
                
                
                Attribute* structAtt = createAttribute(cont);
                structAtt->name = malloc(sizeof(char) *strlen(attrName)+2);
                
                strcpy(structAtt->name, attrName);
                strcpy(structAtt->value, cont);
                insertBack(svg->otherAttributes, (void*)structAtt);
                
            } 
            // printf("\tattribute name: %s, attribute value = %s\n", attrName, cont);  
        }  
        print_element_names(cur_node->children, svg);
    }

    return svg;

}