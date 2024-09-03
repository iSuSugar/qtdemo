#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMutex>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:

    void on_dirBtn_clicked();

    void on_openBtn_clicked();

    void on_saveBtn_clicked();
    void onLineEditTextChanged();

private:
    Ui::MainWindow *ui;
    QString  fileName;
    QMutex fileMutex;
};
#endif // MAINWINDOW_H
