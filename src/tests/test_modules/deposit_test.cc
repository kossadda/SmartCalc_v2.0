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
using Data = s21::DepositModel::Data;
using Freq = s21::DepositModel::Frequency;
using Type = s21::DepositModel::Type;
using Date = s21::Date;

void testDeposit(const Data &data, Freq freq,
                 std::vector<long double> expected) {
  s21::DepositModel deposit;

  deposit.addData(data, 16, freq);
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

TEST(deposit, by_day_1) {
  Data data{10000, 12, MONTHS, 15, Type::FIRST, Date{1, 1, 2020}};
  testDeposit(data, Freq::DAY, {1500.61, 10000});
}

TEST(deposit, by_day_2) {
  Data data{10000, 12, MONTHS, 15, Type::SECOND, Date{1, 1, 2020}};
  testDeposit(data, Freq::DAY, {1617.99, 11617.99});
}

TEST(deposit, by_day_3) {
  Data data{147634.72, 17, MONTHS, 13.218, Type::FIRST, Date{7, 5, 2017}};
  testDeposit(data, Freq::DAY, {27692.28, 147634.72});
}

TEST(deposit, by_day_4) {
  Data data{147634.72, 17, MONTHS, 13.218, Type::SECOND, Date{7, 5, 2017}};
  testDeposit(data, Freq::DAY, {30456.34, 178091.06});
}

TEST(deposit, by_day_5) {
  Data data{895625.37, 25, MONTHS, 12.345, Type::FIRST, Date{8, 2, 1988}};
  testDeposit(data, Freq::DAY, {229644.87, 895625.37});
}

TEST(deposit, by_day_6) {
  Data data{895625.37, 25, MONTHS, 12.345, Type::SECOND, Date{8, 2, 1988}};
  testDeposit(data, Freq::DAY, {261720.87, 1157346.24});
}

TEST(deposit, by_day_7) {
  Data data{7777777.77, 77, MONTHS, 7.777, Type::FIRST, Date{7, 7, 1977}};
  testDeposit(data, Freq::DAY, {3882818.82, 7777777.77});
}

TEST(deposit, by_day_8) {
  Data data{7777777.77, 77, MONTHS, 7.777, Type::SECOND, Date{7, 7, 1977}};
  testDeposit(data, Freq::DAY, {5034923.39, 12812701.16});
}

TEST(deposit, by_day_9) {
  Data data{326741742.86, 7037, DAYS, 16.123, Type::FIRST, Date{1, 1, 2024}};
  testDeposit(data, Freq::DAY, {1014931284.35, 326741742.86});
}

TEST(deposit, by_day_10) {
  Data data{326741742.86, 7037, DAYS, 16.123, Type::SECOND, Date{1, 1, 2024}};
  testDeposit(data, Freq::DAY, {6966499579.12, 7293241321.98});
}

TEST(deposit, by_week_1) {
  Data data{10000, 12, MONTHS, 15, Type::FIRST, Date{1, 1, 2020}};
  testDeposit(data, Freq::WEEK, {1500.09, 10000});
}

TEST(deposit, by_week_2) {
  Data data{10000, 12, MONTHS, 15, Type::SECOND, Date{1, 1, 2020}};
  testDeposit(data, Freq::WEEK, {1615.86, 11615.86});
}

TEST(deposit, by_week_3) {
  Data data{147634.72, 17, MONTHS, 13.218, Type::FIRST, Date{7, 5, 2017}};
  testDeposit(data, Freq::WEEK, {27694.5, 147634.72});
}

TEST(deposit, by_week_4) {
  Data data{147634.72, 17, MONTHS, 13.218, Type::SECOND, Date{7, 5, 2017}};
  testDeposit(data, Freq::WEEK, {30419.95, 178054.67});
}

TEST(deposit, by_week_5) {
  Data data{895625.37, 25, MONTHS, 12.345, Type::FIRST, Date{8, 2, 1988}};
  testDeposit(data, Freq::WEEK, {229643.64, 895625.37});
}

TEST(deposit, by_week_6) {
  Data data{895625.37, 25, MONTHS, 12.345, Type::SECOND, Date{8, 2, 1988}};
  testDeposit(data, Freq::WEEK, {261421.69, 1157047.06});
}

TEST(deposit, by_week_7) {
  Data data{7777777.77, 77, MONTHS, 7.777, Type::FIRST, Date{7, 7, 1977}};
  testDeposit(data, Freq::WEEK, {3882819.34, 7777777.77});
}

TEST(deposit, by_week_8) {
  Data data{7777777.77, 77, MONTHS, 7.777, Type::SECOND, Date{7, 7, 1977}};
  testDeposit(data, Freq::WEEK, {5030844.09, 12808621.86});
}

TEST(deposit, by_week_9) {
  Data data{326741742.86, 18037, DAYS, 16.123, Type::FIRST, Date{1, 1, 2024}};
  testDeposit(data, Freq::WEEK, {2601410292.21, 326741742.86});
}

TEST(deposit, by_week_10) {
  Data data{326741742.86, 18037, DAYS, 16.123, Type::SECOND, Date{1, 1, 2024}};
  testDeposit(data, Freq::WEEK, {925615593479.03, 925942335221.89});
}

TEST(deposit, by_month_1) {
  Data data{10000, 12, MONTHS, 15, Type::FIRST, Date{1, 1, 2020}};
  testDeposit(data, Freq::MONTH, {1500.01, 10000});
}

TEST(deposit, by_month_2) {
  Data data{10000, 12, MONTHS, 15, Type::SECOND, Date{1, 1, 2020}};
  testDeposit(data, Freq::MONTH, {1607.55, 11607.55});
}

TEST(deposit, by_month_3) {
  Data data{147634.72, 17, MONTHS, 13.218, Type::FIRST, Date{7, 5, 2017}};
  testDeposit(data, Freq::MONTH, {27694.31, 147634.72});
}

TEST(deposit, by_month_4) {
  Data data{147634.72, 17, MONTHS, 13.218, Type::SECOND, Date{7, 5, 2017}};
  testDeposit(data, Freq::MONTH, {30279.24, 177913.96});
}

TEST(deposit, by_month_5) {
  Data data{895625.37, 25, MONTHS, 12.345, Type::FIRST, Date{8, 2, 1988}};
  testDeposit(data, Freq::MONTH, {229643.87, 895625.37});
}

TEST(deposit, by_month_6) {
  Data data{895625.37, 25, MONTHS, 12.345, Type::SECOND, Date{8, 2, 1988}};
  testDeposit(data, Freq::MONTH, {260259.36, 1155884.73});
}

TEST(deposit, by_month_7) {
  Data data{7777777.77, 77, MONTHS, 7.777, Type::FIRST, Date{7, 7, 1977}};
  testDeposit(data, Freq::MONTH, {3882818.11, 7777777.77});
}

TEST(deposit, by_month_8) {
  Data data{7777777.77, 77, MONTHS, 7.777, Type::SECOND, Date{7, 7, 1977}};
  testDeposit(data, Freq::MONTH, {5014960.02, 12792737.79});
}

TEST(deposit, by_month_9) {
  Data data{326741742.86, 7037, DAYS, 16.123, Type::FIRST, Date{1, 1, 2024}};
  testDeposit(data, Freq::MONTH, {1014931288.92, 326741742.86});
}

TEST(deposit, by_month_10) {
  Data data{326741742.86, 7037, DAYS, 16.123, Type::SECOND, Date{1, 1, 2024}};
  testDeposit(data, Freq::MONTH, {6822138779.35, 7148880522.21});
}

TEST(deposit, by_quarter_1) {
  Data data{10000, 12, MONTHS, 15, Type::FIRST, Date{1, 1, 2020}};
  testDeposit(data, Freq::QUARTER, {1500.01, 10000});
}

TEST(deposit, by_quarter_2) {
  Data data{10000, 12, MONTHS, 15, Type::SECOND, Date{1, 1, 2020}};
  testDeposit(data, Freq::QUARTER, {1586.52, 11586.52});
}

TEST(deposit, by_quarter_3) {
  Data data{147634.72, 17, MONTHS, 13.218, Type::FIRST, Date{7, 5, 2017}};
  testDeposit(data, Freq::QUARTER, {27694.36, 147634.72});
}

TEST(deposit, by_quarter_4) {
  Data data{147634.72, 17, MONTHS, 13.218, Type::SECOND, Date{7, 5, 2017}};
  testDeposit(data, Freq::QUARTER, {29942.8, 177577.52});
}

TEST(deposit, by_quarter_5) {
  Data data{895625.37, 25, MONTHS, 12.345, Type::FIRST, Date{8, 2, 1988}};
  testDeposit(data, Freq::QUARTER, {229643.87, 895625.37});
}

TEST(deposit, by_quarter_6) {
  Data data{895625.37, 25, MONTHS, 12.345, Type::SECOND, Date{8, 2, 1988}};
  testDeposit(data, Freq::QUARTER, {257405.01, 1153030.38});
}

TEST(deposit, by_quarter_7) {
  Data data{7777777.77, 77, MONTHS, 7.777, Type::FIRST, Date{7, 7, 1977}};
  testDeposit(data, Freq::QUARTER, {3882818.14, 7777777.77});
}

TEST(deposit, by_quarter_8) {
  Data data{7777777.77, 77, MONTHS, 7.777, Type::SECOND, Date{7, 7, 1977}};
  testDeposit(data, Freq::QUARTER, {4974861.53, 12752639.3});
}

TEST(deposit, by_quarter_9) {
  Data data{326741742.86, 7037, DAYS, 16.123, Type::FIRST, Date{1, 1, 2024}};
  testDeposit(data, Freq::QUARTER, {1014931289.5, 326741742.86});
}

TEST(deposit, by_quarter_10) {
  Data data{326741742.86, 7037, DAYS, 16.123, Type::SECOND, Date{1, 1, 2024}};
  testDeposit(data, Freq::QUARTER, {6540254793.1, 6866996535.96});
}

TEST(deposit, by_halfyear_1) {
  Data data{10000, 12, MONTHS, 15, Type::FIRST, Date{1, 1, 2020}};
  testDeposit(data, Freq::HALFYEAR, {1500.01, 10000});
}

TEST(deposit, by_halfyear_2) {
  Data data{10000, 12, MONTHS, 15, Type::SECOND, Date{1, 1, 2020}};
  testDeposit(data, Freq::HALFYEAR, {1556.26, 11556.26});
}

TEST(deposit, by_halfyear_3) {
  Data data{147634.72, 17, MONTHS, 13.218, Type::FIRST, Date{7, 5, 2017}};
  testDeposit(data, Freq::HALFYEAR, {27694.34, 147634.72});
}

TEST(deposit, by_halfyear_4) {
  Data data{147634.72, 17, MONTHS, 13.218, Type::SECOND, Date{7, 5, 2017}};
  testDeposit(data, Freq::HALFYEAR, {29456.11, 177090.83});
}

TEST(deposit, by_halfyear_5) {
  Data data{895625.37, 25, MONTHS, 12.345, Type::FIRST, Date{8, 2, 1988}};
  testDeposit(data, Freq::HALFYEAR, {229643.87, 895625.37});
}

TEST(deposit, by_halfyear_6) {
  Data data{895625.37, 25, MONTHS, 12.345, Type::SECOND, Date{8, 2, 1988}};
  testDeposit(data, Freq::HALFYEAR, {253275.69, 1148901.06});
}

TEST(deposit, by_halfyear_7) {
  Data data{7777777.77, 77, MONTHS, 7.777, Type::FIRST, Date{7, 7, 1977}};
  testDeposit(data, Freq::HALFYEAR, {3882818.19, 7777777.77});
}

TEST(deposit, by_halfyear_8) {
  Data data{7777777.77, 77, MONTHS, 7.777, Type::SECOND, Date{7, 7, 1977}};
  testDeposit(data, Freq::HALFYEAR, {4916176.13, 12693953.9});
}

TEST(deposit, by_halfyear_9) {
  Data data{326741742.86, 7037, DAYS, 16.123, Type::FIRST, Date{1, 1, 2024}};
  testDeposit(data, Freq::HALFYEAR, {1014931289.31, 326741742.86});
}

TEST(deposit, by_halfyear_10) {
  Data data{326741742.86, 7037, DAYS, 16.123, Type::SECOND, Date{1, 1, 2024}};
  testDeposit(data, Freq::HALFYEAR, {6158421560.45, 6485163303.31});
}

TEST(deposit, by_year_1) {
  Data data{10000, 12, MONTHS, 15, Type::FIRST, Date{1, 1, 2020}};
  testDeposit(data, Freq::YEAR, {1500.01, 10000});
}

TEST(deposit, by_year_2) {
  Data data{10000, 12, MONTHS, 15, Type::SECOND, Date{1, 1, 2020}};
  testDeposit(data, Freq::YEAR, {1500.01, 11500.01});
}

TEST(deposit, by_year_3) {
  Data data{147634.72, 17, MONTHS, 13.218, Type::FIRST, Date{7, 5, 2017}};
  testDeposit(data, Freq::YEAR, {27694.35, 147634.72});
}

TEST(deposit, by_year_4) {
  Data data{147634.72, 17, MONTHS, 13.218, Type::SECOND, Date{7, 5, 2017}};
  testDeposit(data, Freq::YEAR, {28775.58, 176410.3});
}

TEST(deposit, by_year_5) {
  Data data{895625.37, 25, MONTHS, 12.345, Type::FIRST, Date{8, 2, 1988}};
  testDeposit(data, Freq::YEAR, {229643.87, 895625.37});
}

TEST(deposit, by_year_6) {
  Data data{895625.37, 25, MONTHS, 12.345, Type::SECOND, Date{8, 2, 1988}};
  testDeposit(data, Freq::YEAR, {245520.84, 1141146.21});
}

TEST(deposit, by_year_7) {
  Data data{7777777.77, 77, MONTHS, 7.777, Type::FIRST, Date{7, 7, 1977}};
  testDeposit(data, Freq::YEAR, {3882818.18, 7777777.77});
}

TEST(deposit, by_year_8) {
  Data data{7777777.77, 77, MONTHS, 7.777, Type::SECOND, Date{7, 7, 1977}};
  testDeposit(data, Freq::YEAR, {4809852.33, 12587630.1});
}

TEST(deposit, by_year_9) {
  Data data{326741742.86, 7037, DAYS, 16.123, Type::FIRST, Date{1, 1, 2024}};
  testDeposit(data, Freq::YEAR, {1014931289.4, 326741742.86});
}

TEST(deposit, by_year_10) {
  Data data{326741742.86, 7037, DAYS, 16.123, Type::SECOND, Date{1, 1, 2024}};
  testDeposit(data, Freq::YEAR, {5505997235.41, 5832738978.27});
}

TEST(deposit, by_end_term_1) {
  Data data{10000, 12, MONTHS, 15, Type::FIRST, Date{1, 1, 2020}};
  testDeposit(data, Freq::ENDTERM, {1500.01, 10000});
}

TEST(deposit, by_end_term_2) {
  Data data{147634.72, 17, MONTHS, 13.218, Type::FIRST, Date{7, 5, 2017}};
  testDeposit(data, Freq::ENDTERM, {27694.35, 147634.72});
}

TEST(deposit, by_end_term_3) {
  Data data{895625.37, 25, MONTHS, 12.345, Type::FIRST, Date{8, 2, 1988}};
  testDeposit(data, Freq::ENDTERM, {229643.88, 895625.37});
}

TEST(deposit, by_end_term_4) {
  Data data{7777777.77, 77, MONTHS, 7.777, Type::FIRST, Date{7, 7, 1977}};
  testDeposit(data, Freq::ENDTERM, {3882818.17, 7777777.77});
}

TEST(deposit, by_end_term_5) {
  Data data{326741742.86, 7037, DAYS, 16.123, Type::FIRST, Date{1, 1, 2024}};
  testDeposit(data, Freq::ENDTERM, {1014931289.38, 326741742.86});
}
