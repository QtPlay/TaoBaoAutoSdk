#ifndef APIDOMAIN_H
#define APIDOMAIN_H
#include <domain/BaseObject.h>

class ApiDomain : public BaseObject
{
public:
  bool isInUsed() const {
    return inUsed;
  }
  void setInUsed(bool use) {
    inUsed = use;
  }
  QString getClassName() const {
    return StringKit::capitalize(StringKit::toCamelCase(getName()));
  }

private:
  bool inUsed;
};

#endif // APIDOMAIN_H
