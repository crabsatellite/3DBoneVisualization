//**********************************************************************
// Header includes
//**********************************************************************
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "./gui_service/toolbar.h" // Include the toolbar header
#include "./gui_service/view.h"   // Include the view header
#include "./gui_service/controlpanel.h" // Include the right panel header
#include <QFileDialog>

//**********************************************************************
// Class method definitions
//**********************************************************************

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Setup ui
    ui->setupUi(this);

    // Setup Toolbar
    toolbar.reset(new GUIService::ToolBar());
    toolbar->setupToolbar(this);

    // Setup View
    view.reset(new GUIService::View());
    view->setupView(this);

    // Setup Right Panel
    controlPanel.reset(new GUIService::ControlPanel());
    controlPanel->setupRightPanel(this);

    // Setup Status Bar
    statusbar.reset(new QStatusBar(this));
    this->setStatusBar(statusbar.data());
    statusbar->showMessage("Ready");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onOpenFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Files", QString(), "Images (*.png *.jpg);;All Files (*)");
    if (!fileName.isEmpty()) {
        // TODO: Handle the file
    }
}
