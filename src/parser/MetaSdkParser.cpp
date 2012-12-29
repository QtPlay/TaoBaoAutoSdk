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


#include <parser/MetaSdkParser.h>
#include <QFile>
#include <QDebug>

MetaSdkParser::MetaSdkParser(TypeMapper* typeMapper, const QString&
metadataXmlPath)
{
    readFile(metadataXmlPath);
    mapper = typeMapper;
}

bool MetaSdkParser::readFile(const QString& filePath)
{
  QFile file(filePath);
  if (!file.open(QFile::ReadOnly | QFile::Text)) {
    qDebug() << QString("Cannot read\
file%1:\n%2.\n App will exit").arg(filePath).arg(file.errorString());
    exit(1);
  }

  QString errorStr;
  int errorLine;
  int errorColumn;

  if(!domDocument.setContent(&file,false,&errorStr, &errorLine, &errorColumn)) {
    qDebug() << QString("parser xmlFile error at line %1, column\
%2:\n%d").arg(errorLine).arg(errorColumn).arg(errorStr);
  exit(1);
  }

  root = domDocument.documentElement();
  if (root.tagName() != "metadata") {
    qDebug() << "The file is not an taobao metadata file.";
    exit(1);
  }
  /**
   * @todo 尚未设置Sdk VersionNo
   **/
  if (root.hasAttribute("versionNo")) {
    ; //TODO: set the sdk version
  }
  return true;
}

const QList< ApiDomain > MetaSdkParser::getApiDomains()
{
  QList<ApiDomain> apiDomains;
  QDomNodeList structNodes;
  structNodes = root.elementsByTagName("struct");

  for (int i = 0; i < structNodes.size(); i++) {
    QDomNode structNode = structNodes.at(i);
    ApiDomain tmp;
    tmp.setName(structNode.firstChildElement("name").text());
    tmp.setDesc(structNode.firstChildElement("desc").text());
    QDomNodeList propNodes = structNode.toElement().elementsByTagName("prop");
    for (int j = 0; j < propNodes.size(); j++) {
      QDomNode propNode;
      ApiField field;
      field.setName(propNode.firstChildElement("name").text());
      field.setDesc(propNode.firstChildElement("desc").text());
      QString typeStr = propNode.firstChildElement("type").text();
      field.setApiType(typeStr);
      if (mapper != NULL)
        field.setLangType(mapper->getDomainLangType(typeStr));
      field.setApiLevel(propNode.firstChildElement("level").text());
      tmp.addField(field);
    }
    apiDomains.append(tmp);
  }
  return apiDomains;
}

/**
 * @brief 获取Request Api类
 * 与getApiResponse不同的是, Requests只是借助level确定langType
 * 而Response直接存储meta数据中的level。
 *
 * @return const QList< ApiDomain >
 **/
const QList< ApiRequest > MetaSdkParser::getApiRequests()
{
  QList<ApiRequest> apiRequests;
  QDomNodeList apiNodes = root.elementsByTagName("api");

  for (int i = 0; i < apiNodes.size(); i++) {
    QDomNode apiNode = apiNodes.at(i);
    ApiRequest tmp;
    tmp.setName(apiNode.firstChildElement("name").text());
    tmp.setDesc(apiNode.firstChildElement("desc").text());
    QDomElement requestNode = apiNode.firstChildElement("request");
    QDomNodeList paramNodes = requestNode.elementsByTagName("param");
    for (int j = 0; j < paramNodes.size(); j++) {
      QDomNode paramNode = paramNodes.at(i);
      ApiField field;
      field.setName(paramNode.firstChildElement("name").text());
      field.setDesc(paramNode.firstChildElement("desc").text());
      /**
       * @brief level "Basic Array"其实为String类型
       **/
      QString level = paramNode.firstChildElement("level").text();
      QString type = paramNode.firstChildElement("type").text();
      if (SdkConstants::TYPE_BASIC_ARRAY == level)
        field.setApiType("QString");
      else
        field.setApiType(type);

      if (mapper != NULL)
        field.setLangType(mapper->getRequestLangType(type));
      tmp.addField(field);
    }
    apiRequests.append(tmp);
  }
  return apiRequests;
}

const QList< ApiResponse > MetaSdkParser::getApiResponses()
{
  QList<ApiResponse> apiResponses;
  QDomNodeList apiNodes = root.elementsByTagName("api");

  for (int i = 0; i < apiNodes.size(); i++) {
    QDomNode apiNode = apiNodes.at(i);
    ApiResponse tmp;
    tmp.setName(apiNode.firstChildElement("name").text());
    tmp.setDesc(apiNode.firstChildElement("desc").text());
    QDomElement responseNode = apiNode.firstChildElement("request");
    QDomNodeList paramNodes = responseNode.elementsByTagName("param");
    for (int j = 0; j < paramNodes.size(); j++) {
      QDomNode paramNode = paramNodes.at(i);
      ApiField field;
      field.setName(paramNode.firstChildElement("name").text());
      field.setDesc(paramNode.firstChildElement("desc").text());
      field.setApiLevel(paramNode.firstChildElement("level").text());
      QString type = paramNode.firstChildElement("type").text();
      field.setApiType(type);
      if (mapper != NULL)
        field.setLangType(mapper->getResponseLangType(type));
      tmp.addField(field);
    }
    apiResponses.append(tmp);
  }
  return apiResponses;
}
