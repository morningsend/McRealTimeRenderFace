//
// Created by Zaiyang Li on 31/01/2018.
//

#ifndef RENDERER_EXCEPTION_HPP
#define RENDERER_EXCEPTION_HPP

#include <string>

namespace McRenderer {
    using namespace std;
    class Exception {
    private:
        string message;
    public:
        explicit Exception(const string& messageIn) noexcept : message{messageIn} {};
        explicit Exception(const Exception& exception) noexcept: Exception(exception.message){}
    };
}


#endif //RENDERER_EXCEPTION_HPP
