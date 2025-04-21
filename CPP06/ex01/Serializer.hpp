#pragma once

#include <iostream>
#include <string>
#include <cstdint>

typedef struct s_data
{
    std::string userName;
    int age;
} t_data;


class Serializer
{
    private:
        Serializer();
        Serializer(const Serializer &src);
        Serializer &operator=(const Serializer &rhs);
        ~Serializer();

    public:
        static uintptr_t serialize(t_data *ptr);
        static t_data *deserialize(uintptr_t raw);
};