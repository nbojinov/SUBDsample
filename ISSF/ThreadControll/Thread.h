#ifndef THREAD_H_
#define THREAD_H_

#include <boost/thread.hpp>
#include <pcap.h>
#include <QThread>
#include "SharedMemoryClasses/SharedMemoryController.h"



//this class deals with thread creation and synchronization
class Thread: public QObject{
Q_OBJECT
private:
    typedef void (*workerMethod)(pcap_t *dev, SharedMemoryController *app);
    boost::thread *m_workerThread;
    SharedMemoryController *m_sharedMemory;
    workerMethod m_method;
    pcap_t *m_dev;
    bool m_started;
public:
    Thread(void (workerFunction)(pcap_t *dev, SharedMemoryController *shMem),pcap_t *dev, SharedMemoryController *shMem);
    ~Thread();

    void start();
    void stop();

    bool isStarted();

public slots:
    void onStartThread();
    void onStopThread();

signals:
    void startThread();
    void stopThread();
};


#endif

