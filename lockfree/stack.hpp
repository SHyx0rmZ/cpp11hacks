#ifndef _LIBSHY_LOCKFREE_STACK_HPP_
#define _LIBSHY_LOCKFREE_STACK_HPP_

#include <atomic>

namespace shy
{
    template <typename T>
    struct LockfreeStack
    {
        template <typename U>
        struct LockfreeStackNode
        {
            LockfreeStackNode *previous = nullptr;
            U data;

            LockfreeStackNode(U &value)
            {
                data = value;
            }
        };

        private:

            std::atomic<LockfreeStackNode<T> *> pointer = ATOMIC_VAR_INIT(nullptr);
            std::atomic<int> nodes = ATOMIC_VAR_INIT(0);

        public:

            void push(T value)
            {
                nodes.fetch_add(1);

                LockfreeStackNode<T> *n, *i = new LockfreeStackNode<T>(value);

                while (i != (n = pointer))
                {
                    if (n)
                        i->previous = n;
                    else
                        i->previous = nullptr;

                    if (pointer.compare_exchange_strong(n, i))
                        break;
                }
            }

            T pop()
            {
                LockfreeStackNode<T> *n;

                while (n = pointer)
                {
                    if (!n)
                        return T();

                    if (pointer.compare_exchange_strong(n, n->previous))
                        break;
                }

                T value = n->data;

                delete n;

                nodes.fetch_sub(1);

                return value;
            }

            volatile int size()
            {
                return nodes;
            }
    };
}

#endif
