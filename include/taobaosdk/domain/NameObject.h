#ifndef NAMEOBJECT_H
#define NAMEOBJECT_H

#include <QString>

class NameObject
{
public:
  const QString &getName() const {
    return name;
  }

  void setName(const QString &name) {
    this->name = name;
  }

  const QString &getDesc() const {
    return desc;
  }

  void setDesc(const QString &desc) {
    this->desc = desc;
  }

  bool equals(const NameObject &obj) {
    return name.compare(obj.getName(),Qt::CaseInsensitive);
  }

private:
  QString name;
  QString desc;
};

#endif // NAMEOBJECT_H
