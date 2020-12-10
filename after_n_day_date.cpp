#include<iostream>
#include<string>
using namespace std;















































class Date {
private:
	static int m_s_month[12];
	int m_year;
	int m_month;
	int m_day;
public:
	Date(int y = 0, int m = 0, int d = 0) {
		m_year = y;
		m_month = m;
		m_day = d;
	}
	friend ostream& operator<<(ostream& os, Date& a);
	friend istream& operator>>(istream& os, Date& t);
	static int getMonthDay(int y, size_t n);
	bool LeapYear(int year) const;
	int countLeapYear(int year) const;
	Date operator+(size_t n)const;
};

int Date::m_s_month[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
int Date::getMonthDay(int y, size_t n) {
	return m_s_month[n - 1] + (n == 2 && (y % 400 == 0 || (y % 4 == 0 && y % 100)));
}
bool Date::LeapYear(int y)const {
	return y % 400 == 0 || (y % 4 == 0 && y % 100 != 0);
}
ostream& operator<<(ostream& os, Date& a) {
	os << a.m_year << "-" << a.m_month << "-" << a.m_day << endl;
	return os;
}
istream& operator>>(istream& os, Date& t) {
	cout << "input year" << endl;
	while (1) {
		os >> t.m_year;
		if (t.m_year >= 0) {
			break;
		}
		cout << "cannot be negative! Plz re-input" << endl;
	}
	cout << "input month" << endl;
	while (1) {
		os >> t.m_month;
		if (t.m_month < 1) {
			cout << "month must be larger than 0, plz re-input" << endl;
			continue;
		}
		if (t.m_month > 12) {
			cout << "month must be smaller than 12, plz re-input" << endl;
			continue;
		}
		break;
	}
	cout << "input a day: " << endl;
	while (1) {
		os >> t.m_day;
		if (t.m_day < 1) {
			cout << "day must be larger than 0"<<endl;
			continue;
		}
		if (t.m_day > Date::getMonthDay(t.m_year, t.m_month)) {
			cout << "day input exceeds days of this month: " << Date::getMonthDay(t.m_year, t.m_month) << "plz re-input\n";
			continue;
		}
		break;
	}
	return os;
}
Date Date::operator+(size_t n) const {
	Date tmp = *this;
	size_t count = 0;
	for (int i = 1; i < (int)tmp.m_month; ++i) {
		count += getMonthDay(tmp.m_year, i);
	}
	count += tmp.m_day;
	if (n >= (365 + LeapYear(tmp.m_year) - count)) {
		n -= (365 + LeapYear(tmp.m_year) - count);
		tmp.m_month = 12;
		tmp.m_day = 31;
		while ((int)n >= (365 + LeapYear(tmp.m_year + 1))) {
			n -= (365 + LeapYear(++tmp.m_year));
		}
	}
	for (; n > 0; --n) {
		if (tmp.m_day == getMonthDay(tmp.m_year, tmp.m_month)) {
			tmp.m_day = 1;
			tmp.m_month == 12 ? tmp.m_month = 1, ++tmp.m_year : ++tmp.m_month;
		}
		else {
			++tmp.m_day;
		}
	}
	return tmp;

}
int main() {
	int n;
	Date a,b;
	cout << "input a date\n";
	cin >> a;
	//cout << a;
	cout << "How many days after?" << endl;
	cin >> n;
	b = a + n;
	cout << a << " after " << n << " days is " << b;

}


