#include <QObject>
#include <QByteArray>
#include <QFile>
#include <QFileInfo>
#include <QString>
#include <QStringList>
#include <QTextCodec> 

#include "markdown.h"
#include "markdownreader.h"
#include "scribusstructs.h"
#include "util.h"

QString FileFormatName()
{
    return QObject::tr("Markdown Files");
}

QStringList FileExtensions()
{
    return QStringList("md");
}

void GetText(QString filename, QString encoding, bool textOnly, gtWriter *writer)
{
	MarkdownGetText* markdownGetText = new MarkdownGetText(filename, encoding, textOnly, writer);
	delete markdownGetText;
}

MarkdownGetText::MarkdownGetText(const QString filename, const QString encoding, bool textOnly, gtWriter *writer)
{
	this->filename = filename;
	this->encoding = encoding;
	this->writer = writer;
	this->textOnly = textOnly;
	loadText();
}

void MarkdownGetText::write()
{
}

void MarkdownGetText::loadText()
{
    MarkdownReader* handler = new MarkdownReader(writer, encoding, textOnly);
    handler->parse(filename);
    delete handler;
}

MarkdownGetText::~MarkdownGetText()
{

}
