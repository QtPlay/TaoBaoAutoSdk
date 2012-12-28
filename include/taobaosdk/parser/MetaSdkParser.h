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
    with this program; if not, write to the Free Software FoundatiThis is a
simple mirroring test:
    This field should be mirrored into field on, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/


#ifndef METASDKPARSER_H
#define METASDKPARSER_H

#include <parser/SdkParser.h>
#include <mapper/TypeMapper.h>
#include <QDomDocument>

/**
 * @brief metadata.xml的处理类，要求完善的metadata.xml：struct、api、param等节点都为同级兄弟，
 * 只适用于淘宝metadata
 **/
class MetaSdkParser : public SdkParser
{
public:
  MetaSdkParser(TypeMapper *typeMapper, const QString &metadataXmlPath);
  virtual const QList< ApiDomain > getApiDomains();
  virtual const QList< ApiRequest > getApiRequests();
  virtual const QList< ApiResponse > getApiResponses();
private:
  bool readFile(const QString &filePath);
  /**
   * @brief 类型映射器
   **/
  TypeMapper *mapper;
  /**
   * @brief Qt Dom Xml处理
   **/
  QDomDocument domDocument;
  QDomElement root;
};

#endif // METASDKPARSER_H
