#!/bin/bash

function mostrarBannerMensajeInicial() {
  clear
  echo "================================================="
  echo "=              SUPER MARIO BROS                 ="
  echo "=                by Honguitos                   ="
  echo "================================================="
  echo ""
}

function mostrarAyuda() {
  echo "    ▒▒▒▒▒       Opciones:"
  echo "  ▒▒▒▒▒▒▒▒▒       d: Instala solamente dependencias necesarias."
  echo "  ▓▓▓░░▓░         i: Instala el juego sin las dependencias"
  echo " ▓░▓░░░▓░░░       a: Instala todo lo necesario"
  echo " ▓░▓▓░░░▓░░░      u: Desinstala el juego."
  echo " ▓▓░░░░▓▓▓▓       h: Muestra esta ayuda."
  echo "  ░░░░░░░░        q: Cierra el instalador."
  echo "  ▓▓▒▓▓▓▒▓▓"
  echo " ▓▓▓▒▓▓▓▒▓▓▓"
  echo "▓▓▓▓▒▒▒▒▒▓▓▓▓"
  echo "░░▓▒░▒▒▒░▒▓░░"
  echo "░░░▒▒▒▒▒▒▒░░░"
  echo "░░▒▒▒▒▒▒▒▒▒░░"
  echo "  ▒▒▒   ▒▒▒"
  echo " ▓▓▓    ▓▓▓"
  echo "▓▓▓▓    ▓▓▓▓"
}

function instalarDependencias() {
  echo "~~~~~~~ INSTALANDO DEPENDENCIAS ~~~~~~~"
  echo ""
  echo "1/5 >> Instalando CMake"
  sudo apt-get install cmake
  echo ""
  echo "2/5 >> Instalando SDL2"
  sudo apt-get install libsdl2-dev
  echo ""
  echo "3/5 >> Instalando SDL2 Image"
  sudo apt-get install libsdl2-image-dev
  echo ""
  echo "4/5 >> Instalando SDL2 TTF"
  sudo apt-get install libsdl2-ttf-dev
  echo ""
  echo "5/5 >> Instalando SDL2 Mixer"
  sudo apt-get install libsdl2-mixer-dev
  echo ""
  echo "Termino la instalacion de dependencias"
  echo ""
}

function instalarJuego() {
  echo "~~~~~~~ INSTALACIÓN DEL JUEGO ~~~~~~~"
  echo "1/6 >> Sacando carpeta anterior"
  sudo rm -rf build
  echo "2/6 >> Creando directorio para compilar"
  mkdir build
  echo "3/6 >> Moviendose"
  cd build || (echo "Ocurrio un error durante la instalacion. Terminando"  && exit)
  echo "4/6 >> Usando CMake"
  cmake ..
  echo "5/6 >> Copiando recursos"
  cp -r "../resources" "resources"
  echo "6/6 >> Compilando"
  sudo make
  echo ""
  echo "Se instalo el juego."
  echo ""
}

function desinstalar() {
  echo "~~~~~~~ DESINSTALADOR ~~~~~~~"
  echo "1/1"
  sudo rm -rf build
  echo ""
  echo "Se desinstalo el juego."
  echo ""
}

mostrarBannerMensajeInicial
mostrarAyuda
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
printf "> Ingrese una opción: "

while true; do
  read opcion
  clear
  mostrarBannerMensajeInicial
  echo ""
  case $opcion in
  d)
    instalarDependencias
    ;;
  i)
    instalarJuego
    ;;
  a)
    instalarDependencias
    instalarJuego
    ;;
  u)
    desinstalar
    ;;
  h)
    mostrarAyuda
    ;;
  m)
    comoJugar
    ;;
  q)
    echo "Saliendo del instalador."
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    exit 0
    ;;
  *)
    echo "Ingreso una opcion que no es valida. Puede ver ayuda con 'h'."
    ;;
  esac
  echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
  printf "> Ingrese una opción: "
done
