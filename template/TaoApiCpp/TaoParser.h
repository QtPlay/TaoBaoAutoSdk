#ifndef TAOPARSER_H
#define TAOPARSER_H

#include <TaoApiCpp/Constants.h>
#include <TaoApiCpp/util/Parser.h>

/**
 * @brief parse the response Xml/Json
 * @param responseStr, response Text
 * @param responseFormat, Constants::FORMAT_XML or Constants::FORMAT_JSON
 * @return XmlParser or JsonParser;
 */
//TODO : JSON parser
Parser *TaoParser(const QString &responseStr,const QString &responseFormat = Constants::FORMAT_XML);

#endif // TAOPARSER_H
