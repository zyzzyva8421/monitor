#ifndef KEYBOARD_CONTEXT_H
#define KEYBOARD_CONTEXT_H
#include <QtGui/QInputContext>

#include "keyboard.h"

class Keyboard;

class KeyboardContext : public QInputContext
{
    Q_OBJECT

public:
    KeyboardContext();
    ~KeyboardContext();

    bool filterEvent(const QEvent* event);

    QString identifierName();
    QString language();

    bool isComposing() const;

    void reset();

    void showKeyboard();

private slots:
    void sendKey(QString str);

private:
    void updatePosition();

private:
    Keyboard *keyboard;
};

#endif // KEYBOARD_CONTEXT_H
