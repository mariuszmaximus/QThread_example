#ifndef CONTROLER_H
#define CONTROLER_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include "data.h"

#include "worker.h"

class Controler : public QObject
{
    Q_OBJECT

    Worker *worker{nullptr};
    QThread workerThread;
public:
    // Prevents any type of copy or new instance
    Controler(const Controler&) = delete;
    void operator=(const Controler&) = delete;

    // singleton Controler&
    static Controler& Get()
    {
        static Controler instance;
        return instance;
    }
private:
    Controler(QObject *parent = nullptr)
    {
        worker = new Worker;
        worker->moveToThread(&workerThread);
        connect(this, &Controler::addWork, worker, &Worker::doWork);
        workerThread.start();
    }

    ~Controler()
    {
        stopAndWait();
    }
private:
    void stopAndWait()
    {
        qDebug()<<"stopAndWait begin";
        workerThread.requestInterruption(); //   worker->stop=true;

        workerThread.quit();
        workerThread.wait();

        // workerThread.wait();
        qDebug()<<"stopAndWait end";
    }
signals:
    void addWork(const Data&);
};

#endif // CONTROLER_H
