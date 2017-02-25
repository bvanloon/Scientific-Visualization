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

public slots:

private:
    bool eventFilter(QObject *object, QEvent *event);
    bool handleEvent(QKeyEvent *event);
};

#endif // KEYBOARDHANDLER_H
