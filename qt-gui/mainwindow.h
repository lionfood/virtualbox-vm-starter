#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "vm.cpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
		Q_OBJECT

	public:
		MainWindow(QWidget *parent = nullptr);
		~MainWindow();

	private:
		Ui::MainWindow *ui;
		std::vector<VM> vms;
		void getVMs();

	private slots:
		void OK_Click();

};
#endif // MAINWINDOW_H
