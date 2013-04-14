#include <TaoApiCpp/TaoRequest.h>
#include <TaoApiCpp/TaoResponse.h>
#include <TaoApiCpp/util/WebUtils.h>
#include <QMapIterator>
#include <QDebug>

QString TaoRequest::getResponseStr()
{
  return responseStr;
}

QString TaoRequest::getWebReply(const QString &session, const QString &accessToken)
{
  this->session = session;
  this->accessToken = accessToken;

  if (taoApiInfo == 0) {
    qDebug() << "appInfo is NULL,pls use setDefaultAppinfo or TaoRequest::setAppInfo";
    exit(1);
  }

  if (taoApiInfo->serverUrl.scheme() == "https" &&
        !accessToken.isEmpty())
    httpsSysParams();
  else
    httpSysParams();

  QMap<QString, QString> mergeMap = sysParams;
  QMapIterator<QString, QString> i(appParams);
  while (i.hasNext()) {
    i.next();
    mergeMap.insert(i.key(), i.value());
  }

  QByteArray result;

  if (fileParams.size() == 0)
    result = WebUtils::getResult(taoApiInfo, mergeMap);
  else
    result = WebUtils::getResult(taoApiInfo, mergeMap, fileParams);

  responseStr = QString::fromUtf8(result);
  return responseStr;
}

void TaoRequest::httpSysParams() {
  sysParams.clear();
  if (!session.isEmpty())
    sysParams.insert(taoApiInfo->SESSION, session);

  sysParams.insert(taoApiInfo->METHOD, getApiMethodName());
  /**
    * @brief 从UTC时间+8,确保不因用户时区为非中国时区而产生错误
    **/
  QDateTime utfZone = QDateTime::currentDateTimeUtc();
  utfZone.addSecs(60 * 60 * 8);
  sysParams.insert(taoApiInfo->TIMESTAMP, utfZone.toString(Constants::DATE_TIME_FORMAT));
  sysParams.insert(taoApiInfo->FORMAT, taoApiInfo->format);
  sysParams.insert(taoApiInfo->APP_KEY, taoApiInfo->appKey);
  sysParams.insert(taoApiInfo->VERSION, taoApiInfo->VERSIONVALUE);
  sysParams.insert(taoApiInfo->SIGN_METHOD, taoApiInfo->signMethod);
}

void TaoRequest::httpsSysParams() {
  sysParams.clear();
  sysParams.insert(taoApiInfo->METHOD, getApiMethodName());
  sysParams.insert(taoApiInfo->FORMAT, taoApiInfo->format);
  sysParams.insert(taoApiInfo->VERSION, taoApiInfo->VERSIONVALUE);
  sysParams.insert(taoApiInfo->ACCESSTOKEN, accessToken);
}
