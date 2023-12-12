#ifndef POST_H
#define POST_H

#include <QFrame>
#include <QVideoWidget>

typedef struct PostUi
{
    QFrame* frame;
    QVideoWidget* video_widget;
} PostUi;

typedef struct PostBlank
{
    QFrame* frame;
} PostBlank;

typedef struct Post
{
    QString username;
    QString post_url;
    QString post_time;
} Post;

#endif // POST_H