#include "BaseLogic.h"

#include <iterator>

QVector<int>& BaseLogic::getId(){
	return id;
}

QVector<QDate>& BaseLogic::getDate() {
	return date;
}

QVector<double>& BaseLogic::getCash() {
	return cash;
}

BaseLogic::BaseLogic() {

}



void BaseLogic::calculate(int count, double invest) {
	caseLife.clear();
	casesCount.clear();

	curCash = invest;
	buyCase();

	for (int i = 1; i < in.size(); i++) {

			for (int key: casesCount.keys()) {
				double delta = cases[key];
				for (int j = 0; j < casesCount[key]; j++) {
					curCash += delta;
				}
			}

			curCash += in[i];
			curCash -= out[i];

		for (int j = caseLife.size() - 1; j >= 0; j--) {
			caseLife[j].life--;
			if (caseLife[j].life <= 0) {
				caseLife.remove(j);
			}
		}

		cash[i] = curCash;

		if (i < count) {
			buyCase();
		}
		groupCase();

		casesFlags[i] = QHash<int, int>(casesCount);

	}
}
void BaseLogic::buyCase() {
	if (curCash >= 65610) {
		curCash -= 65610;
		casesCount[65610]++;
		Case c;
		c.type = 65610;
		c.life = 53;
		caseLife.push_back(c);
	} else if (curCash >= 21870) {
		curCash -= 21870;
		casesCount[21870]++;
		Case c;
		c.type = 21870;
		c.life = 53;
		caseLife.push_back(c);
	} else if (curCash >= 7290) {
		curCash -= 7290;
		casesCount[7290]++;
		Case c;
		c.type = 7290;
		c.life = 53;
		caseLife.push_back(c);
	} else if (curCash >= 2430) {
		curCash -= 2430;
		casesCount[2430]++;
		Case c;
		c.type = 2430;
		c.life = 53;
		caseLife.push_back(c);
	} else if (curCash >= 810) {
		curCash -= 810;
		casesCount[810]++;
		Case c;
		c.type = 810;
		c.life = 53;
		caseLife.push_back(c);
	} else if (curCash >= 270) {
		curCash -= 270;
		casesCount[270]++;
		Case c;
		c.type = 270;
		c.life = 53;
		caseLife.push_back(c);
	} else if (curCash >= 90) {
		curCash -= 90;
		casesCount[90]++;
		Case c;
		c.type = 90;
		c.life = 53;
		caseLife.push_back(c);
	}
}

void BaseLogic::groupCase() {
	casesCount[90] = 0;
	casesCount[270] = 0;
	casesCount[810] = 0;
	casesCount[2430] = 0;
	casesCount[7290] = 0;
	casesCount[21870] = 0;
	casesCount[65610] = 0;

	for (Case c : caseLife) {
		casesCount[c.type]++;
	}
	for (QHash<int, int>::iterator i = casesCount.begin(); i != casesCount.end(); ++i) {
		int key = i.key();
		if (key == 65610)
			continue;
		if (casesCount[key] >= 3) {
			int life = 0;
			int counter = 0;
			for (int j = caseLife.size() - 1; j >= 0; j--) {
				if (caseLife[j].type == key) {
					counter++;
					life += caseLife[j].life;
					caseLife.remove(j);
					if (counter == 3)
						break;
				}
			}
			Case c;
			c.life = life / 3;
			c.type = key * 3;
			caseLife.push_back(c);
		}
	}
}


