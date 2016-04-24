#include "menu.h"
#include <QFont>
#include "ui_menu.h"
#include <QDebug>

Menu::Menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Menu)
{
    QFont font("Arial", 10, QFont::Bold);
    ui->setupUi(this);
    ui->finishMessage->setFont(font );
    ui->finishMessage->setAlignment(Qt::AlignCenter);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_restartButton_clicked()
{
    emit restartPressed();
}
void Menu::changeMessage(bool success)
{
    if (success)
        ui->finishMessage->setText("<font color='orange'>УРОВЕНЬ ПРОЙДЕН!</font>");
    else
        ui->finishMessage->setText("<font color='orange'>УРОВЕНЬ ПРОВАЛЕН!</font>");
}
