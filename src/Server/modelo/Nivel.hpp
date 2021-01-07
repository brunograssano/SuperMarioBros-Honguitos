#ifndef SRC_SERVER_MODELO_NIVEL_HPP_
#define SRC_SERVER_MODELO_NIVEL_HPP_

#include <map>
#include <string>
#include <tuple>
#include <cstdlib>
#include <utility>
#include "src/Server/modelo/Bloques/Tuberia.hpp"
#include "Bloques/Plataforma.hpp"
#include "src/Utils/Contador.hpp"
#include "Bloques/Bloque.hpp"
#include "Enemigos/Enemigo.hpp"
#include "Moneda.hpp"
using namespace std;

const int ANCHO_FONDO2 = 8177;
const int ALTO_NIVEL = 600;

class Nivel{
    //TODO: Pasar todo al cpp...
	public:
		Nivel(int mundo, string direccionFondo, int tiempo, int cantidadMonedas, int puntoBanderaFin){
			this->mundo = mundo;
			this->direccionFondo = std::move(direccionFondo);
			this->tiempo = tiempo;
			this->cantidadMonedas = cantidadMonedas;
			this->puntoBanderaFin = ANCHO_FONDO2* (float) puntoBanderaFin /100;
			this->contador = new Contador(tiempo, SEGUNDOS);
		}

		void inicializar();

        void agregarTuberia(int posicionXNuevaTuberia, int tipoTuberia, int colorTuberia);

		void agregarPlataforma(Plataforma* unaPlataforma){
			plataformas.push_back(unaPlataforma);
		}

		void agregarEnemigo(Enemigo* unEnemigo){
			enemigos.push_back(unEnemigo);
		}

		void agregarMoneda(Moneda* unaMoneda){
			monedas.push_back(unaMoneda);
		}

		int obtenerMundo() const{
			return mundo;
		}

		int tiempoRestante(){
		    return contador->tiempoRestante();
		}

		void iniciar(){
		    contador->iniciar();
		}


		/*
         * Completará la información de los siguientes campos:
         *
         * mundo
         * tiempoFaltante
         * bloques[], tope
         * enemigos[], tope
         * monedas[], tope
         * tuberias[], tope
         */
		void completarInformacionRonda(info_ronda_t* ptrInfoRonda, bool (* deboAgregarlo)(void*, int), void* ctx);

        void actualizarModelo();


		float obtenerPuntoBanderaFin() const;
		string obtenerDireccionFondoActual();

		~Nivel(){
			for(const auto& plataforma:plataformas){
				delete plataforma;
			}
			for(const auto& moneda:monedas){
				delete moneda;
			}
			for(const auto& enemigo:enemigos){
				delete enemigo;
			}
			plataformas.clear();
			enemigos.clear();
			monedas.clear();
			delete contador;
		}

    private:
        void actualizarPosicionesEnemigos();
        void actualizarMonedas();
        bool esUnaPosicionXValidaEnemigo(int coordenadaX);
        bool esUnaPosicionValidaMoneda(int numeroPosicionX, int numeroPosicionY);

        void inicializarPosicionEnemigo();
        void inicializarPosicionMonedas();
        void inicializarPosicionesOcupadasPorBloques();

        map<int, bool> posicionesOcupadasXEnemigos;
        map<tuple<int, int>, bool> posicionesOcupadas;

        list<Plataforma*> plataformas;
        list<Enemigo*> enemigos;
        list<Moneda*> monedas;
        list<Tuberia*> tuberias;

        Contador* contador;
        int mundo;
        string direccionFondo;
        int tiempo;
        int cantidadMonedas;
        float puntoBanderaFin;
};

#endif /* SRC_SERVER_MODELO_NIVEL_HPP_ */