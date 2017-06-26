#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHash>
#include <QVector>
#include "BaseLogic.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();


	void createTables();

private slots:
	void on_pushButton_clicked();

private:
	Ui::MainWindow *ui;

	int nrOfWeeks = 0;

	BaseLogic base;
};

#endif // MAINWINDOW_H
