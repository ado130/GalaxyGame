#include <QString>
#include <QtTest>
#include "statistics.hh"
#include "stateexception.hh"

class StatisticsTest : public QObject
{
    Q_OBJECT

public:
    StatisticsTest();

private Q_SLOTS:
    void addingSavedShip();
    void addingLostShip();
    void addingDestroyedShip();
    void addingCompletedQuest();
    void changeMaxLoanAllowance();
    void changeAmountOfPoints();
    void changeAmountOfPoints_data();
    void changeAmountOfCredits();
    void changeAmountOfCredits_data();
};

StatisticsTest::StatisticsTest()
{
}


void StatisticsTest::addingSavedShip()
{
    Student::Statistics stats = Student::Statistics();
    stats.addSavedShip();
    QVERIFY2(stats.getSavedShips() == 1, "Number of saved ships doesn't match statistics");
    stats.addSavedShip();
    QVERIFY2(stats.getSavedShips() == 2, "Number of saved ships doesn't match statistics");
}

void StatisticsTest::addingLostShip()
{
    Student::Statistics stats = Student::Statistics();
    stats.addLostShip();
    QVERIFY2(stats.getLostShips() == 1, "Number of lost ships doesn't match statistics");
    stats.addLostShip();
    QVERIFY2(stats.getLostShips() == 2, "Number of lost ships doesn't match statistics");
}

void StatisticsTest::addingDestroyedShip()
{
    Student::Statistics stats = Student::Statistics();
    stats.addDestroyedShip();
    QVERIFY2(stats.getDestroyedShips() == 1, "Number of destroyed ships doesn't match statistics");
    stats.addDestroyedShip();
    QVERIFY2(stats.getDestroyedShips() == 2, "Number of destroyed ships doesn't match statistics");
}

void StatisticsTest::addingCompletedQuest()
{
    Student::Statistics stats = Student::Statistics();
    stats.addCompletedQuest();
    QVERIFY2(stats.getCompletedQuests() == 1, "Number of completed quests doesn't match statistics");
    stats.addCompletedQuest();
    QVERIFY2(stats.getCompletedQuests() == 2, "Number of completed quests doesn't match statistics");
}

void StatisticsTest::changeMaxLoanAllowance()
{
    Student::Statistics stats = Student::Statistics();
    QVERIFY2(stats.getMaxLoanAllowance() > 0, "Initial allowance not set / set wrongly");
    stats.setMaxLoanAllowance(111);
    QVERIFY2(stats.getMaxLoanAllowance() == 111, "Initial allowance after change not set correctly");
}

void StatisticsTest::changeAmountOfPoints()
{
    QFETCH(unsigned, add);
    QFETCH(unsigned, remove);

    Student::Statistics stats = Student::Statistics();
    QVERIFY2(stats.getPoints() == 0, "Initial points are not 0.");
    stats.addPoints(add);
    QVERIFY2(stats.getPoints() == add, "Amount of points after adding is not correct");
    if(remove > add)
    {
        QVERIFY_EXCEPTION_THROWN(stats.reducePoints(remove), Common::StateException);
        QVERIFY2(stats.getPoints() == add, "Amount of points after exception in removing isn't correct");
    }
    else
    {
        stats.reducePoints(remove);
        QVERIFY2(stats.getPoints() == add-remove, "Amount of points after removing is not correct");
    }
}

void StatisticsTest::changeAmountOfPoints_data()
{
    QTest::addColumn<unsigned>("add");
    QTest::addColumn<unsigned>("remove");

    QTest::newRow("allowed") << 20u << 5u;
    QTest::newRow("allowed, result zero")  << 10u << 10u;
    QTest::newRow("not allowed") << 20u << 50u;
}

void StatisticsTest::changeAmountOfCredits()
{
    QFETCH(int, maxLoan);
    QFETCH(unsigned, add);
    QFETCH(unsigned, remove);
    QFETCH(int, result);

    Student::Statistics stats = Student::Statistics(maxLoan);
    QVERIFY2(stats.getCreditBalance() == 0, "Initial credit is not 0.");
    stats.addCredits(add);
    QVERIFY2(stats.getCreditBalance() == add, "Amount of credits after adding is not correct");
    if(remove > add + stats.getMaxLoanAllowance())
    {
        QVERIFY_EXCEPTION_THROWN(stats.reduceCredits(remove), Common::StateException);
        QVERIFY2(stats.getCreditBalance() == add, "Amount of points after exception in removing isn't correct");
    }
    else
    {
        stats.reduceCredits(remove);

        QVERIFY2(stats.getCreditBalance() == result, "Amount of points after removing is not correct");
    }
}

void StatisticsTest::changeAmountOfCredits_data()
{
    QTest::addColumn<int>("maxLoan");
    QTest::addColumn<unsigned>("add");
    QTest::addColumn<unsigned>("remove");
    QTest::addColumn<int>("result");

    QTest::newRow("allowed") << 30 << 20u << 5u << 15;
    QTest::newRow("allowed, result zero")  << 30 << 10u << 10u << 0;
    QTest::newRow("loan fully drained") << 30 << 20u << 50u << -30;
    QTest::newRow("not possible to reduce") << 30 << 20u << 51u << -31;
}


QTEST_APPLESS_MAIN(StatisticsTest)

#include "statisticstest.moc"
