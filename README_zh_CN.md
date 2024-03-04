# qzmodem

qzmodem是一个Qt的ZModem协议实现，它不依赖于Qt之外的任何库，可以跨平台使用。代码在qt6.6上通过了测试，应该可以在其他版本的Qt上工作。

## 使用

在你的.pro文件中添加以下行：

```pro
include(qzmodem.pri)
```

然后你可以使用`QSendZmodem`和`QRecvZmodem`类来发送和接收文件。
