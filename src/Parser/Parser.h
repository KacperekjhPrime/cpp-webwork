#ifndef PARSER_H
#define PARSER_H
#include <vector>
#include <functional>
#include <stack>

#include "BasicToken.h"
#include "Chunk.h"
#include "Tree.h"
#include "Block.h"

namespace webwork {
    using TokenTree = Tree<char, TokenT>;
    using MergeRules = Tree<TokenT, TokenT>;

    template <class T>
    using TokenCreator = std::function<std::shared_ptr<T>(std::string_view text, const Chunk &chunk)>;

    void PushTextToken(std::vector<BasicToken> &tokens, std::string_view text, size_t i, size_t depth, size_t tokenStart);
    void PushToken(std::vector<BasicToken> &tokens, std::string_view text, TokenT type, size_t i, size_t depth);
    void PushTextChunk(std::vector<Chunk> &chunks, const std::vector<BasicToken> &tokens, size_t i, size_t depth);
    void PushChunk(std::vector<Chunk> &chunks, const std::vector<BasicToken> &tokens, size_t i, size_t depth, TokenT type, bool &escape);

    template <class T>
    constexpr auto GetTokenCreator() {
        return [](std::string_view text, const Chunk &chunk) { return std::make_shared<T>(text, chunk); };
    }

    std::shared_ptr<TokenTree> MakeRecursiveTrailingSpace(TokenT type);


    std::vector<BasicToken> TokenizeText(std::string_view text, const std::shared_ptr<TokenTree> &tree);

    std::vector<Chunk> MergeTokens(const std::vector<BasicToken> &tokens, const std::shared_ptr<MergeRules> &rules);

    template <class Token, class Root, class Text>
    std::shared_ptr<Root> AssembleTree(std::string_view text, const std::vector<Chunk> &chunks, const std::map<TokenT, TokenCreator<Token>> &map) {
        const auto root = std::make_shared<Root>();
        std::stack<std::pair<std::shared_ptr<Block<Token>>, size_t>> children;
        children.push({root, 0});

        for (const auto &chunk : chunks) {
            const auto &top = children.top().first;
            if (chunk.type == top->closingToken) {
                children.top().first->CloseBlock();
                children.pop();
            } else {
                const auto creator = map.find(chunk.type);
                if (creator != map.end()) {
                    const auto created = creator->second(text, chunk);
                    top->AddChild(created);

                    const auto block = std::dynamic_pointer_cast<Block<Token>>(created);
                    if (block) {
                        children.push({block, chunk.GetTextIndex(text)});
                    }
                } else if ((chunk.type & TokenTextBit) > 0) {
                    top->AddChild(std::make_shared<Text>(text, chunk));
                } else {
                    throw std::runtime_error(std::format("Unexpected token at {}: {}", chunk.GetTextIndex(text), chunk.GetText()));
                }
            }
        }

        if (children.size() > 1) {
            const auto &[block, index] = children.top();
            throw std::runtime_error(std::format("Unclosed {} block at {}.", block->name, index));
        }

        root->CloseBlock();
        return root;
    }
}

#endif //PARSER_H
