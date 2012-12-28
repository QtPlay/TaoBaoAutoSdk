/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2012  sea <email>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/


#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include <domain/NameObject.h>
#include <domain/ApiField.h>
#include <QList>


class BaseObject : public NameObject
{
public:
  const QString &getLastModified() const {
    return lastModified;
  }

  void setLastModified(const QString &lastModified) {
    this->lastModified = lastModified;
  }

  void setFields(const QList<ApiField> &fields) {
    this->fields = fields;
  }

  const QList<ApiField> &getFields() {
    qSort(fields);
    return fields;
  }

  void addField(const ApiField &field) {
    if (!getFields().contains(field)) {
      fields.append(field);
    }
  }

  /**
   * 验证对象是否包含属性。
   */
  bool isContainField() {
    return !getFields().isEmpty();
  }

  /**
   * 验证对象是否包含列表属性。
   */
  bool isContainListField() {
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
  bool isContainDateField() {
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
