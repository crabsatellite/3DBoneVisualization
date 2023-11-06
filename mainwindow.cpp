//**********************************************************************
// Header includes
//**********************************************************************
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "./gui_service/toolbar.h"
#include "./gui_service/controlpanel.h"
#include "./render_service/renderproxy.h"
#include "./image_process_service/image_processor.h"
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

    // Setup Right Panel
    controlPanel.reset(new GUIService::ControlPanel());
    controlPanel->setupRightPanel(this);

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
    QString defaultDicomPath = QDir::current().absoluteFilePath("dicoms");
    QStringList fileNames = QFileDialog::getOpenFileNames(
                                this,
                                tr("Open DICOM Files"),
                                defaultDicomPath,
                                tr("DICOM Files (*.dcm)")
                            );

    if (!fileNames.isEmpty()) {
        loadedDicomFiles.clear();
        for (const QString &fileName : fileNames) {
            qDebug() << "Selected DICOM file:" << fileName;
            loadedDicomFiles.append(fileName);
        }

        ImageProcessor imageProcessor;
        imageProcessor.processDicomFiles(loadedDicomFiles);
    }
}

void MainWindow::setUpSignalSlotConnections()
{
    auto widgetList = ui->centralwidget->children();
    Q_ASSERT(!widgetList.isEmpty());

    RenderService::RenderProxy* renderProxy = dynamic_cast<RenderService::RenderProxy*>(widgetList.at(0));
    Q_ASSERT(renderProxy != nullptr);

    // Control Panel -> Render Proxy
    connect(controlPanel.data(), &GUIService::ControlPanel::sliderMouseEvent, renderProxy, &RenderService::RenderProxy::onSliderMouseEvent);
}
