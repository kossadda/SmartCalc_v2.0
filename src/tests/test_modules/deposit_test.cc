/**
 * @file deposit_test.cc
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "tests/main_test.h"

#define MONTHS s21::DepositModel::TermType::MONTHS
#define DAYS s21::DepositModel::TermType::DAYS
using Op = s21::DepositModel::Operation;
using OpType = s21::DepositModel::OperationType;
using Data = s21::DepositModel::Data;
using Freq = s21::DepositModel::Frequency;
using Type = s21::DepositModel::Type;
using Date = s21::Date;

void testDeposit(const Data &data, std::vector<long double> expected) {
  s21::DepositModel deposit;

  deposit.addData(data);
  deposit.calculatePayments();
  std::vector<long double> result{0.0L, std::stold(deposit.table().back()[4])};

  for (auto i : deposit.table()) {
    result[0] += std::stold(i[1]);
  }

  for (std::size_t i{}; i < expected.size(); ++i) {
    long double res = result.at(i);
    long double exp = expected.at(i);
    EXPECT_NEAR(res, exp, 1e-3)
        << "\nRes : " << res << "\nTrue: " << exp << '\n';
  }
}

TEST(deposit, byDay_1) {
  Data data{10000, 12,          MONTHS,    15,
            16,    Type::FIRST, Freq::DAY, Date{1, 1, 2020}};
  testDeposit(data, {1500.61, 10000});
}

TEST(deposit, byDay_2) {
  Data data{10000, 12,           MONTHS,    15,
            16,    Type::SECOND, Freq::DAY, Date{1, 1, 2020}};
  testDeposit(data, {1617.99, 11617.99});
}

TEST(deposit, byDay_3) {
  Data data{147634.72, 17,          MONTHS,    13.218,
            16,        Type::FIRST, Freq::DAY, Date{7, 5, 2017}};
  testDeposit(data, {27692.28, 147634.72});
}

TEST(deposit, byDay_4) {
  Data data{147634.72, 17,           MONTHS,    13.218,
            16,        Type::SECOND, Freq::DAY, Date{7, 5, 2017}};
  testDeposit(data, {30456.34, 178091.06});
}

TEST(deposit, byDay_5) {
  Data data{895625.37, 25,          MONTHS,    12.345,
            16,        Type::FIRST, Freq::DAY, Date{8, 2, 1988}};
  testDeposit(data, {229644.87, 895625.37});
}

TEST(deposit, byDay_6) {
  Data data{895625.37, 25,           MONTHS,    12.345,
            16,        Type::SECOND, Freq::DAY, Date{8, 2, 1988}};
  testDeposit(data, {261720.87, 1157346.24});
}

TEST(deposit, byDay_7) {
  Data data{7777777.77, 77,          MONTHS,    7.777,
            16,         Type::FIRST, Freq::DAY, Date{7, 7, 1977}};
  testDeposit(data, {3882818.82, 7777777.77});
}

TEST(deposit, byDay_8) {
  Data data{7777777.77, 77,           MONTHS,    7.777,
            16,         Type::SECOND, Freq::DAY, Date{7, 7, 1977}};
  testDeposit(data, {5034923.39, 12812701.16});
}

TEST(deposit, byDay_9) {
  Data data{326741742.86, 7037,        DAYS,      16.123,
            16,           Type::FIRST, Freq::DAY, Date{1, 1, 2024}};
  testDeposit(data, {1014931284.35, 326741742.86});
}

TEST(deposit, byDay_10) {
  Data data{326741742.86, 7037,         DAYS,      16.123,
            16,           Type::SECOND, Freq::DAY, Date{1, 1, 2024}};
  testDeposit(data, {6966499579.12, 7293241321.98});
}

TEST(deposit, byWeek_1) {
  Data data{10000, 12,          MONTHS,     15,
            16,    Type::FIRST, Freq::WEEK, Date{1, 1, 2020}};
  testDeposit(data, {1500.09, 10000});
}

TEST(deposit, byWeek_2) {
  Data data{10000, 12,           MONTHS,     15,
            16,    Type::SECOND, Freq::WEEK, Date{1, 1, 2020}};
  testDeposit(data, {1615.86, 11615.86});
}

TEST(deposit, byWeek_3) {
  Data data{147634.72, 17,          MONTHS,     13.218,
            16,        Type::FIRST, Freq::WEEK, Date{7, 5, 2017}};
  testDeposit(data, {27694.5, 147634.72});
}

TEST(deposit, byWeek_4) {
  Data data{147634.72, 17,           MONTHS,     13.218,
            16,        Type::SECOND, Freq::WEEK, Date{7, 5, 2017}};
  testDeposit(data, {30419.95, 178054.67});
}

TEST(deposit, byWeek_5) {
  Data data{895625.37, 25,          MONTHS,     12.345,
            16,        Type::FIRST, Freq::WEEK, Date{8, 2, 1988}};
  testDeposit(data, {229643.64, 895625.37});
}

TEST(deposit, byWeek_6) {
  Data data{895625.37, 25,           MONTHS,     12.345,
            16,        Type::SECOND, Freq::WEEK, Date{8, 2, 1988}};
  testDeposit(data, {261421.69, 1157047.06});
}

TEST(deposit, byWeek_7) {
  Data data{7777777.77, 77,          MONTHS,     7.777,
            16,         Type::FIRST, Freq::WEEK, Date{7, 7, 1977}};
  testDeposit(data, {3882819.34, 7777777.77});
}

TEST(deposit, byWeek_8) {
  Data data{7777777.77, 77,           MONTHS,     7.777,
            16,         Type::SECOND, Freq::WEEK, Date{7, 7, 1977}};
  testDeposit(data, {5030844.09, 12808621.86});
}

TEST(deposit, byWeek_9) {
  Data data{326741742.86, 18037,       DAYS,       16.123,
            16,           Type::FIRST, Freq::WEEK, Date{1, 1, 2024}};
  testDeposit(data, {2601410292.21, 326741742.86});
}

TEST(deposit, byWeek_10) {
  Data data{326741742.86, 18037,        DAYS,       16.123,
            16,           Type::SECOND, Freq::WEEK, Date{1, 1, 2024}};
  testDeposit(data, {925615593479.03, 925942335221.89});
}

TEST(deposit, byMonth_1) {
  Data data{10000, 12,          MONTHS,      15,
            16,    Type::FIRST, Freq::MONTH, Date{1, 1, 2020}};
  testDeposit(data, {1500.01, 10000});
}

TEST(deposit, byMonth_2) {
  Data data{10000, 12,           MONTHS,      15,
            16,    Type::SECOND, Freq::MONTH, Date{1, 1, 2020}};
  testDeposit(data, {1607.55, 11607.55});
}

TEST(deposit, byMonth_3) {
  Data data{147634.72, 17,          MONTHS,      13.218,
            16,        Type::FIRST, Freq::MONTH, Date{7, 5, 2017}};
  testDeposit(data, {27694.31, 147634.72});
}

TEST(deposit, byMonth_4) {
  Data data{147634.72, 17,           MONTHS,      13.218,
            16,        Type::SECOND, Freq::MONTH, Date{7, 5, 2017}};
  testDeposit(data, {30279.24, 177913.96});
}

TEST(deposit, byMonth_5) {
  Data data{895625.37, 25,          MONTHS,      12.345,
            16,        Type::FIRST, Freq::MONTH, Date{8, 2, 1988}};
  testDeposit(data, {229643.87, 895625.37});
}

TEST(deposit, byMonth_6) {
  Data data{895625.37, 25,           MONTHS,      12.345,
            16,        Type::SECOND, Freq::MONTH, Date{8, 2, 1988}};
  testDeposit(data, {260259.36, 1155884.73});
}

TEST(deposit, byMonth_7) {
  Data data{7777777.77, 77,          MONTHS,      7.777,
            16,         Type::FIRST, Freq::MONTH, Date{7, 7, 1977}};
  testDeposit(data, {3882818.11, 7777777.77});
}

TEST(deposit, byMonth_8) {
  Data data{7777777.77, 77,           MONTHS,      7.777,
            16,         Type::SECOND, Freq::MONTH, Date{7, 7, 1977}};
  testDeposit(data, {5014960.02, 12792737.79});
}

TEST(deposit, byMonth_9) {
  Data data{326741742.86, 7037,        DAYS,        16.123,
            16,           Type::FIRST, Freq::MONTH, Date{1, 1, 2024}};
  testDeposit(data, {1014931288.92, 326741742.86});
}

TEST(deposit, byMonth_10) {
  Data data{326741742.86, 7037,         DAYS,        16.123,
            16,           Type::SECOND, Freq::MONTH, Date{1, 1, 2024}};
  testDeposit(data, {6822138779.35, 7148880522.21});
}

TEST(deposit, byQuarter_1) {
  Data data{10000, 12,          MONTHS,        15,
            16,    Type::FIRST, Freq::QUARTER, Date{1, 1, 2020}};
  testDeposit(data, {1500.01, 10000});
}

TEST(deposit, byQuarter_2) {
  Data data{10000, 12,           MONTHS,        15,
            16,    Type::SECOND, Freq::QUARTER, Date{1, 1, 2020}};
  testDeposit(data, {1586.52, 11586.52});
}

TEST(deposit, byQuarter_3) {
  Data data{147634.72, 17,          MONTHS,        13.218,
            16,        Type::FIRST, Freq::QUARTER, Date{7, 5, 2017}};
  testDeposit(data, {27694.36, 147634.72});
}

TEST(deposit, byQuarter_4) {
  Data data{147634.72, 17,           MONTHS,        13.218,
            16,        Type::SECOND, Freq::QUARTER, Date{7, 5, 2017}};
  testDeposit(data, {29942.8, 177577.52});
}

TEST(deposit, byQuarter_5) {
  Data data{895625.37, 25,          MONTHS,        12.345,
            16,        Type::FIRST, Freq::QUARTER, Date{8, 2, 1988}};
  testDeposit(data, {229643.87, 895625.37});
}

TEST(deposit, byQuarter_6) {
  Data data{895625.37, 25,           MONTHS,        12.345,
            16,        Type::SECOND, Freq::QUARTER, Date{8, 2, 1988}};
  testDeposit(data, {257405.01, 1153030.38});
}

TEST(deposit, byQuarter_7) {
  Data data{7777777.77, 77,          MONTHS,        7.777,
            16,         Type::FIRST, Freq::QUARTER, Date{7, 7, 1977}};
  testDeposit(data, {3882818.14, 7777777.77});
}

TEST(deposit, byQuarter_8) {
  Data data{7777777.77, 77,           MONTHS,        7.777,
            16,         Type::SECOND, Freq::QUARTER, Date{7, 7, 1977}};
  testDeposit(data, {4974861.53, 12752639.3});
}

TEST(deposit, byQuarter_9) {
  Data data{326741742.86, 7037,        DAYS,          16.123,
            16,           Type::FIRST, Freq::QUARTER, Date{1, 1, 2024}};
  testDeposit(data, {1014931289.5, 326741742.86});
}

TEST(deposit, byQuarter_10) {
  Data data{326741742.86, 7037,         DAYS,          16.123,
            16,           Type::SECOND, Freq::QUARTER, Date{1, 1, 2024}};
  testDeposit(data, {6540254793.1, 6866996535.96});
}

TEST(deposit, byHalfyear_1) {
  Data data{10000, 12,          MONTHS,         15,
            16,    Type::FIRST, Freq::HALFYEAR, Date{1, 1, 2020}};
  testDeposit(data, {1500.01, 10000});
}

TEST(deposit, byHalfyear_2) {
  Data data{10000, 12,           MONTHS,         15,
            16,    Type::SECOND, Freq::HALFYEAR, Date{1, 1, 2020}};
  testDeposit(data, {1556.26, 11556.26});
}

TEST(deposit, byHalfyear_3) {
  Data data{147634.72, 17,          MONTHS,         13.218,
            16,        Type::FIRST, Freq::HALFYEAR, Date{7, 5, 2017}};
  testDeposit(data, {27694.34, 147634.72});
}

TEST(deposit, byHalfyear_4) {
  Data data{147634.72, 17,           MONTHS,         13.218,
            16,        Type::SECOND, Freq::HALFYEAR, Date{7, 5, 2017}};
  testDeposit(data, {29456.11, 177090.83});
}

TEST(deposit, byHalfyear_5) {
  Data data{895625.37, 25,          MONTHS,         12.345,
            16,        Type::FIRST, Freq::HALFYEAR, Date{8, 2, 1988}};
  testDeposit(data, {229643.87, 895625.37});
}

TEST(deposit, byHalfyear_6) {
  Data data{895625.37, 25,           MONTHS,         12.345,
            16,        Type::SECOND, Freq::HALFYEAR, Date{8, 2, 1988}};
  testDeposit(data, {253275.69, 1148901.06});
}

TEST(deposit, byHalfyear_7) {
  Data data{7777777.77, 77,          MONTHS,         7.777,
            16,         Type::FIRST, Freq::HALFYEAR, Date{7, 7, 1977}};
  testDeposit(data, {3882818.19, 7777777.77});
}

TEST(deposit, byHalfyear_8) {
  Data data{7777777.77, 77,           MONTHS,         7.777,
            16,         Type::SECOND, Freq::HALFYEAR, Date{7, 7, 1977}};
  testDeposit(data, {4916176.13, 12693953.9});
}

TEST(deposit, byHalfyear_9) {
  Data data{326741742.86, 7037,        DAYS,           16.123,
            16,           Type::FIRST, Freq::HALFYEAR, Date{1, 1, 2024}};
  testDeposit(data, {1014931289.31, 326741742.86});
}

TEST(deposit, byHalfyear_10) {
  Data data{326741742.86, 7037,         DAYS,           16.123,
            16,           Type::SECOND, Freq::HALFYEAR, Date{1, 1, 2024}};
  testDeposit(data, {6158421560.45, 6485163303.31});
}

TEST(deposit, byYear_1) {
  Data data{10000, 12,          MONTHS,     15,
            16,    Type::FIRST, Freq::YEAR, Date{1, 1, 2020}};
  testDeposit(data, {1500.01, 10000});
}

TEST(deposit, byYear_2) {
  Data data{10000, 12,           MONTHS,     15,
            16,    Type::SECOND, Freq::YEAR, Date{1, 1, 2020}};
  testDeposit(data, {1500.01, 11500.01});
}

TEST(deposit, byYear_3) {
  Data data{147634.72, 17,          MONTHS,     13.218,
            16,        Type::FIRST, Freq::YEAR, Date{7, 5, 2017}};
  testDeposit(data, {27694.35, 147634.72});
}

TEST(deposit, byYear_4) {
  Data data{147634.72, 17,           MONTHS,     13.218,
            16,        Type::SECOND, Freq::YEAR, Date{7, 5, 2017}};
  testDeposit(data, {28775.58, 176410.3});
}

TEST(deposit, byYear_5) {
  Data data{895625.37, 25,          MONTHS,     12.345,
            16,        Type::FIRST, Freq::YEAR, Date{8, 2, 1988}};
  testDeposit(data, {229643.87, 895625.37});
}

TEST(deposit, byYear_6) {
  Data data{895625.37, 25,           MONTHS,     12.345,
            16,        Type::SECOND, Freq::YEAR, Date{8, 2, 1988}};
  testDeposit(data, {245520.84, 1141146.21});
}

TEST(deposit, byYear_7) {
  Data data{7777777.77, 77,          MONTHS,     7.777,
            16,         Type::FIRST, Freq::YEAR, Date{7, 7, 1977}};
  testDeposit(data, {3882818.18, 7777777.77});
}

TEST(deposit, byYear_8) {
  Data data{7777777.77, 77,           MONTHS,     7.777,
            16,         Type::SECOND, Freq::YEAR, Date{7, 7, 1977}};
  testDeposit(data, {4809852.33, 12587630.1});
}

TEST(deposit, byYear_9) {
  Data data{326741742.86, 7037,        DAYS,       16.123,
            16,           Type::FIRST, Freq::YEAR, Date{1, 1, 2024}};
  testDeposit(data, {1014931289.4, 326741742.86});
}

TEST(deposit, byYear_10) {
  Data data{326741742.86, 7037,         DAYS,       16.123,
            16,           Type::SECOND, Freq::YEAR, Date{1, 1, 2024}};
  testDeposit(data, {5505997235.41, 5832738978.27});
}

TEST(deposit, byEndTerm_1) {
  Data data{10000, 12,          MONTHS,        15,
            16,    Type::FIRST, Freq::ENDTERM, Date{1, 1, 2020}};
  testDeposit(data, {1500.01, 10000});
}

TEST(deposit, byEndTerm_2) {
  Data data{147634.72, 17,          MONTHS,        13.218,
            16,        Type::FIRST, Freq::ENDTERM, Date{7, 5, 2017}};
  testDeposit(data, {27694.35, 147634.72});
}

TEST(deposit, byEndTerm_3) {
  Data data{895625.37, 25,          MONTHS,        12.345,
            16,        Type::FIRST, Freq::ENDTERM, Date{8, 2, 1988}};
  testDeposit(data, {229643.88, 895625.37});
}

TEST(deposit, byEndTerm_4) {
  Data data{7777777.77, 77,          MONTHS,        7.777,
            16,         Type::FIRST, Freq::ENDTERM, Date{7, 7, 1977}};
  testDeposit(data, {3882818.17, 7777777.77});
}

TEST(deposit, byEndTerm_5) {
  Data data{326741742.86, 7037,        DAYS,          16.123,
            16,           Type::FIRST, Freq::ENDTERM, Date{1, 1, 2024}};
  testDeposit(data, {1014931289.38, 326741742.86});
}
