#include <QString>
#include <QtTest>
#include "statistics.hh"
class StatisticsTest : public QObject
{
    Q_OBJECT

public:
    StatisticsTest();

private Q_SLOTS:
    void testCase1();
};

StatisticsTest::StatisticsTest()
{
}


void StatisticsTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(StatisticsTest)

#include "statisticstest.moc"
