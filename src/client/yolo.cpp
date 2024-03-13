#include"yolo.h"
#include <QDebug>

using namespace std;
using namespace cv;
using namespace cv::dnn;


// Yolov5::Yolov5() {}
// Yolov5::~Yolov5() {}

void Yolov5::LetterBox(const Mat& image, Mat& outImage, Vec4d& params, const Size& newShape,
    bool autoShape, bool scaleFill, bool scaleUp, int stride, const cv::Scalar& color)
{
    if (false) {
        int maxLen = MAX(image.rows, image.cols);
        outImage = Mat::zeros(Size(maxLen, maxLen), CV_8UC3);
        image.copyTo(outImage(Rect(0, 0, image.cols, image.rows)));
        params[0] = 1;
        params[1] = 1;
        params[3] = 0;
        params[2] = 0;
    }

    cv::Size shape = image.size();
    float r = std::min((float)newShape.height / (float)shape.height,
        (float)newShape.width / (float)shape.width);
    if (!scaleUp)
        r = std::min(r, 1.0f);

    float ratio[2]{ r, r };
    int new_un_pad[2] = { (int)std::round((float)shape.width * r),(int)std::round((float)shape.height * r) };

    auto dw = (float)(newShape.width - new_un_pad[0]);
    auto dh = (float)(newShape.height - new_un_pad[1]);

    if (autoShape)
    {
        dw = (float)((int)dw % stride);
        dh = (float)((int)dh % stride);
    }
    else if (scaleFill)
    {
        dw = 0.0f;
        dh = 0.0f;
        new_un_pad[0] = newShape.width;
        new_un_pad[1] = newShape.height;
        ratio[0] = (float)newShape.width / (float)shape.width;
        ratio[1] = (float)newShape.height / (float)shape.height;
    }

    dw /= 2.0f;
    dh /= 2.0f;

    if (shape.width != new_un_pad[0] && shape.height != new_un_pad[1])
    {
        cv::resize(image, outImage, cv::Size(new_un_pad[0], new_un_pad[1]));
    }
    else {
        outImage = image.clone();
    }

    int top = int(std::round(dh - 0.1f));
    int bottom = int(std::round(dh + 0.1f));
    int left = int(std::round(dw - 0.1f));
    int right = int(std::round(dw + 0.1f));
    params[0] = ratio[0];
    params[1] = ratio[1];
    params[2] = left;
    params[3] = top;
    cv::copyMakeBorder(outImage, outImage, top, bottom, left, right, cv::BORDER_CONSTANT, color);
}



bool Yolov5::readModel(Net& net, string& netPath, bool isCuda = false) {
    try {

        //net = readNet(netPath);
        net = readNetFromONNX(netPath);
        qDebug()<<"readNet ok!" ;
#if CV_VERSION_MAJOR==4 &&CV_VERSION_MINOR==7&&CV_VERSION_REVISION==0
        net.enableWinograd(false);  //bug of opencv4.7.x in AVX only platform ,https://github.com/opencv/opencv/pull/23112 and https://github.com/opencv/opencv/issues/23080
        //net.enableWinograd(true);		//If your CPU supports AVX2, you can set it true to speed up
#endif
    }
    catch (const std::exception&) {
        qDebug()<<"模型加载错误！请检查！" ;
        return false;
    }
    //cuda
    if (isCuda) {
        net.setPreferableBackend(cv::dnn::DNN_BACKEND_CUDA);
        net.setPreferableTarget(cv::dnn::DNN_TARGET_CUDA);
    }
    //cpu
    else {
        net.setPreferableBackend(cv::dnn::DNN_BACKEND_DEFAULT);
        net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
    }
    return true;
}
bool Yolov5::Detect(Mat& SrcImg, Net& net, vector<Output>& output) {
    Mat blob;
//    int col = SrcImg.cols;
//    int row = SrcImg.rows;
//    int maxLen = MAX(col, row);
    Mat netInputImg = SrcImg.clone();
    Vec4d params;
    LetterBox(SrcImg, netInputImg, params, cv::Size(_netWidth, _netHeight));
    blobFromImage(netInputImg, blob, 1 / 255.0, cv::Size(_netWidth, _netHeight), cv::Scalar(0, 0, 0), true, false);
    net.setInput(blob);
    std::vector<Mat> netOutputImg;
    net.forward(netOutputImg, net.getUnconnectedOutLayersNames());
    std::vector<int> classIds;//结果id数组
    std::vector<float> confidences;//结果每个id对应置信度数组
    std::vector<cv::Rect> boxes;//每个id矩形框
    int net_width = _className.size() + 5;  //输出的网络宽度是类别数+5
    int net_out_width = netOutputImg[0].size[2];
    assert(net_out_width == net_width);  //模型类别数目不对
    float* pdata = (float*)netOutputImg[0].data;
    int net_height = netOutputImg[0].size[1];
    for (int r = 0; r < net_height; ++r) {
        float box_score = pdata[4]; ;//获取每一行的box框中含有某个物体的概率
        if (box_score >= _classThreshold) {
            Mat scores(1, _className.size(), CV_32FC1, pdata + 5);
            Point classIdPoint;
            double max_class_socre;
            minMaxLoc(scores, 0, &max_class_socre, 0, &classIdPoint);
            max_class_socre = max_class_socre* box_score;
            if (max_class_socre >= _classThreshold) {
                //rect [x,y,w,h]
                float x = (pdata[0] - params[2]) / params[0];
                float y = (pdata[1] - params[3]) / params[1];
                float w = pdata[2] / params[0];
                float h = pdata[3] / params[1];
                int left = MAX(round(x - 0.5 * w +0.5), 0);
                int top = MAX(round(y - 0.5 * h+0.5 ), 0);
                classIds.push_back(classIdPoint.x);
                confidences.push_back(max_class_socre );
                boxes.push_back(Rect(left, top, int(w + 0.5), int(h + 0.5)));
            }
        }
        pdata += net_width;//下一行

    }

    //执行非最大抑制以消除具有较低置信度的冗余重叠框（NMS）
    vector<int> nms_result;
    NMSBoxes(boxes, confidences, _classThreshold, _nmsThreshold, nms_result);
    for (int i = 0; i < nms_result.size(); i++) {
        int idx = nms_result[i];
        Output result;
        result.id = classIds[idx];
        result.confidence = confidences[idx];
        result.box = boxes[idx];
        output.push_back(result);
    }
    if (output.size())
        return true;
    else
        return false;
}


//输入原始图片、结果矩阵、色彩矩阵
void Yolov5::drawPred(Mat& img, vector<Output> result) {
    vector<Scalar> color;
        srand(time(0));
        for (int i = 0; i < 80; i++) {
            int b = rand() % 256;
            int g = rand() % 256;
            int r = rand() % 256;
            color.push_back(Scalar(b, g, r));
        }
    for (int i = 0; i < result.size(); i++) { //在图片的尺度内遍历
        int left, top;    //图片的x，y坐标
        left = result[i].box.x;
        top = result[i].box.y;
        int color_num = i;    //给图片上色
        rectangle(img, result[i].box, color[result[i].id], 2, 8);

        string label = _className[result[i].id] + ":" + to_string(result[i].confidence);

        int baseLine;
        Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
        top = max(top, labelSize.height);
        putText(img, label, Point(left, top), FONT_HERSHEY_SIMPLEX, 1, color[result[i].id], 2);
    }
}
