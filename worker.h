#pragma once

#include <deque>
#include <thread>
#include <mutex>

#include <QObject>
#include <QDebug>
#include <QThread>

#include "data.h"

class Worker : public QObject
{
    Q_OBJECT
    friend class Controler;
    std::mutex mutex;    
public:
     Worker()= default;
    ~Worker() override = default;
    std::deque<Data> queueData = {};

    int workCount(){
        std::lock_guard<std::mutex> l{mutex};
        return queueData.size();
    }
public slots:
    void addWork(const Data &data){
        std::lock_guard<std::mutex> l{mutex};
        queueData.emplace_back(data); 
        qDebug() << queueData.size();
    }

    void doWork(){
        if(QThread::currentThread()->isInterruptionRequested()) return; 

        while(!queueData.empty())
        {
            auto const &_data=queueData.begin();
            qDebug()<< "doWork begin" << " value:"<< _data->Value;
            for(int i = 0 ; i < 5; ++i)
            {
                if(QThread::currentThread()->isInterruptionRequested()) return; 
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                qDebug()<< i;
                if(QThread::currentThread()->isInterruptionRequested()) return; 
            }
            qDebug()<< "doWork end";
            std::lock_guard<std::mutex> l{mutex};
            queueData.erase(queueData.begin());
        }
    }
};
