#pragma once

#include <Windows.h>
#include <Psapi.h>
#include <iostream>
#include <print>
#include <map>
#include <span>
#include <sstream>
#include <vector>

#define SIGSCAN_API

enum SIGSCAN_API SigType {
    Relative,
    RelCall,
    Absolute
};

class SIGSCAN_API Sig {
public:
    const char* pattern;
    const char* mod;
    const char* name;
    const int offset;
    const SigType type;

    constexpr Sig(const char* pattern, const char* mod, const char* name, const int offset, const SigType type)
        : pattern(pattern), mod(mod), name(name), offset(offset), type(type) {}
};

SIGSCAN_API MODULEINFO get_module_info(const char* mod);

SIGSCAN_API std::vector<int> parse_sig(const char* pattern);

class SIGSCAN_API SigManager
{
private:

    std::map<std::string, uintptr_t> sigs;

public:

    void init(std::span<const Sig> precached_sigs) {
        for (const auto& sig: precached_sigs) {
            cache_sig(sig);
        }

        for (const auto& [name, addr]: sigs) {
            std::println("[+]SIG FOUND: {} -> {:X}", name, addr);
        }
    }

    void cache_sig(const Sig& sig) {
        const auto info { get_module_info(sig.mod) };
        const auto parsed_sig { parse_sig(sig.pattern) };

        auto* base { reinterpret_cast<uint8_t*>(info.lpBaseOfDll) };
        const auto image_size { static_cast<size_t>(info.SizeOfImage) };
        size_t sig_size { parsed_sig.size() };

        for (size_t i{0}; i < image_size - sig_size; ++i) {
            bool found { true };

            for (size_t j{0}; j < sig_size; ++j) {
                if (parsed_sig[j] != base[i + j] && parsed_sig[j] != -1) {
                    found = false;
                    break;
                }
            }

            if (found) {
                auto address { reinterpret_cast<uintptr_t>(base) + i };
                switch (sig.type) {
                case SigType::Relative: {
                    const auto offset { *reinterpret_cast<int*>(address + sig.offset) };
                    address = address + offset + 7;
                    break;
                }
                case SigType::RelCall: {
                    const auto offset { *reinterpret_cast<int*>(address + sig.offset) };
                    address = address + offset + 5;
                    break;
                }
                case SigType::Absolute: {
                    break;
                }
                }
                sigs.try_emplace(std::string(sig.name), address);
            }
        }
    }

    template <typename T>
    T get(const char* name) {
        return reinterpret_cast<T>(this->sigs.find(name)->second);
    }

    template <typename T>
    T* get_class(const char* name) {
        return *reinterpret_cast<T**>(this->sigs.find(name)->second);
    }
};
