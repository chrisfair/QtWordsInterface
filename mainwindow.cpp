#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QDebug>

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

//!
//! Initialization
void MainWindow::Initialize()
{


    SetUpConnections();


}


void MainWindow::SetUpConnections()
{
    connect(ui->Translate,SIGNAL(clicked()),this, SLOT(Translate_click()));
    connect(ui->ClearText,SIGNAL(clicked()),this,SLOT(ClearText_click()));

}

void MainWindow::ClearText_click()
{
    if (ui->englishToLatin->isChecked())
    {
        qDebug()<<"You want to delete the latin window";
    }

    else if (ui->latinToEnglish->isChecked())
    {
        qDebug()<<"You want to delete the English window";
    }
}

QString MainWindow::TranslateToEnglish(QString LatinWordToTranslate)
{

    QString stringResultFromWhitakersWords;

    if (LatinWordToTranslate.count() > 0)
    {
        QString command = "words";
        command += " ";
        command += LatinWordToTranslate;
        QProcess whitakersWords;
        whitakersWords.setReadChannel(QProcess::StandardOutput);
        whitakersWords.start(command);
        while (whitakersWords.waitForFinished()) {};
        QByteArray resultFromWhitakersWords;
        resultFromWhitakersWords.append(whitakersWords.readAll());
        stringResultFromWhitakersWords = resultFromWhitakersWords.data();

        QStringList noLines = stringResultFromWhitakersWords.split('\n');
        noLines.removeAt(0);
        noLines.removeLast();
        noLines.removeLast();

        stringResultFromWhitakersWords.clear();
        stringResultFromWhitakersWords = noLines.join('\n');


    }

    return stringResultFromWhitakersWords;
}


void MainWindow::SendListOfWordsToBeTranslatedIntoEnglish()
{

    QString originalText = ui->EditLatin->toPlainText();
    QString finalTranslation;
    originalText.remove('.');
    originalText.remove(',');
    originalText.remove(';');
    originalText.remove("/n/n~~~");
    QStringList noSpaces = originalText.split(' ');
    foreach(QString string, noSpaces)
    {

        finalTranslation.append(TranslateToEnglish(string));
        finalTranslation.append("\n\n");

    }



    ui->EditEnglish->append(finalTranslation);


}

void MainWindow::Translate_click()
{


    if( ui->englishToLatin->isChecked())
    {
        qDebug()<<"I cannot translate English into Latin yet";


    }
    else if (ui->latinToEnglish)
    {
        SendListOfWordsToBeTranslatedIntoEnglish();
    }

}

