
#include "src/Client/App/ManejadorSDL.hpp"
#include "DibujadorPuntos.hpp"

DibujadorPuntos::DibujadorPuntos(CargadorTexturas* cargadorTexturas, SDL_Renderer* renderizador, int ancho_pantalla, int alto_pantalla, JuegoCliente* juegoCliente) {
    nivelAMostrarPuntos = 0;
    this->alto_pantalla = alto_pantalla;
    this->ancho_pantalla = ancho_pantalla;
    this->cargadorTexturas = cargadorTexturas;
    this->renderizador = renderizador;

    this->botonIzquierdo = new BotonConTexto(ancho_pantalla/4 - 200/2 - 25 - 40 ,175,40,40, "<<", renderizador, cargarFuente("resources/Fuentes/fuenteSuperMarioBros.ttf", 12));
    this->botonDerecho = new BotonConTexto(ancho_pantalla/4 - 200/2- 25 + 250,175,40,40, ">>", renderizador, cargarFuente("resources/Fuentes/fuenteSuperMarioBros.ttf", 12));
    this->juegoCliente = juegoCliente;

    colores[-1] = {150, 150 , 150, 255}; // Gris.
    colores[0] = {230, 30 , 044, 255}; // Rojo.
    colores[1] = {69 , 230, 52 , 255}; // Verde.
    colores[2] = {179, 25 , 252, 255}; // Violeta.
    colores[3] = {76 , 225, 252, 255}; // Celeste.
}

void DibujadorPuntos::aumentarNivelAMostrarPuntos (int ultimoNivel){
    if(nivelAMostrarPuntos < ultimoNivel){
        nivelAMostrarPuntos++;
    }else{
        nivelAMostrarPuntos = 0;
    }
}

void DibujadorPuntos::disminuirNivelAMostrarPuntos(int ultimoNivel){
    if(nivelAMostrarPuntos > 0){
        nivelAMostrarPuntos--;
    }else{
        nivelAMostrarPuntos = ultimoNivel;
    }
}

void DibujadorPuntos::dibujar() {
    botonIzquierdo->mostrarse();
    botonDerecho->mostrarse();
    int ultimoNivel = juegoCliente->obtenerNivelesJugados()-1;

    if (botonIzquierdo->botonClickeado(eventoMouse)) {
        this->disminuirNivelAMostrarPuntos(ultimoNivel);
        eventoMouse.type = 0;
    } else if (botonDerecho->botonClickeado(eventoMouse)) {
        this->aumentarNivelAMostrarPuntos(ultimoNivel);
        eventoMouse.type = 0;
    }

    if(nivelAMostrarPuntos == 0){
        dibujarPuntosTotales(juegoCliente);
    }else {
        dibujarPuntosDelNivel(juegoCliente);
    }
}

void DibujadorPuntos::dibujarPuntosTotales(JuegoCliente *juegoCliente) {

    int ancho_puntosJugador = 200;
    int alto_puntosJugador = 30;
    int desfase_puntosJugador = 50;
    SDL_Rect cuadradoPuntos;

    std::stringstream puntosJugador;

    dibujarRectanguloPuntos(ancho_puntosJugador,alto_puntosJugador,desfase_puntosJugador);

    std::stringstream tituloPuntos;
    tituloPuntos << "Puntos totales";

    SDL_Rect cuadradoTituloPuntos = {ancho_pantalla/4 - ancho_puntosJugador/2,
                                     alto_pantalla/2 - alto_puntosJugador/2 + desfase_puntosJugador - 150,
                                     ancho_puntosJugador,
                                     alto_puntosJugador};

    renderizarTexto(cuadradoTituloPuntos, tituloPuntos.str(), colorDefault);

    std::map<int, jugador> jugadores = juegoCliente->obtenerJugadores();
    podio_t podio = juegoCliente->obtenerPodioPuntosAcumulados();
    int cantidadJugadores = jugadores.size();

    for (int indiceJugador = 0; indiceJugador < cantidadJugadores; indiceJugador++){
        int idJugador = podio.ids[indiceJugador];
        jugador_t  jugador = jugadores[idJugador];
        puntosJugador.str("");
        std::string nombreJugador = jugador.nombreJugador;
        puntosJugador << "Puntos de "<< nombreJugador <<": " << podio.puntosNivel[indiceJugador];

        cuadradoPuntos = {ancho_pantalla/4 - ancho_puntosJugador/2,
                          alto_pantalla/2 - alto_puntosJugador/2 + desfase_puntosJugador - 100,
                          ancho_puntosJugador,
                          alto_puntosJugador};

        int idColor = idJugador;

        if(jugador.mario.recorteImagen == MARIO_GRIS){
            idColor = MARIO_GRIS;
        }

        renderizarTexto(cuadradoPuntos, puntosJugador.str(), colores[idColor]);
        desfase_puntosJugador +=40;
    }

}

void DibujadorPuntos::dibujarPuntosDelNivel(JuegoCliente *juegoCliente) {
    int ancho_puntosJugador = 200;
    int alto_puntosJugador = 30;
    int desfase_puntosJugador = 50;
    SDL_Rect cuadradoPuntos;
    std::stringstream puntosJugador;
    std::stringstream tituloPuntos;

    dibujarRectanguloPuntos(ancho_puntosJugador, alto_puntosJugador, desfase_puntosJugador);

    podio_t podio = juegoCliente->obtenerPodios().at(nivelAMostrarPuntos);
    tituloPuntos << "Puntos nivel " <<std::to_string(podio.nivel);

    SDL_Rect cuadradoTituloPuntos = {ancho_pantalla/4 - ancho_puntosJugador/2,
                                     alto_pantalla/2 - alto_puntosJugador/2 + desfase_puntosJugador - 150,
                                     ancho_puntosJugador,
                                     alto_puntosJugador};


    renderizarTexto(cuadradoTituloPuntos, tituloPuntos.str(), colorDefault);

    std::map<int, jugador> jugadores = juegoCliente->obtenerJugadores();
    int cantidadJugadores = jugadores.size();

    for (int indiceJugador = 0; indiceJugador < cantidadJugadores; indiceJugador++){
        puntosJugador.str("");
        int idJugador = podio.ids[indiceJugador];
        jugador_t  jugador = jugadores[idJugador];

        std::string nombreJugador = jugador.nombreJugador;
        puntosJugador << "Puntos de "<< nombreJugador <<": " << podio.puntosNivel[indiceJugador];

        cuadradoPuntos = {ancho_pantalla/4 - ancho_puntosJugador/2,
                          alto_pantalla/2 - alto_puntosJugador/2 + desfase_puntosJugador - 100,
                          ancho_puntosJugador,
                          alto_puntosJugador};

        int idColor = idJugador;

        if( jugador.mario.recorteImagen == MARIO_GRIS){
            idColor = MARIO_GRIS;
        }

        renderizarTexto(cuadradoPuntos, puntosJugador.str(), colores[idColor]);

        desfase_puntosJugador +=40;
    }
}


void DibujadorPuntos::agregarEventoDeClick(SDL_Event eventoClick) {
    this->eventoMouse = eventoClick;
}

void DibujadorPuntos::renderizarTexto(SDL_Rect renderQuad, std::string textoAMostrar, SDL_Color color){
    SDL_Rect* clip = nullptr;
    double angle = 0.0;
    SDL_Point* center = nullptr;
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    SDL_SetRenderDrawColor(renderizador, colorDefault.r, colorDefault.g, colorDefault.b, colorDefault.a);

    SDL_Texture* texto = cargadorTexturas->cargarFuenteDeTextoATextura(textoAMostrar, renderizador, color);

    SDL_RenderCopyEx( renderizador, texto, clip, &renderQuad, angle, center, flip );
    destructorDeTexturas(texto);

}

void DibujadorPuntos::dibujarRectanguloPuntos(int ancho_puntosJugador,int alto_puntosJugador, int desfase_puntosJugador ){
    SDL_Rect rectanguloTransparente = {ancho_pantalla/4 - ancho_puntosJugador/2 - 25,
                                       alto_pantalla/2 - alto_puntosJugador/2 + desfase_puntosJugador - 150 - 25,
                                       ancho_puntosJugador + 50,
                                       (alto_puntosJugador + desfase_puntosJugador)*4+50};
    SDL_SetRenderDrawBlendMode(renderizador, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderizador, 220, 220, 220, 120);
    SDL_RenderFillRect(renderizador, &rectanguloTransparente);
}


DibujadorPuntos::~DibujadorPuntos(){
    delete this->botonIzquierdo;
    delete this->botonDerecho;
}
