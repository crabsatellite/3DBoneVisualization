#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

//**********************************************************************
// Header includes
//**********************************************************************
#include <QLabel>
#include <QSlider>
#include <QComboBox>
#include <QGroupBox>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QDockWidget>

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

private:
//**********************************************************************
// Private attributes
//**********************************************************************
    QMap<QString, QSharedPointer<QSlider>> sliders;
    QMap<QString, QSharedPointer<QLabel>> labels;
    QSharedPointer<QVBoxLayout> layout;
    QSharedPointer<QComboBox> comboBox;
    QSharedPointer<QGroupBox> rightPanel;
    QSharedPointer<QDockWidget> dockWidget;
};
}

#endif // CONTROLPANEL_H
