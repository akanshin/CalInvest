#ifndef BASELOGIC_H
#define BASELOGIC_H

#include <QVector>
#include <QDate>
#include <QHash>

typedef struct Case {
	int type;
	int life;
}Case;

class BaseLogic
{
public:
	QVector<int> id;
	QVector<QDate> date;
	QVector<double> cash;
	QVector<double> in;
	QVector<double> out;

	QHash<int, int> casesCount;
	QVector<QHash<int, int>> casesFlags;

	QHash<int, double> cases;
	QVector<Case> caseLife;


	double curCash = 0;

public:
	BaseLogic();

	QVector<int>& getId();
	QVector<QDate>& getDate();
	QVector<double>& getCash();

	void calculate(int count, double invest);
	void buyCase();
	void groupCase();
};

#endif // BASELOGIC_H
