#include "browserthread.h"
#include <QtDebug>
#include <QMimeDatabase>
#include "params.h"

BrowserThread::BrowserThread(QObject *parent) :
    QThread(parent)
{
    Params p;
    checkMime = p.getMime();
}

void BrowserThread::setFolder(QString d)
{
    folder = d;
}

QString BrowserThread::getFolder()
{
    return folder;
}

void BrowserThread::run()
{
    QDir dir(folder);
    QFileInfoList dedans = dir.entryInfoList(QStringList("*"),QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::NoSymLinks);
    emit numFiles(dedans.count());
    int i = 0;
    foreach(QFileInfo f,dedans)
    {

        emit nextFile(i);
        i++;
        if (f.isDir())
        {
            urls.append(browseFolder(f.absoluteFilePath()));
        }
        else
        {
            if (checkFormat(f.absoluteFilePath()))
            {
                urls.append(QUrl::fromLocalFile(f.absoluteFilePath()));
            }
        }
    }

    emit finished();
}

QList<QUrl> BrowserThread::getUrls()
{
    return urls;
}

QList<QUrl> BrowserThread::browseFolder(QString d)
{
    QList<QUrl> trouve;
    QDir dir(d);

    //d.setFilter(QDir::NoDotAndDotDot);
    QFileInfoList dedans = dir.entryInfoList(QStringList("*"),QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::NoSymLinks);


    foreach(QFileInfo f,dedans)
    {
        if (f.isDir())
        {
            trouve.append(browseFolder(f.absoluteFilePath()));
        }
        else
        {
            if (checkFormat(f.absoluteFilePath()))
            {
                trouve.append(QUrl::fromLocalFile(f.absoluteFilePath()));
            }
        }
    }
    return trouve;
}

bool BrowserThread::checkFormat(QString filePath)
{
    bool ok = false;
    //using mimetype
    if (!checkMime)
    {
        //Using filename (extension)
        QString fp = filePath.toLower();
        ok =  fp.endsWith("mp3") || fp.endsWith("wav") || fp.endsWith("aac") || fp.endsWith("wma") || fp.endsWith("m3u") || fp.endsWith("ogg") || fp.endsWith("flac")\
                || fp.endsWith("mov") || fp.endsWith("avi") || fp.endsWith("mp4") || fp.endsWith("mp2") || fp.endsWith("mpg") || fp.endsWith("mpeg") || fp.endsWith("flv") || fp.endsWith("vob") || fp.endsWith("mkv") || fp.endsWith("dv");
    }
    //using mimetype
    else
    {
        QMimeDatabase mdb;
        QString mimeName = mdb.mimeTypeForUrl(QUrl::fromLocalFile(filePath)).name();
        ok = mimeName.toLower().startsWith("video") || mimeName.toLower().startsWith("audio");
    }
    return ok;
}

