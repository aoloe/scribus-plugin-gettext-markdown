# scribus-plugin-gettext-markdown

Text importer for loading simple Markdown text into Scribus files.

It must at least support:
- headings
- italics
- bold
- lists
- rendering links in a printer friendly way
- blockquotes as intended paragraph

All information concerning this plugin's code is in `src/README.md`.

## Install

Clone the `scribus-plugin-gettext-markdown` repository and put – or symlink – the `src` directory into `scribus/plugins/gettext/` as `markdown`. Then add 

    ADD_SUBDIRECTORY(markdown)

to `CMakeList` file in `scribus/plugins/gettext/`.

## Specifications

This specification follows the structure of (John Gruber's Markdown Syntax](http://daringfireball.net/projects/markdown/syntax) specification.

### Overview

#### Philosophy

For a first step we will try to implement the minimal feature set that allows to meaningfully use Markdown for a redaction system in a workflow that uses (also) Scribus.

The plugin will be for the 1.5.0svn version of Scribus.

If they don't exist we will create "standard" styles. In the future we could define a per document (or per frame) way to match to existing styles.

#### Inline HTML

HTML tags will be ignored for now.

In the future, only tags that are clearly useful in a Scribus related workflow will be considered.

#### Automatic escaping for special characters

Named escaped characters will be converted to the correct caracter.

- &amp;amp; → &amp;
- &amp;lt; → &lt;
- &amp;gt; → &gt;

###Block Elements

#### Paragraphs and Line Breaks

Paragraph are separated by consecutive empty lines

Line break is supported with two spaces at the end of the line (we will need two paragraph styles, one for the first paragraph and one for the following ones)

#### Headers

We support the use of "#" to mark headers, up to 6 levels

#### Blockquotes

Paragraphs starting with a "&gt;" are marked as blockquote and indented (by using a specific paragraph style).

In a first version, blocquote cannot contain other paragraph formatting (headings, ...)

#### Lists

We want to support the following formats for lists:

    * Red
    * Green
    * Blue
    
    - Red
    - Green
    - Blue

    1. Red
    2. Green
    3. Blue

For numerated lists, the number is ignored and a counter is used instead.

#### Code Blocks

Paragraphs intended by at least four spaces or one tab are considered code blocks (using a specific paragraph style).

#### Horizontal Rules

Ignored.

### Span Elements

#### Links

Links written as `[This link](http://example.net)` will be converted to `This link (example.net)`.

No "real" link is created as long Scribus does not "really" support them.

#### Emphasis

Single asterisks and underscores produce italics (emphasis) and double asterisks or underscores bold (strong).

Litteral asterisks and underscore must be prefixed by a backslash.

#### Code

The forward quote starts a character "code block".

#### Images

Images are ignore for now.

### Miscellaneous

#### Automatic Links

Automatic links are reformatted by removing the starting and end sign (&lt;, &gt;).

#### Backslash Escapes

We will support the markdown escaping.


## Interesting reads

- Hacker News discussion about [A Formal Spec for GitHub Flavored Markdown](https://news.ycombinator.com/item?id=13869484)
