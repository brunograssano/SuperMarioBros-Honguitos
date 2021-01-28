#include "DibujadorJuego.hpp"
#include "src/Utils/Constantes.hpp"
#include "src/Client/App/Dibujadores/Recortes/RecortePozo.hpp"

DibujadorJuego::DibujadorJuego(CargadorTexturas* cargadorTexturas,SDL_Renderer* renderizador, int ancho_pantalla,int alto_pantalla,JuegoCliente* juegoCliente){
    this->cargadorTexturas = cargadorTexturas;
    this->renderizador = renderizador;
    this->alto_pantalla = alto_pantalla;
    this->ancho_pantalla = ancho_pantalla;
    this->juegoCliente = juegoCliente;

    this->recorteSpriteMario = new RecorteMario();
    this->recorteSpriteGoomba = new RecorteGoomba();
    this->recorteSpriteKoopa = new RecorteKoopa();
    this->recorteSpriteMoneda = new RecorteMoneda();
    this->recorteSpriteBloque = new RecorteBloque();
    this->recorteSpriteTuberia = new RecorteTuberia();
    recortes[POZO_RECORTE] = new RecortePozo();

    recortes[BOLA_DE_FUEGO] = new RecorteBolaDeFuego();
    clavesEfectos[BOLA_DE_FUEGO] = CLAVE_TEXTURA_BOLA_DE_FUEGO;

    recortes[MONEDA_FLOTANTE] = new RecorteMonedaFlotante();
    clavesEfectos[MONEDA_FLOTANTE] = CLAVE_TEXTURA_MONEDA_FLOTANTE;

    recortes[CHISPA] = new RecorteChispa();
    clavesEfectos[CHISPA] = CLAVE_TEXTURA_CHISPA;

    recortes[FLOR] = new RecorteFlor();
    clavesEfectos[FLOR] = CLAVE_TEXTURA_FLOR;

    colores[-1] = {150, 150 , 150, 255}; // Gris.
    colores[0] = {230, 30 , 044, 255};   // Rojo.
	colores[1] = {69 , 230, 52 , 255};   // Verde.
	colores[2] = {179, 25 , 252, 255};   // Violeta.
	colores[3] = {76 , 225, 252, 255};   // Celeste.
}

void DibujadorJuego::dibujar(){
	rectanguloCamara = juegoCliente->obtenerCamara();
	SDL_RenderClear( renderizador );
	SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaFondo(), &rectanguloCamara, nullptr);

	dibujarPlataformas();
    dibujarFondoPozos();
    dibujarTuberias();
	dibujarMonedas();
    dibujarEnemigos();
    dibujarEfectos();
    dibujarMarios();
    dibujarPozos();
	dibujarTexto();

	SDL_RenderPresent( renderizador );
}

void DibujadorJuego::dibujarEnemigos(){
	list<entidad_t> enemigos = juegoCliente->obtenerEnemigos();
	string tipo;
	SDL_Texture* texturaEnemigo = nullptr;
	for (auto const& enemigo : enemigos) {
		SDL_Rect recorteTextura;
		if(enemigo.tipo==GOOMBA){
			recorteTextura = recorteSpriteGoomba->obtenerRecorte(enemigo.recorteX,enemigo.recorteY);
            texturaEnemigo = cargadorTexturas->obtenerTextura(CLAVE_TEXTURA_GOOMBA);
		}
		else{
			recorteTextura = recorteSpriteKoopa->obtenerRecorte(enemigo.recorteX,enemigo.recorteY);
            texturaEnemigo = cargadorTexturas->obtenerTextura(CLAVE_TEXTURA_KOOPAS);
		}

		SDL_Rect rectanguloEnemigo = {enemigo.x-rectanguloCamara.x,
									alto_pantalla - enemigo.y - ALTO_ENEMIGOS,
									ANCHO_ENEMIGOS, ALTO_ENEMIGOS};

        //SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 0x0F );
		//SDL_RenderDrawRect(renderizador, &rectanguloEnemigo);

		SDL_RenderCopyEx(renderizador,texturaEnemigo,&recorteTextura,&rectanguloEnemigo,0,
                         nullptr,enemigo.espejado?SDL_FLIP_HORIZONTAL:SDL_FLIP_NONE);
    }
}

void DibujadorJuego::dibujarPlataformas(){
	list<entidad_t> bloques = juegoCliente->obtenerBloques();
    SDL_Texture* texturaBloques = cargadorTexturas->obtenerTextura(CLAVE_TEXTURA_BLOQUES);
	for (auto const& bloque : bloques) {

		SDL_Rect rectanguloBloque = {bloque.x - rectanguloCamara.x,
									alto_pantalla - bloque.y - LARGO_BLOQUE,
									LARGO_BLOQUE, LARGO_BLOQUE};
		SDL_Rect recorteBloque = recorteSpriteBloque->obtenerRecorte(bloque.recorteX,bloque.recorteY);
		SDL_RenderCopy( renderizador, texturaBloques, &recorteBloque, &rectanguloBloque);
	}

}

void DibujadorJuego::dibujarFondoPozos() {
    list<entidad_t> pozos = juegoCliente->obtenerPozos();
    SDL_Texture* texturaFondoPozos = cargadorTexturas->obtenerTextura(CLAVE_TEXTURA_FONDO_POZO);
    for (auto const& pozo : pozos) {
        SDL_Rect rectanguloPozo = {pozo.x - rectanguloCamara.x,
                                   alto_pantalla - (int)(alto_pantalla*0.12),
                                   ANCHO_POZO, (int)(alto_pantalla*0.12)};
        SDL_Rect recortePozo = recortes[POZO_RECORTE]->obtenerRecorte(0,pozo.tipo);
        recortePozo.y += 1; // TODO acomodar o crear un nuevo recorte, agarra una parte de la imagen de arriba
        SDL_RenderCopy( renderizador, texturaFondoPozos, &recortePozo, &rectanguloPozo);
    }
}


void DibujadorJuego::dibujarPozos(){
    list<entidad_t> pozos = juegoCliente->obtenerPozos();
    SDL_Texture* texturaPozos = cargadorTexturas->obtenerTextura(CLAVE_TEXTURA_POZO);
    for (auto const& pozo : pozos) {
        SDL_Rect rectanguloPozo = {pozo.x - rectanguloCamara.x,
                                     alto_pantalla - ALTO_POZO,
                                     ANCHO_POZO, ALTO_POZO};
        SDL_Rect recortePozo = recortes[POZO_RECORTE]->obtenerRecorte(0,pozo.recorteY);
        SDL_RenderCopy( renderizador, texturaPozos, &recortePozo, &rectanguloPozo);
    }
}

void DibujadorJuego::dibujarMonedas(){
	list<entidad_t> monedas = juegoCliente->obtenerMonedas();
    SDL_Texture* texturaMoneda = cargadorTexturas->obtenerTextura(CLAVE_TEXTURA_MONEDA);
	for (auto const& moneda : monedas) {
		SDL_Rect rectanguloMoneda = {moneda.x - rectanguloCamara.x,
									alto_pantalla - moneda.y - LARGO_MONEDA,
                                     LARGO_MONEDA, LARGO_MONEDA};
		SDL_Rect recorteMoneda = recorteSpriteMoneda->obtenerRecorte(moneda.recorteX);
		SDL_RenderCopy( renderizador, texturaMoneda, &recorteMoneda, &rectanguloMoneda);
	}
}

void DibujadorJuego::dibujarTuberias() {
    list<entidad_t> tuberias = juegoCliente->obtenerTuberias();
    SDL_Texture* texturaTuberia = cargadorTexturas->obtenerTextura(CLAVE_TEXTURA_TUBERIAS);
    for (auto const& tuberia : tuberias) {
        SDL_Rect recorteTuberia = recorteSpriteTuberia->obtenerRecorte(tuberia.recorteX,tuberia.recorteY);
        SDL_Rect rectanguloTuberia = {tuberia.x - rectanguloCamara.x,
                                      alto_pantalla - recorteSpriteTuberia->obtenerAlturaParaDibujarImagen(tuberia.recorteX) - tuberia.y,
                                      recorteSpriteTuberia->obtenerAnchuraParaDibujarImagen(tuberia.recorteX),
                                      recorteSpriteTuberia->obtenerAlturaParaDibujarImagen(tuberia.recorteX)};
        SDL_RenderCopy( renderizador, texturaTuberia, &recorteTuberia, &rectanguloTuberia);
    }
}

void DibujadorJuego::dibujarMarios(){
	map<int,jugador_t> jugadores = juegoCliente->obtenerJugadores();
	int idPropio = juegoCliente->obtenerIDPropio();
	for(auto const parClaveJugador:jugadores){
		mario_t mario = parClaveJugador.second.mario;
		if(mario.idImagen != idPropio && mario.vidas != 0){
			int idMario = mario.idImagen;
			SDL_Rect rectanguloMario = {mario.posX - rectanguloCamara.x,
											alto_pantalla -ALTO_MARIO- mario.posY,
											ANCHO_MARIO, ALTO_MARIO};
			SDL_Rect recorteMario = recorteSpriteMario->obtenerRecorte(mario.recorteImagen, mario.modificador);
			if(mario.recorteImagen==MARIO_GRIS){
				idMario = mario.recorteImagen;
				recorteMario = recorteSpriteMario->obtenerRecorte(0);
			}

			SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaMario(idMario), &recorteMario, &rectanguloMario);
		}
	}

	mario_t mario = jugadores[idPropio].mario;
    if(mario.vidas != 0) {
        SDL_Rect rectanguloMario = {mario.posX - rectanguloCamara.x,alto_pantalla - ALTO_MARIO - mario.posY,
                                    ANCHO_MARIO, ALTO_MARIO};

        SDL_Rect recorteMario = recorteSpriteMario->obtenerRecorte(mario.recorteImagen, mario.modificador);
        //SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 0x0F);
        //SDL_RenderDrawRect(renderizador, &rectanguloMario);
        SDL_RenderCopy(renderizador, cargadorTexturas->obtenerTexturaMario(mario.idImagen), &recorteMario,&rectanguloMario);
    }

    /*SDL_Rect cuadradoCoordenadas = {ancho_pantalla - 130, 110, 120, 35};
    std::string coordenadas = "";
    coordenadas.append(to_string(mario.posX));
    coordenadas.append(",");
    coordenadas.append(to_string(mario.posY));
    renderizarTexto(cuadradoCoordenadas, coordenadas, colorDefault);*/
}

void DibujadorJuego::dibujarEfectos() {
    list<entidad_t> efectos = juegoCliente->obtenerEfectos();
    for (auto const& efecto : efectos) {
        if(efecto.tipo == BOLA_DE_FUEGO || efecto.tipo == CHISPA || efecto.tipo == FLOR || efecto.tipo == MONEDA_FLOTANTE) {
            SDL_Texture* textura = cargadorTexturas->obtenerTextura(clavesEfectos[efecto.tipo]);
            Recorte* recorteEfecto = recortes[efecto.tipo];
            SDL_Rect rectanguloRecorte = recorteEfecto->obtenerRecorte(efecto.recorteX);
            SDL_Rect rectanguloEfecto = {efecto.x - rectanguloCamara.x,
                                         alto_pantalla - efecto.y -
                                                 recorteEfecto->obtenerAlturaParaDibujarImagen(0),
                                         recorteEfecto->obtenerAnchuraParaDibujarImagen(0),
                                         recorteEfecto->obtenerAlturaParaDibujarImagen(0)};
            SDL_RendererFlip flip = recorteEfecto->direccion(efecto.recorteX) == DERECHA?SDL_FLIP_NONE:SDL_FLIP_HORIZONTAL; // todo usar el espejado
            SDL_RenderCopyEx(renderizador, textura, &rectanguloRecorte, &rectanguloEfecto, 0, nullptr, flip);
        }
    }
}

void DibujadorJuego::dibujarTexto(){
	SDL_SetRenderDrawColor( renderizador, 0xFF, 0xFF, 0xFF, 0xFF );

	textoDeTiempo.str( "" );
	int tiempo = juegoCliente->obtenerTiempoFaltante();
	textoDeTiempo << "Tiempo " << tiempo;

	textoDeNivel.str("");
	textoDeNivel << "Mundo " << juegoCliente->obtenerMundoActual();

	map<int,jugador_t> jugadores = juegoCliente->obtenerJugadores();
	int espacioX = 0;
	const int ESPACIO = obtenerEspaciado(jugadores.size());
	SDL_Texture* texturaCorazon = cargadorTexturas->obtenerTextura(CLAVE_TEXTURA_CORAZON);
	for(auto const& parClaveJugador:jugadores){
		textoDePuntos.str("");
		textoDePuntos << parClaveJugador.second.nombreJugador << ": "<<parClaveJugador.second.mario.puntos;
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
    for(auto& parClaveRecorte: recortes){
        delete parClaveRecorte.second;
    }
    recortes.clear();
    clavesEfectos.clear();
}

int DibujadorJuego::obtenerEspaciado(int cantidadJugadores) { // TODO HACER QUE SE ACOMODEN LOS VALORES DE ACUERDO AL ANCHO PANTALLA
    return cantidadJugadores == 2 ? 500 : cantidadJugadores == 3 ? 250 : 170;
}
