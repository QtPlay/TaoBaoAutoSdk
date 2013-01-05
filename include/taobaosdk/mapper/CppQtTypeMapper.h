#ifndef CPPQTTYPEMAPPER_H
#define CPPQTTYPEMAPPER_H
#include <mapper/TypeMapper.h>

class CppQtTypeMapper : public TypeMapper
{
public:
  virtual QString getDomainLangType(const QString &apiType) const;
  virtual QString getRequestLangType(const QString &apiType) const;
  virtual QString getResponseLangType(const QString &apiType) const;
};

#endif // CPPQTTYPEMAPPER_H
