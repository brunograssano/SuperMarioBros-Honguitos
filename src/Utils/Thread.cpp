#include "Thread.hpp"
#include "log/Log.hpp"

void Thread::empezarHilo(const std::string& nombreHilo) {
    int resultado = pthread_create(&hilo, nullptr, ejecutar_helper,this);
    if (resultado != 0) {
        throw std::runtime_error("ErrorAlCrearElHilo");
    }
    Log::getInstance()->mostrarMensajeDeInfo("Se creó el hilo "+nombreHilo+": (" + std::to_string(hilo) +").");
}

void Thread::join(const std::string& nombreHilo) const {
    int resultadoJoin = pthread_join(hilo, nullptr);
    if(resultadoJoin != 0) {
        Log::getInstance()->huboUnError(
                "Ocurrió un error al juntar los hilos con "+nombreHilo+", el codigo de error es: " + std::to_string(resultadoJoin));
        pthread_cancel(hilo);
        throw std::runtime_error("ErrorAlCrearElHilo");
    }
    Log::getInstance()->mostrarMensajeDeInfo("Se juntaron los hilos con "+nombreHilo+".");
}

void *Thread::ejecutar_helper(void *ptr) {
    ((Thread*)ptr)->ejecutar();
    return nullptr;
}

Thread::Thread(Thread &&otroThread) noexcept {
    this->hilo = otroThread.hilo;
}

Thread &Thread::operator=(Thread&& otroThread) noexcept {
    this->hilo = otroThread.hilo;
    return *this;
}

void Thread::dormirHilo() {
    pthread_mutex_lock(&mutexHilo);
    pthread_cond_wait(&variableCondicional, &mutexHilo);
    pthread_mutex_unlock(&mutexHilo);
}

void Thread::despertarHilo() {
    pthread_mutex_lock(&mutexHilo);
    pthread_cond_signal(&variableCondicional);
    pthread_mutex_unlock(&mutexHilo);
}
