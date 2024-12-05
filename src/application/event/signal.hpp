#pragma once

#include <functional>
#include <vector>

template <typename Ret>
class Signal
{
public:
    using Slot = std::function<void(Ret)>;

    void connect(Slot slot)
    {
        slots.push_back(slot);
    }

    template <typename Obj>
    void connect(Obj* obj, void (Obj::*member)(Ret))
    {
        auto slot = [obj, member](Ret value) {
            (obj->*member)(value);
        };
        slots.push_back(slot);
    }

    void emit(const Ret value) const
    {
        for (auto& slot : slots) {
            slot(value);
        }
    }

private:
    std::vector<Slot> slots;
};