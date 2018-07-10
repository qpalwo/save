#ifndef SAVEANDLOAD_H
#define SAVEANDLOAD_H

#include <QWidget>

namespace Ui {
class SaveAndLoad;
}

class SaveAndLoad : public QWidget
{
    Q_OBJECT

public:
    explicit SaveAndLoad(QWidget *parent = 0);
    ~SaveAndLoad();

private:
    Ui::SaveAndLoad *ui;
};

#endif // SAVEANDLOAD_H
