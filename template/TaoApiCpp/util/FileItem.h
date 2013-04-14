#ifndef FILEITEM_H
#define FILEITEM_H

#include <QString>
#include <QByteArray>
#include <QFile>

class FileItem
{
  public:
  FileItem(QFile *file);

  //基于文件绝对路径的构造器
  FileItem(const QString &fileAbsolutePath);

  //基于文件名和字节流的构造器。
  FileItem(const QString &fileNameArg, const QByteArray &contentArg);

  //基于文件名、字节流和媒体类型的构造器。
  FileItem(const QString &fileNameArg, const QByteArray &contentArg, const QString &mimeArg);

  QString getFileName() {
    return fileName;
  }

  QString getMimeType();
  QByteArray getContent();

  private:
  QString fileName;
  QString mimeType;
  QByteArray content;
  QFile *file;
};

#endif // FILEITEM_H
