//
// Created by pawkrol on 12/26/15.
//

#ifndef DUDESPATROL_GAMEEXCEPTION_H
#define DUDESPATROL_GAMEEXCEPTION_H

#include <exception>

class GameException : public std::exception {
private:
    const char *err_msg;
public:
    GameException(const char *msg) : err_msg(msg){
    }

    virtual const char *what() const noexcept{
        return err_msg;
    }
};

#endif //DUDESPATROL_GAMEEXCEPTION_H
