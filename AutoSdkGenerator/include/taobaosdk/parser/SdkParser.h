#ifndef SDKPARSER_H
#define SDKPARSER_H

#include <domain/ApiDomain.h>
#include <domain/ApiRequest.h>
#include <domain/ApiResponse.h>

class SdkParser
{
public:
  virtual QList<ApiDomain> getApiDomains() = 0;
  virtual QList<ApiRequest> getApiRequests() = 0;
  virtual QList<ApiResponse> getApiResponses() = 0;
};

#endif // SDKPARSER_H
