#ifndef WORDWINDOW_H
#define WORDWINDOW_H

#include <QWidget>
#include <QString>
#include <QPainter>
#include <QFont>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <qjsonobject.h>
#include <qjsondocument.h>
#include <QTimer>
#include <qdesktopwidget.h>

namespace Ui {
class WordWindow;
}

class WordWindow : public QWidget
{
    Q_OBJECT

public:
    explicit WordWindow(QWidget *parent = 0);
    ~WordWindow();

	void showText();

public slots:
	void handelWord(QNetworkReply *);

	void hidWindow();

private:
    Ui::WordWindow *ui;
	void paintEvent(QPaintEvent *e);

	QString showedText;
};

#endif // WORDWINDOW_H
