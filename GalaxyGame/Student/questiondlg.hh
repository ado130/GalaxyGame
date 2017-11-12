#ifndef QUESTIONDLG_H
#define QUESTIONDLG_H

#include <QDialog>

typedef std::pair<std::string, std::pair< std::string, std::string > > questions_t;

namespace Ui {
class QuestionDlg;
}

class QuestionDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QuestionDlg(QList<questions_t> active, QList<questions_t> completed, QWidget *parent = 0);
    ~QuestionDlg();

private:
    Ui::QuestionDlg *ui;
    QList<questions_t> active_;
    QList<questions_t> completed_;

    void showQuestions();
};

#endif // QUESTIONDLG_H
