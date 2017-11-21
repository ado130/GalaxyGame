#ifndef QUESTION_H
#define QUESTION_H

#include <QObject>
#include <memory>

#include "galaxy.hh"
#include "planet.hh"
#include "itemsingalaxy.hh"

//! Number of questions for one game
#define MAX_QUESTIONS 5

//! pair of string and another pair if string and string to store questions; first string = goods, second string = star system, thirth string = planet
typedef std::pair < std::string, std::pair< std::string, std::string > > questions_t;

namespace Student {
class Question : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Question constructor
     * @param galaxy Galaxy
     * @param itemsInGalaxy all items existing in galaxy
     * @param parent parent QObject
     */
    Question(std::shared_ptr<Student::Galaxy> galaxy,
             std::shared_ptr<ItemsInGalaxy> itemsInGalaxy,
             QObject *parent = 0);

    /**
     * @brief getPlanetsByStarSystem Return a ShipVector which contain only planets
     * @param ships ShipVector
     * @return ShipVector
     */
    Common::IGalaxy::ShipVector getPlanetsByStarSystem(Common::IGalaxy::ShipVector ships);

    /**
     * @brief generateQuestions Generate questions for player
     */
    void generateQuestions();

    /**
     * @brief getActiveQuestions
     * @return Return list of active questions
     */
    QList<questions_t> getActiveQuestions() const;

    /**
     * @brief getCompletedQuestions
     * @return Return list of completed questions
     */
    QList<questions_t> getCompletedQuestions() const;

    /**
     * @brief checkQuestion Check if player successfully complete a question
     * @param starSystem Starsystem whose player wants to sell the goods
     * @param planet Planet whose player wants to sell the goods
     * @param goods Goods which player is trying to sell
     * @return Return true/false if it is correct or not, respectively
     */
    bool checkQuestion(std::string starSystem, std::string planet, std::string goods);
private:
    //! galaxy_ Galaxy
    std::shared_ptr<Student::Galaxy> galaxy_;

    //! itemsInGalaxy_ is ised to store all items existing in galaxy
    std::shared_ptr<ItemsInGalaxy> itemsInGalaxy_;

    //! questionList_ is used to store all questions
    QList<questions_t> questionList_;

    //! activeQuestions_ is used to store all active questions
    QList<questions_t> activeQuestions_;

    //! completedQuestions_ is used to stode all completed questions
    QList<questions_t> completedQuestions_;

Q_SIGNALS:
    /**
     * @brief allQuestionsDone A signal which is emitted if player complete all questions
     */
    void allQuestionsDone();

    /**
     * @brief questionCompleted A signal which is emitted if player complete one question.
     */
    void questionCompleted();
};
}
#endif // QUESTION_H
