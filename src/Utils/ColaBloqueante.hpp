#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_COLABLOQUEANTE_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_COLABLOQUEANTE_HPP

#include <queue>
#include <pthread.h>

template <class T>class BlockingQueue{
    private:
        std::queue<T> queue;
        pthread_mutex_t mutexQueue = PTHREAD_MUTEX_INITIALIZER;

    public:
        bool empty(){
            bool empty;
            pthread_mutex_lock(&mutexQueue);
            empty = queue.empty();
            pthread_mutex_unlock(&mutexQueue);
            return empty;
        }

        void push(T t){
            pthread_mutex_lock(&mutexQueue);
            queue.push(t);
            pthread_mutex_unlock(&mutexQueue);
        }

        T front(){
            pthread_mutex_lock(&mutexQueue);
            T t = queue.front();
            pthread_mutex_unlock(&mutexQueue);
            return t;
        }

        T back(){
            pthread_mutex_lock(&mutexQueue);
            T t = queue.back();
            pthread_mutex_unlock(&mutexQueue);
            return t;
        }

        size_t size(){
            pthread_mutex_lock(&mutexQueue);
            size_t size = queue.size();
            pthread_mutex_unlock(&mutexQueue);
            return size;
        }

        void pop(){
            pthread_mutex_lock(&mutexQueue);
            queue.pop();
            pthread_mutex_unlock(&mutexQueue);
        }

};






#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_COLABLOQUEANTE_HPP
