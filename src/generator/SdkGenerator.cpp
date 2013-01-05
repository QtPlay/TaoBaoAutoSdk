/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2012  sea <email>

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


#include <generator/SdkGenerator.h>
#include <QDebug>
#include <QDate>

void SdkGenerator::writeFile(const QString &codeStr,const  QString & absoluteFilePath)
{
  QFile file(absoluteFilePath);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    qDebug() << QString("file: %1, write error.\n%2")
    .arg(absoluteFilePath).arg(file.errorString());
  QTextStream out(&file);
  out.setCodec("UTF-8");
  out << codeStr;
}


void SdkGenerator::generateSdkVersion()
{
  QFile outFile(getSdkVersionFilePath());
  if (!outFile.open(QIODevice::ReadOnly | QIODevice::Text))
    return;
  QByteArray fileContents = outFile.readAll();
  outFile.close();
  fileContents.replace("dynamicVersionNo",
                  QDate::currentDate().toString("yyyyMMdd").toUtf8());

  if (!outFile.open(QIODevice::WriteOnly | QIODevice::Truncate |
QIODevice::Text))
    return;
  outFile.write(fileContents);
  outFile.close();
}

void SdkGenerator::init() {
  // parse meta data
  domains = parser->getApiDomains();
  requests = parser->getApiRequests();
  responses = parser->getApiResponses();

}


void SdkGenerator::process()
{
  generateDomains();
  generateRequests();
  generateResponses();
  generateSdkVersion();
}

void SdkGenerator::generateDomains()
{
  foreach (ApiDomain domain, domains) {
    QString sourceCode = getDomainSourceCode(domain);
    QString domainFileName = getDomainSourceFileName(domain);
    writeFile(sourceCode, domainFileName);
  }
}

void SdkGenerator::generateRequests() {
  foreach (ApiRequest request ,requests) {
    QString sourceCode = getRequestSourceCode(request);
    QString requestFileName = getRequestSourceFileName(request);
    writeFile(sourceCode, requestFileName);
  }
}

void SdkGenerator::generateResponses() {
  foreach (ApiResponse response ,responses) {
    QString sourceCode = getResponseSourceCode(response);
    QString responseFileName = getResponseSourceFileName(response);
    writeFile(sourceCode, responseFileName);
  }
}
