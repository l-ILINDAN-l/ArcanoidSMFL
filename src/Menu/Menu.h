//
// Created by gellertilya on 25.05.25.
//

#ifndef MENU_H
#define MENU_H

#include "../GameState/GameState.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

/**
 * @class MainMenuState
 * @brief Реализация состояния главного меню игры.
 *
 * Отвечает за отображение фона, логотипа и кнопок "Start" и "Quit".
 * Управляет переходом в игровое состояние или выходом из игры.
 */
class MainMenuState : public GameState {
public:
    /**
     * @brief Конструктор.
     * @param window Ссылка на главное окно SFML.
     * @param gui Ссылка на главный объект TGUI, к которому будут добавляться виджеты.
     */
    MainMenuState(sf::RenderWindow& window, tgui::Gui& gui);

    /**
     * @brief Деструктор.
     *
     * Очищает GUI, удаляя все виджеты этого состояния.
     */
    ~MainMenuState() override;

    // Запрещаем копирование, чтобы избежать проблем с владением виджетами
    MainMenuState(const MainMenuState&) = delete;
    MainMenuState& operator=(const MainMenuState&) = delete;

    void handleEvent(const sf::Event& event) override;
    void update(sf::Time dt) override;
    void draw() override;

    /**
     * @brief Проверяет, была ли нажата кнопка "Start".
     * @return true, если нужно переходить в игровое состояние, иначе false.
     */
    bool isStartPressed() const { return mStartPressed; }

    /**
     * @brief Сбрасывает флаг нажатия кнопки "Start".
     *
     * Нужно вызывать после смены состояния, чтобы избежать повторного срабатывания.
     */
    void resetStartPressed() { mStartPressed = false; }


private:
    tgui::Gui& mGui; ///< Ссылка на главный GUI-объект

    // Флаги для управления переходами
    bool mStartPressed = false;

    // Указатели на виджеты TGUI
    tgui::Picture::Ptr mBackground;
    tgui::Picture::Ptr mLogo;
    tgui::Button::Ptr mStartButton;
    tgui::Button::Ptr mQuitButton;
};

#endif //MENU_H
