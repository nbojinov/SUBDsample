#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QPushButton>
#include <QTextEdit>
#include <QTextBrowser>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QVector<QPushButton*>* getProcessButtons(){
        return buttons;
    }

    QPushButton* getApplyButton(){
        return applyButton;
    }

    QTextEdit* getFilterField(){
        return filterField;
    }

    QTextBrowser* getPacketsCptrdField(){
        return m_packetsCptrdField;
    }

    QTextBrowser* getPacketsFullInfoField(){
        return m_packetFullInfoField;
    }

    QPushButton* getInterfaceButton(){
        return interfaceButton;
    }

    QPushButton* getShowInfoButton(){
        return showFullInfoButton;
    }

    QPushButton* getContinueButton(){
        return continueButton;
    }

private:
    Ui::MainWindow *ui;
    QVector<QPushButton*> *buttons;

    QPushButton *applyButton;
    QPushButton *interfaceButton;
    QPushButton *showFullInfoButton;
    QPushButton *continueButton;

    QTextEdit *filterField;
    QTextBrowser *m_packetsCptrdField;
    QTextBrowser *m_packetFullInfoField;
};



#endif // MAINWINDOW_H
