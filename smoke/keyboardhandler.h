#ifndef KEYBOARDHANDLER_H
#define KEYBOARDHANDLER_H

#include <QObject>
#include <QEvent>
#include <QKeyEvent>

#include <QDebug>

class KeyboardHandler : public QObject
{
    Q_OBJECT
public:
    explicit KeyboardHandler(QObject *parent = 0);
    ~KeyboardHandler();

signals:
    void toggleFrozen();
    void step();

public slots:

private:
    bool eventFilter(QObject *object, QEvent *event);

    bool handleKeyEvent(QKeyEvent *event);
    void handleSpaceBar(QKeyEvent * event);
    void handleS(QKeyEvent * event);

    void setUpConnections();
};

#endif // KEYBOARDHANDLER_H
