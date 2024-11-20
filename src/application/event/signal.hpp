#pragma once

#include <functional>
#include <vector>

class Signal
{
public:
    using Slot = std::function<void()>;

    void connect(Slot slot)
    {
        slots.push_back(slot);
    }

    void emit() {
        for (auto& slot : slots) {
            slot();
        }
    }

private:
    std::vector<Slot> slots;
};
