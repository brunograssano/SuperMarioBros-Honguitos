#ifndef SRC_SERVER_MODELO_NIVEL_HPP_
#define SRC_SERVER_MODELO_NIVEL_HPP_

#include <map>
#include <string>
#include <tuple>
#include <cstdlib>
#include <utility>

#include "src/Server/Modelo/Juego/Nivel/Piso/Pozo.hpp"
#include "Bloques/Tuberia.hpp"
#include "Bloques/Bloque.hpp"
#include "Bloques/ObjetosSorpresa/ObjetoSorpresa.hpp"
#include "Enemigos/Enemigo.hpp"
#include "Moneda.hpp"
#include "Meta.hpp"
#include "Piso/Piso.hpp"
#include "Podio.hpp"

#include "src/Server/Modelo/Juego/Objetos/ObjetoFugaz.hpp"
#include "src/Server/Modelo/Juego/Posiciones/PosicionFija.hpp"
#include "src/Utils/Contador.hpp"
#include "Actualizador.hpp"
#include "Serializador.hpp"

const int ALTO_NIVEL = 600;

class Nivel{
	public:
        Nivel(int mundo, std::string direccionFondo, int tiempo, int cantidadMonedas, int puntoBanderaFin, int altoPiso);
        ~Nivel();
		void inicializar();
        void agregarTuberia(int posicionXNuevaTuberia, int tipoTuberia, int colorTuberia);
        void agregarPozo(int posicionX, int tipoPozo, int fondo);
		void agregarPlataforma(std::list<Bloque *> unaPlataforma);
		void agregarEnemigo(Enemigo* unEnemigo);
		void agregarMoneda(Moneda* unaMoneda);
		int obtenerMundo() const;
		int tiempoRestante();
		void iniciar(const std::map<int, Mario*>& jugadores);

        /* Completará la información de los siguientes campos:
         * tiempoFaltante, mundo, bloques[], enemigos[], monedas[],tuberias[], y sus respectivos topes */
		void completarInformacionRonda(info_ronda_t* ptrInfoRonda, bool (* deboAgregarlo)(void*, rectangulo_t), void* contexto);
        void actualizarModelo(const std::map<int, Mario*>& jugadores, rectangulo_t rectanguloEscena);
        bool todosEnLaMeta(const std::map<int, Mario*>& jugadores);
        std::string obtenerDireccionFondoActual();
        void terminar(const std::map<int, Mario*>& jugadores);
        void completarInformacionNivel(nivel_t *nivel);
        void aparecerDisparo(ObjetoFugaz* disparo);
        Podio* obtenerPodio();

    private:
        void sacarEnemigosMuertos();
        void actualizarPosicionesEnemigos(rectangulo_t rectangulo);
        void actualizar(std::list<Actualizable*> actualizables);
        void resolverColisiones(const std::map<int,Mario*>& jugadores, rectangulo_t rectanguloEscena);
        bool esUnaPosicionXValidaEnemigo(int coordenadaX);
        bool esUnaPosicionValidaMoneda(int numeroPosicionX, int numeroPosicionY);
        void resolverGanadores(const std::map<int, Mario *>& map);
        void elevarObstaculos();
        void inicializarPosicionEnemigo();
        void inicializarPosicionMonedas();
        void inicializarPosicionOcupadasPorTuberias();
        void inicializarPosicionesOcupadasPorBloques();
        static void agregarObjeto_helper(void* ptr_jugador, void* ptr_bloque, void* ptr_nivel);
        void utilizarSorpresa(Mario* jugador, Bloque* bloque);

        std::map<int, bool> posicionesOcupadasXEnemigos;
        std::map<std::tuple<int, int>, bool> posicionesOcupadas;

        std::list<Bloque*> plataformas;
        std::list<Enemigo*> enemigos;
        std::list<Moneda*> monedas;
        std::list<Tuberia*> tuberias;
        std::list<ObjetoFugaz*> objetosFugaces;
        Piso piso;

        Meta meta;
        Contador contador;
        Podio podio;
        Actualizador actualizador;
        Serializador serializador;

        int mundo;
        std::string direccionFondo;
        int cantidadMonedas;
        float puntoBanderaFin;

        void imponerPosicionDeReaparicion(const std::map<int, Mario*>& jugadores, rectangulo_t rectanguloEscena);
        void buscarBloqueParaCaer(rectangulo_t rectanguloEscena, PosicionFija* pos);
        void buscarBloqueMasAlto(PosicionFija* posicion);
};

#endif /* SRC_SERVER_MODELO_NIVEL_HPP_ */