#ifndef  HASHMD5_INC
#define  HASHMD5_INC

#include <QString>
#include <QCryptographicHash>

QString md5_q(const QString &key);
QString hmacMd5_q(const QString &key, const QString &message);

#endif   /* ----- #ifndef HASHMD5_INC  ----- */
