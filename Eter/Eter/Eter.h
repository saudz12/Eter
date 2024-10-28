#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Eter.h"

class Eter : public QMainWindow
{
    Q_OBJECT

public:
    Eter(QWidget *parent = nullptr);
    ~Eter();

private:
    Ui::EterClass ui;
};
