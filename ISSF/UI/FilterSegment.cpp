#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QString>
#include <QTextStream>
#include <stdio.h>


#include "UI/FilterSegment.h"


FilterSegment::FilterSegment(QWidget *parent, QPushButton *apply, QTextEdit *filterField)
    :QWidget(parent),m_applyButton(apply),m_filterField(filterField)
{
    m_filterString.clear();
    connect(m_applyButton,SIGNAL(clicked()),this,SLOT(onApply()));
}

FilterSegment::~FilterSegment(){
    m_applyButton = 0;
    m_filterField = 0;
}

void FilterSegment::onApply(){
    m_filterString += m_filterField->toPlainText();
    /*
     * -implement a way to set the string in a shared memory buffer between the qt and the
     * pcap thread
     *
     */


    // for now I'm only testing if I can get the string from the field
    QTextStream out(stdout);


    //it works
}
