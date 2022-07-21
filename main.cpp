#include "HandwritingRecognition.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HandwritingRecognition w;
    w.show();
    return a.exec();
}
