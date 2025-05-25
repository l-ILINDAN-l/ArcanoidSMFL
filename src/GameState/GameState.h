//
// Created by gellertilya on 25.05.25.
//

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "SMFL/SMFL.h"

/**
 * @class GameState
 * @brief Абстрактный базовый класс для всех состояний игры.
 *
 * Определяет общий интерфейс, который должен реализовывать каждое состояние (например, главное меню, игровой процесс).
 * Это позволяет главному игровому циклу обрабатывать любое состояние единообразно.
 */
class GameState {
public:
    virtual ~GameState() = default;

    /**
     * @brief Обрабатывает события ввода (например, нажатия клавиш, клики мыши).
     * @param event Событие SFML для обработки.
     */
    virtual void handleEvent(const sf::Event& event) = 0;

    /**
     * @brief Обновляет логику состояния игры.
     * @param dt Время, прошедшее с последнего кадра (delta time), для физически корректного движения.
     */
    virtual void update(sf::Time dt) = 0;

    /**
     * @brief Отрисовывает все объекты состояния на экране.
     */
    virtual void draw() = 0;

protected:
    explicit GameState(sf::RenderWindow& window) : mWindow(window) {}

    sf::RenderWindow& mWindow; // Ссылка на главное окно для отрисовки
};



#endif //GAMESTATE_H
