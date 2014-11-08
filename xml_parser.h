/**
 *  Filename: xml_parser.h
 *   Created: 2014-11-08 14:22:22
 *      Desc: 
 *    Author: xutao(Tony Xu), butbueatiful@gmail.com
 *   Company: myself
 */
#ifndef XML_PARSER_H
#define XML_PARSER_H

#include <stdio.h>
#include <assert.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdint.h>
#include <libxml/encoding.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

#define XML_DEL_SPACE 0

// void xmlerror(void *ctx, const char *msg, ...);
xmlDocPtr xml_get_doc(const char *docname);
xmlChar *xml_get_prop(xmlDocPtr doc, const char *nodepath, const char *propname);
xmlChar *xml_get_value(xmlDocPtr doc, const char *nodepath);
void xml_edit_properties(char *filename, char *node_path, char *prop_name,
						 char *new_prop_val);
void xml_create_new_file(const char *filename, const char *root_name);
int xml_verify_file(const char *filename);
void xml_add_child(char *filename, char *node_name, char *node_val);
void xml_edit_key(const char *filename, const char *node_path, const char *new_val);
int xml_remove_node_and_childs(const char *filename, char *nodepath);
xmlChar *xml_doc_to_string(xmlDocPtr doc);
void xml_list_all_key(xmlDocPtr doc);

#endif /* end of include guard: XML_PARSER_H */
