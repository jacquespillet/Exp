#include "MainWindow.hpp"

#include "Tests/1/Scene_1.hpp"
#include "Tests/2/Scene_2.hpp"
#include "Tests/3/Scene_3.hpp"
#include "Tests/4/Scene_4.hpp"
#include "Tests/5/Scene_5.hpp"
#include "Tests/6/Scene_6.hpp"
#include "Tests/7/Scene_7.hpp"
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
            view3D->setAttribute(Qt::WA_DeleteOnClose);
        });

        QPushButton* waterButton = new QPushButton("Water");
        mainLayout->addWidget(waterButton);
        connect(waterButton, &QPushButton::clicked, this, [this]() {
            View3DGL* view3D= new View3DGL;
            Scene_1_::Scene_1* scene = new Scene_1_::Scene_1();
            view3D->scene = scene;
            view3D->scene->parentWidget = view3D;
            view3D->setAttribute(Qt::WA_DeleteOnClose);

            view3D->showMaximized();
        });

        QPushButton* causticsButton = new QPushButton("WaterCaustics");
        mainLayout->addWidget(causticsButton);
        connect(causticsButton, &QPushButton::clicked, this, [this]() {
            View3DGL* view3D= new View3DGL;
            Scene_2_::Scene_2* scene = new Scene_2_::Scene_2();
            view3D->setAttribute(Qt::WA_DeleteOnClose);
            view3D->scene = scene;
            view3D->scene->parentWidget = view3D;
            view3D->showMaximized();
        });

        QPushButton* perlinTexButton = new QPushButton("Noise Explorer");
        mainLayout->addWidget(perlinTexButton);
        connect(perlinTexButton, &QPushButton::clicked, this, [this]() {
            View3DGL* view3D= new View3DGL;
            Scene_3_::Scene_3* scene = new Scene_3_::Scene_3();
            view3D->setAttribute(Qt::WA_DeleteOnClose);
            view3D->scene = scene;
            view3D->scene->parentWidget = view3D;
            
            view3D->showMaximized();
        });

        QPushButton* noisySphereButton = new QPushButton("Noisy spheres");
        mainLayout->addWidget(noisySphereButton);
        connect(noisySphereButton, &QPushButton::clicked, this, [this]() {
            View3DGL* view3D= new View3DGL;
            Scene_4_::Scene_4* scene = new Scene_4_::Scene_4();
            view3D->setAttribute(Qt::WA_DeleteOnClose);
            view3D->scene = scene;
            view3D->scene->parentWidget = view3D;
            
            view3D->showMaximized();
        });

        QPushButton* countlessGrassButton = new QPushButton("Countless Grass");
        mainLayout->addWidget(countlessGrassButton);
        connect(countlessGrassButton, &QPushButton::clicked, this, [this]() {
            View3DGL* view3D= new View3DGL;
            Scene_5_::Scene_5* scene = new Scene_5_::Scene_5();
            view3D->setAttribute(Qt::WA_DeleteOnClose);
            view3D->scene = scene;
            view3D->scene->parentWidget = view3D;
            view3D->showMaximized();
        });

        QPushButton* diffractionButton = new QPushButton("Diffraction");
        mainLayout->addWidget(diffractionButton);
        connect(diffractionButton, &QPushButton::clicked, this, [this]() {
            View3DGL* view3D= new View3DGL;
            Scene_6_::Scene_6* scene = new Scene_6_::Scene_6();
            view3D->setAttribute(Qt::WA_DeleteOnClose);
            view3D->scene = scene;
            view3D->scene->parentWidget = view3D;
            view3D->showMaximized();
        });

        QPushButton* sssButton = new QPushButton("Sub Surface Scattering");
        mainLayout->addWidget(sssButton);
        connect(sssButton, &QPushButton::clicked, this, [this]() {
            View3DGL* view3D= new View3DGL;
            Scene_7_::Scene_7* scene = new Scene_7_::Scene_7();
            view3D->setAttribute(Qt::WA_DeleteOnClose);
            view3D->scene = scene;
            view3D->scene->parentWidget = view3D;
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