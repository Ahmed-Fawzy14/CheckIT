#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <fstream>

#include "RabinKarp.h"
#include "RKphrases.h"
#include"RKsentences.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Ui::MainWindow *ui;
    std::ifstream inputFileStream; // Input file stream for uploaded file
    RabinKarp rabinKarp; // Rabin-Karp object for plagiarism detection
    Phrases phrases; // Phrases object for plagiarism detection
    Sentences sentences; // Sentences object for plagiarism detection
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_pushButton_3_clicked();

private:

#endif // MAINWINDOW_H
};
