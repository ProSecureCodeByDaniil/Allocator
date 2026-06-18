#ifndef PATTERNSTRATEGY_H
#define PATTERNSTRATEGY_H

#include "BBV.h"
#include "boolinterval.h"
#include <vector>
#include <algorithm>

// <-- добавляем: интерфейс стратегии (паттерн "Стратегия")
// Позволяет подменять алгоритм выбора переменной для ветвления
class PatternStrategy
{
public:
    virtual ~PatternStrategy() = default;

    // Выбор индекса переменной для ветвления
    // cnf - массив интервалов (дизъюнктов)
    // cnfSize - размер КНФ
    // mask - маска зафиксированных переменных (1 - уже назначена)
    virtual int chooseVariable(BoolInterval **cnf, int cnfSize, const BBV &mask) = 0;
};

// <-- добавляем: стратегия 1 - оригинальная (MinDefended)
// Выбирает переменную с минимальным количеством определённых значений
class MinDefendedStrategy : public PatternStrategy
{
public:
    int chooseVariable(BoolInterval **cnf, int cnfSize, const BBV &mask) override;
};

// <-- добавляем: стратегия 2 - максимальная частота вхождения
// Выбирает переменную, которая встречается в наибольшем количестве активных дизъюнктов
class MaxOccurrenceStrategy : public PatternStrategy
{
public:
    int chooseVariable(BoolInterval **cnf, int cnfSize, const BBV &mask) override;
};

#endif // PATTERNSTRATEGY_H
