#include "controlpanel.h"
#include <QVBoxLayout>
#include <QGroupBox>
#include <QDockWidget>
#include <QLabel>

void setupRightPanel(QMainWindow *parent) {
    // Sliders
    QSlider *rotateSliderX = new QSlider(Qt::Horizontal, parent);
    QSlider *rotateSliderY = new QSlider(Qt::Horizontal, parent);
    QSlider *rotateSliderZ = new QSlider(Qt::Horizontal, parent);
    QSlider *zoomSlider = new QSlider(Qt::Horizontal, parent);
    QSlider *moveSliderX = new QSlider(Qt::Horizontal, parent);
    QSlider *moveSliderY = new QSlider(Qt::Horizontal, parent);
    QSlider *moveSliderZ = new QSlider(Qt::Horizontal, parent);

    // Combo box
    QComboBox *comboBox = new QComboBox(parent);
    comboBox->addItems({"Wireframe Mode", "Solid Mode"});

    // Layout for the right panel
    QVBoxLayout *layout = new QVBoxLayout;

    // Add labels and sliders to the layout
    layout->addWidget(new QLabel("Rotate X:", parent));
    layout->addWidget(rotateSliderX);

    layout->addWidget(new QLabel("Rotate Y:", parent));
    layout->addWidget(rotateSliderY);

    layout->addWidget(new QLabel("Rotate Z:", parent));
    layout->addWidget(rotateSliderZ);

    layout->addWidget(new QLabel("Zoom:", parent));
    layout->addWidget(zoomSlider);

    layout->addWidget(new QLabel("Move X:", parent));
    layout->addWidget(moveSliderX);

    layout->addWidget(new QLabel("Move Y:", parent));
    layout->addWidget(moveSliderY);

    layout->addWidget(new QLabel("Move Z:", parent));
    layout->addWidget(moveSliderZ);

    layout->addWidget(comboBox);

    // Container for the control panel
    QGroupBox *rightPanel = new QGroupBox("Control Panel", parent);
    rightPanel->setLayout(layout);

    // Add the right panel to the main window
    QDockWidget *dockWidget = new QDockWidget(parent);
    dockWidget->setWindowTitle("");  // set empty title
    dockWidget->setTitleBarWidget(new QWidget());  // hide title bar
    dockWidget->setWidget(rightPanel);

    dockWidget->setFeatures(QDockWidget::DockWidgetMovable);

    // Add the QDockWidget to the QMainWindow's right side
    parent->addDockWidget(Qt::RightDockWidgetArea, dockWidget);
}
