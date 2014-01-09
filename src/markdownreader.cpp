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
            // QString content = document->toPlainText();
            // QByteArray ba = content.toLatin1();
            // char *content_cstring = strdup((char *)ba.data());

            char *content_cstring = strdup((char *)rawText.data());

            QString text = QString::fromUtf8(rawText);

            mp_element **result;

            // qDebug() << "content_cstring" << content_cstring;
            mp_markdown_to_elements(content_cstring, mp_EXT_NONE, &result);

            /*
            // mp_realelement *cursor = (mp_realelement*)result[mp_ALL];
            // mp_element *cursor = result[mp_ALL];
            // mp_element *cursor = result[mp_RAW_LIST];
            QVector<mp_element> list;
            for (int i = mp_LINK; i <= mp_NOTE; i++) {
                mp_element *cursor = result[i];
                while (cursor != NULL) {
                    // mp_realelement *current = cursor;
                    // mp_element *current = cursor;
                    list.append(*cursor);
                    cursor = cursor->next;
                    qDebug() << "pos:" << current->pos;
                    QString snippet = text.mid(current->pos, current->end - current->pos);
                    qDebug() << "snippet:" << snippet;
                }
            }
            // TODO: sort by pos!
            // qDebug() << "list:" << list;
            foreach (mp_element item, list)
            {
                qDebug() << "----";
                qDebug() << "type:" << item.type;
                qDebug() << "pos:" << item.pos;
                qDebug() << "end:" << item.end;
                qDebug() << "text:" << text.mid(item.pos, item.end - item.pos);
            }
            */

            qDebug() << result;

            /*
            if (result != NULL)
                mp_free_elements(result);
            free(content_cstring);
            */
        }
    }
}
