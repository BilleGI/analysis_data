#pragma once
#include <string>
#include <vector>
#include <ctime>

struct Actor
{
    std::string actingPerson;
    std::string actorName;
};

struct Film
{
    std::string title;
    std::string country;
    std::tm date;
    std::string atelier;
    std::string autorScript;
    std::string director;
    std::string producer;
    std::vector<Actor> actors;
};

void checkInformation(std::tm& date, std::tm& timeNow);
void inputInformation(std::tm& date);

void checkTitle(std::string& title);

void checkInformation(std::string& information);

void inputInformation(std::string& information, std::string&& description);

void inputInformation(std::vector<Actor>& actors);

void createFilm(Film& film);
