#include "store.h"

QVector<Post> Store::posts;
FeedMode Store::feed_mode = FeedMode::PrePost;
QString Store::temporary_file_name;

void
Store::loadPosts()
{
    Store::posts.clear();

    // Load in the input data file
    QString json = Resource::load(QString(":/data/input"));

    // Read the file contents to a document
    QJsonDocument document = QJsonDocument::fromJson(json.toUtf8());

    if (document.isNull()) return;

    QJsonObject root_object = document.object();
    QJsonArray posts_array = root_object["posts"].toArray();

    for (QJsonValue post_value : posts_array)
    {
        qDebug() << "POST READ";

        QJsonObject post_object = post_value.toObject();

        QString username = post_object["username"].toString();
        QString post_url = post_object["post_url"].toString();
        QString post_time = post_object["post_time"].toString();
        QString post_caption = post_object["post_caption"].toString();

        Post post;
        post.username = username;
        post.post_url = post_url;
        post.post_time = post_time;
        post.post_caption = post_caption;

        Store::posts.append(post);
    };
};
