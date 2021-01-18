
#include "DibujadorPuntos.hpp"

DibujadorPuntos::DibujadorPuntos(CargadorTexturas* cargadorTexturas, SDL_Renderer* renderizador, int ancho_pantalla, int alto_pantalla) {
    nivelAMostrarPuntos = 0;
    this->alto_pantalla = alto_pantalla;
    this->ancho_pantalla = ancho_pantalla;
    this->cargadorTexturas = cargadorTexturas;
    this->renderizador = renderizador;

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

void DibujadorPuntos::dibujarPuntos(JuegoCliente *juegoCliente) {
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

    stringstream puntosJugador;

    dibujarRectanguloPuntos(ancho_puntosJugador,alto_puntosJugador,desfase_puntosJugador);

    stringstream tituloPuntos;
    tituloPuntos << "Puntos totales";

    SDL_Rect cuadradoTituloPuntos = {ancho_pantalla/4 - ancho_puntosJugador/2,
                                     alto_pantalla/2 - alto_puntosJugador/2 + desfase_puntosJugador - 150,
                                     ancho_puntosJugador,
                                     alto_puntosJugador};

    renderizarTexto(cuadradoTituloPuntos, tituloPuntos.str().c_str(), colorDefault);
    int indiceJugador = 0;
    for (auto const& parIdJugador : juegoCliente->obtenerJugadores()){

        podio_t podio = juegoCliente->obtenerPodioPuntosAcumulados();
        puntosJugador.str("");
        //int id;
        string nombreJugador = juegoCliente->obtenerJugadores()[podio.ids[indiceJugador]].nombreJugador;
        puntosJugador << "Puntos de "<< nombreJugador <<": " << podio.puntosNivel[indiceJugador];

        cuadradoPuntos = {ancho_pantalla/4 - ancho_puntosJugador/2,
                          alto_pantalla/2 - alto_puntosJugador/2 + desfase_puntosJugador - 100,
                          ancho_puntosJugador,
                          alto_puntosJugador};

        int idColor = podio.ids[indiceJugador];

        if( juegoCliente->obtenerJugadores()[podio.ids[indiceJugador]].mario.recorteImagen == MARIO_GRIS){
            idColor = MARIO_GRIS;
        }

        renderizarTexto(cuadradoPuntos, puntosJugador.str().c_str(), colores[idColor]);

        desfase_puntosJugador +=40;
        indiceJugador++;
    }

}

void DibujadorPuntos::dibujarPuntosDelNivel(JuegoCliente *juegoCliente) {
    int ancho_puntosJugador = 200;
    int alto_puntosJugador = 30;
    int desfase_puntosJugador = 50;
    SDL_Rect cuadradoPuntos;

    dibujarRectanguloPuntos(ancho_puntosJugador, alto_puntosJugador, desfase_puntosJugador);

    stringstream puntosJugador;

    stringstream tituloPuntos;
    tituloPuntos << "Puntos nivel " <<to_string(this->nivelAMostrarPuntos);

    SDL_Rect cuadradoTituloPuntos = {ancho_pantalla/4 - ancho_puntosJugador/2,
                                     alto_pantalla/2 - alto_puntosJugador/2 + desfase_puntosJugador - 150,
                                     ancho_puntosJugador,
                                     alto_puntosJugador};


    renderizarTexto(cuadradoTituloPuntos, tituloPuntos.str().c_str(), colorDefault);
    int indiceJugador = 0;
    for (auto const& parIdJugador : juegoCliente->obtenerJugadores()){

        podio_t podio = juegoCliente->obtenerPodios().at(nivelAMostrarPuntos);
        puntosJugador.str("");
        //int id;
        string nombreJugador = juegoCliente->obtenerJugadores()[podio.ids[indiceJugador]].nombreJugador;
        puntosJugador << "Puntos de "<< nombreJugador <<": " << podio.puntosNivel[indiceJugador];

        cuadradoPuntos = {ancho_pantalla/4 - ancho_puntosJugador/2,
                          alto_pantalla/2 - alto_puntosJugador/2 + desfase_puntosJugador - 100,
                          ancho_puntosJugador,
                          alto_puntosJugador};

        int idColor = podio.ids[indiceJugador];

        if( juegoCliente->obtenerJugadores()[podio.ids[indiceJugador]].mario.recorteImagen == MARIO_GRIS){
            idColor = MARIO_GRIS;
        }

        renderizarTexto(cuadradoPuntos, puntosJugador.str().c_str(), colores[idColor]);

        desfase_puntosJugador +=40;
        indiceJugador++;
    }


}

void DibujadorPuntos::renderizarTexto(SDL_Rect renderQuad, string textoAMostrar, SDL_Color color){
    SDL_Rect* clip = NULL;
    double angle = 0.0;
    SDL_Point* center = NULL;
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    SDL_SetRenderDrawColor(renderizador, colorDefault.r, colorDefault.g, colorDefault.b, colorDefault.a);

    SDL_Texture* texto = cargadorTexturas->cargarFuenteDeTextoATextura(textoAMostrar, renderizador, color);

    SDL_RenderCopyEx( renderizador, texto, clip, &renderQuad, angle, center, flip );
    destructorDeTexturas(texto);

};

void DibujadorPuntos::dibujarRectanguloPuntos(int ancho_puntosJugador,int alto_puntosJugador, int desfase_puntosJugador ){
    SDL_Rect rectanguloTransparente = {ancho_pantalla/4 - ancho_puntosJugador/2 - 25,
                                       alto_pantalla/2 - alto_puntosJugador/2 + desfase_puntosJugador - 150 - 25,
                                       ancho_puntosJugador + 50,
                                       (alto_puntosJugador + desfase_puntosJugador)*4+50};
    SDL_SetRenderDrawBlendMode(renderizador, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderizador, 220, 220, 220, 120);
    SDL_RenderFillRect(renderizador, &rectanguloTransparente);
}

void DibujadorPuntos::dibujarPuntosTotalesGameOver(JuegoCliente *juegoCliente) {

    int ancho_puntosJugador = 200;
    int alto_puntosJugador = 30;
    int desfase_puntosJugador = 50;
    SDL_Rect cuadradoPuntos;

    stringstream puntosJugador;

    dibujarRectanguloPuntos(ancho_puntosJugador,alto_puntosJugador,desfase_puntosJugador);

    stringstream tituloPuntos;
    tituloPuntos << "Puntos totales";

    SDL_Rect cuadradoTituloPuntos = {ancho_pantalla/4 - ancho_puntosJugador/2,
                                     alto_pantalla/2 - alto_puntosJugador/2 + desfase_puntosJugador - 150,
                                     ancho_puntosJugador,
                                     alto_puntosJugador};

    renderizarTexto(cuadradoTituloPuntos, tituloPuntos.str().c_str(), colorDefault);
    int indiceJugador = 0;
    for (auto const& parIdJugador : juegoCliente->obtenerJugadores()){

        puntosJugador.str("");
        //int id;
        string nombreJugador = parIdJugador.second.nombreJugador;
        puntosJugador << "Puntos de "<< nombreJugador <<": " << parIdJugador.second.puntos;

        cuadradoPuntos = {ancho_pantalla/4 - ancho_puntosJugador/2,
                          alto_pantalla/2 - alto_puntosJugador/2 + desfase_puntosJugador - 100,
                          ancho_puntosJugador,
                          alto_puntosJugador};

        int idColor = parIdJugador.second.mario.idImagen;

        if( parIdJugador.second.mario.recorteImagen == MARIO_GRIS){
            idColor = MARIO_GRIS;
        }

        renderizarTexto(cuadradoPuntos, puntosJugador.str().c_str(), colores[idColor]);

        desfase_puntosJugador +=40;
        indiceJugador++;
    }

}

void DibujadorPuntos::dibujarPuntosGameOver(JuegoCliente *juegoCliente) {
    if(nivelAMostrarPuntos == 0){
        dibujarPuntosTotalesGameOver(juegoCliente);
    }else {
        dibujarPuntosDelNivel(juegoCliente);
    }
}
