#ifndef BOOLEQUATION_H
#define BOOLEQUATION_H

#include "boolinterval.h"
#include "Allocator.h"   // <-- добавляем: подключаем аллокатор
#include "PatternStrategy.h"  // <-- добавляем: для использования стратегии

class BoolEquation
{
#ifdef USE_ALLOCATOR
    DECLARE_ALLOCATOR   // <-- добавляем: аллокатор для класса BoolEquation (только если включён)
#endif
public:
	BoolInterval **cnf;//множество интервалов
	BoolInterval *root;//Корень уравнения
	int cnfSize; // Размер КНФ
	int count; //количество дизъюнкций
	BBV mask; //маска для столбцов
    PatternStrategy* strategy;   // <-- добавляем: указатель на стратегию (паттерн "Стратегия")
	BoolEquation(BoolInterval **cnf, BoolInterval *root, int cnfSize, int count, BBV mask);
	BoolEquation(BoolEquation &equation);
    void setStrategy(PatternStrategy* s) { strategy = s; }   // <-- добавляем: метод для установки стратегии
	int CheckRules();
	bool Rule1Row1(BoolInterval *interval);
	bool Rule2RowNull(BoolInterval *interval);
	void Rule3ColNull(BBV vector);
	bool Rule4Col0(BBV vector);
	bool Rule5Col1(BBV vector);
	void Simplify(int ixCol, char value);
	int ChooseColForBranching();
};

#endif // BOOLEQUATION_H
