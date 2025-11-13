![Tests](https://github.com/WilliamTuominiemi/planetary-system-simulator/actions/workflows/main.yml/badge.svg)

![demo](demo.gif)

Run program
`g++ -std=c++17 -Isrc src/physics.cpp src/controller.cpp main.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system && ./main`

Run unit tests
`g++ -std=c++17 -Isrc src/physics.cpp src/controller.cpp tests/test_physics.cpp tests/test_controller.cpp -o test_runner -lsfml-graphics -lsfml-window -lsfml-system && ./test_runner`