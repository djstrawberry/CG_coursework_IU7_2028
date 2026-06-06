#include "Facade.h"
#include "../commands/BaseCommand.h"

void Facade::execute(std::shared_ptr<BaseCommand> command) {
    if (command) {
        command->execute();
    }
}
