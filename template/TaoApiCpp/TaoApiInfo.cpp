#include <TaoApiCpp/TaoApiInfo.h>

const QString TaoApiInfo::APP_KEY = "app_key";
const QString TaoApiInfo::FORMAT = "format";
const QString TaoApiInfo::METHOD = "method";
const QString TaoApiInfo::TIMESTAMP = "timestamp";
const QString TaoApiInfo::VERSION = "v";
const QString TaoApiInfo::VERSIONVALUE = "2.0";
const QString TaoApiInfo::SIGN = "sign";
const QString TaoApiInfo::SIGN_METHOD = "sign_method";
const QString TaoApiInfo::PARTNER_ID = "partner_id";
const QString TaoApiInfo::SESSION = "session";
const QString TaoApiInfo::ACCESSTOKEN = "access_token";

TaoApiInfo *TaoApiInfo::useGlobalInfo = 0;

void setDefaultTaoApiInfo(TaoApiInfo* appInfo)
{
  if (appInfo == 0)
    return;

  TaoApiInfo::useGlobalInfo = appInfo;
}

