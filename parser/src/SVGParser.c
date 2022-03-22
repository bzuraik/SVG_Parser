#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <unistd.h>
#include <math.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#include <libxml/xmlschemastypes.h>
#include "LinkedListAPI.h"
#include "SVGParser.h"
#include "SVGHelper.h"

void docGroup(Group *tmpName, xmlNodePtr node)
{
			xmlNodePtr node1;
			// ListIterator iter = createIterator(tmpName->groups);
			if(tmpName->rectangles != NULL)
			{
				ListIterator iter3 = createIterator(tmpName->rectangles);
				void* elem2;
				while((elem2 = nextElement(&iter3)) != NULL)
				{
					Rectangle* tmpName = (Rectangle*)elem2;
					char x[20];
					sprintf(x, "%f", tmpName->x);

					char y[20];
					sprintf(y, "%f", tmpName->y);

					char H[20];
					sprintf(H, "%f", tmpName->height);

					char W[20];
					sprintf(W, "%f", tmpName->width);
					
					node1 =
					xmlNewChild(node, NULL, BAD_CAST "rect",NULL);
					xmlNewProp(node1, BAD_CAST "x", BAD_CAST x);
					xmlNewProp(node1, BAD_CAST "y", BAD_CAST y);
					xmlNewProp(node1, BAD_CAST "width", BAD_CAST W);
					xmlNewProp(node1, BAD_CAST "height", BAD_CAST H);

					if(tmpName->otherAttributes != NULL)
					{
						ListIterator iter2 = createIterator(tmpName->otherAttributes);
						void* elem;
						while((elem = nextElement(&iter2)) != NULL)
						{
							Attribute* tmpName = (Attribute*)elem;
							xmlNewProp(node1, BAD_CAST tmpName->name, BAD_CAST tmpName->value);
						}
					}

				}
			}		

			if(tmpName->circles != NULL)
			{
				ListIterator iter4 = createIterator(tmpName->circles);
				void* elem3;
				while((elem3 = nextElement(&iter4)) != NULL)
				{
					Circle* tmpName = (Circle*)elem3;
					char cx[20];
					sprintf(cx, "%f", tmpName->cx);

					char cy[20];
					sprintf(cy, "%f", tmpName->cy);

					char r[20];
					sprintf(r, "%f", tmpName->r);

					node1 =
					xmlNewChild(node, NULL, BAD_CAST "circle",NULL);
					xmlNewProp(node1, BAD_CAST "cx", BAD_CAST cx);
					xmlNewProp(node1, BAD_CAST "cy", BAD_CAST cy);
					xmlNewProp(node1, BAD_CAST "r", BAD_CAST r);

					if(tmpName->otherAttributes != NULL)
					{
						ListIterator iter2 = createIterator(tmpName->otherAttributes);
						void* elem;
						while((elem = nextElement(&iter2)) != NULL)
						{
							Attribute* tmpName = (Attribute*)elem;
							xmlNewProp(node1, BAD_CAST tmpName->name, BAD_CAST tmpName->value);
						}
					}
	
				}
			}
			if(tmpName->paths!= NULL)
			{
				ListIterator iter5 = createIterator(tmpName->paths);

				void* elem4;
				while((elem4 = nextElement(&iter5)) != NULL)
				{
					Path* tmpName = (Path*)elem4;
					


					node1 =
					xmlNewChild(node, NULL, BAD_CAST "path",NULL);
					xmlNewProp(node1, BAD_CAST "d", BAD_CAST tmpName->data);
				
					if(tmpName->otherAttributes != NULL)
					{
						ListIterator iter2 = createIterator(tmpName->otherAttributes);
						void* elem;
						while((elem = nextElement(&iter2)) != NULL)
						{
							Attribute* tmpName = (Attribute*)elem;
							xmlNewProp(node1, BAD_CAST tmpName->name, BAD_CAST tmpName->value);
						}
					}

				}
			}
			
			if(tmpName->groups != NULL)
			{
				if(getLength(tmpName->groups) != 0)
				{
					ListIterator iter5 = createIterator(tmpName->groups);
					void* elem4;
					while((elem4 = nextElement(&iter5)) != NULL)
					{
						Group* tmpName = (Group*)elem4;
						node1 = xmlNewChild(node, NULL, BAD_CAST "g", NULL);

						if(tmpName->otherAttributes != NULL)
						{
							ListIterator iter2 = createIterator(tmpName->otherAttributes);
							void* elem;
							while((elem = nextElement(&iter2)) != NULL)
							{
								Attribute* tmpName = (Attribute*)elem;
								xmlNewProp(node1, BAD_CAST tmpName->name, BAD_CAST tmpName->value);
							}
						}
						
						docGroup(tmpName, node1);
					}
					
							
				}
			}		// To do: deal with units	
}

xmlDoc *createTree(const SVG* svg)
{

    xmlNodePtr node = NULL;/* node pointers */
	xmlNsPtr ns1;
    LIBXML_TEST_VERSION;

    /* 
     * Creates a new document, a node and set it as a root node
     */
    xmlDoc *doc = xmlNewDoc(BAD_CAST "1.0");
    xmlNode *root_node = xmlNewNode(NULL, BAD_CAST "svg");
    xmlDocSetRootElement(doc, root_node);

	ns1 = xmlNewNs(root_node, BAD_CAST svg->namespace, NULL);
		xmlSetNs(root_node, ns1);

    /* 
     * xmlNewChild() creates a new node, which is "attached" as child node
     * of root_node node. 
     */
	if(strlen(svg->title) > 1)
	{
		xmlNewChild(root_node, NULL, BAD_CAST "title",
                BAD_CAST svg->title);	
	}

	if(strlen(svg->description) > 1)
	{
		xmlNewChild(root_node, NULL, BAD_CAST "desc",
                BAD_CAST svg->description);
	}

	
	if(svg->otherAttributes != NULL)
	{
		ListIterator iter = createIterator(svg->otherAttributes);
		void* elem;
		while((elem = nextElement(&iter)) != NULL)
		{
			Attribute* tmpName = (Attribute*)elem;
			xmlNewProp(root_node, BAD_CAST tmpName->name, BAD_CAST tmpName->value);
		}
	}
	if(svg->rectangles != NULL)
	{
		
		ListIterator iter = createIterator(svg->rectangles);

		void* elem;
		while((elem = nextElement(&iter)) != NULL)
		{
			Rectangle* tmpName = (Rectangle*)elem;
			if(strlen(tmpName->units) != 0)
			{
				
				char x[256];
				sprintf(x, "%f%s", tmpName->x, tmpName->units);

				char y[256];
				sprintf(y, "%f%s", tmpName->y, tmpName->units);

				char H[256];
				sprintf(H, "%f%s", tmpName->height, tmpName->units);

				char W[256];
				sprintf(W, "%f%s", tmpName->width, tmpName->units);
				node =
				xmlNewChild(root_node, NULL, BAD_CAST "rect",NULL);
				xmlNewProp(node, BAD_CAST "x", BAD_CAST x);
				xmlNewProp(node, BAD_CAST "y", BAD_CAST y);
				xmlNewProp(node, BAD_CAST "width", BAD_CAST W);
				xmlNewProp(node, BAD_CAST "height", BAD_CAST H);
			}
			else
			{
				
				char x[256];
				sprintf(x, "%f", tmpName->x);

				char y[256];
				sprintf(y, "%f", tmpName->y);

				char H[256];
				sprintf(H, "%f", tmpName->height);

				char W[256];
				sprintf(W, "%f", tmpName->width);
				node =
				xmlNewChild(root_node, NULL, BAD_CAST "rect",NULL);
				xmlNewProp(node, BAD_CAST "x", BAD_CAST x);
				xmlNewProp(node, BAD_CAST "y", BAD_CAST y);
				xmlNewProp(node, BAD_CAST "width", BAD_CAST W);
				xmlNewProp(node, BAD_CAST "height", BAD_CAST H);
			}
			
			
			if(tmpName->otherAttributes != NULL)
			{
				ListIterator iter2 = createIterator(tmpName->otherAttributes);
				void* elem;
				while((elem = nextElement(&iter2)) != NULL)
				{
					Attribute* tmpName = (Attribute*)elem;
					xmlNewProp(node, BAD_CAST tmpName->name, BAD_CAST tmpName->value);
				}
			}
			
			// To do: deal with units	
		}
		
	}
	if(svg->circles != NULL)
	{

		ListIterator iter = createIterator(svg->circles);

		void* elem;
		while((elem = nextElement(&iter)) != NULL)
		{
			Circle* tmpName = (Circle*)elem;

			if(strlen(tmpName->units) != 0)
			{
				char cx[256];
				sprintf(cx, "%f%s", tmpName->cx, tmpName->units);

				char cy[256];
				sprintf(cy, "%f%s", tmpName->cy, tmpName->units);

				char r[256];
				sprintf(r, "%f%s", tmpName->r, tmpName->units);


				node =
				xmlNewChild(root_node, NULL, BAD_CAST "circle",NULL);
				xmlNewProp(node, BAD_CAST "cx", BAD_CAST cx);
				xmlNewProp(node, BAD_CAST "cy", BAD_CAST cy);
				xmlNewProp(node, BAD_CAST "r", BAD_CAST r);
			}
			else
			{
				char cx[256];
				sprintf(cx, "%f", tmpName->cx);

				char cy[256];
				sprintf(cy, "%f", tmpName->cy);

				char r[256];
				sprintf(r, "%f", tmpName->r);


				node =
				xmlNewChild(root_node, NULL, BAD_CAST "circle",NULL);
				xmlNewProp(node, BAD_CAST "cx", BAD_CAST cx);
				xmlNewProp(node, BAD_CAST "cy", BAD_CAST cy);
				xmlNewProp(node, BAD_CAST "r", BAD_CAST r);
			}
			
			if(tmpName->otherAttributes != NULL)
			{
				ListIterator iter2 = createIterator(tmpName->otherAttributes);
				void* elem;
				while((elem = nextElement(&iter2)) != NULL)
				{
					Attribute* tmpName = (Attribute*)elem;
					xmlNewProp(node, BAD_CAST tmpName->name, BAD_CAST tmpName->value);
				}
			}
			
			// To do: deal with units	
		}
	}
	if(svg->paths != NULL)
	{
		ListIterator iter = createIterator(svg->paths);

		void* elem;
		while((elem = nextElement(&iter)) != NULL)
		{
			Path* tmpName = (Path*)elem;
			


			node =
			xmlNewChild(root_node, NULL, BAD_CAST "path",NULL);
			xmlNewProp(node, BAD_CAST "d", BAD_CAST tmpName->data);
		
			if(tmpName->otherAttributes != NULL)
			{
				ListIterator iter2 = createIterator(tmpName->otherAttributes);
				void* elem;
				while((elem = nextElement(&iter2)) != NULL)
				{
					Attribute* tmpName = (Attribute*)elem;
					xmlNewProp(node, BAD_CAST tmpName->name, BAD_CAST tmpName->value);
				}
			}
			
			// To do: deal with units	
		}

	}


    /* 
     * A simple loop that "automates" nodes creation 
     */
	if(getLength(svg->groups) != 0 && svg->groups != NULL)
	{
			ListIterator iter5 = createIterator(svg->groups);

			void* elem4;
			while((elem4 = nextElement(&iter5)) != NULL)
			{
				Group* tmpName = (Group*)elem4;
				node = xmlNewChild(root_node, NULL, BAD_CAST "g", NULL);

				if(tmpName->otherAttributes != NULL)
				{
					ListIterator iter2 = createIterator(tmpName->otherAttributes);
					void* elem;
					while((elem = nextElement(&iter2)) != NULL)
					{
						Attribute* tmpName = (Attribute*)elem;
						xmlNewProp(node, BAD_CAST tmpName->name, BAD_CAST tmpName->value);
					}
				}
				docGroup(tmpName, node);
				// To do: deal with units	
			}
				
	}
    
    return doc;
}

bool validateContentGroups(Group * tmpName)
{
	if(tmpName->rectangles == NULL)
	{
		return false;
	}
	else
	{
		ListIterator iter = createIterator(tmpName->rectangles);
		void* elem;
		while((elem = nextElement(&iter)) != NULL)
		{
			Rectangle* tmpName = (Rectangle*)elem;
			if(tmpName->width < 0)
			{
				return false;
			}
			if(tmpName->height < 0)
			{
				return false;
			}
			if(tmpName->otherAttributes == NULL)
			{
				return false;
			}

			ListIterator iter = createIterator(tmpName->otherAttributes);
			void* elem;
			while((elem = nextElement(&iter)) != NULL)
			{
				Attribute* tmpName = (Attribute*)elem;
				if(tmpName->name == NULL)
				{
					return false;
				}
			}

		}
	}

	if(tmpName->circles == NULL)
	{
		return false;
	}
	else
	{
		ListIterator iter = createIterator(tmpName->circles);
		void* elem;
		while((elem = nextElement(&iter)) != NULL)
		{
			Circle* tmpName = (Circle*)elem;
			if(tmpName->r < 0)
			{
				return false;
			}
			if(tmpName->otherAttributes == NULL)
			{
				return false;
			}

			if(tmpName->otherAttributes != NULL)
			{
				ListIterator iter = createIterator(tmpName->otherAttributes);
				void* elem;
				while((elem = nextElement(&iter)) != NULL)
				{
					Attribute* tmpName = (Attribute*)elem;
					if(tmpName->name == NULL)
					{
						return false;
					}
				}
			}
			
		}
	}
	
	if(tmpName->paths == NULL)
	{
		return false;
	}
	else
	{
		ListIterator iter = createIterator(tmpName->paths);
		void* elem;
		while((elem = nextElement(&iter)) != NULL)
		{
			Path* tmpName = (Path*)elem;
			if(tmpName->data == NULL)
			{
				return false;
			}
			else if(tmpName->otherAttributes == NULL)
			{
				return false;
			}

			ListIterator iter = createIterator(tmpName->otherAttributes);
			void* elem;
			while((elem = nextElement(&iter)) != NULL)
			{
				Attribute* tmpName = (Attribute*)elem;
				if(tmpName->name == NULL)
				{
					return false;
				}
			}
		}
	}

	if(tmpName->otherAttributes == NULL)
	{
		return false;

	}
	else
	{
		ListIterator iter = createIterator(tmpName->otherAttributes);
		void* elem;
		while((elem = nextElement(&iter)) != NULL)
		{
			Attribute* tmpName = (Attribute*)elem;
			if(tmpName->name == NULL)
			{
				return false;
			}
		}
	}

	if(tmpName->groups == NULL)
	{
		return false;
	}
	if(getLength(tmpName->groups) != 0)
	{
		ListIterator iter = createIterator(tmpName->groups);
		void* elem;
		while((elem = nextElement(&iter)) != NULL)
		{
			Group* tmpName = (Group*)elem;
			bool result = validateContentGroups(tmpName);
			if(!(result))
			{
				return false;
			}
		}
	}
	return true;
}

bool validateContent(const SVG* svg)
{

	if(svg->rectangles == NULL)
	{
		return false;
	}
	else
	{
		ListIterator iter = createIterator(svg->rectangles);
		void* elem;
		while((elem = nextElement(&iter)) != NULL)
		{
			Rectangle* tmpName = (Rectangle*)elem;
			if(tmpName->width < 0)
			{
				return false;
			}
			if(tmpName->height < 0)
			{
				return false;
			}
			if(tmpName->otherAttributes == NULL)
			{
				return false;
			}

			ListIterator iter = createIterator(tmpName->otherAttributes);
			void* elem;
			while((elem = nextElement(&iter)) != NULL)
			{
				Attribute* tmpName = (Attribute*)elem;
				if(tmpName->name == NULL)
				{
					return false;
				}
			}

		}
	}

	if(svg->circles == NULL)
	{
		return false;
	}
	else
	{
		ListIterator iter = createIterator(svg->circles);
		void* elem;
		while((elem = nextElement(&iter)) != NULL)
		{
			Circle* tmpName = (Circle*)elem;
			if(tmpName->r < 0)
			{
				return false;
			}
			if(tmpName->otherAttributes == NULL)
			{
				return false;
			}

			if(tmpName->otherAttributes != NULL)
			{
				ListIterator iter = createIterator(tmpName->otherAttributes);
				void* elem;
				while((elem = nextElement(&iter)) != NULL)
				{
					Attribute* tmpName = (Attribute*)elem;
					if(tmpName->name == NULL)
					{
						return false;
					}
				}
			}
			
		}
	}
	
	if(svg->paths == NULL)
	{
		return false;
	}
	else
	{
		ListIterator iter = createIterator(svg->paths);
		void* elem;
		while((elem = nextElement(&iter)) != NULL)
		{
			Path* tmpName = (Path*)elem;
			if(tmpName->data == NULL)
			{
				return false;
			}
			else if(tmpName->otherAttributes == NULL)
			{
				return false;
			}

			ListIterator iter = createIterator(tmpName->otherAttributes);
			void* elem;
			while((elem = nextElement(&iter)) != NULL)
			{
				Attribute* tmpName = (Attribute*)elem;
				if(tmpName->name == NULL)
				{
					return false;
				}
			}
		}
	}

	if(svg->otherAttributes == NULL)
	{
		return false;

	}
	else
	{
		ListIterator iter = createIterator(svg->otherAttributes);
		void* elem;
		while((elem = nextElement(&iter)) != NULL)
		{
			Attribute* tmpName = (Attribute*)elem;
			if(tmpName->name == NULL)
			{
				return false;
			}
		}
	}

	if(svg->groups == NULL)
	{
		return false;
	}
	if(getLength(svg->groups) != 0)
	{
		
		ListIterator iter = createIterator(svg->groups);
		void* elem;
		while((elem = nextElement(&iter)) != NULL)
		{
			Group* tmpName = (Group*)elem;
			bool result = validateContentGroups(tmpName);
			if(!result)
			{
				return false;
			}
		}
		
	}
		
	

	return true;
}

bool validateSVG(const SVG* img, const char* schemaFile)
{
	if(img == NULL )
	{
        return NULL;
    }
    
    xmlDocPtr doc = createTree(img); 
	if (doc == NULL)
	{
		xmlFreeDoc(doc);
		xmlCleanupParser();
		return false; 
	}
    xmlSchemaPtr schema = NULL;
    xmlSchemaParserCtxtPtr ctxt;
    
    xmlLineNumbersDefault(1);

    ctxt = xmlSchemaNewParserCtxt(schemaFile);

    xmlSchemaSetParserErrors(ctxt, (xmlSchemaValidityErrorFunc) fprintf, (xmlSchemaValidityWarningFunc) fprintf, stderr);
    schema = xmlSchemaParse(ctxt);
    xmlSchemaFreeParserCtxt(ctxt);

    
    xmlSchemaValidCtxtPtr ctxt2;
    ctxt2 = xmlSchemaNewValidCtxt(schema);
    xmlSchemaSetValidErrors(ctxt2, (xmlSchemaValidityErrorFunc) fprintf, (xmlSchemaValidityWarningFunc) fprintf, stderr);
	int result = 0;
    result = xmlSchemaValidateDoc(ctxt2, doc);

	if(!validateContent(img))
	{
       result = -1;
    }
    if (result == 0)
    {
        
        xmlFreeDoc(doc);
        if(schema != NULL)
		{
            xmlSchemaFree(schema);
		}
            xmlSchemaCleanupTypes();
            xmlSchemaFreeValidCtxt(ctxt2);
            xmlMemoryDump();
            xmlCleanupParser();
        
        return true; 
    }
    else
    {
        xmlFreeDoc(doc);
        if(schema != NULL)
		{
            xmlSchemaFree(schema);
		}
            xmlSchemaCleanupTypes();
            xmlSchemaFreeValidCtxt(ctxt2);
            xmlMemoryDump();
            xmlCleanupParser();
        

    }
    
    return false;
} 

SVG* createValidSVG(const char* fileName, const char* schemaFile)
{
	if(!(access( fileName, F_OK ) == 0) || !(access( schemaFile, F_OK ) == 0))
	{
        return NULL;
    }
    

    xmlDocPtr doc =  xmlReadFile(fileName, NULL, 0);;
	if (doc == NULL)
	{
		xmlFreeDoc(doc);
		xmlCleanupParser();
		return false; 
	}
	SVG* svg = NULL;
	
    xmlSchemaPtr schema = NULL;
    xmlSchemaParserCtxtPtr ctxt;
    
    xmlLineNumbersDefault(1);

    ctxt = xmlSchemaNewParserCtxt(schemaFile);

    xmlSchemaSetParserErrors(ctxt, (xmlSchemaValidityErrorFunc) fprintf, (xmlSchemaValidityWarningFunc) fprintf, stderr);
    schema = xmlSchemaParse(ctxt);
    xmlSchemaFreeParserCtxt(ctxt);
	

    xmlSchemaValidCtxtPtr ctxt2;
    ctxt2 = xmlSchemaNewValidCtxt(schema);
    xmlSchemaSetValidErrors(ctxt2, (xmlSchemaValidityErrorFunc) fprintf, (xmlSchemaValidityWarningFunc) fprintf, stderr);
	int result = 0;
    result = xmlSchemaValidateDoc(ctxt2, doc);
    if (result == 0)
    {
		
       
		xmlFreeDoc(doc);
		xmlSchemaFreeValidCtxt(ctxt2);
        if(schema != NULL)
		{
            xmlSchemaFree(schema);
		}
		
		xmlSchemaCleanupTypes();
		xmlMemoryDump();
		xmlCleanupParser();

		svg = createSVG(fileName);
        
    }
    else
    {
		xmlSchemaFreeValidCtxt(ctxt2);
        xmlFreeDoc(doc);

        if(schema != NULL)
		{
            xmlSchemaFree(schema);
		}
            xmlSchemaCleanupTypes();
            xmlMemoryDump();
            xmlCleanupParser();
        

    }
    return svg;
}

bool writeSVG(const SVG* img, const char* fileName)
{
	xmlDoc *doc = NULL;
	if(fileName == NULL || img == NULL)
	{
		return false;
	}

	doc = createTree(img);

	if ( doc == NULL)
	{
		xmlFreeDoc(doc);
		xmlCleanupParser();
		return false;
	}

    	xmlSaveFormatFileEnc(fileName, doc, "UTF-8", 1);
		xmlFreeDoc(doc);
		xmlCleanupParser();
    	xmlMemoryDump();
	 
	

	return true;
}

//This function does the parsing and allocates an SVG struct
SVG* createSVG(const char* fileName){

    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;
	
	
	
    
    LIBXML_TEST_VERSION

    /*parse the file and get the DOM */
    doc = xmlReadFile(fileName, NULL, 0);

    if (doc == NULL) {
		xmlFreeDoc(doc);
		xmlCleanupParser();
		return NULL;
    }
	
    root_element = xmlDocGetRootElement(doc);
	

	SVG* svg = (SVG*)malloc(sizeof(SVG));

	strcpy(svg->title, "");
	strcpy(svg->description, "");
	svg->rectangles = initializeList(&rectangleToString, &deleteRectangle, &compareRectangles);
    svg->circles = initializeList(&circleToString, &deleteCircle, &compareCircles);
    svg->paths = initializeList(&pathToString, &deletePath, &comparePaths);
    svg->groups = initializeList(&groupToString, &deleteGroup, &compareGroups);
    svg->otherAttributes = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);
    
    svg = print_element_names(root_element, svg);
	

    /*free the document */
    xmlFreeDoc(doc);
	

    /*
     *Free the global variables that may
     *have been allocated by the parser.
     */
    xmlCleanupParser();
    

    return svg;
    
}

char* SVGToString(const SVG* img)
{
	if(img == NULL)
	{
		return NULL;
	}

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
	
	if (data == NULL){
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
	
	if (data == NULL){
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
	
	// int length = strlen(tmpName->units);
	char *str3 = toString(tmpName->otherAttributes);
	
	tmpStr = malloc(sizeof(str3) * len + 24);

	sprintf(tmpStr, "\nRect\nx = %f y = %f Width = %f = Height = %f units =%s\n", tmpName->x, tmpName->y, tmpName->width, tmpName->height, tmpName->units);
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

void getRectG(List *Slist, List *list)
{

		ListIterator iter1 = createIterator(list);

		void* elem1;
		while((elem1 = nextElement(&iter1)) != NULL)
		{
			Group* tmpName = (Group*)elem1;
			ListIterator iter = createIterator(tmpName->rectangles);

			void* elem;
			while((elem = nextElement(&iter)) != NULL)
			{
				
				Rectangle* tmpName = (Rectangle*)elem;
				
				insertBack(Slist, tmpName);
				
			}

			if(getLength(tmpName->groups) > 0)
			{
				getRectG(Slist, tmpName->groups);
			}
		}
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
	


	void* elem;
	while((elem = nextElement(&iter)) != NULL){
		Rectangle* tmpName = (Rectangle*)elem;
		
		insertBack(list, tmpName);

	}

	void* elem1;
	while((elem1 = nextElement(&iter1)) != NULL){
		Group* tmpName = (Group*)elem1;
		ListIterator iter2 = createIterator(tmpName->rectangles);
		void* elem2;
		while((elem2 = nextElement(&iter2)) != NULL)
		{
			
			Rectangle* tmpName = (Rectangle*)elem2;
			insertBack(list, tmpName);
			
		}
		if(getLength(tmpName->groups) != 0)
		{
			
				getRectG(list, tmpName->groups);
		}
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

void getCircG(List *Slist, List *list)
{

		ListIterator iter1 = createIterator(list);

		void* elem1;
		while((elem1 = nextElement(&iter1)) != NULL)
		{
			Group* tmpName = (Group*)elem1;
			ListIterator iter = createIterator(tmpName->circles);

			void* elem;
			while((elem = nextElement(&iter)) != NULL)
			{
				
				Circle* tmpName = (Circle*)elem;
				
				insertBack(Slist, tmpName);
				
			}

			if(getLength(tmpName->groups) > 0)
			{
				getRectG(Slist, tmpName->groups);
			}
		}
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

			if(getLength(tmpName->groups) != 0)
			{
				
					getCircG(list, tmpName->groups);
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
void getGroupsH(List *Slist, List* group)
{

	ListIterator iter = createIterator(group);
	void* elem;
	while((elem = nextElement(&iter)) != NULL){
		Group* tmpName = (Group*)elem;
		insertBack(Slist, tmpName);

		if(getLength(tmpName->groups)!= 0)
		{
			getGroupsH(Slist, tmpName->groups);
		} 
		
		
	}

}
List* getGroups(const SVG* img)
{
	if(img == NULL)
	{
		return NULL;
	}
	List *list = initializeList(&groupToStringList, &deleteGroupList, &compareGroups);
	getGroupsH(list, img->groups);
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

void getPathG(List *Slist, List *list)
{

		ListIterator iter1 = createIterator(list);

		void* elem1;
		while((elem1 = nextElement(&iter1)) != NULL)
		{
			Group* tmpName = (Group*)elem1;
			ListIterator iter = createIterator(tmpName->paths);

			void* elem;
			while((elem = nextElement(&iter)) != NULL)
			{
				
				Path* tmpName = (Path*)elem;
				
				insertBack(Slist, tmpName);
				
			}

			if(getLength(tmpName->groups) > 0)
			{
				getRectG(Slist, tmpName->groups);
			}
		}
}
List* getPaths(const SVG* img)
{
	if(img == NULL)
	{
		return NULL;
	}
	List *list = initializeList(&CircleToStringList, &deleteCircleList, &compareCircles);

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

			if(getLength(tmpName->groups) != 0)
			{
					getPathG(list, tmpName->groups);
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
	return 0; 
}
// Function that returns the number of all groups with the specified length - 
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
		// int groupL = getLength(tmpName->groups);
		
		total = circL + rectL + pathL;
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



bool setAttribute(SVG* img, elementType elemType, int elemIndex, Attribute* newAttribute)
{
	if(img == NULL || newAttribute == NULL)
	{
		return false;
	}

	if(elemType == RECT)
	{
		if(newAttribute->name == NULL)
		{
			return false;
		}
		if(elemIndex < 0)
		{
			return false;
		}
		if(img->rectangles == NULL)
		{
			return false;
		}
		ListIterator iter = createIterator(img->rectangles);
		int count = 0;

		void* elem;
		while((elem = nextElement(&iter)) != NULL)
		{
			if(count == elemIndex)
			{
				Rectangle* tmpRect = (Rectangle*)elem;
				if(strcmp(newAttribute->name, "x") == 0)
				{
					tmpRect->x = atof(newAttribute->value);
					free(newAttribute->name);
					free(newAttribute);
					
					return true;
				}
				else if(strcmp(newAttribute->name, "y") == 0)
				{
					tmpRect->y = atof(newAttribute->value);
					free(newAttribute->name);
					free(newAttribute);
					
					return true;
				}
				else if(strcmp(newAttribute->name, "width") == 0)
				{
					tmpRect->width = atof(newAttribute->value);
					free(newAttribute->name);
					free(newAttribute);
					return true;
				}
				else if(strcmp(newAttribute->name, "height") == 0)
				{
					tmpRect->height = atof(newAttribute->value);
					free(newAttribute->name);
					free(newAttribute);
					return true;
				} 
				else
				{
					if(tmpRect->otherAttributes != NULL && getLength(tmpRect->otherAttributes) > 0)
					{
						ListIterator iter = createIterator(tmpRect->otherAttributes);
						void* elem;
						while((elem = nextElement(&iter)) != NULL)
						{
							Attribute* tmpName = (Attribute*)elem;
							if(strcmp(newAttribute->name, tmpName->name) == 0)
							{
								strcpy(tmpName->value, newAttribute->value);
								free(newAttribute->name);
								free(newAttribute);
								return true;
							}
						}

					}
						insertBack(tmpRect->otherAttributes, (void*)newAttribute);				
						return true;		
				}
			}
			count++;
		}	
	}
	else if(elemType == CIRC)
	{
		if(elemIndex < 0)
		{
			return false;
		}
		
		ListIterator iter = createIterator(img->circles);
		int count = 0;

		void* elem;
		while((elem = nextElement(&iter)) != NULL)
		{
			if(count == elemIndex)
			{
				Circle* tmpCirc = (Circle*)elem;
				if(strcmp(newAttribute->name, "cx") == 0)
				{

					tmpCirc->cx = atof(newAttribute->value);
					free(newAttribute->name);
					free(newAttribute);
					
					return true;
				}
				else if(strcmp(newAttribute->name, "cy") == 0)
				{
					tmpCirc->cy = atof(newAttribute->value);
					free(newAttribute->name);
					free(newAttribute);
					
					return true;
				}
				else if(strcmp(newAttribute->name, "r") == 0)
				{
					tmpCirc->r = atof(newAttribute->value);
					free(newAttribute->name);
					free(newAttribute);
					
					return true;
				}
				else
				{
					if(tmpCirc->otherAttributes != NULL && getLength(tmpCirc->otherAttributes) != 0)
					{
						ListIterator iter = createIterator(tmpCirc->otherAttributes);
						void* elem;
						while((elem = nextElement(&iter)) != NULL)
						{
							Attribute* tmpName = (Attribute*)elem;
							if(strcmp(newAttribute->name, tmpName->name) == 0)
							{

								strcpy(tmpName->value, newAttribute->value);
								free(newAttribute->name);
								free(newAttribute);
								
								return true;
							}
						}
					}					
					insertBack(tmpCirc->otherAttributes, (void*)newAttribute);						
					return true;	
				}
			}
			count++;

		}
	
	}
	else if(elemType == PATH)
	{
		if(elemIndex < 0)
		{
			return false;
		}
		
		ListIterator iter = createIterator(img->paths);
		int count = 0;

		void* elem;
		while((elem = nextElement(&iter)) != NULL)
		{
			if(count == elemIndex)
			{
				Path* tmpPath = (Path*)elem;
				if(strcmp(newAttribute->name, "d") == 0)
				{

					strcpy(tmpPath->data, newAttribute->value);
					free(newAttribute->name);
					free(newAttribute);
					
					return true;
				}
				else
				{
					if(tmpPath->otherAttributes != NULL && getLength(tmpPath->otherAttributes) != 0)
					{
						ListIterator iter = createIterator(tmpPath->otherAttributes);
						void* elem;
						while((elem = nextElement(&iter)) != NULL)
						{
							Attribute* tmpName = (Attribute*)elem;
							if(strcmp(newAttribute->name, tmpName->name) == 0)
							{
								strcpy(tmpName->value, newAttribute->value);
								free(newAttribute->name);
								free(newAttribute);
								return true;
							}
						}
					}	
						insertBack(tmpPath->otherAttributes, (void*)newAttribute);
						return true;	
				}
			}
			count++;
		}
	
	}
	else if(elemType == SVG_IMG)
	{
		if(strcmp(newAttribute->name, "title") == 0)
		{
			strcpy(img->title, newAttribute->value);
			free(newAttribute->name);
			free(newAttribute);
			return true;
		}
		else if(strcmp(newAttribute->name, "title") == 0)
		{
			strcpy(img->title, newAttribute->value);
			free(newAttribute->name);
			free(newAttribute);
			return true;
		}
		else
		{
			if(img->otherAttributes != NULL)
			{
				if(getLength(img->otherAttributes) != 0)
				{
					ListIterator iter = createIterator(img->otherAttributes);
					void* elem;
					while((elem = nextElement(&iter)) != NULL)
					{
						Attribute* tmpName = (Attribute*)elem;
						if(strcmp(tmpName->name, newAttribute->name) == 0)
						{
							strcpy(tmpName->value, newAttribute->value);
							free(newAttribute->name);
							free(newAttribute);
							return true;
						}
						
					}
				}
					insertBack(img->otherAttributes, newAttribute);
					return true;
			}
		}
	}
	else
	{
		return false;
	}
	return false;
}

void addComponent(SVG* img, elementType type, void* newElement)
{
	if(img != NULL)
	{
		if(type == RECT)
		{
			Rectangle* tmpName = (Rectangle*)newElement;
			insertBack(img->rectangles,tmpName);
		}
		if(type == CIRC)
		{
			Circle* tmpName = (Circle*)newElement;
			insertBack(img->circles,tmpName);
		}
		if(type == PATH)
		{
			Path* tmpName = (Path*)newElement;
			insertBack(img->paths,tmpName);
		}
		
	}
}

char* attrToJSON(const Attribute *a)
{
	char *string = "{}";
	if(a == NULL)
	{
		return string;
	}
	int len = strlen(a->name)+strlen(a->value)+24;
	string = (char*)malloc(sizeof(char)*len + 100);

	sprintf(string, "{\"name\":\"%s\",\"value\":\"%s\"}", a->name, a->value);
	return string;
}

char* circleToJSON(const Circle *c)
{
	char *string = "{}";
	if(c == NULL)
	{
		return string;
	}
	int len = snprintf(NULL, 0, "%f %f %f", c->cx, c->cy, c->r);
	string = (char*)malloc(sizeof(char)*len + 1000);
	int numAtt = getLength(c->otherAttributes);
	char units[20] = "";
	strcpy(units, c->units);

	sprintf(string, "{\"cx\":%.2f,\"cy\":%.2f,\"r\":%.2f,\"numAttr\":%d,\"units\":\"%s\"}", c->cx, c->cy, c->r, numAtt, c->units);
	return string;
	
}
char* rectToJSON(const Rectangle *r)
{
	char *string = "{}";
	if(r == NULL)
	{
		return string;
	}
	int len = snprintf(NULL, 0, "%f %f %f %f", r->x, r->y, r->width, r->height);
	string = (char*)malloc(sizeof(char)*len + 100);
	int numAtt = getLength(r->otherAttributes);

	sprintf(string, "{\"x\":%.2f,\"y\":%.2f,\"w\":%.2f,\"h\":%.2f,\"numAttr\":%d,\"units\":\"%s\"}", r->x, r->y, r->width, r->height,numAtt,r->units);
	return string;
}
char* pathToJSON(const Path *p)
{
	char *string = "{}";
	if(p == NULL)
	{
		return string;
	}
	string = (char*)malloc(sizeof(char)*strlen(p->data) + 100);
	int numAtt = getLength(p->otherAttributes);
	char *tempD = malloc(sizeof(char)* strlen(p->data)+2);
	strcpy(tempD,p->data);
	if(strlen(tempD) > 64)
	{
		tempD[64] = '\0';
	}
	

	sprintf(string, "{\"d\":\"%s\",\"numAttr\":%d}", tempD, numAtt);
	free(tempD);
	return string;
	
}
char* groupToJSON(const Group *g)
{
	char *string = "{}";
	if(g == NULL)
	{
		return string;
	}
	string = (char*)malloc(sizeof(char)* 100);
	int numAtt = getLength(g->otherAttributes);
	int children = 0;
	children += getLength(g->rectangles);
	children += getLength(g->circles);
	children += getLength(g->paths);
	children += getLength(g->groups);


	sprintf(string, "{\"children\":%d,\"numAttr\":%d}", children, numAtt);
	return string;
}
char* attrListToJSON(const List *list)
{
	char *string = NULL;
	char *tempString = NULL;
	int size = 0;
	if(list == NULL)
	{
		return "[]";
	}
	
	ListIterator iter = createIterator((List*)list);
	void* elem;
	while((elem = nextElement(&iter)) != NULL)
	{
		Attribute* tmpName = (Attribute*)elem;
		char *str = attrToJSON(tmpName);
		size += strlen(str);
		free(str);

	}
	string = malloc(sizeof(char)*size+24);
	strcpy(string, "[");
	ListIterator iter2 = createIterator((List*)list);
	int stop = getLength((List*)list);
	int count = 0;
	void* elem2;
	while((elem2 = nextElement(&iter2)) != NULL)
	{
		count++;
		Attribute* tmpName = (Attribute*)elem2;
		// tempString = malloc(sizeof(char)*size + 24);
		tempString = attrToJSON(tmpName);

		strcat(string, tempString);
		if(count != stop)
		{
			strcat(string, ",");
		}
		
		free(tempString);
		tempString = NULL;
	}
	
	strcat(string, "]");
	return string;
}
char* circListToJSON(const List *list)
{

	char *string = NULL;
	char *tempString = NULL;
	int size = 0;
	if(list == NULL)
	{
		return "[]";
	}
	
	ListIterator iter = createIterator((List*)list);
	void* elem;
	while((elem = nextElement(&iter)) != NULL)
	{
		Circle* tmpName = (Circle*)elem;
		char *str = circleToJSON(tmpName);
		size += strlen(str);
		
		free(str);

	}
	string = malloc(sizeof(char)*size+24);
	strcpy(string, "[");
	ListIterator iter2 = createIterator((List*)list);
	int stop = getLength((List*)list);
	int count = 0;
	void* elem2;
	while((elem2 = nextElement(&iter2)) != NULL)
	{
		count++;
		Circle* tmpName = (Circle*)elem2;
		
		tempString = circleToJSON(tmpName);

		
		strcat(string, tempString);
		if(count != stop)
		{
			strcat(string, ",");
		}
		
		free(tempString);
		tempString = NULL;
	}
	
	strcat(string, "]");
	return string;
}
char* rectListToJSON(const List *list)
{
	char *string = NULL;
	char *tempString = NULL;
	int size = 0;
	if(list == NULL)
	{
		return "[]";
	}
	
	ListIterator iter = createIterator((List*)list);
	void* elem;
	while((elem = nextElement(&iter)) != NULL)
	{
		Rectangle* tmpName = (Rectangle*)elem;
		char *str = rectToJSON(tmpName);
		size += strlen(str);
		
		free(str);

	}
	string = malloc(sizeof(char)*size+24);
	strcpy(string, "[");
	ListIterator iter2 = createIterator((List*)list);
	int stop = getLength((List*)list);
	int count = 0;
	void* elem2;
	while((elem2 = nextElement(&iter2)) != NULL)
	{
		count++;
		Rectangle* tmpName = (Rectangle*)elem2;
		
		tempString = rectToJSON(tmpName);

		strcat(string, tempString);
		if(count != stop)
		{
			strcat(string, ",");
		}
		
		free(tempString);
		tempString = NULL;
	}
	
	strcat(string, "]");
	return string;
}
char* pathListToJSON(const List *list)
{

	char *string = NULL;
	char *tempString = NULL;
	int size = 0;
	if(list == NULL)
	{
		return "[]";
	}
	
	ListIterator iter = createIterator((List*)list);
	void* elem;
	while((elem = nextElement(&iter)) != NULL)
	{
		Path* tmpName = (Path*)elem;
		char *str = pathToJSON(tmpName);
		size += strlen(str);
		
		free(str);

	}
	string = malloc(sizeof(char)*size+24);
	strcpy(string, "[");
	ListIterator iter2 = createIterator((List*)list);
	int stop = getLength((List*)list);
	int count = 0;
	void* elem2;
	while((elem2 = nextElement(&iter2)) != NULL)
	{
		count++;
		Path* tmpName = (Path*)elem2;
		// tempString = malloc(sizeof(char)*size + 24);
		tempString = pathToJSON(tmpName);

		
		strcat(string, tempString);
		if(count != stop)
		{
			strcat(string, ",");
		}
		
		free(tempString);
		tempString = NULL;
	}
	
	strcat(string, "]");
	return string;
}
char* groupListToJSON(const List *list)
{
	char *string = NULL;
	char *tempString = NULL;
	int size = 0;
	if(list == NULL)
	{
		return "[]";
	}
	
	ListIterator iter = createIterator((List*)list);
	void* elem;
	while((elem = nextElement(&iter)) != NULL)
	{
		Group* tmpName = (Group*)elem;
		char *str = groupToJSON(tmpName);
		size += strlen(str);
		
		free(str);

	}
	string = malloc(sizeof(char)*size+24);
	strcpy(string, "[");
	ListIterator iter2 = createIterator((List*)list);
	int stop = getLength((List*)list);
	int count = 0;
	void* elem2;
	while((elem2 = nextElement(&iter2)) != NULL)
	{
		count++;
		Group* tmpName = (Group*)elem2;
		// tempString = malloc(sizeof(char)*size + 24);
		tempString = groupToJSON(tmpName);

		
		strcat(string, tempString);
		if(count != stop)
		{
			strcat(string, ",");
		}
		
		free(tempString);
		tempString = NULL;
	}
	
	strcat(string, "]");
	return string;
}
char* SVGtoJSON(const SVG* img)
{
	char *string = "{}";
	if(img == NULL)
	{
		return string;
	}
	string = (char*)malloc(sizeof(char)* 100);
	List *list1 = getRects(img);
	List *list2 = getCircles(img);
	List *list3 = getPaths(img);
	List *list4 = getGroups(img);

	int rectLength = getLength(list1);
	int circLength = getLength(list2);
	int pathLength = getLength(list3);
	int groupLength = getLength(list4);


	sprintf(string, "{\"numRect\":%d,\"numCirc\":%d,\"numPaths\":%d,\"numGroups\":%d}", rectLength, circLength, pathLength, groupLength);
	return string;
}

SVG* JSONtoSVG(const char* svgString)
{

	return NULL;
}
Rectangle* JSONtoRect(const char* svgString)
{
	return NULL;
}
Circle* JSONtoCircle(const char* svgString)
{
	return NULL;
}

int test(int i)
{

	return i+1;
}


char *JSONString(char *filename, char *schemafile)
{
	SVG *svg = createValidSVG(filename, schemafile);
	if(svg == NULL)
	{
		return NULL;
	}
	bool res = validateSVG(svg, schemafile);
	if(res == false)
	{
		return NULL;
	}
	char *str = SVGtoJSON(svg);
	deleteSVG(svg);

	return str;
}

char *JSONStringRect(char *filename, char *schemafile)
{
	SVG *svg = createValidSVG(filename, schemafile);
	if(svg == NULL)
	{
		return NULL;
	}
	bool res = validateSVG(svg, schemafile);
	if(res == false)
	{
		return NULL;
	}
	List *list = getRects(svg);
	char *str = rectListToJSON(list);
	freeList(list);
	deleteSVG(svg);

	return str;
}

char *JSONStringCirc(char *filename, char *schemafile)
{
	SVG *svg = createValidSVG(filename, schemafile);
	if(svg == NULL)
	{
		return NULL;
	}
	bool res = validateSVG(svg, schemafile);
	if(res == false)
	{
		return NULL;
	}
	List *list = getCircles(svg);
	char *str = circListToJSON(list);
	freeList(list);
	deleteSVG(svg);

	return str;
}

char *JSONStringPath(char *filename, char *schemafile)
{
	SVG *svg = createValidSVG(filename, schemafile);
	if(svg == NULL)
	{
		return NULL;
	}
	bool res = validateSVG(svg, schemafile);
	if(res == false)
	{
		return NULL;
	}
	List *list = getPaths(svg);
	char *str = pathListToJSON(list);
	freeList(list);
	deleteSVG(svg);

	return str;
}
char *JSONStringGroup(char *filename, char *schemafile)
{
	SVG *svg = createValidSVG(filename, schemafile);
	if(svg == NULL)
	{
		return NULL;
	}
	bool res = validateSVG(svg, schemafile);
	if(res == false)
	{
		return NULL;
	}
	List *list = getGroups(svg);
	char *str = groupListToJSON(list);
	freeList(list);
	deleteSVG(svg);
	return str;
}

char *JSONStringTandD(char *filename, char *schemafile)
{
	SVG *svg = createValidSVG(filename, schemafile);
	if(svg == NULL)
	{
		return NULL;
	}
	bool res = validateSVG(svg, schemafile);
	if(res == false)
	{
		return NULL;
	}

	int j = 0;
	
	char *desc = (char*)malloc(sizeof(char)*strlen(svg->description)+24);
	strcpy(desc, svg->description);
	

	
	for (int i = 0; i < strlen(desc); i ++) {
				if (desc[i] != '"' && desc[i] != '\\') { 
					desc[j++] = desc[i];
				} else if (desc[i+1] == '"' && desc[i] == '\\') { 
					desc[j++] = '"';
				} else if (desc[i+1] != '"' && desc[i] == '\\') { 
					desc[j++] = '\\';
				}
	}


	if(j>0)
	desc[j]=0;


	
	int size = strlen(svg->title) +  strlen(desc);
	char *string = (char*)malloc(sizeof(char)*size+24);
	sprintf(string, "{\"title\":\"%s\",\"desc\":\"%s\"}", svg->title, desc);
	free(desc);
	deleteSVG(svg);
	return string;
}

char *scaleShape(char *filename,char *schemafile, char *elemType, int elementIndex, char *value)
{
	
	SVG *svg = createValidSVG(filename, schemafile);
	if(svg == NULL)
	{
		return NULL;
	}
	bool res = validateSVG(svg, schemafile);
	if(res == false)
	{
		return NULL;
	}

	if(strcmp(elemType, "rect") == 0)
	{
		int count = 0;
		elementType elem = RECT;
		Attribute *Att = createAttribute("HI");
		int memLen = strlen("attrName")+2;
        Att->name = malloc(sizeof(char) *memLen);

		Attribute *Att2 = createAttribute("HI");
		int memLen2 = strlen("attrName")+2;
        Att2->name = malloc(sizeof(char) *memLen2);
		
		List *list = getRects(svg);
		List *list2 = getGroups(svg);
		ListIterator iter2 = createIterator(list);
		ListIterator iter3 = createIterator(list2);
		void* elem1;
		while((elem1 = nextElement(&iter3)) != NULL)
		{
			
			Group* tmpName = (Group*)elem1;
			ListIterator iter3 = createIterator(tmpName->rectangles);
			
			while((elem1 = nextElement(&iter3)) != NULL)
			{
				count++;
			}
			
			
		}
		freeList(list2);
		
		void* elem2;
		bool value1 = false;
		bool value2 = false;
		int i = 0;
		int length = getLength(list);
		length = length - count;
		while((elem2 = nextElement(&iter2)) != NULL)
		{
			Attribute *Att = createAttribute("HI");
			int memLen = strlen("attrName")+2;
			Att->name = malloc(sizeof(char) *memLen);

			Attribute *Att2 = createAttribute("HI");
			int memLen2 = strlen("attrName")+2;
			Att2->name = malloc(sizeof(char) *memLen2);
			
			Rectangle* tmpName = (Rectangle*)elem2;
			float xtemp = tmpName->width * atof(value);
			float ytemp = tmpName->height * atof(value);
			// tempString = malloc(sizeof(char)*size + 24);
			strcpy(Att->name,"width");
			char x[20];
			sprintf(x, "%f", xtemp);
			strcpy(Att->value,x);
			memset(x, 0, 20);

			strcpy(Att2->name,"height");
			char y[20];
			sprintf(y, "%f", ytemp);
			strcpy(Att2->value,y);
			memset(y, 0, 20);
			if(i < length)
			{
				value1 = setAttribute(svg, elem, i, Att);
			 	value2 = setAttribute(svg, elem, i, Att2);
			}
			 
			i++;
		}
			if(value1 == false)
			{
				// free(Att);
				// free(Att2);
				deleteSVG(svg);
				return NULL;
			}
			if(value2 == false)
			{
				// free(Att);
				// free(Att2);
				deleteSVG(svg);
				return NULL;
			}	
		bool write = writeSVG(svg, filename);
		if(write == false)
		{
			// free(Att);
			// free(Att2);
			deleteSVG(svg);
			return NULL;
		}
		freeList(list);
	}

	if(strcmp(elemType, "circ") == 0)
	{
		int count = 0;
		elementType elem = CIRC;
		Attribute *Att = createAttribute("HI");
		int memLen = strlen("attrName")+2;
        Att->name = malloc(sizeof(char) *memLen);

		List *list = getCircles(svg);
		List *list2 = getGroups(svg);
		ListIterator iter2 = createIterator(list);
		ListIterator iter3 = createIterator(list2);
		void* elem1;
		while((elem1 = nextElement(&iter3)) != NULL)
		{
			
			Group* tmpName = (Group*)elem1;
			ListIterator iter3 = createIterator(tmpName->circles);
			
			while((elem1 = nextElement(&iter3)) != NULL)
			{
				count++;
			}
			
			
		}
		
		freeList(list2);
		void* elem2;
		bool value1 = false;
		
		int i = 0;
		int length = getLength(list);
		length = length - count;
		while((elem2 = nextElement(&iter2)) != NULL)
		{
			Attribute *Att = createAttribute("HI");
			int memLen = strlen("attrName")+2;
			Att->name = malloc(sizeof(char) *memLen);

			
			Circle* tmpName = (Circle*)elem2;
			float xtemp = tmpName->r * atof(value);
			
			// tempString = malloc(sizeof(char)*size + 24);
			strcpy(Att->name,"r");
			char x[20];
			sprintf(x, "%f", xtemp);
			strcpy(Att->value,x);
			memset(x, 0, 20);

			
			if(i < length)
			{
				value1 = setAttribute(svg, elem, i, Att);
			}
			
			
			i++;
		}
			if(value1 == false)
			{
				// free(Att);
				// free(Att2);
				deleteSVG(svg);
				return "nyaheh";
			}
				
		bool write = writeSVG(svg, filename);
		if(write == false)
		{
			// free(Att);
			// free(Att2);
			deleteSVG(svg);
			return "ll";
		}
		freeList(list);
	}

deleteSVG(svg);
return "yes";
}