#include <mapper/CppQtTypeMapper.h>

QString CppQtTypeMapper::getDomainLangType(const QString &apiType) const
{
  //WARNNING: 是否还需要其他类型？
  QString langType = apiType;
  if (langType == "String")
    langType = "QString";
  else if (langType == "Number")
    langType = "qlonglong";
  else if (langType == "Date")
    langType = "QDateTime";
  else if (langType == "Boolean")
    langType = "bool";
  else if (langType == "byte[]")
    langType = "FileItem";
  else if (langType == "Price")
    langType = "QString";
  else if (langType == "Field List")
    langType = "QString";
  else if (langType.isEmpty())
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
