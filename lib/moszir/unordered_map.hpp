#pragma once

#include <unordered_map>

namespace moszir
{

template <typename KeyType, typename ValueType>
class UnorderedMap : public std::unordered_map<KeyType, ValueType>
{
    using BaseClass = std::unordered_map<KeyType, ValueType>;
    using This = UnorderedMap<KeyType, ValueType>;

public:

    ValueType get(const KeyType& key, const ValueType& defaultValue) const
    {
        const auto it = BaseClass::find(key);
        return it == BaseClass::end() ? defaultValue : it->second;
    }
};

} // namespace moszir
