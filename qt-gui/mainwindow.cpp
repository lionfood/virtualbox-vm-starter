#include <cstdlib>
#include <iostream>
#include <QProcess>
#include <QString>
#include <vector>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	connect(ui->okButton, SIGNAL(clicked()), SLOT(OK_Click()));
	getVMs();
	for (VM vm : vms)
	{
		ui->comboBox->addItem(vm.name);
	}
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getVMs()
{
	QProcess process;
	QString vboxmanage_output;

	char *VBOX_MANAGE_COMMAND;

#ifdef _WIN32
    VBOX_MANAGE_COMMAND = (char*)"\"C:\\Program Files\\Oracle\\VirtualBox\\VBoxManage.exe\"";
#else
	VBOX_MANAGE_COMMAND = (char*)"VBoxManage";
#endif

	process.setProcessChannelMode(QProcess::MergedChannels);
	process.start(VBOX_MANAGE_COMMAND, QStringList() << "list" << "vms");

	while (!process.waitForFinished())
	{
		//do.nothig;
	}

	QStringList data;
	while (process.canReadLine())
	{
		data << process.readLine();
	}

	for (QString entry : data)
	{
		QStringList vm_entry = entry.remove(0, 1).split("\" ");
		vms.push_back(VM(vm_entry[0], vm_entry[1]));
	}
}

void MainWindow::OK_Click()
{
	int curIndex = ui->comboBox->currentIndex();
	if(curIndex < 0)
	{
		exit(-1);
	}
#ifdef _WIN32
	QString command = "start \"\" \"C:\\Program Files\\Oracle\\VirtualBox\\VirtualBoxVM.exe\";
	QString arguments " --comment \"" + vms[curIndex].name + "\" --startvm \"" + vms[curIndex].UID + "\"";
#else
	QString command = "VBoxManage";
	QString arguments = " startvm \"" + vms[curIndex].UID + "\" &";
#endif
	QString COMMAND = command + arguments;
	std::system(COMMAND.toStdString().c_str());
	close();
}
