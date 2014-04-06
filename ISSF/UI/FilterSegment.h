#ifndef FILTERSEGMENT_H
#define FILTERSEGMENT_H

#include <QString>
#include <QTextEdit>
#include <QWidget>
#include <QPushButton>



//this class is used to interact with the
//filter text edit field and the apply button
class FilterSegment: public QWidget{
private:
    Q_OBJECT

    QPushButton *m_applyButton;
    QString m_filterString;
    QTextEdit  *m_filterField;

private slots:
    void onApply();

signals:
    void apply();

public:
    FilterSegment(QWidget *parent = 0, QPushButton *apply = 0, QTextEdit *filterField = 0);
    ~FilterSegment();



};


#endif // FILTERSEGMENT_H
