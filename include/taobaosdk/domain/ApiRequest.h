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


#ifndef APIREQUEST_H
#define APIREQUEST_H

#include <domain/BaseObject.h>

class ApiRequest : public BaseObject
{
public:
  /**
   * @brief 获得请求类的名称，去掉metadata中api名字的前缀"taobao."
   *
   * @return const QString
   **/

  QString getRequestClassName() const {
    return StringKit::capitalize(StringKit::toCamelCase(getName().mid(7))) +
"Request";
  }

  /**
   * @brief 获得响应类的名称，去掉metadata中api名字的前缀"taobao."
   *
   * @return const QString
   **/
  QString getResponseClassName() const {
    return StringKit::capitalize(StringKit::toCamelCase(getName().mid(7))) +
"Response";
  }

  bool isUploadRequest() {
    foreach(ApiField field, getFields()) {
      if (field.getApiType() == "byte[]")
        return true;
    }
    return false;
  }

};

#endif // APIREQUEST_H
