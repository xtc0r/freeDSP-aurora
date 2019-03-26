#include <math.h>

#include <QDebug>
#include <QFile>
#include <QMessageBox>


#include <cstdint>
#include <cstring>

#include "freeDSP-Aurora.hpp"

extern QString wifiIpHost;
extern int wifiPortHost;

//==============================================================================
/*! Constructor
 *
 */
CFreeDspAurora::CFreeDspAurora( QWidget* parent ) : QWidget( parent )
{
  tcpSocket = new QTcpSocket( this );
  connect( tcpSocket, SIGNAL( readyRead()), this, SLOT(readyReadWifi()) );
  connect( this, SIGNAL( haveReplyWifi() ), &loopWaitForResponseWiFi, SLOT( quit() ) );
}

//==============================================================================
/*! Destructor
 *
 */
CFreeDspAurora::~CFreeDspAurora( void )
{

}

//==============================================================================
/*!
 *
 */
#if 0
bool CFreeDspAurora::sendByteSecured( char* txbyte )
{
  qDebug()<<"TX:"<<"0x" + QString::number( static_cast<uint32_t>(*txbyte), 16 );

  if( !isOpen )
    return false;

//#if !defined( __IOS__ )
  const qint64 bytesWritten = serialBT.write( txbyte, 1 );
  if (bytesWritten == -1)
  {
    qDebug()<<"Failed to write the data"<<serialBT.errorString();
    return false;
  }
  else if( bytesWritten != 1 )
  {
    qDebug()<<"Failed to write all the data"<<serialBT.errorString();
    return false;
  }
  else if( !serialBT.waitForBytesWritten() )
  {
    qDebug()<<"Operation timed out or an error occurred"<<serialBT.errorString();
    return false;
  }

  serialBT.waitForReadyRead();
  QByteArray rxData = serialBT.readAll();
  char rxByte = rxData[0];
  //qDebug()<<"RX:"<<"0x" + QString::number( ((int)rxByte & 0xFF), 16 );

  if( *txbyte != rxByte )
  {
    qDebug()<<"[ERROR] Received wrong byte. Connection seems corrupted.";
    return false;
  }

  return true;
}
#endif

//==============================================================================
/*!
 *
 */
#if 0
bool CFreeDspAurora::sendByteSecured( byte txbyte )
{
  qDebug()<<"TX:"<<"0x" + QString::number( static_cast<uint32_t>(txbyte), 16 );

  if( !isOpen )
    return false;

//#if !defined( __IOS__ )
  const qint64 bytesWritten = serialBT.write( &txbyte, 1 );
  if (bytesWritten == -1)
  {
    qDebug()<<"Failed to write the data"<<serialBT.errorString();
    return false;
  }
  else if( bytesWritten != 1 )
  {
    qDebug()<<"Failed to write all the data"<<serialBT.errorString();
    return false;
  }
  else if( !serialBT.waitForBytesWritten() )
  {
    qDebug()<<"Operation timed out or an error occurred"<<serialBT.errorString();
    return false;
  }

  serialBT.waitForReadyRead();
  QByteArray rxData = serialBT.readAll();
  char rxByte = rxData[0];
  //qDebug()<<"RX:"<<"0x" + QString::number( ((int)rxByte & 0xFF), 16 );

  if( txbyte != rxByte )
  {
    qDebug()<<"[ERROR] Received wrong byte. Connection seems corrupted.";
    return false;
  }

  return true;

}
#endif

//==============================================================================
/*!
 *
 */
bool CFreeDspAurora::open( const QString portname )
{
  isOpen = false;
#if 0
  #if !defined( DEMO )
  //----------------------------------------------------------------------------
  //--- Open the serial port Bluetooth device
  //----------------------------------------------------------------------------
  serialBT.setPortName( portname );
  serialBT.open( QIODevice::ReadWrite );
  serialBT.setBaudRate( QSerialPort::Baud115200 );
  serialBT.setDataBits( QSerialPort::Data8 );
  serialBT.setParity( QSerialPort::NoParity );
  serialBT.setStopBits( QSerialPort::OneStop );
  serialBT.setFlowControl( QSerialPort::NoFlowControl );
  if( !serialBT.isOpen() )
  {
    if( !serialBT.open( QIODevice::ReadWrite ) )
    {
      qDebug()<<"Failed to open serial port"<<serialBT.errorString();
      return false;
    }
  }
  qDebug()<<"Opened serial port freeDSP-Aurora";
  isOpen = true;
  #endif
#endif
  return true;
}

//==============================================================================
/*!
 *
 */
void CFreeDspAurora::close( void )
{
  isOpen = false;
#if 0
  #if !defined( DEMO )
  serialBT.close();
  #endif
#endif
}

//==============================================================================
/*!
 *
 */
bool CFreeDspAurora::sendParameter( uint16_t reg, float val )
{
  qDebug()<<"---------------------------------------------------------------";
  qDebug()<<"sendParameter()";
#if 0
  char cmd = PARAM;
  if( !sendByteSecured( &cmd ) )
    return false;

/*  uint32_t numbytes = 6;
  qDebug()<<"Bytes: "<<numbytes;

  if( !sendByteSecured( (numbytes >> 24) & 0xFF ) )
    return false;
  if( !sendByteSecured( (numbytes >> 16) & 0xFF ) )
    return false;
  if( !sendByteSecured( (numbytes >> 8) & 0xFF ) )
    return false;
  if( !sendByteSecured( numbytes & 0xFF ) )
    return false;
*/

  if( !sendByteSecured( (reg >> 8) & 0xFF ) )
    return false;
  if( !sendByteSecured( reg & 0xFF ) )
    return false;

  uint32_t data;
  std::memcpy( &data, &val, sizeof(float) );
  if( !sendByteSecured( (data >> 24) & 0xFF ) )
    return false;
  if( !sendByteSecured( (data >> 16) & 0xFF ) )
    return false;
  if( !sendByteSecured( (data >> 8) & 0xFF ) )
    return false;
  if( !sendByteSecured( data & 0xFF ) )
    return false;
#endif
  return true;
}

//==============================================================================
/*!
 *
 */
bool CFreeDspAurora::sendParameter( uint16_t reg, uint32_t val )
{
  qDebug()<<"---------------------------------------------------------------";
  qDebug()<<"sendParameter()";
#if 0
  char cmd = PARAM;
  if( !sendByteSecured( &cmd ) )
    return false;

/*  uint32_t numbytes = 6;
  qDebug()<<"Bytes: "<<numbytes;

  if( !sendByteSecured( (numbytes >> 24) & 0xFF ) )
    return false;
  if( !sendByteSecured( (numbytes >> 16) & 0xFF ) )
    return false;
  if( !sendByteSecured( (numbytes >> 8) & 0xFF ) )
    return false;
  if( !sendByteSecured( numbytes & 0xFF ) )
    return false;
*/

  if( !sendByteSecured( (reg >> 8) & 0xFF ) )
    return false;
  if( !sendByteSecured( reg & 0xFF ) )
    return false;

  uint32_t data = val;
  //std::memcpy( &data, &val, sizeof(float) );
  if( !sendByteSecured( (data >> 24) & 0xFF ) )
    return false;
  if( !sendByteSecured( (data >> 16) & 0xFF ) )
    return false;
  if( !sendByteSecured( (data >> 8) & 0xFF ) )
    return false;
  if( !sendByteSecured( data & 0xFF ) )
    return false;
#endif
  return true;
}

//==============================================================================
/*!
 *
 */
bool CFreeDspAurora::storeRegAddr( uint16_t reg )
{
#if 0
  if( !sendByteSecured( static_cast<byte>((reg >> 8) & 0xFF) ) )
    return false;
  if( !sendByteSecured( static_cast<byte>(reg & 0xFF) ) )
    return false;
 #endif
  return true;
}

//==============================================================================
/*!
 *
 */
bool CFreeDspAurora::storeValue( float val )
{
#if 0
  uint32_t data;
  std::memcpy( &data, &val, sizeof(float) );
  if( !sendByteSecured( static_cast<byte>((data >> 24) & 0xFF) ) )
    return false;
  if( !sendByteSecured( static_cast<byte>((data >> 16) & 0xFF) ) )
    return false;
  if( !sendByteSecured( static_cast<byte>((data >> 8) & 0xFF) ) )
    return false;
  if( !sendByteSecured( static_cast<byte>(data & 0xFF) ) )
    return false;
#endif
  return true;
}

//==============================================================================
/*!
 *
 */
bool CFreeDspAurora::storeValue( uint32_t val )
{
#if 0
  uint32_t data = val;
  if( !sendByteSecured( static_cast<byte>((data >> 24) & 0xFF) ) )
    return false;
  if( !sendByteSecured( static_cast<byte>((data >> 16) & 0xFF) ) )
    return false;
  if( !sendByteSecured( static_cast<byte>((data >> 8) & 0xFF) ) )
    return false;
  if( !sendByteSecured( static_cast<byte>(data & 0xFF) ) )
    return false;
#endif
  return true;
}

#if 0
//==============================================================================
/*!
 *
 */
bool CFreeDspAurora::beginStoreParams( uint32_t numbytes )
{
  qDebug()<<"---------------------------------------------------------------";
  qDebug()<<"beginStoreParams()";

  char cmd = SAVEPARAMS;
  if( !sendByteSecured( &cmd ) )
    return false;

  if( !sendByteSecured( (numbytes >> 24) & 0xFF ) )
    return false;
  if( !sendByteSecured( (numbytes >> 16) & 0xFF ) )
    return false;
  if( !sendByteSecured( (numbytes >> 8) & 0xFF ) )
    return false;
  if( !sendByteSecured( numbytes & 0xFF ) )
    return false;
  return true;
}
#endif

uint32_t convertTo824( double val )
{
  double fractpart, intpart;
  uint32_t ret;
  fractpart = modf( val, &intpart );
  if( intpart > 127.0 )
    intpart = 127.0;
  if( intpart < -128.0 )
    intpart = -128.0;

  if( fractpart < 0 )
    fractpart *= -1.0;
  
  
  intpart = floor( val );
  fractpart = val - intpart;
  
  ret = (((static_cast<int8_t>(intpart))<<24) & 0xff000000)
      + ((static_cast<uint32_t>(fractpart * 16777216.0)) & 0x00ffffff);

  return ret;
}


//==============================================================================
/*!
 *
 */
QByteArray CFreeDspAurora::makeParameterForWifi( uint16_t reg, double val )
{
  QByteArray content;
  content.append( (reg >> 8) & 0xFF );
  content.append( reg & 0xFF );

  uint32_t data = convertTo824( val );

  content.append( (data >> 24) & 0xFF );
  content.append( (data >> 16) & 0xFF );
  content.append( (data >> 8) & 0xFF );
  content.append( data & 0xFF );

  qDebug()<<content.toHex();
  
  return content;
}

//==============================================================================
/*!
 *
 */
bool CFreeDspAurora::sendParameterWifi( QByteArray content )
{
  qDebug()<<"---------------------------------------------------------------";
  qDebug()<<"sendParameterWifi()";

  tcpSocket->abort();
  tcpSocket->connectToHost( wifiIpHost, wifiPortHost );

  QEventLoop loopConnect;
  connect( tcpSocket, SIGNAL(connected()), &loopConnect, SLOT(quit()) );
  // \TODO Add timeout timer
  #warning Add timeout timer
  //connect(timeoutTimer, SIGNAL(timeout()), &loop, SLOT(quit()));
  loopConnect.exec();

  QString requestString = QString("PUT /param HTTP/1.1\r\nHost: ")
                        + wifiIpHost
                        + QString("\r\nContent-type:application/octet-stream\r\nContent-length: ")
                        + QString::number( content.size()*2 )
                        + QString("\r\n\r\n");
  QByteArray request;
  request.append( requestString );
  request.append( content.toHex() );  
  request.append( "\r\n" );
  
  qDebug()<<QString( request );
  tcpSocket->write( request );

  QEventLoop loopDisconnect;
  connect( tcpSocket, SIGNAL(disconnected()), &loopDisconnect, SLOT(quit()) );
  // \TODO Add timeout timer
  #warning Add timeout timer
  //connect(timeoutTimer, SIGNAL(timeout()), &loop, SLOT(quit()));
  loopDisconnect.exec();

  return true;
}

//==============================================================================
/*! Starts the transfer of a new dsp firmware block.
 *
 * \param content First block of firmware.
 */
bool CFreeDspAurora::sendDspFirmwareWifi( QByteArray content )
{
  bool ret = false;

  qDebug()<<"---------------------------------------------------------------";
  qDebug()<<"sendDspFirmwareWifi()";

  tcpSocket->abort();
  tcpSocket->connectToHost( wifiIpHost, wifiPortHost );

  QEventLoop loopConnect;
  connect( tcpSocket, SIGNAL(connected()), &loopConnect, SLOT(quit()) );
  // \TODO Add timeout timer
  #warning Add timeout timer
  //connect(timeoutTimer, SIGNAL(timeout()), &loop, SLOT(quit()));
  loopConnect.exec();

  QString requestString = QString("PUT /dspfw HTTP/1.1\r\nHost: ")
                        + wifiIpHost
                        + QString("\r\nContent-type:application/octet-stream\r\nContent-length: ")
                        + QString::number( content.size()*2 )
                        + QString("\r\n\r\n");
  QByteArray request;
  request.append( requestString );
  request.append( content.toHex() );  
  request.append( "\r\n" );
  
  qDebug()<<QString( request );
  tcpSocket->write( request );

  //ret = waitForAckWifi();
  //tcpSocket->abort();

  QEventLoop loopDisconnect;
  connect( tcpSocket, SIGNAL(disconnected()), &loopDisconnect, SLOT(quit()) );
  // \TODO Add timeout timer
  #warning Add timeout timer
  //connect(timeoutTimer, SIGNAL(timeout()), &loop, SLOT(quit()));
  loopDisconnect.exec();

  return ret;
}

//==============================================================================
/*! Finishes the transfer of a new dsp firmware.
 *
 */
bool CFreeDspAurora::finishDspFirmwareWifi( uint32_t totalTransmittedBytes )
{
  qDebug()<<"---------------------------------------------------------------";
  qDebug()<<"finishDspFirmwareWifi";

  tcpSocket->abort();
  tcpSocket->connectToHost( wifiIpHost, wifiPortHost );

  QEventLoop loopConnect;
  connect( tcpSocket, SIGNAL(connected()), &loopConnect, SLOT(quit()) );
  // \TODO Add timeout timer
  #warning Add timeout timer
  //connect(timeoutTimer, SIGNAL(timeout()), &loop, SLOT(quit()));
  loopConnect.exec();

  QString requestString = QString("GET /finishdspfw HTTP/1.1\r\nHost: ")
                        + wifiIpHost
                        + QString("\r\n\r\n");
  QByteArray request;
  request.append( requestString );
  
  qDebug()<<QString( request );
  tcpSocket->write( request );

  QEventLoop loopWaitForAck;
  connect( tcpSocket, SIGNAL(readyRead()), &loopWaitForAck, SLOT(quit()) );
  // \TODO Add timeout timer
  #warning Add timeout timer
  loopWaitForAck.exec();

  QByteArray reply;
  reply.append( tcpSocket->readAll() );
  qDebug()<<QString( reply );
  QStringList listReply = QString( reply ).split( QRegExp("\\s+") );

  uint32_t totalReceivedBytes = listReply.at(4).toUInt();
  qDebug()<<totalTransmittedBytes<<totalReceivedBytes;

/*  tcpSocket->abort();

  QEventLoop loopDisconnect;
  connect( tcpSocket, SIGNAL(disconnected()), &loopDisconnect, SLOT(quit()) );
  // \TODO Add timeout timer
  #warning Add timeout timer
  //connect(timeoutTimer, SIGNAL(timeout()), &loop, SLOT(quit()));
  loopDisconnect.exec();
*/

  if( totalTransmittedBytes == totalReceivedBytes )
    return true;
  else
    return false;
}

//==============================================================================
/*! Waits for an ACK from WiFi connection.
 *
 */
bool CFreeDspAurora::waitForAckWifi( void )
{
  QEventLoop loopWaitForAck;
  connect( tcpSocket, SIGNAL(readyRead()), &loopWaitForAck, SLOT(quit()) );
  loopWaitForAck.exec();

  QByteArray reply;
  reply.append( tcpSocket->readAll() );
  qDebug()<<QString( reply );

  QStringList listReply = QString( reply ).split( QRegExp("\\s+") );
  if( listReply.at(4) == QString("ACK") )
    return true;
  else
  {
    qDebug()<<"No ACK received"<<listReply.at(4);
    return false;
  }
}

//==============================================================================
/*! Requests the PID of current installed DSP-Plugin
 *
 */
uint32_t CFreeDspAurora::requestPidWifi( void )
{
  qDebug()<<"---------------------------------------------------------------";
  qDebug()<<"requestPidWifi";

  QString requestString = QString("GET /pid HTTP/1.1\r\nHost: ")
                        + wifiIpHost
                        + QString("\r\n\r\n");
  QByteArray request;
  request.append( requestString );

  writeRequestWifi( request );
  waitForResponseWifi();

  //! \TODO Check for valid reply

  QStringList listReply = QString( replyDSP ).split( QRegExp("\\s+") );
  uint32_t pid = 0;
  if( listReply.size() > 4 )
    pid = listReply.at(4).toUInt();
  
  qDebug()<<pid;

  return pid;
}

//==============================================================================
/*! Starts the transfer of a user data block.
 *
 * \param content Data block of user data.
 */
bool CFreeDspAurora::sendUserParameterWifi( QByteArray content )
{
  bool ret = false;

  qDebug()<<"---------------------------------------------------------------";
  qDebug()<<"sendUserParameterWifi()";

  tcpSocket->abort();
  tcpSocket->connectToHost( wifiIpHost, wifiPortHost );

  QEventLoop loopConnect;
  connect( tcpSocket, SIGNAL(connected()), &loopConnect, SLOT(quit()) );
  // \TODO Add timeout timer
  #warning Add timeout timer
  //connect(timeoutTimer, SIGNAL(timeout()), &loop, SLOT(quit()));
  loopConnect.exec();

  QString requestString = QString("PUT /userparam HTTP/1.1\r\nHost: ")
                        + wifiIpHost
                        + QString("\r\nContent-type:application/octet-stream\r\nContent-length: ")
                        + QString::number( content.size()*2 )
                        + QString("\r\n\r\n");
  QByteArray request;
  request.append( requestString );
  request.append( content.toHex() );  
  request.append( "\r\n" );
  
  qDebug()<<QString( request );
  tcpSocket->write( request );

  //ret = waitForAckWifi();
  //tcpSocket->abort();

  QEventLoop loopDisconnect;
  connect( tcpSocket, SIGNAL(disconnected()), &loopDisconnect, SLOT(quit()) );
  // \TODO Add timeout timer
  #warning Add timeout timer
  //connect(timeoutTimer, SIGNAL(timeout()), &loop, SLOT(quit()));
  loopDisconnect.exec();

  return ret;
}

//==============================================================================
/*! Finishes the transfer of user parameter file.
 *
 */
bool CFreeDspAurora::finishUserParameterWifi( uint32_t totalTransmittedBytes )
{
  qDebug()<<"---------------------------------------------------------------";
  qDebug()<<"finishUserParameterWifi";

  QString requestString = QString("GET /finishuserparam HTTP/1.1\r\nHost: ")
                        + wifiIpHost
                        + QString("\r\n\r\n");
  QByteArray request;
  request.append( requestString );
  
  writeRequestWifi( request );

  if( !waitForResponseWifi() )
  {
    QMessageBox::critical( this, tr("Error"), tr("Could not finish transfer of user parameter file. Please double check everything, reset DSP and try again."), QMessageBox::Ok ); 
    return false;
  }
  else
  {
    qDebug()<<QString( replyDSP );
    QStringList listReply = QString( replyDSP ).split( QRegExp("\\s+") );
    uint32_t totalReceivedBytes = listReply.at(4).toUInt();

    if( totalTransmittedBytes == totalReceivedBytes )
      return true;
    else
      return false;
  }
}

//==============================================================================
/*! Request the user parameter file.
 *
 */
bool CFreeDspAurora::requestUserParameterWifi( QByteArray& userparams )
{
  qDebug()<<"---------------------------------------------------------------";
  qDebug()<<"receiveUserParameterWifi";

  uint32_t totalBytes = 0;

  QString requestString = QString("GET /sizeuserparam HTTP/1.1\r\nHost: ")
                        + wifiIpHost
                        + QString("\r\n\r\n");
  QByteArray request;
  request.append( requestString );

  writeRequestWifi( request );
  if( !waitForResponseWifi() )
  {
    QMessageBox::critical( this, tr("Error"), tr("Could not receive the size of the user parameter file. Please double check everything and try again."), QMessageBox::Ok ); 
    return false;
  }
  else
  {
    qDebug()<<QString( replyDSP );
    QStringList listReply = QString( replyDSP ).split( QRegExp("\\s+") );
    totalBytes = listReply.at(4).toUInt();

    if( totalBytes > 0 )
    {
      requestString = QString("GET /userparam HTTP/1.1\r\nHost: ")
                    + wifiIpHost
                    + QString("\r\n\r\n");
      request.clear();
      request.append( requestString );
      writeRequestWifi( request );
      if( !waitForResponseWifi() )
      {
        QMessageBox::critical( this, tr("Error"), tr("Could not receive the user parameter file. Please double check everything and try again."), QMessageBox::Ok ); 
        return false;
      }
      else
      {
        listReply = QString( replyDSP ).split( QRegExp("\\s+") );
        qDebug()<<"Received user parameter"<<listReply.at(4).size();
        QString str = listReply.at(4);
        int offset = 0;
        
        while( offset < str.length() )
        {
          bool ok;
          uint8_t val = str.mid( offset, 2 ).toUInt( &ok, 16 );
          userparams.append( val );
          //qDebug()<<QString::number( val, 16 )<<str.mid( offset, 2 );
          offset += 2;
        }
      }
    }
  }  

  qDebug()<<"Done";
  qDebug()<<"Received: "<<userparams.size()<<"/"<<totalBytes;

  if( userparams.size() < totalBytes )
  {
    QMessageBox::critical( this, tr("Error"), tr("Could not receive all bytes of the user parameter file. Please double check all connections and reset all devices and try again."), QMessageBox::Ok ); 
    return false;
  }

  return true;
}

//==============================================================================
/*! Wait for reply of DSP via WiFi.
 *
 */
void CFreeDspAurora::waitForReplyWifi( void )
{
  QEventLoop loopWaitForReply;
  connect( tcpSocket, SIGNAL(readyRead()), &loopWaitForReply, SLOT(quit()) );
  // \TODO Add timeout timer
  #warning Add timeout timer
  loopWaitForReply.exec();
}

//==============================================================================
/*! 
 *
 */
bool CFreeDspAurora::waitForResponseWifi( void )
{
  #warning Add timeout timer
  loopWaitForResponseWiFi.exec();
  //! \TODO Check for valid response
  //! \TOOD Disconnect after transfer?
  return true;
}

//==============================================================================
/*!
 */
void CFreeDspAurora::readyReadWifi( void )
{
  replyWifi.append( tcpSocket->readAll() );
  qDebug()<<"readyReadWifi "<<QString( replyWifi );
  QString str = QString( replyWifi );
  QStringList listReply = str.split( QRegExp("\\s+") );
  qDebug()<<str.mid( str.length()-2, 2 );
  if( (listReply.size() > 4) && (str.mid( str.length()-2, 2 ) == QString("\r\n")) )
  {
    qDebug()<<"Reply complete";
    replyDSP = replyWifi;
    replyWifi.clear();
    emit haveReplyWifi();
  }
}

//==============================================================================
/*!
 */
void CFreeDspAurora::writeRequestWifi( QByteArray& request )
{
  tcpSocket->abort();
  tcpSocket->connectToHost( wifiIpHost, wifiPortHost );

  QEventLoop loopConnect;
  connect( tcpSocket, SIGNAL(connected()), &loopConnect, SLOT(quit()) );
  // \TODO Add timeout timer
  #warning Add timeout timer
  //connect(timeoutTimer, SIGNAL(timeout()), &loop, SLOT(quit()));
  loopConnect.exec();

  replyWifi.clear();
  qDebug()<<QString( request );
  tcpSocket->write( request );
}


