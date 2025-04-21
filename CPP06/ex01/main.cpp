#include "Serializer.hpp"

int main()
{
    t_data data;
    data.userName = "John Doe";
    data.age = 30;

    std::cout << "================================================" << std::endl;


    std::cout << "Original Address: " << &data << std::endl;
    std::cout << "Original User Name: " << data.userName << std::endl;
    std::cout << "Original Age: " << data.age << std::endl;

    std::cout << "================================================" << std::endl;
    uintptr_t serializedData = Serializer::serialize(&data);

    t_data *deserializedData = Serializer::deserialize(serializedData);
    std::cout << "Deserialized Address: " << deserializedData << std::endl;
    std::cout << "Deserialized User Name: " << deserializedData->userName << std::endl;
    std::cout << "Deserialized Age: " << deserializedData->age << std::endl;

    std::cout << "================================================" << std::endl;

    uintptr_t newSerializedData = Serializer::serialize(deserializedData);
    std::cout << "New Serialized Address: " << Serializer::deserialize(newSerializedData) << std::endl;
    std::cout << "New Serialized User Name: " << Serializer::deserialize(newSerializedData)->userName << std::endl;
    std::cout << "New Serialized Age: " << Serializer::deserialize(newSerializedData)->age << std::endl;

    std::cout << "================================================" << std::endl;


    return 0;
}