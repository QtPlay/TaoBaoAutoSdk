#ifndef CPPQTSDKGENERATOR_H
#define CPPQTSDKGENERATOR_H

#include <generator/SdkGenerator.h>

/**
 * @todo getXXXSourceCode函数部份，为通过模板文件转换为实际代码。模板文件写的意义不清，为
 * 数字代替，使代码较为晦涩难懂。以后如有时间再更正为意义清晰的字符串。
 **/
class CppQtSdkGenerator : public SdkGenerator
{
public:
  CppQtSdkGenerator(SdkParser* parser);

protected:
  virtual QString getSdkBasicSourceDir();
  virtual QString getSdkVersionFilePath();

  virtual QString getDomainHeaderFileName(const ApiDomain &domain);
  virtual QString getDomainSourceFileName(const ApiDomain& domain);
  virtual QString getDomainHeader(const ApiDomain &domain);
  virtual QString getDomainSource(const ApiDomain& domain);

  virtual QString getRequestHeaderFileName(const ApiRequest &request);
  virtual QString getRequestSourceFileName(const ApiRequest &request);
  virtual QString getRequestHeader(const ApiRequest &request);
  virtual QString getRequestSource(const ApiRequest& request);

  virtual QString getResponseHeaderFileName(const ApiResponse &response);
  virtual QString getResponseSourceFileName(const ApiResponse &response);
  virtual QString getResponseHeader(const ApiResponse &response);
  virtual QString getResponseSource(const ApiResponse &response);

private:
  QString generateParseResponse(const ApiField &field);
};

#endif // CPPQTSDKGENERATOR_H
