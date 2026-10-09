# Курсовая работа по компьютерной графике

Интерактивный конструктор планетных систем с трёхмерной визуализацией.

## Структура

```text
CG_coursework_IU7_2028/
├── program/     # Программа
└── report/      # Исходник РПЗ, задание и иллюстрации
```

## Сборка

РПЗ собирается через LaTeX Workshop: `Ctrl+Alt+B`, просмотр PDF — `Ctrl+Alt+V`.
Результат находится в `report/build/rpz.pdf`.

Для программы нужны CMake, компилятор C++20 и Qt6 с компонентами Core, Gui,
Widgets и OpenGLWidgets. Из корня репозитория:

```sh
cmake -S program -B program/build
cmake --build program/build
```