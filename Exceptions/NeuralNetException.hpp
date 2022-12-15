#ifndef NEURAL_NET_EXCEPTION_HPP
#define NEURAL_NET_EXCEPTION_HPP

#include<exception>
#include<string>

class NeuralNetException : public std::exception
{
    public:
    NeuralNetException() = delete;
    NeuralNetException(const std::string& message)
        :   m_message(message)
    {

    }

    const char* what() const noexcept override
    {
        return m_message.c_str();
    }


    private:
    const std::string& m_message;
};

#endif
