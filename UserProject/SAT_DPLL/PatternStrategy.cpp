#include "PatternStrategy.h"

// <-- добавляем: реализация MinDefendedStrategy (пересмотренное оригинальное решение из UserProject)
// Оригинальная логика из BoolEquation::ChooseColForBranching():
// - values инициализируются: 1 для '-', 0 для определённых значений
// - выбирается переменная с МИНИМАЛЬНЫМ values (т.е. с МАКСИМУМОМ '-')
int MinDefendedStrategy::chooseVariable(BoolInterval **cnf, int cnfSize, const BBV &mask)
{
    std::vector<int> indexes;
    std::vector<int> values;
    bool rezInit = false;

    // Используем const_cast для вызова getSize() и operator[] у const BBV
    BBV& mutableMask = const_cast<BBV&>(mask);

    // Собираем индексы незафиксированных переменных (mask[i] == 0)
    for (int i = 0; i < mutableMask.getSize(); i++) {
        if (mutableMask[i] == 0) {
            indexes.push_back(i);
        }
    }

    if (indexes.empty()) return -1;

    // Оригинальная логика подсчёта values
    for (int i = 0; i < cnfSize; i++) {
        BoolInterval *interval = cnf[i];

        if (interval != nullptr) {
            if (!rezInit) {
                // Первый проход: инициализируем values
                for (size_t k = 0; k < indexes.size(); k++) {
                    if (interval->getValue(indexes.at(k)) == '-') {
                        values.push_back(1);   // <-- как в оригинале: 1 для '-'
                    } else {
                        values.push_back(0);   // <-- как в оригинале: 0 для определённых
                    }
                }
                rezInit = true;
            } else {
                // Последующие проходы: увеличиваем счётчик для '-'
                for (size_t k = 0; k < indexes.size(); k++) {
                    if (interval->getValue(indexes.at(k)) == '-') {
                        values.at(k)++;
                    }
                }
            }
        }
    }

    // Выбираем переменную с МИНИМАЛЬНЫМ values (как в оригинале)
    int minElementIndex = std::min_element(values.begin(), values.end()) - values.begin();
    return indexes.at(minElementIndex);
}
