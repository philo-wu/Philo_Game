#pragma once

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QMutex>
#include <QMutexLocker>
#include <QQueue>

#include "Common.h"


template<typename T>
class ThreadSafeQueue
{
public:
    void enqueue(const T& value) {
        QMutexLocker locker(&m_mutex);
        m_queue.enqueue(value);
    }

    T dequeue() {
        QMutexLocker locker(&m_mutex);
        if (m_queue.isEmpty()) {
            return T();
        }
        return m_queue.dequeue();
    }
    bool isEmpty() const {
        QMutexLocker locker(&m_mutex);
        return m_queue.isEmpty();
    }

private:
    QQueue<T> m_queue;
    mutable QMutex m_mutex;
};

// @緩衝區
class EventThread : public QThread
{
    Q_OBJECT
public:
    EventThread(QObject* parent = nullptr)
        : QThread(parent)
    {
        m_queue = new ThreadSafeQueue<QPair<QTcpSocket*, QByteArray>>();
    }
    void addEvent( QTcpSocket* socket,  QByteArray packet) {
        // 將事件加入到事件隊列
        m_queue->enqueue({socket, packet });
    }
    ~EventThread()
    {
        delete m_queue;
    }
public slots:
    void ThreadFinish()
    {
        working = 0;
    }

protected:
    bool working = 0;
    void run() override {
        while (true) {
            if (!m_queue->isEmpty() && !working) {
                auto event = m_queue->dequeue();
                working = 1;
                // 因QTCPsocket 無法跨Thread呼叫或使用,故由第二條Thread儲存及管理,
                // 待MainThread 有空閒時才通知MainThread進行下一件事情
                emit writeDataToSocket(event.first, event.second);
            }
        }
    }
signals:
    void writeDataToSocket(QTcpSocket* socket , QByteArray packet);

private:
    ThreadSafeQueue<QPair<QTcpSocket*, QByteArray >> *m_queue;
};
