#include <domain/ApiField.h>

bool operator<(const ApiField &field1, const ApiField &field2) {
  return field1.getName() < field2.getName();
}

bool operator==(const ApiField &field1, const ApiField &field2) {
  return field1.getName() == field2.getName();
}

bool operator!=(const ApiField &field1, const ApiField &field2) {
  return !(field1 == field2);
}

