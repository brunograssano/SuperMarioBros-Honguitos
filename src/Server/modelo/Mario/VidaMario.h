#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_VIDAMARIO_H
#define TP_TALLER_DE_PROGRAMACION_FIUBA_VIDAMARIO_H


class VidaMario {
    public:
        VidaMario();
        int obtenerVida() const;
        ~VidaMario();
        void perderVida();

    private:
        int vidas;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_VIDAMARIO_H
