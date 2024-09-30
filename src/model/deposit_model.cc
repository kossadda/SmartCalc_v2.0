/**
 * @file deposit_model.cc
 * @author kossadda (https://github.com/kossadda)
 * @brief Implementation of the DepositModel class.
 * @version 1.0
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "include/model/deposit_model.h"

namespace s21 {

/// @brief Constructs a DepositModel object.
DepositModel::DepositModel() : BaseModel{}, data_{new Data}, tax_{new Tax} {}

/// @brief Destructs the DepositModel object.
DepositModel::~DepositModel() {
  delete data_->base;
  delete data_;
  delete tax_;
}

/**
 * @brief Constructs an Operation object with the given parameters.
 * @param sum_ The sum of the operation.
 * @param type_ The type of the operation.
 * @param date_ The date of the operation.
 */
DepositModel::Operation::Operation(long double sum_, OperationType type_,
                                   const Date &date_)
    : sum{sum_}, type{type_}, date{date_} {}

/**
 * @brief Constructs a Data object with the given parameters.
 * @param amount_ The amount of the deposit.
 * @param term_ The term of the deposit.
 * @param term_type_ The type of the term (years, months, days).
 * @param rate_ The interest rate.
 * @param tax_rate_ The tax rate.
 * @param type_ The type of the deposit.
 * @param freq_ The frequency of interest accrual.
 * @param date_ The start date of the deposit.
 * @param ops_ The list of operations.
 */
DepositModel::Data::Data(long double amount_, long double term_,
                         TermType term_type_, long double rate_,
                         long double tax_rate_, Type type_, Frequency freq_,
                         const Date &date_, std::vector<Operation> *ops_)
    : base{new BaseModel::Data{amount_, term_, term_type_, rate_, type_,
                               date_}},
      freq{freq_},
      tax_rate{tax_rate_} {
  if (ops_) {
    ops = *ops_;
  }
}

/**
 * @brief Adds data to the deposit model.
 * @param data The data to add.
 */
void DepositModel::addData(const Data &data) noexcept {
  *tax_ = Tax{};
  data_->base = data.base;
  data_->freq = data.freq;
  data_->tax_rate = data.tax_rate;
  data_->ops = data.ops;
  tax_->nontaxable *= data_->tax_rate;
  BaseModel::data_ = data_->base;
  BaseModel::data_->rate /= 100.0L;
}

/**
 * @brief Adds an operation to the deposit model.
 * @param op The operation to add.
 */
void DepositModel::addOperation(const Operation &op) noexcept {
  data_->ops.push_back(op);
}

/// @brief Clears the table of payments and operations.
void DepositModel::clear() noexcept {
  table_.clear();
  tax_table_.clear();
  data_->ops.clear();
}

/// @brief Calculates the payments for the deposit model.
void DepositModel::calculatePayments() noexcept {
  month_->current = BaseModel::data_->date;
  month_->payment_date = BaseModel::data_->date;
  month_->balance = BaseModel::data_->amount;
  Date last_day{lastDepositDay()};
  sortOperations();

  while (month_->current != last_day) {
    addPeriod(last_day);

    calculateOperations();

    calculatePeriod();

    calculateTaxes(last_day);

    month_->current = month_->payment_date;
    monthToTable();
  }
}

/**
 * @brief Calculates the last day of the deposit.
 * @return The last day of the deposit.
 */
Date DepositModel::lastDepositDay() const noexcept {
  Date last_day{month_->current};
  Date::DateSize init_day{month_->current.day()};

  if (BaseModel::data_->term_type == TermType::DAYS) {
    last_day.addDays(BaseModel::data_->term);
  } else {
    std::size_t term = BaseModel::data_->term;

    if (BaseModel::data_->term_type == TermType::YEARS) {
      term *= Date::kYearMonths;
    }

    for (std::size_t i{}; i < term; ++i) {
      last_day.addCreditMonth(init_day);
    }
  }

  return last_day;
}

/**
 * @brief Adds a period to the deposit model.
 * @param last_day The last day of the deposit.
 */
void DepositModel::addPeriod(const Date &last_day) noexcept {
  std::size_t period{static_cast<std::size_t>(data_->freq)};

  if (data_->freq == Frequency::ENDTERM) {
    month_->payment_date = last_day;
  } else if (data_->freq == Frequency::DAY) {
    month_->payment_date.addDays(1);
  } else if (data_->freq == Frequency::WEEK) {
    month_->payment_date.addDays(7);
  } else {
    month_->payment_date.addDepositMonth(period);
  }

  if (month_->payment_date > last_day) {
    month_->payment_date = last_day;
  }
}

/// @brief Calculates the period for the deposit model.
void DepositModel::calculatePeriod() noexcept {
  month_->percent = roundVal(formula(month_->current, month_->payment_date) +
                             data_->ops_percent);

  if (BaseModel::data_->type == Type::FIRST) {
    month_->summary = 0.0L;
    month_->main = month_->percent;
  } else {
    month_->summary = month_->percent;
    month_->main = 0.0L;
    month_->balance += roundVal(month_->percent);
  }
}

/**
 * @brief Calculates the taxes for the deposit model.
 * @param last_day The last day of the deposit.
 */
void DepositModel::calculateTaxes(const Date &last_day) {
  tax_->total_profit_ += month_->percent;

  if (month_->current.year() != month_->payment_date.year() ||
      month_->payment_date == last_day) {
    if (month_->payment_date == last_day) {
      tax_->income += month_->percent;
      tax_->year = last_day.year();
    } else {
      tax_->year = month_->current.year();
    }

    if (tax_->income > tax_->nontaxable) {
      tax_->income_deduction = tax_->income - tax_->nontaxable;
      tax_->tax_amount = roundVal(tax_->income_deduction * kNDFLRate);
      tax_->total_tax_ += tax_->tax_amount;
    }

    taxToTable();

    tax_->income = 0.0L;
    tax_->income_deduction = 0.0L;
  }

  if (month_->payment_date != last_day) {
    tax_->income += month_->percent;
  } else {
    tax_->income -= month_->percent;
  }
}

/// @brief Calculates the operations for the deposit model.
void DepositModel::calculateOperations() {
  data_->ops_percent = 0.0L;

  if (!data_->ops.size()) {
    return;
  }

  auto op = data_->ops.begin();
  Date payment_date{month_->payment_date};

  while (data_->ops.size() && op->date >= month_->current &&
         op->date < month_->payment_date) {
    if (op->type == OperationType::WITHDRAWAL &&
        (month_->balance < op->sum || month_->balance - op->sum < 0)) {
      data_->ops.erase(data_->ops.begin());
      continue;
    } else {
      if (op->type == OperationType::REFILL) {
        month_->summary = op->sum;
      } else {
        month_->summary = -op->sum;
      }
    }

    data_->ops_percent += formula(month_->current, op->date);

    month_->current = op->date;
    month_->balance += month_->summary;
    month_->main = 0.0L;
    month_->percent = 0.0L;
    monthToTable();

    data_->ops.erase(data_->ops.begin());
    if (data_->ops.size()) {
      op = data_->ops.begin();
    } else {
      break;
    }
  }
}

/// @brief Adds the tax data to the table.
void DepositModel::taxToTable() noexcept {
  std::vector<std::string> str_year;

  str_year.emplace_back(std::to_string(tax_->year));
  str_year.emplace_back(toStr(tax_->income));
  str_year.emplace_back(toStr(tax_->nontaxable));
  str_year.emplace_back(toStr(tax_->income_deduction));
  str_year.emplace_back(toStr(tax_->tax_amount));
  str_year.emplace_back("Pay by 01.12." + std::to_string(tax_->year + 1));

  tax_table_.emplace_back(str_year);
}

/// @brief Sorts the operations by date.
void DepositModel::sortOperations() {
  Operation temp;
  for (std::size_t i{}; i < data_->ops.size(); ++i) {
    for (std::size_t j{}; j < data_->ops.size() - i - 1; ++j) {
      if (data_->ops[j + 1].date < data_->ops[j].date) {
        temp = data_->ops[j];
        data_->ops[j] = data_->ops[j + 1];
        data_->ops[j + 1] = temp;
      }
    }
  }

  while (data_->ops.size() && data_->ops[0].date < BaseModel::data_->date) {
    data_->ops.erase(data_->ops.begin());
  }
}

/**
 * @brief Returns the total table of payments.
 * @return The total table of payments.
 */
std::vector<std::string> DepositModel::totalTable() const noexcept {
  std::vector<std::string> total_str;
  auto eff_rate{
      toStr(tax_->total_profit_ / BaseModel::data_->amount * Date::kYearDays /
            (month_->payment_date - BaseModel::data_->date) * 100.0L)};
  auto tbalance{toStr((BaseModel::data_->type == Type::SECOND)
                          ? month_->balance
                          : BaseModel::data_->amount + tax_->total_profit_)};
  auto tax_prof{toStr(tax_->total_profit_ - tax_->total_tax_)};
  auto tprofit{toStr(tax_->total_profit_)};
  auto ttax{toStr(tax_->total_tax_)};
  auto balance{toStr(month_->balance)};

  total_str.emplace_back(std::string("Profit\n") + tprofit);
  total_str.emplace_back(std::string("Total tax\n") + ttax);
  total_str.emplace_back(std::string("Profit with tax\n") + tax_prof);
  total_str.emplace_back(std::string("Effective rate\n") + eff_rate);
  total_str.emplace_back(std::string("Total balance\n") + tbalance);
  total_str.emplace_back(std::string("Balance\n") + balance);

  return total_str;
}

/**
 * @brief Returns the table of tax data.
 * @return The table of tax data.
 */
const std::vector<std::vector<std::string>> &DepositModel::taxTable()
    const noexcept {
  return tax_table_;
}

}  // namespace s21
