#include "buffer.h"
#include <cassert>
#include <iostream>

constexpr int size{10};

int main(void)
{
    int value{0};
    using bf_type = std::remove_reference<decltype(value)>::type;
    Buffer<bf_type, size> bff;

    assert(0 == bff.available());

    for (size_t i = 1; i <= size; i++)
    {
        bff.enqueue(i * 10);
        assert(i == bff.available());
        std::cout << bff << std::endl;
    }

    std::cout << std::endl;
    assert(bff.is_full());
    std::cout << "average = " << bff.average() << std::endl;

    for (size_t i = 1; i <= size; i++)
    {
        bff.enqueue(i * 100);
        assert(size == bff.available());
        std::cout << bff << std::endl;
    }

    std::cout << std::endl;
    std::cout << "average = " << bff.average() << std::endl;

    bff.enqueue(5000);
    while (bff.available() != 0)
    {
        value = bff.dequeue();
    }
    assert(0 == bff.available());

    std::cout << "average = " << bff.average() << std::endl;

    return 0;
}