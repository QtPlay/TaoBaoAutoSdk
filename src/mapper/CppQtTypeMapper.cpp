#include <mapper/CppQtTypeMapper.h>

const QString CppQtTypeMapper::getDomainLangType(const QString &apiType) const
{
  //WARNNING: 是否还需要其他类型？
  QString langType = apiType;
  if (langType == "String")
    langType = "QString";
  else if (langType == "Number")
    langType = "quint64";
  else if (langType == "Date")
    langType = "QDateTime";
  else if (langType == "Boolean")
    langType = "bool";
  else if (langType == "byte[]")
    langType = "QByteArray";
  else if (langType == "price")
    langType = "QString";
  else if (langType.isEmpty())
    langType = "QString";

  return langType;
}

const QString CppQtTypeMapper::getRequestLangType(const QString &apiType) const
{
  return getDomainLangType(apiType);
}

const QString CppQtTypeMapper::getResponseLangType(const QString &apiType) const
{
  return getDomainLangType(apiType);
}
