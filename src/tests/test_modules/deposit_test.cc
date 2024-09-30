/**
 * @file deposit_test.cc
 * @author kossadda (https://github.com/kossadda)
 * @brief Test module for DepositModel class.
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

TEST(deposit, refillByDay_1) {
  Op op_1{25000, OpType::REFILL, Date{5, 1, 2024}};
  std::vector<Op> ops{op_1};
  Data data{150000, 12,           MONTHS,    15,
            16,     Type::SECOND, Freq::DAY, Date{23, 11, 2023},
            &ops};
  testDeposit(data, {27815.05, 202815.05});
}

TEST(deposit, refillByDay_2) {
  Op op_1{25000, OpType::REFILL, Date{5, 1, 2024}};
  std::vector<Op> ops{op_1};
  Data data{150000, 12,          MONTHS,    15,
            16,     Type::FIRST, Freq::DAY, Date{23, 11, 2023},
            &ops};
  testDeposit(data, {25815.28, 175000});
}

TEST(deposit, refillByDay_3) {
  Op op_1{1235567, OpType::REFILL, Date{6, 6, 2013}};
  std::vector<Op> ops{op_1};
  Data data{12578367.22,       52,  MONTHS, 7.852, 16, Type::SECOND, Freq::DAY,
            Date{15, 2, 2011}, &ops};
  testDeposit(data, {5303950.87, 19117885.09});
}

TEST(deposit, refillByDay_4) {
  Op op_1{1235567, OpType::REFILL, Date{6, 6, 2013}};
  std::vector<Op> ops{op_1};
  Data data{12578367.22,       52,  MONTHS, 7.852, 16, Type::FIRST, Freq::DAY,
            Date{15, 2, 2011}, &ops};
  testDeposit(data, {4471749.36, 13813934.22});
}

TEST(deposit, refillByDay_5) {
  Op op_1{25715345, OpType::REFILL, Date{7, 8, 2024}};
  Op op_2{16152222, OpType::REFILL, Date{9, 9, 2024}};
  std::vector<Op> ops{op_1, op_2};
  Data data{102635556.23, 66,        MONTHS,           5.562, 16,
            Type::SECOND, Freq::DAY, Date{7, 2, 2021}, &ops};
  testDeposit(data, {41526809.44, 186029932.67});
}

TEST(deposit, refillByDay_6) {
  Op op_1{25715345, OpType::REFILL, Date{7, 8, 2024}};
  Op op_2{16152222, OpType::REFILL, Date{9, 9, 2024}};
  std::vector<Op> ops{op_1, op_2};
  Data data{102635556.23, 66,        MONTHS,           5.562, 16,
            Type::FIRST,  Freq::DAY, Date{7, 2, 2021}, &ops};
  testDeposit(data, {35947582.6, 144503123.23});
}

TEST(deposit, refillByDay_7) {
  Op op_1{22222222, OpType::REFILL, Date{2, 2, 2015}};
  Op op_2{11111111, OpType::REFILL, Date{2, 2, 2018}};
  std::vector<Op> ops{op_1, op_2};
  Data data{8737647.43,        121, MONTHS, 8.476, 16, Type::SECOND, Freq::DAY,
            Date{31, 1, 2015}, &ops};
  testDeposit(data, {50861846.52, 92932826.95});
}

TEST(deposit, refillByDay_8) {
  Op op_1{22222222, OpType::REFILL, Date{2, 2, 2015}};
  Op op_2{11111111, OpType::REFILL, Date{2, 2, 2018}};
  std::vector<Op> ops{op_1, op_2};
  Data data{8737647.43,        121, MONTHS, 8.476, 16, Type::FIRST, Freq::DAY,
            Date{31, 1, 2015}, &ops};
  testDeposit(data, {33092108.47, 42070980.43});
}

TEST(deposit, refillByDay_9) {
  Op op_1{1111111, OpType::REFILL, Date{3, 5, 2022}};
  Op op_2{2222222, OpType::REFILL, Date{29, 2, 2024}};
  Op op_3{3333333, OpType::REFILL, Date{3, 7, 2025}};
  Op op_4{4444444, OpType::REFILL, Date{10, 7, 2025}};
  std::vector<Op> ops{op_1, op_2, op_3, op_4};
  Data data{62563535.23,        76,  MONTHS, 7.851, 16, Type::SECOND, Freq::DAY,
            Date{22, 11, 2020}, &ops};
  testDeposit(data, {42493683.37, 116168328.6});
}

TEST(deposit, refillByDay_10) {
  Op op_1{1111111, OpType::REFILL, Date{3, 5, 2022}};
  Op op_2{2222222, OpType::REFILL, Date{29, 2, 2024}};
  Op op_3{3333333, OpType::REFILL, Date{3, 7, 2025}};
  Op op_4{4444444, OpType::REFILL, Date{10, 7, 2025}};
  std::vector<Op> ops{op_1, op_2, op_3, op_4};
  Data data{62563535.23,        76,  MONTHS, 7.851, 16, Type::FIRST, Freq::DAY,
            Date{22, 11, 2020}, &ops};
  testDeposit(data, {33086504.37, 73674645.23});
}

TEST(deposit, refillByWeek_1) {
  Op op_1{25000, OpType::REFILL, Date{5, 1, 2024}};
  std::vector<Op> ops{op_1};
  Data data{150000, 12,           MONTHS,     15,
            16,     Type::SECOND, Freq::WEEK, Date{23, 11, 2023},
            &ops};
  testDeposit(data, {27778.37, 202778.37});
}

TEST(deposit, refillByWeek_2) {
  Op op_1{25000, OpType::REFILL, Date{5, 1, 2024}};
  std::vector<Op> ops{op_1};
  Data data{150000, 12,          MONTHS,     15,
            16,     Type::FIRST, Freq::WEEK, Date{23, 11, 2023},
            &ops};
  testDeposit(data, {25815.87, 175000});
}

TEST(deposit, refillByWeek_3) {
  Op op_1{1235567, OpType::REFILL, Date{6, 6, 2013}};
  std::vector<Op> ops{op_1};
  Data data{12578367.22,       52,  MONTHS, 7.852, 16, Type::SECOND, Freq::WEEK,
            Date{15, 2, 2011}, &ops};
  testDeposit(data, {5299936.53, 19113870.75});
}

TEST(deposit, refillByWeek_4) {
  Op op_1{1235567, OpType::REFILL, Date{6, 6, 2013}};
  std::vector<Op> ops{op_1};
  Data data{12578367.22,       52,  MONTHS, 7.852, 16, Type::FIRST, Freq::WEEK,
            Date{15, 2, 2011}, &ops};
  testDeposit(data, {4471747.25, 13813934.22});
}

TEST(deposit, refillByWeek_5) {
  Op op_1{25715345, OpType::REFILL, Date{7, 8, 2024}};
  Op op_2{16152222, OpType::REFILL, Date{9, 9, 2024}};
  std::vector<Op> ops{op_1, op_2};
  Data data{102635556.23, 66,         MONTHS,           5.562, 16,
            Type::SECOND, Freq::WEEK, Date{7, 2, 2021}, &ops};
  testDeposit(data, {41505063.46, 186008186.69});
}

TEST(deposit, refillByWeek_6) {
  Op op_1{25715345, OpType::REFILL, Date{7, 8, 2024}};
  Op op_2{16152222, OpType::REFILL, Date{9, 9, 2024}};
  std::vector<Op> ops{op_1, op_2};
  Data data{102635556.23, 66,         MONTHS,           5.562, 16,
            Type::FIRST,  Freq::WEEK, Date{7, 2, 2021}, &ops};
  testDeposit(data, {35947583.74, 144503123.23});
}

TEST(deposit, refillByWeek_7) {
  Op op_1{22222222, OpType::REFILL, Date{2, 2, 2015}};
  Op op_2{11111111, OpType::REFILL, Date{2, 2, 2018}};
  std::vector<Op> ops{op_1, op_2};
  Data data{8737647.43,        121, MONTHS, 8.476, 16, Type::SECOND, Freq::WEEK,
            Date{31, 1, 2015}, &ops};
  testDeposit(data, {50810309.72, 92881290.15});
}

TEST(deposit, refillByWeek_8) {
  Op op_1{22222222, OpType::REFILL, Date{2, 2, 2015}};
  Op op_2{11111111, OpType::REFILL, Date{2, 2, 2018}};
  std::vector<Op> ops{op_1, op_2};
  Data data{8737647.43,        121, MONTHS, 8.476, 16, Type::FIRST, Freq::WEEK,
            Date{31, 1, 2015}, &ops};
  testDeposit(data, {33092100.07, 42070980.43});
}

TEST(deposit, refillByWeek_9) {
  Op op_1{1111111, OpType::REFILL, Date{3, 5, 2022}};
  Op op_2{2222222, OpType::REFILL, Date{29, 2, 2024}};
  Op op_3{3333333, OpType::REFILL, Date{3, 7, 2025}};
  Op op_4{4444444, OpType::REFILL, Date{10, 7, 2025}};
  std::vector<Op> ops{op_1, op_2, op_3, op_4};
  Data data{62563535.23, 76,           MONTHS,     7.851,
            16,          Type::SECOND, Freq::WEEK, Date{22, 11, 2020},
            &ops};
  testDeposit(data, {42459188.99, 116133834.22});
}

TEST(deposit, refillByWeek_10) {
  Op op_1{1111111, OpType::REFILL, Date{3, 5, 2022}};
  Op op_2{2222222, OpType::REFILL, Date{29, 2, 2024}};
  Op op_3{3333333, OpType::REFILL, Date{3, 7, 2025}};
  Op op_4{4444444, OpType::REFILL, Date{10, 7, 2025}};
  std::vector<Op> ops{op_1, op_2, op_3, op_4};
  Data data{62563535.23,        76,  MONTHS, 7.851, 16, Type::FIRST, Freq::WEEK,
            Date{22, 11, 2020}, &ops};
  testDeposit(data, {33086507.75, 73674645.23});
}

TEST(deposit, refillByMonth_1) {
  Op op_1{25000, OpType::REFILL, Date{5, 1, 2024}};
  std::vector<Op> ops{op_1};
  Data data{150000, 12,           MONTHS,      15,
            16,     Type::SECOND, Freq::MONTH, Date{23, 11, 2023},
            &ops};
  testDeposit(data, {27636.03, 202636.03});
}

TEST(deposit, refillByMonth_2) {
  Op op_1{25000, OpType::REFILL, Date{5, 1, 2024}};
  std::vector<Op> ops{op_1};
  Data data{150000, 12,          MONTHS,      15,
            16,     Type::FIRST, Freq::MONTH, Date{23, 11, 2023},
            &ops};
  testDeposit(data, {25815.83, 175000});
}

TEST(deposit, refillByMonth_3) {
  Op op_1{1235567, OpType::REFILL, Date{6, 6, 2013}};
  std::vector<Op> ops{op_1};
  Data data{12578367.22, 52,           MONTHS,      7.852,
            16,          Type::SECOND, Freq::MONTH, Date{15, 2, 2011},
            &ops};
  testDeposit(data, {5284328.43, 19098262.65});
}

TEST(deposit, refillByMonth_4) {
  Op op_1{1235567, OpType::REFILL, Date{6, 6, 2013}};
  std::vector<Op> ops{op_1};
  Data data{12578367.22,       52,  MONTHS, 7.852, 16, Type::FIRST, Freq::MONTH,
            Date{15, 2, 2011}, &ops};
  testDeposit(data, {4471747.2, 13813934.22});
}

TEST(deposit, refillByMonth_5) {
  Op op_1{25715345, OpType::REFILL, Date{7, 8, 2024}};
  Op op_2{16152222, OpType::REFILL, Date{9, 9, 2024}};
  std::vector<Op> ops{op_1, op_2};
  Data data{102635556.23, 66,          MONTHS,           5.562, 16,
            Type::SECOND, Freq::MONTH, Date{7, 2, 2021}, &ops};
  testDeposit(data, {41420296.14, 185923419.37});
}

TEST(deposit, refillByMonth_6) {
  Op op_1{25715345, OpType::REFILL, Date{7, 8, 2024}};
  Op op_2{16152222, OpType::REFILL, Date{9, 9, 2024}};
  std::vector<Op> ops{op_1, op_2};
  Data data{102635556.23, 66,          MONTHS,           5.562, 16,
            Type::FIRST,  Freq::MONTH, Date{7, 2, 2021}, &ops};
  testDeposit(data, {35947584.18, 144503123.23});
}

TEST(deposit, refillByMonth_7) {
  Op op_1{22222222, OpType::REFILL, Date{2, 2, 2015}};
  Op op_2{11111111, OpType::REFILL, Date{2, 2, 2018}};
  std::vector<Op> ops{op_1, op_2};
  Data data{8737647.43, 121,          MONTHS,      8.476,
            16,         Type::SECOND, Freq::MONTH, Date{31, 1, 2015},
            &ops};
  testDeposit(data, {50610081.91, 92681062.34});
}

TEST(deposit, refillByMonth_8) {
  Op op_1{22222222, OpType::REFILL, Date{2, 2, 2015}};
  Op op_2{11111111, OpType::REFILL, Date{2, 2, 2018}};
  std::vector<Op> ops{op_1, op_2};
  Data data{8737647.43,        121, MONTHS, 8.476, 16, Type::FIRST, Freq::MONTH,
            Date{31, 1, 2015}, &ops};
  testDeposit(data, {33092099.52, 42070980.43});
}

TEST(deposit, refillByMonth_9) {
  Op op_1{1111111, OpType::REFILL, Date{3, 5, 2022}};
  Op op_2{2222222, OpType::REFILL, Date{29, 2, 2024}};
  Op op_3{3333333, OpType::REFILL, Date{3, 7, 2025}};
  Op op_4{4444444, OpType::REFILL, Date{10, 7, 2025}};
  std::vector<Op> ops{op_1, op_2, op_3, op_4};
  Data data{62563535.23, 76,           MONTHS,      7.851,
            16,          Type::SECOND, Freq::MONTH, Date{22, 11, 2020},
            &ops};
  testDeposit(data, {42325111.44, 115999756.67});
}

TEST(deposit, refillByMonth_10) {
  Op op_1{1111111, OpType::REFILL, Date{3, 5, 2022}};
  Op op_2{2222222, OpType::REFILL, Date{29, 2, 2024}};
  Op op_3{3333333, OpType::REFILL, Date{3, 7, 2025}};
  Op op_4{4444444, OpType::REFILL, Date{10, 7, 2025}};
  std::vector<Op> ops{op_1, op_2, op_3, op_4};
  Data data{62563535.23, 76,          MONTHS,      7.851,
            16,          Type::FIRST, Freq::MONTH, Date{22, 11, 2020},
            &ops};
  testDeposit(data, {33086508.05, 73674645.23});
}

TEST(deposit, refillByQuarter_1) {
  Op op_1{25000, OpType::REFILL, Date{5, 1, 2024}};
  std::vector<Op> ops{op_1};
  Data data{150000, 12,           MONTHS,        15,
            16,     Type::SECOND, Freq::QUARTER, Date{23, 11, 2023},
            &ops};
  testDeposit(data, {27279.01, 202279.01});
}

TEST(deposit, refillByQuarter_2) {
  Op op_1{25000, OpType::REFILL, Date{5, 1, 2024}};
  std::vector<Op> ops{op_1};
  Data data{150000, 12,          MONTHS,        15,
            16,     Type::FIRST, Freq::QUARTER, Date{23, 11, 2023},
            &ops};
  testDeposit(data, {25815.83, 175000});
}

TEST(deposit, refillByQuarter_3) {
  Op op_1{1235567, OpType::REFILL, Date{6, 6, 2013}};
  std::vector<Op> ops{op_1};
  Data data{12578367.22, 52,           MONTHS,        7.852,
            16,          Type::SECOND, Freq::QUARTER, Date{15, 2, 2011},
            &ops};
  testDeposit(data, {5245229.35, 19059163.57});
}

TEST(deposit, refillByQuarter_4) {
  Op op_1{1235567, OpType::REFILL, Date{6, 6, 2013}};
  std::vector<Op> ops{op_1};
  Data data{12578367.22, 52,          MONTHS,        7.852,
            16,          Type::FIRST, Freq::QUARTER, Date{15, 2, 2011},
            &ops};
  testDeposit(data, {4471747.16, 13813934.22});
}

TEST(deposit, refillByQuarter_5) {
  Op op_1{25715345, OpType::REFILL, Date{7, 8, 2024}};
  Op op_2{16152222, OpType::REFILL, Date{9, 9, 2024}};
  std::vector<Op> ops{op_1, op_2};
  Data data{102635556.23, 66,           MONTHS,        5.562,
            16,           Type::SECOND, Freq::QUARTER, Date{7, 2, 2021},
            &ops};
  testDeposit(data, {41202790.15, 185705913.38});
}

TEST(deposit, refillByQuarter_6) {
  Op op_1{25715345, OpType::REFILL, Date{7, 8, 2024}};
  Op op_2{16152222, OpType::REFILL, Date{9, 9, 2024}};
  std::vector<Op> ops{op_1, op_2};
  Data data{102635556.23, 66,          MONTHS,        5.562,
            16,           Type::FIRST, Freq::QUARTER, Date{7, 2, 2021},
            &ops};
  testDeposit(data, {35947584.13, 144503123.23});
}

TEST(deposit, refillByQuarter_7) {
  Op op_1{22222222, OpType::REFILL, Date{2, 2, 2015}};
  Op op_2{11111111, OpType::REFILL, Date{2, 2, 2018}};
  std::vector<Op> ops{op_1, op_2};
  Data data{8737647.43, 121,          MONTHS,        8.476,
            16,         Type::SECOND, Freq::QUARTER, Date{31, 1, 2015},
            &ops};
  testDeposit(data, {50102707.75, 92173688.18});
}

TEST(deposit, refillByQuarter_8) {
  Op op_1{22222222, OpType::REFILL, Date{2, 2, 2015}};
  Op op_2{11111111, OpType::REFILL, Date{2, 2, 2018}};
  std::vector<Op> ops{op_1, op_2};
  Data data{8737647.43, 121,         MONTHS,        8.476,
            16,         Type::FIRST, Freq::QUARTER, Date{31, 1, 2015},
            &ops};
  testDeposit(data, {33092099.68, 42070980.43});
}

TEST(deposit, refillByQuarter_9) {
  Op op_1{1111111, OpType::REFILL, Date{3, 5, 2022}};
  Op op_2{2222222, OpType::REFILL, Date{29, 2, 2024}};
  Op op_3{3333333, OpType::REFILL, Date{3, 7, 2025}};
  Op op_4{4444444, OpType::REFILL, Date{10, 7, 2025}};
  std::vector<Op> ops{op_1, op_2, op_3, op_4};
  Data data{62563535.23, 76,           MONTHS,        7.851,
            16,          Type::SECOND, Freq::QUARTER, Date{22, 11, 2020},
            &ops};
  testDeposit(data, {41986483.1, 115661128.33});
}

TEST(deposit, refillByQuarter_10) {
  Op op_1{1111111, OpType::REFILL, Date{3, 5, 2022}};
  Op op_2{2222222, OpType::REFILL, Date{29, 2, 2024}};
  Op op_3{3333333, OpType::REFILL, Date{3, 7, 2025}};
  Op op_4{4444444, OpType::REFILL, Date{10, 7, 2025}};
  std::vector<Op> ops{op_1, op_2, op_3, op_4};
  Data data{62563535.23, 76,          MONTHS,        7.851,
            16,          Type::FIRST, Freq::QUARTER, Date{22, 11, 2020},
            &ops};
  testDeposit(data, {33086507.93, 73674645.23});
}

TEST(deposit, refillByHalfYear_1) {
  Op op_1{25000, OpType::REFILL, Date{5, 1, 2024}};
  std::vector<Op> ops{op_1};
  Data data{150000, 12,           MONTHS,         15,
            16,     Type::SECOND, Freq::HALFYEAR, Date{23, 11, 2023},
            &ops};
  testDeposit(data, {26767.44, 201767.44});
}

TEST(deposit, refillByHalfYear_2) {
  Op op_1{25000, OpType::REFILL, Date{5, 1, 2024}};
  std::vector<Op> ops{op_1};
  Data data{150000, 12,          MONTHS,         15,
            16,     Type::FIRST, Freq::HALFYEAR, Date{23, 11, 2023},
            &ops};
  testDeposit(data, {25815.83, 175000});
}

TEST(deposit, refillByHalfYear_3) {
  Op op_1{1235567, OpType::REFILL, Date{6, 6, 2013}};
  std::vector<Op> ops{op_1};
  Data data{12578367.22, 52,           MONTHS,         7.852,
            16,          Type::SECOND, Freq::HALFYEAR, Date{15, 2, 2011},
            &ops};
  testDeposit(data, {5189094.39, 19003028.61});
}

TEST(deposit, refillByHalfYear_4) {
  Op op_1{1235567, OpType::REFILL, Date{6, 6, 2013}};
  std::vector<Op> ops{op_1};
  Data data{12578367.22, 52,          MONTHS,         7.852,
            16,          Type::FIRST, Freq::HALFYEAR, Date{15, 2, 2011},
            &ops};
  testDeposit(data, {4471747.18, 13813934.22});
}

TEST(deposit, refillByHalfYear_5) {
  Op op_1{25715345, OpType::REFILL, Date{7, 8, 2024}};
  Op op_2{16152222, OpType::REFILL, Date{9, 9, 2024}};
  std::vector<Op> ops{op_1, op_2};
  Data data{102635556.23, 66,           MONTHS,         5.562,
            16,           Type::SECOND, Freq::HALFYEAR, Date{7, 2, 2021},
            &ops};
  testDeposit(data, {40882001.62, 185385124.85});
}

TEST(deposit, refillByHalfYear_6) {
  Op op_1{25715345, OpType::REFILL, Date{7, 8, 2024}};
  Op op_2{16152222, OpType::REFILL, Date{9, 9, 2024}};
  std::vector<Op> ops{op_1, op_2};
  Data data{102635556.23, 66,          MONTHS,         5.562,
            16,           Type::FIRST, Freq::HALFYEAR, Date{7, 2, 2021},
            &ops};
  testDeposit(data, {35947584.14, 144503123.23});
}

TEST(deposit, refillByHalfYear_7) {
  Op op_1{22222222, OpType::REFILL, Date{2, 2, 2015}};
  Op op_2{11111111, OpType::REFILL, Date{2, 2, 2018}};
  std::vector<Op> ops{op_1, op_2};
  Data data{8737647.43, 121,          MONTHS,         8.476,
            16,         Type::SECOND, Freq::HALFYEAR, Date{31, 1, 2015},
            &ops};
  testDeposit(data, {49364771.59, 91435752.02});
}

TEST(deposit, refillByHalfYear_8) {
  Op op_1{22222222, OpType::REFILL, Date{2, 2, 2015}};
  Op op_2{11111111, OpType::REFILL, Date{2, 2, 2018}};
  std::vector<Op> ops{op_1, op_2};
  Data data{8737647.43, 121,         MONTHS,         8.476,
            16,         Type::FIRST, Freq::HALFYEAR, Date{31, 1, 2015},
            &ops};
  testDeposit(data, {33092099.7, 42070980.43});
}

TEST(deposit, refillByHalfYear_9) {
  Op op_1{1111111, OpType::REFILL, Date{3, 5, 2022}};
  Op op_2{2222222, OpType::REFILL, Date{29, 2, 2024}};
  Op op_3{3333333, OpType::REFILL, Date{3, 7, 2025}};
  Op op_4{4444444, OpType::REFILL, Date{10, 7, 2025}};
  std::vector<Op> ops{op_1, op_2, op_3, op_4};
  Data data{62563535.23, 76,           MONTHS,         7.851,
            16,          Type::SECOND, Freq::HALFYEAR, Date{22, 11, 2020},
            &ops};
  testDeposit(data, {41500138.75, 115174783.98});
}

TEST(deposit, refillByHalfYear_10) {
  Op op_1{1111111, OpType::REFILL, Date{3, 5, 2022}};
  Op op_2{2222222, OpType::REFILL, Date{29, 2, 2024}};
  Op op_3{3333333, OpType::REFILL, Date{3, 7, 2025}};
  Op op_4{4444444, OpType::REFILL, Date{10, 7, 2025}};
  std::vector<Op> ops{op_1, op_2, op_3, op_4};
  Data data{62563535.23, 76,          MONTHS,         7.851,
            16,          Type::FIRST, Freq::HALFYEAR, Date{22, 11, 2020},
            &ops};
  testDeposit(data, {33086507.98, 73674645.23});
}

TEST(deposit, refillByYear_1) {
  Op op_1{25000, OpType::REFILL, Date{5, 1, 2024}};
  std::vector<Op> ops{op_1};
  Data data{150000, 12,           MONTHS,     15,
            16,     Type::SECOND, Freq::YEAR, Date{23, 11, 2023},
            &ops};
  testDeposit(data, {25815.83, 200815.83});
}

TEST(deposit, refillByYear_2) {
  Op op_1{25000, OpType::REFILL, Date{5, 1, 2024}};
  std::vector<Op> ops{op_1};
  Data data{150000, 12,          MONTHS,     15,
            16,     Type::FIRST, Freq::YEAR, Date{23, 11, 2023},
            &ops};
  testDeposit(data, {25815.83, 175000});
}

TEST(deposit, refillByYear_3) {
  Op op_1{1235567, OpType::REFILL, Date{6, 6, 2013}};
  std::vector<Op> ops{op_1};
  Data data{12578367.22,       52,  MONTHS, 7.852, 16, Type::SECOND, Freq::YEAR,
            Date{15, 2, 2011}, &ops};
  testDeposit(data, {5086208.02, 18900142.24});
}

TEST(deposit, refillByYear_4) {
  Op op_1{1235567, OpType::REFILL, Date{6, 6, 2013}};
  std::vector<Op> ops{op_1};
  Data data{12578367.22,       52,  MONTHS, 7.852, 16, Type::FIRST, Freq::YEAR,
            Date{15, 2, 2011}, &ops};
  testDeposit(data, {4471747.17, 13813934.22});
}

TEST(deposit, refillByYear_5) {
  Op op_1{25715345, OpType::REFILL, Date{7, 8, 2024}};
  Op op_2{16152222, OpType::REFILL, Date{9, 9, 2024}};
  std::vector<Op> ops{op_1, op_2};
  Data data{102635556.23, 66,         MONTHS,           5.562, 16,
            Type::SECOND, Freq::YEAR, Date{7, 2, 2021}, &ops};
  testDeposit(data, {40340725.2, 184843848.43});
}

TEST(deposit, refillByYear_6) {
  Op op_1{25715345, OpType::REFILL, Date{7, 8, 2024}};
  Op op_2{16152222, OpType::REFILL, Date{9, 9, 2024}};
  std::vector<Op> ops{op_1, op_2};
  Data data{102635556.23, 66,         MONTHS,           5.562, 16,
            Type::FIRST,  Freq::YEAR, Date{7, 2, 2021}, &ops};
  testDeposit(data, {35947584.14, 144503123.23});
}

TEST(deposit, refillByYear_7) {
  Op op_1{22222222, OpType::REFILL, Date{2, 2, 2015}};
  Op op_2{11111111, OpType::REFILL, Date{2, 2, 2018}};
  std::vector<Op> ops{op_1, op_2};
  Data data{8737647.43,        121, MONTHS, 8.476, 16, Type::SECOND, Freq::YEAR,
            Date{31, 1, 2015}, &ops};
  testDeposit(data, {47963663.67, 90034644.1});
}

TEST(deposit, refillByYear_8) {
  Op op_1{22222222, OpType::REFILL, Date{2, 2, 2015}};
  Op op_2{11111111, OpType::REFILL, Date{2, 2, 2018}};
  std::vector<Op> ops{op_1, op_2};
  Data data{8737647.43,        121, MONTHS, 8.476, 16, Type::FIRST, Freq::YEAR,
            Date{31, 1, 2015}, &ops};
  testDeposit(data, {33092099.71, 42070980.43});
}

TEST(deposit, refillByYear_9) {
  Op op_1{1111111, OpType::REFILL, Date{3, 5, 2022}};
  Op op_2{2222222, OpType::REFILL, Date{29, 2, 2024}};
  Op op_3{3333333, OpType::REFILL, Date{3, 7, 2025}};
  Op op_4{4444444, OpType::REFILL, Date{10, 7, 2025}};
  std::vector<Op> ops{op_1, op_2, op_3, op_4};
  Data data{62563535.23, 76,           MONTHS,     7.851,
            16,          Type::SECOND, Freq::YEAR, Date{22, 11, 2020},
            &ops};
  testDeposit(data, {40599318.75, 114273963.98});
}

TEST(deposit, refillByYear_10) {
  Op op_1{1111111, OpType::REFILL, Date{3, 5, 2022}};
  Op op_2{2222222, OpType::REFILL, Date{29, 2, 2024}};
  Op op_3{3333333, OpType::REFILL, Date{3, 7, 2025}};
  Op op_4{4444444, OpType::REFILL, Date{10, 7, 2025}};
  std::vector<Op> ops{op_1, op_2, op_3, op_4};
  Data data{62563535.23,        76,  MONTHS, 7.851, 16, Type::FIRST, Freq::YEAR,
            Date{22, 11, 2020}, &ops};
  testDeposit(data, {33086507.98, 73674645.23});
}

TEST(deposit, refillByEndTerm_1) {
  Op op_1{25000, OpType::REFILL, Date{5, 1, 2024}};
  std::vector<Op> ops{op_1};
  Data data{150000, 12,          MONTHS,        15,
            16,     Type::FIRST, Freq::ENDTERM, Date{23, 11, 2023},
            &ops};
  testDeposit(data, {25815.83, 175000});
}

TEST(deposit, refillByEndTerm_2) {
  Op op_1{1235567, OpType::REFILL, Date{6, 6, 2013}};
  std::vector<Op> ops{op_1};
  Data data{12578367.22, 52,          MONTHS,        7.852,
            16,          Type::FIRST, Freq::ENDTERM, Date{15, 2, 2011},
            &ops};
  testDeposit(data, {4471747.18, 13813934.22});
}

TEST(deposit, refillByEndTerm_3) {
  Op op_1{25715345, OpType::REFILL, Date{7, 8, 2024}};
  Op op_2{16152222, OpType::REFILL, Date{9, 9, 2024}};
  std::vector<Op> ops{op_1, op_2};
  Data data{102635556.23, 66,          MONTHS,        5.562,
            16,           Type::FIRST, Freq::ENDTERM, Date{7, 2, 2021},
            &ops};
  testDeposit(data, {35947584.13, 144503123.23});
}

TEST(deposit, refillByEndTerm_4) {
  Op op_1{22222222, OpType::REFILL, Date{2, 2, 2015}};
  Op op_2{11111111, OpType::REFILL, Date{2, 2, 2018}};
  std::vector<Op> ops{op_1, op_2};
  Data data{8737647.43, 121,         MONTHS,        8.476,
            16,         Type::FIRST, Freq::ENDTERM, Date{31, 1, 2015},
            &ops};
  testDeposit(data, {33092099.71, 42070980.43});
}

TEST(deposit, refillByEndTerm_5) {
  Op op_1{1111111, OpType::REFILL, Date{3, 5, 2022}};
  Op op_2{2222222, OpType::REFILL, Date{29, 2, 2024}};
  Op op_3{3333333, OpType::REFILL, Date{3, 7, 2025}};
  Op op_4{4444444, OpType::REFILL, Date{10, 7, 2025}};
  std::vector<Op> ops{op_1, op_2, op_3, op_4};
  Data data{62563535.23, 76,          MONTHS,        7.851,
            16,          Type::FIRST, Freq::ENDTERM, Date{22, 11, 2020},
            &ops};
  testDeposit(data, {33086507.98, 73674645.23});
}

TEST(deposit, withdrawalByDay_1) {
  Op op_1{25000, OpType::WITHDRAWAL, Date{5, 1, 2024}};
  std::vector<Op> ops{op_1};
  Data data{150000, 12,           MONTHS,    15,
            16,     Type::SECOND, Freq::DAY, Date{23, 11, 2023},
            &ops};
  testDeposit(data, {20739.51, 145739.51});
}

TEST(deposit, withdrawalByDay_2) {
  Op op_1{25000, OpType::WITHDRAWAL, Date{5, 1, 2024}};
  std::vector<Op> ops{op_1};
  Data data{150000, 12,          MONTHS,    15,
            16,     Type::FIRST, Freq::DAY, Date{23, 11, 2023},
            &ops};
  testDeposit(data, {19197.01, 125000});
}

TEST(deposit, withdrawalByDay_3) {
  Op op_1{1235567, OpType::WITHDRAWAL, Date{6, 6, 2013}};
  std::vector<Op> ops{op_1};
  Data data{12578367.22,       52,  MONTHS, 7.852, 16, Type::SECOND, Freq::DAY,
            Date{15, 2, 2011}, &ops};
  testDeposit(data, {4878199.41, 16220999.63});
}

TEST(deposit, withdrawalByDay_4) {
  Op op_1{1235567, OpType::WITHDRAWAL, Date{6, 6, 2013}};
  std::vector<Op> ops{op_1};
  Data data{12578367.22,       52,  MONTHS, 7.852, 16, Type::FIRST, Freq::DAY,
            Date{15, 2, 2011}, &ops};
  testDeposit(data, {4078896.96, 11342800.22});
}

TEST(deposit, withdrawalByDay_5) {
  Op op_1{25715345, OpType::WITHDRAWAL, Date{7, 8, 2024}};
  Op op_2{16152222, OpType::WITHDRAWAL, Date{9, 9, 2024}};
  std::vector<Op> ops{op_1, op_2};
  Data data{102635556.23, 66,        MONTHS,           5.562, 16,
            Type::SECOND, Freq::DAY, Date{7, 2, 2021}, &ops};
  testDeposit(data, {31861340.39, 92629329.62});
}

TEST(deposit, withdrawalByDay_6) {
  Op op_1{25715345, OpType::WITHDRAWAL, Date{7, 8, 2024}};
  Op op_2{16152222, OpType::WITHDRAWAL, Date{9, 9, 2024}};
  std::vector<Op> ops{op_1, op_2};
  Data data{102635556.23, 66,        MONTHS,           5.562, 16,
            Type::FIRST,  Freq::DAY, Date{7, 2, 2021}, &ops};
  testDeposit(data, {26799978.62, 60767989.23});
}

TEST(deposit, withdrawalByDay_7) {
  Op op_1{22222222, OpType::WITHDRAWAL, Date{2, 2, 2015}};
  Op op_2{11111111, OpType::WITHDRAWAL, Date{2, 2, 2018}};
  std::vector<Op> ops{op_1, op_2};
  Data data{8737647.43,        121, MONTHS, 8.476, 16, Type::SECOND, Freq::DAY,
            Date{31, 1, 2015}, &ops};
  testDeposit(data, {2667113.45, 293649.88});
}

TEST(deposit, withdrawalByDay_8) {
  Op op_1{22222222, OpType::WITHDRAWAL, Date{2, 2, 2015}};
  Op op_2{11111111, OpType::WITHDRAWAL, Date{2, 2, 2018}};
  std::vector<Op> ops{op_1, op_2};
  Data data{8737647.43,        121, MONTHS, 8.476, 16, Type::FIRST, Freq::DAY,
            Date{31, 1, 2015}, &ops};
  testDeposit(data, {7462850.13, 8737647.43});
}

TEST(deposit, withdrawalByDay_9) {
  Op op_1{1111111, OpType::WITHDRAWAL, Date{3, 5, 2022}};
  Op op_2{2222222, OpType::WITHDRAWAL, Date{29, 2, 2024}};
  Op op_3{3333333, OpType::WITHDRAWAL, Date{3, 7, 2025}};
  Op op_4{4444444, OpType::WITHDRAWAL, Date{10, 7, 2025}};
  std::vector<Op> ops{op_1, op_2, op_3, op_4};
  Data data{62563535.23,        76,  MONTHS, 7.851, 16, Type::SECOND, Freq::DAY,
            Date{22, 11, 2020}, &ops};
  testDeposit(data, {38018815.09, 89471240.32});
}

TEST(deposit, withdrawalByDay_10) {
  Op op_1{1111111, OpType::WITHDRAWAL, Date{3, 5, 2022}};
  Op op_2{2222222, OpType::WITHDRAWAL, Date{29, 2, 2024}};
  Op op_3{3333333, OpType::WITHDRAWAL, Date{3, 7, 2025}};
  Op op_4{4444444, OpType::WITHDRAWAL, Date{10, 7, 2025}};
  std::vector<Op> ops{op_1, op_2, op_3, op_4};
  Data data{62563535.23,        76,  MONTHS, 7.851, 16, Type::FIRST, Freq::DAY,
            Date{22, 11, 2020}, &ops};
  testDeposit(data, {29082699.38, 51452425.23});
}

TEST(deposit, withdrawalByWeek_1) {
  Op op_1{25000, OpType::WITHDRAWAL, Date{5, 1, 2024}};
  std::vector<Op> ops{op_1};
  Data data{150000, 12,           MONTHS,     15,
            16,     Type::SECOND, Freq::WEEK, Date{23, 11, 2023},
            &ops};
  testDeposit(data, {20712.22, 145712.22});
}

TEST(deposit, withdrawalByWeek_2) {
  Op op_1{25000, OpType::WITHDRAWAL, Date{5, 1, 2024}};
  std::vector<Op> ops{op_1};
  Data data{150000, 12,          MONTHS,     15,
            16,     Type::FIRST, Freq::WEEK, Date{23, 11, 2023},
            &ops};
  testDeposit(data, {19197.14, 125000});
}

TEST(deposit, withdrawalByWeek_3) {
  Op op_1{1235567, OpType::WITHDRAWAL, Date{6, 6, 2013}};
  std::vector<Op> ops{op_1};
  Data data{12578367.22,       52,  MONTHS, 7.852, 16, Type::SECOND, Freq::WEEK,
            Date{15, 2, 2011}, &ops};
  testDeposit(data, {4874480.79, 16217281.01});
}

TEST(deposit, withdrawalByWeek_4) {
  Op op_1{1235567, OpType::WITHDRAWAL, Date{6, 6, 2013}};
  std::vector<Op> ops{op_1};
  Data data{12578367.22,       52,  MONTHS, 7.852, 16, Type::FIRST, Freq::WEEK,
            Date{15, 2, 2011}, &ops};
  testDeposit(data, {4078895.91, 11342800.22});
}

TEST(deposit, withdrawalByWeek_5) {
  Op op_1{25715345, OpType::WITHDRAWAL, Date{7, 8, 2024}};
  Op op_2{16152222, OpType::WITHDRAWAL, Date{9, 9, 2024}};
  std::vector<Op> ops{op_1, op_2};
  Data data{102635556.23, 66,         MONTHS,           5.562, 16,
            Type::SECOND, Freq::WEEK, Date{7, 2, 2021}, &ops};
  testDeposit(data, {31844231.67, 92612220.9});
}

TEST(deposit, withdrawalByWeek_6) {
  Op op_1{25715345, OpType::WITHDRAWAL, Date{7, 8, 2024}};
  Op op_2{16152222, OpType::WITHDRAWAL, Date{9, 9, 2024}};
  std::vector<Op> ops{op_1, op_2};
  Data data{102635556.23, 66,         MONTHS,           5.562, 16,
            Type::FIRST,  Freq::WEEK, Date{7, 2, 2021}, &ops};
  testDeposit(data, {26799981.96, 60767989.23});
}

TEST(deposit, withdrawalByWeek_7) {
  Op op_1{22222222, OpType::WITHDRAWAL, Date{2, 2, 2015}};
  Op op_2{11111111, OpType::WITHDRAWAL, Date{2, 2, 2018}};
  std::vector<Op> ops{op_1, op_2};
  Data data{8737647.43,        121, MONTHS, 8.476, 16, Type::SECOND, Freq::WEEK,
            Date{31, 1, 2015}, &ops};
  testDeposit(data, {2663355.22, 289891.65});
}

TEST(deposit, withdrawalByWeek_8) {
  Op op_1{22222222, OpType::WITHDRAWAL, Date{2, 2, 2015}};
  Op op_2{11111111, OpType::WITHDRAWAL, Date{2, 2, 2018}};
  std::vector<Op> ops{op_1, op_2};
  Data data{8737647.43,        121, MONTHS, 8.476, 16, Type::FIRST, Freq::WEEK,
            Date{31, 1, 2015}, &ops};
  testDeposit(data, {7462845.41, 8737647.43});
}

TEST(deposit, withdrawalByWeek_9) {
  Op op_1{1111111, OpType::WITHDRAWAL, Date{3, 5, 2022}};
  Op op_2{2222222, OpType::WITHDRAWAL, Date{29, 2, 2024}};
  Op op_3{3333333, OpType::WITHDRAWAL, Date{3, 7, 2025}};
  Op op_4{4444444, OpType::WITHDRAWAL, Date{10, 7, 2025}};
  std::vector<Op> ops{op_1, op_2, op_3, op_4};
  Data data{62563535.23, 76,           MONTHS,     7.851,
            16,          Type::SECOND, Freq::WEEK, Date{22, 11, 2020},
            &ops};
  testDeposit(data, {37987524.98, 89439950.21});
}

TEST(deposit, withdrawalByWeek_10) {
  Op op_1{1111111, OpType::WITHDRAWAL, Date{3, 5, 2022}};
  Op op_2{2222222, OpType::WITHDRAWAL, Date{29, 2, 2024}};
  Op op_3{3333333, OpType::WITHDRAWAL, Date{3, 7, 2025}};
  Op op_4{4444444, OpType::WITHDRAWAL, Date{10, 7, 2025}};
  std::vector<Op> ops{op_1, op_2, op_3, op_4};
  Data data{62563535.23,        76,  MONTHS, 7.851, 16, Type::FIRST, Freq::WEEK,
            Date{22, 11, 2020}, &ops};
  testDeposit(data, {29082701.1, 51452425.23});
}

// ============================================================================

TEST(deposit, withdrawalByMonth_1) {
  Op op_1{25000, OpType::WITHDRAWAL, Date{5, 1, 2024}};
  std::vector<Op> ops{op_1};
  Data data{150000, 12,           MONTHS,      15,
            16,     Type::SECOND, Freq::MONTH, Date{23, 11, 2023},
            &ops};
  testDeposit(data, {20604.87, 145604.87});
}

TEST(deposit, withdrawalByMonth_2) {
  Op op_1{25000, OpType::WITHDRAWAL, Date{5, 1, 2024}};
  std::vector<Op> ops{op_1};
  Data data{150000, 12,          MONTHS,      15,
            16,     Type::FIRST, Freq::MONTH, Date{23, 11, 2023},
            &ops};
  testDeposit(data, {19196.97, 125000});
}

TEST(deposit, withdrawalByMonth_3) {
  Op op_1{1235567, OpType::WITHDRAWAL, Date{6, 6, 2013}};
  std::vector<Op> ops{op_1};
  Data data{12578367.22, 52,           MONTHS,      7.852,
            16,          Type::SECOND, Freq::MONTH, Date{15, 2, 2011},
            &ops};
  testDeposit(data, {4860015.6, 16202815.82});
}

TEST(deposit, withdrawalByMonth_4) {
  Op op_1{1235567, OpType::WITHDRAWAL, Date{6, 6, 2013}};
  std::vector<Op> ops{op_1};
  Data data{12578367.22,       52,  MONTHS, 7.852, 16, Type::FIRST, Freq::MONTH,
            Date{15, 2, 2011}, &ops};
  testDeposit(data, {4078895.78, 11342800.22});
}

TEST(deposit, withdrawalByMonth_5) {
  Op op_1{25715345, OpType::WITHDRAWAL, Date{7, 8, 2024}};
  Op op_2{16152222, OpType::WITHDRAWAL, Date{9, 9, 2024}};
  std::vector<Op> ops{op_1, op_2};
  Data data{102635556.23, 66,          MONTHS,           5.562, 16,
            Type::SECOND, Freq::MONTH, Date{7, 2, 2021}, &ops};
  testDeposit(data, {31777599.25, 92545588.48});
}

TEST(deposit, withdrawalByMonth_6) {
  Op op_1{25715345, OpType::WITHDRAWAL, Date{7, 8, 2024}};
  Op op_2{16152222, OpType::WITHDRAWAL, Date{9, 9, 2024}};
  std::vector<Op> ops{op_1, op_2};
  Data data{102635556.23, 66,          MONTHS,           5.562, 16,
            Type::FIRST,  Freq::MONTH, Date{7, 2, 2021}, &ops};
  testDeposit(data, {26799981.96, 60767989.23});
}

TEST(deposit, withdrawalByMonth_7) {
  Op op_1{22222222, OpType::WITHDRAWAL, Date{2, 2, 2015}};
  Op op_2{11111111, OpType::WITHDRAWAL, Date{2, 2, 2018}};
  std::vector<Op> ops{op_1, op_2};
  Data data{8737647.43, 121,          MONTHS,      8.476,
            16,         Type::SECOND, Freq::MONTH, Date{31, 1, 2015},
            &ops};
  testDeposit(data, {2648712.42, 275248.85});
}

TEST(deposit, withdrawalByMonth_8) {
  Op op_1{22222222, OpType::WITHDRAWAL, Date{2, 2, 2015}};
  Op op_2{11111111, OpType::WITHDRAWAL, Date{2, 2, 2018}};
  std::vector<Op> ops{op_1, op_2};
  Data data{8737647.43,        121, MONTHS, 8.476, 16, Type::FIRST, Freq::MONTH,
            Date{31, 1, 2015}, &ops};
  testDeposit(data, {7462843.42, 8737647.43});
}

TEST(deposit, withdrawalByMonth_9) {
  Op op_1{1111111, OpType::WITHDRAWAL, Date{3, 5, 2022}};
  Op op_2{2222222, OpType::WITHDRAWAL, Date{29, 2, 2024}};
  Op op_3{3333333, OpType::WITHDRAWAL, Date{3, 7, 2025}};
  Op op_4{4444444, OpType::WITHDRAWAL, Date{10, 7, 2025}};
  std::vector<Op> ops{op_1, op_2, op_3, op_4};
  Data data{62563535.23, 76,           MONTHS,      7.851,
            16,          Type::SECOND, Freq::MONTH, Date{22, 11, 2020},
            &ops};
  testDeposit(data, {37865831.27, 89318256.5});
}

TEST(deposit, withdrawalByMonth_10) {
  Op op_1{1111111, OpType::WITHDRAWAL, Date{3, 5, 2022}};
  Op op_2{2222222, OpType::WITHDRAWAL, Date{29, 2, 2024}};
  Op op_3{3333333, OpType::WITHDRAWAL, Date{3, 7, 2025}};
  Op op_4{4444444, OpType::WITHDRAWAL, Date{10, 7, 2025}};
  std::vector<Op> ops{op_1, op_2, op_3, op_4};
  Data data{62563535.23, 76,          MONTHS,      7.851,
            16,          Type::FIRST, Freq::MONTH, Date{22, 11, 2020},
            &ops};
  testDeposit(data, {29082700.21, 51452425.23});
}

// ============================================================================

TEST(deposit, withdrawalByQuarter_1) {
  Op op_1{25000, OpType::WITHDRAWAL, Date{5, 1, 2024}};
  std::vector<Op> ops{op_1};
  Data data{150000, 12,           MONTHS,        15,
            16,     Type::SECOND, Freq::QUARTER, Date{23, 11, 2023},
            &ops};
  testDeposit(data, {20330.35, 145330.35});
}

TEST(deposit, withdrawalByQuarter_2) {
  Op op_1{25000, OpType::WITHDRAWAL, Date{5, 1, 2024}};
  std::vector<Op> ops{op_1};
  Data data{150000, 12,          MONTHS,        15,
            16,     Type::FIRST, Freq::QUARTER, Date{23, 11, 2023},
            &ops};
  testDeposit(data, {19196.97, 125000});
}

TEST(deposit, withdrawalByQuarter_3) {
  Op op_1{1235567, OpType::WITHDRAWAL, Date{6, 6, 2013}};
  std::vector<Op> ops{op_1};
  Data data{12578367.22, 52,           MONTHS,        7.852,
            16,          Type::SECOND, Freq::QUARTER, Date{15, 2, 2011},
            &ops};
  testDeposit(data, {4823663.1, 16166463.32});
}

TEST(deposit, withdrawalByQuarter_4) {
  Op op_1{1235567, OpType::WITHDRAWAL, Date{6, 6, 2013}};
  std::vector<Op> ops{op_1};
  Data data{12578367.22, 52,          MONTHS,        7.852,
            16,          Type::FIRST, Freq::QUARTER, Date{15, 2, 2011},
            &ops};
  testDeposit(data, {4078895.87, 11342800.22});
}

TEST(deposit, withdrawalByQuarter_5) {
  Op op_1{25715345, OpType::WITHDRAWAL, Date{7, 8, 2024}};
  Op op_2{16152222, OpType::WITHDRAWAL, Date{9, 9, 2024}};
  std::vector<Op> ops{op_1, op_2};
  Data data{102635556.23, 66,           MONTHS,        5.562,
            16,           Type::SECOND, Freq::QUARTER, Date{7, 2, 2021},
            &ops};
  testDeposit(data, {31605984.47, 92373973.7});
}

TEST(deposit, withdrawalByQuarter_6) {
  Op op_1{25715345, OpType::WITHDRAWAL, Date{7, 8, 2024}};
  Op op_2{16152222, OpType::WITHDRAWAL, Date{9, 9, 2024}};
  std::vector<Op> ops{op_1, op_2};
  Data data{102635556.23, 66,          MONTHS,        5.562,
            16,           Type::FIRST, Freq::QUARTER, Date{7, 2, 2021},
            &ops};
  testDeposit(data, {26799981.96, 60767989.23});
}

TEST(deposit, withdrawalByQuarter_7) {
  Op op_1{22222222, OpType::WITHDRAWAL, Date{2, 2, 2015}};
  Op op_2{11111111, OpType::WITHDRAWAL, Date{2, 2, 2018}};
  std::vector<Op> ops{op_1, op_2};
  Data data{8737647.43, 121,          MONTHS,        8.476,
            16,         Type::SECOND, Freq::QUARTER, Date{31, 1, 2015},
            &ops};
  testDeposit(data, {2611594.37, 238130.8});
}

TEST(deposit, withdrawalByQuarter_8) {
  Op op_1{22222222, OpType::WITHDRAWAL, Date{2, 2, 2015}};
  Op op_2{11111111, OpType::WITHDRAWAL, Date{2, 2, 2018}};
  std::vector<Op> ops{op_1, op_2};
  Data data{8737647.43, 121,         MONTHS,        8.476,
            16,         Type::FIRST, Freq::QUARTER, Date{31, 1, 2015},
            &ops};
  testDeposit(data, {7462843.39, 8737647.43});
}

TEST(deposit, withdrawalByQuarter_9) {
  Op op_1{1111111, OpType::WITHDRAWAL, Date{3, 5, 2022}};
  Op op_2{2222222, OpType::WITHDRAWAL, Date{29, 2, 2024}};
  Op op_3{3333333, OpType::WITHDRAWAL, Date{3, 7, 2025}};
  Op op_4{4444444, OpType::WITHDRAWAL, Date{10, 7, 2025}};
  std::vector<Op> ops{op_1, op_2, op_3, op_4};
  Data data{62563535.23, 76,           MONTHS,        7.851,
            16,          Type::SECOND, Freq::QUARTER, Date{22, 11, 2020},
            &ops};
  testDeposit(data, {37557368.32, 89009793.55});
}

TEST(deposit, withdrawalByQuarter_10) {
  Op op_1{1111111, OpType::WITHDRAWAL, Date{3, 5, 2022}};
  Op op_2{2222222, OpType::WITHDRAWAL, Date{29, 2, 2024}};
  Op op_3{3333333, OpType::WITHDRAWAL, Date{3, 7, 2025}};
  Op op_4{4444444, OpType::WITHDRAWAL, Date{10, 7, 2025}};
  std::vector<Op> ops{op_1, op_2, op_3, op_4};
  Data data{62563535.23, 76,          MONTHS,        7.851,
            16,          Type::FIRST, Freq::QUARTER, Date{22, 11, 2020},
            &ops};
  testDeposit(data, {29082700.16, 51452425.23});
}

TEST(deposit, withdrawalByHalfYear_1) {
  Op op_1{25000, OpType::WITHDRAWAL, Date{5, 1, 2024}};
  std::vector<Op> ops{op_1};
  Data data{150000, 12,           MONTHS,         15,
            16,     Type::SECOND, Freq::HALFYEAR, Date{23, 11, 2023},
            &ops};
  testDeposit(data, {19933.78, 144933.78});
}

TEST(deposit, withdrawalByHalfYear_2) {
  Op op_1{25000, OpType::WITHDRAWAL, Date{5, 1, 2024}};
  std::vector<Op> ops{op_1};
  Data data{150000, 12,          MONTHS,         15,
            16,     Type::FIRST, Freq::HALFYEAR, Date{23, 11, 2023},
            &ops};
  testDeposit(data, {19196.97, 125000});
}

TEST(deposit, withdrawalByHalfYear_3) {
  Op op_1{1235567, OpType::WITHDRAWAL, Date{6, 6, 2013}};
  std::vector<Op> ops{op_1};
  Data data{12578367.22, 52,           MONTHS,         7.852,
            16,          Type::SECOND, Freq::HALFYEAR, Date{15, 2, 2011},
            &ops};
  testDeposit(data, {4771120.2, 16113920.42});
}

TEST(deposit, withdrawalByHalfYear_4) {
  Op op_1{1235567, OpType::WITHDRAWAL, Date{6, 6, 2013}};
  std::vector<Op> ops{op_1};
  Data data{12578367.22, 52,          MONTHS,         7.852,
            16,          Type::FIRST, Freq::HALFYEAR, Date{15, 2, 2011},
            &ops};
  testDeposit(data, {4078895.92, 11342800.22});
}

TEST(deposit, withdrawalByHalfYear_5) {
  Op op_1{25715345, OpType::WITHDRAWAL, Date{7, 8, 2024}};
  Op op_2{16152222, OpType::WITHDRAWAL, Date{9, 9, 2024}};
  std::vector<Op> ops{op_1, op_2};
  Data data{102635556.23, 66,           MONTHS,         5.562,
            16,           Type::SECOND, Freq::HALFYEAR, Date{7, 2, 2021},
            &ops};
  testDeposit(data, {31352883.68, 92120872.91});
}

TEST(deposit, withdrawalByHalfYear_6) {
  Op op_1{25715345, OpType::WITHDRAWAL, Date{7, 8, 2024}};
  Op op_2{16152222, OpType::WITHDRAWAL, Date{9, 9, 2024}};
  std::vector<Op> ops{op_1, op_2};
  Data data{102635556.23, 66,          MONTHS,         5.562,
            16,           Type::FIRST, Freq::HALFYEAR, Date{7, 2, 2021},
            &ops};
  testDeposit(data, {26799981.97, 60767989.23});
}

TEST(deposit, withdrawalByHalfYear_7) {
  Op op_1{22222222, OpType::WITHDRAWAL, Date{2, 2, 2015}};
  Op op_2{11111111, OpType::WITHDRAWAL, Date{2, 2, 2018}};
  std::vector<Op> ops{op_1, op_2};
  Data data{8737647.43, 121,          MONTHS,         8.476,
            16,         Type::SECOND, Freq::HALFYEAR, Date{31, 1, 2015},
            &ops};
  testDeposit(data, {2557792.72, 184329.15});
}

TEST(deposit, withdrawalByHalfYear_8) {
  Op op_1{22222222, OpType::WITHDRAWAL, Date{2, 2, 2015}};
  Op op_2{11111111, OpType::WITHDRAWAL, Date{2, 2, 2018}};
  std::vector<Op> ops{op_1, op_2};
  Data data{8737647.43, 121,         MONTHS,         8.476,
            16,         Type::FIRST, Freq::HALFYEAR, Date{31, 1, 2015},
            &ops};
  testDeposit(data, {7462843.28, 8737647.43});
}

TEST(deposit, withdrawalByHalfYear_9) {
  Op op_1{1111111, OpType::WITHDRAWAL, Date{3, 5, 2022}};
  Op op_2{2222222, OpType::WITHDRAWAL, Date{29, 2, 2024}};
  Op op_3{3333333, OpType::WITHDRAWAL, Date{3, 7, 2025}};
  Op op_4{4444444, OpType::WITHDRAWAL, Date{10, 7, 2025}};
  std::vector<Op> ops{op_1, op_2, op_3, op_4};
  Data data{62563535.23, 76,           MONTHS,         7.851,
            16,          Type::SECOND, Freq::HALFYEAR, Date{22, 11, 2020},
            &ops};
  testDeposit(data, {37111947.66, 88564372.89});
}

TEST(deposit, withdrawalByHalfYear_10) {
  Op op_1{1111111, OpType::WITHDRAWAL, Date{3, 5, 2022}};
  Op op_2{2222222, OpType::WITHDRAWAL, Date{29, 2, 2024}};
  Op op_3{3333333, OpType::WITHDRAWAL, Date{3, 7, 2025}};
  Op op_4{4444444, OpType::WITHDRAWAL, Date{10, 7, 2025}};
  std::vector<Op> ops{op_1, op_2, op_3, op_4};
  Data data{62563535.23, 76,          MONTHS,         7.851,
            16,          Type::FIRST, Freq::HALFYEAR, Date{22, 11, 2020},
            &ops};
  testDeposit(data, {29082700.15, 51452425.23});
}

//  ============================================================================

TEST(deposit, withdrawalByYear_1) {
  Op op_1{25000, OpType::WITHDRAWAL, Date{5, 1, 2024}};
  std::vector<Op> ops{op_1};
  Data data{150000, 12,           MONTHS,     15,
            16,     Type::SECOND, Freq::YEAR, Date{23, 11, 2023},
            &ops};
  testDeposit(data, {19196.97, 144196.97});
}

TEST(deposit, withdrawalByYear_2) {
  Op op_1{25000, OpType::WITHDRAWAL, Date{5, 1, 2024}};
  std::vector<Op> ops{op_1};
  Data data{150000, 12,          MONTHS,     15,
            16,     Type::FIRST, Freq::YEAR, Date{23, 11, 2023},
            &ops};
  testDeposit(data, {19196.97, 125000});
}

TEST(deposit, withdrawalByYear_3) {
  Op op_1{1235567, OpType::WITHDRAWAL, Date{6, 6, 2013}};
  std::vector<Op> ops{op_1};
  Data data{12578367.22,       52,  MONTHS, 7.852, 16, Type::SECOND, Freq::YEAR,
            Date{15, 2, 2011}, &ops};
  testDeposit(data, {4673986.21, 16016786.43});
}

TEST(deposit, withdrawalByYear_4) {
  Op op_1{1235567, OpType::WITHDRAWAL, Date{6, 6, 2013}};
  std::vector<Op> ops{op_1};
  Data data{12578367.22,       52,  MONTHS, 7.852, 16, Type::FIRST, Freq::YEAR,
            Date{15, 2, 2011}, &ops};
  testDeposit(data, {4078895.91, 11342800.22});
}

TEST(deposit, withdrawalByYear_5) {
  Op op_1{25715345, OpType::WITHDRAWAL, Date{7, 8, 2024}};
  Op op_2{16152222, OpType::WITHDRAWAL, Date{9, 9, 2024}};
  std::vector<Op> ops{op_1, op_2};
  Data data{102635556.23, 66,         MONTHS,           5.562, 16,
            Type::SECOND, Freq::YEAR, Date{7, 2, 2021}, &ops};
  testDeposit(data, {30879882.35, 91647871.58});
}

TEST(deposit, withdrawalByYear_6) {
  Op op_1{25715345, OpType::WITHDRAWAL, Date{7, 8, 2024}};
  Op op_2{16152222, OpType::WITHDRAWAL, Date{9, 9, 2024}};
  std::vector<Op> ops{op_1, op_2};
  Data data{102635556.23, 66,         MONTHS,           5.562, 16,
            Type::FIRST,  Freq::YEAR, Date{7, 2, 2021}, &ops};
  testDeposit(data, {26799981.98, 60767989.23});
}

TEST(deposit, withdrawalByYear_7) {
  Op op_1{22222222, OpType::WITHDRAWAL, Date{2, 2, 2015}};
  Op op_2{11111111, OpType::WITHDRAWAL, Date{2, 2, 2018}};
  std::vector<Op> ops{op_1, op_2};
  Data data{8737647.43,        121, MONTHS, 8.476, 16, Type::SECOND, Freq::YEAR,
            Date{31, 1, 2015}, &ops};
  testDeposit(data, {2456615.95, 83152.38});
}

TEST(deposit, withdrawalByYear_8) {
  Op op_1{22222222, OpType::WITHDRAWAL, Date{2, 2, 2015}};
  Op op_2{11111111, OpType::WITHDRAWAL, Date{2, 2, 2018}};
  std::vector<Op> ops{op_1, op_2};
  Data data{8737647.43,        121, MONTHS, 8.476, 16, Type::FIRST, Freq::YEAR,
            Date{31, 1, 2015}, &ops};
  testDeposit(data, {7462843.38, 8737647.43});
}

TEST(deposit, withdrawalByYear_9) {
  Op op_1{1111111, OpType::WITHDRAWAL, Date{3, 5, 2022}};
  Op op_2{2222222, OpType::WITHDRAWAL, Date{29, 2, 2024}};
  Op op_3{3333333, OpType::WITHDRAWAL, Date{3, 7, 2025}};
  Op op_4{4444444, OpType::WITHDRAWAL, Date{10, 7, 2025}};
  std::vector<Op> ops{op_1, op_2, op_3, op_4};
  Data data{62563535.23, 76,           MONTHS,     7.851,
            16,          Type::SECOND, Freq::YEAR, Date{22, 11, 2020},
            &ops};
  testDeposit(data, {36275146.38, 87727571.61});
}

TEST(deposit, withdrawalByYear_10) {
  Op op_1{1111111, OpType::WITHDRAWAL, Date{3, 5, 2022}};
  Op op_2{2222222, OpType::WITHDRAWAL, Date{29, 2, 2024}};
  Op op_3{3333333, OpType::WITHDRAWAL, Date{3, 7, 2025}};
  Op op_4{4444444, OpType::WITHDRAWAL, Date{10, 7, 2025}};
  std::vector<Op> ops{op_1, op_2, op_3, op_4};
  Data data{62563535.23,        76,  MONTHS, 7.851, 16, Type::FIRST, Freq::YEAR,
            Date{22, 11, 2020}, &ops};
  testDeposit(data, {29082700.15, 51452425.23});
}

//  ============================================================================

TEST(deposit, withdrawalByEndTerm_1) {
  Op op_1{25000, OpType::WITHDRAWAL, Date{5, 1, 2024}};
  std::vector<Op> ops{op_1};
  Data data{150000, 12,          MONTHS,        15,
            16,     Type::FIRST, Freq::ENDTERM, Date{23, 11, 2023},
            &ops};
  testDeposit(data, {19196.97, 125000});
}

TEST(deposit, withdrawalByEndTerm_2) {
  Op op_1{1235567, OpType::WITHDRAWAL, Date{6, 6, 2013}};
  std::vector<Op> ops{op_1};
  Data data{12578367.22, 52,          MONTHS,        7.852,
            16,          Type::FIRST, Freq::ENDTERM, Date{15, 2, 2011},
            &ops};
  testDeposit(data, {4078895.91, 11342800.22});
}

TEST(deposit, withdrawalByEndTerm_3) {
  Op op_1{25715345, OpType::WITHDRAWAL, Date{7, 8, 2024}};
  Op op_2{16152222, OpType::WITHDRAWAL, Date{9, 9, 2024}};
  std::vector<Op> ops{op_1, op_2};
  Data data{102635556.23, 66,          MONTHS,        5.562,
            16,           Type::FIRST, Freq::ENDTERM, Date{7, 2, 2021},
            &ops};
  testDeposit(data, {26799981.96, 60767989.23});
}

TEST(deposit, withdrawalByEndTerm_4) {
  Op op_1{22222222, OpType::WITHDRAWAL, Date{2, 2, 2015}};
  Op op_2{11111111, OpType::WITHDRAWAL, Date{2, 2, 2018}};
  std::vector<Op> ops{op_1, op_2};
  Data data{8737647.43, 121,         MONTHS,        8.476,
            16,         Type::FIRST, Freq::ENDTERM, Date{31, 1, 2015},
            &ops};
  testDeposit(data, {7462843.34, 8737647.43});
}

TEST(deposit, withdrawalByEndTerm_5) {
  Op op_1{1111111, OpType::WITHDRAWAL, Date{3, 5, 2022}};
  Op op_2{2222222, OpType::WITHDRAWAL, Date{29, 2, 2024}};
  Op op_3{3333333, OpType::WITHDRAWAL, Date{3, 7, 2025}};
  Op op_4{4444444, OpType::WITHDRAWAL, Date{10, 7, 2025}};
  std::vector<Op> ops{op_1, op_2, op_3, op_4};
  Data data{62563535.23, 76,          MONTHS,        7.851,
            16,          Type::FIRST, Freq::ENDTERM, Date{22, 11, 2020},
            &ops};
  testDeposit(data, {29082700.15, 51452425.23});
}

TEST(deposit, combinated_1) {
  Op op_1{1111111, OpType::WITHDRAWAL, Date{3, 5, 2026}};
  Op op_2{2222222, OpType::WITHDRAWAL, Date{29, 2, 2028}};
  Op op_3{5555555, OpType::REFILL, Date{3, 7, 2029}};
  Op op_4{84444444, OpType::WITHDRAWAL, Date{10, 7, 2029}};
  std::vector<Op> ops{op_1, op_2, op_3, op_4};
  Data data{62563535.23, 76,           MONTHS,      7.851,
            16,          Type::SECOND, Freq::MONTH, s21::Date{22, 11, 2024},
            &ops};
  testDeposit(data, {27771206.62, 8112519.85});
}

TEST(deposit, combinated_2) {
  Op op_1{2533444, OpType::REFILL, Date{1, 2, 2029}};
  Op op_2{1245234, OpType::WITHDRAWAL, Date{5, 6, 2030}};
  Op op_3{2222222, OpType::WITHDRAWAL, Date{1, 1, 2031}};
  Op op_4{987656, OpType::REFILL, Date{11, 11, 2031}};
  Op op_5{12423556, OpType::REFILL, Date{8, 7, 2032}};
  std::vector<Op> ops{op_1, op_2, op_3, op_4, op_5};
  Data data{12343452.12, 51,           MONTHS,        11.213,
            16,          Type::SECOND, Freq::QUARTER, s21::Date{29, 2, 2028},
            &ops};
  testDeposit(data, {7904118.47, 20301214.59});
}

TEST(deposit, combinated_3) {
  Op op_1{6672311, OpType::WITHDRAWAL, Date{4, 12, 2029}};
  Op op_2{42335566, OpType::REFILL, Date{1, 2, 2030}};
  Op op_3{31000000, OpType::WITHDRAWAL, Date{7, 2, 2030}};
  Op op_4{3211111, OpType::REFILL, Date{28, 2, 2030}};
  Op op_5{12001233, OpType::WITHDRAWAL, Date{8, 8, 2035}};
  Op op_6{1987656, OpType::REFILL, Date{5, 6, 2037}};
  std::vector<Op> ops{op_1, op_2, op_3, op_4, op_5, op_6};
  Data data{9999999.99, 99,           MONTHS,    9.999,
            16,         Type::SECOND, Freq::DAY, s21::Date{9, 9, 2029},
            &ops};
  testDeposit(data, {18969788.40, 26830577.39});
}

TEST(deposit, combinated_4) {
  Op op_1{6672311, OpType::WITHDRAWAL, Date{4, 12, 2029}};
  Op op_2{42335566, OpType::REFILL, Date{1, 2, 2030}};
  Op op_3{31000000, OpType::WITHDRAWAL, Date{7, 2, 2030}};
  Op op_4{3211111, OpType::REFILL, Date{28, 2, 2030}};
  Op op_5{12001233, OpType::WITHDRAWAL, Date{8, 8, 2033}};
  Op op_6{1987656, OpType::REFILL, Date{5, 6, 2034}};
  std::vector<Op> ops{op_1, op_2, op_3, op_4, op_5, op_6};
  Data data{61253378.11, 92,           MONTHS,     22.311,
            16,          Type::SECOND, Freq::WEEK, s21::Date{21, 2, 2029},
            &ops};
  testDeposit(data, {291466976.93, 350581144.04});
}

TEST(deposit, combinated_5) {
  Op op_1{42335566, OpType::REFILL, Date{23, 6, 2025}};
  Op op_2{1987656, OpType::REFILL, Date{29, 7, 2025}};
  Op op_3{12001233, OpType::WITHDRAWAL, Date{8, 8, 2025}};
  Op op_4{3211111, OpType::REFILL, Date{28, 2, 2029}};
  Op op_5{6672311, OpType::WITHDRAWAL, Date{4, 12, 2029}};
  Op op_6{31000000, OpType::WITHDRAWAL, Date{7, 2, 2030}};
  std::vector<Op> ops{op_1, op_2, op_3, op_4, op_5, op_6};
  Data data{771332.12, 56,           MONTHS,         17.275,
            16,        Type::SECOND, Freq::HALFYEAR, s21::Date{22, 6, 2025},
            &ops};
  testDeposit(data, {39244887.07, 37877008.19});
}
