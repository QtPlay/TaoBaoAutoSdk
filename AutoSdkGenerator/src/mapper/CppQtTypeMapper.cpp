#include <mapper/CppQtTypeMapper.h>

QString CppQtTypeMapper::getDomainLangType(const QString &apiType) const
{
  //WARNNING: 是否还需要其他类型？
  QString langType = apiType;
  if (apiType == "String")
    langType = "QString";
  else if (apiType == "Number")
    langType = "qlonglong";
  else if (apiType == "Date")
    langType = "QDateTime";
  else if (apiType == "Boolean")
    langType = "bool";
  else if (apiType == "byte[]")
    langType = "FileItem";
  else if (apiType == "Price")
    langType = "QString";
  else if (apiType == "Field List")
    langType = "QString";
  else if (apiType.isEmpty())
    langType = "QString";

  return langType;
}

QString CppQtTypeMapper::getRequestLangType(const QString &apiType) const
{
  return getDomainLangType(apiType);
}

QString CppQtTypeMapper::getResponseLangType(const QString &apiType) const
{
  return getDomainLangType(apiType);
}
