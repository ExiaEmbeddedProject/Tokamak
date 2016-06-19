#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTextStream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:

    void on_browseInButton_clicked();

    void on_browseOutButton_clicked();

    void on_execButton_clicked();

private:
    QStringList findFiles(const QStringList &files, const QString &text);
    Ui::MainWindow *ui;
    QString inDirPath;
    QString outDirPath;
};

#endif // MAINWINDOW_H
