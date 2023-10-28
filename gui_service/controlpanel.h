#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

//**********************************************************************
// Header includes
//**********************************************************************
#include <QMainWindow>
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
    QSharedPointer<QDockWidget> dockWidget;
};
}

#endif // CONTROLPANEL_H
