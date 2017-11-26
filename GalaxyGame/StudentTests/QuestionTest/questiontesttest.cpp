#include <QString>
#include <QtTest>

#include <memory>

#include "question.hh"
#include "galaxy.hh"
#include "planet.hh"
#include "itemsingalaxy.hh"
#include "eventhandler.hh"
#include "planetcoredrive.hh"

#include "igalaxy.hh"
#include "ship.hh"
#include "cargoship.hh"
#include "warpdrive.hh"
#include "stateexception.hh"
#include "objectnotfoundexception.hh"

class QuestionTestTest : public QObject
{
    Q_OBJECT

public:
    QuestionTestTest();

private Q_SLOTS:
    void init();
    void testConstructor();
    void testGenerateQuestions();
    void testCompleteOneQuestion();
    void testAllQuestions();

private:
    std::shared_ptr<Student::Galaxy> galaxy_;
    std::shared_ptr<Student::Question> question_;
    std::shared_ptr<Student::ItemsInGalaxy> itemsInGalaxy_;
    std::shared_ptr<Student::SimpleTradeGoods> simpleTradeGoods_;
    std::shared_ptr<Student::EventHandler> event_;
    Student::SimpleTradeGoods goods_;
};

QuestionTestTest::QuestionTestTest()
{
    Common::utilityInit(123);
}

void QuestionTestTest::init()
{
    QVERIFY2(true, "Failure");      // just in case
    galaxy_.reset();
    question_.reset();
    itemsInGalaxy_.reset();
    event_.reset();
    simpleTradeGoods_.reset();
    simpleTradeGoods_ = std::make_shared<Student::SimpleTradeGoods>();
    event_ = std::make_shared<Student::EventHandler>();
    galaxy_ = std::make_shared<Student::Galaxy>();
    itemsInGalaxy_ = std::make_shared<Student::ItemsInGalaxy>();
    question_ = std::make_shared<Student::Question>(galaxy_, itemsInGalaxy_);
}

void QuestionTestTest::testConstructor()
{
    QVERIFY2(galaxy_->getShips()->size() == 0, "No ships should be in a Galaxy when it is created");
    QVERIFY_EXCEPTION_THROWN(galaxy_->getRandomSystem(), Common::ObjectNotFoundException);

    QVERIFY2(question_->getActiveQuestions().count() == 0 && question_->getCompletedQuestions().count() == 0, "No questions should be there when it is created");
}

void QuestionTestTest::testGenerateQuestions()
{
    auto starSystem1 = std::make_shared<Common::StarSystem>("Sol", Common::StarSystem::ECONOMY_TYPE::Agriculture, 1, 10000, Common::Point(13,6));
    auto starSystem2 = std::make_shared<Common::StarSystem>("Sirius", Common::StarSystem::ECONOMY_TYPE::Agriculture, 2, 10000, Common::Point(15,6));
    auto starSystem3 = std::make_shared<Common::StarSystem>("Polar", Common::StarSystem::ECONOMY_TYPE::HiTech, 3, 5000, Common::Point(20,12));
    auto starSystem4 = std::make_shared<Common::StarSystem>("Mira", Common::StarSystem::ECONOMY_TYPE::Tourism, 4, 15000, Common::Point(10,8));
    auto starSystem5 = std::make_shared<Common::StarSystem>("Alpha Centauri", Common::StarSystem::ECONOMY_TYPE::Refinery, 5, 15000, Common::Point(1,1));
    galaxy_->addStarSystem(starSystem1);
    galaxy_->addStarSystem(starSystem2);
    galaxy_->addStarSystem(starSystem3);
    galaxy_->addStarSystem(starSystem4);
    galaxy_->addStarSystem(starSystem5);

    auto ship1 = std::make_shared<Student::Planet> (std::make_shared<Student::PlanetCoreDrive>(galaxy_), galaxy_->getStarSystemByName("Sol"), event_, goods_);
    auto ship2 = std::make_shared<Student::Planet> (std::make_shared<Student::PlanetCoreDrive>(galaxy_), galaxy_->getStarSystemByName("Sirius"), event_, goods_);
    auto ship3 = std::make_shared<Student::Planet> (std::make_shared<Student::PlanetCoreDrive>(galaxy_), galaxy_->getStarSystemByName("Polar"), event_, goods_);
    auto ship4 = std::make_shared<Student::Planet> (std::make_shared<Student::PlanetCoreDrive>(galaxy_), galaxy_->getStarSystemByName("Mira"), event_, goods_);
    auto ship5 = std::make_shared<Student::Planet> (std::make_shared<Student::PlanetCoreDrive>(galaxy_), galaxy_->getStarSystemByName("Alpha Centauri"), event_, goods_);
    galaxy_->addShip(ship1);
    galaxy_->addShip(ship2);
    galaxy_->addShip(ship3);
    galaxy_->addShip(ship4);
    galaxy_->addShip(ship5);

    question_->generateQuestions();

    QVERIFY2(question_->getActiveQuestions().count() == MAX_QUESTIONS, "There should exists some questions");
}

void QuestionTestTest::testCompleteOneQuestion()
{
    auto starSystem1 = std::make_shared<Common::StarSystem>("Sol", Common::StarSystem::ECONOMY_TYPE::Agriculture, 1, 10000, Common::Point(13,6));
    auto starSystem2 = std::make_shared<Common::StarSystem>("Sirius", Common::StarSystem::ECONOMY_TYPE::Agriculture, 2, 10000, Common::Point(15,6));
    auto starSystem3 = std::make_shared<Common::StarSystem>("Polar", Common::StarSystem::ECONOMY_TYPE::HiTech, 3, 5000, Common::Point(20,12));
    auto starSystem4 = std::make_shared<Common::StarSystem>("Mira", Common::StarSystem::ECONOMY_TYPE::Tourism, 4, 15000, Common::Point(10,8));
    auto starSystem5 = std::make_shared<Common::StarSystem>("Alpha Centauri", Common::StarSystem::ECONOMY_TYPE::Refinery, 5, 15000, Common::Point(1,1));
    galaxy_->addStarSystem(starSystem1);
    galaxy_->addStarSystem(starSystem2);
    galaxy_->addStarSystem(starSystem3);
    galaxy_->addStarSystem(starSystem4);
    galaxy_->addStarSystem(starSystem5);

    auto ship1 = std::make_shared<Student::Planet> (std::make_shared<Student::PlanetCoreDrive>(galaxy_), galaxy_->getStarSystemByName("Sol"), event_, goods_);
    auto ship2 = std::make_shared<Student::Planet> (std::make_shared<Student::PlanetCoreDrive>(galaxy_), galaxy_->getStarSystemByName("Sirius"), event_, goods_);
    auto ship3 = std::make_shared<Student::Planet> (std::make_shared<Student::PlanetCoreDrive>(galaxy_), galaxy_->getStarSystemByName("Polar"), event_, goods_);
    auto ship4 = std::make_shared<Student::Planet> (std::make_shared<Student::PlanetCoreDrive>(galaxy_), galaxy_->getStarSystemByName("Mira"), event_, goods_);
    auto ship5 = std::make_shared<Student::Planet> (std::make_shared<Student::PlanetCoreDrive>(galaxy_), galaxy_->getStarSystemByName("Alpha Centauri"), event_, goods_);
    galaxy_->addShip(ship1);
    galaxy_->addShip(ship2);
    galaxy_->addShip(ship3);
    galaxy_->addShip(ship4);
    galaxy_->addShip(ship5);

    question_->generateQuestions();

    int rand = Common::randomMinMax(0, MAX_QUESTIONS-1);
    std::string starSystem = question_->getActiveQuestions().at(rand).second.first;
    std::string planet = question_->getActiveQuestions().at(rand).second.second;
    std::string stuff = question_->getActiveQuestions().at(rand).first;

    QVERIFY2(question_->checkQuestion(starSystem, planet, stuff) == true, "Problem with completing question");

    QVERIFY2(question_->getActiveQuestions().count() == MAX_QUESTIONS-1 && question_->getCompletedQuestions().count() == 1, "Problem with completing question");
}

void QuestionTestTest::testAllQuestions()
{

    auto starSystem1 = std::make_shared<Common::StarSystem>("Sol", Common::StarSystem::ECONOMY_TYPE::Agriculture, 1, 10000, Common::Point(13,6));
    auto starSystem2 = std::make_shared<Common::StarSystem>("Sirius", Common::StarSystem::ECONOMY_TYPE::Agriculture, 2, 10000, Common::Point(15,6));
    auto starSystem3 = std::make_shared<Common::StarSystem>("Polar", Common::StarSystem::ECONOMY_TYPE::HiTech, 3, 5000, Common::Point(20,12));
    auto starSystem4 = std::make_shared<Common::StarSystem>("Mira", Common::StarSystem::ECONOMY_TYPE::Tourism, 4, 15000, Common::Point(10,8));
    auto starSystem5 = std::make_shared<Common::StarSystem>("Alpha Centauri", Common::StarSystem::ECONOMY_TYPE::Refinery, 5, 15000, Common::Point(1,1));
    galaxy_->addStarSystem(starSystem1);
    galaxy_->addStarSystem(starSystem2);
    galaxy_->addStarSystem(starSystem3);
    galaxy_->addStarSystem(starSystem4);
    galaxy_->addStarSystem(starSystem5);

    auto ship1 = std::make_shared<Student::Planet> (std::make_shared<Student::PlanetCoreDrive>(galaxy_), galaxy_->getStarSystemByName("Sol"), event_, goods_);
    auto ship2 = std::make_shared<Student::Planet> (std::make_shared<Student::PlanetCoreDrive>(galaxy_), galaxy_->getStarSystemByName("Sirius"), event_, goods_);
    auto ship3 = std::make_shared<Student::Planet> (std::make_shared<Student::PlanetCoreDrive>(galaxy_), galaxy_->getStarSystemByName("Polar"), event_, goods_);
    auto ship4 = std::make_shared<Student::Planet> (std::make_shared<Student::PlanetCoreDrive>(galaxy_), galaxy_->getStarSystemByName("Mira"), event_, goods_);
    auto ship5 = std::make_shared<Student::Planet> (std::make_shared<Student::PlanetCoreDrive>(galaxy_), galaxy_->getStarSystemByName("Alpha Centauri"), event_, goods_);
    galaxy_->addShip(ship1);
    galaxy_->addShip(ship2);
    galaxy_->addShip(ship3);
    galaxy_->addShip(ship4);
    galaxy_->addShip(ship5);

    question_->generateQuestions();

    for(int i=0; i<MAX_QUESTIONS; ++i)
    {
        std::string starSystem = question_->getActiveQuestions().at(0).second.first;
        std::string planet = question_->getActiveQuestions().at(0).second.second;
        std::string stuff = question_->getActiveQuestions().at(0).first;

        QVERIFY2(question_->checkQuestion(starSystem, planet, stuff) == true, "Problem with completing question");
    }

    QVERIFY2(question_->getActiveQuestions().count() == 0 && question_->getCompletedQuestions().count() == MAX_QUESTIONS, "Problem with completing question");
}

QTEST_APPLESS_MAIN(QuestionTestTest)

#include "questiontesttest.moc"
