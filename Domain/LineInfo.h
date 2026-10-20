#pragma once

struct LineInfo {
    int a = 0;                // формула линии: f(t) = a*t^2 + b*t + c
    int b = 0;                // t = 0 это первая клетка линии
    int c = 0;
    int length = 0;           // сколько клеток в линии
    int primeCount = 0;       // сколько из них простые
    double primeShare = 0.0;  // доля простых (от 0 до 1)
    int direction = 0;        // 0 - по строке, 1 - по столбцу, 2 - диагональ вниз-вправо, 3 - диагональ вниз-влево
};