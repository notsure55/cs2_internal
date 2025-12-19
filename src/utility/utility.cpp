#include <utility/utility.h>
#include <cstdint>
#include <Windows.h>

namespace Utility {
    const char* get_class_name(void* class_obj) {
        const auto base { *reinterpret_cast<uintptr_t*>(cast_ptr(class_obj)) };
        const auto class_name_offset { *reinterpret_cast<uint32_t*>(*reinterpret_cast<uintptr_t*>(base - 0x8) + 0xC) };
        const auto client { cast_ptr(GetModuleHandleW(L"client.dll")) };
        return reinterpret_cast<const char*>(client + class_name_offset + 0x14);
    }
}
