/**
 * @file credit_test.cc
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-09-20
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../main_test.h"

using Type = CreditModel::CreditType;

void testAnnuity(long double amount, int period, long double rate, int day,
                 int month, int year,
                 const std::vector<long double>& expected_results) {
  CreditModel credit;

  credit.addData(amount, period, rate, Date(day, month, year),
                 CreditModel::CreditType::ANNUITY);
  credit.calculatePayments();
  std::vector<long double> true_res = expected_results;

  for (std::size_t i{}; i < true_res.size(); ++i) {
    long double res = credit.total().at(i);
    long double exp = true_res.at(i);
    EXPECT_NEAR(res, exp, 1e-3)
        << "\nRes : " << res << "\nTrue: " << exp << '\n';
  }
}

void testDifferentiated(long double amount, int period, long double rate,
                        int day, int month, int year,
                        const std::vector<long double>& expected_results) {
  CreditModel credit;

  credit.addData(amount, period, rate, Date(day, month, year),
                 CreditModel::CreditType::DIFFERENTIATED);
  credit.calculatePayments();
  std::vector<long double> true_res = expected_results;

  for (std::size_t i{}; i < true_res.size(); ++i) {
    long double res = credit.total().at(i);
    long double exp = true_res.at(i);
    EXPECT_NEAR(res, exp, 1e-3)
        << "\nRes : " << res << "\nTrue: " << exp << '\n';
  }
}

TEST(credit, annuity_1) {
  testAnnuity(1000, 4, 5, 6, 7, 2021, {1010.57, 1000, 10.57});
}

TEST(credit, annuity_2) {
  testAnnuity(800, 12, 3, 22, 2, 2016, {812.99, 800, 12.99});
}

TEST(credit, annuity_3) {
  testAnnuity(9862.12, 7, 13.77, 9, 9, 2000, {10318.04, 9862.12, 455.92});
}

TEST(credit, annuity_4) {
  testAnnuity(26744.12, 15, 16.111, 12, 3, 2005, {29719.33, 26744.12, 2975.21});
}

TEST(credit, annuity_5) {
  testAnnuity(38235.23, 18, 9.725, 24, 4, 2014, {41250.63, 38235.23, 3015.4});
}

TEST(credit, annuity_6) {
  testAnnuity(49715.84, 21, 19.875, 21, 7, 2019, {59305.94, 49715.84, 9590.1});
}

TEST(credit, annuity_7) {
  testAnnuity(54798.48, 25, 17.121, 16, 1, 2022, {65509.5, 54798.48, 10711.02});
}

TEST(credit, annuity_8) {
  testAnnuity(64972.21, 26, 14.875, 28, 2, 2024,
              {76361.58, 64972.21, 11389.37});
}

TEST(credit, annuity_9) {
  testAnnuity(72578.54, 28, 21.254, 8, 11, 2008,
              {92635.41, 72578.54, 20056.87});
}

TEST(credit, annuity_10) {
  testAnnuity(81458.47, 21, 16.789, 12, 12, 2012,
              {94559.9, 81458.47, 13101.43});
}

TEST(credit, annuity_11) {
  testAnnuity(92784.88, 29, 19.987, 25, 11, 2020,
              {117690.04, 92784.88, 24905.16});
}

TEST(credit, annuity_12) {
  testAnnuity(99999.99, 30, 19.999, 9, 9, 2009,
              {127853.88, 99999.99, 27853.89});
}

TEST(credit, annuity_13) {
  testAnnuity(105597.84, 32, 21.847, 4, 10, 2011,
              {140275.08, 105597.84, 34677.24});
}

TEST(credit, annuity_14) {
  testAnnuity(114874.84, 34, 22.221, 8, 8, 2008,
              {155807.13, 114874.84, 40932.29});
}

TEST(credit, annuity_15) {
  testAnnuity(120000, 12, 12, 19, 12, 2023, {127947.47, 120000, 7947.47});
}

TEST(credit, annuity_16) {
  testAnnuity(122784.45, 35, 24.876, 11, 12, 1989,
              {173860.53, 122784.45, 51076.08});
}

TEST(credit, annuity_17) {
  testAnnuity(137846.94, 37, 27.182, 25, 2, 1998,
              {204743.09, 137846.94, 66896.15});
}

TEST(credit, annuity_18) {
  testAnnuity(143975.18, 38, 1.845, 15, 9, 1945,
              {148330.04, 143975.18, 4354.86});
}

TEST(credit, annuity_19) {
  testAnnuity(151879.84, 40, 8.971, 20, 11, 1978,
              {176256.41, 151879.84, 24376.57});
}

TEST(credit, annuity_20) {
  testAnnuity(158797.48, 42, 45.847, 1, 1, 2001,
              {320600.04, 158797.48, 161802.56});
}

TEST(credit, annuity_21) {
  testAnnuity(168848.24, 43, 33.333, 3, 3, 2033,
              {291898.66, 168848.24, 123050.42});
}

TEST(credit, annuity_22) {
  testAnnuity(177548.15, 45, 30.001, 6, 7, 2028,
              {297904.33, 177548.15, 120356.18});
}

TEST(credit, annuity_23) {
  testAnnuity(184999.99, 47, 24.919, 4, 11, 2021,
              {291326.81, 184999.99, 106326.82});
}

TEST(credit, annuity_24) {
  testAnnuity(199999.99, 39, 9.999, 9, 9, 1999,
              {235054.76, 199999.99, 35054.77});
}

TEST(credit, annuity_25) {
  testAnnuity(224875.67, 48, 57.487, 11, 2, 1947,
              {573870.68, 224875.67, 348995.01});
}

TEST(credit, annuity_26) {
  testAnnuity(249723.16, 49, 43.196, 4, 9, 1967,
              {534585.92, 249723.16, 284862.76});
}

TEST(credit, annuity_27) {
  testAnnuity(276314.57, 50, 64.878, 1, 2, 2003,
              {795788.74, 276314.57, 519474.17});
}

TEST(credit, annuity_28) {
  testAnnuity(300000, 51, 68.778, 6, 11, 2048, {924455.42, 300000, 624455.42});
}

TEST(credit, annuity_29) {
  testAnnuity(337541.43, 52, 71.381, 9, 5, 2005,
              {1110467.87, 337541.43, 772926.44});
}

TEST(credit, annuity_30) {
  testAnnuity(374112.34, 53, 74.164, 11, 12, 2013,
              {1275795.53, 374112.34, 901683.19});
}

TEST(credit, annuity_31) {
  testAnnuity(400000, 54, 45.694, 16, 1, 1982, {945742.58, 400000, 545742.58});
}

TEST(credit, annuity_32) {
  testAnnuity(442341.55, 55, 26.533, 6, 11, 1987,
              {768335.62, 442341.55, 325994.07});
}

TEST(credit, annuity_33) {
  testAnnuity(485212.25, 56, 44.444, 14, 5, 2045,
              {1161540.56, 485212.25, 676328.31});
}

TEST(credit, annuity_34) {
  testAnnuity(542678.51, 57, 34.157, 11, 6, 2033,
              {1104172.78, 542678.51, 561494.27});
}

TEST(credit, annuity_35) {
  testAnnuity(594314.32, 58, 26.441, 2, 3, 2022,
              {1060209.81, 594314.32, 465895.49});
}

TEST(credit, annuity_36) {
  testAnnuity(642314.87, 59, 79.548, 5, 4, 2012,
              {2560669.04, 642314.87, 1918354.17});
}

TEST(credit, annuity_37) {
  testAnnuity(697431.11, 60, 81.544, 11, 10, 2016,
              {2885566.46, 697431.11, 2188135.35});
}

TEST(credit, annuity_38) {
  testAnnuity(764131.15, 61, 84.517, 18, 6, 2154,
              {3375016.47, 764131.15, 2610885.32});
}

TEST(credit, annuity_39) {
  testAnnuity(812341.58, 62, 64.115, 6, 11, 2054,
              {2784070.78, 812341.58, 1971729.2});
}

TEST(credit, annuity_40) {
  testAnnuity(866471.88, 63, 14.587, 31, 1, 2002,
              {1244204.61, 866471.88, 377732.73});
}

TEST(credit, annuity_41) {
  testAnnuity(904131.41, 64, 11.124, 5, 3, 2012,
              {1202915.95, 904131.41, 298784.54});
}

TEST(credit, annuity_42) {
  testAnnuity(971121.54, 65, 7.891, 6, 7, 2021,
              {1196801.19, 971121.54, 225679.65});
}

TEST(credit, annuity_43) {
  testAnnuity(1000000, 66, 100, 5, 12, 2027, {5467523.02, 1000000, 4467523.02});
}

TEST(credit, annuity_44) {
  testAnnuity(1087135.54, 67, 51.112, 17, 7, 2041,
              {3324244.94, 1087135.54, 2237109.4});
}

TEST(credit, annuity_45) {
  testAnnuity(1175434.15, 68, 14.871, 22, 3, 2141,
              {1747477.36, 1175434.15, 572043.21});
}

TEST(credit, annuity_46) {
  testAnnuity(1317981.54, 69, 21.441, 21, 6, 2084,
              {2303273.23, 1317981.54, 985291.69});
}

TEST(credit, annuity_47) {
  testAnnuity(1498752.24, 70, 24.749, 27, 1, 2051,
              {2842310.65, 1498752.24, 1343558.41});
}

TEST(credit, annuity_48) {
  testAnnuity(1674111.57, 71, 8.244, 5, 5, 2005,
              {2121675.22, 1674111.57, 447563.65});
}

TEST(credit, annuity_49) {
  testAnnuity(1847566.39, 72, 14.479, 15, 7, 2029,
              {2776653.67, 1847566.39, 929087.28});
}

TEST(credit, annuity_50) {
  testAnnuity(2000000, 73, 22.222, 22, 2, 2222,
              {3657198.22, 2000000, 1657198.22});
}

TEST(credit, differentiated_1) {
  testDifferentiated(1000, 4, 5, 6, 7, 2021, {1010.54, 1000, 10.54});
}

TEST(credit, differentiated_2) {
  testDifferentiated(800, 12, 3, 22, 2, 2016, {812.94, 800, 12.94});
}

TEST(credit, differentiated_3) {
  testDifferentiated(9862.12, 7, 13.77, 9, 9, 2000,
                     {10312.98, 9862.12, 450.86});
}

TEST(credit, differentiated_4) {
  testDifferentiated(26744.12, 15, 16.111, 12, 3, 2005,
                     {29627.64, 26744.12, 2883.52});
}

TEST(credit, differentiated_5) {
  testDifferentiated(38235.23, 18, 9.725, 24, 4, 2014,
                     {41182.76, 38235.23, 2947.53});
}

TEST(credit, differentiated_6) {
  testDifferentiated(49715.84, 21, 19.875, 21, 7, 2019,
                     {58799.98, 49715.84, 9084.14});
}

TEST(credit, differentiated_7) {
  testDifferentiated(54798.48, 25, 17.121, 16, 1, 2022,
                     {64943.26, 54798.48, 10144.78});
}

TEST(credit, differentiated_8) {
  testDifferentiated(64972.21, 26, 14.875, 28, 2, 2024,
                     {75815.12, 64972.21, 10842.91});
}

TEST(credit, differentiated_9) {
  testDifferentiated(72578.54, 28, 21.254, 8, 11, 2008,
                     {91187.66, 72578.54, 18609.12});
}

TEST(credit, differentiated_10) {
  testDifferentiated(81458.47, 21, 16.789, 12, 12, 2012,
                     {93983.55, 81458.47, 12525.08});
}

TEST(credit, differentiated_11) {
  testDifferentiated(92784.88, 29, 19.987, 25, 11, 2020,
                     {115930.84, 92784.88, 23145.96});
}

TEST(credit, differentiated_12) {
  testDifferentiated(99999.99, 30, 19.999, 9, 9, 2009,
                     {125811.83, 99999.99, 25811.84});
}

TEST(credit, differentiated_13) {
  testDifferentiated(105597.84, 32, 21.847, 4, 10, 2011,
                     {137325.72, 105597.84, 31727.88});
}

TEST(credit, differentiated_14) {
  testDifferentiated(114874.84, 34, 22.221, 8, 8, 2008,
                     {152085.1, 114874.84, 37210.26});
}

TEST(credit, differentiated_15) {
  testDifferentiated(120000, 12, 12, 19, 12, 2023,
                     {127804.58, 120000, 7804.58});
}

TEST(credit, differentiated_16) {
  testDifferentiated(122784.45, 35, 24.876, 11, 12, 1989,
                     {168592.06, 122784.45, 45807.61});
}

TEST(credit, differentiated_17) {
  testDifferentiated(137846.94, 37, 27.182, 25, 2, 1998,
                     {197040, 137846.94, 59193.06});
}

TEST(credit, differentiated_18) {
  testDifferentiated(143975.18, 38, 1.845, 15, 9, 1945,
                     {148289.28, 143975.18, 4314.1});
}

TEST(credit, differentiated_19) {
  testDifferentiated(151879.84, 40, 8.971, 20, 11, 1978,
                     {175137.6, 151879.84, 23257.76});
}

TEST(credit, differentiated_20) {
  testDifferentiated(158797.48, 42, 45.847, 1, 1, 2001,
                     {289085.83, 158797.48, 130288.35});
}

TEST(credit, differentiated_21) {
  testDifferentiated(168848.24, 43, 33.333, 3, 3, 2033,
                     {272200.89, 168848.24, 103352.65});
}

TEST(credit, differentiated_22) {
  testDifferentiated(177548.15, 45, 30.001, 6, 7, 2028,
                     {279688.78, 177548.15, 102140.63});
}

TEST(credit, differentiated_23) {
  testDifferentiated(184999.99, 47, 24.919, 4, 11, 2021,
                     {277131.45, 184999.99, 92131.46});
}

TEST(credit, differentiated_24) {
  testDifferentiated(199999.99, 39, 9.999, 9, 9, 1999,
                     {233312.06, 199999.99, 33312.07});
}

TEST(credit, differentiated_25) {
  testDifferentiated(224875.67, 48, 57.487, 11, 2, 1947,
                     {488354.28, 224875.67, 263478.61});
}

TEST(credit, differentiated_26) {
  testDifferentiated(249723.16, 49, 43.196, 4, 9, 1967,
                     {474344.46, 249723.16, 224621.3});
}

TEST(credit, differentiated_27) {
  testDifferentiated(276314.57, 50, 64.878, 1, 2, 2003,
                     {656611.77, 276314.57, 380297.2});
}

TEST(credit, differentiated_28) {
  testDifferentiated(300000, 51, 68.778, 6, 11, 2048,
                     {746693.89, 300000, 446693.89});
}

TEST(credit, differentiated_29) {
  testDifferentiated(337541.43, 52, 71.381, 9, 5, 2005,
                     {870241.02, 337541.43, 532699.59});
}

TEST(credit, differentiated_30) {
  testDifferentiated(374112.34, 53, 74.164, 11, 12, 2013,
                     {998288.37, 374112.34, 624176.03});
}

TEST(credit, differentiated_31) {
  testDifferentiated(400000, 54, 45.694, 16, 1, 1982,
                     {818483.57, 400000, 418483.57});
}

TEST(credit, differentiated_32) {
  testDifferentiated(442341.55, 55, 26.533, 6, 11, 1987,
                     {716034.89, 442341.55, 273693.34});
}

TEST(credit, differentiated_33) {
  testDifferentiated(485212.25, 56, 44.444, 14, 5, 2045,
                     {997946.16, 485212.25, 512733.91});
}

TEST(credit, differentiated_34) {
  testDifferentiated(542678.51, 57, 34.157, 11, 6, 2033,
                     {990837.77, 542678.51, 448159.26});
}

TEST(credit, differentiated_35) {
  testDifferentiated(594314.32, 58, 26.441, 2, 3, 2022,
                     {981102.3, 594314.32, 386787.98});
}

TEST(credit, differentiated_36) {
  testDifferentiated(642314.87, 59, 79.548, 5, 4, 2012,
                     {1919478.63, 642314.87, 1277163.76});
}

TEST(credit, differentiated_37) {
  testDifferentiated(697431.11, 60, 81.544, 11, 10, 2016,
                     {2142613.84, 697431.11, 1445182.73});
}

TEST(credit, differentiated_38) {
  testDifferentiated(764131.15, 61, 84.517, 18, 6, 2154,
                     {2433110.7, 764131.15, 1668979.55});
}

TEST(credit, differentiated_39) {
  testDifferentiated(812341.58, 62, 64.115, 6, 11, 2054,
                     {2178758.18, 812341.58, 1366416.6});
}

TEST(credit, differentiated_40) {
  testDifferentiated(866471.88, 63, 14.587, 31, 1, 2002,
                     {1203053.55, 866471.88, 336581.67});
}

TEST(credit, differentiated_41) {
  testDifferentiated(904131.41, 64, 11.124, 5, 3, 2012,
                     {1176608.45, 904131.41, 272477.04});
}

TEST(credit, differentiated_42) {
  testDifferentiated(971121.54, 65, 7.891, 6, 7, 2021,
                     {1182023.94, 971121.54, 210902.4});
}

TEST(credit, differentiated_43) {
  testDifferentiated(1000000, 66, 100, 5, 12, 2027,
                     {3791435.39, 1000000, 2791435.39});
}

TEST(credit, differentiated_44) {
  testDifferentiated(1087135.54, 67, 51.112, 17, 7, 2041,
                     {2662741.49, 1087135.54, 1575605.95});
}

TEST(credit, differentiated_45) {
  testDifferentiated(1175434.15, 68, 14.871, 22, 3, 2141,
                     {1678496.81, 1175434.15, 503062.66});
}

TEST(credit, differentiated_46) {
  testDifferentiated(1317981.54, 69, 21.441, 21, 6, 2084,
                     {2142092.39, 1317981.54, 824110.85});
}

TEST(credit, differentiated_47) {
  testDifferentiated(1498752.24, 70, 24.749, 27, 1, 2051,
                     {2595361.53, 1498752.24, 1096609.29});
}

TEST(credit, differentiated_48) {
  testDifferentiated(1674111.57, 71, 8.244, 5, 5, 2005,
                     {2088511.44, 1674111.57, 414399.87});
}

TEST(credit, differentiated_49) {
  testDifferentiated(1847566.39, 72, 14.479, 15, 7, 2029,
                     {2661800.25, 1847566.39, 814233.86});
}

TEST(credit, differentiated_50) {
  testDifferentiated(2000000, 73, 22.222, 22, 2, 2222,
                     {3368737.81, 2000000, 1368737.81});
}
