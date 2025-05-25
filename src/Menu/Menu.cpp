//
// Created by gellertilya on 25.05.25.
//

#include "Menu.h"
#include <iostream> // Для отладки

MainMenuState::MainMenuState(sf::RenderWindow& window, tgui::Gui& gui) : GameState(window), mGui(gui) {
    try {
        // 1. Фон
        // Создаем виджет-картинку и задаем ему растягиваться на 100% окна
        mBackground = tgui::Picture::create("texture/background.png");
        mBackground->setSize("100%", "100%");
        mGui.add(mBackground, "Background"); // Добавляем в GUI

        // 2. Логотип
        mLogo = tgui::Picture::create("texture/Arcanoid-logo.png");
        // Позиционируем по центру горизонтально и с отступом 10% сверху
        mLogo->setPosition("(parent.width - width) / 2", "10%");
        mGui.add(mLogo);

        // 3. Кнопка "Start"
        mStartButton = tgui::Button::create();
        // Указываем разные текстуры для обычного состояния и при наведении
        mStartButton->getRenderer()->setTexture("texture/ButtonStartND.png");
        mStartButton->getRenderer()->setTextureHover("texture/ButtonStartD.png");
        mStartButton->setSize(430, 200);
        // Позиционируем по центру горизонтально и с отступом 45% сверху
        mStartButton->setPosition("(parent.width - width) / 2", "45%");
        // Привязываем действие к событию "pressed" (нажатие)
        mStartButton->onPress([this] {
            std::cout << "Start button pressed!" << std::endl;
            this->mStartPressed = true;
        });
        mGui.add(mStartButton);

        // 4. Кнопка "Quit"
        mQuitButton = tgui::Button::create();
        mQuitButton->getRenderer()->setTexture("texture/QuitButtonND.png");
        mQuitButton->getRenderer()->setTextureHover("texture/QuitButtonD.png");
        mQuitButton->setSize(400, 168);
        // Позиционируем под кнопкой "Start"
        mQuitButton->setPosition("(parent.width - width) / 2", "65%");
        // При нажатии закрываем окно
        mQuitButton->onPress([this] {
            std::cout << "Quit button pressed!" << std::endl;
            this->mWindow.close();
        });
        mGui.add(mQuitButton);

    } catch (const tgui::Exception& e) {
        // Обработка ошибки, если текстура не найдена
        std::cerr << "TGUI Exception: " << e.what() << std::endl;
    }
}

MainMenuState::~MainMenuState() {
    // Очень важно удалить виджеты из GUI, когда состояние больше не нужно.
    // TGUI::remove() безопасно обработает nullptr, если виджет не был создан.
    mGui.remove(mBackground);
    mGui.remove(mLogo);
    mGui.remove(mStartButton);
    mGui.remove(mQuitButton);
}

void MainMenuState::handleEvent(const sf::Event& event) {
    // Просто передаем событие в TGUI. Он сам разберется.
    mGui.handleEvent(event);
}

void MainMenuState::update(sf::Time dt) {
    // В статичном меню обновлять ничего не нужно.
}

void MainMenuState::draw() {
    // TGUI сам знает, как и что рисовать.
    // Очистка экрана и display() будут вызываться в главном цикле игры.
    mGui.draw();
}