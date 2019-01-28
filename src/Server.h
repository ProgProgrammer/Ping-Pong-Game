﻿#pragma once
#include "ServerPackage.h"
#include "Ball.h"
#include "Paddle.h"
#include "ClientFactory.h"

class Server
{
    const int gameWidth;
    const int gameHeight;

    Paddle leftPaddle;
    Paddle rightPaddle;
    Ball ball;
    sf::SoundBuffer ballSoundBuffer;

    bool isAutoChangeColor = true;
    bool isSurpriseMode = false;

    GameStatus gameStatus = GameStatus::Init;

    const float paddleSpeed = 400.f;
    const float ballSpeed = 400.f;
    float ballAngle = 0.f; // to be changed later

    sf::Clock clock;

    std::shared_ptr<IClient> client01;
    std::shared_ptr<IClient> client02;

public:
    Server(int gameWidht, int gameHeight);
    void restartGame();
    void draw(sf::RenderWindow& window);
    void iterate();
    void setClient01(std::shared_ptr<IClient> client);
    void setClient02(std::shared_ptr<IClient> client);
    ServerPackage getPackage() const;

private:
    void loadBallSoundBuffer();
    void checkPaddlesCollision();
    void checkScreenCollision();
    void movePaddles(float);
    void moveBall(float);
};
