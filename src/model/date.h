#pragma once

#include <string>

namespace biblioteca::model {

/**
 * Uma data simples (ano, mês, dia), sem hora.
 *
 * Substitui o `java.time.LocalDate` do original. A biblioteca padrão do C++17
 * não tem um tipo de calendário pronto, então esta classe existe só para isso:
 * "hoje", "daqui a N dias" e comparar duas datas.
 */
class Date {
public:
    Date(int year, int month, int day);

    static Date today();

    Date plusDays(int days) const;
    Date minusDays(int days) const;

    /** Quantos dias faltam daqui até `other` (negativo se `other` já passou). */
    long daysUntil(const Date& other) const;

    bool operator==(const Date& other) const;
    bool operator<(const Date& other) const;

    int year() const { return year_; }
    int month() const { return month_; }
    int day() const { return day_; }

    /** Formato dd/mm/aaaa. */
    std::string toString() const;

private:
    int year_;
    int month_;
    int day_;
};

} // namespace biblioteca::model
