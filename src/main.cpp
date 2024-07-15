#include <QApplication>
#include <QFile>
#include <QMainWindow>
#include "mainwindow.h"

void applyStyleSheet(QApplication &app) {
    QFile file(":/stylesheet.qss");
    if (!file.exists()) {
        qWarning("未找到样式表");
        return;
    }
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString styleSheet = stream.readAll();
        app.setStyleSheet(styleSheet);
        file.close();
    } else {
        qWarning("无法加载样式表");
    }
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    applyStyleSheet(app);

    MainWindow w;
    w.show();
    return app.exec();
}
