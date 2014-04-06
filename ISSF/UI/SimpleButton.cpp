#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <stdio.h>
#include <cstring>

#include "SimplePushButton.h"


SimplePushButton::SimplePushButton(char *message, char *text, QWidget *parent, u_int8_t signalType)
:Button(text, parent),m_message(message)
{}


SimplePushButton::~SimplePushButton(){
}


void SimplePushButton::Initialization(){
    m_button = new QPushButton(m_buttonText,this);
    m_button->setGeometry(400,400,40,20);

    QWidget *parent = this->parentWidget();

    connect(m_button, SIGNAL(clicked()),parent,SLOT(this->close()));

}

void SimplePushButton::buttonAction(){

}



