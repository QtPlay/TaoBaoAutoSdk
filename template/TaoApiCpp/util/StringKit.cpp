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


#include <util/StringKit.h>

QString StringKit::getSetMethod(const QString &str)
{
  if (str.isEmpty())
    return "";

  QString tmpStr = str;
  if (tmpStr.size() > 1 && tmpStr.at(1).isUpper()) {
    return tmpStr;
  }

  tmpStr[0] = tmpStr[0].toUpper();
  return tmpStr;
}

QString StringKit::capitalize(const QString& str)
{
  if (str.isEmpty())
    return "";

  QString tmpStr = str;
  if (tmpStr.at(0).isLower())
    tmpStr[0] = tmpStr.at(0).toUpper();
  return tmpStr;
}

QString StringKit::toLowerWithUnderscore(const QString& str)
{
  if (str.isEmpty())
    return "";

  QString tmpStr;

  if (str.at(0).isUpper())
    tmpStr += str.at(0).toLower();

  for (int i = 1; i < str.size(); i++) {
    if (str.at(i).isUpper()) {
      tmpStr += '_';
      tmpStr += str.at(i).toLower();
    }
    else
      tmpStr += str.at(i);
  }

  return tmpStr;
}

QString StringKit::toCamelCase(const QString& str)
{
  if (str.isEmpty())
    return "";

  QString tmpStr;
  for (int i = 0; i < str.size(); i++) {
    if (str.at(i) == '.' || str.at(i) == '_') {
      if (++i < str.size())
        tmpStr += str.at(i).toUpper();
    } else
      tmpStr += str.at(i);
  }
  return tmpStr;
}

QString StringKit::toPascalCase(const QString& str)
{
  if (str.isEmpty())
    return "";

  QString tmpStr = toCamelCase(str);
  tmpStr[0] = tmpStr.at(0).toUpper();
  return tmpStr;
}

QString StringKit::escapeInvalidXml(const QString& str)
{
  return str;
}


