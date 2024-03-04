# qzmodem

qzmodem is a ZModem protocol implementation for Qt, which does not rely on any library other than Qt and can be used across platforms.

## Usage

Add the following line to your .pro file:

```pro
include(qzmodem.pri)
```

Then you can use the `QSendZmodem` and `QReceiveZmodem` classes to send and receive files.
