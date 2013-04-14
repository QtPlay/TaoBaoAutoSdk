#include <parser/MetaSdkParser.h>

#include <QtCore>

MetaSdkParser::MetaSdkParser(TypeMapper* typeMapper, const QString&
metadataXmlPath)
{
    readFile(metadataXmlPath);
    if (mapper == NULL) {
      qDebug() << "mapper cannot be NULL";
      exit(1);
    }
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
%2:\n%3").arg(errorLine).arg(errorColumn).arg(errorStr);
  exit(1);
  }

  root = domDocument.documentElement();
  if (root.tagName() != "metadata") {
    qDebug() << "The taobao metadata file is InValid.";
    exit(1);
  }
  if (root.hasAttribute("versionNo")) {
    // TODO: set the TaoBao ApiVersion
    ;
  }
  return true;
}

QList< ApiDomain > MetaSdkParser::getApiDomains()
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
      QDomNode propNode = propNodes.at(j);
      ApiField field;
      field.setName(propNode.firstChildElement("name").text());
      field.setDesc(propNode.firstChildElement("desc").text());
      QString typeStr = propNode.firstChildElement("type").text();
      field.setApiType(typeStr);
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
 *
 * @return QList< ApiRequest >
 **/
QList< ApiRequest > MetaSdkParser::getApiRequests()
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
      QDomNode paramNode = paramNodes.at(j);
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

      field.setLangType(mapper->getRequestLangType(type));
      tmp.addField(field);
    }
    apiRequests.append(tmp);
  }
  return apiRequests;
}

/**
 * @brief 获取Response Api类
 *
 * @return QList< ApiResponse >
 **/
QList< ApiResponse > MetaSdkParser::getApiResponses()
{
  QList<ApiResponse> apiResponses;
  QDomNodeList apiNodes = root.elementsByTagName("api");

  for (int i = 0; i < apiNodes.size(); i++) {
    QDomNode apiNode = apiNodes.at(i);
    ApiResponse tmp;
    tmp.setName(apiNode.firstChildElement("name").text());
    tmp.setDesc(apiNode.firstChildElement("desc").text());
    QDomElement responseNode = apiNode.firstChildElement("response");
    QDomNodeList paramNodes = responseNode.elementsByTagName("param");
    for (int j = 0; j < paramNodes.size(); j++) {
      QDomNode paramNode = paramNodes.at(j);
      ApiField field;
      field.setName(paramNode.firstChildElement("name").text());
      field.setDesc(paramNode.firstChildElement("desc").text());
      field.setApiLevel(paramNode.firstChildElement("level").text());
      QString type = paramNode.firstChildElement("type").text();
      field.setApiType(type);
      field.setLangType(mapper->getResponseLangType(type));
      tmp.addField(field);
    }
    apiResponses.append(tmp);
  }
  return apiResponses;
}
