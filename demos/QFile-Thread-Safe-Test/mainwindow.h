#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTimer>
#include <QMutex>
#include <QMutexLocker>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onTimeout();


private:
    Ui::MainWindow *ui;
    QFile* m_file;
    QTimer m_timer;
    QThread* m_thread;
    QMutex* m_mutex;
};

#endif // MAINWINDOW_H
