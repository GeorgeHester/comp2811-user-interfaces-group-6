#ifndef RESOURCE_H
#define RESOURCE_H

#include <QFile>
#include <QString>
#include <QDebug>
#include <QTextStream>

class Resource
{
  public:
    static void import(QString id)
    {
        QFile file(id);

        if (!file.open(QIODevice::ReadOnly))
            qDebug() << "Failed to import resource file" << id;
    };

    static QString load(QString id)
    {
        QFile file(id);

        if (!file.open(QFile::ReadOnly | QFile::Text))
            qDebug() << "Failed to load resource file" << id;

        QTextStream text_stream(&file);

        return text_stream.readAll();
    };
};

#endif // RESOURCE_H
