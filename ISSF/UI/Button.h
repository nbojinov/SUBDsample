#ifndef BUTTON_H_
#define BUTTON_H_

#include <QWidget>
#include <QApplication>
#include <QPushButton>


class Button: public QWidget{
protected:
    char *m_buttonText;
    QPushButton *m_button;
public:
    Button(char *text,QWidget *parent = 0)
    :QWidget(parent),m_buttonText(text)
    {}

    virtual void buttonAction() = 0;


};



#endif
