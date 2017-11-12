#include "questiondlg.hh"
#include "ui_questiondlg.h"

QuestionDlg::QuestionDlg(QList<questions_t> active, QList<questions_t> completed, QWidget *parent) :
    QDialog(parent), ui(new Ui::QuestionDlg), active_(active), completed_(completed)
{
    ui->setupUi(this);

    showQuestions();
}

QuestionDlg::~QuestionDlg()
{
    delete ui;
}

void QuestionDlg::showQuestions()
{
    for(auto k : active_)
    {
        QString text = "Planet " + QString(k.second.second.data()) + "in " + QString(k.second.first.data()) + " Star system" +
                " is looking for " + QString(k.first.data()) + "\n";
        ui->lwActive->addItem(text);
    }

    for(auto k : completed_)
    {
        QString text = "Planet " + QString(k.second.second.data()) + "in" + QString(k.second.first.data()) + "Star system" +
                "is looking for " + QString(k.first.data());
        ui->lwActive->addItem(text);
    }
}
