/** \file
* \brief Markdown parser's public interface.
*/

#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifndef __cplusplus
#include <stdbool.h>
#endif

#include <stdlib.h>
#include <assert.h>
#include "mp_definitions.h"

/**
* \brief Parse Markdown text, return elements
* 
* Parses the given Markdown text and returns the results as an
* array of linked lists of elements, indexed by type.
* 
* \param[in]  text        The Markdown text to parse for highlighting.
* \param[in]  extensions  The extensions to use in parsing (a bitfield
*                         of pmh_extensions values).
* \param[out] out_result  A pmh_element array, indexed by type, containing
*                         the results of the parsing (linked lists of elements).
*                         You must pass this to pmh_free_elements() when it's
*                         not needed anymore.
* 
* \sa pmh_element_type
*/
void mp_markdown_to_elements(char *text, int extensions,
                              mp_element **out_result[]);

