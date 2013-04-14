#include "TaoParser.h"
#include <TaoApiCpp/util/XmlParser.h>

Parser *TaoParser(const QString &responseStr, const QString &responseFormat)
{
  if (responseFormat == Constants::FORMAT_XML) {
    XmlParser *xmlParser = new XmlParser(responseStr);
    return xmlParser;
  } else {
    //TODO: JSON Support is not support now
    return NULL;
  }
}
