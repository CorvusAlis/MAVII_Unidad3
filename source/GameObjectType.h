#pragma once
//lista de todos los posibles objetos del juego, a modo de etiqueta para usar en GameContactListener
//la clase generica GameObject pide el ObjectType del objeto, el objeto busca en el enum y devuelve su tipo
enum class GameObjectType
{
    Unknown,
    ZonaEntrega,
    Caja,
    Esfera,
    Garra,
    Suelo,
    Pared
};