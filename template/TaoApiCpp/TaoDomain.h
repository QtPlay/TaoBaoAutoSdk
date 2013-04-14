#ifndef TAODOMAIN_H
#define TAODOMAIN_H

#include <TaoApiCpp/TaoParser.h>

#include <QList>
#include <QPair>

class TaoDomain
{
public:
  TaoDomain();
  virtual ~TaoDomain();

  void setParser(Parser *parser) {
    responseParser = parser;
  }

  Parser *responseParser;
  virtual void parseResponse() = 0;

};

#endif // TAODOMAIN_H
