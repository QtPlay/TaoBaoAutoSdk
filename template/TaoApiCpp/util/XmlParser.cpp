#include "XmlParser.h"
#include <TaoApiCpp/Constants.h>
#include <QtCore>
#include <QtXml>

XmlParser::XmlParser(const QString &string)
  : Parser(string)
{
  QDomDocument doc;
  QString errorMsg;
  int errorLine;
  int errorColumn;

  if(!doc.setContent(responseStr, &errorMsg,
                     &errorLine, &errorColumn)) {
    qDebug() << "error occured:\n" << errorMsg
             << "in line: " << errorLine << "\tline: " << errorColumn;
    return;
  }

  rootElement = doc.documentElement();
}

XmlParser::XmlParser(const QDomElement &rootElement)
  : Parser("")
{
  this->rootElement = rootElement;
}

XmlParser::~XmlParser()
{
}

bool XmlParser::hasName(const QString &name)
{
  QDomElement element = rootElement.firstChildElement(name);
  if (element.isNull())
    return false;
  return true;
}

bool XmlParser::getBoolByName(const QString &name)
{
  QDomElement element = rootElement.firstChildElement(name);
  QString boolValue = element.text();
  if (boolValue.compare("true", Qt::CaseInsensitive) == 0)
    return true;
  else if (boolValue.compare("false", Qt::CaseInsensitive) == 0)
    return false;
  else {
    qDebug() << "in xmlParser, getboolByname translator error\n"
             << "the Text is:\n" << boolValue;
    return false;
  }
}

qlonglong XmlParser::getNumByName(const QString &name)
{
  QDomElement element = rootElement.firstChildElement(name);
  QString number = element.text();
  bool ok;
  qlonglong longlongNum = number.toLongLong(&ok);
  if (!ok)
    qDebug() << "error in XmlParser getNumByname()"
             << "the elem text is:\n" << number;
  return longlongNum;
}

QDateTime XmlParser::getDateByName(const QString &name)
{
  QDomElement element = rootElement.firstChildElement(name);
  QString dateStr = element.text();
  QDateTime dateTime = QDateTime::fromString(dateStr, Constants::DATE_TIME_FORMAT);
  if (!dateTime.isValid())
    qDebug() << "error in XmlParser getDateByName()"
             << "the elem text is:\n" << dateStr;
  return dateTime;
}

QString XmlParser::getStrByName(const QString &name)
{
  QDomElement element = rootElement.firstChildElement(name);
  QString elemStr = element.text();
  return elemStr;
}

Parser *XmlParser::getObjectParser(const QString &name)
{
  QDomElement element = rootElement.firstChildElement(name);
  if (element.isNull()) {
    qDebug() << "pls use XmlParser::hasName(name) to test if response has the elementName";
    return NULL;
  }
  XmlParser *objectParser = new XmlParser(element);
  return objectParser;
}

QList<bool> XmlParser::getListBoolByName(const QString &name)
{
  QList<bool> listBool;

  QDomNodeList nodeList = rootElement.elementsByTagName(name);
  QDomElement elem;
  for (int i = 0; i < nodeList.size(); i++) {
    if ((elem = nodeList.at(i).toElement()).isNull()) {
      qDebug() << "maybe error in XmlParser::getListBoolByname\n";
      break;
    }
    QString boolValue = elem.text();
    if (boolValue.compare("true", Qt::CaseInsensitive) == 0)
      listBool.append(true);
    else if (boolValue.compare("false", Qt::CaseInsensitive) == 0)
      listBool.append(false);
    else
      qDebug() << "in xmlParser, getListBoolByname error\n"
               << "the Text is:\n" << boolValue;
  }

  return listBool;
}

QList<qlonglong> XmlParser::getListNumByName(const QString &name)
{
  QList<qlonglong> listNum;

  QDomNodeList nodeList = rootElement.elementsByTagName(name);
  QDomElement elem;

  for (int i = 0; i < nodeList.size(); i++) {
    if ((elem = nodeList.at(i).toElement()).isNull()) {
      qDebug() << "maybe error in XmlParser::getListBoolByname\n";
      break;
    }
    QString number = elem.text();
    bool ok;

    qlonglong longlongNum = number.toLongLong(&ok);
    if (!ok) {
      qDebug() << "error in XmlParser getNumByname()"
               << "the elem text is:\n" << number;
      break;
    }
    listNum.append(longlongNum);
  }
  return listNum;
}

QList<QDateTime> XmlParser::getListDateByName(const QString &name)
{
  QList<QDateTime> listDate;
  QDomNodeList nodeList = rootElement.elementsByTagName(name);
  QDomElement element;

  for (int i = 0; i < nodeList.size(); i++) {
    if ((element = nodeList.at(i).toElement()).isNull()) {
      qDebug() << "maybe error in XmlParser::getListDateByName\n";
      break;
    }
    QString dateStr = element.text();
    QDateTime dateTime = QDateTime::fromString(dateStr, Constants::DATE_TIME_FORMAT);
    if (!dateTime.isValid())
      qDebug() << "error in XmlParser::getListDateByName()"
               << "the elem text is:\n" << dateStr;
    listDate.append(dateTime);
  }
  return listDate;
}

QList<QString> XmlParser::getListStrByName(const QString &name)
{
  QList<QString> listStr;
  QDomNodeList nodeList = rootElement.elementsByTagName(name);

  for (int i = 0 ; i < nodeList.size(); i++) {
    listStr.append(nodeList.at(i).toElement().text());
  }
  return listStr;
}

QList<Parser *> XmlParser::getListObjectParser(const QString &name)
{
  QList<Parser *> listParser;
  QDomNodeList nodeList = rootElement.elementsByTagName(name);
  QDomElement element;

  XmlParser *objectParser;
  for (int i = 0; i < nodeList.size(); i++) {
    element = nodeList.at(i).toElement();
    if (element.isNull()) {
      qDebug() << "null data in XmlParser::getListObjectParser\n";
    }
    objectParser = new XmlParser(element);
    listParser.append(objectParser);
  }
  return listParser;
}
