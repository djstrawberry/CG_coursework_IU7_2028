#ifndef FACADE_H
#define FACADE_H

#include <memory>

class BaseCommand;

class Facade {
public:
    Facade() = default;
    ~Facade() = default;

    void execute(std::shared_ptr<BaseCommand> command);
};

#endif // FACADE_H
