#include "keyboardhandler.h"
#include "settings/settings.h"
#include "settings/simulationsettings.h"

KeyboardHandler::KeyboardHandler(QObject *parent) :
    QObject(parent)
{
    setUpConnections();
}

KeyboardHandler::~KeyboardHandler()
{}

bool KeyboardHandler::eventFilter(QObject *object, QEvent *event)
{
    switch(event->type()){
    case QEvent::KeyPress:
        return handleKeyEvent(static_cast<QKeyEvent *>(event));
    default:
        return QObject::eventFilter(object, event);
    }
}

bool KeyboardHandler::handleKeyEvent(QKeyEvent *event)
{
    qDebug() << "KeyboardHandler::handleKeyEvent: Key Press: " << event->key();
    switch (event->key()) {
    case Qt::Key_A:
        //Fall through
    case Qt::Key_Space:
        freezeSimulation(event);
        break;
    case Qt::Key_S:
        stepSimulation(event);
    default:
        break;
    }
    return true;
}

void KeyboardHandler::freezeSimulation(QKeyEvent *event)
{
    emit toggleFrozen();
}

void KeyboardHandler::stepSimulation(QKeyEvent *event)
{
    emit step();
}

void KeyboardHandler::setUpConnections()
{
    connect(this, SIGNAL(toggleFrozen()),
            &Settings::simulation(), SLOT(onToggleFrozen()));
}

