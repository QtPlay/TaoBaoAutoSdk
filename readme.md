README： 淘宝ApiMetadata.xml解析并自动生成SDK工具，基于C++/Qt
==========

简介:
----------
TaobaoAutoSdk为一个淘宝SDK的生成器框架，使用Qt/C++开发，其数据来源于淘宝官方所提供的metadata xml，采用GNU GPLV2+协议发放。

在此框架基础上，可以生成各种语言的SDK，前提是有模板以及相应模板生成方法。

具体示例可以参考本项目中自带的Qt C++的Taobao Sdk生成器。可供学习研究。

本库移植自tbtop，疑似淘宝官方老版本的AutoSdk生成工具（工具使用JAVA语言实现）。
https://code.google.com/p/tbtop/
并做了一些优化与调整，使之适应当前的淘宝OpenApi并有较高效率。

相关文档
----------
http://sd44.github.com/TaoBaoAutoSdk

C++/Qt SDK所需文件
----------
见template目录，存有ApiMetadata.xml，相应模板txt文件，以及C++/Qt的基础文件。
需要修改本项目中CppQtSdkGenerator.cpp中相应的路径。
成品代码见 https://github.com/sd44/TaobaoCppQtSDK

淘宝OpenApi说明：
----------
淘宝的OpenApi调用开放，遵守REST规范，通过URL进行请求和获取数据，

其中官方的JAVA/PHP/PYTHON/NET SDK是由其SDK自动生成工具根据OPENAPI的METADATA元数据来自动生成的。
使极为庞大，数量极多，并且OPENAPI的变动更新不会导致代码的重复修改，可以瞬间生成各种语言的SDK。

但是淘宝并没有直接开放相应的自动生成器。所以我做了这个软件，主要是为学习研究。


OPENAPI调用方式的文档在：https://www.google.com/search?client=ubuntu&channel=fs&q=github+remote+origin+url&ie=utf-8&oe=utf-8
http://open.taobao.com/doc/category_list.htm?spm=0.0.0.71.E4HqCC&id=32

依赖的metadata.xml 在以下链接的metadata sdk下载链接
http://api.taobao.com/myresources/standardSdk.htm

TODO列表：
----------
1，没有解析metadata Request请求参数中的Required检测以及上限/下限的检测。如果想加入的话大概半小时就能完成。因意义不大，本软件估计也没几个人用(汗。。)，所以暂时不做。


联系我：
----------
sd44sd44@yeah.net
irc.freenode.net #qt-cn
