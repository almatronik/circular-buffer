#ifndef BUFFER_H
#define BUFFER_H

#include <iostream>
#include <cstddef>

template <typename T, size_t SIZE>
class Buffer
{
    T buffer[SIZE]{0};
    size_t front{0};
    size_t back{0};
    size_t elements{0};

public:
    Buffer() { static_assert(SIZE > 3, "The size shall be > 3"); }

    Buffer(const Buffer &) = delete;
    Buffer &operator=(const Buffer &) = delete;

    void enqueue(T data)
    {
        buffer[back] = data;
        back = (back + 1) % SIZE;

        if (elements == SIZE)
        {
            front = (front + 1) % SIZE;
        }
        else
        {
            elements++;
        }
    }

    T dequeue(void)
    {
        T data{buffer[front]};
        if (elements != 0)
        {
            front = (front + 1) % SIZE;
            elements--;
        }

        return data;
    }

    // bool dequeue(T &data)
    // {
    //     bool status{false};

    //     if (elements != 0)
    //     {
    //         data = buffer[front];
    //         front = (front + 1) % SIZE;
    //         elements--;
    //         status = true;
    //     }

    //     return status;
    // }

    size_t available(void)
    {
        return elements;
    }

    bool is_full(void)
    {
        return (elements == SIZE);
    }

    void clear(void)
    {
        elements = front = back = 0;
    }

    friend std::ostream &operator<<(std::ostream &out, const Buffer &buf)
    {
        for (size_t i = 0; i < buf.elements; i++)
        {
            out << buf.buffer[(i + buf.front) % SIZE] << "\t";
        }

        return out;
    }

    template <typename U = T, typename = std::enable_if_t<std::is_arithmetic<U>::value>>
    float average(void)
    {
        float temp{0};

        for (size_t i = 0; i < elements; i++)
        {
            temp += static_cast<float>(buffer[(i + front) % SIZE]);
        }

        return (elements > 0) ? (temp / elements) : temp;
    }
};

#endif
