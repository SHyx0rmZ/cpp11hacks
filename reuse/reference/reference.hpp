#ifndef _LIBSHY_REFERENCE_HPP_
#define _LIBSHY_REFERENCE_HPP_

#include <cstddef>
#include <map>
#include <stdexcept>

#if defined(_MSC_VER)
#pragma warning(disable: 4251)
#endif

namespace shy
{
    extern std::map<void *, unsigned int> *references;

    // manage N instances of type T
    template <typename T, std::size_t N = 1> class referenced
    {
        private:
            std::map<void *, unsigned int>::iterator iterator;
            std::size_t size;

            // decrease reference count
            inline void decrease_count() noexcept
            {
                this->iterator->second--;

                // delete resource if unreferenced
                if (this->iterator->second == 0)
                {
                    delete[] reinterpret_cast<T *>(this->iterator->first);

                    references->erase(this->iterator);
                }

                this->iterator = references->end();
            }

            // increase reference count
            constexpr inline void increase_count() noexcept
            {
                this->iterator->second++;
            }


        public:
            referenced()
            {
                // map that keeps track of every referenced type (for cleanup)
                if (references == nullptr)
                    references = new std::map<void *, unsigned int>;

                this->iterator = references->end();
                this->size = sizeof(T) * N;

                T *t = new T[N];

                std::pair<std::map<void *, unsigned int>::iterator, bool> result = references->insert(std::pair<void *, unsigned int>(reinterpret_cast<void *>(t), 0));

                if (result.second == false)
                    throw std::runtime_error("Inserting reference");

                this->iterator = result.first;

                increase_count();
            }

            referenced(const referenced<T, N> &copy) noexcept
            {
                this->iterator = copy.iterator;

                increase_count();
            }

            ~referenced() noexcept
            {
                decrease_count();

                if (references->size() == 0)
                {
                    delete references;

                    references = nullptr;
                }
            }

            referenced<T, N> &operator=(const referenced<T, N> &copy) noexcept
            {
                decrease_count();

                this->iterator = copy.iterator;

                increase_count();

                return *this;
            }

            constexpr T *address() const noexcept
            {
                return reinterpret_cast<T *>(this->iterator->first);
            }

            constexpr T &value() const noexcept
            {
                return *reinterpret_cast<T *>(this->iterator->first);
            }

            constexpr bool is_last() const noexcept
            {
                return (this->iterator->second == 1);
            }

            T *operator->() const
            {
                return address();
            }
    };
}

#endif
