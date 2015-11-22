#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Initialize();

private:
    Ui::MainWindow *ui;
    QString TranslateToEnglish(QString initialWords);
    void SetUpConnections();
    void SendListOfWordsToBeTranslatedIntoEnglish();

private slots:

    void Translate_click();


};

#endif // MAINWINDOW_H
