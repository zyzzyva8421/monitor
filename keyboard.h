#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QWidget>
#include<QSignalMapper>
#include <QPushButton>

namespace Ui {
class Keyboard;
}

class Keyboard : public QWidget
{
    Q_OBJECT
    
public:
    explicit Keyboard(QWidget *parent = 0);
    ~Keyboard();
    bool getIsCapsLock() {return isCapsLock;}
    QWidget* getLastFocusedWidget() {return lastFocusedWidget;}

signals:
    void keyGenerated(QString str);

protected:
    bool event(QEvent *e);

private slots:
    void saveFocusWidget(QWidget *oldFocus, QWidget *newFocus);
    void buttonClicked(QWidget *w);
    
    void on_pushButton_capslock_clicked();
    void updateButton();

    void on_pushButton_return_clicked();

private:
    Ui::Keyboard *ui;
    bool    isCapsLock;
    QWidget *lastFocusedWidget;
    QSignalMapper signalMapper;
    QList<QPushButton*> keyList;
};

#endif // KEYBOARD_H
