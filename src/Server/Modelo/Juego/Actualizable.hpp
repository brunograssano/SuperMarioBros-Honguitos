#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_ACTUALIZABLE_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_ACTUALIZABLE_HPP


class Actualizable {
    public:
        virtual ~Actualizable() = default;
        virtual void actualizar()= 0;
};

#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_ACTUALIZABLE_HPP
