#include "DibujadorJuego.hpp"
#include "src/Utils/Constantes.hpp"
#include "src/Client/App/Dibujadores/Recortes/RecortePozo.hpp"
#include "src/Client/App/Dibujadores/Recortes/RecorteMario.hpp"
#include "src/Client/App/Dibujadores/Recortes/RecorteKoopa.hpp"
#include "src/Client/App/Dibujadores/Recortes/RecorteGoomba.hpp"
#include "src/Client/App/Dibujadores/Recortes/RecorteMoneda.hpp"
#include "src/Client/App/Dibujadores/Recortes/RecorteBloque.hpp"
#include "src/Client/App/Dibujadores/Recortes/RecorteBolaDeFuego.hpp"
#include "src/Client/App/Dibujadores/Recortes/RecorteChispa.hpp"
#include "src/Client/App/Dibujadores/Recortes/RecorteFlor.hpp"
#include "src/Client/App/Dibujadores/Recortes/RecorteMonedaFlotante.hpp"
#include "src/Client/App/Dibujadores/Recortes/RecorteTuberia.hpp"

#define ESPACIADO_VIDA 25
#define GRIS (-1)
#define ROJO 0
#define VERDE 1
#define VIOLETA 2
#define CELESTE 3

DibujadorJuego::DibujadorJuego(CargadorTexturas* cargadorTexturas, SDL_Renderer* renderizador, int ancho_pantalla, int alto_pantalla, JuegoCliente* juegoCliente){
    this->cargadorTexturas = cargadorTexturas;
    this->renderizador = renderizador;
    this->alto_pantalla = alto_pantalla;
    this->ancho_pantalla = ancho_pantalla;
    this->juegoCliente = juegoCliente;

    recortes[MARIO_RECORTE] = new RecorteMario();

    recortes[POZO_RECORTE] = new RecortePozo();
    clavesTexturas[POZO_RECORTE] = CLAVE_TEXTURA_POZO;

    recortes[TUBERIA_RECORTE] = new RecorteTuberia();
    clavesTexturas[TUBERIA_RECORTE] = CLAVE_TEXTURA_TUBERIAS;

    recortes[BLOQUE_RECORTE] = new RecorteBloque();
    clavesTexturas[BLOQUE_RECORTE] = CLAVE_TEXTURA_BLOQUES;

    recortes[MONEDA_RECORTE] = new RecorteMoneda();
    clavesTexturas[MONEDA_RECORTE] = CLAVE_TEXTURA_MONEDA;

    recortes[KOOPA_RECORTE] = new RecorteKoopa();
    clavesTexturas[KOOPA_RECORTE] = CLAVE_TEXTURA_KOOPAS;

    recortes[GOOMBA_RECORTE] = new RecorteGoomba();
    clavesTexturas[GOOMBA_RECORTE] = CLAVE_TEXTURA_GOOMBA;

    recortes[BOLA_DE_FUEGO] = new RecorteBolaDeFuego();
    clavesTexturas[BOLA_DE_FUEGO] = CLAVE_TEXTURA_BOLA_DE_FUEGO;

    recortes[MONEDA_FLOTANTE] = new RecorteMonedaFlotante();
    clavesTexturas[MONEDA_FLOTANTE] = CLAVE_TEXTURA_MONEDA_FLOTANTE;

    recortes[CHISPA] = new RecorteChispa();
    clavesTexturas[CHISPA] = CLAVE_TEXTURA_CHISPA;

    recortes[FLOR] = new RecorteFlor();
    clavesTexturas[FLOR] = CLAVE_TEXTURA_FLOR;

    colores[GRIS] = {150, 150 , 150, 255}; // Gris.
    colores[ROJO] = {230, 30 , 044, 255};   // Rojo.
	colores[VERDE] = {69 , 230, 52 , 255};   // Verde.
	colores[VIOLETA] = {179, 25 , 252, 255};   // Violeta.
	colores[CELESTE] = {76 , 225, 252, 255};   // Celeste.
}

void DibujadorJuego::dibujar(){
	rectanguloCamara = juegoCliente->obtenerCamara();
	SDL_RenderClear( renderizador );
	SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaFondo(), &rectanguloCamara, nullptr);

	dibujar(BLOQUE_RECORTE,&DibujadorJuego::dibujadorSimple_helper);
    dibujar(POZO_RECORTE,&DibujadorJuego::dibujadorFondoPozo_helper);
    dibujar(TUBERIA_RECORTE,&DibujadorJuego::dibujadorSimple_helper);
	dibujar(MONEDA_RECORTE,&DibujadorJuego::dibujadorSimple_helper);
    dibujar(ENEMIGOS_RECORTE,&DibujadorJuego::dibujadorEnemigos_helper);
    dibujar(EFECTOS_RECORTE,&DibujadorJuego::dibujadorEfectos_helper);
    dibujarMarios();
    dibujar(POZO_RECORTE,&DibujadorJuego::dibujadorSimple_helper);
	dibujarTexto();

	SDL_RenderPresent( renderizador );
}

void DibujadorJuego::dibujar(int claveEntidad, FuncionParaDibujar funcion){
    std::list<entidad_t> entidades = juegoCliente->obtenerEntidad(claveEntidad);
    SDL_Texture* textura = cargadorTexturas->obtenerTextura(clavesTexturas[claveEntidad]);
    for (auto const& entidad : entidades) {
        funcion(this, &claveEntidad, textura, (void *) &entidad);
    }
}

void DibujadorJuego::dibujadorSimple_helper(void *dibujador, void *claveEntidad, void *textura, void *entidad) {
    ((DibujadorJuego *) dibujador)->dibujadorSimple((int*)claveEntidad, (SDL_Texture *) textura, (entidad_t*)entidad);
}

void DibujadorJuego::dibujadorSimple(int* claveEntidad, SDL_Texture *textura, entidad_t *entidad) {
    const int alto = recortes[*claveEntidad]->obtenerAlturaParaDibujarImagen(entidad->tipo);
    const int ancho = recortes[*claveEntidad]->obtenerAnchuraParaDibujarImagen(entidad->tipo);
    SDL_Rect posicionEnPantalla = {entidad->x - rectanguloCamara.x,alto_pantalla - entidad->y - alto,ancho, alto};
    SDL_Rect recorteImagen = recortes[*claveEntidad]->obtenerRecorte(entidad->recorteX, entidad->recorteY);
    SDL_RenderCopy(renderizador, textura, &recorteImagen, &posicionEnPantalla);
}

void DibujadorJuego::dibujadorFondoPozo_helper(void *dibujador, void *claveEntidad, void *textura, void *entidad) {
    ((DibujadorJuego *) dibujador)->dibujadorFondoPozo((int*)claveEntidad, (SDL_Texture *) textura, (entidad_t*)entidad);
}

void DibujadorJuego::dibujadorFondoPozo(int* claveEntidad, SDL_Texture *textura, entidad_t *entidad) {
    textura = cargadorTexturas->obtenerTextura(CLAVE_TEXTURA_FONDO_POZO);
    SDL_Rect posicionEnPantalla = {entidad->x - rectanguloCamara.x,alto_pantalla - (int)(alto_pantalla*0.12),
                                   ANCHO_POZO, (int)(alto_pantalla*0.12)};
    SDL_Rect recorteImagen = recortes[POZO_RECORTE]->obtenerRecorte(0,entidad->tipo);
    recorteImagen.y += 1; // TODO acomodar o crear un nuevo recorte, agarra una parte de la imagen de arriba
    SDL_RenderCopy(renderizador, textura, &recorteImagen, &posicionEnPantalla);
}

void DibujadorJuego::dibujadorEfectos_helper(void *dibujador, void *claveEntidad, void *textura, void *entidad) {
    ((DibujadorJuego *) dibujador)->dibujadorEfectos((int*)claveEntidad, (SDL_Texture *) textura, (entidad_t*)entidad);
}

void DibujadorJuego::dibujadorEfectos(int* claveEntidad, SDL_Texture *textura, entidad_t *entidad) {
    const int alto = recortes[entidad->tipo]->obtenerAlturaParaDibujarImagen(0);
    const int ancho =recortes[entidad->tipo]->obtenerAnchuraParaDibujarImagen(0);
    SDL_Rect rectanguloRecorte = recortes[entidad->tipo]->obtenerRecorte(entidad->recorteX);
    SDL_Rect rectanguloEfecto = {entidad->x - rectanguloCamara.x,alto_pantalla - entidad->y - alto, ancho, alto};
    textura = cargadorTexturas->obtenerTextura(clavesTexturas[entidad->tipo]);
    SDL_RendererFlip flip = entidad->espejado?SDL_FLIP_HORIZONTAL:SDL_FLIP_NONE;
    SDL_RenderCopyEx(renderizador, textura, &rectanguloRecorte, &rectanguloEfecto, 0, nullptr, flip);
}


void DibujadorJuego::dibujadorEnemigos_helper(void *dibujador, void *claveEntidad, void *textura, void *entidad) {
    ((DibujadorJuego *) dibujador)->dibujadorEnemigos((int*)claveEntidad, (SDL_Texture *) textura, (entidad_t*)entidad);
}

void DibujadorJuego::dibujadorEnemigos(int* claveEntidad, SDL_Texture *textura, entidad_t *entidad) {
    Recorte* recorte;
    if(entidad->tipo==GOOMBA){
        recorte = recortes[GOOMBA_RECORTE];
        textura = cargadorTexturas->obtenerTextura(CLAVE_TEXTURA_GOOMBA);
    }
    else{
        recorte = recortes[KOOPA_RECORTE];
        textura = cargadorTexturas->obtenerTextura(CLAVE_TEXTURA_KOOPAS);
    }
    const int alto = recorte->obtenerAlturaParaDibujarImagen(entidad->tipo);
    const int ancho = recorte->obtenerAnchuraParaDibujarImagen(entidad->tipo);
    SDL_Rect posicionEnPantalla = {entidad->x - rectanguloCamara.x,alto_pantalla - entidad->y - alto,ancho, alto};
    SDL_Rect recorteImagen = recorte->obtenerRecorte(entidad->recorteX, entidad->recorteY);
    SDL_RenderCopyEx(renderizador,textura,&recorteImagen,&posicionEnPantalla,0,nullptr,
                     entidad->espejado?SDL_FLIP_HORIZONTAL:SDL_FLIP_NONE);
}

void DibujadorJuego::dibujarMarios(){
    std::map<int,jugador_t> jugadores = juegoCliente->obtenerJugadores();
	int idPropio = juegoCliente->obtenerIDPropio();
	for(auto const parClaveJugador:jugadores){
		mario_t mario = parClaveJugador.second.mario;
		if(mario.idImagen != idPropio && mario.vidas != 0){
			int idMario = mario.idImagen;
			SDL_Rect rectanguloMario = {mario.posX - rectanguloCamara.x,
											alto_pantalla -ALTO_MARIO- mario.posY,
											ANCHO_MARIO, ALTO_MARIO};
			SDL_Rect recorteMario = recortes[MARIO_RECORTE]->obtenerRecorte(mario.recorteImagen, mario.modificador);
			if(mario.recorteImagen==MARIO_GRIS){
				idMario = mario.recorteImagen;
				recorteMario = recortes[MARIO_RECORTE]->obtenerRecorte(0);
			}

			SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaMario(idMario), &recorteMario, &rectanguloMario);
		}
	}

	mario_t mario = jugadores[idPropio].mario;
    if(mario.vidas != 0) {
        SDL_Rect rectanguloMario = {mario.posX - rectanguloCamara.x,alto_pantalla - ALTO_MARIO - mario.posY,
                                    ANCHO_MARIO, ALTO_MARIO};

        SDL_Rect recorteMario = recortes[MARIO_RECORTE]->obtenerRecorte(mario.recorteImagen, mario.modificador);
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

void DibujadorJuego::dibujarTexto(){
    std::map<int,jugador_t> jugadores = juegoCliente->obtenerJugadores();
    const int ESPACIADO_NOMBRES = obtenerEspaciado(jugadores.size());

	SDL_SetRenderDrawColor( renderizador, 0xFF, 0xFF, 0xFF, 0xFF );
	textoDeTiempo.str( "" );
	int tiempo = juegoCliente->obtenerTiempoFaltante();
	textoDeTiempo << "Tiempo " << tiempo;

	textoDeNivel.str("");
	textoDeNivel << "Mundo " << juegoCliente->obtenerMundoActual();

	int espacioX = 0;
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
            cuadradoCorazon.x += ESPACIADO_VIDA;
        }
		espacioX += ESPACIADO_NOMBRES;
	}

	SDL_Rect cuadradoTiempo = { ancho_pantalla - 130, 60, 120, 35 };
	SDL_Rect cuadradoMundo = { ancho_pantalla - 130, 10, 120, 35 };
	renderizarTexto(cuadradoTiempo, textoDeTiempo.str(), colorDefault);
	renderizarTexto(cuadradoMundo, textoDeNivel.str(), colorDefault);
}

int DibujadorJuego::obtenerEspaciado(int cantidadJugadores) { // TODO HACER QUE SE ACOMODEN LOS VALORES DE ACUERDO AL ANCHO PANTALLA
    return cantidadJugadores == 2 ? 500 : cantidadJugadores == 3 ? 250 : 170;
}

DibujadorJuego::~DibujadorJuego(){
    for(auto& parClaveRecorte: recortes){
        delete parClaveRecorte.second;
    }
    recortes.clear();
    clavesTexturas.clear();
}
