#ifndef FUNCTION_H
#define FUNCTION_H
#include <functional>

#include "Helper.h"
#include "../Helper.h"
#include "Interfaces/IFunction.h"

namespace webwork::properties {
    namespace detail {
        template <class T>
        constexpr T GetPropertyValue(std::span<std::shared_ptr<const Property>> props, size_t index) {
            using Interface = PropertyInterfaceT<T>;
            const auto ptr = std::dynamic_pointer_cast<const Interface>(props[index]);
            if (!ptr) throw std::runtime_error(std::format("Property at {} is not type {}.", index, GetTypeName<Interface>()));
            return static_cast<T>(Interface::GetValue(*ptr));
        }

        template <class ...Ts>
        constexpr auto GetPropertyValues(std::span<std::shared_ptr<const Property>> props) {
            constexpr auto fn = []<size_t ...I>(std::span<std::shared_ptr<const Property>> props, std::index_sequence<I...>) {
                return std::make_tuple(GetPropertyValue<Ts>(props, I)...);
            };
            return fn(props, std::make_index_sequence<sizeof...(Ts)>());
        }

        template <class Result, class ...Args>
        constexpr auto WrapFunction(const std::function<Result(Args...)> &function) {
            return [function](std::span<std::shared_ptr<const Property>> props) {
                if (props.size() < sizeof...(Args)) throw std::runtime_error(std::format("Missing function paramters. {} required.", sizeof...(Args)));
                const auto values = GetPropertyValues<Args...>(props);
                return CreateProperty(std::apply(function, values));
            };
        }
    }

    class Function final : public Property, public IFunction {
    public:
        using FunctionT = std::function<std::shared_ptr<const Property>(std::span<std::shared_ptr<const Property>> props)>;

        const FunctionT function;

        explicit Function(const FunctionT &function);
        explicit Function(const auto &function) : function(detail::WrapFunction(std::function(function))) {}

        std::shared_ptr<const Property> Execute(std::span<std::shared_ptr<const Property>> properties) const override;
    };
}

#endif //FUNCTION_H
