//**********************************************************************
// Header includes
//**********************************************************************
#include "view.h"

//**********************************************************************
// Function definitions
//**********************************************************************
GUIService::View::View()
{
    label.reset(new QLabel("Display Area"));
}

void GUIService::View::setupView(QMainWindow *parent)
{
    label->setParent(parent);
    parent->setCentralWidget(label.data());
    // TODO: Integrate OpenGL or another 3D framework to display the model
}
