
#include <QWidget>
#include <QWindow>
#include <QApplication>
#include <QPushButton>
#include <QList>
#include <QVector>
#include <stdio.h>
#include <cstring>


#include "UI/ProcessButtonsSegment.h"
#include "UI/SimplePushButton.h"



// TODO :unknown error, find what causes "undefined reference to vtable"
PBSegment::PBSegment(QWidget *parent, QVector<QPushButton*> *buttons)
:QWidget(parent)
{


    if(buttons->size() < 3){
        throw new PBSegmentException();
    }

    play = buttons->at(0);
    pause = buttons->at(1);
    stop = buttons->at(2);

    connect(play,SIGNAL(clicked()),this,SLOT(playMsgRecieved()));
    connect(pause,SIGNAL(clicked()),this,SLOT(pauseMsgRecieved()));
    connect(stop,SIGNAL(clicked()),this,SLOT(stopMsgRecieved()));
}


void PBSegment::playMsgRecieved(){

}

void PBSegment::pauseMsgRecieved(){
}

void PBSegment::stopMsgRecieved(){}
