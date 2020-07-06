#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include <QDebug>

static int count = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_file = new QFile("1.txt");
    m_file->open(QFile::WriteOnly);

    m_timer.setInterval(3);
    m_timer.start();
    connect(&m_timer, &QTimer::timeout, this, &MainWindow::onTimeout);

    m_mutex = new QMutex;

    m_thread = QThread::create([this](){
        while(true) {
            count++;
            QString data = QString("this is a msg[%1] thread[%2]\n")
                    .arg(count).arg((int)(QThread::currentThreadId()));
            QByteArray dataA = data.toUtf8();

            {
                //QMutexLocker locker(m_mutex);
                m_file->write(dataA, dataA.length());
                m_file->flush();
            }
            //qDebug() << "QThread::create create create create->" << data;

            QThread::msleep(300);
        }

    });
    m_thread->start();
}

MainWindow::~MainWindow()
{
    m_file->close();
    delete ui;
}

void MainWindow::onTimeout()
{
    count++;
    QString data = QString("this is a msg[%1] thread[%2]\n")
            .arg(count).arg((int)(QThread::currentThreadId()));
    QByteArray dataA = data.toUtf8();

    {
        //QMutexLocker locker(m_mutex);
        m_file->write(dataA, dataA.length());
        m_file->flush();
    }

    //qDebug() << "QThread::onTimeout->" << data;
}
