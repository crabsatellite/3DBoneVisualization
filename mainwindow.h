#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//**********************************************************************
// Header includes
//**********************************************************************
#include <QStatusBar>
#include <QMainWindow>

//**********************************************************************
// Forward declarations
//**********************************************************************
namespace Ui {
class MainWindow;
}
namespace GUIService {
class ToolBar;
class ControlPanel;
}

//**********************************************************************
// Class declaration
//**********************************************************************
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
//**********************************************************************
//  Constructors & destructors
//**********************************************************************
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
//**********************************************************************
// Public slots
//**********************************************************************
    void onOpenFile();

private:
//**********************************************************************
// Private methods
//**********************************************************************
    void setUpSignalSlotConnections();
    QList<QString> loadedDicomFiles;

private:
//**********************************************************************
// Private attributes
//**********************************************************************
    Ui::MainWindow* ui;
    QSharedPointer<QStatusBar> statusbar;
    QSharedPointer<GUIService::ToolBar> toolbar;
    QSharedPointer<GUIService::ControlPanel> controlPanel;
};

#endif // MAINWINDOW_H
