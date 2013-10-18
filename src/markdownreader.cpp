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
#include "markdownreader.h"
#include "util.h" // for loadRawText

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
    }
}
