/**
 * @file   global.h
 * @Author Lavrentiy Ivanov (ookami@mail.ru)
 * @date   August, 2013
 * @brief  Brief description of file.
 *
 * Detailed description of file.
 */

#ifndef XMLXPATH_H
#define XMLXPATH_H
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

void xmlerror(void *ctx, const char *msg, ...);
void xml_edit_properties(char *filename, char *node_path, char *prop_name,
						 char *new_prop_val);
void xml_create_new_file(const char *filename, const char *root_name);
int xml_verify_file(const char *filename);
void xml_add_child(char *filename, char *node_name, char *node_val);
xmlChar *xml_get_value_from_buf_by_xpath(xmlDocPtr doc, const char *nodepath);
xmlChar *xml_get_prop_by_xpath(xmlDocPtr doc, const char *nodepath, const char *propname);
void xml_edit_key(const char *filename, const char *node_path, const char *new_val);
int xml_remove_node_and_childs(const char *filename, char *nodepath);
xmlDocPtr get_doc(const char *docname);
xmlChar *xml_doc_to_string(xmlDocPtr doc);
void xml_list_all_key(xmlDocPtr doc);

#endif
