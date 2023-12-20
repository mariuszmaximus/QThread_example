#ifndef WORKER_H
#define WORKER_H

#include <QObject>

#include <thread>
#include <QDebug>
#include <QThread>

#include "data.h"

class Worker : public QObject
{
    Q_OBJECT
public:
     Worker()= default;
    ~Worker() override = default;

//     bool stop{false};

public slots:
    void doWork(const Data &data){
        if(QThread::currentThread()->isInterruptionRequested()) return; // if(stop) return;

        qDebug()<< "doWork begin";
        for(int i = 0 ; i < 5; ++i)
        {
            if(QThread::currentThread()->isInterruptionRequested()) return; // if(stop) return;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            qDebug()<< i;
            if(QThread::currentThread()->isInterruptionRequested()) return; // if(stop) return;
        }
        qDebug()<< "doWork end";
    }

};

#endif // WORKER_H
