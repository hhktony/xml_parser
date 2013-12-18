#include "xmlxpath.h"

int main(int argc, char *argv[])
{
    xmlDocPtr doc = NULL;
	xmlChar *result = NULL;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <xmlfile>\n", argv[0]);
        return -1;
    }

	xmlInitParser();

	xmlKeepBlanksDefault(0);

    doc = get_doc(argv[1]);

    result = xml_get_value_from_buf_by_xpath(doc, "//Format/meta/good");
    if (result == NULL)
        fprintf(stderr, "Not found\n");
    else
    {
        fprintf(stdout, "result = %s\n", result);
        xmlFree(result);
    }

    result = xml_get_prop_by_xpath(doc, "//Format", "FmtName");
    if (result == NULL)
        fprintf(stderr, "Not found\n");
    else
    {
        fprintf(stdout, "result = %s\n", result);
        xmlFree(result);
    }

    result = xml_doc_to_string(doc);
    if (result == NULL)
        fprintf(stderr, "Not fount\n");
    else
    {
        fprintf(stdout, "result = %s\n", result);
        xmlFree(result);
    }

    xmlFreeDoc(doc);
	xmlCleanupParser();

	return (0);
}
