#ifndef QUESTIONDLG_H
#define QUESTIONDLG_H

#include "question.hh"

#include <QDialog>

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

    //! active_ is used to store all active questions
    QList<questions_t> active_;

    //! completed_ is used to stode all completed questions
    QList<questions_t> completed_;

    /**
     * @brief showQuestions Method which show active and completed questions in a widget
     */
    void showQuestions();
};

#endif // QUESTIONDLG_H
