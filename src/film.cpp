#include "film.h"
#include <iostream>
#include <iomanip>
#include <limits>

void checkInformation(std::tm& date, std::tm& timeNow)
{
    while(true)
    {
        bool flag = true;
        if(std::cin.fail() || (date.tm_year >= timeNow.tm_year && date.tm_mon >= timeNow.tm_mon && date.tm_mday > timeNow.tm_mday)
            || (date.tm_year >= timeNow.tm_year && date.tm_mon > timeNow.tm_mon)
            || (date.tm_year > timeNow.tm_year)) flag = false;
        if(flag) break;
        std::cout << "Enter the correct date: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cin.clear();
        std::string input;
        std::getline(std::cin, input);
        std::istringstream iss(input);
        iss >> std::get_time(&date, "%d:%m:%Y");
    }
}

void inputInformation(std::tm& date)
{
    time_t now = std::time(nullptr);
    std::tm timeNow = *std::localtime(&now);
    date = timeNow;
    std::cout << "Enter the creation date of movie in firmat DD:MM:YYYY -";
    std::cin >> std::get_time(&date, " %d:%m:%Y");
    std::cin.ignore();
    checkInformation(date, timeNow);
}

void checkTitle(std::string& title)
{
    while(true)
    {
        bool flag = true;
        for(int i = 0; i < title.size(); ++i)
        {
            if(!(title[i] >='a' && title[i] <= 'z') && !(title[i] >= 'A' && title[i] <= 'Z') && title[i] != ' ' && !(title[i] >= '0' && title[i] <= '9'))
            {
                flag = false;
                break;
            }
        }
        if(flag) break;
        std::cout << "Enter the correct title: ";
        std::getline(std::cin, title);
    }
}

void checkInformation(std::string& information)
{
    while(true)
    {
        bool flag = true;
        for(int i = 0; i < information.size(); ++i)
        {
            if(!(information[i] >= 'a' && information[i] <= 'z') && !(information[i] >= 'A' && information[i] <= 'z') && information[i] != ' ')
            {
                flag = false;
                break;
            }
        }
        if(flag) break;
        std::cout << "Enter the correct mean: ";
        std::getline(std::cin, information);
    }
}

void inputInformation(std::string& information, std::string&& description)
{
    std::cout << "Enter the field " << description << ": ";
    std::getline(std::cin, information);
    if(description == "title") checkTitle(information);
    else checkInformation(information);
}

void inputInformation(std::vector<Actor>& actors)
{
    while(true)
    {
        char add;
        Actor actor;
        inputInformation(actor.actorName, "actor name");
        inputInformation(actor.actingPerson, "actring person");
        actors.push_back(actor);
        std::cout << "Add actor?(y/n) ";
        std::cin >> add;
        std::cin.ignore();
        if(add == 'n') break;
    }
}

void createFilm(Film& film)
{
    inputInformation(film.title, "title");
    inputInformation(film.country, "country");
    inputInformation(film.date);
    inputInformation(film.atelier, "atelier");
    inputInformation(film.autorScript, " autor script");
    inputInformation(film.director, "director");
    inputInformation(film.producer, "producer");
    inputInformation(film.actors);
}
