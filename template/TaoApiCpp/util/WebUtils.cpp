#include <TaoApiCpp/util/HashMd5.h>
#include <TaoApiCpp/util/WebUtils.h>
#include <QMapIterator>
#include <QNetworkRequest>
#include <QHttpMultiPart>
#include <QHttpPart>
#include <QEventLoop>
#include <QNetworkReply>
#include <QDebug>


QNetworkAccessManager WebUtils::qnam;

WebUtils::WebUtils(QObject *parent) :
  QObject(parent)
{
}

QByteArray WebUtils::getByUrl(const QString &urlStr)
{
  return getByUrl(QUrl(urlStr));
}

/**
 * @brief 通过HTTP GET发送URL，因为QNetWorkAccessManager默认不CACHE，所以不必设置
 **/
QByteArray WebUtils::getByUrl(const QUrl &url)
{
  QNetworkReply *reply = qnam.get(QNetworkRequest(url));
  QEventLoop loop;
  connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
  loop.exec();

  QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

  // WARNING: taobao only have once redirect url
  if (reply->error()) {
    qDebug() << reply->errorString();
    return "";
  } else if (!redirectionTarget.isNull()) {
    QUrl newUrl = url.resolved(redirectionTarget.toUrl());
    reply->deleteLater();
    return getByUrl(newUrl);
  }

  QByteArray returnStr = reply->readAll();
  reply->deleteLater();
  return returnStr;
}

QByteArray WebUtils::postByUrl(const QUrl &url,
                            const QMap<QString, QString> &sysAndAppParams,
                            const QMap<QString, FileItem> &tmpFiles)
{
  QHttpMultiPart multiParts(QHttpMultiPart::FormDataType);

  QMapIterator<QString, QString> appParamIter(sysAndAppParams);
  while (appParamIter.hasNext()) {
    appParamIter.next();
    QHttpPart appParamPart;
    appParamPart.setHeader(QNetworkRequest::ContentTypeHeader,
                           QVariant("text/plain; charset = UTF-8"));
    appParamPart.setHeader(QNetworkRequest::ContentDispositionHeader,
                           QVariant("form-data; name =" + appParamIter.key().toUtf8()));
    appParamPart.setBody(appParamIter.value().toUtf8());
    multiParts.append(appParamPart);
  }


  QMapIterator<QString, FileItem> i(tmpFiles);
  while (i.hasNext()) {
    i.next();
    FileItem fileItem = i.value();
    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant(fileItem.getMimeType()));
    QString disposition = QString("form-data; name = %1; filename = %2")
        .arg(i.key()).arg(fileItem.getFileName());
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(disposition));
    filePart.setBody(fileItem.getContent());
    multiParts.append(filePart);
  }

  QNetworkReply *reply = qnam.post(QNetworkRequest(url), &multiParts);
  QEventLoop loop;
  connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
  loop.exec();

  QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

  if (reply->error()) {
    qDebug() << reply->errorString();
    return reply->errorString().toUtf8();
  } else if (!redirectionTarget.isNull()) {
    QUrl newUrl = url.resolved(redirectionTarget.toUrl());
    reply->deleteLater();
    return postByUrl(newUrl, sysAndAppParams, tmpFiles);
  }

  QByteArray returnStr = reply->readAll();
  reply->deleteLater();
  return returnStr;
}

QString WebUtils::signHttp(const TaoApiInfo *appInfo, const QMap<QString, QString> &urlMap)
{
  QString signParams;
  QString urlSuffix;

  QMap<QString, QString>::const_iterator i;
  for (i = urlMap.constBegin(); i != urlMap.constEnd(); ++i) {
    if (!i.key().isEmpty() && !i.value().isEmpty()) {
      signParams += i.key();
      signParams += i.value();
      urlSuffix+= QString("&%1=%2").arg(i.key(),i.value());
    }
  }

  QString signStr;
  if (appInfo->signMethod == Constants::SIGN_METHOD_MD5) {
    signParams += appInfo->appSecret;
    signParams.prepend(appInfo->appSecret);
    signStr = md5_q(signParams);
  } else if (appInfo->signMethod == Constants::SIGN_METHOD_HMAC) {
    signStr = hmacMd5_q(signParams, appInfo->appSecret);
  } else
    Q_ASSERT(!"signMethod is wrong");

  signStr.prepend("sign=");
  return appInfo->serverUrl.toString() + "?" + signStr + urlSuffix;
}

QByteArray WebUtils::getResult(const TaoApiInfo *appInfo, const QMap<QString, QString> &urlMap)
{
  QString url = signHttp(appInfo, urlMap);
  return getByUrl(url);
}

QByteArray WebUtils::getResult(const TaoApiInfo *appInfo, const QMap<QString, QString> &urlMap,
                            const QMap<QString, FileItem> &tmpFiles)
{
  QString url = signHttp(appInfo, urlMap);
  return postByUrl(url, urlMap, tmpFiles);
}

QByteArray WebUtils::postByUrl(const QString &urlStr,
                            const QMap<QString, QString> &sysAndAppParams,
                            const QMap<QString, FileItem> &tmpFiles)
{
  return postByUrl(QUrl(urlStr), sysAndAppParams, tmpFiles);
}
