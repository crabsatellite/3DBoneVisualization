//**********************************************************************
// Header includes
//**********************************************************************
#include "controlpanel.h"
#include <QLabel>
#include <QSlider>
#include <QGroupBox>
#include <QComboBox>
#include <QMainWindow>
#include <QVBoxLayout>

//**********************************************************************
// Constants
//**********************************************************************
namespace {
const QVector<QString> SLIDER_IDS = {"Rotate X:", "Rotate Y:", "Rotate Z:",
                                     "Zoom:", "Move X:", "Move Y:", "Move Z:"};
}
//**********************************************************************
// Function definitions
//**********************************************************************
GUIService::ControlPanel::ControlPanel()
{
    dockWidget.reset(new QDockWidget());
}

void GUIService::ControlPanel::setupRightPanel(QMainWindow *parent) {

    // Add labels and sliders to the layout
    QVBoxLayout* layout = new QVBoxLayout();
    for ( const auto& slider_id : SLIDER_IDS ) {
        QLabel* label = new QLabel(slider_id);
        QSlider* slider = new QSlider(Qt::Horizontal);
        layout->addWidget(label);
        layout->addWidget(slider);
    }

    // Add combo box to the layout
    QComboBox* comboBox = new QComboBox();
    comboBox->addItems({"Wireframe Mode", "Solid Mode"});
    layout->addWidget(comboBox);

    // Add container for the control panel
    QGroupBox* rightPanel = new QGroupBox("Right Panel");
    rightPanel->setLayout(layout);

    // Add the right panel to the main window
    dockWidget->setParent(parent);
    dockWidget->setWindowTitle("");  // set empty title
    dockWidget->setTitleBarWidget(new QWidget());  // hide title bar
    dockWidget->setWidget(rightPanel);
    dockWidget->setFeatures(QDockWidget::DockWidgetMovable);

    // Add the QDockWidget to the QMainWindow's right side
    parent->addDockWidget(Qt::RightDockWidgetArea, dockWidget.data());
}

