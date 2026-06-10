#pragma onces

#include <memory>

class BaseCommand;

class Facade {
public:
    Facade() = default;
    ~Facade() = default;

    void execute(std::shared_ptr<BaseCommand> command);
};
