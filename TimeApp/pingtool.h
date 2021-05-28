#ifndef PINGTOOL_H
#define PINGTOOL_H

#include <scheduler.h>
#include <QTimer>


#define SERVER_PORT 6001
#define CLIENT_PORT 6002
struct NTPReq {
    int flag = 0xAA;
};

struct NTPReply {
    int    flag = 0xBB;
    qint64 time;
};

/// TOPIC: DDSReq
struct DDSReq {
    char reserve;
};

/// TOPIC: DDSReply
struct DDSReply {
    char reserve;
};


/*
 * 服务器发送一个UDP包和一个DDS包，
 * 然后客户端分别发送UDP应答包（带自己NTP时间)和DDS应答包
 * 计算多个UDP包之间时间差异和DDS时间差异
 * 为方便计算只有两个客户端和一个服务器
 */

class ServerPing : public Callback
{
    Q_OBJECT
public:
    ServerPing(Scheduler *schd);
private:
    virtual void apply(const DDSDatagram &datagram) override;
    virtual void apply(const QByteArray &datagram) override;
    //
    void sendNTP();
    void sendDDS();

private:
    QTimer m_ntpTimer;
    QTimer m_ddsTimer;
    QList<qint64> m_ntpReply;
    QList<qint64> m_ddsReply;
};

class ClientPing : public Callback
{
    Q_OBJECT
public:
    ClientPing(Scheduler *schd);
private:
    virtual void apply(const DDSDatagram &datagram) override;
    virtual void apply(const QByteArray &datagram) override;

private:
    int m_number;
};
#endif // PINGTOOL_H
