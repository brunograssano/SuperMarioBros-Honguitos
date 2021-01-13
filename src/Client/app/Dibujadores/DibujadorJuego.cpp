#include "DibujadorJuego.hpp"
#include "src/Utils/Constantes.hpp"
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
    this->recorteSpriteTuberia = new RecorteTuberia();
    recorteEfectos[BOLA_DE_FUEGO] = new RecorteBolaDeFuego();
    clavesEfectos[BOLA_DE_FUEGO] = "BolaDeFuego";
    recorteEfectos[CHISPA] = new RecorteChispa();
    clavesEfectos[CHISPA] = "Chispa";
    recorteEfectos[FLOR] = new RecorteFlor();
    clavesEfectos[FLOR] = "Flor";

    colores[-1] = {150, 150 , 150, 255}; // Gris.
    colores[0] = {230, 30 , 044, 255}; // Rojo.
	colores[1] = {69 , 230, 52 , 255}; // Verde.
	colores[2] = {179, 25 , 252, 255}; // Violeta.
	colores[3] = {76 , 225, 252, 255}; // Celeste.
}

void DibujadorJuego::dibujar(SDL_Rect* rectanguloCamara,JuegoCliente* juegoCliente){
	rectanguloCamara->x = juegoCliente->obtenerPosXCamara();
	SDL_RenderClear( renderizador );
	SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaFondo(), rectanguloCamara, nullptr);

	dibujarEnemigos(rectanguloCamara, juegoCliente);
	dibujarPlataformas(rectanguloCamara, juegoCliente);
	dibujarMonedas(rectanguloCamara, juegoCliente);
	dibujarTuberias(rectanguloCamara, juegoCliente);
    dibujarEfectos(rectanguloCamara, juegoCliente);
    dibujarMarios(rectanguloCamara, juegoCliente);
	dibujarTexto(juegoCliente);

	SDL_RenderPresent( renderizador );
}

void DibujadorJuego::dibujarEnemigos(SDL_Rect* rectanguloCamara,JuegoCliente* juegoCliente){
	list<enemigo_t> enemigos = juegoCliente->obtenerEnemigos();
	string tipo;
	SDL_Texture* texturaEnemigo = nullptr;
	for (auto const& enemigo : enemigos) {
		SDL_Rect recorteTextura;
		if(enemigo.tipoEnemigo==GOOMBA){
			recorteTextura = recorteSpriteGoomba->obtenerRecorte(enemigo.numeroRecorteX,enemigo.numeroRecorteY);
            texturaEnemigo = cargadorTexturas->obtenerTextura("Goombas");
		}
		else{
			recorteTextura = recorteSpriteKoopa->obtenerRecorte(enemigo.numeroRecorteX,enemigo.numeroRecorteY);
            texturaEnemigo = cargadorTexturas->obtenerTextura("Koopas");
		}

		SDL_Rect rectanguloEnemigo = {enemigo.posX-rectanguloCamara->x,
									alto_pantalla - (int)(alto_pantalla*PROPORCION_PISO_EN_IMAGEN) - enemigo.posY - ALTO_ENEMIGOS,
									ANCHO_ENEMIGOS, ALTO_ENEMIGOS};

        SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 0x0F );
		SDL_RenderDrawRect(renderizador, &rectanguloEnemigo);

		SDL_RenderCopyEx(renderizador,texturaEnemigo,&recorteTextura,&rectanguloEnemigo,0,
                         nullptr,enemigo.espejar?SDL_FLIP_HORIZONTAL:SDL_FLIP_NONE);
    }
}

void DibujadorJuego::dibujarPlataformas(SDL_Rect* rectanguloCamara,JuegoCliente* juegoCliente){
	list<bloque_t> bloques = juegoCliente->obtenerBloques();
    SDL_Texture* texturaBloques = cargadorTexturas->obtenerTextura("Bloques");
	for (auto const& bloque : bloques) {

		SDL_Rect rectanguloBloque = {bloque.posX - rectanguloCamara->x,
									alto_pantalla - (int)(alto_pantalla*PROPORCION_PISO_EN_IMAGEN) - bloque.posY - LARGO_BLOQUE,
									LARGO_BLOQUE, LARGO_BLOQUE};
		SDL_Rect recorteBloque = recorteSpriteBloque->obtenerRecorte(bloque.numeroRecorteX,bloque.numeroRecorteY);
		SDL_RenderCopy( renderizador, texturaBloques, &recorteBloque, &rectanguloBloque);
	}

}

void DibujadorJuego::dibujarMonedas(SDL_Rect* rectanguloCamara,JuegoCliente* juegoCliente){
	list<moneda_t> monedas = juegoCliente->obtenerMonedas();
    SDL_Texture* texturaMoneda = cargadorTexturas->obtenerTextura("Moneda");
	for (auto const& moneda : monedas) {
		SDL_Rect rectanguloMoneda = {moneda.posX - rectanguloCamara->x,
									alto_pantalla - (int)(alto_pantalla*PROPORCION_PISO_EN_IMAGEN) - moneda.posY - LARGO_BLOQUE,
									LARGO_BLOQUE, LARGO_BLOQUE};
		SDL_Rect recorteMoneda = recorteSpriteMoneda->obtenerRecorte(moneda.numeroRecorte);
		SDL_RenderCopy( renderizador, texturaMoneda, &recorteMoneda, &rectanguloMoneda);
	}
}

void DibujadorJuego::dibujarTuberias(SDL_Rect *rectanguloCamara, JuegoCliente *juegoCliente) {
    list<tuberia_t> tuberias = juegoCliente->obtenerTuberias();
    SDL_Texture* texturaTuberia = cargadorTexturas->obtenerTextura("Tuberia");
    for (auto const& tuberia : tuberias) {
        SDL_Rect recorteTuberia = recorteSpriteTuberia->obtenerRecorte(tuberia.tipo,tuberia.color);
        SDL_Rect rectanguloTuberia = {tuberia.posX - rectanguloCamara->x,
                                      alto_pantalla - (int)(alto_pantalla*PROPORCION_PISO_EN_IMAGEN),
                                      recorteTuberia.h, recorteTuberia.w};
        if(tuberia.tipo==0){
            rectanguloTuberia.h *= 5;
            rectanguloTuberia.w *= 2;
        }
        else{
            rectanguloTuberia.h *= 3;
            rectanguloTuberia.w *= 3;
        }
        rectanguloTuberia.y -= rectanguloTuberia.h;
        SDL_RenderCopy( renderizador, texturaTuberia, &recorteTuberia, &rectanguloTuberia);
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
				recorteMario = recorteSpriteMario->obtenerRecorte(0);
			}

			SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaMario(idMario), &recorteMario, &rectanguloMario);
		}
	}

	mario_t mario = jugadores[idPropio].mario;
	SDL_Rect rectanguloMario = {mario.posX - rectanguloCamara->x,
												alto_pantalla - (int)(alto_pantalla*PROPORCION_PISO_EN_IMAGEN) -ALTO_MARIO- mario.posY,
												ANCHO_MARIO, ALTO_MARIO};

	SDL_Rect recorteMario = recorteSpriteMario->obtenerRecorte(mario.recorteImagen);
    SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 0x0F );
    SDL_RenderDrawRect(renderizador, &rectanguloMario);
	SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaMario(mario.idImagen), &recorteMario, &rectanguloMario);
}

void DibujadorJuego::dibujarEfectos(SDL_Rect* rectanguloCamara, JuegoCliente* juegoCliente) {
    list<efecto_t> efectos = juegoCliente->obtenerEfectos();
    for (auto const& efecto : efectos) {
        if(efecto.tipoDeEfecto == BOLA_DE_FUEGO || efecto.tipoDeEfecto == CHISPA || efecto.tipoDeEfecto == FLOR) {
            SDL_Texture* textura = cargadorTexturas->obtenerTextura(clavesEfectos[efecto.tipoDeEfecto]);
            Recorte* recorteEfecto = recorteEfectos[efecto.tipoDeEfecto];
            SDL_Rect rectanguloRecorte = recorteEfecto->obtenerRecorte(efecto.numeroRecorte);
            SDL_Rect rectanguloEfecto = {efecto.posX - rectanguloCamara->x,
                                         alto_pantalla - (int) (alto_pantalla * PROPORCION_PISO_EN_IMAGEN) - efecto.posY - recorteEfecto->obtenerAltura(),
                                         recorteEfecto->obtenerAnchura(), recorteEfecto->obtenerAltura()};
            SDL_RendererFlip flip = recorteEfecto->direccion(efecto.numeroRecorte) == DERECHA?SDL_FLIP_NONE:SDL_FLIP_HORIZONTAL;
            SDL_RenderCopyEx(renderizador, textura, &rectanguloRecorte, &rectanguloEfecto, 0, nullptr, flip);
        }
    }
}

void DibujadorJuego::dibujarTexto(JuegoCliente* juegoCliente){
	SDL_SetRenderDrawColor( renderizador, 0xFF, 0xFF, 0xFF, 0xFF );

	textoDeTiempo.str( "" );
	int tiempo = juegoCliente->obtenerTiempoFaltante();
	textoDeTiempo << "Tiempo " << tiempo;

	textoDeNivel.str("");
	textoDeNivel << "Mundo " << juegoCliente->obtenerMundoActual();

	map<int,jugador_t> jugadores = juegoCliente->obtenerJugadores();
	int espacioX = 0;
	int ESPACIO = jugadores.size() == 2 ? 500 : jugadores.size() == 3 ? 250 : 170; // calcular alguna mejor forma
	SDL_Texture* texturaCorazon = cargadorTexturas->obtenerTextura("Corazon");
	for(auto const& parClaveJugador:jugadores){
		textoDePuntos.str("");
		textoDePuntos << parClaveJugador.second.nombreJugador << ": "<<parClaveJugador.second.puntos;
		SDL_Rect cuadradoPuntos = { 10 + espacioX, 10, 140, 30 };
        SDL_Rect cuadradoCorazon = { 20 + espacioX, 50, 20, 20 };
		int id = parClaveJugador.first;
		if(parClaveJugador.second.mario.recorteImagen == MARIO_GRIS){
			id = MARIO_GRIS;
		}
		renderizarTexto(cuadradoPuntos, textoDePuntos.str(), colores[id]);
        for(int i = 0; i<parClaveJugador.second.mario.vidas;i++){
            SDL_RenderCopy( renderizador, texturaCorazon, nullptr, &cuadradoCorazon);
            cuadradoCorazon.x += 25;
        }
		espacioX += ESPACIO;
	}

	SDL_Rect cuadradoTiempo = { ancho_pantalla - 130, 60, 120, 35 };
	SDL_Rect cuadradoMundo = { ancho_pantalla - 130, 10, 120, 35 };

	renderizarTexto(cuadradoTiempo, textoDeTiempo.str(), colorDefault);
	renderizarTexto(cuadradoMundo, textoDeNivel.str(), colorDefault);
}

DibujadorJuego::~DibujadorJuego(){
	delete this->recorteSpriteMario;
	delete this->recorteSpriteGoomba;
	delete this->recorteSpriteKoopa;
	delete this->recorteSpriteTuberia;
	delete this->recorteSpriteMoneda;
	delete this->recorteSpriteBloque;
    for(auto& parClaveRecorte: recorteEfectos){
        delete parClaveRecorte.second;
    }
    recorteEfectos.clear();
    clavesEfectos.clear();
}