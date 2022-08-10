#include "mainwindow.h"
#include "drawer.h"
#include <QHBoxLayout>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setCentralWidget(new QWidget);
    this->setFixedWidth(120);
    this->setMinimumHeight(360);
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);

    drawer = new Drawer();
    drawer->LoadCfgFile(":/res/tools.json");
    QHBoxLayout* layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(drawer);

    this->centralWidget()->setLayout(layout);

    QFile fp(":/res/style/stylesheet.qss");
    if (fp.open(QIODevice::ReadOnly))
    {
        this->setStyleSheet(fp.readAll());
        fp.close();
    }
}

MainWindow::~MainWindow()
{
}

