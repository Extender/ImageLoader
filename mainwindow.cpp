#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dialog=new QFileDialog(this);
    dialog->setAcceptMode(QFileDialog::AcceptOpen);
    QStringList filters;
    filters<<"All images (*.jpg *.jpeg *.png *.gif *.bmp)"
           <<"JPEG images (*.jpg *.jpeg)"
           <<"PNG images (*.png)"
           <<"GIF images (*.gif)"
           <<"Bitmaps (*.bmp)";
    dialog->setNameFilters(filters);
    dialog->setDirectory(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
    connect(dialog,SIGNAL(fileSelected(QString)),this,SLOT(dialogFileSelected(QString)));
    connect(ui->browseBtn,SIGNAL(clicked(bool)),this,SLOT(browseBtnClicked()));
    connect(ui->loadBtn,SIGNAL(clicked(bool)),this,SLOT(loadBtnClicked()));
    connect(ui->fitToWindowBtn,SIGNAL(clicked(bool)),this,SLOT(fitToWindow()));
    connect(ui->resetZoomBtn,SIGNAL(clicked(bool)),this,SLOT(resetZoom()));
    image=0;
    scene=new QGraphicsScene();
    pixmapItem=new QGraphicsPixmapItem();
    scene->addItem(pixmapItem);
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::browseBtnClicked()
{
    dialog->exec();
}

void MainWindow::loadBtnClicked()
{
    QString path=ui->pathBox->text();
    if(path.length()==0)
    {
        QMessageBox::critical(this,"Error","No file selected.");
        return;
    }
    QFile f(path);
    if(!f.exists())
    {
        QMessageBox::critical(this,"Error","The selected file does not exist.");
        return;
    }
    image=new QImage(path);
    if(image->isNull())
    {
        QMessageBox::critical(this,"Error","The selected file has an unsupported format.");
        return;
    }
    scene->setSceneRect(0,0,image->width(),image->height());
    pixmapItem->setPixmap(QPixmap::fromImage(*image));
    ui->graphicsView->viewport()->update();
    fitToWindow();
}

void MainWindow::fitToWindow()
{
    if(image==0||image->isNull())
        return;
    int width=image->width();
    int height=image->height();
    QRect rect=ui->graphicsView->contentsRect();
    int availableWidth=rect.width()-ui->graphicsView->verticalScrollBar()->width();
    int availableHeight=rect.height()-ui->graphicsView->horizontalScrollBar()->height();
    if((width-availableWidth)>(height-availableHeight))
        ui->graphicsView->setZoomFactor((float)((float)availableWidth)/((float)width));
    else if(height>availableHeight)
        ui->graphicsView->setZoomFactor((float)((float)availableHeight)/((float)height));
    else
        ui->graphicsView->setZoomFactor(1.0);
}

void MainWindow::resetZoom()
{
    ui->graphicsView->setZoomFactor(1.0);
}

void MainWindow::dialogFileSelected(QString path)
{
    ui->pathBox->setText(path);
}
