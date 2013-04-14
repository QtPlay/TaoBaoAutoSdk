#ifndef  TAOAPPINFO_INC
#define  TAOAPPINFO_INC

#include <TaoApiCpp/Constants.h>
#include <QUrl>
#include <QDebug>


class TaoApiInfo
{
 public:
  TaoApiInfo(QString serverUrl, QString appKey, QString appSecret,
                   QString format = Constants::FORMAT_XML,
                   QString signMethod = Constants::SIGN_METHOD_MD5,
                   int connectTimeout = 0,
                   int readTimeout = 0)
  {
    this->appKey = appKey;
    this->appSecret = appSecret;
    this->serverUrl = QUrl(serverUrl);
    if (!this->serverUrl.isValid()) {
      qDebug() << QString("Invalid Url: %1\n Error: %2")
                  .arg(this->serverUrl.toString()).arg(this->serverUrl.errorString());
      exit(1);
    }

    this->format = format;
    this->connectTimeout = connectTimeout;
    this->readTimeout = readTimeout;
    this->signMethod = signMethod;
    needCheckRequest = true;
    needEnableParser = true;
  }

  QString appKey;
  QString appSecret;
  QUrl serverUrl;
  QString format;
  QString signMethod;
  int connectTimeout;
  int readTimeout;
  bool needCheckRequest;
  bool needEnableParser;

  static TaoApiInfo *useGlobalInfo;
  const static QString APP_KEY;
  const static QString FORMAT;
  const static QString METHOD;
  const static QString TIMESTAMP;
  const static QString VERSION;
  const static QString VERSIONVALUE;
  const static QString SIGN;
  const static QString SIGN_METHOD;
  const static QString PARTNER_ID;
  const static QString SESSION;
  const static QString ACCESSTOKEN;

};

void setDefaultTaoApiInfo(TaoApiInfo *appInfo);

#endif   /* ----- #ifndef TAOAPPINFO_INC  ----- */
