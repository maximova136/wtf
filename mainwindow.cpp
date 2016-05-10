#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <vector>
#include <iostream>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    scene = new QGraphicsScene(this);
//    scene->setSceneRect(0,0,50,50);
//    ui->graphicsView->setScene(scene);
//    ui->graphicsView->setSceneRect(0,0,50,50);

    scene = new paintScene();
    scene->setSceneRect(0,0, ui->graphicsView->width()-40, ui->graphicsView->height()-30);
    ui->graphicsView->setScene(scene);


    QPushButton *ellipseButton = new QPushButton(tr("&Ellipse"));
    ellipseButton->setObjectName(tr("Ellipse"));

    QPushButton *rectangleButton = new QPushButton(tr("&Rectangle"));
    rectangleButton->setObjectName(tr("Rectangle"));
    QPushButton *triangleButton = new QPushButton(tr("&Triangle"));
    triangleButton->setObjectName(tr("Triangle"));
    QPushButton *lineButton = new QPushButton(tr("&Line"));
    lineButton->setObjectName(tr("Line"));
    QPushButton *curveButton = new QPushButton(tr("&Curve"));
    curveButton->setObjectName(tr("Curve"));
    QPushButton *polygonButton = new QPushButton(tr("&Polygon"));
    polygonButton->setObjectName(tr("Polygon"));
    QPushButton *brushButton = new QPushButton(tr("&Brush"));
    brushButton->setObjectName(tr("Brush"));
    QPushButton *textButton = new QPushButton(tr("&Text"));
    brushButton->setObjectName(tr("Text"));

    allButtons.push_back(brushButton);
    allButtons.push_back(ellipseButton);
    allButtons.push_back(rectangleButton);
    allButtons.push_back(triangleButton);
    allButtons.push_back(lineButton);
    allButtons.push_back(curveButton);
    allButtons.push_back(polygonButton);
    allButtons.push_back(textButton);


    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addLayout(createToolsGroup());
    hbox->addWidget(ui->graphicsView);
    hbox->addWidget(ui->pushButton);

    /*QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(ui->menuBar);
    vbox->addWidget(ui->mainToolBar);
    vbox->addLayout(hbox);*/

    for (unsigned int i = 0; i < allButtons.size(); i++)
    {
        //connect(allButtons[i],SIGNAL(clicked(int)),this, SLOT(on_allButtons_clicked(int)));
       // connect(allButtons[i],SIGNAL(clicked()),this, SLOT(on_allButtons_clicked()));
        connect(allButtons[i],SIGNAL(clicked()),this, SLOT(on_allButtons_clicked()));
        allButtons[i]->setCheckable(true);
    }
    allButtons[0]->setChecked(true);
    QGraphicsDropShadowEffect* pShadow = new QGraphicsDropShadowEffect;
    pShadow->setXOffset(2);
    pShadow->setYOffset(2);
    allButtons[0]->setGraphicsEffect(pShadow);
    ui->centralWidget->setLayout(hbox);


    //ui->centralWidget->setLayout(createToolsGroup());


}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    QBrush blueBrush(Qt::blue);
    QPen blackPen(Qt::black);

    blackPen.setWidth(3);

    this->ellipse = this->scene->addEllipse(0,0,30,30,blackPen, blueBrush);

    this->ellipse->setFlag(QGraphicsItem::ItemIsMovable);

    //QString path = QFileDialog::getOpenFileName(0,tr("������� ���� ���� ������"),QDir::homePath(), QObject::tr("���� SQLite (*.db);;��� ����� (*.*)"));
    //qDebug()<<path;
    QColor col = QColorDialog::getColor(Qt::blue);
    qDebug()<<col;


}

/*void MainWindow::on_Buttons_clicked(int but)
{

    std::cout<<but<<" CLICKED!"<<std::endl;
}*/

void MainWindow::on_allButtons_clicked()
{
    QPushButton *currentButton = (QPushButton*) sender();
    qDebug()<<currentButton->objectName();

    for (unsigned int i = 0; i < allButtons.size(); i++)
    {
        allButtons[i]->setChecked(false);
        allButtons[i]->setGraphicsEffect(0);
    }
    currentButton->setChecked(true);
    QGraphicsDropShadowEffect* pShadow = new QGraphicsDropShadowEffect;
    pShadow->setXOffset(2);
    pShadow->setYOffset(2);
    currentButton->setGraphicsEffect(pShadow);
    this->scene->setSettings(currentButton->objectName(),QColor(Qt::darkBlue),Qt::DotLine,QColor(Qt::yellow),Qt::BDiagPattern);
}


QVBoxLayout *MainWindow::createToolsGroup()
{

    QVBoxLayout *vbox = new QVBoxLayout;

    for (int i = 0; i < allButtons.size();i++)
    {
        vbox->addWidget(allButtons[i]);
    }

    return vbox;
}

void MainWindow::setSettings()
{

}

/*
void MainWindow::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    this->scene->addEllipse(event->scenePos().x() - 5, event->scenePos().y() - 5, 10 , 10, QPen(Qt::NoPen), QBrush(Qt::blue));
    //previousPoint = this->scene->event->scenePos();
    previousPoint = event->scenePos();
    qDebug()<<"mouse pressed";
}


void MainWindow::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->scene->addLine(previousPoint.x(), previousPoint.y(), event->scenePos().x(), event->scenePos().y(), QPen(Qt::red,10,Qt::SolidLine, Qt::RoundCap));
    previousPoint = event->scenePos();
    qDebug()<<"mouse moved";

}*/
