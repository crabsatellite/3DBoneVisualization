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
const float CENTER_POS = 50.5;
const int DEFAULT_ZOOM = 45;
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
    for ( const auto& sliderId : Slider::SLIDER_NAMES ) {
        QLabel* label = new QLabel(sliderId);

        QSlider* slider = new QSlider(Qt::Horizontal);
        slider->setObjectName(sliderId);
        slider->setValue(sliderId == Slider::ZOOM_SLIDER_NAME ? DEFAULT_ZOOM : CENTER_POS);
        setUpSignalSlotConnections(slider);

        layout->addWidget(label);
        layout->addWidget(slider);
        sliders.insert(sliderId, slider);
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

void GUIService::ControlPanel::onPitchSliderMousePressedEvent()
{
    QSlider* slider = sliders[Slider::PITCH_SLIDER_NAME];
    emit sliderMouseEvent(Slider::Action::ROTATE, Mouse::Action::PRESSED, Slider::Axis::X, slider->value());
}

void GUIService::ControlPanel::onPitchSliderMouseMovedEvent(int position)
{
    QSlider* slider = sliders[Slider::PITCH_SLIDER_NAME];
    emit sliderMouseEvent(Slider::Action::ROTATE, Mouse::Action::MOVED, Slider::Axis::X, slider->value());
}

void GUIService::ControlPanel::onPitchSliderMouseReleasedEvent()
{
    QSlider* slider = sliders[Slider::PITCH_SLIDER_NAME];
    emit sliderMouseEvent(Slider::Action::ROTATE, Mouse::Action::RELEASED, Slider::Axis::X, slider->value());
}

void GUIService::ControlPanel::onYawSliderMousePressedEvent()
{
    QSlider* slider = sliders[Slider::YAW_SLIDER_NAME];
    emit sliderMouseEvent(Slider::Action::ROTATE, Mouse::Action::PRESSED, Slider::Axis::Y, slider->value());
}

void GUIService::ControlPanel::onYawSliderMouseMovedEvent(int position)
{
    QSlider* slider = sliders[Slider::YAW_SLIDER_NAME];
    emit sliderMouseEvent(Slider::Action::ROTATE, Mouse::Action::MOVED, Slider::Axis::Y, slider->value());
}

void GUIService::ControlPanel::onYawSliderMouseReleasedEvent()
{
    QSlider* slider = sliders[Slider::YAW_SLIDER_NAME];
    emit sliderMouseEvent(Slider::Action::ROTATE, Mouse::Action::RELEASED, Slider::Axis::Y, slider->value());
}

void GUIService::ControlPanel::onZoomSliderMousePressedEvent()
{
    QSlider* slider = sliders[Slider::ZOOM_SLIDER_NAME];
    emit sliderMouseEvent(Slider::Action::ZOOM, Mouse::Action::PRESSED, Slider::Axis::UNDEFINED, slider->value());
}

void GUIService::ControlPanel::onZoomSliderMouseMovedEvent(int position)
{
    QSlider* slider = sliders[Slider::ZOOM_SLIDER_NAME];
    emit sliderMouseEvent(Slider::Action::ZOOM, Mouse::Action::MOVED, Slider::Axis::UNDEFINED, slider->maximum() - slider->value());
}

void GUIService::ControlPanel::onZoomSliderMouseReleasedEvent()
{
    QSlider* slider = sliders[Slider::ZOOM_SLIDER_NAME];
    emit sliderMouseEvent(Slider::Action::ZOOM, Mouse::Action::RELEASED, Slider::Axis::UNDEFINED, slider->value());
}

void GUIService::ControlPanel::setUpSignalSlotConnections(QSlider* slider)
{
    // Slider -> Control Panel
    const QString sliderId = slider->objectName();
    if ( sliderId == Slider::PITCH_SLIDER_NAME ) {
        connect(slider, &QSlider::sliderPressed, this, &GUIService::ControlPanel::onPitchSliderMousePressedEvent);
        connect(slider, &QSlider::sliderMoved, this, &GUIService::ControlPanel::onPitchSliderMouseMovedEvent);
        connect(slider, &QSlider::sliderReleased, this, &GUIService::ControlPanel::onPitchSliderMouseReleasedEvent);

    } else if ( sliderId == Slider::YAW_SLIDER_NAME ) {
        connect(slider, &QSlider::sliderPressed, this, &GUIService::ControlPanel::onYawSliderMousePressedEvent);
        connect(slider, &QSlider::sliderMoved, this, &GUIService::ControlPanel::onYawSliderMouseMovedEvent);
        connect(slider, &QSlider::sliderReleased, this, &GUIService::ControlPanel::onYawSliderMouseReleasedEvent);

    } else if ( sliderId == Slider::HORIZONTAL_MOVE_SLIDER_NAME ) {
        // TODO

    } else if ( sliderId == Slider::VERTICAL_MOVE_SLIDER_NAME ) {
        // TODO

    } else if ( sliderId == Slider::ZOOM_SLIDER_NAME ) {
        connect(slider, &QSlider::sliderPressed, this, &GUIService::ControlPanel::onZoomSliderMousePressedEvent);
        connect(slider, &QSlider::sliderMoved, this, &GUIService::ControlPanel::onZoomSliderMouseMovedEvent);
        connect(slider, &QSlider::sliderReleased, this, &GUIService::ControlPanel::onZoomSliderMouseReleasedEvent);
    }
}

