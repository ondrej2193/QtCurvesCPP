#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    update_ui();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_ui()
{
    this->ui->spinScale->setValue (this->ui->renderArea->scale());
    this->ui->spinIntervalLength->setValue(this->ui->renderArea->IntervalLength());
    this->ui->spinCount->setValue(this->ui->renderArea->StepCount());
}


void MainWindow::on_btnAstroid_clicked()
{
    // change background color for render area
    // add a function to change the background color
    this->ui->renderArea->setShape(RenderArea::Astroid);
    this->ui->renderArea->repaint();
    update_ui();
}
void MainWindow::on_btnCycloid_clicked()
{
    this->ui->renderArea->setShape(RenderArea::Cycloid);
    this->ui->renderArea->repaint();
    update_ui();
}

void MainWindow::on_btnHuygens_clicked()
{
    this->ui->renderArea->setShape(RenderArea::HuygensCycloid);
    this->ui->renderArea->repaint();
    update_ui();
}

void MainWindow::on_btnHypoCycloid_clicked()
{
    this->ui->renderArea->setShape(RenderArea::HypoCycloid);
    this->ui->renderArea->repaint();
    update_ui();
}

void MainWindow::on_btnLine_clicked()
{
    this->ui->renderArea->setShape(RenderArea::Line);
    this->ui->renderArea->repaint();
    update_ui();
}

void MainWindow::on_btnCircle_clicked()
{
    this->ui->renderArea->setShape(RenderArea::Circle);
    this->ui->renderArea->repaint();
    update_ui();
}

void MainWindow::on_btnElipse_clicked()
{
    this->ui->renderArea->setShape(RenderArea::Elipse);
    this->ui->renderArea->repaint();
    update_ui();
}

void MainWindow::on_btnFancy_clicked()
{
    this->ui->renderArea->setShape(RenderArea::Fancy);
    this->ui->renderArea->repaint();
    update_ui();
}

void MainWindow::on_btnStarrfish_clicked()
{
    this->ui->renderArea->setShape(RenderArea::Starfish);
    this->ui->renderArea->repaint();
    update_ui();
}

void MainWindow::on_spinScale_valueChanged(double scale)
{
    this->ui->renderArea->setScale(scale);
}

void MainWindow::on_spinIntervalLength_valueChanged(double IntervalLength)
{
    this->ui->renderArea->setIntervalLength(IntervalLength);
}

void MainWindow::on_spinCount_valueChanged(int StepCount)
{
    this->ui->renderArea->setStepCount(StepCount);
}

void MainWindow::on_btnBackgroundColor_clicked()
{
    // open a color picker dialog and change the button,s color
    QColor color = QColorDialog::getColor(this->ui->renderArea->backroundColor(), this, "Select Background Color");
    this->ui->renderArea->setBackgroundColor(color);
}

void MainWindow::on_btnLineColor_clicked()
{
    // open a color picker dialog and change the line,s color
    QColor color = QColorDialog::getColor(this->ui->renderArea->shapeColor(), this, "Select Color");
    this->ui->renderArea->setShapeColor(color);
}
