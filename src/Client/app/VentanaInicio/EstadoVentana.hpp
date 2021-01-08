#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_ESTADOVENTANA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_ESTADOVENTANA_HPP


class EstadoVentana {
    public:
        virtual ~EstadoVentana()= default;
        virtual void mostrarse(unsigned short jugadoresConectados, unsigned short jugadoresTotales)= 0;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_ESTADOVENTANA_HPP
