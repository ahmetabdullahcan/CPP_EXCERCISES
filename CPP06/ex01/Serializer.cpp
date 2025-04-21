#include "Serializer.hpp"


Serializer::Serializer() {
    std::cout << "Serializer default constructor called" << std::endl;
}

Serializer::Serializer(const Serializer &src) {
    *this = src;
}

Serializer &Serializer::operator=(const Serializer &rhs) {
    (void)rhs;
    return *this;
}

Serializer::~Serializer() {
    std::cout << "Serializer destructor called" << std::endl;
}


uintptr_t Serializer::serialize(t_data *ptr) {
    return reinterpret_cast<uintptr_t>(ptr);
}

t_data *Serializer::deserialize(uintptr_t raw) {
    return reinterpret_cast<t_data *>(raw);
}