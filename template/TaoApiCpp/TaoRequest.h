#ifndef  TAOREQUEST_INC
#define  TAOREQUEST_INC

#include <QString>
#include <QMap>
#include <QDateTime>
#include <QList>

#include <TaoApiCpp/Constants.h>
#include <TaoApiCpp/TaoApiInfo.h>
#include <TaoApiCpp/util/FileItem.h>

class TaoResponse;

/**
 * @brief Api请求基类。
 *
 * @todo 暂时没有对Required参数的检测机制，以后再加入。需要注意的是，Sdk自动生成器同样需要因此而改动。
 * @todo 对于生成URL以及调用网络有些耦合，以后再重构。
 **/
class TaoRequest
{
public:
  TaoRequest() {
    taoApiInfo = TaoApiInfo::useGlobalInfo;
  }

  void setAppInfo(TaoApiInfo *appInfo)
  {
    this->taoApiInfo = appInfo;
  }

  virtual QString getApiMethodName() const = 0;

  /**
   * @brief 发送请求，返回Reponse派生类。
   *
   * @param session ... 默认为空。用于获取用户隐私数据。只有获得用户授权，才可得到session。
   * @param accessToken ... 默认为空。accessToken只用于https免签调用，需要SDK使用者OAUTH2.0获取。
   * 调用方式： getResponse("", "accesstokenValue")
   **/
  virtual TaoResponse *getResponseClass(const QString &session = "",
                                   const QString &accessToken = "") = 0;

  /**
   * @brief get ResponseStr
   * @note only can be used after getResponseClass();
   */
  QString getResponseStr();

  QString getWebReply(const QString &session = "", const QString &accessToken = "");

  /**
   * @brief 获取当前的用户级调用参数配对
   *
   * @return QMap< QString, QString >
   **/
  QMap<QString, QString> getAppParams() const
  {
    return appParams;
  }

  /**
   * @brief 获取当前的文件参数配对
   *
   * @return QMap< QString, FileItem >
   **/
  QMap<QString, FileItem> getFileParams() const
  {
    return fileParams;
  }

  /**
   * @brief 加入其他键值配对，key与value不可以为空字符串
   */
  void putOtherTextParam(const QString &key, const QString &value) {
    if (key.isEmpty() || value.isEmpty())
      return;
    appParams.insert(key, value);
  }

protected:
  /**
   * @brief 除签名SIGN外，组装http系统参数
   **/
  void httpSysParams();

  /**
   * @brief 组装https系统参数
   **/
  void httpsSysParams();

  TaoApiInfo *taoApiInfo;
  QString session;
  QString accessToken;
  QMap<QString, QString> sysParams;
  QMap<QString, QString> appParams;
  QMap<QString, FileItem> fileParams;

  QString responseStr;
};

#endif   /* ----- #ifndef TAOREQUEST_INC  ----- */
