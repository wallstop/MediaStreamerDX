/*===========================================
Main GUI for AudioDX The Best
Author: Kyle Easterling
Date: Today
===========================================*/

#include "MainWindow.h"
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMenu>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

MainWindow::MainWindow(int argc, char* argv[]) : QApplication(argc, argv)
{
	init();
}

MainWindow::~MainWindow()
{
	// OS will clean up everything...
}

bool MainWindow::init()
{
	m_window = new QMainWindow();
	m_menuBar = new QMenuBar();
	m_menuBar->addMenu(tr("File"));		//more menus/actions can be added as needed
	m_window->setMenuBar(m_menuBar);

	m_mainWidget = new MainWidget();
	connect(m_mainWidget, SIGNAL(activateClientSignal()), this, SLOT(activateClient()));
	connect(m_mainWidget, SIGNAL(activateServerSignal()), this, SLOT(activateServer()));

	m_window->setCentralWidget(m_mainWidget);

	//aw yea hard coding. Currently matches client/server widget widths
	//for smoother transitioning, should probly make a ui file for mainWidget.
	m_window->setFixedWidth(186);
	m_window->setFixedHeight(100);
	m_window->show();
	return true;
}

void MainWindow::activateClient()
{
	m_clientWidget = new ClientWidget();
	m_window->setCentralWidget(m_clientWidget);	//setCentralWidget orphans m_mainWidget and qt automatically destroys it.
	m_window->setFixedSize(m_clientWidget->sizeHint());
}

void MainWindow::activateServer()
{
	m_serverWidget = new ServerWidget();
	m_window->setCentralWidget(m_serverWidget);
	m_window->setFixedSize(m_serverWidget->sizeHint());
}

MainWidget::MainWidget(QMainWindow* parent) : QWidget(parent)
{
	m_mainLayout = new QVBoxLayout();
	m_titleLayout = new QHBoxLayout();
	m_buttonLayout = new QHBoxLayout();
	m_mainLayout->addLayout(m_titleLayout);
	m_mainLayout->addLayout(m_buttonLayout);

	m_title = new QLabel();
	m_title->setText(tr("Choose device role"));
	m_titleLayout->addStretch();
	m_titleLayout->addWidget(m_title);
	m_titleLayout->addStretch();

	m_activateClientButton = new QPushButton();
	m_activateClientButton->setText(tr("&Client"));

	m_activateServerButton = new QPushButton();
	m_activateServerButton->setText(tr("&Server"));

	//qt lets us connect signals to signals which prevents having to pass member variables
	//to the parent just for connections.
	connect(m_activateClientButton, SIGNAL(clicked()), this, SIGNAL(activateClientSignal()));
	connect(m_activateServerButton, SIGNAL(clicked()), this, SIGNAL(activateServerSignal()));

	m_buttonLayout->addWidget(m_activateClientButton);
	m_buttonLayout->addWidget(m_activateServerButton);

	setLayout(m_mainLayout);
}

MainWidget::~MainWidget()
{

}