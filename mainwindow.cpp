#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &MainWindow::onLineEditTextChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_dirBtn_clicked()
{
    fileName = QFileDialog::getOpenFileName(this, tr("打开文件"), "",
                                            tr("Text Files (*.txt);;All Files (*)"));

    if ( fileName.isEmpty())
                    return;
    ui->lineEdit->setText(fileName);
}

/*void MainWindow::on_openBtn_clicked()
{
    QFile file(fileName);

    // 如果文件不存在，则创建它
    if (!file.exists()) {
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qWarning("Cannot create file for writing");
            return;
        }
        file.close();
    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Cannot open file for reading");
        return;
    }
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextStream in(&file);
    in.setCodec(codec);            //转为utf-8  --为了显示中文，不转会乱码
    QString content = in.readAll(); // 读取文件的全部内容

    // 设置QTextEdit的文本为文件内容
    ui->textEdit->setText(content);

    // 完成后关闭文件
    file.close();

}
*/

void MainWindow::on_openBtn_clicked()
{
    QMutexLocker locker(&fileMutex);
    QFile file(fileName);
    if (!file.exists()) {
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qWarning("Cannot create file for writing");
            return;
        }
        file.close();
    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Cannot open file for reading");
        return;
    }

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextStream in(&file);
    in.setCodec(codec);

    QString content;
    while (!in.atEnd()) {
        content += in.readLine() + "\n";
    }

    // 设置 QTextEdit 的文本为文件内容
    ui->textEdit->setText(content);

    // 完成后关闭文件
    file.close();
}

void MainWindow::on_saveBtn_clicked()
{
    QString text= ui->textEdit->toPlainText();
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        file.write(text.toUtf8());
        qDebug() << "写入成功";

    }
    else {
        // 处理文件打开失败的情况
        qDebug() << "无法打开文件：" << fileName;
    }

    file.close();
}

void MainWindow::onLineEditTextChanged()
{
    fileName = ui->lineEdit->text();
    qDebug() <<fileName;
}
