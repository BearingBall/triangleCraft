#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSurfaceFormat format;
    format.setSamples(16);
    format.setVersion(3,3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    ui->openGLWidget->setFormat(format);
    ui->openGLWidget->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

