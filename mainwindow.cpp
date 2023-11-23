//**********************************************************************
// Header includes
//**********************************************************************
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "./gui_service/toolbar.h"
#include "./render_service/renderproxy.h"
#include "./image_process_service/image_processor.h"

#include <QFileDialog>
#include <QDir>v
#include <QLayout>
#include <QVTKOpenGLNativeWidget.h>

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

    // Setup Status Bar
    statusbar.reset(new QStatusBar(this));
    this->setStatusBar(statusbar.data());
    statusbar->showMessage("Ready");

    setUpSignalSlotConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onOpenFile()
{
    QString directory = QFileDialog::getExistingDirectory(
        this, tr("Open DICOM Directory"), QDir::current().absoluteFilePath("dicoms"));

    if (!directory.isEmpty()) {
        ImageProcessor processor;
        auto renderWindow = processor.processDICOM(directory);

        auto vtkWidget = new QVTKOpenGLNativeWidget(this);
        QLayout* layout = ui->centralwidget->layout();
        if (!layout) {
            layout = new QVBoxLayout(ui->centralwidget);
            ui->centralwidget->setLayout(layout);
        }
        layout->addWidget(vtkWidget);

        // Set Render Window
        vtkWidget->SetRenderWindow(renderWindow);
        vtkWidget->GetRenderWindow()->Render();
    }
}


void MainWindow::setUpSignalSlotConnections()
{
    auto widgetList = ui->centralwidget->children();
    Q_ASSERT(!widgetList.isEmpty());

    RenderService::RenderProxy* renderProxy = dynamic_cast<RenderService::RenderProxy*>(widgetList.at(0));
    Q_ASSERT(renderProxy != nullptr);

}
