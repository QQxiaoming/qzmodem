# qzmodem

qzmodem is a ZModem protocol implementation for Qt, which does not rely on any library other than Qt and can be used across platforms.The code passed the test on qt6.6, and it should work on other versions of Qt.

## Usage

Add the following line to your .pro file:

```pro
include(qzmodem.pri)
```

Then you can use the `QSendZmodem` and `QRecvZmodem` classes to send and receive files.
