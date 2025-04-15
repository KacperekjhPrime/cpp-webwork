#include "Comma.h"

namespace webwork::expression {
    const std::shared_ptr<Comma> &Comma::GetInstance() {
        if (!instance) {
            instance = std::make_shared<Comma>();
        }
        return instance;
    }
}