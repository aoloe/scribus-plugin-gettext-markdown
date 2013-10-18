/**
 * Load a markdown file into the current Scribus text frame
 */
#ifndef MARKDOWNREADER_H
#define MARKDOWNREADER_H

#include <gtwriter.h>

class MarkdownReader
{
public:
	MarkdownReader(gtWriter *w, QString encoding, bool textOnly);
	~MarkdownReader();
private:
	gtWriter *writer;
	QString encoding;
	bool textOnly;
public:
	void parse(QString filename);
};

#endif
