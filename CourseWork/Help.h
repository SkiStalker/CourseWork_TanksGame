#pragma once

#include "INCLUDES_QT.h"
#include "ui_Help.h"

// ����� ���� � �����������
class Help : public QDialog
{
	Q_OBJECT

public:
	// ����������� QT ����������
	// QWidget *parent - �������� ������
	Help(QWidget *parent = Q_NULLPTR);

	// ����������
	~Help();




private:

	// ���������������� ���������
	Ui::Help ui;
};
