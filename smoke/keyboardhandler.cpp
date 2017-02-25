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
        return handleEvent(static_cast<QKeyEvent *>(event));
    default:
        return QObject::eventFilter(object, event);
    }
}

bool KeyboardHandler::handleEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_A:
        //Fall through
    case Qt::Key_Space:
        handleSpaceBar(event);
        break;
    default:
        break;
    }
    return true;
}

void KeyboardHandler::handleSpaceBar(QKeyEvent *event)
{
    emit toggleFrozen();
}

void KeyboardHandler::setUpConnections()
{
    connect(this, SIGNAL(toggleFrozen()),
            &Settings::simulation(), SLOT(onToggleFrozen()));
}

