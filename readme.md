README： 淘宝ApiMetadata.xml解析并自动生成SDK工具，基于C++/Qt
==========

简介:
----------
根据metadata数据自动生成各语言SDK，是在OPENAPI中极少见的，也是淘宝较为自豪的，
但其并没有开放自动SDK生成工具与相关文档。

本库移植自tbtop，疑似淘宝官方老版本的AutoSdk生成工具（工具使用JAVA语言实现）。
https://code.google.com/p/tbtop/
并做了一些优化与调整，使之适应当前的淘宝OpenApi并有较高效率。

淘宝OpenApi说明：
----------
淘宝的OpenApi调用开放，遵守REST规范，通过URL进行请求和获取数据，
其中相应的JAVA/PHP/PYTHON/NET SDK是由其SDK自动生成工具根据OPENAPI的METADATA元数据来自动生成的。
使极为庞大，数量极多，并且OPENAPI的变动更新不会导致代码的重复修改，可以瞬间生成各种语言的SDK。当然，前提是各种语言的淘宝基础构件已经在AUTOSDK工具中搭建完成。

OPENAPI调用方式的文档在：
http://open.taobao.com/doc/category_list.htm?spm=0.0.0.71.E4HqCC&id=32

依赖的metadata.xml 在以下链接的metadata sdk下载链接
http://api.taobao.com/myresources/standardSdk.htm

联系我：
----------
sd44sd44@yeah.net
