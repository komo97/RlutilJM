/* rlutilJM
* Biblioteca especializada para crear videojuegos en consola de windows.
* No es compatible con otro sistema operativo.
*
* Utiliza SFML para audios.
* Utilizar la siguiente guía para inicializar el proyecto https://www.sfml-dev.org/tutorials/2.3/start-vc.php
* Todos los archivos utilizados han sido modificados.
*
* Utiliza rlutil de Tapio Vierros.
*
* Licencia:
* This software is provided 'as-is', without any express or implied warranty.
* In no event will the authors be held liable for any damages arising from
* the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:

* 1. The origin of this software must not be misrepresented; you must not claim
* that you wrote the original software. If you use this software in a product,
* an acknowledgment in the product documentation would be appreciated but is
* not required.
*
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
*
* 3. This notice may not be removed or altered from any source distribution.
*
* José María Pérez Parrillat 2016
*/


#pragma once
#ifndef _RLUTILJM_H_
#define _RLUTILJM_H_
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <Windows.h>
#include <Wincon.h>
#include <mmsystem.h>
#include <iostream>
#include "rlutil.h"
#include "SFML\System.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Network.hpp"
#define _CRT_SECURE_NO_WARNINGS

#pragma region Structs
//Estructura base para cada entidad en el juego.
//Contiene su posicion (que es el punto m疽 alto izquierdo del rectangulo sprite).
//Su vida, su ataque y su velocidad, sus 4 canales de color,
//sus 4 canales de background, su arma,
//y un pointer a su sprite, SE TIENE QUE DECLARAR DESPUES.
//No se tienen que llenar todos los rubros.
//NO SOBREESCRIBIR DIRECTAMENTE, LLENAR LOS PARAMETROS USANDO FUNCIONES, DE ESTA MANERA
//SE EVITAN PROBLEMAS BASICOS
typedef struct stats {
	int x, y;
	int life;
	int attack;
	int speed;
	int** sprite;
	int alive;
	int color1, color2, color3, color4;
	int weapon;
	char letter1, letter2, letter3, letter4, charWeapon;
	int bg1, bg2, bg3, bg4;
	int spriteSizeX, spriteSizeY;
	int type;
}stats;

//Cada buffer de CMD es un tile que tiene 3 propiedades. Un color de letra, un color de fondo y una letra
//No llamar nunca.
typedef struct tile
{
	int colorVal;
	int backVal;
	char letVal;
	int ocupant;
}tile;

//Estructura especifica para las barras. Para inicializarlas de forma diferente
typedef struct bar
{
	int x, y;
	int currValue, maxValue;
	int color1, color2, color3, constraint;
	int spriteSizeX, spriteSizeY;
	int percent;
}bar;
#pragma endregion


using namespace rlutil;
//Bloques
#pragma region Defines
#define CLEAR 0
#define FLOOR1 1
#define FLOOR2 (1<<1)
#define FLOOR3 (1<<2)
#define FLOOR4 (1<<3)
#define BACKGROUND1 2
#define BACKGROUND2 (2<<1)
#define BACKGROUND3 (2<<2)
#define BACKGROUND4 (2<<3)
#define BAR1 3
#define BAR2 (3<<1)
#define BAR3 (3<<2)
#define BARCONSTRAINTS (3<<3)
#define CHARACTER1 (4<<1)
#define CHARACTER2 (4<<2)
#define CHARACTER3 (4<<3)
#define CHARACTER4 (4<<4)
#define WEAPON (4<<5)
#define EMPTY 5
#define DIRRIGHT 1
#define DIRLEFT -1
#define DIRUP 1
#define DIRDOWN -1
#define NOMOVE 0
#define CHARACTER 0x0001
#define BACKGROUND 0x0002
#define BAR 0x0003
#define TEXT 0x0004  
#pragma endregion


///<summary>Llamar para mantener el aspecto de la pantalla una vez cada frame al inicio</summary>
void KeepScreenSize();

///<summary>
///Cambia el tama de la pantalla. Llamar en el update para evitar que el usuario cambie el tama en el juego.
///</summary>
///<param name="_x">tama en x.</param>
///<param name="_y">tama en y.</param>
void WindowSize(int _x, int _y);

///<summary>Llama a un evento para reproducir musica, usar .ogg o flac.
///<remark>Utiliza SFML</remark></summary>
///<param name="_musicPath">El path completo hacia el archivo del audio, de C:\\</param>
///<param name="_loop">Si la musica se repetira o no, TRUE o FALSE</param>
///<param name="_vol">el volumen de la musica</param>
void PlayMusic(char* _musicPath, BOOL _loop, float _vol);

///<summary>
///Hace cuadrados los pixeles de la pantalla, SOLO LLAMAR UNA VEZ.
///</summary>
void FontSize();

///<summary>
///Funcion que llena barras de estado, se usa con valores y representa porcentajes
///</summary>
///<param name="_entity">La estructura que contiene a la barra de vida.</param>
///<param name="_fullParam">El valor a revisar de la barra, representa el 100%. Usar NULL si no se quiere modificar</param>
///<param name="_currParam">El valor actual a revisar de la barra, representa el porcentaje actual.</param>
void FillBar(bar * _entity, int _fullParam, int _currParam);

///<summary>
///Inicializa los valores licos de un <remark><code>struct stats</code></remark>,
///para sus valores visuales usar <remark><code>SpriteParams()</code></remark>.
///</summary>
///<param name="_entity">La entidad a inicializar.</param><param name="_x">Posici en x.</param>
///<param name="_y">Posici en y.</param><param name="_life">Vida, dejar en 1 si no es un personaje vivo.</param>
///<param name="_attack">Ataque, dejare en 0 si no es un personaje vivo.</param>
///<param name="_speed">Velocidad, dejar en 0 si no es un personaje vivo.</param>
///<param name="_characterType">El tipo de personaje, solo usar CHARACTER, BACKGROUND o BAR para este parametro</param>
void SetStats(stats* _entity, int _x, int _y, int _life, int _attack, int _speed, int _characterType);

///<summary>Funci que recoge un <remark><code>struct stats</code></remark> y cambia sus valores. 0 es un valor para no modificar.</summary>
///<param name="_entity">La entidad a modificar.</param>
///<param name="_x">Modificador de posici en x.</param><param name="_y">Modificador de posici en y.</param>
///<param name="_life">Modificador de vida.</param><param name="_attack">Modificador de ataque.</param>
///<param name="_speed">Modificador de su velocidad.</param>
void UpdateStats(stats* _entity, int _x, int _y, int _life, int _attack, int _speed);

///<summary>Asigna todos los parametros visuales a un <remark><code>struct stats</code></remark>.
///Si no se quiere usar un canal asignarle el valor 0.
///Si se quieren modificar sus valores licos utilizar <remark><code>SetStats()</code></remark>.</summary>
///<param name="_entity">La entidad a modificar.</param><param name="_color1">El canal 1 del sprite.</param>
///<param name="_color2">El canal 2 del sprite.</param><param name="_color3">El canal 3 del sprite.</param>
///<param name="_color4">El canal 4 del sprite.</param><param name="_bg1">El canal 1 del background del color del sprite.</param>
///<param name="_bg2">El canal 2 del background del color del sprite.</param><param name="_bg3">El canal 3 del background del color del sprite.</param>
///<param name="_bg4">El canal 4 del background del color del sprite.</param><param name="_sprite">El array del sprite como pointer.</param>
///<param name="_weapon">El color del arma del sprite.</param>
int** SpriteParams(stats* _entity, int _color1, int _color2, int _color3, int _color4, int _bg1, int _bg2, int _bg3, int _bg4, int** _sprite, int _weapon);

///<summary>Asigna los parametros de letra a una entidad, puede ser usada para cualquier tipo de entidad.
///Introducir " " si no se desea poner nada o para dibujar un espacio en blanco.</summary>
///<param name="_entity">La entidad a modificar.</param><param name="_letter1">La letra 1 para dibujar el sprite.</param>
///<param name="_letter2">La letra 2 para dibujar el sprite.</param><param name="_letter3">La letra 3 para dibujar el sprite</param>
///<param name="_letter4">La letra 4 para dibujar el sprite.</param><param name="_weapon">La letra para dibujar el arma del sprite</param>
void CharSpriteParams(stats* _entity, char _letter1, char _letter2, char _letter3, char _letter4, char _charWeapon);

///<summary>Dibuja un sprite del personaje.</summary>
///<param name="_entity">La entidad que contiene al sprite.</param>
void DrawSprite(stats* _entity);

///<summary>Se debe llamar esta funcion para inicializar cualquier arreglo de sprites en el juego, solo una vez. Llamar a <code>FreeSpriteArray</code>
///cuando entre en deshuso el array</summary>
///<param name="_entity">La entidad a modificar</param><param name="_spriteSizeX">El tama del arreglo en x</param>
///<param name="_spriteSizeY">El tama del arreglo en y</param>
int** InitializeSpriteArray(stats* _entity, int _spriteSizeX, int _spriteSizeY);

///<summary>Solo llamar una vez para iniciar una entidad de barra.</summary>
///<param name="_entity">La entidad a trabajar</param><param name="_x"> posicion en X</param>
///<param name="_y">Posicion en Y</param><param name="_maxValue">El valor maximo a tratar de la barra</param>
///<param name="_spriteSizeX">El tamaño de la barra en X</param><param name="_spriteSizeY">El tamaño de la barra en Y</param>
///<param name="_color1">El color de la barra cuando esta arriba del 50%</param><param name="_color2">El color de la barra cuando esta arriba del 20% y abajo del 50%</param>
///<param name="_color3">El color de la barra cuando esta abajo del 20%</param><param name="_constraint">El color de la barra en sus barreras</param>
void InitializeBar(bar* _entity, int _x, int _y, int _maxValue, int _spriteSizeX, int _spriteSizeY, int _color1, int _color2, int _color3, int _constraint);

///<summary>Limpia la memoria que ocupaba el array, es decir lo borra, solo llamar cuando ya no se vaya a volver a usar.</summary>
///<param name="_entity">La entidad a modificar.</param>
void FreeSpriteArray(stats* _entity);

/////<summary>Maquina de colisiones, revisa si el personaje en cuestion no esta colisionando con otro de toda la escena.
/////Para utilizarla hay que adir todos los objetos con los que puede colisionar a un array de <remark><code>struct stats</code></remark>, 
/////inclusive al mismo personaje.
/////</summary>
/////<param name="_entity"> La entidad que contiene al sprite del personaje que colisionar・</param>
/////<param name="_entities">El array de entidades con los que puede colisionar.</param>
//void CheckCollisions(stats* _entity, struct stats _entities[]);

///<summary>Llamar en el update para mover un personaje.</summary>
///<param name="_entity">La entidad a modificar.</param>
///<param name="_movDirX"> La direcci del personaje, usar DIRRIGHT, DIRLEFT o NOMOVE.</param>
void SpriteMoveX(stats* _entity, int _movDirX);

///<summary>Llamar en el update para mover un personaje.</summary>
///<param name="_entity">La entidad a modificar.</param>
///<param name="_movDirX"> La direcci del personaje, usar DIRUP, DIRDOWN o NOMOVE.</param>
void SpriteMoveY(stats* _entity, int _movDirY);

///<summary>El sistema utiliza una fake screen buffer para resolver todo el screen printing. Al llamar a cualquier metodo Draw se incluye esto.
///NO LLENAR POR OTRO LADO
///</summary>
///<param name="_colorVal">El color a mostrar del tile</param>
///<param name="_backVal">El color a mostrar del fondo del tile</param>
///<param name="_letVal">La letra a mostrar</param>
///<param name="posx">La posición del tile en x</param>
///<param name="posy">La posición del tile en y</param>
///<param name="ocup">El ocupante del tile</param>
void AddToBuffer(int _colorVal, int _backVal, char _letVal, int posx, int posy, int ocup);

///<summary>Limpia el fake screen buffer. Llamar una vez al inicio de cada frame.</summary>
void ClearBuffer();

///<summary>Imprime el fakse screen buffer. Solo llamar una vez al final de todas las operaciones</summary>
void PrintBuffer();

///<summary>Crea un fake screen buffer. Solo llamar una vez o puede corromper la memoria</summary>
void CreateFakeScreenBuffer();

///<summary>Escribe texto en pantalla que funciona en base al fake buffer Solo funciona en c++ No da lineskips.</summary>
///<param name="text">Constante del texto, pasar como string o const char array</param>
///<param name="color">El color de las letras a mostrar</param>
///<param name="background">El fondo de las letras a mostrar</param>
///<param name="posx">La posición en X inicial de las letras</param>
///<param name="posy">La posición en Y inicial de las letras</param>
void TextWrapper(const char* text, int color, int background, int posx, int posy);

///<summary>Limpia e inicializa un array para un sprite. Llamar para inicializar en alguna función de sprite</summary>
///<param name ="_entity">La entidad a trabajar</param>
///<param name ="_sprite">El array a inicializar</param>
int** FillEmptySprite(stats* _entity, int** _sprite);

///<summary>Alternativa a llenar el array usando metodos convencionales. Solamente es un wrapper.</summary>
///<param name="y">Posición en Y.</param><param name="x">Posición en X.</param>
///<param name="content">El contenido del pixel</param><param name="_sprite">El array a trabajar pasado por referencia</param>
void AddPixel(int y, int x, int content, int*** _sprite);

#endif 