/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2013  sea <email>

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

#ifndef CPPQTSDKGENERATOR_H
#define CPPQTSDKGENERATOR_H

#include <generator/SdkGenerator.h>

/**
 * @todo getXXXSourceCode函数部份，为通过模板文件转换为实际代码。模板文件写的意义不清，为
 * 数字代替，使代码较为晦涩难懂。以后如有时间再更正为意义清晰的字符串。
 **/
class CppQtSdkGenerator : public SdkGenerator
{
public:
  CppQtSdkGenerator(SdkParser* parser);

protected:
  virtual QString getSdkBasicSourceDir();
  virtual QString getSdkVersionFilePath();
  virtual QString getResponseSourceFileName(const ApiResponse &response);
  virtual QString getResponseSourceCode(const ApiResponse &response);
  virtual QString getRequestSourceFileName(const ApiRequest &request);
  virtual QString getRequestSourceCode(const ApiRequest& request);
  virtual QString getDomainSourceFileName(const ApiDomain& domain);
  virtual QString getDomainSourceCode(const ApiDomain& domain);
};

#endif // CPPQTSDKGENERATOR_H
