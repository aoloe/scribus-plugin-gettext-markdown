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

// Internal language element occurrence structure, containing
// both public and private members:
struct mp_RealElement
{
    // "Public" members:
    // (these must match what's defined in pmh_definitions.h)
    // ----------------------------------------------
    mp_element_type type;
    unsigned long pos;
    unsigned long end;
    struct mp_RealElement *next;
    char *label;
    char *address;
    
    // "Private" members for use by the parser itself:
    // -----------------------------------------------
    
    // next element in list of all elements:
    struct mp_RealElement *all_elems_next;
    
    // offset to text (for elements of type pmh_EXTRA_TEXT, used when the
    // parser reads the value of 'text'):
    int text_offset;
    
    // text content (for elements of type pmh_EXTRA_TEXT):
    char *text;
    
    // children of element (for elements of type pmh_RAW_LIST)
    struct mp_RealElement *children;
};
typedef struct mp_RealElement mp_realelement;

/*
Copy `str` to `out`, while doing the following:
  - remove UTF-8 continuation bytes
  - remove possible UTF-8 BOM (byte order mark)
  - append two newlines to the end (like peg-markdown does)
  - keep track of which bytes we have stripped (in strip_positions)
Copy pasted from pmh_parser.c
*/
static int _mp_strcpy_preformat(char *str, char **out,
                            unsigned long **out_strip_positions,
                            size_t *out_strip_positions_len)
{
    size_t strip_positions_size = 1024;
    size_t strip_positions_pos = 0;
    unsigned long *strip_positions = (unsigned long *)
                                     calloc(strip_positions_size,
                                            sizeof(unsigned long));
    
    
    // +2 in the following is due to the "\n\n" suffix:
    char *new_str = (char *)malloc(sizeof(char) * strlen(str) + 1 + 2);
    char *c = str;
    int i = 0;
    
    if (HAS_UTF8_BOM(c)) {
        c += 3;
        ADD_STRIP_POS(0);
        ADD_STRIP_POS(1);
        ADD_STRIP_POS(2);
    }
    
    while (*c != '\0')
    {
        if (!IS_CONTINUATION_BYTE(*c)) {
            *(new_str+i) = *c, i++;
        } else {
            ADD_STRIP_POS((int)(c-str));
        }
        c++;
    }
    
    *(new_str+(i++)) = '\n';
    *(new_str+(i++)) = '\n';
    *(new_str+i) = '\0';
    
    *out = new_str;
    *out_strip_positions = strip_positions;
    *out_strip_positions_len = strip_positions_pos;
    return i;
}

/**
* \brief Parse Markdown text, return elements
* 
* Parses the given Markdown text and returns the results as an
* array of linked lists of elements, indexed by position.
* 
* \param[in]  text        The Markdown text to parse for highlighting.
* \param[in]  extensions  The extensions to use in parsing (a bitfield
*                         of pmh_extensions values).
* \param[out] out_result  A pmh_element array, indexed by position, containing
*                         the results of the parsing (linked lists of elements).
*                         You must pass this to pmh_free_parsed() when it's
*                         not needed anymore.
* 
* \sa pmh_element_type
*/
void mp_markdown_to_elements(char *text, int extensions,
                              mp_element **out_result[])
{
    // make a copy of text while stripping (and tracking) some utf8 information
    char *text_copy = NULL;
    unsigned long *strip_positions = NULL;
    size_t strip_positions_len = 0;
    int text_copy_len = _mp_strcpy_preformat(text, &text_copy, &strip_positions,
                                         &strip_positions_len);
    
    mp_realelement *parsing_elem = (mp_realelement *)
                                    malloc(sizeof(mp_realelement));
    parsing_elem->type = mp_RAW;
    parsing_elem->pos = 0;
    parsing_elem->end = text_copy_len;
    parsing_elem->next = NULL;
    
    parser_data *p_data = mk_parser_data(
        text,
        strip_positions,
        strip_positions_len,
        text_copy,
        parsing_elem,
        0,
        extensions,
        NULL,
        NULL
    );
    mp_realelement **result = p_data->head_elems;
    
    if (*text_copy != '\0')
    {
        // Get reference definitions into p_data->references
        parse_references(p_data);
        
        // Reset parser state to beginning of input
        p_data->offset = 0;
        p_data->current_elem = p_data->elem_head;
        
        // Parse whole document
        GREG *g = YY_NAME(parse_new)(p_data);
        YY_NAME(parse)(g);


}
