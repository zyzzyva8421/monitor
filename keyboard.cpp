#include "keyboard.h"
#include "ui_keyboard.h"
#include <QKeyEvent>
#include <iostream>

Keyboard::Keyboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Keyboard)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    isCapsLock = false;
    connect(qApp, SIGNAL(focusChanged(QWidget*,QWidget*)),
            this, SLOT(saveFocusWidget(QWidget*,QWidget*)));

    if (keyList.isEmpty()) {
        // generate the key list
        keyList << ui->pushButton_1 << ui->pushButton_2 << ui->pushButton_3 << ui->pushButton_4 << ui->pushButton_5
                   << ui->pushButton_6 << ui->pushButton_7 << ui->pushButton_8 << ui->pushButton_9 << ui->pushButton_0
                   << ui->pushButton_a
                      << ui->pushButton_b << ui->pushButton_c << ui->pushButton_d << ui->pushButton_e <<ui->pushButton_f
                         << ui->pushButton_g << ui->pushButton_h << ui->pushButton_i << ui->pushButton_j << ui->pushButton_k
                            << ui->pushButton_l << ui->pushButton_m << ui->pushButton_n << ui->pushButton_o << ui->pushButton_p
                               << ui->pushButton_q << ui->pushButton_r << ui->pushButton_s << ui->pushButton_t << ui->pushButton_u
                                  << ui->pushButton_v << ui->pushButton_w << ui->pushButton_x << ui->pushButton_y << ui->pushButton_z
                                     << ui->pushButton_space << ui->pushButton_backspace << ui->pushButton_capslock << ui->pushButton_return;
    }

    for (int i = 0; i < keyList.size(); i++) {
        signalMapper.setMapping((QObject*)keyList[i], keyList[i]);
        connect(keyList[i], SIGNAL(clicked()), &signalMapper, SLOT(map()));
        if (i<keyList.size()-1) {
            setTabOrder(keyList[i], keyList[i+1]);
        } else {
            setTabOrder(keyList[i], keyList[0]);
        }
    }
    connect(&signalMapper, SIGNAL(mapped(QWidget*)),
            this, SLOT(buttonClicked(QWidget*)));
    updateButton();
    ui->pushButton_1->setFocus();
}

Keyboard::~Keyboard()
{
    delete ui;
}

bool Keyboard::event(QEvent *e)
{
    switch (e->type()) {
    case QEvent::KeyPress: {
        QKeyEvent *event=(QKeyEvent *)e;
        switch (event->key()) {
        case Qt::Key_Return:
            ( (QPushButton*)focusWidget())->click();
            break;
        default:
            break;
        }
    }
    default:
        break;
    }
    return QWidget::event(e);
}

void Keyboard::saveFocusWidget(QWidget * /*oldFocus*/, QWidget *newFocus)
{
    if (newFocus != 0 && !this->isAncestorOf(newFocus)) {
//        std::cout << newFocus->objectName().toStdString() << std::endl;
        lastFocusedWidget = newFocus;
    }
}

void Keyboard::buttonClicked(QWidget *w)
{
    if (w != ui->pushButton_capslock && w != ui->pushButton_return) {
        QString objName = w->objectName();
        // name is pushButton_xx
        emit keyGenerated(objName.mid(11));
    }
}


void Keyboard::updateButton()
{
    QPushButton *button = NULL;
    for (int i = 0; i < keyList.size(); i++) {
        button = keyList[i];
        if (button != ui->pushButton_space &&
                button != ui->pushButton_backspace &&
                button != ui->pushButton_return &&
                button != ui->pushButton_capslock) {
            if (isCapsLock) {
                button->setText(button->text().toUpper());
            } else {
                button->setText(button->text().toLower());
            }
        }
    }
    if (isCapsLock) {
        ui->pushButton_capslock->setText(QString::fromStdWString(L"小写"));
    } else {
        ui->pushButton_capslock->setText(QString::fromStdWString(L"大写"));
    }
}

void Keyboard::on_pushButton_capslock_clicked()
{
    if (isCapsLock) {
        isCapsLock = false;
    } else {
        isCapsLock = true;
    }
    updateButton();
}

void Keyboard::on_pushButton_return_clicked()
{
    hide();
    lastFocusedWidget->setFocus();
}
