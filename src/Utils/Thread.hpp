#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_THREAD_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_THREAD_HPP

#include <pthread.h>
#include <string>

class Thread {
    public:
        Thread() = default;
        virtual ~Thread() = default;
        void empezarHilo(std::string nombreHilo);
        void join(std::string nombreHilo) const;
        virtual void ejecutar() = 0;
        static void* ejecutar_helper(void* ptr);
        Thread(const Thread&) = delete;
        Thread& operator=(const Thread&) = delete;
        Thread(Thread&& otroThread) noexcept ;
        Thread& operator=(Thread&& otroThread) noexcept ;
    private:
        pthread_t hilo{};
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_THREAD_HPP
