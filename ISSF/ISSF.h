#ifndef ISSF_H_
#define ISSF_H_

#include <stdio.h>
#include <QWidget>
#include <QDesktopWidget>
#include <QApplication>
#include <QTextBlock>
#include <QTextEdit>
#include <QTextBrowser>

#include "UI/SimplePushButton.h"
#include "UI/ProcessButtonsSegment.h"
#include "UI/FilterSegment.h"
#include "MainWindow.h"
#include "SharedMemoryClasses/SharedMemoryController.h"
#include "SharedMemoryClasses/Packet.h"
#include "ThreadControll/Thread.h"
#include "findname.h"
#include "Filter.h"

#define DEFAULT_WINDOW_HEIGHT 500
#define DEFAULT_WINDOW_WIDTH 500
//using namespace Ui;


class ISSFApplication: public QApplication{
      Q_OBJECT
private:

   MainWindow *main;
   SharedMemoryController *m_sharedMemory;
   QTextBrowser *m_PacketsCptrdField;
   Thread *m_workerThread;
   std::string m_interfaceName;
   NetworkInterface networkIf;
   pcap_t *m_dev;
   QTextBrowser *m_interfaces;
   QTextBrowser *m_packetsFullInfo;
   bool m_allowedToAdd = true;
   u_int m_AddedPackets;
   Filter *m_filter;

public:
    ISSFApplication(int &argc, char **argv);
    ~ISSFApplication();

    void run();
    SharedMemoryController* getSharedMemoryPtr();
    void emitPacketsAdded();
    pcap_t* openPcapInterface(const char *interface,u_int8_t ifType);


signals:
    void packetsAdded();

public slots:
    void onPacketsAdded();
    void onStartWorkerThread();
    void onStopWorkerThread();
    void onPauseWorkerThread();
    void onFilterApplied();
    void onInterfaceClicked();
    void onPacketSelected();
    void onOk();
    void onContinue();
};


#endif
