#ifndef STORE_H
#define STORE_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QVector>
#include <QString>
#include <QJsonValue>

#include "resource.h"
#include "feedmode.h"
#include "window.h"
#include "post.h"

class Store
{
  public:
    static FeedMode feed_mode;
    static QVector<Post> posts;
    static QString output_file_name;
    static void loadPosts();
};

#endif // STORE_H
