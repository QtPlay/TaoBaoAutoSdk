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


#ifndef SDKGENERATOR_H
#define SDKGENERATOR_H

#include <parser/SdkParser.h>
#include <QString>
#include <QDate>
#include <QDir>


class SdkGenerator
{
public:
  SdkGenerator(SdkParser *parser) {
    this->parser = parser;
    init();
  }

  void generate(QDir outDir)
  {
    process();
  }

protected:
  QString sourcesDir;
  /**
  * @brief 生成数据结构源码。
  */
  virtual const QString getDomainSourceCode(const ApiDomain &domain) = 0;

  /**
  * @brief 获取domain相关的文件路径，相对于sourcesDir来说
  *
  * @param domain ...
  * @return QString domain文件名
  **/
  virtual const QString getDomainSourceFileName(const ApiDomain &domain) = 0;

  /**
  * @brief 生成API请求源码。
  */
  virtual const QString getRequestSourceCode(const ApiRequest &request) = 0;

  /**
  * @brief 获取API请求文件路径，相对于sourcesDir来说
  **/
  virtual const QString getRequestSourceFileName(ApiRequest request) = 0;

  /**
  * @brief 生成API响应源码。
  */
  virtual const QString getResponseSourceCode(ApiResponse response) = 0;
  /**
  * @brief 生成API响应文件路径，，相对于sourcesDir来说
  */
  virtual const QString getResponseSourceFileName(ApiResponse response) = 0;
  /**
   * @brief 获取SDK版本文件路径，用于替换版本号。版本文件中版本号用dynamicVersionNo表示。用户的继承类必须实现此函数
   */
  virtual const QString getSdkVersionFilePath() = 0;

  /**
   * @brief
   * @return void
   **/
  void generateSdkVersion();

  /**
   * @brief SDK基础框架源文件所在路径。用户的继承类必须实现此函数
   */
  virtual const QString getSdkBasicSourceDir() = 0;

  void process();

  void generateDomains();
  void generateRequests();
  void generateResponses();

private:
  void init();
  void writeFile(const QString &codeStr, const QString &absoluteFilePath);

  SdkParser *parser;

  QList<ApiDomain> domains;
  QList<ApiRequest> requests;
  QList<ApiResponse> responses;
};

#endif // SDKGENERATOR_H
