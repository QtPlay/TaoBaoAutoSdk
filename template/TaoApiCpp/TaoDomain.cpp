#include "TaoDomain.h"

TaoDomain::TaoDomain()
{
  responseParser = NULL;
}

TaoDomain::~TaoDomain()
{
  if (responseParser != NULL)
    delete responseParser;
}
