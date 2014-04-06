#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <QWidget>
#include <QApplication>
#include <QDesktopWidget>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <QVector>
#include <QPushButton>
#include <QTextEdit>
#include <QGridLayout>
#include <QTextBrowser>
#include <QSignalMapper>
#include <pcap.h>

#include "ISSF.h"


#include "MainWindow.h"
#include "UI/FilterSegment.h"
#include "SharedMemoryClasses/SharedMemoryController.h"
#include "SharedMemoryClasses/Packet.h"
#include "ThreadControll/Thread.h"
#include "findname.h"
#include "Filter.h"
#include "PcapLoop.h"


using namespace std;
//using namespace Ui;



ISSFApplication::ISSFApplication(int &argc, char **argv)
    :QApplication(argc,argv),m_allowedToAdd(true), m_AddedPackets(0),
      m_filter(new Filter())
{

    main = new MainWindow();
    main->setGeometry(200,200,500,600);
    main->show();


    //creating the filter segment
    QPushButton *apply = main->getApplyButton();
    QPushButton *interface = main->getInterfaceButton();
    m_PacketsCptrdField = main->getPacketsCptrdField();
    m_packetsFullInfo = main->getPacketsFullInfoField();

    m_sharedMemory = new SharedMemoryController();
    QPushButton *showFullInfo = main->getShowInfoButton();
    QPushButton *continueButton = main->getContinueButton();
    QVector<QPushButton*> *buttons = main->getProcessButtons();
    m_workerThread = new Thread(loopThread,m_dev,m_sharedMemory);

    m_sharedMemory->setInterface(ETHER_IF);

    connect(buttons->at(0),SIGNAL(clicked()),this,SLOT(onStartWorkerThread()));
    connect(buttons->at(2),SIGNAL(clicked()),this,SLOT(onStopWorkerThread()));
    connect(this,SIGNAL(packetsAdded()),this,SLOT(onPacketsAdded()));
    connect(apply,SIGNAL(clicked()),this,SLOT(onFilterApplied()));
    connect(interface,SIGNAL(clicked()),this,SLOT(onInterfaceClicked()));
    connect(showFullInfo,SIGNAL(clicked()),this,SLOT(onPacketSelected()));
    connect(continueButton,SIGNAL(clicked()),this,SLOT(onContinue()));

    qtApp = this;
}

ISSFApplication::~ISSFApplication(){

    delete m_sharedMemory;
    delete m_workerThread;
}

void ISSFApplication::run(){
    networkIf.findDevices();
    this->exec();
}

SharedMemoryController* ISSFApplication::getSharedMemoryPtr(){
    return m_sharedMemory;
}

void ISSFApplication::onPacketsAdded(){
    if(m_allowedToAdd){
        m_AddedPackets++;
        const Packet& packet = m_sharedMemory->getLatestPacket();


        stringstream sPacketStream;
        sPacketStream << m_AddedPackets << ". ";

        string packetInfo = sPacketStream.str();
        packetInfo += packet.AbridgedHeadersInfo();

        QString qEtherInfo(packetInfo.c_str());

        m_PacketsCptrdField->append(qEtherInfo);


    }
}


void ISSFApplication::emitPacketsAdded(){
    emit this->packetsAdded();
}

void ISSFApplication::onStartWorkerThread(){
    m_workerThread->start();
}

void ISSFApplication::onStopWorkerThread(){
    m_workerThread->stop();

    fstream logStream;
    logStream.open("./log.txt",fstream::out);
    logStream << m_PacketsCptrdField->document()->toPlainText().toUtf8().data();
    m_PacketsCptrdField->clear();
}

void ISSFApplication::onPauseWorkerThread(){
    m_workerThread->stop();
}

void ISSFApplication::onFilterApplied(){
    QTextEdit *filterField = main->getFilterField();
    QString filter = filterField->textCursor().currentFrame()->
                        document()->toPlainText();

    string filterToCompile = filter.toUtf8().data_ptr()->data();

    bpf_program *compiledFilter = m_filter->compileFilter(m_dev,filterToCompile);

    m_workerThread->stop();
    pcap_setfilter(m_dev,compiledFilter);
    m_workerThread->start();
}

void ISSFApplication::onInterfaceClicked(){
    QWidget *interfaceWindow = new QWidget();
    interfaceWindow->setGeometry(200,200,200,200);
    m_interfaces = new QTextBrowser(interfaceWindow);
    QPushButton *ok = new QPushButton(interfaceWindow);
    QPushButton *cancel = new QPushButton(interfaceWindow);

    ok->setText(*(new QString("Ok")));
    cancel->setText(*(new QString("Cancel")));

    QGridLayout *interfaceWindowLayout = new QGridLayout(interfaceWindow);
    QGridLayout *firstRowLayout = new QGridLayout(interfaceWindow);
    QGridLayout *secondRowLayout = new QGridLayout(interfaceWindow);

    interfaceWindowLayout->addLayout(firstRowLayout,1,1,1,1);
    interfaceWindowLayout->addLayout(secondRowLayout,2,1,1,1);



    firstRowLayout->addWidget(m_interfaces);
    secondRowLayout->addWidget(ok,1,1,1,1);
    secondRowLayout->addWidget(cancel,1,2,1,1);

    list<string>& interfaceList = networkIf.GetList();
    for(list<string>::iterator it = interfaceList.begin();
        it != interfaceList.end(); it++){
        QString pcapIf((*it).c_str());
        m_interfaces->append(pcapIf);
    }

    connect(ok,SIGNAL(clicked()),this,SLOT(onOk()));

    connect(cancel,SIGNAL(clicked()),interfaceWindow,SLOT(close()));
    interfaceWindow->show();
}



pcap_t* ISSFApplication::openPcapInterface(const char *interface, u_int8_t ifType){
    char errbuf[PCAP_ERRBUF_SIZE];

    pcap_t *pcap_device = NULL;
    memset(errbuf,0,PCAP_ERRBUF_SIZE);

    if(ifType == ETHER_IF){
        pcap_device = pcap_open_live(interface,PACKET_BUFFSIZE,0,0,errbuf);
        if(!pcap_device){
            fprintf(stderr,"Error in opening: %s",errbuf);
        }
    } else {
        /*pcap_device = pcap_open_live("wlan0",PACKET_BUFFSIZE,1,0,errbuf);
        if(!pcap_device){
                fprintf(stderr,"Error in opening: %s",errbuf);
        }*/
        pcap_device = pcap_create("wlan0",errbuf);


        pcap_set_rfmon(pcap_device,1);
        pcap_set_promisc(pcap_device,1);
        pcap_set_snaplen(pcap_device,PACKET_BUFFSIZE);
        pcap_set_timeout(pcap_device,0);
        pcap_activate(pcap_device);
    }


    return pcap_device;
}


void ISSFApplication::onOk(){
    if(m_workerThread->isStarted()){
        m_workerThread->stop();
        delete m_workerThread;

    }
    u_int8_t ifType = ETHER_IF;

    QString intfName = m_interfaces->textCursor().selectedText();
    m_interfaceName = string(intfName.toUtf8().constData());

    if(!strcmp(m_interfaceName.c_str(),"wlan0")){
        ifType = WLAN_IF;
    }

    m_dev = openPcapInterface(m_interfaceName.c_str(),ifType);
    m_sharedMemory->setInterface(ifType);
    m_workerThread = new Thread(loopThread,m_dev,m_sharedMemory);
    ((QWidget*)m_interfaces->parent())->close();



}


void ISSFApplication::onPacketSelected(){
    m_allowedToAdd = false;
    QString row = m_PacketsCptrdField->textCursor().selectedText();
    string temps;

    for(QString::iterator it = row.begin(); it != row.end();++it){
        if(*it!='.'){
            char digit = it->toLatin1();
            temps.append(&digit);
        } else {
            break;
        }
    }

    stringstream stemps(temps);
    u_int packetNum=0;
    stemps >> packetNum;
    const Packet& packet = m_sharedMemory->getPacket(packetNum-1);
    QString packetFullInfo = packet.HeadersInfo();

    m_packetsFullInfo->clear();
    m_packetsFullInfo->append(packetFullInfo);
}

void ISSFApplication::onContinue(){
    for(int i = m_AddedPackets;
           i < m_sharedMemory->getVectorSize(); i++){
        const Packet& packet = m_sharedMemory->getPacket(i-1);
        stringstream sPacketStream;
        sPacketStream << i << ". ";

        string packetInfo = sPacketStream.str();
        packetInfo += packet.AbridgedHeadersInfo();

        QString qEtherInfo(packetInfo.c_str());

        m_PacketsCptrdField->append(qEtherInfo);\

    }

    m_allowedToAdd = true;
}
