#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include <domain/NameObject.h>
#include <domain/ApiField.h>
#include <QList>


class BaseObject : public NameObject
{
public:
  QString getLastModified() const {
    return lastModified;
  }

  void setLastModified(const QString &lastModified) {
    this->lastModified = lastModified;
  }

  void setFields(const QList<ApiField> &fields) {
    this->fields = fields;
  }

  QList<ApiField> getFields() const {
    return fields;
  }

  void addField(const ApiField &field) {
    if (!getFields().contains(field)) {
      fields += field;
      qSort(fields);
    }
  }

  /**
   * 验证对象是否包含属性。
   */
  bool isContainField() const {
    return !getFields().isEmpty();
  }

  /**
   * 验证对象是否包含列表属性。
   */
  bool isContainListField() const {
    ApiField field;
    foreach (field , fields) {
      if (field.isListField()) {
        return true;
      }
    }
    return false;
  }

  /**
   * 验证是否包含日期属性。
   */
  bool isContainDateField() const{
    ApiField field;
    foreach (field, getFields()) {
      if ("Date" == field.getApiType()) {
        return true;
      }
    }
    return false;
  }

private:
  QString lastModified;
  QList<ApiField> fields;

};

#endif // BASEOBJECT_H
