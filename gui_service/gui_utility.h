#ifndef GUI_UTILITY_H
#define GUI_UTILITY_H

namespace Slider {

enum Action {
    ROTATE,
    MOVE,
    ZOOM
};

enum Axis {
    X,
    Y,
    UNDEFINED
};

const QString PITCH_SLIDER_NAME = "Pitch: ";
const QString YAW_SLIDER_NAME = "Yaw: ";
const QString HORIZONTAL_MOVE_SLIDER_NAME = "Horizontal Move: ";
const QString VERTICAL_MOVE_SLIDER_NAME = "Vertical Move: ";
const QString ZOOM_SLIDER_NAME = "Zoom: ";
const QVector<QString> SLIDER_NAMES = {PITCH_SLIDER_NAME, YAW_SLIDER_NAME, HORIZONTAL_MOVE_SLIDER_NAME, VERTICAL_MOVE_SLIDER_NAME, ZOOM_SLIDER_NAME };

}

namespace Mouse {

enum Action {
    PRESSED,
    MOVED,
    RELEASED
};

}

#endif // GUI_UTILITY_H
