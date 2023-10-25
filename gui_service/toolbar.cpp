//**********************************************************************
// Header includes
//**********************************************************************
#include "toolbar.h"
#include "../mainwindow.h"

//**********************************************************************
// Function definitions
//**********************************************************************
GUIService::ToolBar::ToolBar()
{
    toolbar.reset(new QToolBar());
}

void GUIService::ToolBar::setupToolbar(QMainWindow *parent) {
    toolbar->setParent(parent);
    QAction *openFileAction = toolbar->addAction("Upload");
    // Connect the action's signal to the main window's slot
    QObject::connect(openFileAction, &QAction::triggered, parent, [parent](){
        static_cast<MainWindow*>(parent)->onOpenFile();
    });
    parent->addToolBar(toolbar.data());
}

