#pragma once
#include <unordered_map>
#include <string>

class SymbolTable {
private:
    std::unordered_map<std::string, bool> table;

public:
    void addVariable(const std::string& name) {
        table[name] = true;
    }

    bool exists(const std::string& name) const {
        return table.find(name) != table.end();
    }

    const std::unordered_map<std::string, bool>& getTable() const {
        return table;
    }
};
