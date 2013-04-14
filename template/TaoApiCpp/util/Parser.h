#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include <QDateTime>
#include <QList>

class Parser
{
public:
  Parser(const QString &string) { responseStr = string; }
  virtual ~Parser() { }
  virtual bool hasName(const QString &name) = 0;

  virtual bool getBoolByName(const QString &name) = 0;
  virtual qlonglong getNumByName(const QString &name) = 0;
  virtual QDateTime getDateByName(const QString &name) = 0;
  virtual QString getStrByName(const QString &name) = 0;
  virtual Parser *getObjectParser(const QString &name) = 0;

  virtual QList<bool> getListBoolByName(const QString &name) = 0;
  virtual QList<qlonglong> getListNumByName(const QString &name) = 0;
  virtual QList<QDateTime> getListDateByName(const QString &name) = 0;
  virtual QList<QString> getListStrByName(const QString &name) = 0;
  virtual QList<Parser *> getListObjectParser(const QString &name) = 0;

  QString responseStr;
};

#endif // PARSER_H
