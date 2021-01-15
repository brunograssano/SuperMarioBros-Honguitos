#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_VIDAMARIO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_VIDAMARIO_HPP


class VidaMario {
    public:
        VidaMario();
        int obtenerVida() const;
        ~VidaMario();
        void perderVida();
        bool estaVivo();
private:
        int vidas;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_VIDAMARIO_HPP
