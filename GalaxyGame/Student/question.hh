#ifndef QUESTION_H
#define QUESTION_H

#include <QObject>
#include <memory>

#include "galaxy.hh"
#include "planet.hh"
#include "itemsingalaxy.hh"

#define MAX_QUESTIONS 15

typedef std::pair < std::string, std::pair< std::string, std::string > > questions_t;

namespace Student {
class Question : public QObject
{
    Q_OBJECT
public:
    Question(std::shared_ptr<Student::Galaxy> galaxy,
             std::shared_ptr<ItemsInGalaxy> itemsInGalaxy,
             QObject *parent = 0);

     void generateQuestions();
     QList<questions_t> activeQuestions() const;
     QList<questions_t> completedQuestions() const;

private:
     std::shared_ptr<Student::Galaxy> galaxy_;
     std::shared_ptr<ItemsInGalaxy> itemsInGalaxy_;
     QList<questions_t> questionList_;
     QList<questions_t> activeQuestions_;
     QList<questions_t> completedQuestions_;
};
}
#endif // QUESTION_H
