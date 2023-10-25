//**********************************************************************
// Header includes
//**********************************************************************
#include "controlpanel.h"
#include <QMainWindow>

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
    layout.reset(new QVBoxLayout());
    comboBox.reset(new QComboBox());
    rightPanel.reset(new QGroupBox("Right Panel"));
    dockWidget.reset(new QDockWidget());
}

void GUIService::ControlPanel::setupRightPanel(QMainWindow *parent) {

    // Add labels and sliders to the layout
    for ( const auto& slider_id : SLIDER_IDS ) {
        auto label = QSharedPointer<QLabel>(new QLabel(slider_id, parent));
        auto slider = QSharedPointer<QSlider>(new QSlider(Qt::Horizontal, parent));
        sliders[slider_id] = slider;
        labels[slider_id] = label;
        layout->addWidget(label.data());
        layout->addWidget(slider.data());
    }

    // Add combo box to the layout
    comboBox->setParent(parent);
    comboBox->addItems({"Wireframe Mode", "Solid Mode"});
    layout->addWidget(comboBox.data());

    // Add container for the control panel
    rightPanel->setParent(parent);
    rightPanel->setLayout(layout.data());

    // Add the right panel to the main window
    dockWidget->setParent(parent);
    dockWidget->setWindowTitle("");  // set empty title
    dockWidget->setTitleBarWidget(new QWidget());  // hide title bar
    dockWidget->setWidget(rightPanel.data());
    dockWidget->setFeatures(QDockWidget::DockWidgetMovable);

    // Add the QDockWidget to the QMainWindow's right side
    parent->addDockWidget(Qt::RightDockWidgetArea, dockWidget.data());
}

