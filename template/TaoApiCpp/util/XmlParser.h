#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <TaoApiCpp/util/Parser.h>
#include <QDomElement>


class XmlParser : public Parser
{
public:
  XmlParser(const QString &string);
  XmlParser(const QDomElement &rootElement);
  virtual ~XmlParser();

  virtual bool hasName(const QString &name);

  virtual bool getBoolByName(const QString &name);
  virtual qlonglong getNumByName(const QString &name);
  virtual QDateTime getDateByName(const QString &name);
  virtual QString getStrByName(const QString &name);
  virtual Parser *getObjectParser(const QString &name);

  virtual QList<bool> getListBoolByName(const QString &name);
  virtual QList<qlonglong> getListNumByName(const QString &name);
  virtual QList<QDateTime> getListDateByName(const QString &name);
  virtual QList<QString> getListStrByName(const QString &name);
  virtual QList<Parser *> getListObjectParser(const QString &name);

private:
  QDomElement rootElement;
};

#endif // XMLPARSER_H
