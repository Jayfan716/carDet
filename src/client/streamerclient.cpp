#include "streamerclient.h"
#include "ui_streamerclient.h"
#include "streamerthread.h"
#include <numeric>
#include <QTime>
#include"yolo.h"
#include <QDebug>
#include <QMessageBox>
using namespace std;
using namespace cv;
using namespace cv::dnn;

#define parking R"(..\models\parking.onnx)"
#define column R"(..\models\column.onnx)"
#define person R"(..\models\person.onnx)"

//static int i = 0;

TheStreamerClient::TheStreamerClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TheStreamerClient)
{
    ui->setupUi(this);

    StreamerThread *thread = new StreamerThread(this);
    connect(thread, SIGNAL(signalNouvelleImage(QByteArray)), this, SLOT(slotNouvelleImage(QByteArray)));
    connect(this, SIGNAL(signalQuit()), thread, SLOT(slotQuit()));

    // Initialize the checkbox pointers
    checkBox = new QCheckBox();
    checkBox_2 = new QCheckBox();
    checkBox_3 = new QCheckBox();

    // Connect the stateChanged signals to the appropriate slots
    connect(checkBox, &QCheckBox::stateChanged, this, &TheStreamerClient::on_checkBox_stateChanged);
    connect(checkBox_2, &QCheckBox::stateChanged, this, &TheStreamerClient::on_checkBox_2_stateChanged);
    connect(checkBox_3, &QCheckBox::stateChanged, this, &TheStreamerClient::on_checkBox_3_stateChanged);

    thread->start();
}

TheStreamerClient::~TheStreamerClient()
{
    emit(signalQuit());

    QTime dieTime = QTime::currentTime().addMSecs( 100 );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }

    delete ui;
}
void useModel(vector<string> _className, string _model, Mat& img){
    Yolov5 v5;
    Net net;
    if(_className.size()!=0) v5._className = _className;
    v5.readModel(net, _model, false);
    vector<Output> output;
    v5.Detect(img, net, output);
    v5.drawPred(img, output);
}

void predict(Mat &img, int cls){
    //通过字符串获取要识别的类
    switch(cls){
        case 1:{    // 检测车和车位
            useModel({"occupied", "empty"}, parking, img);
            break;
        }
        case 2:{       // 检测柱子
            useModel({"column"}, column, img);
            break;
        }
        case 3:{    //检测人
            useModel({"person"}, person, img);
            break;
        }
        default: break; //否则不检测任何类
    }
}
void BGR2RGB(Mat bgrImg, Mat &rgbImg)
{
    rgbImg = bgrImg.clone();
    for(int i = 0;i < bgrImg.rows; i++)
    {
        for(int j = 0;j < bgrImg.cols; j++)
        {
            rgbImg.at<Vec3b>(i, j)[2] = bgrImg.at<Vec3b>(i, j)[0];
            rgbImg.at<Vec3b>(i, j)[0] = bgrImg.at<Vec3b>(i, j)[2];
        }
    }
}

Mat qimage_to_mat(const QImage& qimage)
{
    Mat mat(qimage.height(), qimage.width(), CV_8UC4, const_cast<uchar*>(qimage.bits()), qimage.bytesPerLine());
    Mat mat_rgb;
    cv::cvtColor(mat, mat_rgb, cv::COLOR_RGBA2BGR);
    return mat_rgb;
}

QPixmap mat2qpixmap(const cv::Mat& mat)
{
    QImage img;
    Mat Rgb;
    img = QImage((const uchar*)(mat.data), mat.cols, mat.rows,
    mat.cols * mat.channels(), QImage::Format_RGB888);
    QPixmap map = QPixmap::fromImage(img);
    return map;
}

void TheStreamerClient::slotNouvelleImage(QByteArray baImage)
{
    QPixmap pixImage;
    QImage image;
    if (!pixImage.loadFromData(baImage, "JPG"))
        return;
    image = pixImage.toImage();
    Mat mat=qimage_to_mat(image);
    predict(mat, classId);         //根据筛选类别进行预测推理
    QPixmap map = mat2qpixmap(mat);
    ui->lblImage->setPixmap(map);
}

int state0,state1,state2,state3,state4;

void TheStreamerClient::on_checkBox_stateChanged(int state)
{
    switch (state) {
        case Qt::Checked:
            /* 选中状态 */
            ui->checkBox->setChecked(true);
            ui->checkBox_2->setChecked(false);
            ui->checkBox_3->setChecked(false);
            classId=1;
            QMessageBox::information(NULL,"提示","选择了停车检测");
            break;
        case Qt::Unchecked:
            /* 未选中状态 */
//            QMessageBox::information(NULL,"test","取消停车检测");
            classId=0;
            break;
    }
}

void TheStreamerClient::on_checkBox_2_stateChanged(int state)
{
    switch (state) {
        case Qt::Checked:
            /* 选中状态 */
            ui->checkBox_2->setChecked(true);
            ui->checkBox->setChecked(false);
            ui->checkBox_3->setChecked(false);
            classId=2;
            QMessageBox::information(NULL,"提示","选择了柱子检测");
            break;
        case Qt::Unchecked:
            /* 未选中状态 */
//            QMessageBox::information(NULL,"test","取消柱子检测");
            classId=0;
            break;
    }
}

void TheStreamerClient::on_checkBox_3_stateChanged(int state)
{
    switch (state) {
        case Qt::Checked:
            /* 选中状态 */
            ui->checkBox_3->setChecked(true);
            ui->checkBox->setChecked(false);
            ui->checkBox_2->setChecked(false);
            classId=3;
            QMessageBox::information(NULL,"提示","选择了人检测");
            break;
        case Qt::Unchecked:
            /* 未选中状态 */
//            QMessageBox::information(NULL,"test","取消人检测");
            classId=0;
            break;
    }

}


// Function To Go FullScreen
int _isFullScreen = 0;
void TheStreamerClient::on_btnFS_clicked()
{
    if (!_isFullScreen) // If not on fullscreen
    {
        TheStreamerClient::showFullScreen(); // Full Screen mode
    }
    else // If on full screen
    {
        TheStreamerClient::showNormal(); // Put it off
    }
    _isFullScreen = !_isFullScreen; // Change the value of the var at the end
}

// Exit when btnQuit is clicked
void TheStreamerClient::on_btnQuit_clicked()
{
    exit(0);
}




