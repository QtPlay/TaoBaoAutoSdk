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


#ifndef STRINGKIT_H
#define STRINGKIT_H

#include <QString>

class StringKit
{
public:
  /**
   * @brief 生成JAVA/Qt风格的get/set方法名
   *
   * @param str 传入的字符串
   * @return const QString&
   **/
  static const QString getSetMethod(const QString &str);

  /**
   * @brief 生成首字母大写的字符串
   *
   * @param str ...
   * @return const QString&
   **/
  static const QString capitalize(const QString &str);

  /**
   * @brief 将字符串由驼峰转换为下划线形式
   *
   * @param str ...
   * @return const QString&
   **/
  static const QString toLowerWithUnderscore(const QString &str);

  /**
   * @brief 将字符串转换为驼峰风格
   *
   * @param str ...
   * @return const QString&
   **/
  static const QString toCamelCase(const QString &str);

  /**
   * @brief 将字符串转化为帕斯卡风格

   * @param str ...
   * @return const QString&
   **/
  static const QString toPascalCase(const QString &str);

  /**
   * @brief 过滤不可见字符，不知在Qt中是否需要实现
   *
   * @param str ...
   * @return const QString&
   **/
  static const QString escapeInvalidXml(const QString &str);
};

#endif // STRINGKIT_H
