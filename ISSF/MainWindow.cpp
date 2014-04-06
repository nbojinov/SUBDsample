#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QWidget>
#include <QPushButton>

//using namespace Ui

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    buttons = new QVector<QPushButton*>();
    buttons->push_back(ui->playButton);
    buttons->push_back(ui->pauseButton);
    buttons->push_back(ui->stopButton);

    applyButton = ui->applyButton;
    filterField = ui->filterField;
    m_packetsCptrdField = ui->packetsCptrd;
    m_packetFullInfoField = ui->packetInfo;
    interfaceButton = ui->Interface;

    showFullInfoButton = ui->m_ShowFullInfoButton;
    continueButton = ui->m_continueButton;


}

MainWindow::~MainWindow()
{
    delete ui;
}

