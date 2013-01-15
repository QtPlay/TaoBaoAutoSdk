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

  QString qProperty;
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
    privateField.append(QString("  %1 %2;\n").arg(field.getDefineLangType("QList<", ">"))
                                  .arg(field.getCamelCaseName()));

    publicMethod.append(QString(" %1 %2() {\n").arg(field.getDefineLangType("QList<", ">"))
                                    .arg(field.getGetMethodName()));
    publicMethod.append(QString("    return %1;\n").arg(field.getCamelCaseName()));
    publicMethod.append("  }\n");

    publicMethod.append(QString("  void %1 (%2 %3) {\n").arg(field.getSetMethodName())
                                           .arg(field.getDefineLangType("QList<", ">"))
                                           .arg(field.getCamelCaseName()));
    publicMethod.append(QString("    this->%1 = %1;\n").arg(field.getCamelCaseName()));
    publicMethod.append("  }\n\n");

    qProperty += QString("  Q_PROPERTY(%1 %2 READ %3 WRITE %4)\n")
        .arg(field.isListField() ? "QList" : field.getLangType())
        .arg(field.getName())
        .arg(field.getGetMethodName())
        .arg(field.getSetMethodName());
  }


  QString declareMetaType = QString("Q_DECLARE_METATYPE(%1)\n").arg(response.getClassName());

  QFile file("/home/sd44/Response.txt");
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << "fucking open Response.txt";
    exit(1);
  }
  QTextStream in(&file);
  in.setCodec("UTF-8");

  QString result = in.readAll().arg(filePre).arg(includeFiles.join("")).arg(response.getDesc())
                               .arg(response.getClassName())
                               .arg(publicMethod).arg(privateField).arg(declareMetaType)
                               .arg(qProperty);
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
    privateField.append(QString("/**\n"
              " * @brief %1\n").arg(field.getDesc()));
    privateField.append(" **/\n");

    privateField.append(QString("  %1 %2;\n").arg(field.getLangType())
                                  .arg(field.getCamelCaseName()));

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

  QString qProperty;
  QList<ApiField> domainFields  = domain.getFields();
  foreach(field, domainFields) {
    if (privateField.size() > 0)
      privateField.append("\n");
    privateField.append(QString("/**\n"
              " * @brief %1\n").arg(field.getDesc()));
    privateField.append(" **/\n");

    privateField.append(QString("  %1 %2;\n").arg(field.getDefineLangType("QList<", ">"))
                                  .arg(field.getCamelCaseName()));

    QString otherIncludeFile = field.getLangType();
    QString includeDomainFile(QString("#include <TaoApiCpp/domain/%1.h>\n").arg(otherIncludeFile));
    if (!includeFiles.contains(includeDomainFile) && field.isObjectField())
//        otherIncludeFile != "QString" && otherIncludeFile != "qlonglong" &&
//        otherIncludeFile != "QDateTime" && otherIncludeFile != "bool"
//        && otherIncludeFile != "FileItem")
      includeFiles += includeDomainFile;


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

    qProperty += QString("  Q_PROPERTY(%1 %2 READ %3 WRITE %4)\n")
        .arg(field.isListField() ? "QList" : field.getDefineLangType("QList<", ">"))
        .arg(field.getName())
        .arg(field.getGetMethodName())
        .arg(field.getSetMethodName());
  }


  QFile file("/home/sd44/Domain.txt");
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << "fucking open Domain.txt";
    exit(1);
  }
  QTextStream in(&file);
  in.setCodec("UTF-8");

  QString declareMetaType = QString("Q_DECLARE_METATYPE(%1)\n").arg(domain.getClassName());
  QString result = in.readAll().arg(filePre).arg(includeFiles.join("")).arg(domain.getDesc())
                               .arg(domain.getClassName())
                               .arg(publicMethod).arg(privateField).arg(declareMetaType)
                               .arg(qProperty);
  return result;
}
