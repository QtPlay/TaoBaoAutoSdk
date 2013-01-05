FIND_PACKAGE(Qt4 REQUIRED QtXml)
SET(TaoBaoAutoSdk_INCLUDES ${CMAKE_SOURCE_DIR}/include/taobaosdk)
INCLUDE_DIRECTORIES(${QT_INCLUDES} ${TaoBaoAutoSdk_INCLUDES})

set(TaoBaoAutoSdk_SRCS
  SdkConstants.cpp
  util/StringKit.cpp
  generator/SdkGenerator.cpp
  domain/ApiField.cpp
  domain/BaseObject.cpp
  mapper/CppQtTypeMapper.cpp
  parser/MetaSdkParser.cpp
  generator/CppQtSdkGenerator.cpp
  )

qt4_automoc(${TaoBaoAutoSdk_SRCS})
ADD_LIBRARY(TaoBaoAutoSdk SHARED ${TaoBaoAutoSdk_SRCS})
target_link_libraries(TaoBaoAutoSdk ${QT_QTCORE_LIBRARY} ${QT_QTXML_LIBRARY})
set_target_properties(TaoBaoAutoSdk PROPERTIES
  VERSION ${${PROJECT}_VERSION}
  SOVERSION ${${PROJECT}_SOVERSION}
  )
add_executable(testQtDomain main.cpp ${TaoBaoAutoSdk_SRCS})
target_link_libraries(testQtDomain ${QT_QTCORE_LIBRARY} ${QT_QTXML_LIBRARY})

INSTALL(TARGETS TaoBaoAutoSdk
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

INSTALL(DIRECTORY ${TaoBaoAutoSdk_INCLUDES} DESTINATION include)
