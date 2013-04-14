#include <generator/CppQtSdkGenerator.h>
#include <domain/ApiDomain.h>
#include <domain/ApiRequest.h>
#include <domain/ApiResponse.h>
#include <qtextstream.h>
#include <QDebug>

CppQtSdkGenerator::CppQtSdkGenerator(SdkParser *parser)
  : SdkGenerator((parser))
{

}

QString CppQtSdkGenerator::getSdkBasicSourceDir()
{
  return QString("/home/sd44/projects/Taobao/TaoApiCpp/TaoApiCpp");
}

QString CppQtSdkGenerator::getSdkVersionFilePath()
{
  return sourcesDir + "/Constants.cpp";
}

QString CppQtSdkGenerator::getDomainHeaderFileName(const ApiDomain &domain)
{
  return sourcesDir + "/domain/" + domain.getClassName() + ".h";
}


QString CppQtSdkGenerator::getDomainSourceFileName(const ApiDomain& domain)
{
  return sourcesDir + "/domain/" + domain.getClassName() + ".cpp";
}

QString CppQtSdkGenerator::getDomainHeader(const ApiDomain &domain)
{
  ApiField field;

  QString filePre = domain.getClassName().toUpper() + "_H";

  QStringList includeFiles;
  if (domain.isContainDateField())
    includeFiles += "#include <QDateTime>\n";
  if (domain.isContainListField())
    includeFiles += "#include <QList>\n";
  includeFiles += "#include <QString>\n";

  /**
   * @brief domain的私有字段的字符串组装
   *
   **/
  QString privateField;
  /**
   * @brief domain类中method的字符串的组装
   **/
  QString publicMethod;

  QList<ApiField> domainFields  = domain.getFields();
  foreach(field, domainFields) {
    if (privateField.size() > 0)
      privateField.append("\n");
    privateField.append(QString("/**\n"
                                " * @brief %1\n").arg(field.getDesc()));
    privateField.append(" **/\n");

    privateField.append(QString("  %1 %2;\n").arg(field.getDefineLangType())
                        .arg(field.getCamelCaseName()));

    QString langType = field.getLangType();
    if (field.isObjectField()) {
      QString includeDomainFile(QString("#include <TaoApiCpp/domain/%1.h>\n")
                                .arg(langType));
      if (!includeFiles.contains(includeDomainFile))
        includeFiles += includeDomainFile;
    }

    if (publicMethod.size() > 0)
      publicMethod.append("\n");
    publicMethod.append(QString("  %1 %2() const;\n").arg(field.getDefineLangType())
                        .arg(field.getGetMethodName()));

    publicMethod.append(QString("  void %1 (%2 %3);").arg(field.getSetMethodName())
                        .arg(field.getDefineLangType())
                        .arg(field.getCamelCaseName()));
  }

  QFile file("/home/sd44/DomainHeader.txt");
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << "fucking open DomainHeader.txt";
    exit(1);
  }
  QTextStream in(&file);
  in.setCodec("UTF-8");

  QString result = in.readAll().arg(filePre).arg(includeFiles.join("")).arg(domain.getDesc())
      .arg(domain.getClassName())
      .arg(publicMethod)
      .arg(privateField);
  return result;
}

QString CppQtSdkGenerator::getDomainSource(const ApiDomain& domain)
{
  ApiField field;

  QString className = domain.getClassName();

  QString publicMethod;

  /**
   * @brief parseResponse method's str;
   */
  QString parseResponse;

  QList<ApiField> domainFields  = domain.getFields();
  foreach(field, domainFields) {

    if (publicMethod.size() > 0)
      publicMethod.append("\n");
    publicMethod.append(QString("%1 %2::%3() const {\n").arg(field.getDefineLangType())
                        .arg(className)
                        .arg(field.getGetMethodName()));
    publicMethod.append(QString("  return %1;\n").arg(field.getCamelCaseName()));
    publicMethod.append("}\n");

    publicMethod.append(QString("void %1::%2 (%3 %4) {\n")
                        .arg(className)
                        .arg(field.getSetMethodName())
                        .arg(field.getDefineLangType())
                        .arg(field.getCamelCaseName()));
    publicMethod.append(QString("  this->%1 = %1;\n").arg(field.getCamelCaseName()));
    publicMethod.append("}\n");

    parseResponse += generateParseResponse(field);
  }

  QFile file("/home/sd44/DomainSrc.txt");
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << "fucking open DomainSrc.txt";
    exit(1);
  }
  QTextStream in(&file);
  in.setCodec("UTF-8");

  QString result = in.readAll()
      .arg(domain.getClassName())
      .arg(publicMethod)
      .arg(parseResponse);
  return result;
}

QString CppQtSdkGenerator::getRequestHeaderFileName(const ApiRequest &request)
{
  return sourcesDir + "/request/" + request.getRequestClassName() + ".h";
}


QString CppQtSdkGenerator::getRequestSourceFileName(const ApiRequest &request)
{
  return sourcesDir + "/request/" + request.getRequestClassName() + ".cpp";
}

QString CppQtSdkGenerator::getRequestHeader(const ApiRequest& request)
{
  ApiField field;

  QString filePre = request.getRequestClassName().toUpper() + "_H";

  /**
   * @brief request类中method的字符串的组装
   **/
  QString publicMethod;

  /**
   * @brief request类中的私有字段的字符串组装
   *
   **/
  QString privateField;
  QList<ApiField> requestFields  = request.getFields();
  foreach(field, requestFields) {
    if (privateField.size() > 0)
      privateField.append("\n");
    privateField.append(
          QString("/**\n" " * @brief %1\n").arg(field.getDesc()));
    privateField.append(" **/\n");

    privateField.append(QString("  %1 %2;\n").arg(field.getLangType())
                        .arg(field.getCamelCaseName()));

    publicMethod.append(QString(" %1 %2() const\n;").arg(field.getLangType())
                        .arg(field.getGetMethodName()));

    publicMethod.append(QString("  void %1 (%2 %3);\n").arg(field.getSetMethodName())
                        .arg(field.getLangType())
                        .arg(field.getCamelCaseName()));

    publicMethod.append("\n");
  }

  QFile file("/home/sd44/RequestHeader.txt");
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << "fucking open Request.txt";
    exit(1);
  }
  QTextStream in(&file);
  in.setCodec("UTF-8");

  QString result = in.readAll().arg(filePre).arg(request.getDesc())
      .arg(request.getRequestClassName())
      .arg(publicMethod)
      .arg(request.getResponseClassName())
      .arg(privateField);
  return result;
}

QString CppQtSdkGenerator::getRequestSource(const ApiRequest& request)
{
  ApiField field;

  QString className = request.getRequestClassName();

  /**
   * @brief request类中method的字符串的组装
   **/
  QString publicMethod;

  /**
   * @brief request类中的私有字段的字符串组装
   *
   **/
  QList<ApiField> requestFields  = request.getFields();
  foreach(field, requestFields) {

    publicMethod.append(QString("%1 %2::%3() const {\n")
                        .arg(field.getLangType())
                        .arg(className)
                        .arg(field.getGetMethodName()));
    publicMethod.append(QString("  return %1;\n").arg(field.getCamelCaseName()));
    publicMethod.append("}\n");
    publicMethod.append(QString("void %1::%2 (%3 %4) {\n")
                        .arg(className)
                        .arg(field.getSetMethodName())
                        .arg(field.getLangType())
                        .arg(field.getCamelCaseName()));
    publicMethod.append(QString("  this->%1 = %1;\n").arg(field.getCamelCaseName()));
    if (field.getLangType() == "QString")
      publicMethod.append(QString("  appParams.insert(\"%1\", %2);\n")
                          .arg(field.getName())
                          .arg(field.getCamelCaseName()));
    else if (field.getLangType() == "qlonglong")
      publicMethod.append(QString("  appParams.insert(\"%1\", QString::number(%2));\n")
                          .arg(field.getName())
                          .arg(field.getCamelCaseName()));
    else if (field.getLangType() == "QDateTime")
      publicMethod.append(QString("  appParams.insert(\"%1\", %2.toString(\"yyyy-MM-dd hh:mm:ss\"));\n")
                          .arg(field.getName())
                          .arg(field.getCamelCaseName()));
    else if (field.getLangType() == "bool")
      publicMethod.append(QString("  appParams.insert(\"%1\", %2? \"true\": \"false\");\n")
                          .arg(field.getName())
                          .arg(field.getCamelCaseName()));
    else if (field.getLangType() == "FileItem")
      publicMethod.append(QString("  fileParams.insert(\"%1\", %2);\n")
                          .arg(field.getName())
                          .arg(field.getCamelCaseName()));

    publicMethod.append("}\n\n");
  }

  QFile file("/home/sd44/RequestSrc.txt");
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << "fucking open RequestSrc.txt";
    exit(1);
  }
  QTextStream in(&file);
  in.setCodec("UTF-8");
  QString result = in.readAll()
      .arg(className)
      .arg(request.getName())
      .arg(publicMethod)
      .arg(request.getResponseClassName());

  return result;
}

QString CppQtSdkGenerator::getResponseHeaderFileName(const ApiResponse &response)
{
  return sourcesDir + "/response/" + response.getClassName() + ".h";
}


QString CppQtSdkGenerator::getResponseSourceFileName(const ApiResponse  &response)
{
  return sourcesDir + "/response/" + response.getClassName() + ".cpp";
}

QString CppQtSdkGenerator::getResponseHeader(const ApiResponse &response)
{
  ApiField field;

  QString filePre = response.getClassName().toUpper() + "_H";

  QStringList includeFiles;
  if (response.isContainDateField())
    includeFiles += "#include <QDateTime>\n";
  if (response.isContainListField())
    includeFiles += "#include <QList>\n";

  /**
   * @brief response类中method的字符串的组装
   **/
  QString publicMethod;

  /**
   * @brief request类中的私有字段的字符串组装
   **/
  QString privateField;

  QList<ApiField> responseFields  = response.getFields();
  foreach(field, responseFields) {
    QString includeResponseFile = (QString("#include <TaoApiCpp/domain/%1.h>\n")
                                   .arg(field.getLangType()));
    if (field.isObjectField() && !includeFiles.contains(includeResponseFile))
      includeFiles += includeResponseFile;

    if (privateField.size() > 0)
      privateField.append("\n");
    privateField.append(QString("/**\n"
                                " * @brief %1\n").arg(field.getDesc()));
    privateField.append(" **/\n");
    privateField.append(QString("  %1 %2;\n").arg(field.getDefineLangType())
                        .arg(field.getCamelCaseName()));

    publicMethod.append(QString("  %1 %2() const;\n").arg(field.getDefineLangType())
                        .arg(field.getGetMethodName()));

    publicMethod.append(QString("  void %1 (%2 %3);").arg(field.getSetMethodName())
                        .arg(field.getDefineLangType())
                        .arg(field.getCamelCaseName()));
  }

  QFile file("/home/sd44/ResponseHeader.txt");
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << "fucking open Response.txt";
    exit(1);
  }
  QTextStream in(&file);
  in.setCodec("UTF-8");

  QString result = in.readAll().arg(filePre).arg(includeFiles.join("")).arg(response.getDesc())
      .arg(response.getClassName())
      .arg(publicMethod).arg(privateField);
  return result;
}

QString CppQtSdkGenerator::getResponseSource(const ApiResponse &response)
{
  ApiField field;

  QString publicMethod;

  QString parseResponse;
  parseResponse = "  parseError();\n";

  QString className = response.getClassName();
  QList<ApiField> responseFields  = response.getFields();
  foreach(field, responseFields) {

    publicMethod.append(QString("%1 %2::%3() const {\n")
                        .arg(field.getDefineLangType())
                        .arg(className)
                        .arg(field.getGetMethodName()));
    publicMethod.append(QString("  return %1;\n").arg(field.getCamelCaseName()));
    publicMethod.append("}\n");

    publicMethod.append(QString("void %1::%2 (%3 %4) {\n")
                        .arg(className)
                        .arg(field.getSetMethodName())
                        .arg(field.getDefineLangType())
                        .arg(field.getCamelCaseName()));
    publicMethod.append(QString("  this->%1 = %1;\n").arg(field.getCamelCaseName()));
    publicMethod.append("}\n");

    parseResponse += generateParseResponse(field);
  }

  QFile file("/home/sd44/ResponseSrc.txt");
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << "fucking open ResponseSrc.txt";
    exit(1);
  }
  QTextStream in(&file);
  in.setCodec("UTF-8");

  QString result = in.readAll()
      .arg(className)
      .arg(publicMethod)
      .arg(parseResponse);
  return result;
}

QString CppQtSdkGenerator::generateParseResponse(const ApiField &field)
{
  QString elemname = field.getCamelCaseName();
  QString elemXmlName = field.getName();

  QString parseField = "  if (responseParser->hasName(\"%1\")) {\n  ";
  if (!field.isListField()) {
    if (field.getLangType() == "QString")
      parseField += elemname + " = responseParser->getStrByName(\"%1\");\n";
    else if (field.getLangType() == "qlonglong")
      parseField += elemname + " = responseParser->getNumByName(\"%1\");\n";
    else if (field.getLangType() == "bool")
      parseField += elemname + " = responseParser->getBoolByName(\"%1\");\n";
    else if (field.getLangType() == "QDateTime")
      parseField += elemname + " = responseParser->getDateByName(\"%1\");\n";
    else if (field.isObjectField()) {
      parseField += elemname + ".setParser(responseParser->getObjectParser(\"%1\"));\n";
      parseField += "  " + elemname + ".parseResponse();\n";
    }
  } else {
    if (field.getLangType() == "QString")
      parseField += elemname + " = responseParser->getListStrByName(\"%1\");\n";
    else if (field.getLangType() == "qlonglong")
      parseField += elemname + " = responseParser->getListNumByName(\"%1\");\n";
    else if (field.getLangType() == "bool")
      parseField += elemname + " = responseParser->getListBoolByName(\"%1\");\n";
    else if (field.getLangType() == "QDateTime")
      parseField += elemname + " = responseParser->getListDateByName(\"%1\");\n";
    else if (field.isObjectField()) {
      parseField += "QList<Parser *> listParser = responseParser->getListObjectParser(\"%1\");\n";
      parseField += "  Parser *parser;\n";
      parseField += "  foreach (parser, listParser) {\n";
      parseField += QString("    %1 tmp;\n").arg(field.getLangType());
      parseField += "    tmp.setParser(parser);\n";
      parseField += "    tmp.parseResponse();\n";
      parseField += "    " + elemname + ".append(tmp);\n";
      parseField += "  }\n";
    }
  }
  parseField += "  }\n";
  parseField = parseField.arg(elemXmlName);
  return parseField;
}
