#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QTableWidgetItem>
#include <iostream>


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	ui->initialDate->setDate(QDate::currentDate());
	ui->outDate->setDate((QDate::currentDate()).addYears(1));


	base.cases[90] = 90.0 * 0.04;
	base.cases[270] = 270.0 * 0.042;
	base.cases[810] = 810.0 * 0.046;
	base.cases[2430] = 2430 * 0.05;
	base.cases[7290] = 7290 * 0.052;
	base.cases[21870] = 21870 * 0.06;
	base.cases[65610] = 65610 * 0.062;

	createTables();

}

MainWindow::~MainWindow()
{
	delete ui;
}


bool comp(int a, int b) {
	return a > b;
}



void MainWindow::createTables() {

	ui->packagesTable->clear();
	ui->packagesTable->setRowCount( 0);

	ui->resultTable->clear();
	ui->resultTable->setRowCount( 0);

	QStringList list1;
	list1 << "Id" << "Date" << "In" << "Out" << "Cash" << "90" << "270" << "810" << "2430" << "7290" << "21870" << "65610";

	QStringList list2;
	list2 << "Case" << "Profit";

	ui->resultTable->setHorizontalHeaderLabels(list1);
	ui->packagesTable->setHorizontalHeaderLabels(list2);

	ui->resultTable->setShowGrid(true);
	ui->resultTable->setSelectionMode(QAbstractItemView::SingleSelection);
	ui->resultTable->hideColumn(0);

	ui->packagesTable->insertRow(0);
	ui->packagesTable->setItem(0, 0, new QTableWidgetItem(QString::number(90)));
	ui->packagesTable->setItem(0, 1, new QTableWidgetItem(QString::number(base.cases[90])));
	ui->packagesTable->insertRow(1);
	ui->packagesTable->setItem(1, 0, new QTableWidgetItem(QString::number(270)));
	ui->packagesTable->setItem(1, 1, new QTableWidgetItem(QString::number(base.cases[270])));
	ui->packagesTable->insertRow(2);
	ui->packagesTable->setItem(2, 0, new QTableWidgetItem(QString::number(810)));
	ui->packagesTable->setItem(2, 1, new QTableWidgetItem(QString::number(base.cases[810])));
	ui->packagesTable->insertRow(3);
	ui->packagesTable->setItem(3, 0, new QTableWidgetItem(QString::number(2430)));
	ui->packagesTable->setItem(3, 1, new QTableWidgetItem(QString::number(base.cases[2430])));
	ui->packagesTable->insertRow(4);
	ui->packagesTable->setItem(4, 0, new QTableWidgetItem(QString::number(7290)));
	ui->packagesTable->setItem(4, 1, new QTableWidgetItem(QString::number(base.cases[7290])));
	ui->packagesTable->insertRow(5);
	ui->packagesTable->setItem(5, 0, new QTableWidgetItem(QString::number(21870)));
	ui->packagesTable->setItem(5, 1, new QTableWidgetItem(QString::number(base.cases[21870])));
	ui->packagesTable->insertRow(6);
	ui->packagesTable->setItem(6, 0, new QTableWidgetItem(QString::number(65610)));
	ui->packagesTable->setItem(6, 1, new QTableWidgetItem(QString::number(base.cases[65610])));

	for (int i = 0; i < base.in.size(); i++) {
		ui->resultTable->insertRow(i);
		ui->resultTable->setItem(i, 0, new QTableWidgetItem(QString::number(base.id[i])));
		ui->resultTable->setItem(i, 1, new QTableWidgetItem(base.date[i].toString("dd.MM.yyyy")));
		ui->resultTable->setItem(i, 2, new QTableWidgetItem(QString::number(base.in[i])));
		ui->resultTable->setItem(i, 3, new QTableWidgetItem(QString::number(base.out[i])));
		ui->resultTable->setItem(i, 4, new QTableWidgetItem(QString::number(base.cash[i])));
		ui->resultTable->setItem(i, 5, new QTableWidgetItem(QString::number(base.casesFlags[i][90])));
		ui->resultTable->setItem(i, 6, new QTableWidgetItem(QString::number(base.casesFlags[i][270])));
		ui->resultTable->setItem(i, 7, new QTableWidgetItem(QString::number(base.casesFlags[i][810])));
		ui->resultTable->setItem(i, 8, new QTableWidgetItem(QString::number(base.casesFlags[i][2430])));
		ui->resultTable->setItem(i, 9, new QTableWidgetItem(QString::number(base.casesFlags[i][7290])));
		ui->resultTable->setItem(i, 10, new QTableWidgetItem(QString::number(base.casesFlags[i][21870])));
		ui->resultTable->setItem(i, 11, new QTableWidgetItem(QString::number(base.casesFlags[i][65610])));

		double nn = ui->resultTable->item(i, 2)->text().toDouble();
		if (nn > 0) {
			ui->resultTable->item(i, 2)->setBackground(QBrush(Qt::blue));
		}
		nn = ui->resultTable->item(i, 3)->text().toDouble();
		if (nn > 0) {
			ui->resultTable->item(i, 3)->setBackground(QBrush(Qt::gray));
		}

		QDate d = ui->outDate->date();
		while (d.dayOfWeek() != 5) {
			d = d.addDays(-1);
		}

		if (base.date[i] < d) {
			ui->resultTable->item(i, 1)->setBackground(QBrush(QColor(255, 200, 100)));
		}

		for (int j = 5; j < 12; j++) {
			int n = ui->resultTable->item(i, j)->text().toInt();
			if (n == 1) {
				ui->resultTable->item(i, j)->setBackground(QBrush(Qt::green));
			} else if (n == 2) {
				ui->resultTable->item(i, j)->setBackground(QBrush(Qt::yellow));
			} else if (n >= 3) {
				ui->resultTable->item(i, j)->setBackground(QBrush(Qt::red));
			}
		}
	}
	ui->resultTable->resizeColumnsToContents();
	ui->packagesTable->resizeColumnsToContents();
}

void MainWindow::on_pushButton_clicked() {

	for (int i = 0; i < nrOfWeeks; i++) {
		base.in[i] = ui->resultTable->item(i, 2)->text().toDouble();
		base.out[i] = ui->resultTable->item(i, 3)->text().toDouble();
	}


	QDate begin, end;
	begin = ui->initialDate->date();
	end = ui->outDate->date();

	int nrOfDays = 0;

//	for (int m = begin.month() + 1; m < end.month(); ++m)
//		nrOfDays += daysOfMonth(begin.year(), m);

//	if (begin.month() == end.month())
//		nrOfDays += end.day() - begin.day();
//	else
//		nrOfDays += daysOfMonth(begin.year(), begin.month()) - begin.day() + end.day();
	nrOfDays = begin.daysTo(end);


	nrOfWeeks = nrOfDays / 7;

	if (base.in.size() == 0) {
		for (int i = 0; i < nrOfWeeks + 104; i++) {
			base.in.push_back(0);
		}
	} else if (base.in.size() < nrOfWeeks + 104) {
		for (int i = base.in.size(); i < nrOfWeeks + 104; i++) {
			base.in.push_back(0);
		}
	} else if (base.in.size() != nrOfWeeks + 104) {
		for (int i = base.in.size(); i < nrOfWeeks + 104; i--) {
			base.in.pop_back();
		}
	}
	if (base.out.size() == 0) {
		for (int i = 0; i < nrOfWeeks + 104; i++) {
			base.out.push_back(0);
		}
	} else if (base.out.size() < nrOfWeeks + 104) {
		for (int i = base.out.size(); i < nrOfWeeks + 104; i++) {
			base.out.push_back(0);
		}
	} else if (base.out.size() != nrOfWeeks + 104) {
		for (int i = base.out.size(); i < nrOfWeeks + 104; i--) {
			base.out.pop_back();
		}
	}
	while (begin.dayOfWeek() != 5) {
		begin = begin.addDays(1);
	}
	base.date.clear();
	base.id.clear();
	base.cash.clear();
	base.casesFlags.clear();
	for (int i = 0; i < base.in.size(); i++) {
		base.id.push_back(i);
		base.date.push_back(QDate(begin));
		base.cash.push_back(0);
		QHash<int, int> row;
		row[90] = 0;
		row[270] = 0;
		row[810] = 0;
		row[2430] = 0;
		row[7290] = 0;
		row[21870] = 0;
		row[65610] = 0;
		base.casesFlags.push_back(QHash<int, int>(row));

		begin = begin.addDays(7);
	}

	base.calculate(nrOfWeeks, ui->beginInvest->value());
	createTables();
}
