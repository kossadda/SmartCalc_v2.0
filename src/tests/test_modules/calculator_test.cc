/**
 * @file calculator_test.cc
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-08-16
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../main_test.h"

void testCalculating(const std::string& infix, long double exp,
                     long double precision = 1.0e-7L, long double var = 0.0L) {
  CalculatorModel model{infix, var};

  long double res = model.evaluate();

  EXPECT_TRUE(model.validate()) << "Validation failed";
  EXPECT_NEAR(exp, res, precision)
      << "\nRes : " << res << "\nTrue: " << exp << '\n';
}

TEST(smartcalc, arithmetic_1) {
  std::string infix =
      "(((1.123*213.5555-((217.12354))*1/2)/4/6*(5632.57-123.344)/(23.12346)/"
      "(4.213*(((653.13*(14.123*121.2345+2/(23.123+9*0.213))))/"
      "((237.12*21.8888))/(1.888+92.14)))))";
  testCalculating(infix, 134.97247948L);
}

TEST(smartcalc, arithmetic_2) {
  std::string infix = "((2*3)-(4/2))";
  testCalculating(infix, 4.0L);
}

TEST(smartcalc, arithmetic_3) {
  std::string infix = "324.14*(10+5)/(2*3)";
  testCalculating(infix, 810.35L);
}

TEST(smartcalc, arithmetic_4) {
  std::string infix = "(((1.5*2)/3)-((4-2)*1))";
  testCalculating(infix, -1.0L);
}

TEST(smartcalc, arithmetic_5) {
  std::string infix = "((6/2)+(4*2))";
  testCalculating(infix, 11.0L);
}

TEST(smartcalc, arithmetic_6) {
  std::string infix = "((6/2)+(4*2))";
  testCalculating(infix, 11.0L);
}

TEST(smartcalc, arithmetic_7) {
  std::string infix = "0.04230*(((12/3)*2)-5)";
  testCalculating(infix, 0.1269L);
}

TEST(smartcalc, arithmetic_8) {
  std::string infix = "(((2.5*3)/(1.5-0.5))-((4/2)+1))";
  testCalculating(infix, 4.5L);
}

TEST(smartcalc, arithmetic_9) {
  std::string infix = "((10*(2/5))+((3-1)*(8/2)))";
  testCalculating(infix, 12.0L);
}

TEST(smartcalc, arithmetic_10) {
  std::string infix = "((20/4)(5-(3/1.5)))";
  testCalculating(infix, 15.0L);
}

TEST(smartcalc, arithmetic_11) {
  std::string infix = "(((15*2)/(3+2))-(7*0.5)) - (-2)";
  testCalculating(infix, 4.5L);
}

TEST(smartcalc, arithmetic_12) {
  std::string infix = "-1*((6.213*(2.552-1.312))/(3.321-(2.423/4.1123)))";
  testCalculating(infix, -2.82017077L);
}

TEST(smartcalc, arithmetic_13) {
  std::string infix = "0.09000012*(((18.435/3.432)+2.412)*(4.8324-1.2432))";
  testCalculating(infix, 2.51429291L);
}

TEST(smartcalc, arithmetic_14) {
  std::string infix = "((9.756+(7/2.756))*(4.253-(3.142/1.523)))";
  testCalculating(infix, 26.92763754L);
}

TEST(smartcalc, arithmetic_15) {
  std::string infix = "(((12/2)+(5*1.5))/(3-1))";
  testCalculating(infix, 6.75L);
}

TEST(smartcalc, arithmetic_16) {
  std::string infix =
      "325.5324*(((2.5432*3.432)/(1342.5-10.5324))-((44325.11123/"
      "2324.234)+1.234))/(3.234-((2.7568*1.5234)+0.5324))";
  testCalculating(infix, 4410.72838720L);
}

TEST(smartcalc, arithmetic_17) {
  std::string infix =
      "((10.00032*(223.21/5.214))+((23.53-1.321)*(2123.8/2.5326)))/"
      "(1.3412+(2123.52/(3321.234-1.41142)))";
  testCalculating(infix, 9618.22208480L);
}

TEST(smartcalc, arithmetic_18) {
  std::string infix =
      "((2.2340/43.541)*(5.1325-(3.3214/14.5231)))/((31.22*31.5321)-(141.52/"
      "103.5324))";
  testCalculating(infix, 0.00025593L);
}

TEST(smartcalc, arithmetic_19) {
  std::string infix =
      "(((132.5*232.4)/(34.32+423.2))-(74.32*30.5432))*(432.4/(243.24-14.52))";
  testCalculating(infix, -4164.18755839L);
}

TEST(smartcalc, arithmetic_20) {
  std::string infix =
      "((64.57*(2774.5-165.445))/(353.4678-(276.9354/43.456)))+(57.65-(323.5/"
      "1.3425))";
  testCalculating(infix, 302.04350416L);
}

TEST(smartcalc, arithmetic_21) {
  std::string infix =
      "(((189.67/423.3)+2.34)*(46.34/6.348-1634.2))/((25.343*0.63465)+(54.371/"
      "50543.55))";
  testCalculating(infix, -281.99663138L);
}

TEST(smartcalc, arithmetic_22) {
  std::string infix =
      "235-((953.26+(763.24/432.432))*(45.66-(39.78/1978.995)))-(9792.995/"
      "(9780.5978*2789.5234))";
  testCalculating(infix, -43352.24453277L);
}

TEST(smartcalc, arithmetic_23) {
  std::string infix =
      "634*(((1234.45232/2.2354)+(5123.324*1241.2355))/"
      "(235.553-142.71))+(2346.26*(1423.525/10432.3255))";
  testCalculating(infix, 43429718.64983888L);
}

TEST(smartcalc, arithmetic_24) {
  std::string infix =
      "(((5232.555*3876.8768)/(107.578-0078.0785))-((70784.78/"
      "50782.807)+4321.67))/(13.42-((532.2253*1523.5523)+5230.3255))";
  testCalculating(infix, -0.83734470L);
}

TEST(smartcalc, arithmetic_25) {
  std::string infix =
      "((137610.432*(2234.532/5.643))+((34.23423-521.42365)*(5238.523/"
      "62.325)))/(4571.2345+(252.253/(5233.523-1523.745)))";
  testCalculating(infix, 11911.36244976L);
}

TEST(smartcalc, arithmetic_26) {
  std::string infix =
      "328*(253*(203.41/44.32)*(5.3214-(142.3/1532.5532)))/"
      "((25.23*4231.53254)-(11.2/4350.5325))";
  testCalculating(infix, 18.65233133L);
}

TEST(smartcalc, arithmetic_27) {
  std::string infix =
      "(((1432.22345*532.652)/"
      "(3.324234+423.4322))-(741.4132*0.5432))*(4324.234/(232.1234-1324.325))";
  testCalculating(infix, -5483.00538785L);
}

TEST(smartcalc, arithmetic_28) {
  std::string infix =
      "34*((631543.151*(253154.124-1532.12521))/(3235.124353-(2532.1241/"
      "452.432)))+(535.21354-(32314.123/15342.342))";
  testCalculating(infix, 1672983604.33760846L, 1.0e-6L);
}

TEST(smartcalc, arithmetic_29) {
  std::string infix = "((18235.352/3.5322)+2325/1214.41)*(434.8-321.3252)";
  testCalculating(infix, 586042.77411927L);
}

TEST(smartcalc, arithmetic_30) {
  std::string infix =
      "0.321*((9324.235+(5432.7/3254.662))*(4432.11-(423.143/"
      "1423.3245)))-(25324.5111/(324.5412*213.24))";
  testCalculating(infix, 13267141.74182536L);
}

TEST(smartcalc, arithmetic_31) {
  std::string infix =
      "(((12324.342/2342.234)+(342.4325*154.65))/"
      "(876.3-3451))+(2534.543*(1234.655/320.542))";
  testCalculating(infix, 9741.91379147L);
}

TEST(smartcalc, arithmetic_32) {
  std::string infix =
      "(((((4342.8675*5463)/(4231.4325-0.3245))-((44234.412/582)+1376))/"
      "(3654-((543.2*1345.5543)+0.5543)))*(5326543/(2645.658765-1654)))+(12563/"
      "((3654.576*2564)+(1342.56/23450.5)))";
  testCalculating(infix, -30.68889694L);
}

TEST(smartcalc, arithmetic_33) {
  std::string infix =
      "(((1630*(2234/54325))+((4233-4234321)*(823423/3452)))/(145+(234.2341/"
      "(356.4612-1543.3234))))*((454.3345-(3534.543/4321.5432))-(5432.3524/"
      "(2435*0.532442)))";
  testCalculating(infix, -3131029812.34034567L, 1.0e-6L);
}

TEST(smartcalc, arithmetic_34) {
  std::string infix =
      "(((26340/4634)*(6345-(3643/6341.6345)))/((5672*19786.55324)-(1234/"
      "7560.7565)))*(3423-((2432*13546.3425)+4320.524))";
  testCalculating(infix, -10586.27400295L);
}

TEST(smartcalc, arithmetic_35) {
  std::string infix =
      "324.5342*((((15365*3242)/(3654+2243))-(2347*43210.54435))*(57764/"
      "(243242-7561)))/(1432+(6542/(3654-1423654)))";
  testCalculating(infix, -5632720.32424436L);
}

TEST(smartcalc, arithmetic_36) {
  std::string infix =
      "(((65324*(2654.5645-6541))/(3654234-(2234/4345)))+(5747-(3534/"
      "561.5345)))*(5432-((6541/4230.4325)+(4232*1654.655)))";
  testCalculating(infix, -39682001894.71318113L);
}

TEST(smartcalc, arithmetic_37) {
  std::string infix =
      "((((13428/3432)+76542)*(45432.8243-6341.2634))/((6432*5430.635)+(5431/"
      "5430.5435)))+(3457/(4323*4322))";
  testCalculating(infix, 85.66615852L);
}

TEST(smartcalc, arithmetic_38) {
  std::string infix =
      "(((967575+(744234/2352))*(4765-(3765/13234.5224)))-(4322.4325/"
      "(210423.5*3422)))*((6534.51+(321/(311-11.35423)))/(414.5234-(3.42342/"
      "35421.12355)))";
  testCalculating(infix, 72710793992.85143845L);
}

TEST(smartcalc, arithmetic_39) {
  std::string infix =
      "((((134.52/23421)+(5324.78*1665.5342))/(423.4323-1323))+(236*(51.552354/"
      "0.5324)))/(54536/(14.142-11.4132))";
  testCalculating(infix, 0.65013492L);
}

TEST(smartcalc, arithmetic_40) {
  std::string infix =
      "((((134.52/23421)+(5324.78-1665.5342))/(423.4323-1323))+(236-(51.552354/"
      "0.5324)))/(54536/(14.142-11.4132))";
  testCalculating(infix, 0.00676005L);
}

TEST(smartcalc, trigonometric_1) {
  std::string infix = "sin(((1432.35*24.3)/(34/3+24/43-23))-sin(7324.35*0.5))";
  testCalculating(infix, 0.30830568L);
}

TEST(smartcalc, trigonometric_2) {
  std::string infix = "sin((6.213*(2.552-1.312))/(3.321-(2.423/4.1123)))";
  testCalculating(infix, 0.31591594L);
}

TEST(smartcalc, trigonometric_3) {
  std::string infix =
      "sin(0.09000012*((sin(18.435/3.432)+2.412)*(4.8324-sin(1.2432))))";
  testCalculating(infix, 0.53712999L);
}

TEST(smartcalc, trigonometric_4) {
  std::string infix = "sin(((12/2)+(5*sin(1.5)*24))/(3324.132-1.32523))";
  testCalculating(infix, 0.03782026L);
}

TEST(smartcalc, trigonometric_5) {
  std::string infix =
      "sin(325.5324*(((2.5432*3.432)/(1342.5-10.5324))-sin((44325.11123/"
      "2324.234)+1.234))/(3.234-((2.7568*1.5234)+0.5324)))";
  testCalculating(infix, 0.71414008L);
}

TEST(smartcalc, trigonometric_6) {
  std::string infix =
      "cos(((65324*(2654.5645-6541))/(3654234-(2234/4345)))+(5747-(cos(3534/"
      "561.5345))))*(5432-((6541/4230.4325)+(4232*1654.655)))";
  testCalculating(infix, 6613209.02036235L, 1.0e-5L);
}

TEST(smartcalc, trigonometric_7) {
  std::string infix =
      "cos((((13428/3432)+76542)*(45432.8243-6341.2634))/"
      "((6432*5430.635)+(5431/5430.5435)))+(3457/(4323*4322))";
  testCalculating(infix, -0.66506188L);
}

TEST(smartcalc, trigonometric_8) {
  std::string infix =
      "cos(((96775+(744234/2352))*(4765-(375/13234.5224)))-(4322.4325/"
      "(210423.5*322)))*((654.51+(cos(321/(311-11.35423))))/(414.5234-(3.42342/"
      "351.12355)))";
  testCalculating(infix, -0.70591667L);
}

TEST(smartcalc, trigonometric_9) {
  std::string infix =
      "cos((((134.52/23421)+(5324.78*1665.5342))/"
      "(423.4323-1323))+(236*(cos(51.552354/0.5324))))/(54536/"
      "(14.142-11.4132))";
  testCalculating(infix, 0.00004143L);
}

TEST(smartcalc, trigonometric_10) {
  std::string infix =
      "cos(((26340/4634)*(6345-(3643/6341.6345)))/((5672*19786.55324)-(1234/"
      "7560.7565)))*(3423-((2432*13546.3425)+4320.524))";
  testCalculating(infix, -32945600.78318327L, 1.0e-5L);
}

TEST(smartcalc, trigonometric_11) {
  std::string infix =
      "tan(((sin(45)*cos(30))/2)-(tan(12.34)/(cos(2.55)-1.32)))";
  testCalculating(infix, -0.04151937L);
}

TEST(smartcalc, trigonometric_12) {
  std::string infix = "tan((sin(2.5*cos(30)))-(tan(2.34)*cos(1.23)))";
  testCalculating(infix, 0.87951986L);
}

TEST(smartcalc, trigonometric_13) {
  std::string infix =
      "tan(((sin(0.5)*cos(60))/(cos(45)+tan(30)))-(tan(15.5)/"
      "(cos(12.34)-sin(7.65))))";
  testCalculating(infix, -0.08189528L);
}

TEST(smartcalc, trigonometric_14) {
  std::string infix =
      "tan(((sin(1.5)*cos(75))/cos(0.5))-(tan(45.67)/(cos(2.55)-1.32)))";
  testCalculating(infix, 0.23308907L);
}

TEST(smartcalc, trigonometric_15) {
  std::string infix =
      "tan((sin(23)*cos(11.5))-(tan(34.12)*cos(1.23)))*asin(((6.213*(2.552-1."
      "312))/(3.321-(2.423/4.1123)))/3)*asin(((6.213*(2.552-1.312))/"
      "(3.321-(2.423/4.1123)))/3)";
  testCalculating(infix, -0.38600570L);
}

TEST(smartcalc, trigonometric_16) {
  std::string infix =
      "(((asin(0.54321)*acos(0.3245+321/1284))/acos((45.14123/124766+321/"
      "1545)*41.421/4327.34)+atan(35432.253))-(atan(154.5324)/(acos(142.34/"
      "10327)-asin(7.65/102))))";
  testCalculating(infix, 0.86614354L);
}

TEST(smartcalc, trigonometric_17) {
  std::string infix =
      "acos((asin(acos(0.2141)/123))/54.32)*(acos(0.375)/"
      "acos(0.5))-(atan(43245.67)/(acos(0.432455)-0.0032))";
  testCalculating(infix, 0.37737235L);
}

TEST(smartcalc, trigonometric_18) {
  std::string infix =
      "asin(0.123*(asin(0.999)*acos(0.9995)))+(atan(34.12)*acos(0.4323))";
  testCalculating(infix, 1.73819952L);
}

TEST(smartcalc, trigonometric_19) {
  std::string infix =
      "atan(acos(asin(1.43/1432.35*24.3)/(34/3+24/"
      "43-23))-asin(7324.35*0.00005))";
  testCalculating(infix, 0.87525383L);
}

TEST(smartcalc, trigonometric_20) {
  std::string infix = "asin(((6.213*(2.552-1.312))/(3.321-(2.423/4.1123)))/3)";
  testCalculating(infix, 1.22279719L);
}

TEST(smartcalc, trigonometric_21) {
  std::string infix =
      "asin((0.09000012*((asin(18.435/341.432)+2.412)*(4.8324-asin(1.2432/"
      "123+0.0532))))-1)";
  testCalculating(infix, 0.05848612L);
}

TEST(smartcalc, trigonometric_22) {
  std::string infix =
      "asin(((12/2)+(5*asin(1.5/123*0.00043)*24))/(3324.132-1.32523))";
  testCalculating(infix, 0.00180589L);
}

TEST(smartcalc, trigonometric_23) {
  std::string infix =
      "asin((325.5324*(((2.5432*3.432)/(1342.5-10.5324))-asin((44325.11123/"
      "233324.234)+0.00234))/(3.234-((2.7568*1.5234)+0.5324))/49.13278))";
  testCalculating(infix, 0.97352649L);
}

TEST(smartcalc, trigonometric_24) {
  std::string infix =
      "asin(((((((acos(6524*(264.5645-651)/1236345573.3245)/(365234-(234/"
      "435)))+(5747-(acos(353.4/561.535))))*(5432-((6541/"
      "4230.4325)+(422*164.655))))+atan(45.67*2*52))/(acos(2.55/"
      "100)-0.21332)))/100000/100000)";
  testCalculating(infix, -0.02763627L);
}

TEST(smartcalc, trigonometric_25) {
  std::string infix =
      "asin((((13428/3432)+76542)*(acos((45432.8243-6341.2634)/3274652.3214))/"
      "((6432*5430.635)+(5431/5430.5435)))+(3457/(4323*4322)))";
  testCalculating(infix, 0.00360114L);
}

TEST(smartcalc, trigonometric_26) {
  std::string infix = "sin(2*(cos(1.5*atan(0.75))))";
  testCalculating(infix, 0.90797254L);
}

TEST(smartcalc, trigonometric_27) {
  std::string infix =
      "tan((sin(0.5)*cos(1.5))-(tan(1.2)*cos(0.8)))*asin(0.2*((0.2*(1.5-0.8))/"
      "(3-(2/4)))/3)*asin(0.2*((2*(1.5-0.8))/(3-(2/4)))/3)";
  testCalculating(infix, 0.00073548L);
}

TEST(smartcalc, trigonometric_28) {
  std::string infix =
      "acos((asin(acos(0.5)/123))/54.32)*(acos(0.375)/"
      "acos(0.5))-(atan(0.4324567)/(acos(0.432455)-0.0032))";
  testCalculating(infix, 1.41510909L);
}

TEST(smartcalc, trigonometric_29) {
  std::string infix =
      "asin(0.123*(asin(0.999)*acos(0.9995)))+(atan(453341.2)*acos(0.4323))";
  testCalculating(infix, 1.77112297L);
}

TEST(smartcalc, trigonometric_30) {
  std::string infix =
      "atan(acos(asin(1.43/1432.35*24.3)/(34/3+24/"
      "43-23))-asin(7324.35*0.00005))";
  testCalculating(infix, 0.87525383L);
}

TEST(smartcalc, combinated_1) {
  std::string infix =
      "sqrt((sqrt(5233332.555)*sqrt(3876.8768))/"
      "(sqrt(107.578-0078.0785))-(sqrt((70784.78/50782.807)+sqrt(4321.67)))/"
      "(sqrt(13433.42)-((532.2253*sqrt(1523.5523))+5230.3255)))";
  testCalculating(infix, 161.94271729L);
}

TEST(smartcalc, combinated_2) {
  std::string infix =
      "ln(sqrt((log((sqrt(5233332.555)*log(3876.8768))/"
      "(log(107.578-0078.0785))-(log((70784.78/(50782.807-ln(123.432)/"
      "ln(4762.213))+ln(4321.67)))/"
      "(ln(13433.42)-((532.2253*sqrt(1523.5523))+5230.3255)))*123456.12346))))";
  testCalculating(infix, 0.66053149L);
}

TEST(smartcalc, combinated_3) {
  std::string infix =
      "(log(3654234)-sqrt(4345)*log(2234)*65324*(ln(2654.5645)-ln(6541))+(5747-"
      "log(561.5345)/ln(3534)))/(5432-(sqrt(4230.4325)/"
      "sin(log(6541)+log(10)-4232*ln(1654.655))))";
  testCalculating(infix, 2347.50964106L);
}

TEST(smartcalc, combinated_4) {
  std::string infix = "14.36/463.32*(1.326/50-34+20/2)^2^2-2^(2)^(2)";
  testCalculating(infix, 10221.58960857L);
}

TEST(smartcalc, combinated_5) {
  std::string infix = "234.213 mod 35.4+57-56*(3-754 mod 33.51) mod 2";
  testCalculating(infix, 78.493L);
}

TEST(smartcalc, combinated_6) {
  std::string infix = "56*(3+754 mod 33.51) mod 2.5421 mod 2+2";
  testCalculating(infix, 3.8665L);
}

TEST(smartcalc, combinated_7) {
  std::string infix =
      "((asin(log((ln((6(((((((((((((5-6)*5)*3)*2)*5)*4)/2.421)/"
      "432)*324.12)*31.23)/4.123)+213.4325)-834.324))^2 mod 4))^6)))^5) mod "
      "0.023";
  testCalculating(infix, 0.00889416L);
}

TEST(smartcalc, combinated_8) {
  std::string infix = "(5*(-6)^3*sin(-241.1324)/213.4321*(-2))*(-5)";
  testCalculating(infix, 35.23404963L);
}

TEST(smartcalc, combinated_9) {
  std::string infix =
      "(-324.5342*((((15365*(-3242))/"
      "(3654+2243))-(-2347*(-43210.54435)))*(57764/(243242-7561)))/"
      "(-1432+(6542/(3654-1423654))))";
  testCalculating(infix, -5633622.49229791L);
}

TEST(smartcalc, combinated_10) {
  std::string infix =
      "(((-65324*(2654.5645-6541))/(3654234-(-2234/4345)))+(-5747-(-3534/"
      "561.5345)))*(5432-((-6541/4230.4325)+(-4232*1654.655)))";
  testCalculating(infix, -39743614292.13980964L);
}

TEST(smartcalc, combinated_11) {
  std::string infix =
      "((((-13428/3432)+(-76542))*(45432.8243-6341.2634))/"
      "((-6432*(-5430.635))+(-5431/(-5430.5435))))+(-3457/(4323*4322))";
  testCalculating(infix, -85.66615852L);
}

TEST(smartcalc, combinated_12) {
  std::string infix =
      "(((-967575+(-744234/2352))*(4765-(-3765/13234.5224)))-(-4322.4325/"
      "(210423.5*3422)))*((-6534.51+(321/(311-(-11.35423))))/"
      "(-414.5234-(-3.42342/35421.12355)))";
  testCalculating(infix, -72696476962.15221077L);
}

TEST(smartcalc, combinated_13) {
  std::string infix =
      "(((-134.52/23421)+(-5324.78*1665.5342))/"
      "(-423.4323-1323)+(-236*(51.552354/0.5324)))/(-54536/(-14.142-11.4132))";
  testCalculating(infix, -8.32867356L);
}

TEST(smartcalc, combinated_14) {
  std::string infix =
      "sin(-325.5324*(((2.5432*3.432)/(-1342.5+10.5324))-sin((-44325.11123/"
      "2324.234)-1.234))/(3.234-((-2.7568*1.5234)-0.5324)))";
  testCalculating(infix, -0.49350345L);
}

TEST(smartcalc, combinated_15) {
  std::string infix =
      "cos(((-65324*(2654.5645-6541))/(-3654234-(-2234/"
      "4345)))+(-5747-(cos(-3534/561.5345))))*(-5432-((-6541/"
      "4230.4325)-(-4232*1654.655)))";
  testCalculating(infix, -5104898.25816558L, 1.0e-5);
}

TEST(smartcalc, combinated_16) {
  std::string infix =
      "cos((((-13428/3432)-76542)*(45432.8243-6341.2634))/"
      "((-6432*(-5430.635))-(-5431/(-5430.5435))))+(-3457/(4323*4322))";
  testCalculating(infix, -0.66542827L);
}

TEST(smartcalc, combinated_17) {
  std::string infix =
      "cos(((-9675+(-7424/2352))*(4765-(-3765/13234.5224)))-(-4322.4325/"
      "(2042.5*3422)))*((6534.51+(cos(-321/(311-11.35423))))/"
      "(-414.5234-(-3.42342/3541.12355)))";
  testCalculating(infix, 5.93937361L);
}

TEST(smartcalc, combinated_18) {
  std::string infix =
      "cos(((-134.52/23421)+(-5324.78*1665.5342))/"
      "(-423.4323-1323))+(236*(cos(-51.552354/0.5324)))/(54536/"
      "(-14.142-11.4132))";
  testCalculating(infix, 0.34943122L);
}

TEST(smartcalc, combinated_19) {
  std::string infix =
      "sqrt(ln(asin(-0.15)/((sin(-52.11))^2^2/264.324)-26.432(-41.4723/"
      "(123.348/sqrt(45.354)))))";
  testCalculating(infix, 1.61395184L);
}

TEST(smartcalc, combinated_20) {
  std::string infix = "sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(2^2))^2)^2)^2)^2^2)";
  testCalculating(infix, 2.0L);
}

TEST(smartcalc, combinated_21) {
  std::string infix =
      "sin(cos(tan(atan(acos(asin(0.02*sqrt(2.56)/"
      "(ln(1.5)-log(4.321)))+0.14159)/sqrt(5.432)))))";
  testCalculating(infix, 0.70463403L);
}

TEST(smartcalc, combinated_22) {
  std::string infix =
      "ln((cos(1.2*atan(0.75)))/"
      "(log(5.4321*sqrt(3.14159))))+log((tan(0.5)-asin(0.25))/"
      "(ln(2.5)+sqrt(3.14)))";
  testCalculating(infix, -1.27864300L);
}

TEST(smartcalc, combinated_23) {
  std::string infix =
      "sqrt(1 + (cos(2.5) + sin(1.2))^2/(ln(0.5) + log(2.3))^2)";
  testCalculating(infix, 1.07516921L);
}

TEST(smartcalc, combinated_24) {
  std::string infix =
      "sin(2*(cos(1.5*atan(0.75)))*log(1+ln(2.5))/(sqrt(2.5)+log(3.14)))";
  testCalculating(infix, 0.15412291L);
}

TEST(smartcalc, combinated_25) {
  std::string infix =
      "ln(log(2.5)*cos(0.5)/(sin(1.2) + tan(0.75))) - "
      "sqrt(ln(-2.5*log(0.75)/ln(1.2)))";
  testCalculating(infix, -2.40828557L);
}

TEST(smartcalc, combinated_26) {
  std::string infix =
      "0.543(ln(cos(1.5*atan(0.75)) + log(5.4321*sqrt(3.14159))))";
  testCalculating(infix, 0.23893583L);
}

TEST(smartcalc, combinated_27) {
  std::string infix =
      "523(sin(2*(cos(1.5*atan(0.75)))*log(1+ln(2.5))/(sqrt(2.5)+log(3.14))))";
  testCalculating(infix, 80.60628465L);
}

TEST(smartcalc, combinated_28) {
  std::string infix =
      "342(acos((asin(acos(0.5)/123))/54.32)*(acos(0.375)/"
      "acos(0.5))-(atan(43245.67)/(acos(0.432455)-0.0032)))";
  testCalculating(infix, 129.07919834L);
}

TEST(smartcalc, combinated_29) {
  std::string infix =
      "6(((ln(cos(1.5*atan(0.75)))/"
      "(log(5.4321*sqrt(3.14159))))+log((tan(0.5)-asin(0.25))/"
      "(ln(2.5)+sqrt(3.14)))))";
  testCalculating(infix, -9.20773786L);
}

TEST(smartcalc, combinated_30) {
  std::string infix =
      "5.345 mod 7/(sqrt(1 + (cos(2.5) + sin(1.2))^2/(ln(0.5) + log(2.3))^2))";
  testCalculating(infix, 4.97131049L);
}

TEST(smartcalc, combinated_31) {
  std::string infix = "sqrt(sin(P/2.1324) + cos(3.123P))/2.53";
  testCalculating(infix, 0.10381191L);
}

TEST(smartcalc, combinated_32) {
  std::string infix = "log(2.5e-3) * ln(1000) / P";
  testCalculating(infix, -5.72142719L);
}

TEST(smartcalc, combinated_33) {
  std::string infix = "sqrt(2.234*P^2) + log(34e4) - ln(134e-5)";
  testCalculating(infix, 16.84216850L);
}

TEST(smartcalc, combinated_34) {
  std::string infix = "(2/45*5432e3 * (P/3.14)) + log(123e3 * 123 e-4)";
  testCalculating(infix, 241547.85488877L);
}

TEST(smartcalc, combinated_35) {
  std::string infix = "(1+P*P*P-P^3)^3 -1";
  testCalculating(infix, 0.0L);
}

TEST(smartcalc, combinated_36) {
  std::string infix =
      "x(((ln(cos(1.5*atan(1)))/(log(x*sqrt(x))))+log((tan(1)-asin(0.25))/"
      "(ln(x)+sqrt(x)))))";
  testCalculating(infix, -65.10591506L, 1.0e-7L, 50.0L);
}

TEST(smartcalc, combinated_37) {
  std::string infix = "sqrt(x*x*x*x*x*x)x";
  testCalculating(infix, 5.19885601L, 1.0e-7L, 1.51L);
}

TEST(smartcalc, combinated_38) {
  std::string infix = "log(((sqrt(x*x*x*x*x*x)x)^2/1.25566*15.2333)/x^2)";
  testCalculating(infix, 7.79212070L, 1.0e-7L, -13.123L);
}

TEST(smartcalc, combinated_39) {
  std::string infix =
      "log(((sqrt(sqrt(x*x*x*x*x*x)x)/(ln(42)*5.123))^2/1.25566*15.2333)/x^2)";
  testCalculating(infix, 1.25113394L, 1.0e-7L, 23.213L);
}

TEST(smartcalc, combinated_40) {
  std::string infix =
      "e * e "
      "-(log(3654234)-sqrt(4345)*log(2234)*65324*(ln(2654.5645)-ln(6541))+("
      "5747-log(561.5345)/ln(3534)))/(5432-(sqrt(4230.4325)/"
      "sin(log(6541)+log(10)-4232*ln(1654.655))))";

  testCalculating(infix, -2340.12058496L);
}
