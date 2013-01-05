#include <mapper/CppQtTypeMapper.h>
#include <generator/CppQtSdkGenerator.h>
#include <parser/MetaSdkParser.h>

int main(void)
{
  CppQtTypeMapper mapper;
  MetaSdkParser parser(&mapper, "/home/sd44/Tao.xml");
  CppQtSdkGenerator gen(&parser);
  gen.generate();
}
