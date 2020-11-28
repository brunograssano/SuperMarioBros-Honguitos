#include "../AplicacionCliente.hpp"
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
	this->recorteSpriteBloque = new RecorteBloque();
}

void DibujadorJuego::dibujar(SDL_Rect* rectanguloCamara,JuegoCliente* juegoCliente){
	rectanguloCamara->x = juegoCliente->obtenerPosXCamara();
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
	string tipo;
	for (auto const& enemigo : enemigos) {
		SDL_Rect recorteTextura;
		if(enemigo.tipoEnemigo==GOOMBA){
			recorteTextura = recorteSpriteGoomba->obtenerRecorte(enemigo.numeroRecorteX,enemigo.numeroRecorteY);
			tipo = "resources/Imagenes/Personajes/Goombas.png";
		}
		else{
			recorteTextura = recorteSpriteKoopa->obtenerRecorte(enemigo.numeroRecorteX,enemigo.numeroRecorteY);
			tipo = "resources/Imagenes/Personajes/Koopas.png";
		}

		SDL_Rect rectanguloEnemigo = {enemigo.posX-rectanguloCamara->x,
									alto_pantalla - (int)(alto_pantalla*PROPORCION_PISO_EN_IMAGEN) - ALTO_ENEMIGOS,
									ANCHO_ENEMIGOS, ALTO_ENEMIGOS};

	    SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaEnemigo(tipo,renderizador), &recorteTextura, &rectanguloEnemigo);
	}
}

void DibujadorJuego::dibujarPlataformas(SDL_Rect* rectanguloCamara,JuegoCliente* juegoCliente){
	list<bloque_t> bloques = juegoCliente->obtenerBloques();
	string direccionBloque = "resources/Imagenes/Bloques/Bloques.png";
	for (auto const& bloque : bloques) {

		SDL_Rect rectanguloBloque = {bloque.posX - rectanguloCamara->x,
									alto_pantalla - (int)(alto_pantalla*PROPORCION_PISO_EN_IMAGEN) - bloque.posY,
									LARGO_BLOQUE, LARGO_BLOQUE};
		SDL_Rect recorteBloque = recorteSpriteBloque->obtenerRecorte(bloque.numeroRecorteX,bloque.numeroRecorteY);
		SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaBloque(direccionBloque, renderizador), &recorteBloque, &rectanguloBloque);
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
	map<int,jugador_t> jugadores = juegoCliente->obtenerJugadores();
	int idPropio = juegoCliente->obtenerIDPropio();
	for(auto const parClaveJugador:jugadores){
		mario_t mario = parClaveJugador.second.mario;
		if(mario.idImagen != idPropio){
			int idMario = mario.idImagen;
			SDL_Rect rectanguloMario = {mario.posX - rectanguloCamara->x,
											alto_pantalla - (int)(alto_pantalla*PROPORCION_PISO_EN_IMAGEN) -ALTO_MARIO- mario.posY,
											ANCHO_MARIO, ALTO_MARIO};

			SDL_Rect recorteMario = recorteSpriteMario->obtenerRecorte(mario.recorteImagen);
			if(mario.recorteImagen==MARIO_GRIS){
				idMario = mario.recorteImagen;
			}
			SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaMario(idMario), &recorteMario, &rectanguloMario);
		}
	}

	mario_t mario = jugadores[idPropio].mario;
	SDL_Rect rectanguloMario = {mario.posX - rectanguloCamara->x,
												alto_pantalla - (int)(alto_pantalla*PROPORCION_PISO_EN_IMAGEN) -ALTO_MARIO- mario.posY,
												ANCHO_MARIO, ALTO_MARIO};

	SDL_Rect recorteMario = recorteSpriteMario->obtenerRecorte(mario.recorteImagen);
	SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaMario(mario.idImagen), &recorteMario, &rectanguloMario);
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
		textoDePuntos << "Puntos de: "<< parClaveJugador.second.nombreJugador << " "<<parClaveJugador.second.puntos;
		SDL_Rect cuadradoPuntos = { 10, espacioY, 200, 30 };
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
