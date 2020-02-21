#include "MainWindow.hpp"

#include "Tests/1/Scene_1.hpp"
#include "View3D/View3DGL.hpp"

namespace KikooRenderer {
    MainWindow::MainWindow() {
        setWindowTitle("KikooRenderer");
        // view3D= new View3D;
        // setCentralWidget(view3D);
        
        setDockOptions(QMainWindow::AnimatedDocks);

        QGroupBox* mainWidget = new QGroupBox("Tests");
        setCentralWidget(mainWidget);

        QVBoxLayout* mainLayout = new QVBoxLayout();
        mainWidget->setLayout(mainLayout);

        QPushButton* cubeButton = new QPushButton("Cube");
        mainLayout->addWidget(cubeButton);
        connect(cubeButton, &QPushButton::clicked, this, [this]() {
            View3DGL* view3D= new View3DGL;
            view3D->showMaximized();
        });

        QPushButton* waterButton = new QPushButton("Water");
        mainLayout->addWidget(waterButton);
        connect(waterButton, &QPushButton::clicked, this, [this]() {
            View3DGL* view3D= new View3DGL;
            CoreEngine::Scene_1* scene = new CoreEngine::Scene_1();
            view3D->scene = scene;

            view3D->showMaximized();
        });
            

	    showNormal();
        ExpandToFitScreen();
    }

    void MainWindow::ExpandToFitScreen() {
    	QRect rec = QApplication::desktop()->availableGeometry(this);
        int differenceH = frameGeometry().height() - geometry().height();
        int differenceW = frameGeometry().width() - geometry().width();
        int height = rec.height() - differenceH;
        int width = rec.width() - differenceW;
        resize(width, height);

        move(rec.topLeft().x(), rec.topLeft().y());
        
    }
}