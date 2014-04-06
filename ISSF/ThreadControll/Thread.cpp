#include <iostream>
#include <stdio.h>
#include <boost/thread.hpp>
#include <pcap.h>
#include <QtWidgets>

#include "ThreadControll/Thread.h"


Thread::Thread(void (*workerFunction)(pcap_t *dev,SharedMemoryController *shMem),pcap_t *dev,SharedMemoryController *shMem)
    :m_dev(dev), m_sharedMemory(shMem), m_method(workerFunction), m_workerThread(NULL)
{
    connect(this,SIGNAL(startThread()),this,SLOT(onStartThread()));
    connect(this,SIGNAL(stopThread()),this,SLOT(onStopThread()));
}

Thread::~Thread(){
    delete m_workerThread;
}

void Thread::start(){
    m_started = true;
    emit this->startThread();
}

void Thread::stop(){
    m_started = false;
    emit this->stopThread();
}

void Thread::onStartThread(){
    if(!m_workerThread)
        m_workerThread = new boost::thread(m_method,m_dev,m_sharedMemory);
}


void Thread::onStopThread(){
    if(m_workerThread)
        m_workerThread->interrupt();
    delete m_workerThread;
    m_workerThread = NULL;
}

bool Thread::isStarted(){
    return m_started;
}

