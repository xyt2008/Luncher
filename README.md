# Luncher
客户端更新程序，包括服务器端和客户端两个版本

## 传输协议
1. 协议类型
	- Push：向对方发送信息
	- Pull：从对方获取信息
2. 信息类型
	- File：文件类型
	- Data：纯数据信息
3. 参数信息
	- Value：类型值信息：文件：文件名；数据：数据名
	- ContentLength：发送内容长度
4. 结束符
	- \r\n：每个信息的结束符，包头信息为在加一个为：\r\n\r\n

## 更新列表格式
采用xml文件存储更新文件的列表，格式如下：
```xml
<?xml version="1.0" encoding="UTF-8"?>
<app version="1.0.0">
    <files>
        <file>
           <name>文件1.txt</name>
           <size>12598</size>
           <md5>0ca168b9c0f726a235d895e269332461</md5>
        </file>
    </files>
</app>
```
