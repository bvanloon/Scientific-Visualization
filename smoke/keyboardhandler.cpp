#include "keyboardhandler.h"

KeyboardHandler::KeyboardHandler(QObject *parent) :
    QObject(parent)
{}

KeyboardHandler::~KeyboardHandler()
{}

bool KeyboardHandler::eventFilter(QObject *object, QEvent *event)
{
    qDebug() << "KeyboardHandler::eventFilter(QObject *object, QEvent *event)";
    switch(event->type()){
    case QEvent::KeyPress:
        return handleEvent(static_cast<QKeyEvent *>(event));
    default:
        return QObject::eventFilter(object, event);
    }
}

bool KeyboardHandler::handleEvent(QKeyEvent *event)
{
    qDebug() << event;
}

