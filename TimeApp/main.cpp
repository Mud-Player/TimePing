#include "pingtool.h"
#include <configcenter.h>
#include <scheduler.h>
#include <QApplication>
#include <QCommandLineParser>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Schduler System and Callbacks
    Scheduler s;
    s.startDDS(ConfigCenter::ddsID());


    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addPositionalArgument("server", "exec as server");
    parser.process(a);
    if(parser.positionalArguments().contains("server")) {
        s.startUDP(SERVER_PORT);
        new ServerPing(&s);
    }
    else { //client
        s.startUDP(CLIENT_PORT);
        new ClientPing(&s);
    }
    //

    return a.exec();
}
