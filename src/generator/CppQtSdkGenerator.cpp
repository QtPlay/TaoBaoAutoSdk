/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2013  sea <email>

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
  return QString("/home/sd44/TaoApiCpp/TaoApiCpp");
}

QString CppQtSdkGenerator::getSdkVersionFilePath()
{
  return sourcesDir + "Constants.cpp";
}

QString CppQtSdkGenerator::getResponseSourceFileName(const ApiResponse  &response)
{
  return sourcesDir + "/response/" + response.getClassName() + ".h";
}

QString CppQtSdkGenerator::getResponseSourceCode(const ApiResponse &response)
{
  ApiField field;

  QString filePre = response.getClassName().toUpper() + "_H";

  /**
   * @brief request类中的私有字段的字符串组装
   *
   **/
  QString privateField;
  QList<ApiField> responseFields  = response.getFields();
  foreach(field, responseFields) {
    if (privateField.size() > 0)
      privateField.append("\n");
    privateField.append(QString("/**\n"
              " * @brief %1\n").arg(field.getDesc()));
    privateField.append(" **/\n");

    privateField.append(QString("  %1 %2;\n").arg(field.getDefineLangType("QList<", ">"))
                                  .arg(field.getCamelCaseName()));
  }

  /**
   * @brief response类中method的字符串的组装
   **/
  QString publicMethod;
  foreach(field, responseFields) {
    publicMethod.append(QString(" %1 %2() {\n").arg(field.getDefineLangType("QList<", ">"))
                                    .arg(field.getGetMethodName()));
    publicMethod.append(QString("    return %1;\n").arg(field.getCamelCaseName()));
    publicMethod.append("  }\n");

    publicMethod.append(QString("  void %1 (%2 %3) {\n").arg(field.getSetMethodName())
                                           .arg(field.getDefineLangType("QList<", ">"))
                                           .arg(field.getCamelCaseName()));
    publicMethod.append(QString("    this->%1 = %1;\n").arg(field.getCamelCaseName()));
    publicMethod.append("  }\n\n");
  }

  QString includeFiles;
  if (response.isContainDateField())
    includeFiles += "#include <QDateTime>\n";
  if (response.isContainListField())
    includeFiles += "#include <QList>\n";
  foreach(field, responseFields) {
    if (field.isObjectField())
      includeFiles.append(QString("#include <TaoApiCpp/domain/%1.h>\n").arg(field.getLangType()));
  }

  QFile file("/home/sd44/Response.txt");
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << "fucking open Response.txt";
    exit(1);
  }
  QTextStream in(&file);
  in.setCodec("UTF-8");

  QString result = in.readAll().arg(filePre).arg(includeFiles).arg(response.getDesc())
                               .arg(response.getClassName())
                               .arg(publicMethod).arg(privateField);
  return result;
}

QString CppQtSdkGenerator::getRequestSourceFileName(const ApiRequest &request)
{
  return sourcesDir + "/request/" + request.getRequestClassName() + ".h";
}

QString CppQtSdkGenerator::getRequestSourceCode(const ApiRequest& request)
{
  ApiField field;

  QString filePre = request.getRequestClassName().toUpper() + "_H";

  /**
   * @brief request类中的私有字段的字符串组装
   *
   **/
  QString privateField;
  QList<ApiField> requestFields  = request.getFields();
  foreach(field, requestFields) {
    if (privateField.size() > 0)
      privateField.append("\n");
    privateField.append(QString("/**\n"
              " * @brief %1\n").arg(field.getDesc()));
    privateField.append(" **/\n");

    privateField.append(QString("  %1 %2;\n").arg(field.getLangType())
                                  .arg(field.getCamelCaseName()));
  }

  /**
   * @brief request类中method的字符串的组装
   **/
  QString publicMethod;
  foreach(field, requestFields) {
    publicMethod.append(QString(" %1 %2() {\n").arg(field.getLangType())
                                    .arg(field.getGetMethodName()));
    publicMethod.append(QString("    return %1;\n").arg(field.getCamelCaseName()));
    publicMethod.append("  }\n");

    publicMethod.append(QString("  void %1 (%2 %3) {\n").arg(field.getSetMethodName())
                                           .arg(field.getLangType())
                                           .arg(field.getCamelCaseName()));
    publicMethod.append(QString("    this->%1 = %1;\n").arg(field.getCamelCaseName()));

    if (field.getLangType() == "QString")
      publicMethod.append(QString("    appParams.insert(\"%1\", %2);\n")
                          .arg(field.getName())
                          .arg(field.getCamelCaseName()));
    else if (field.getLangType() == "qlonglong")
      publicMethod.append(QString("    appParams.insert(\"%1\", QString::number(%2));\n")
                          .arg(field.getName())
                          .arg(field.getCamelCaseName()));
    else if (field.getLangType() == "QDateTime")
      publicMethod.append(QString("    appParams.insert(\"%1\", %2.toString(\"yyyy-MM-dd hh:mm:ss\"));\n")
                          .arg(field.getName())
                          .arg(field.getCamelCaseName()));
    else if (field.getLangType() == "bool")
      publicMethod.append(QString("    appParams.insert(\"%1\", %2? \"true\": \"false\");\n")
                          .arg(field.getName())
                          .arg(field.getCamelCaseName()));
    else if (field.getLangType() == "FileItem")
      publicMethod.append(QString("    fileParams.insert(\"%1\", %2)")
                          .arg(field.getName())
                          .arg(field.getCamelCaseName()));
    publicMethod.append("  }\n\n");
  }

  QFile file("/home/sd44/Request.txt");
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << "fucking open Request.txt";
    exit(1);
  }
  QTextStream in(&file);
  in.setCodec("UTF-8");

  QString result = in.readAll().arg(filePre).arg(request.getDesc())
                               .arg(request.getRequestClassName())
                               .arg(request.getName())
                               .arg(publicMethod).arg(request.getResponseClassName())
                               .arg(privateField);
  return result;
}

QString CppQtSdkGenerator::getDomainSourceFileName(const ApiDomain& domain)
{
  return sourcesDir + "/domain/" + domain.getClassName() + ".h";

}

/**
 * @brief ...
 *
 * @param domain ...
 * @return QString
 **/
QString CppQtSdkGenerator::getDomainSourceCode(const ApiDomain& domain)
{
  ApiField field;

  QString filePre = domain.getClassName().toUpper() + "_H";

  /**
   * @brief domain的私有字段的字符串组装
   *
   **/
  QString privateField;
  QList<ApiField> domainFields  = domain.getFields();
  foreach(field, domainFields) {
    if (privateField.size() > 0)
      privateField.append("\n");
    privateField.append(QString("/**\n"
              " * @brief %1\n").arg(field.getDesc()));
    if (field.isListField()) {
      privateField.append(QString(" * @ApiListField(\"%1\")\n").arg(field.getName()));
      privateField.append(QString(" * @ApiField(\"%1\")\n").arg(
        StringKit::toLowerWithUnderscore(field.getLangType())));
    } else
      privateField.append(QString(" * @ApiField(\"%1\")\n").arg(field.getName()));

    privateField.append(" **/\n");

    privateField.append(QString("  %1 %2;\n").arg(field.getDefineLangType("QList<", ">"))
                                  .arg(field.getCamelCaseName()));
  }

  /**
   * @brief domain类中method的字符串的组装
   **/
  QString publicMethod;
  foreach(field, domainFields) {
    if (publicMethod.size() > 0)
      publicMethod.append("\n");
    publicMethod.append(QString(" %1 %2() {\n").arg(field.getDefineLangType("QList<", ">"))
                                    .arg(field.getGetMethodName()));
    publicMethod.append(QString("    return %1;\n").arg(field.getCamelCaseName()));
    publicMethod.append("  }\n");

    publicMethod.append(QString("  void %1 (%2 %3) {\n").arg(field.getSetMethodName())
                                           .arg(field.getDefineLangType("QList<", ">"))
                                           .arg(field.getCamelCaseName()));
    publicMethod.append(QString("    this->%1 = %1;\n").arg(field.getCamelCaseName()));
    publicMethod.append("  }\n\n");
  }

  QString includeFiles;
  if (domain.isContainDateField())
    includeFiles += "#include <QDateTime>\n";
  if (domain.isContainListField())
    includeFiles += "#include <QList>\n";
  includeFiles += "#include <QString>\n";

  QFile file("/home/sd44/Domain.txt");
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << "fucking open Domain.txt";
    exit(1);
  }
  QTextStream in(&file);
  in.setCodec("UTF-8");

  QString result = in.readAll().arg(filePre).arg(includeFiles).arg(domain.getDesc())
                               .arg(domain.getClassName())
                               .arg(publicMethod).arg(privateField);
  return result;
}
