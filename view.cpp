#include "view.h"

void setupView(QMainWindow *parent) {
    QLabel *label = new QLabel("Display Area", parent);
    parent->setCentralWidget(label);

    // TODO: Integrate OpenGL or another 3D framework to display the model
}
