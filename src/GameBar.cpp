
#include "GameBar.hpp"
#include <iomanip>
#include <iostream>

GameBar::GameBar() {
    this->font = loadFont();
}

Font GameBar::loadFont() {
    Font f;
    if (!f.loadFromFile("fonts/CENTAUR.TTF")) { std::cout << "Cannot load font!"; }
    return f;
}

void GameBar::updateTexts(Player &player1, Player &player2, float time) {
    std::stringstream ss;
    ss << player1.score;
    std::string si;
    ss >> si;

    std::stringstream ss2;
    ss2 << player2.score;
    std::string si2;
    ss2 >> si2;

    std::stringstream ss3;
    ss3 << player1.covered;
    std::string si3;
    ss3 >> si3;

    std::stringstream ss4;
    ss4 << player2.covered;
    std::string si4;
    ss4 >> si4;

    std::stringstream ss5;
    ss5 << std::setprecision(2) << time;
    std::string si5;
    ss5 >> si5;

    //set new texts
    p1Score.setString("Wins: " + si);
    p2Score.setString("Wins: " + si2);
    p1Covered.setString("Covered: " + si3);
    p2Covered.setString("Covered: " + si4);
    timer.setString("Time left: " + si5 + " s");
}

void GameBar::setTextProperties() {

    //score
    this->p1Score.setFont(this->font);
    this->p2Score.setFont(this->font);
    this->p1Score.setString("Wins: ");
    this->p2Score.setString("Wins: ");
    this->p1Score.setFillColor(Color(255, 90, 0));
    this->p2Score.setFillColor(Color::Cyan);

    //covered tiles
    this->p1Covered.setFont(this->font);
    this->p2Covered.setFont(this->font);
    this->p1Covered.setString("Covered: ");
    this->p2Covered.setString("Covered: ");
    this->p1Covered.setFillColor(Color(255, 90, 0));
    this->p2Covered.setFillColor(Color::Cyan);
    this->p1Covered.setCharacterSize(20);
    this->p2Covered.setCharacterSize(20);

    //timer
    this->timer.setFont(this->font);
    this->timer.setFillColor(Color::White);
    this->timer.setCharacterSize(30);
}
