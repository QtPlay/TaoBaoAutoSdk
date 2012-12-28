#ifndef CPPQTTYPEMAPPER_H
#define CPPQTTYPEMAPPER_H
#include <mapper/TypeMapper.h>

class CppQtTypeMapper : public TypeMapper
{
public:
  const QString getDomainLangType(const QString &apiType) const;
  const QString getRequestLangType(const QString &apiType) const;
  const QString getResponseLangType(const QString &apiType) const;
};

#endif // CPPQTTYPEMAPPER_H
