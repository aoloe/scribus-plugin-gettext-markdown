/* Originally from PEG Markdown Highlight
 * Copyright 2011 Ali Rantakari -- http://hasseg.org
 * Licensed under the GPL2+ and MIT licenses (see LICENSE for more info).
 * 
 * mp_definitions.h
 */

#ifndef mp_MARKDOWN_DEFINITIONS
#define mp_MARKDOWN_DEFINITIONS

/** \file
* \brief Global definitions for the parser. The structure defined in here are available
*        in your code.
*/

/**
* \brief Element types.
* 
* The first (documented) ones are language element types.
* 
* The last (non-documented) ones are utility types used
* by the parser itself.
* 
* \sa pmh_element
*/
typedef enum
{
    mp_LINK,               /**< Explicit link */
    mp_AUTO_LINK_URL,      /**< Implicit URL link */
    mp_AUTO_LINK_EMAIL,    /**< Implicit email link */
    mp_IMAGE,              /**< Image definition */
    mp_CODE,               /**< Code (inline) */
    mp_HTML,               /**< HTML */
    mp_HTML_ENTITY,        /**< HTML special entity definition */
    mp_EMPH,               /**< Emphasized text */
    mp_STRONG,             /**< Strong text */
    mp_LIST_BULLET,        /**< Bullet for an unordered list item */
    mp_LIST_ENUMERATOR,    /**< Enumerator for an ordered list item */
    mp_COMMENT,            /**< (HTML) Comment */
    
    // Code assumes that pmh_H1-6 are in order.
    mp_H1,                 /**< Header, level 1 */
    mp_H2,                 /**< Header, level 2 */
    mp_H3,                 /**< Header, level 3 */
    mp_H4,                 /**< Header, level 4 */
    mp_H5,                 /**< Header, level 5 */
    mp_H6,                 /**< Header, level 6 */
    
    mp_BLOCKQUOTE,         /**< Blockquote */
    mp_VERBATIM,           /**< Verbatim (e.g. block of code) */
    mp_HTMLBLOCK,          /**< Block of HTML */
    mp_HRULE,              /**< Horizontal rule */
    mp_REFERENCE,          /**< Reference */
    mp_NOTE,               /**< Note */
     
    // Utility types used by the parser itself:
    
    // List of pmh_RAW element lists, each to be processed separately from
    // others (for each element in linked lists of this type, `children` points
    // to a linked list of pmh_RAW elements):
    mp_RAW_LIST,   /**< Internal to parser. Please ignore. */
    
    // Span marker for positions in original input to be post-processed
    // in a second parsing step:
    mp_RAW,        /**< Internal to parser. Please ignore. */
    
    // Additional text to be parsed along with spans in the original input
    // (these may be added to linked lists of pmh_RAW elements):
    mp_EXTRA_TEXT, /**< Internal to parser. Please ignore. */
    
    // Separates linked lists of pmh_RAW elements into parts to be processed
    // separate from each other:
    mp_SEPARATOR,  /**< Internal to parser. Please ignore. */
    
    // Placeholder element used while parsing:
    mp_NO_TYPE,    /**< Internal to parser. Please ignore. */
    
    // Linked list of *all* elements created while parsing:
    mp_ALL         /**< Internal to parser. Please ignore. */
} mp_element_type;

/**
* \brief A Language element occurrence.
*/
struct mp_Element
{
    mp_element_type type;    /**< \brief Type of element */
    unsigned long pos;        /**< \brief Start character offset in input */
    unsigned long end;        /**< \brief End character offset in input */
    struct mp_Element *next; /**< \brief Next element in list */
    char *label;              /**< \brief Label (for links and references) */
    char *address;            /**< \brief Address (for links and references) */
};
typedef struct mp_Element mp_element;

/**
* \brief Bitfield enumeration of supported Markdown extensions.
*/
enum mp_extensions
{
    mp_EXT_NONE    = 0,        /**< No extensions */
    mp_EXT_NOTES   = (1 << 0)  /**< A footnote syntax like that of Pandoc or
                                     PHP Markdown Extra */
};

#endif
