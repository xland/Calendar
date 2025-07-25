#pragma once
#include <QDate>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QDateEdit>

class DialogList : public QWidget
{
	Q_OBJECT

public:
	DialogList(const QDate& day, QWidget *parent = nullptr);
	~DialogList();
	QDate curDay;
	QLineEdit* input;
protected:
	void showEvent(QShowEvent* event) override;
private:
	void initSearchBar(QVBoxLayout* layout);
	void initList(QVBoxLayout* layout);
	void initRowBtns(const int& row,const QString& id);
	void initTableRows();
	void delBtnClick(const QString& id);
	void editBtnClick(const QString& id);
	QString getTypeStr(const int& type,const QDate& date);
	QTableWidget* table;
	QDateEdit* calendar1;
	QDateEdit* calendar2;
};

