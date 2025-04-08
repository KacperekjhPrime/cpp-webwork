//
// Created by Kacper on 08/04/25.
//

#include "Text.h"

namespace webwork::properties {
    Text::Text(std::string_view data) : data(data) {}

    std::string Text::ToString() const {
        return data;
    }
} // webwork