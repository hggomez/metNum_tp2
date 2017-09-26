#ifndef METODOS_TP2_MEASURE_H
#define METODOS_TP2_MEASURE_H

#include <chrono>
#include <iostream>

template<typename TimeT = std::chrono::milliseconds, int repeticiones = 1>
struct measure
{
    template<typename F, typename ...Args>
    static typename TimeT::rep execution(F func, Args&&... args)
    {
        auto start = std::chrono::system_clock::now();

        for (size_t counter = 0; counter < repeticiones; ++counter) {
            std::cerr << "\rRepeticion: " << counter << std::flush;
            func(std::forward<Args>(args)...);
        }
        std::cerr << std::endl;

        auto duration = std::chrono::duration_cast< TimeT>
                                (std::chrono::system_clock::now() - start) / repeticiones;

        return duration.count();
    }
};

#endif //METODOS_TP2_MEASURE_H
