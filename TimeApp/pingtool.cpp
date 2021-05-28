#include "pingtool.h"
#include <QDateTime>


ServerPing::ServerPing(Scheduler *schd) : Callback(schd)
{
    setObjectName("ServerPing");
    registerDDS("DDSReply");
    registerUDP(0xBB);
    connect(&m_ddsTimer, &QTimer::timeout, this, &ServerPing::sendDDS);
    connect(&m_ntpTimer, &QTimer::timeout, this, &ServerPing::sendNTP);
    m_ntpTimer.start(5000);
    m_ddsTimer.start(5000);
}

void ServerPing::apply(const DDSDatagram &datagram)
{
    Q_UNUSED(datagram)
    m_ddsReply.append(QDateTime::currentMSecsSinceEpoch());
    if(m_ddsReply.size() < 2)
        return;

    qDebug() << "DDS : " << m_ddsReply.last() - m_ddsReply.first();
}

void ServerPing::apply(const QByteArray &datagram)
{
    auto reply = reinterpret_cast<const NTPReply*>(datagram.data());
    m_ntpReply.append(reply->time);
    if(m_ntpReply.size() < 2)
        return;

    qDebug() << "NTP : " << m_ntpReply.last() - m_ntpReply.first();
}

void ServerPing::sendNTP()
{
    m_ntpReply.clear();
    NTPReq req;
    QByteArray data((char*)&req, sizeof(req));
    scheduler()->getUDPNetwork()->writeDatagram(data, QHostAddress::Broadcast, CLIENT_PORT);
}

void ServerPing::sendDDS()
{
    m_ddsReply.clear();
    DDSReq req;
    QByteArray data((char*)&req, sizeof(req));
    scheduler()->getDDSNetwork()->write("DDSReq", data.data(), data.size());
}

ClientPing::ClientPing(Scheduler *schd) : Callback(schd)
{
    setObjectName("ClientPing");
    registerDDS("DDSReq");
    registerUDP(0xAA);
}

void ClientPing::apply(const DDSDatagram &datagram)
{
    Q_UNUSED(datagram)
    DDSReply reply;
    QByteArray data((char*)&reply, sizeof(reply));
    scheduler()->getDDSNetwork()->write("DDSReply", data.data(), data.size());
}

void ClientPing::apply(const QByteArray &datagram)
{
    Q_UNUSED(datagram)
    NTPReply reply;
    reply.time = QDateTime::currentMSecsSinceEpoch();
    QByteArray data((char*)&reply, sizeof(reply));
    scheduler()->getUDPNetwork()->writeDatagram(data, QHostAddress::Broadcast, SERVER_PORT);
}
