#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QStandardPaths>
#include <QGraphicsPixmapItem>
#include <QStringList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QFileDialog *dialog;
    QImage *image;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *pixmapItem;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void browseBtnClicked();
    void loadBtnClicked();
    void fitToWindow();
    void resetZoom();
    void dialogFileSelected(QString path);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
