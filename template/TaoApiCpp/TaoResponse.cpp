#include <TaoApiCpp/TaoResponse.h>

void TaoResponse::parseResponse()
{
  parseError();
  parseNormalResponse();
}

void TaoResponse::parseError()
{
  if (responseParser->hasName("errorCode"))
    errorCode = responseParser->getStrByName("errorCode");
  if (responseParser->hasName("msg"))
    msg = responseParser->getStrByName("msg");
  if (responseParser->hasName("subCode"))
    msg = responseParser->getStrByName("subCode");
  if (responseParser->hasName("subMs"))
    msg = responseParser->getStrByName("subMsg");
}

#include <TaoApiCpp/TaoResponse.h>
