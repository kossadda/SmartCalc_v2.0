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

#define ANN CreditModel::CreditType::ANNUITY
#define DIF CreditModel::CreditType::DIFFERENTIATED
using Data = CreditModel::Data;
using Early = CreditModel::EarlyPayment;
using EarlyType = CreditModel::EarlyPayType;

void testCredit(Data &data, std::vector<long double> exp, std::vector<Early> early = {}) {
  CreditModel credit;

  credit.addData(data);
  credit.addEarlyPayments(early);
  credit.calculatePayments();
  std::vector<long double> true_res = exp;

  for (std::size_t i{}; i < true_res.size(); ++i) {
    long double res = credit.total().at(i);
    long double exp = true_res.at(i);
    EXPECT_NEAR(res, exp, 1e-3) << "\nRes : " << res << "\nTrue: " << exp << '\n';
  }
}

TEST(credit, annuity_1) {
  Data data{1000, 4, 5, ANN, Date{6, 7, 2021}};
  testCredit(data, {1010.57, 1000, 10.57});
}

TEST(credit, annuity_2) {
  Data data{800, 12, 3, ANN, Date{22, 2, 2016}};
  testCredit(data, {812.99, 800, 12.99});
}

TEST(credit, annuity_3) {
  Data data{9862.12, 7, 13.77, ANN, Date{9, 9, 2000}};
  testCredit(data, {10318.04, 9862.12, 455.92});
}

TEST(credit, annuity_4) {
  Data data{26744.12, 15, 16.111, ANN, Date{12, 3, 2005}};
  testCredit(data, {29719.33, 26744.12, 2975.21});
}

TEST(credit, annuity_5) {
  Data data{38235.23, 18, 9.725, ANN, Date{24, 4, 2014}};
  testCredit(data, {41250.63, 38235.23, 3015.4});
}

TEST(credit, annuity_6) {
  Data data{49715.84, 21, 19.875, ANN, Date{21, 7, 2019}};
  testCredit(data, {59305.94, 49715.84, 9590.1});
}

TEST(credit, annuity_7) {
  Data data{54798.48, 25, 17.121, ANN, Date{16, 1, 2022}};
  testCredit(data, {65509.5, 54798.48, 10711.02});
}

TEST(credit, annuity_8) {
  Data data{64972.21, 26, 14.875, ANN, Date{28, 2, 2024}};
  testCredit(data, {76361.58, 64972.21, 11389.37});
}

TEST(credit, annuity_9) {
  Data data{72578.54, 28, 21.254, ANN, Date{8, 11, 2008}};
  testCredit(data, {92635.41, 72578.54, 20056.87});
}

TEST(credit, annuity_10) {
  Data data{81458.47, 21, 16.789, ANN, Date{12, 12, 2012}};
  testCredit(data, {94559.9, 81458.47, 13101.43});
}

TEST(credit, annuity_11) {
  Data data{92784.88, 29, 19.987, ANN, Date{25, 11, 2020}};
  testCredit(data, {117690.04, 92784.88, 24905.16});
}

TEST(credit, annuity_12) {
  Data data{99999.99, 30, 19.999, ANN, Date{9, 9, 2009}};
  testCredit(data, {127853.88, 99999.99, 27853.89});
}

TEST(credit, annuity_13) {
  Data data{105597.84, 32, 21.847, ANN, Date{4, 10, 2011}};
  testCredit(data, {140275.08, 105597.84, 34677.24});
}

TEST(credit, annuity_14) {
  Data data{114874.84, 34, 22.221, ANN, Date{8, 8, 2008}};
  testCredit(data, {155807.13, 114874.84, 40932.29});
}

TEST(credit, annuity_15) {
  Data data{120000, 12, 12, ANN, Date{19, 12, 2023}};
  testCredit(data, {127947.47, 120000, 7947.47});
}

TEST(credit, annuity_16) {
  Data data{122784.45, 35, 24.876, ANN, Date{11, 12, 1989}};
  testCredit(data, {173860.53, 122784.45, 51076.08});
}

TEST(credit, annuity_17) {
  Data data{137846.94, 37, 27.182, ANN, Date{25, 2, 1998}};
  testCredit(data, {204743.09, 137846.94, 66896.15});
}

TEST(credit, annuity_18) {
  Data data{143975.18, 38, 1.845, ANN, Date{15, 9, 1945}};
  testCredit(data, {148330.04, 143975.18, 4354.86});
}

TEST(credit, annuity_19) {
  Data data{151879.84, 40, 8.971, ANN, Date{20, 11, 1978}};
  testCredit(data, {176256.41, 151879.84, 24376.57});
}

TEST(credit, annuity_20) {
  Data data{158797.48, 42, 45.847, ANN, Date{1, 1, 2001}};
  testCredit(data, {320600.04, 158797.48, 161802.56});
}

TEST(credit, annuity_21) {
  Data data{168848.24, 43, 33.333, ANN, Date{3, 3, 2033}};
  testCredit(data, {291898.66, 168848.24, 123050.42});
}

TEST(credit, annuity_22) {
  Data data{177548.15, 45, 30.001, ANN, Date{6, 7, 2028}};
  testCredit(data, {297904.33, 177548.15, 120356.18});
}

TEST(credit, annuity_23) {
  Data data{184999.99, 47, 24.919, ANN, Date{4, 11, 2021}};
  testCredit(data, {291326.81, 184999.99, 106326.82});
}

TEST(credit, annuity_24) {
  Data data{199999.99, 39, 9.999, ANN, Date{9, 9, 1999}};
  testCredit(data, {235054.76, 199999.99, 35054.77});
}

TEST(credit, annuity_25) {
  Data data{224875.67, 48, 57.487, ANN, Date{11, 2, 1947}};
  testCredit(data, {573870.68, 224875.67, 348995.01});
}

TEST(credit, annuity_26) {
  Data data{249723.16, 49, 43.196, ANN, Date{4, 9, 1967}};
  testCredit(data, {534585.92, 249723.16, 284862.76});
}

TEST(credit, annuity_27) {
  Data data{276314.57, 50, 64.878, ANN, Date{1, 2, 2003}};
  testCredit(data, {795788.74, 276314.57, 519474.17});
}

TEST(credit, annuity_28) {
  Data data{300000, 51, 68.778, ANN, Date{6, 11, 2048}};
  testCredit(data, {924455.42, 300000, 624455.42});
}

TEST(credit, annuity_29) {
  Data data{337541.43, 52, 71.381, ANN, Date{9, 5, 2005}};
  testCredit(data, {1110467.87, 337541.43, 772926.44});
}

TEST(credit, annuity_30) {
  Data data{374112.34, 53, 74.164, ANN, Date{11, 12, 2013}};
  testCredit(data, {1275795.53, 374112.34, 901683.19});
}

TEST(credit, annuity_31) {
  Data data{400000, 54, 45.694, ANN, Date{16, 1, 1982}};
  testCredit(data, {945742.58, 400000, 545742.58});
}

TEST(credit, annuity_32) {
  Data data{442341.55, 55, 26.533, ANN, Date{6, 11, 1987}};
  testCredit(data, {768335.62, 442341.55, 325994.07});
}

TEST(credit, annuity_33) {
  Data data{485212.25, 56, 44.444, ANN, Date{14, 5, 2045}};
  testCredit(data, {1161540.56, 485212.25, 676328.31});
}

TEST(credit, annuity_34) {
  Data data{542678.51, 57, 34.157, ANN, Date{11, 6, 2033}};
  testCredit(data, {1104172.78, 542678.51, 561494.27});
}

TEST(credit, annuity_35) {
  Data data{594314.32, 58, 26.441, ANN, Date{2, 3, 2022}};
  testCredit(data, {1060209.81, 594314.32, 465895.49});
}

TEST(credit, annuity_36) {
  Data data{642314.87, 59, 79.548, ANN, Date{5, 4, 2012}};
  testCredit(data, {2560669.04, 642314.87, 1918354.17});
}

TEST(credit, annuity_37) {
  Data data{697431.11, 60, 81.544, ANN, Date{11, 10, 2016}};
  testCredit(data, {2885566.46, 697431.11, 2188135.35});
}

TEST(credit, annuity_38) {
  Data data{764131.15, 61, 84.517, ANN, Date{18, 6, 2154}};
  testCredit(data, {3375016.47, 764131.15, 2610885.32});
}

TEST(credit, annuity_39) {
  Data data{812341.58, 62, 64.115, ANN, Date{6, 11, 2054}};
  testCredit(data, {2784070.78, 812341.58, 1971729.2});
}

TEST(credit, annuity_40) {
  Data data{866471.88, 63, 14.587, ANN, Date{31, 1, 2002}};
  testCredit(data, {1244204.61, 866471.88, 377732.73});
}

TEST(credit, annuity_41) {
  Data data{904131.41, 64, 11.124, ANN, Date{5, 3, 2012}};
  testCredit(data, {1202915.95, 904131.41, 298784.54});
}

TEST(credit, annuity_42) {
  Data data{971121.54, 65, 7.891, ANN, Date{6, 7, 2021}};
  testCredit(data, {1196801.19, 971121.54, 225679.65});
}

TEST(credit, annuity_43) {
  Data data{1000000, 66, 100, ANN, Date{5, 12, 2027}};
  testCredit(data, {5467523.02, 1000000, 4467523.02});
}

TEST(credit, annuity_44) {
  Data data{1087135.54, 67, 51.112, ANN, Date{17, 7, 2041}};
  testCredit(data, {3324244.94, 1087135.54, 2237109.4});
}

TEST(credit, annuity_45) {
  Data data{1175434.15, 68, 14.871, ANN, Date{22, 3, 2141}};
  testCredit(data, {1747477.36, 1175434.15, 572043.21});
}

TEST(credit, annuity_46) {
  Data data{1317981.54, 69, 21.441, ANN, Date{21, 6, 2084}};
  testCredit(data, {2303273.23, 1317981.54, 985291.69});
}

TEST(credit, annuity_47) {
  Data data{1498752.24, 70, 24.749, ANN, Date{27, 1, 2051}};
  testCredit(data, {2842310.65, 1498752.24, 1343558.41});
}

TEST(credit, annuity_48) {
  Data data{1674111.57, 71, 8.244, ANN, Date{5, 5, 2005}};
  testCredit(data, {2121675.22, 1674111.57, 447563.65});
}

TEST(credit, annuity_49) {
  Data data{1847566.39, 72, 14.479, ANN, Date{15, 7, 2029}};
  testCredit(data, {2776653.67, 1847566.39, 929087.28});
}

TEST(credit, annuity_50) {
  Data data{2000000, 73, 22.222, ANN, Date{22, 2, 2222}};
  testCredit(data, {3657198.22, 2000000, 1657198.22});
}

TEST(credit, differentiated_1) {
  Data data{1000, 4, 5, DIF, Date{6, 7, 2021}};
  testCredit(data, {1010.54, 1000, 10.54});
}

TEST(credit, differentiated_2) {
  Data data{800, 12, 3, DIF, Date{22, 2, 2016}};
  testCredit(data, {812.94, 800, 12.94});
}

TEST(credit, differentiated_3) {
  Data data{9862.12, 7, 13.77, DIF, Date{9, 9, 2000}};
  testCredit(data, {10312.98, 9862.12, 450.86});
}

TEST(credit, differentiated_4) {
  Data data{26744.12, 15, 16.111, DIF, Date{12, 3, 2005}};
  testCredit(data, {29627.64, 26744.12, 2883.52});
}

TEST(credit, differentiated_5) {
  Data data{38235.23, 18, 9.725, DIF, Date{24, 4, 2014}};
  testCredit(data, {41182.76, 38235.23, 2947.53});
}

TEST(credit, differentiated_6) {
  Data data{49715.84, 21, 19.875, DIF, Date{21, 7, 2019}};
  testCredit(data, {58799.98, 49715.84, 9084.14});
}

TEST(credit, differentiated_7) {
  Data data{54798.48, 25, 17.121, DIF, Date{16, 1, 2022}};
  testCredit(data, {64943.26, 54798.48, 10144.78});
}

TEST(credit, differentiated_8) {
  Data data{64972.21, 26, 14.875, DIF, Date{28, 2, 2024}};
  testCredit(data, {75815.12, 64972.21, 10842.91});
}

TEST(credit, differentiated_9) {
  Data data{72578.54, 28, 21.254, DIF, Date{8, 11, 2008}};
  testCredit(data, {91187.66, 72578.54, 18609.12});
}

TEST(credit, differentiated_10) {
  Data data{81458.47, 21, 16.789, DIF, Date{12, 12, 2012}};
  testCredit(data, {93983.55, 81458.47, 12525.08});
}

TEST(credit, differentiated_11) {
  Data data{92784.88, 29, 19.987, DIF, Date{25, 11, 2020}};
  testCredit(data, {115930.84, 92784.88, 23145.96});
}

TEST(credit, differentiated_12) {
  Data data{99999.99, 30, 19.999, DIF, Date{9, 9, 2009}};
  testCredit(data, {125811.83, 99999.99, 25811.84});
}

TEST(credit, differentiated_13) {
  Data data{105597.84, 32, 21.847, DIF, Date{4, 10, 2011}};
  testCredit(data, {137325.72, 105597.84, 31727.88});
}

TEST(credit, differentiated_14) {
  Data data{114874.84, 34, 22.221, DIF, Date{8, 8, 2008}};
  testCredit(data, {152085.1, 114874.84, 37210.26});
}

TEST(credit, differentiated_15) {
  Data data{120000, 12, 12, DIF, Date{19, 12, 2023}};
  testCredit(data, {127804.58, 120000, 7804.58});
}

TEST(credit, differentiated_16) {
  Data data{122784.45, 35, 24.876, DIF, Date{11, 12, 1989}};
  testCredit(data, {168592.06, 122784.45, 45807.61});
}

TEST(credit, differentiated_17) {
  Data data{137846.94, 37, 27.182, DIF, Date{25, 2, 1998}};
  testCredit(data, {197040, 137846.94, 59193.06});
}

TEST(credit, differentiated_18) {
  Data data{143975.18, 38, 1.845, DIF, Date{15, 9, 1945}};
  testCredit(data, {148289.28, 143975.18, 4314.1});
}

TEST(credit, differentiated_19) {
  Data data{151879.84, 40, 8.971, DIF, Date{20, 11, 1978}};
  testCredit(data, {175137.6, 151879.84, 23257.76});
}

TEST(credit, differentiated_20) {
  Data data{158797.48, 42, 45.847, DIF, Date{1, 1, 2001}};
  testCredit(data, {289085.83, 158797.48, 130288.35});
}

TEST(credit, differentiated_21) {
  Data data{168848.24, 43, 33.333, DIF, Date{3, 3, 2033}};
  testCredit(data, {272200.89, 168848.24, 103352.65});
}

TEST(credit, differentiated_22) {
  Data data{177548.15, 45, 30.001, DIF, Date{6, 7, 2028}};
  testCredit(data, {279688.78, 177548.15, 102140.63});
}

TEST(credit, differentiated_23) {
  Data data{184999.99, 47, 24.919, DIF, Date{4, 11, 2021}};
  testCredit(data, {277131.45, 184999.99, 92131.46});
}

TEST(credit, differentiated_24) {
  Data data{199999.99, 39, 9.999, DIF, Date{9, 9, 1999}};
  testCredit(data, {233312.06, 199999.99, 33312.07});
}

TEST(credit, differentiated_25) {
  Data data{224875.67, 48, 57.487, DIF, Date{11, 2, 1947}};
  testCredit(data, {488354.28, 224875.67, 263478.61});
}

TEST(credit, differentiated_26) {
  Data data{249723.16, 49, 43.196, DIF, Date{4, 9, 1967}};
  testCredit(data, {474344.46, 249723.16, 224621.3});
}

TEST(credit, differentiated_27) {
  Data data{276314.57, 50, 64.878, DIF, Date{1, 2, 2003}};
  testCredit(data, {656611.77, 276314.57, 380297.2});
}

TEST(credit, differentiated_28) {
  Data data{300000, 51, 68.778, DIF, Date{6, 11, 2048}};
  testCredit(data, {746693.89, 300000, 446693.89});
}

TEST(credit, differentiated_29) {
  Data data{337541.43, 52, 71.381, DIF, Date{9, 5, 2005}};
  testCredit(data, {870241.02, 337541.43, 532699.59});
}

TEST(credit, differentiated_30) {
  Data data{374112.34, 53, 74.164, DIF, Date{11, 12, 2013}};
  testCredit(data, {998288.37, 374112.34, 624176.03});
}

TEST(credit, differentiated_31) {
  Data data{400000, 54, 45.694, DIF, Date{16, 1, 1982}};
  testCredit(data, {818483.57, 400000, 418483.57});
}

TEST(credit, differentiated_32) {
  Data data{442341.55, 55, 26.533, DIF, Date{6, 11, 1987}};
  testCredit(data, {716034.89, 442341.55, 273693.34});
}

TEST(credit, differentiated_33) {
  Data data{485212.25, 56, 44.444, DIF, Date{14, 5, 2045}};
  testCredit(data, {997946.16, 485212.25, 512733.91});
}

TEST(credit, differentiated_34) {
  Data data{542678.51, 57, 34.157, DIF, Date{11, 6, 2033}};
  testCredit(data, {990837.77, 542678.51, 448159.26});
}

TEST(credit, differentiated_35) {
  Data data{594314.32, 58, 26.441, DIF, Date{2, 3, 2022}};
  testCredit(data, {981102.3, 594314.32, 386787.98});
}

TEST(credit, differentiated_36) {
  Data data{642314.87, 59, 79.548, DIF, Date{5, 4, 2012}};
  testCredit(data, {1919478.63, 642314.87, 1277163.76});
}

TEST(credit, differentiated_37) {
  Data data{697431.11, 60, 81.544, DIF, Date{11, 10, 2016}};
  testCredit(data, {2142613.84, 697431.11, 1445182.73});
}

TEST(credit, differentiated_38) {
  Data data{764131.15, 61, 84.517, DIF, Date{18, 6, 2154}};
  testCredit(data, {2433110.7, 764131.15, 1668979.55});
}

TEST(credit, differentiated_39) {
  Data data{812341.58, 62, 64.115, DIF, Date{6, 11, 2054}};
  testCredit(data, {2178758.18, 812341.58, 1366416.6});
}

TEST(credit, differentiated_40) {
  Data data{866471.88, 63, 14.587, DIF, Date{31, 1, 2002}};
  testCredit(data, {1203053.55, 866471.88, 336581.67});
}

TEST(credit, differentiated_41) {
  Data data{904131.41, 64, 11.124, DIF, Date{5, 3, 2012}};
  testCredit(data, {1176608.45, 904131.41, 272477.04});
}

TEST(credit, differentiated_42) {
  Data data{971121.54, 65, 7.891, DIF, Date{6, 7, 2021}};
  testCredit(data, {1182023.94, 971121.54, 210902.4});
}

TEST(credit, differentiated_43) {
  Data data{1000000, 66, 100, DIF, Date{5, 12, 2027}};
  testCredit(data, {3791435.39, 1000000, 2791435.39});
}

TEST(credit, differentiated_44) {
  Data data{1087135.54, 67, 51.112, DIF, Date{17, 7, 2041}};
  testCredit(data, {2662741.49, 1087135.54, 1575605.95});
}

TEST(credit, differentiated_45) {
  Data data{1175434.15, 68, 14.871, DIF, Date{22, 3, 2141}};
  testCredit(data, {1678496.81, 1175434.15, 503062.66});
}

TEST(credit, differentiated_46) {
  Data data{1317981.54, 69, 21.441, DIF, Date{21, 6, 2084}};
  testCredit(data, {2142092.39, 1317981.54, 824110.85});
}

TEST(credit, differentiated_47) {
  Data data{1498752.24, 70, 24.749, DIF, Date{27, 1, 2051}};
  testCredit(data, {2595361.53, 1498752.24, 1096609.29});
}

TEST(credit, differentiated_48) {
  Data data{1674111.57, 71, 8.244, DIF, Date{5, 5, 2005}};
  testCredit(data, {2088511.44, 1674111.57, 414399.87});
}

TEST(credit, differentiated_49) {
  Data data{1847566.39, 72, 14.479, DIF, Date{15, 7, 2029}};
  testCredit(data, {2661800.25, 1847566.39, 814233.86});
}

TEST(credit, differentiated_50) {
  Data data{2000000, 73, 22.222, DIF, Date{22, 2, 2222}};
  testCredit(data, {3368737.81, 2000000, 1368737.81});
}

TEST(credit, diffReduceTerm_1) {
  Data data{120000, 6, 10, DIF, Date{1, 3, 2022}};
  Early early{EarlyType::REDUCE_TERM, 5232, Date{1, 4, 2022}};
  testCredit(data, {123303.99, 120000, 3303.99}, {early});
}