#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "toolbar.h" // Include the toolbar header
#include "view.h"   // Include the view header
#include "controlpanel.h" // Include the right panel header
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Setup Toolbar
    setupToolbar(this);

    // Setup View
    setupView(this);

    // Setup Right Panel
    setupRightPanel(this);

    // Setup Status Bar
    statusbar = new QStatusBar(this);
    this->setStatusBar(statusbar);
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
