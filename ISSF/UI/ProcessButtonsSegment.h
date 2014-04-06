#pragma

#ifndef PB_SEGMENT_H_
#define PB_SEGMENT_H_

#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QList>

#include "Button.h"



//this class holds the process buttons: start, pause, stop

class PBSegmentException{};


/* TODO:
*   - implement the signal
*   - implement message receiving slots
*   - implement positioning
*/


class PBSegment: public QWidget{
private:
    Q_OBJECT
    QPushButton *play;
    QPushButton *pause;
    QPushButton *stop;

    typedef enum ButtonType{
        Play = 0x01,
        Pause = 0x02,
        Stop = 0x04
    } ButtonType;




public slots:
    void playMsgRecieved();
    void pauseMsgRecieved();
    void stopMsgRecieved();

public:
    PBSegment(QWidget *parent=0,QVector<QPushButton*> *buttons = 0);
    ~PBSegment(){

    }


};



#endif

