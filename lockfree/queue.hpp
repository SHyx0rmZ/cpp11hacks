#ifndef _CPP11HACKS_LOCKFREE_QUEUE_HPP_
#define _CPP11HACKS_LOCKFREE_QUEUE_HPP_

#include <atomic>

namespace cpp11hacks
{
    template <typename T>
    struct LockfreeQueue
    {
        template <typename U>
        struct LockfreeQueueNode
        {
            LockfreeQueueNode *next = nullptr;
            U data;

            LockfreeQueueNode(U &value)
            {
                data = value;
            }
        };

        private:

            std::atomic<LockfreeQueueNode<T> *> first = ATOMIC_VAR_INIT(nullptr);
            std::atomic<LockfreeQueueNode<T> *> last = ATOMIC_VAR_INIT(nullptr);
            std::atomic<int> nodes = ATOMIC_VAR_INIT(0);

        public:

            void enqueue(T value)
            {
                nodes.fetch_add(1);

                LockfreeQueueNode<T> *i = new LockfreeQueueNode<T>(value);
                LockfreeQueueNode<T> *l, *p;

                while (i != (l = last))
                    if (last.compare_exchange_strong(l, i))
                    {
                        if (l)
                            (p = l)->next = i;
                        else
                            p = i;

                        break;
                    }

                while (!(l = first))
                    if (first.compare_exchange_strong(l, p))
                        break;
            }

            T dequeue()
            {
                LockfreeQueueNode<T> *f;

                while (f = first)
                    if (first.compare_exchange_strong(f, f->next))
                        break;

                if (f) {
                    while (f == last)
                        if (last.compare_exchange_strong(f, static_cast<LockfreeQueueNode<T> *>(nullptr)))
                            break;

                    T value = f->data;

                    delete f;

                    nodes.fetch_sub(1);

                    return value;
                }
                else
                    return T();
            }

            volatile int size()
            {
                return nodes;
            }
    };
}

#endif
