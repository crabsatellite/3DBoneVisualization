#include "toolbar.h"
#include "mainwindow.h"

void setupToolbar(QMainWindow *parent) {
    QToolBar *toolbar = new QToolBar(parent);
    QAction *openFileAction = toolbar->addAction("Upload");
    // Connect the action's signal to the main window's slot
    QObject::connect(openFileAction, &QAction::triggered, parent, [parent](){
        static_cast<MainWindow*>(parent)->onOpenFile();
    });
    parent->addToolBar(toolbar);
}
