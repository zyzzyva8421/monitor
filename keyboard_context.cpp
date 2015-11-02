#include <QtCore>
#include <QApplication>

#include "keyboard_context.h".h"
#include <iostream>

KeyboardContext::KeyboardContext()
{
    keyboard = new Keyboard;
    connect(keyboard, SIGNAL(keyGenerated(QString)), SLOT(sendKey(QString)));
}

KeyboardContext::~KeyboardContext()
{
    delete keyboard;
}

void KeyboardContext::showKeyboard()
{
    updatePosition();
    keyboard->show();
}

bool KeyboardContext::filterEvent(const QEvent* event)
{
    if (event->type() == QEvent::RequestSoftwareInputPanel) {
        showKeyboard();
        return true;
//    } else if (event->type() == QEvent::CloseSoftwareInputPanel) {
 //       keyboard->hide();
 //       return true;
    }
    return false;
}

QString KeyboardContext::identifierName()
{
    return "KeyboardContext";
}

void KeyboardContext::reset()
{
}

bool KeyboardContext::isComposing() const
{
    return false;
}

QString KeyboardContext::language()
{
    return "en_US";
}

void KeyboardContext::sendKey(QString str)
{
    QPointer<QWidget> w = keyboard->getLastFocusedWidget();

    if (!w)
        return;

    int key;
    QString text = QString();
    Qt::KeyboardModifiers modifiers = Qt::NoModifier;
    if (str == QString("space")) {
        key = Qt::Key_Space;
        text = QString(" ");
    } else if (str == QString("backspace")) {
        key = Qt::Key_Backspace;
    } else {
        key = str[0].unicode();
        if (keyboard->getIsCapsLock()) {
             text = str.toUpper();
             modifiers = Qt::ShiftModifier;
        } else {
            text = str.toLower();
        }
    }

    QKeyEvent keyPress(QEvent::KeyPress, key, modifiers, text);
    QApplication::sendEvent(w, &keyPress);

    if (!w)
        return;
    if (str != QString("backspace")) {
        QKeyEvent keyRelease(QEvent::KeyPress, key, modifiers,QString());
        QApplication::sendEvent(w, &keyRelease);
    }
}


void KeyboardContext::updatePosition()
{
    QWidget *widget = focusWidget();
    if (!widget)
        return;

    QRect widgetRect = widget->rect();
    QPoint panelPos = QPoint(widgetRect.left(), widgetRect.bottom() + 2);
    panelPos = widget->mapToGlobal(panelPos);
    keyboard->move(panelPos);
}
