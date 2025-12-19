#define cast_ptr(ptr) reinterpret_cast<uintptr_t>(ptr)
#define array_size(arr) sizeof(arr) / sizeof(arr[0])

namespace Utility {
    const char* get_class_name(void* class_obj);
}
