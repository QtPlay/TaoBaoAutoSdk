#ifndef WEBUTILS_H
#define WEBUTILS_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QMap>
#include <QUrl>
#include <TaoApiCpp/util/FileItem.h>
#include <TaoApiCpp/TaoApiInfo.h>

class WebUtils : public QObject
{
  Q_OBJECT
public:
  explicit WebUtils(QObject *parent = 0);

  static QByteArray getResult(const TaoApiInfo *appInfo, const QMap<QString, QString> &urlMap);
  static QByteArray getResult(const TaoApiInfo *appInfo, const QMap<QString, QString> &urlMap,
                           const QMap<QString, FileItem> &tmpFiles);
  static QString signHttp(const TaoApiInfo *appInfo, const QMap<QString, QString> &urlMap);

  static QByteArray getByUrl(const QString &urlStr);
  static QByteArray getByUrl(const QUrl &url);
  static QByteArray postByUrl(const QString &urlStr,
                           const QMap<QString, QString> &sysAndAppParams,
                           const QMap<QString, FileItem> &tmpFiles);
  static QByteArray postByUrl(const QUrl &url,
                           const QMap<QString, QString> &sysAndAppParams,
                           const QMap<QString, FileItem> &tmpFiles);
private:
  static QNetworkAccessManager qnam;
};

#endif // WEBUTILS_H
