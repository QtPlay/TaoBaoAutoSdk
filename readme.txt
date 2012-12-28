尚未完成，还有很多框架要做，请关注。。。
如果愿意参加本项目，请email我， sd44sd44@yeah.net


起因：本来只想简单的做个根据淘宝URL，从中抽取ID，然后通过商品ID获取商品信息的小东东。
越做越大，变成想做
1, C++的淘宝OPENAPI调用SDK。。。因为涉及很多我不知道的知识，例如JSON/XML/HTTP，可以很好的学习。
为方便起见，采用Qt4或5中的非界面库，如类STL容器，QFILE，QXML，QJSON等。
2，因为1，找文档过程中发现淘宝有JAVA/PHP/NET/PYTHON SDK自动生成工具，所以也想做一个淘宝SDK自动生成工具C++/QT版，并通过这个自动生成工具生成我的C++/Qt TaoBaoSdk。


淘宝的OPENAPI调用开放，遵守REST规范，通过URL进行请求和获取数据，
其中相应的JAVA/PHP/PYTHON/NET SDK是由其SDK自动生成工具根据OPENAPI的METADATA元数据来自动生成的。
使极为庞大，数量极多，并且OPENAPI的变动更新不会导致代码的重复修改，可以瞬间生成各种语言的SDK。当然，前提是各种语言的淘宝基础构件已经在AUTOSDK工具中搭建完成。


OPENAPI调用方式的文档在：
http://open.taobao.com/doc/category_list.htm?spm=0.0.0.71.E4HqCC&id=32

自动生成SDK，是在OPENAPI中极少见的，也是淘宝较为自豪的，但其没有开放自动SDK生成工具。
有一个疑似官方老版本的用JAVA实现的SDK生成工具：
https://code.google.com/p/tbtop/

依赖的metadata.xml 在以下链接的metadata sdk下载链接
http://api.taobao.com/myresources/standardSdk.htm?spm=0.0.0.177.vK5A3d

想尽可能的按照几个SDK中功能最全的JAVA SDK来实现。（官方python sdk只是发送请求，对返回的XML或JSON数据直接显示，不做处理）
目前只实现了：
1, http(s)Request基类，封装用户请求的参数，用MD5或HMAC-MD5签名。
2, metadata.xml的解析准备这几天用XQuery来完成，基于Qt库。
