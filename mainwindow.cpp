#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_browseInButton_clicked()
{
    this->inDirPath = QFileDialog::getExistingDirectory(this, tr("Select the directory where JSON files are stored"),
                                                 "C:\\",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    ui->inDirPath->setText(this->inDirPath);
}

void MainWindow::on_browseOutButton_clicked()
{
    this->outDirPath = QFileDialog::getExistingDirectory(this, tr("Select the directory where merged JSON file will be saved"),
                                                 "C:\\",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    ui->outDirPath->setText(this->outDirPath);
}

void MainWindow::on_execButton_clicked()
{
    if (this->inDirPath.isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setText("Please select the directory where JSON files are stored.");
        msgBox.exec();
        return;
    }
    if (this->outDirPath.isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setText("Please select the directory where merged JSON file will be saved.");
        msgBox.exec();
        return;
    }

    QDir recoredDir(this->inDirPath);
    QStringList inFiles = recoredDir.entryList(QStringList("*.json"), QDir::NoDotAndDotDot  | QDir::Files);
    QJsonArray jsonEntries = QJsonArray();

    for (int i = 0; i < inFiles.size(); i++)
    {
        QMessageBox msgBox;
        msgBox.setText(this->inDirPath + "/" + inFiles.at(i));
        msgBox.exec();

        QFile file(this->inDirPath + "/" + inFiles.at(i));

        if(!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(0, "error", file.errorString());
            return;
        }

        QString line = file.readAll();

        file.close();

        QJsonDocument json = QJsonDocument::fromJson(line.toUtf8());
        QJsonArray jsonArray = json.array();

        for (int h = 0; h < jsonArray.size(); h++)
        {
            jsonEntries.append(jsonArray.at(h));
        }
    }

    QString outFileName = this->outDirPath + "\\GRP4_CENTRE-ARRAS_CENTRE-ALGER.JSON";
    QFile outFile(outFileName);

    if (outFile.exists())
    {
        outFile.remove();
    }

    if (!outFile.open(QIODevice::ReadWrite))
    {
        QMessageBox msgBox;
        msgBox.setText("Unable to write in the output file.");
        msgBox.exec();
        return;
    }

    QJsonDocument doc = QJsonDocument(jsonEntries);
    QTextStream outStream(&outFile);
    outStream << doc.toJson() << endl;

    outFile.close();
}






















