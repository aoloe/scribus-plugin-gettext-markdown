/**
 * Parse a markdown file identified by filename and write the result into writer
 *
 * Possible paragraph styles:
 * - Heading 1
 * - Heading 2
 * - Heading 3
 * - Heading 4
 * - Heading 5
 * - Heading 6
 * - Preformatted
 * - Blockquote
 * - List
 * - List 2
 * - List 3
 * Possible character styles:
 * - Italics
 * - Bold
 * - Preformatted
 * Notes:
 * - Styles are craeted only if they are needed.
 * - There should be a way to define which logical style matches which physical style
 *   (preferences? document settings?)
 * - What happens witha <pre> in a <li>?
 * - Do we need a difference between <ul> and <ol>
 */
#include <QString>
#include <QByteArray>
#include <QTextCodec> 
#include <QVector> 
#include <QDebug>

#include "markdownreader.h"
#include "util.h" // for loadRawText

#include "plugins/gettext/htmlim/htmlreader.h"

// TODO: check which of these three are really needed
#include "scribusstructs.h"
#include "gtparagraphstyle.h" // Style for paragraph based formatting.
#include "gtframestyle.h"

MarkdownReader::MarkdownReader(gtWriter *writer, QString encoding, bool textOnly)
{
    this->writer = writer;
    this->encoding = encoding;
    this->textOnly = textOnly;
}

MarkdownReader::~MarkdownReader()
{
}

void MarkdownReader::parse(QString filename)
{
    QString text;
    QByteArray rawText;
    QTextCodec *codec;
    if (loadRawText(filename, rawText))
    {
        if (textOnly)
        {
            // TODO: not correct: if textOnly it should also parse but only retain the text and not the formatting
            if (encoding.isEmpty())
            {
                codec = QTextCodec::codecForLocale();
            }
            else
            {
                codec = QTextCodec::codecForName(encoding.toLocal8Bit());
            }
            text = codec->toUnicode(rawText);
            writer->appendUnstyled(text);
        } else {
            if (encoding.isEmpty())
            {
                codec = QTextCodec::codecForLocale();
            }
            else
            {
                codec = QTextCodec::codecForName(encoding.toLocal8Bit());
            }
            text = codec->toUnicode(rawText);

			// TODO: use cpp-markdown to convert from md to html

            text = "<html>\n <body>\n <h1>A test</h1>\n <p>My test with <i>some italics</i> and <b>some bold</b>.</p>\n </body>\n </html>";

            gtFrameStyle *fstyle = writer->getDefaultStyle();
            gtParagraphStyle *pstyle = new gtParagraphStyle(*fstyle);
            pstyle->setName("HTML_default");

            HTMLReader* handler = new HTMLReader(pstyle, writer, textOnly);
            handler->parseString(text);
            delete handler;


        }
    }
}
