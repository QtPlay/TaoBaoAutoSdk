#include <TaoApiCpp/util/FileItem.h>


FileItem::FileItem(QFile *file)
{
  this->file = file;
}

FileItem::FileItem(const QString &fileAbsolutePath)
{
  file = new QFile(fileAbsolutePath);
}

FileItem::FileItem(const QString &fileNameArg, const QByteArray &contentArg)
{
  fileName = fileNameArg;
  content = contentArg;
  file = 0;
}

FileItem::FileItem(const QString &fileNameArg, const QByteArray &contentArg, const QString &mimeArg)
{
  file = 0;
  fileName = fileNameArg;
  content = contentArg;
  mimeType = mimeArg;
}

QString FileItem::getMimeType()
{
  if (mimeType.isEmpty()) {
    getContent();

    const char *contentData = content.constData();
    if (content.size() < 10)
      mimeType = "application/octet-stream";
    else if (qstrncmp("GIF", contentData, 3))
      mimeType = "image/gif";
    else if (qstrncmp("PNG", contentData + 1, 3))
      mimeType = "image/png";
    else if (qstrncmp("JFIF", contentData + 6, 4))
      mimeType = "image/jpeg";
    else if (qstrncmp("BM", contentData, 2))
      mimeType = "image/bmp";
  }
  return mimeType;
}

QByteArray FileItem::getContent()
{
  if (content.isEmpty() && file != 0 && file->exists() && file->isReadable()) {
    content = file->readAll();
  }
  return content;
}
