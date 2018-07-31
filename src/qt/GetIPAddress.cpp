QHostAddress GetIPAddress() {
  // Get a validate ip
  foreach (const QNetworkInterface &net_intf, QNetworkInterface::allInterfaces()) {
    QNetworkInterface::InterfaceFlags flags = net_intf.flags();
    if ((bool)(flags & QNetworkInterface::IsRunning) && \
        !(bool)(flags & QNetworkInterface::IsLoopBack)) {

      foreach (const QNetworkAddressEntry &address, net_intf.addressEntries()) {
        if (address.ip().protocol() == QAbstractSocket::IPv4Protocol) {
          return address.ip();
        }
      }
    }
  }
  return QHostAddress("127.0.0.1");
}
