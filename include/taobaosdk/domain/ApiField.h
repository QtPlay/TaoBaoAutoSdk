/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2012  sd44 <sd44sd44@yeah.net>

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

#ifndef APIFIELD_H
#define APIFIELD_H

#include <domain/NameObject.h>
#include <util/StringKit.h>
#include <SdkConstants.h>

/**
 * @brief Api属性，针对metadata.xml中的prop下字段
 **/
class ApiField : public NameObject
{
public:
  const QString &getLangType() const {
    return langType;
  }

  void setLangType(const QString &langType) {
    this->langType = langType;
  }

  const QString &getApiType() const {
    return apiType;
  }

  void setApiType(const QString &apiType) {
    this->apiType = apiType;
  }

  const QString &getApiLevel() const {
    return apiLevel;
  }

  void setApiLevel(const QString &apiLevel) {
    this->apiLevel = apiLevel;
  }

  /**
   * @brief 获得驼峰风格名称
   *
   * @return const QString
   **/
  const QString getCamelCaseName() const {
    return StringKit::toCamelCase(getName());
  }

  /**
   * @brief 获得帕斯卡风格名称
   *
   * @return const QString
   **/
  const QString getPascalCaseName() const {
    return StringKit::toPascalCase(getName());
  }

  /**
   * @brief 获得属性的get方法名称
   *
   * @return const QString
   **/
  const QString getGetMethodName() const {
    return "get" + getMethodName();
  }

  /**
   * @brief 获得属性的set方法名称
   *
   * @return const QString
   **/
  const QString getSetMethodName() const {
    return "set" + getMethodName();
  }

  const QString getMethodName() const {
    return StringKit::getSetMethod(getCamelCaseName());
  }
  /**
   * @brief 判断属性是否是列表类型
   */
  bool isListField() const {
    return (SdkConstants::TYPE_BASIC_ARRAY == apiLevel) ||
    (SdkConstants::TYPE_OBJECT_ARRAY == apiLevel);
  }
  /**
   * @brief 判断属性是否是复杂Object类型
   */
  bool isObjectField() {
    return (SdkConstants::TYPE_OBJECT == apiLevel) ||
    (SdkConstants::TYPE_OBJECT_ARRAY == apiLevel);
  }

  /**
   * @brief 获取定义类型：属性定义，方法定义，返回值。
   *
   * @param prefix 列表类型的前缀
   * @param suffix 列表类型的后缀
   */
  QString getDefineLangType(QString prefix, QString suffix) {
    QString str;
    if (!prefix.isEmpty() && isListField()) {
      str.append(prefix);
    }
    str.append(langType);

    if (!suffix.isEmpty() && isListField()) {
      str.append(suffix);
    }
    return str;
  }

private:
  /**
   * @brief 特定语言的类型
   **/
  QString langType;

  /**
   * @brief metadata中固定的语言类型
   **/
  QString apiType;

  /**
   * @brief metadata属性api level: Basic, Basic Object, Object, Object Array
   **/
  QString apiLevel;
};

bool operator<(const ApiField &field1, const ApiField &field2);
bool operator==(const ApiField &field1, const ApiField &field2);
bool operator!=(const ApiField &field1, const ApiField &field2);

#endif // APIFIELD_H

