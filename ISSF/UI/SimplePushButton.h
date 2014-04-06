#ifndef SIMPLE_PUSH_BUTTON_H_
#define SIMPLE_PUSH_BUTTON_H_

#include <QWidget>
#include <QPushButton>

#include "UI/Button.h"

class SimplePushButton: public Button{
private:
    //Q_OBJECT
    char *m_message;

public:
    SimplePushButton(char *message, char* text, QWidget *parent = 0, u_int8_t signalType = 0);
    ~SimplePushButton();

    void Initialization();


    void buttonAction();


};

#endif
