#ifndef  TAORESPONSE_INC
#define  TAORESPONSE_INC

#include <QString>
#include <TaoApiCpp/TaoParser.h>

class TaoResponse
{
 public:
  TaoResponse() {
    responseParser = NULL;
  }

  virtual ~TaoResponse() {
    if (responseParser != NULL)
      delete responseParser;
  }

  virtual void parseNormalResponse() = 0;

  void parseResponse();

  void setParser(Parser *parser) {
    responseParser = parser;
  }

  void parseError();

  QString getErrorCode() const {
    return errorCode;
  }
  void setErrorCode(const QString &errorCode) {
    this->errorCode = errorCode;
  }

  QString getMsg() const {
    return msg;
  }
  void setMsg(const QString &msg) {
    this->msg = msg;
  }

  QString getSubCode() const {
    return subCode;
  }
  void setSubCode(const QString &subCode) {
    this->subCode = subCode;
  }

  QString getSubMsg() const {
    return subMsg;
  }
  void setSubMsg(const QString &subMsg) {
    this->subMsg = subMsg;
  }

  bool isSuccess() {
    return errorCode.isEmpty() && subCode.isEmpty();
  }

  QString getTopForbiddenFields() const {
    return topForbiddenFields;
  }

  void setTopForbiddenFields(const QString &topForbiddenFields) {
    this->topForbiddenFields = topForbiddenFields;
  }

  Parser *responseParser;

 private:
  QString errorCode;
  QString msg;
  QString subCode;
  QString subMsg;
  QString topForbiddenFields;

};

#endif   /* ----- #ifndef TAORESPONSE_INC  ----- */
