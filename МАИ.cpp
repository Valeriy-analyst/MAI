// МАИ.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>

void printMatrix(std::vector<std::vector <float>> matrix) {              // Вывод матрицы
    size_t N = matrix.size();
    std::cout << "Матрица:\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << matrix.at(i).at(j) << "\t";
        }
        std::cout << "\n";
    }
}

void printMatrixW(std::vector<float> matrix, size_t N) {                     // Вывод матрицы весов
    for (int i = 0; i < N; ++i) {
        std::cout << matrix.at(i) << "\t";
    }
    std::cout << "\n";
}

void fillMatrixKriteriev(std::vector<std::vector <float>>& matrix) {      // Заполнение матрицы критериев оценками
    std::cout << "Заполните матрицу Критериев Оценками\n";
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j< matrix.at(i).size(); ++j) {
            std::cin >> matrix.at(i).at(j);
            while (matrix.at(i).at(j) <= 0 || matrix.at(i).at(j) > 9) {
                std::cout << "Вы ввели оценку не в соответствии со шкалой Саати\nПо шкале Саати оценка может быть в интервале от 0 до 9\n";
                std::cin >> matrix.at(i).at(j);
            }
        }
    }
}

void fillMatrixAlternative(std::vector<std::vector <float>>& matrix) {    // Заполнение матрицы альтернатив оценками
    std::cout << "Заполните матрицу Альтернатив Оценками\n";
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j< matrix.at(i).size(); ++j) {
            std::cin >> matrix.at(i).at(j);
            while (matrix.at(i).at(j) <= 0 || matrix.at(i).at(j) > 9) {
                std::cout << "Вы ввели оценку не в соответствии со шкалой Саати\nПо шкале Саати оценка может быть в интервале от 0 до 9\n";
                std::cin >> matrix.at(i).at(j);
            }
        }
    }
}

std::vector<float> calculateWeight(std::vector<std::vector <float>> matrix) {// Расчёт вектора весовых коэффициентов
    size_t N = matrix.size();
    std::vector<float> matrixWeight(N);
    float sumGeometry=0;
    for (int i = 0; i < N; ++i) {
        float avgGeometry = 0, mn=1;
        for (int j = 0; j < N; ++j) {
            mn *= matrix.at(i).at(j);
        }
        avgGeometry = pow(mn, static_cast<float>(1) / N);
        sumGeometry += avgGeometry;
    }
    for (int i = 0; i < N; ++i) {
        float avgGeometry = 0, mn = 1;
        for (int j = 0; j < N; ++j) {
            mn *= matrix.at(i).at(j);
        }
        avgGeometry = pow(mn, static_cast<float>(1) / N);
        matrixWeight.at(i) = avgGeometry / sumGeometry;
    }
    printMatrixW(matrixWeight, N);
    return matrixWeight;
}

std::vector<float> calculateAlternativeWeight(std::vector<std::vector <float>> alternativeWeight, std::vector <float> KriterievWeight, int nAlternative) {
    size_t nKriteriev = KriterievWeight.size();                          // Расчёт финального веса Альтернатив
    std::vector<float>totalAlt;
    float bestAlte = 0;
    for (int i = 0; i < nAlternative; ++i) {
        for (int j = 0; j < nKriteriev; ++j) {
            bestAlte += KriterievWeight.at(j) * alternativeWeight.at(j).at(i);
        }
        totalAlt.push_back(bestAlte);
        bestAlte = 0;
    }
    return totalAlt;
}

void bestAlt(std::vector <float> totalAlt) {                              // Расчёт и вывод наилучшей альтернативы
    size_t nAlternative = totalAlt.size();
    float max = 0;
    int counter;
    for (int i = 0; i < nAlternative; ++i) {
        if (max < totalAlt.at(i)) {
            max = totalAlt.at(i);
            counter = i + 1;
        }
    }
    std::cout << "Лучшая альтернатива под номером:" << counter << std::endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    std::cout << "Введите количество альтернатив" << std::endl;
    int nAlternative, nKriteriev;
    std::cin >> nAlternative;
    while (nAlternative < 1 ) {
        std::cout << "Количество альтернатив не может быть меньше единицы\n";
        std::cin >> nAlternative;
    }
    std::cout << "Введите количество критериев" << std::endl;
    std::cin >> nKriteriev;
    while (nKriteriev < 1) {
        std::cout << "Количество Критериев не может быть меньше единицы\n";
        std::cin >> nKriteriev;
    }
    std::vector <std::vector<float>> matrixAlternative(nAlternative, std::vector<float>(nAlternative));
    std::vector <std::vector<float>> matrixKriteriev(nKriteriev, std::vector<float>(nKriteriev));
    fillMatrixKriteriev(matrixKriteriev);
    printMatrix(matrixKriteriev);
    std::vector<float>KriterievWeight=calculateWeight(matrixKriteriev);
    using AlternativeWeight = std::vector<float>;
    std::vector<AlternativeWeight> alternativeWeight;
    for (int i = 0; i < nKriteriev; ++i) {
        fillMatrixAlternative(matrixAlternative);
        alternativeWeight.push_back(calculateWeight(matrixAlternative));
    }
    //printMatrix(alternativeWeight);
    std::vector<float>totalAlt;
    totalAlt = calculateAlternativeWeight(alternativeWeight, KriterievWeight, nAlternative);
    printMatrixW(totalAlt, nAlternative);
    bestAlt(totalAlt);
    char y = 'B';
    while (y != 'Y') {
        std::cout << "Введите 'Y' чтобы закрыть" << std::endl;
        std::cin >> y;
    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
