#ifndef MENU_H
#define MENU_H

#include <QWidget>

namespace Ui {
class Menu;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = 0);
    void changeMessage (bool success);
    ~Menu();
private:
    Ui::Menu *ui;
private slots:
    void on_restartButton_clicked();
signals:
    void restartPressed ();
};

#endif // MENU_H
