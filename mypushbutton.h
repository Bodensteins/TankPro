#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H
#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyPushButton(QWidget *parent = nullptr);

    //构造函数（正常显示的图片路径，按下后显示的图片路径）
    MyPushButton(QString normalImg, QString pressImg="");

    //成员属性：保存用户传入的默认显示路径     按下后显示的图片路径
    QString normalImgPath;
    QString pressImgPath;

    //弹跳特效
    void zoom_down();  //按钮向下跳
    void zoom_up();  //按钮向上跳

signals:

};

#endif // MYPUSHBUTTON_H
