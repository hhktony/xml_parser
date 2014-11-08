#include "xml_parser.h"

int main(int argc, char *argv[])
{
    xmlDocPtr doc   = NULL;
	xmlChar *result = NULL;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <xmlfile>\n", argv[0]);
        return -1;
    }

    doc = xml_get_doc(argv[1]);
    if (doc == NULL) {
        xmlCleanupParser();
        return -1;
    }

    result = xml_get_value(doc, "//Format/meta/good");
    if (result == NULL)
        fprintf(stderr, "Not found\n");
    else {
        fprintf(stdout, "result = %s\n", result);
        xmlFree(result);
    }

    result = xml_get_prop(doc, "//Format", "FmtName");
    if (result == NULL)
        fprintf(stderr, "Not found\n");
    else {
        fprintf(stdout, "prop result: %s\n", result);
        xmlFree(result);
    }

    result = xml_doc_to_string(doc);
    if (result == NULL)
        fprintf(stderr, "Not fount\n");
    else {
        fprintf(stdout, "result = %s\n", result);
        xmlFree(result);
    }

    xmlFreeDoc(doc);
    xmlCleanupParser();

	return 0;
}
