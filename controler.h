#pragma once

#include <QObject>
#include <QThread>
#include <QDebug>
#include <deque>
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

    void addWork(const Data&d) { 
        worker->addWork(d); // dodaje do listy porcje danych do synchronizacji uzyty std::lock_guard<std::mutex> 
        emit onWorkAdded(); // wysylam sygnal aby robota ruszyła  
    };

    int workCount(){
        return worker->workCount();
    }
private:
    Controler(QObject *parent = nullptr):worker(new Worker) 
    {
        worker->moveToThread(&workerThread);
        connect(this, &Controler::onWorkAdded, worker, &Worker::doWork);
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
        workerThread.requestInterruption(); 
        workerThread.quit();
        workerThread.wait();
        qDebug()<<"stopAndWait end";
    }
signals:
    void onWorkAdded();
};


