/**
 *  Filename: xml_parser.c
 *   Created: 2014-11-08 14:21:54
 *      Desc: xml parser
 *    Author: xutao(Tony Xu), butbueatiful@gmail.com
 *   Company: myself
 */

#include "xml_parser.h"

xmlDocPtr xml_get_doc(const char *docname)
{
    xmlDocPtr doc;

    if (!docname)
        return NULL;

    xmlKeepBlanksDefault(XML_DEL_SPACE);
	doc = xmlParseFile(docname);
	if (!doc) {
		fprintf(stderr, "Document parsed failed.\n");
		return NULL;
	}

	return doc;
}

/* This is template function that can be used to parse entire XML */
void xml_list_element_names(xmlNode * a_node)
{
	xmlNode *cur_node = NULL;

	for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
		if (cur_node->type == XML_ELEMENT_NODE)
			printf("node type: Element, name: %s\n", cur_node->name);

		xml_list_element_names(cur_node->children);
	}
}

xmlXPathObjectPtr xml_get_nodeset(xmlDocPtr doc, xmlChar *xpath)
{
	xmlXPathContextPtr context;
	xmlXPathObjectPtr result;

	context = xmlXPathNewContext(doc);
	if (context == NULL) {
		fprintf(stderr, "Error in xmlXPathNewContext\n");
		return NULL;
	}

	result = xmlXPathEvalExpression(xpath, context);
	xmlXPathFreeContext(context);

    if (XPATH_NODESET != result->type)
        return NULL;

	if (result == NULL)
		return NULL;

	if (xmlXPathNodeSetIsEmpty(result->nodesetval)) {
        xmlXPathFreeObject(result); /* No result */
		return NULL;
	}

	return result;
}

/**
 * @brief xml_get_value
 *
 * @param doc
 * @param nodepath
 *
 * @return On success the value of specific node is returned.
 *         On error, NULL is returned.
 */
xmlChar *xml_get_value(xmlDocPtr doc, const char *nodepath)
{
    int32_t i;
	xmlChar *xpath = (xmlChar *) nodepath;
	xmlNodeSetPtr nodeset;
	xmlXPathObjectPtr result;
	xmlChar *keyword = NULL;

    if (doc == NULL || nodepath == NULL)
        return NULL;

	result = xml_get_nodeset(doc, xpath);
	if (result) {
		nodeset = result->nodesetval;

		for (i = 0; i < nodeset->nodeNr; i++) {
			keyword = xmlNodeListGetString(doc, nodeset->nodeTab[i]->xmlChildrenNode, 1);
			break;
		}

		xmlXPathFreeObject(result);
	}

	return keyword;
}

/**
 * @brief xml_get_prop
 *
 * @param doc
 * @param nodepath
 * @param propname
 *
 * @return On success the specific property of selected node.
 *         On error, NULL is returned.
 */
xmlChar *xml_get_prop(xmlDocPtr doc, const char *nodepath, const char *propname)
{
    int32_t i;
	xmlChar *xpath = (xmlChar *) nodepath;
	xmlNodeSetPtr nodeset;
	xmlXPathObjectPtr result;
	xmlChar *keyword = NULL;

	result = xml_get_nodeset(doc, xpath);
	if (result) {
		nodeset = result->nodesetval;
		for (i = 0; i < nodeset->nodeNr; i++) {
			keyword = xmlGetProp(nodeset->nodeTab[i], (xmlChar *) propname);
			break;
		}
		xmlXPathFreeObject(result);
	}

	return keyword;
}

void xml_create_new_file(const char *filename, const char *root_name)
{
	xmlDocPtr doc = NULL;		/* document pointer */
	xmlNodePtr root_node = NULL;

	doc = xmlNewDoc(BAD_CAST "1.0");
	root_node = xmlNewNode(NULL, BAD_CAST root_name);
	xmlDocSetRootElement(doc, root_node);
	xmlSaveFormatFileEnc(filename, doc, "UTF-8", 1);
	xmlFreeDoc(doc);
}

void xml_add_child_with_properties(char *filename, char *node_name, char *node_val)
{
	xmlDocPtr doc = NULL;		/* document pointer */
	xmlNodePtr root_node = NULL, node_child = NULL;

	doc = xml_get_doc(filename);
	root_node = xmlDocGetRootElement(doc);
	xmlDocSetRootElement(doc, root_node);
	node_child = xmlNewChild(root_node, NULL, BAD_CAST node_name, BAD_CAST node_val);
	xmlNewProp(node_child, BAD_CAST "start", BAD_CAST "1");
	xmlAddChild(root_node, node_child);
	xmlSaveFormatFileEnc(filename, doc, "UTF-8", 1);
	xmlFreeDoc(doc);
}

void xml_add_properties(char *filename, char *node_path, char *prop_name, char *prop_val)
{
    int32_t i;
	xmlDocPtr doc;
	xmlChar *xpath = (xmlChar *) node_path;
	xmlNodeSetPtr nodeset;
	xmlXPathObjectPtr result;

	doc = xml_get_doc(filename);
	result = xml_get_nodeset(doc, xpath);
	if (result) {
		nodeset = result->nodesetval;
		for (i = 0; i < nodeset->nodeNr; i++) {
			xmlNewProp(nodeset->nodeTab[i], BAD_CAST prop_name, BAD_CAST prop_val);
			xmlSaveFormatFileEnc(filename, doc, "UTF-8", 1);
		}

		xmlXPathFreeObject(result);
	}

	xmlFreeDoc(doc);

	return;
}

void xml_edit_properties(char *filename, char *node_path, char *prop_name,
					char *new_prop_val)
{
    int32_t i;
	xmlDocPtr doc;
	xmlChar *xpath = (xmlChar *) node_path;
	xmlNodeSetPtr nodeset;
	xmlXPathObjectPtr result;

	doc = xml_get_doc(filename);
	result = xml_get_nodeset(doc, xpath);
	if (result) {
		nodeset = result->nodesetval;
		for (i = 0; i < nodeset->nodeNr; i++) {
			xmlSetProp(nodeset->nodeTab[i], BAD_CAST prop_name, BAD_CAST new_prop_val);
			xmlSaveFormatFileEnc(filename, doc, "UTF-8", 1);
		}
		xmlXPathFreeObject(result);
	}
	xmlFreeDoc(doc);

	return;
}

void xml_edit_key(const char *filename, const char *node_path, const char *new_val)
{
    int32_t i;
	xmlDocPtr doc;
	xmlChar *xpath = (xmlChar *) node_path;
	xmlNodeSetPtr nodeset;
	xmlXPathObjectPtr result;

	doc = xml_get_doc(filename);
	result = xml_get_nodeset(doc, xpath);
	if (result) {
		nodeset = result->nodesetval;
		for (i = 0; i < nodeset->nodeNr; i++){
			xmlNodeSetContent(nodeset->nodeTab[i], BAD_CAST(xmlChar *) new_val);
			xmlSaveFormatFileEnc(filename, doc, "UTF-8", 1);
		}
		xmlXPathFreeObject(result);
	}
	xmlFreeDoc(doc);
}

void xml_add_child(char *filename, char *node_name, char *node_val)
{
	xmlDocPtr doc = NULL;		/* document pointer */
	xmlNodePtr root_node = NULL, node_child = NULL;

	doc = xml_get_doc(filename);
	root_node = xmlDocGetRootElement(doc);
	xmlDocSetRootElement(doc, root_node);
	node_child = xmlNewChild(root_node, NULL, BAD_CAST node_name, BAD_CAST node_val);

	//xmlNewProp(node_child, BAD_CAST "start", BAD_CAST "1");
	xmlAddChild(root_node, node_child);
	xmlSaveFormatFileEnc(filename, doc, "UTF-8", 1);
	xmlFreeDoc(doc);
}

void xml_list_all_key(xmlDocPtr doc)
{
	xmlNodePtr cur;
	xmlChar *key;

    /* Document not parsed successfully */
	if (!doc)
		return;

    /* Check the document is of the right kind */
	cur = xmlDocGetRootElement(doc);
	if (cur == NULL) {
		xmlFreeDoc(doc);
		return;
	}

    /* Go deeper */
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		if (key) {
			puts((char *) key);
			xmlFree(key);
		}
		cur = cur->next;
    }

    return;
}

/* Checks XML integrity */
int32_t xml_verify_file(const char *filename)
{
	xmlDocPtr doc;
	xmlNodePtr cur;
	doc = xmlParseFile(filename);

    /* Document not parsed successfully */
	if (doc == NULL) {
		return (1);
	}

    /* Check the document is of the right kind */
	cur = xmlDocGetRootElement(doc);
	if (cur == NULL) {
		xmlFreeDoc(doc);
		return (2);
	}
	xmlFreeDoc(doc);

	return 0;
}

int32_t xml_remove_node_and_childs(const char *filename, char *nodepath)
{
    int32_t i;
	xmlDocPtr doc;
	xmlChar *xpath = (xmlChar *) nodepath;
	xmlNodeSetPtr nodeset;
	xmlXPathObjectPtr result;

	doc = xml_get_doc(filename);
	result = xml_get_nodeset(doc, xpath);
	if (result == NULL) {
		xmlFreeDoc(doc);
		return (1);
	}

	nodeset = result->nodesetval;
	for (i = 0; i < nodeset->nodeNr; i++) {
		xmlNodePtr child = nodeset->nodeTab[i]->xmlChildrenNode;
		while (child != NULL) {
			xmlUnlinkNode(child);
			xmlFreeNode(child);
			child = nodeset->nodeTab[i]->xmlChildrenNode;
		}
		xmlUnlinkNode(nodeset->nodeTab[i]);
		xmlFreeNode(nodeset->nodeTab[i]);
	}

	xmlXPathFreeObject(result);
	xmlSaveFormatFileEnc(filename, doc, "UTF-8", 1);
	xmlFreeDoc(doc);

	return (0);
}

xmlChar *xml_doc_to_string(xmlDocPtr doc)
{
	xmlChar *s;
	int32_t size;

	xmlDocDumpMemory(doc, &s, &size);
	if (s == NULL) {
		return NULL;
	}

    return (s);
}
