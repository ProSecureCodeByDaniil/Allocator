#include "PatternStrategy.h"


// <-- добавляем: реализация MinDefendedStrategy (оригинальная логика)
// Учитываем const-корректность: используем mask.getSize() и mask[i]
int MinDefendedStrategy::chooseVariable(BoolInterval **cnf, int cnfSize, const BBV &mask)
{
    std::vector<int> indexes;
    std::vector<int> definedCount;

    // Собираем незафиксированные переменные
    // Используем const_cast для вызова getSize() и operator[] у const BBV
    // В оригинальном BBV методы getSize() и operator[] не помечены const,
    // поэтому используем const_cast для обхода ограничения
    BBV& mutableMask = const_cast<BBV&>(mask);

    for (int i = 0; i < mutableMask.getSize(); i++) {
        if (mutableMask[i] == 0) {
            indexes.push_back(i);
            definedCount.push_back(0);
        }
    }

    if (indexes.empty()) return -1;

    // Подсчитываем для каждой переменной количество определённых значений
    for (int i = 0; i < cnfSize; i++) {
        if (cnf[i] == nullptr) continue;
        for (size_t k = 0; k < indexes.size(); k++) {
            if (cnf[i]->getValue(indexes[k]) != '-') {
                definedCount[k]++;
            }
        }
    }

    // Выбираем переменную с минимальным количеством определённых значений
    int minIdx = std::min_element(definedCount.begin(), definedCount.end()) - definedCount.begin();
    return indexes[minIdx];
}
