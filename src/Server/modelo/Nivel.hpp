#ifndef SRC_SERVER_MODELO_NIVEL_HPP_
#define SRC_SERVER_MODELO_NIVEL_HPP_

#include <map>
#include <string>
#include <tuple>
#include <cstdlib>
#include <utility>
#include "src/Server/modelo/Bloques/Tuberia.hpp"
#include "Bloques/Plataforma.hpp"

#include "Bloques/Bloque.hpp"
#include "Enemigos/Enemigo.hpp"
#include "Moneda.hpp"
using namespace std;

const int ANCHO_FONDO2 = 8177;
const int ALTO_NIVEL = 600;

class Nivel{

	public:
		Nivel(int mundo,string direccionFondo,int tiempo,int cantidadMonedas,int puntoBanderaFin);
        void agregarTuberia(int posicionXNuevaTuberia, int tipoTuberia, int colorTuberia);
		void agregarPlataforma(Plataforma* unaPlataforma);
		void agregarEnemigo(Enemigo* unEnemigo);
		void agregarMoneda(Moneda* unaMoneda);
		int obtenerTiempo() const;
		int obtenerMundo() const;
		void actualizarModelo();
		void inicializarPosicionEnemigo();
		void inicializarPosicionMonedas();
		void inicializarPosicionesOcupadasPorBloques();
		float obtenerPuntoBanderaFin() const;
		list<Enemigo*> obtenerEnemigos();
		list<Plataforma*> obtenerPlataformas();
		list<Moneda*> obtenerMonedas();
        list<Tuberia*> obtenerTuberias();
		string obtenerDireccionFondoActual();
		~Nivel();

    private:
        void sacarEnemigosMuertos();
        void actualizarPosicionesEnemigos();
        void actualizarMonedas();
        bool esUnaPosicionXValidaEnemigo(int coordenadaX);
        bool esUnaPosicionValidaMoneda(int numeroPosicionX, int numeroPosicionY);

        map<int, bool> posicionesOcupadasXEnemigos;
        map<tuple<int, int>, bool> posicionesOcupadas;

        list<Plataforma*> plataformas;
        list<Enemigo*> enemigos;
        list<Moneda*> monedas;
        list<Tuberia*> tuberias;
        list<Enemigo*>enemigosMuertos;

        int mundo;
        string direccionFondo;
        int tiempo;
        int cantidadMonedas;
        float puntoBanderaFin;

};

#endif /* SRC_SERVER_MODELO_NIVEL_HPP_ */