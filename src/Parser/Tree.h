#ifndef TREE_H
#define TREE_H
#include <map>
#include <memory>
#include <variant>

namespace webwork {
    template <class Key, class Type>
    struct Tree {
        using Child = std::variant<std::shared_ptr<Tree>, Type>;

        std::map<Key, Child> children;
        std::optional<Type> type;

        void AddBranch(std::span<const Key> keys, const Child &ending) {
            if (keys.empty()) return;

            auto branch = this;

            for (size_t i = 0; i < keys.size() - 1; i++) {
                const auto existingBranch = branch->children.find(keys[i]);
                if (existingBranch != branch->children.end()) {
                    const auto &value = existingBranch->second;
                    if (std::holds_alternative<Type>(value)) {
                        // Replace the ending branch with a new one and set type;
                        const auto type = std::get<Type>(value);
                        const auto newBranch = std::make_shared<Tree>();
                        newBranch->type = type;
                        existingBranch->second = newBranch;
                        branch = newBranch.get();
                    } else {
                        branch = std::get<std::shared_ptr<Tree>>(value).get();
                    }
                } else {
                    const auto newBranch = std::make_shared<Tree>();
                    branch->children[keys[i]] = newBranch;
                    branch = newBranch.get();
                }
            }

            branch->children[keys.back()] = ending;
        }
    };
}

#endif //TREE_H
