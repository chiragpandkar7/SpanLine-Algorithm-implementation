#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QColorDialog>
#include<QTime>
#include<iostream>

#include "QMouseEvent"
using namespace  std;

// Initialize global variables
QColor color = qRgb(255, 255, 255);
QImage img(500, 500, QImage::Format_RGB888);

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Initialize variables in the constructor
    start = true;
    count = 0;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Function to introduce a delay in milliseconds
void delay(int delayTime)
{
    QTime waitTime = QTime::currentTime().addMSecs(delayTime);
    while (QTime::currentTime() < waitTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 400);
    }
}

// DDA (Digital Differential Analyzer) line drawing algorithm
void MainWindow::dda(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;

    float length = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);

    float xinc = dx / length;
    float yinc = dy / length;

    int i = 0;

    while (i < length)
    {
        img.setPixel(x1, y1, color.rgb());
        x1 += xinc;
        y1 += yinc;
        i++;
    }

    ui->label->setPixmap(QPixmap::fromImage(img));
}

// Mouse press event to capture points for polygon creation
void MainWindow::mousePressEvent(QMouseEvent* event)
{
    if (start)
    {
        a[count] = event->pos().x();
        b[count] = event->pos().y();

        if (event->button() == Qt::RightButton)
        {
            dda(a[count - 1], b[count - 1], a[0], b[0]);
            start = false;
            cout << "Polygon complete\n";
        }
        else
        {
            if (count > 0)
            {
                dda(a[count], b[count], a[count - 1], b[count - 1]);
            }
            count++;
        }
    }
}

// Button click event to choose a color using QColorDialog
void MainWindow::on_pushButton_clicked()
{
    color = QColorDialog::getColor();
}

// Button click event to fill the polygon using the Scanline Fill Algorithm
void MainWindow::on_pushButton_2_clicked()
{
    // Initialize variables for slope calculations and sorting
    float dy, dx, slope[500], xi[500], temp;
    int i, m, k, n, ver;

    // Closing the polygon by connecting the last point to the first point
    a[count] = a[0];
    b[count] = b[0];

    // Calculate slopes for each edge of the polygon
    for (i = 0; i < count; i++)
    {
        dy = b[i + 1] - b[i];
        dx = a[i + 1] - a[i];

        if (dy == 0.0f)
            slope[i] = 1;
        else if (dx == 0.0f)
            slope[i] = 0.0;
        else
            slope[i] = dx / dy;
    }

    // Loop through each scanline (rows of the image)
    for (m = 0; m < 500; m++)
    {
        k = 0;

        // Check intersections with each edge and store the x-intercepts
        for (i = 0; i < count; i++)
        {
            if (((b[i] <= m) && (b[i + 1] > m)) || ((b[i] > m) && (b[i + 1] <= m)))
            {
                xi[k] = a[i] + (slope[i] * (m - b[i]));
                k++;
            }
        }

        // Sort the x-intercepts in descending order
        for (n = 0; n < k - 1; n++)
        {
            for (ver = 0; ver < k - n - 1; ver++)
            {
                if (xi[ver + 1] > xi[ver])
                {
                    temp = xi[ver];
                    xi[ver] = xi[ver + 1];
                    xi[ver + 1] = temp;
                }
            }
        }

        // Draw line segments between pairs of x-intercepts to fill the polygon
        for (i = 0; i < k; i += 2)
        {
            delay(20);
            dda(xi[i], m, xi[i + 1], m);
        }
    }
}
