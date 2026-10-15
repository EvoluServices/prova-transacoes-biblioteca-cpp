#include "model/date.h"

#include <cmath>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <tuple>

namespace biblioteca::model {

namespace {

// Meio-dia evita que um ajuste de horário de verão empurre a data para o dia
// vizinho ao converter de volta para ano/mês/dia.
constexpr int kNoonHour = 12;

std::time_t toTimeT(int year, int month, int day) {
    std::tm tm{};
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    tm.tm_hour = kNoonHour;
    return std::mktime(&tm);
}

} // namespace

Date::Date(int year, int month, int day) : year_(year), month_(month), day_(day) {
}

Date Date::today() {
    std::time_t now = std::time(nullptr);
    std::tm local = *std::localtime(&now);
    return Date(local.tm_year + 1900, local.tm_mon + 1, local.tm_mday);
}

Date Date::plusDays(int days) const {
    std::time_t base = toTimeT(year_, month_, day_);
    std::time_t shifted = base + static_cast<std::time_t>(days) * 86400;
    std::tm local = *std::localtime(&shifted);
    return Date(local.tm_year + 1900, local.tm_mon + 1, local.tm_mday);
}

Date Date::minusDays(int days) const {
    return plusDays(-days);
}

long Date::daysUntil(const Date& other) const {
    std::time_t from = toTimeT(year_, month_, day_);
    std::time_t to = toTimeT(other.year_, other.month_, other.day_);
    double seconds = std::difftime(to, from);
    return std::lround(seconds / 86400.0);
}

bool Date::operator==(const Date& other) const {
    return year_ == other.year_ && month_ == other.month_ && day_ == other.day_;
}

bool Date::operator<(const Date& other) const {
    return std::tie(year_, month_, day_) < std::tie(other.year_, other.month_, other.day_);
}

std::string Date::toString() const {
    std::ostringstream out;
    out << std::setfill('0') << std::setw(2) << day_ << "/"
        << std::setfill('0') << std::setw(2) << month_ << "/"
        << year_;
    return out.str();
}

} // namespace biblioteca::model
