#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <iomanip>

struct Item {
	std::string name;
	double percentage = 0;
};

// Генерирование случайной строки
std::string randomName(int length) {
	std::string name;
	for (int i = 0; i != length; ++i) {
		name += (char)(97 + std::rand() % 26);
	}
	return name;
}

// Заполнение массива псевдослучайными значениями
void fill(std::vector<Item>& array, int n) {
	for (int i = 0; i != n; ++i) {
		array[i].name = randomName(1 + std::rand() % 10);
		array[i].percentage = std::rand() % 1001 * 0.001;
	}
}

bool itemCompare(Item const& lhs, Item const& rhs) {
	return lhs.percentage < rhs.percentage;
}

// Вывод заголовка таблицы
void printHeader(int width, int seed[3]) {
	std::cout << std::setw((width * 5 + 25) / 2) << std::right << "Sorting time, sec" << std::endl;

	std::cout << std::setfill('-') << "+" << std::setw(width) << "" << "+" << 
		std::setw(3 * width + 2) << "" << "+" << std::setw(width) << "" << "+" << std::endl;

	std::cout << std::setfill(' ') << std::left << 
		"|" << std::setw(width) << "" << "|" << std::setw(width * 3 + 2) << "Seed" << 
		"|" << std::setw(width) << "" << "|" << std::endl;

	std::cout << "|" << std::setw(width) << "Data" << "+" <<
		std::setfill('-') << std::setw(width * 3 + 2) << "" << "+" <<
		std::setfill(' ') << std::setw(width) << "Average" << "|" << std::endl;

	std::cout << "|" << std::setw(width) << "Size" << "|" << 
		std::setw(width) << seed[0] << "|" <<
		std::setw(width) << seed[1] << "|" <<
		std::setw(width) << seed[2] << "|" <<
		std::setw(width) << "" << "|" << std::endl;

	std::cout << std::setfill('-') << "+" << 
		std::setw(width) << "" << "+" <<
		std::setw(width) << "" << "+" << std::setw(width) << "" << "+" <<
		std::setw(width) << "" << "+" << std::setw(width) << "" << "+" << std::endl;
}

int main() {
	int seed[3] = { 987, 654, 321 };	// Сиды для ГПСЧ
	const int COLUMN_WIDTH = 9;			// Ширина одной колонки в таблице

	printHeader(COLUMN_WIDTH, seed);

	for (int i = 1; i <= 7; ++i)
	{
		double durSum = 0;				// Суммарное время для вычисления среднего значения
		std::vector<Item> array(5000 * i);
		std::cout << std::setfill(' ') << "|" << std::setw(COLUMN_WIDTH) << 5000 * i << "|";
		for (int j = 0; j != 3; ++j) {
			std::srand(seed[j]);
			fill(array, 5000 * i);

			auto start = std::chrono::high_resolution_clock::now();
			std::sort(array.begin(), array.end(), &itemCompare);
			auto end = std::chrono::high_resolution_clock::now();

			std::chrono::duration<double> dur = end - start;
			durSum += dur.count();
			std::cout << std::fixed << std::setprecision(4) << std::setw(COLUMN_WIDTH) << dur.count() << "|";
		}
		std::cout << std::setw(COLUMN_WIDTH) << durSum / 3 << "|" << std::endl;
	}
	std::cout << std::setfill('-') << "+" <<
		std::setw(COLUMN_WIDTH) << "" << "+" <<
		std::setw(COLUMN_WIDTH) << "" << "+" << std::setw(COLUMN_WIDTH) << "" << "+" <<
		std::setw(COLUMN_WIDTH) << "" << "+" << std::setw(COLUMN_WIDTH) << "" << "+" << std::endl;
}