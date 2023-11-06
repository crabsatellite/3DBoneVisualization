#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

//**********************************************************************
// Header includes
//**********************************************************************
#include <QMap>
#include <QSlider>
#include <QMainWindow>
#include <QDockWidget>
#include "gui_service/gui_utility.h"

//**********************************************************************
// Class declarations
//**********************************************************************
namespace GUIService {

class ControlPanel : public QObject
{
    Q_OBJECT

public:
//**********************************************************************
// Constructors & destructors
//**********************************************************************
    ControlPanel();
    ~ControlPanel() = default;

public:
//**********************************************************************
// Public methods
//**********************************************************************
    void setupRightPanel(QMainWindow *parent);

signals:
    void sliderMouseEvent(Slider::Action, Mouse::Action, Slider::Axis, int position = 0);

private:
//**********************************************************************
// Private methods
//**********************************************************************
    void onPitchSliderMousePressedEvent();
    void onPitchSliderMouseMovedEvent(int position);
    void onPitchSliderMouseReleasedEvent();

    void onYawSliderMousePressedEvent();
    void onYawSliderMouseMovedEvent(int position);
    void onYawSliderMouseReleasedEvent();

    void onZoomSliderMousePressedEvent();
    void onZoomSliderMouseMovedEvent(int position);
    void onZoomSliderMouseReleasedEvent();

    void setUpSignalSlotConnections(QSlider* slider);

private:
//**********************************************************************
// Private attributes
//**********************************************************************
    QSharedPointer<QDockWidget> dockWidget;
    QMap<QString, QSlider*> sliders;
};
}

#endif // CONTROLPANEL_H
