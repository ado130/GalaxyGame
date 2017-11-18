#include <QString>
#include <QtTest>
#include "question.hh"
#include "galaxy.hh"
#include "itemsingalaxy.hh"
#include "igalaxy.hh"
#include "ship.hh"
#include "cargoship.hh"
#include "warpdrive.hh"
#include "stateexception.hh"
#include "ioexception.hh"
#include "formatexception.hh"
#include "objectnotfoundexception.hh"

class QuestionTest : public QObject
{
    Q_OBJECT

public:
    QuestionTest();

private Q_SLOTS:
    void init();
    void testGenerate();
    void testCheck();

private:
    //std::shared_ptr<Student::Question> question_;
    //std::shared_ptr<Student::Galaxy> galaxy_;
    //std::shared_ptr<ItemsInGalaxy> itemsInGalaxy_;

};

QuestionTest::QuestionTest()
{
}

void QuestionTest::init()
{
    //question_.reset();
    //galaxy_ = std::make_shared<Student::Galaxy>();
    //itemsInGalaxy_ = std::make_shared<ItemsInGalaxy>();
    //question_ = std::make_shared<Student::Question>(galaxy_, itemsInGalaxy_);
}

void QuestionTest::testGenerate()
{

}

void QuestionTest::testCheck()
{

}

QTEST_APPLESS_MAIN(QuestionTest)

#include "questiontest.moc"
