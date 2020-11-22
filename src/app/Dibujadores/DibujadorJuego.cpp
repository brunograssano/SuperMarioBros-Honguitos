#include "DibujadorJuego.hpp"

#include "../AplicacionCliente.hpp"
#include "Dibujadores.hpp"

const float PROPORCION_PISO_EN_IMAGEN = 0.1;
const int ALTO_MARIO = 80, ANCHO_MARIO = 40;
const int ALTO_ENEMIGOS = 40, ANCHO_ENEMIGOS = 40;
const int LARGO_BLOQUE = 40;
const int GOOMBA = 1, KOOPA = 2;
const int MARIO_GRIS = -1;

DibujadorJuego::DibujadorJuego(CargadorTexturas* cargadorTexturas,SDL_Renderer* renderizador, int ancho_pantalla,int alto_pantalla){
	this->cargadorTexturas = cargadorTexturas;
	this->renderizador = renderizador;
	this->alto_pantalla = alto_pantalla;
	this->ancho_pantalla = ancho_pantalla;
	this->recorteSpriteMario = new RecorteMario();
	this->recorteSpriteGoomba = new RecorteGoomba();
	this->recorteSpriteKoopa = new RecorteKoopa();
	this->recorteSpriteMoneda = new RecorteMoneda();
}

void DibujadorJuego::dibujar(SDL_Rect* rectanguloCamara,JuegoCliente* juegoCliente){

	SDL_RenderClear( renderizador );
	SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaFondo(), rectanguloCamara, NULL);

	dibujarEnemigos(rectanguloCamara,juegoCliente);
	dibujarPlataformas(rectanguloCamara,juegoCliente);
	dibujarMonedas(rectanguloCamara,juegoCliente);
	dibujarMarios(rectanguloCamara,juegoCliente);
	dibujarTexto(juegoCliente);

	SDL_RenderPresent( renderizador );
}

void DibujadorJuego::dibujarEnemigos(SDL_Rect* rectanguloCamara,JuegoCliente* juegoCliente){
	list<enemigo_t> enemigos = juegoCliente->obtenerEnemigos();
	for (auto const& enemigo : enemigos) {
		SDL_Rect recorteTextura;
		if(enemigo.tipoEnemigo==GOOMBA){
			recorteTextura = recorteSpriteGoomba->obtenerRecorte(enemigo.numeroRecorte);
		}
		else{
			recorteTextura = recorteSpriteKoopa->obtenerRecorte(enemigo.numeroRecorte);
		}

		SDL_Rect rectanguloEnemigo = {enemigo.posX-rectanguloCamara->x,
									alto_pantalla - (int)(alto_pantalla*PROPORCION_PISO_EN_IMAGEN) - ALTO_ENEMIGOS,
									ANCHO_ENEMIGOS, ALTO_ENEMIGOS};

	    SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaEnemigo(enemigo.direccionImagen,renderizador), &recorteTextura, &rectanguloEnemigo);
	}
}

void DibujadorJuego::dibujarPlataformas(SDL_Rect* rectanguloCamara,JuegoCliente* juegoCliente){
	list<bloque_t> bloques = juegoCliente->obtenerBloques();

	for (auto const& bloque : bloques) {

		SDL_Rect rectanguloBloque = {bloque.posX - rectanguloCamara->x,
									alto_pantalla - (int)(alto_pantalla*PROPORCION_PISO_EN_IMAGEN) - bloque.posY,
									LARGO_BLOQUE, LARGO_BLOQUE};
		SDL_Rect recorteBloque = {0,0,16,16}; // Pasaria a ser un RecorteBloque (por los sorpresa)
		SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaBloque(bloque.dirImagen, renderizador), &recorteBloque, &rectanguloBloque);
	}

}

void DibujadorJuego::dibujarMonedas(SDL_Rect* rectanguloCamara,JuegoCliente* juegoCliente){
	list<moneda_t> monedas = juegoCliente->obtenerMonedas();
	for (auto const& moneda : monedas) {
		SDL_Rect rectanguloMoneda = {moneda.posX - rectanguloCamara->x,
									alto_pantalla - (int)(alto_pantalla*PROPORCION_PISO_EN_IMAGEN) - moneda.posY,
									LARGO_BLOQUE, LARGO_BLOQUE};
		SDL_Rect recorteMoneda = recorteSpriteMoneda->obtenerRecorte(moneda.numeroRecorte);
		SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaMoneda(), &recorteMoneda, &rectanguloMoneda);

	}
}

void DibujadorJuego::dibujarMarios(SDL_Rect* rectanguloCamara,JuegoCliente* juegoCliente){
	map<int,jugador_t> marios = juegoCliente->obtenerJugadores();
	int idPropio = juegoCliente->obtenerIDPropio();
	for(auto const mario:marios){
		mario_t jugador = mario.second.mario;
		if(jugador.idImagen != idPropio){
			int idMario = jugador.idImagen;
			SDL_Rect rectanguloMario = {jugador.posX - rectanguloCamara->x,
											alto_pantalla - (int)(alto_pantalla*PROPORCION_PISO_EN_IMAGEN) -ALTO_MARIO- jugador.posY,
											ANCHO_MARIO, ALTO_MARIO};

			SDL_Rect recorteMario = recorteSpriteMario->obtenerRecorte(jugador.recorteImagen);
			if(jugador.recorteImagen==MARIO_GRIS){
				idMario = jugador.recorteImagen;
			}
			SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaMario(idMario), &recorteMario, &rectanguloMario);
		}
	}

	mario_t jugador = marios[idPropio].mario;
	SDL_Rect rectanguloMario = {jugador.posX - rectanguloCamara->x,
												alto_pantalla - (int)(alto_pantalla*PROPORCION_PISO_EN_IMAGEN) -ALTO_MARIO- jugador.posY,
												ANCHO_MARIO, ALTO_MARIO};

	SDL_Rect recorteMario = recorteSpriteMario->obtenerRecorte(jugador.recorteImagen);
	SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaMario(jugador.idImagen), &recorteMario, &rectanguloMario);
}

void DibujadorJuego::dibujarTexto(JuegoCliente* juegoCliente){
	SDL_SetRenderDrawColor( renderizador, 0xFF, 0xFF, 0xFF, 0xFF );

	textoDeTiempo.str( "" );
	int tiempo = juegoCliente->obtenerTiempoFaltante();
	textoDeTiempo << "Tiempo restante " << tiempo;

	textoDeNivel.str("");
	textoDeNivel << "Mundo " << juegoCliente->obtenerMundoActual();

	map<int,jugador_t> jugadores = juegoCliente->obtenerJugadores();
	int espacioY = 10;
	for(auto const& parClaveJugador:jugadores){
		textoDePuntos.str("");
		textoDePuntos << "Puntos de "<< parClaveJugador.second.nombreJugador << parClaveJugador.second.puntos;
		SDL_Rect cuadradoPuntos = { 10, espacioY, 100, 30 };
		renderizarTexto(cuadradoPuntos, textoDePuntos.str().c_str());
		espacioY += 35;
	}

	SDL_Rect cuadradoTiempo = { ancho_pantalla - 340, 10, 330, 30 };
	SDL_Rect cuadradoMundo = { ancho_pantalla - ancho_pantalla/2 - 100, 10, 100, 30 };

	renderizarTexto(cuadradoTiempo, textoDeTiempo.str().c_str());
	renderizarTexto(cuadradoMundo, textoDeNivel.str().c_str());
}

DibujadorJuego::~DibujadorJuego(){
	delete this->recorteSpriteMario;
	delete this->recorteSpriteGoomba;
	delete this->recorteSpriteKoopa;
}
