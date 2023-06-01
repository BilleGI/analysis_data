#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include "nlohmann/json.hpp"
#include "film.h"

const std::string name("analysis.json");
const int SIZE(3);

void fillJson(nlohmann::json& jsonFilm, Film& film)
{
    jsonFilm[film.title]["country"] = film.country;
    jsonFilm[film.title]["date"]["mon_day"] = film.date.tm_mday;
    jsonFilm[film.title]["date"]["mon"] = film.date.tm_mon;
    jsonFilm[film.title]["date"]["year"] = film.date.tm_year;
    jsonFilm[film.title]["atelier"] = film.atelier;
    jsonFilm[film.title]["autor script"] = film.autorScript;
    jsonFilm[film.title]["director"] = film.director;
    jsonFilm[film.title]["producer"] = film.producer;
    for(int i = 0; i < film.actors.size(); ++i)
    {
        jsonFilm[film.title]["actors"][i]["actor name"] = film.actors[i].actorName;
        jsonFilm[film.title]["actors"][i]["acting person"] = film.actors[i].actingPerson;
    }
}

void createFile()
{
    std::ofstream file(name);
    if(!file.is_open())
    {
        std::cerr << "ERROR!" << std::endl;
        exit(1);
    }

    Film film[SIZE];
    for(int i = 0; i < SIZE; ++i)
        createFilm(film[i]);
    nlohmann::json jsonFormate;
    for(int i = 0; i < SIZE; ++i)
        fillJson(jsonFormate, film[i]);

    file << jsonFormate;
    file.close();
}

void fillFilm(Film* film, nlohmann::json& jsonfilm)
{
    int i = 0;
    for(auto it = jsonfilm.begin(); it !=jsonfilm.end(); ++it)
    {
        film[i].title = it.key();
        ++i;
    }


    for(i = 0; i < jsonfilm.size(); ++i)
    {
        film[i].country = jsonfilm[film[i].title]["country"];
        film[i].date.tm_mday = jsonfilm[film[i].title]["date"]["mon_day"];
        film[i].date.tm_mon = jsonfilm[film[i].title]["date"]["mon"];
        film[i].date.tm_year = jsonfilm[film[i].title]["date"]["year"];
        film[i].atelier = jsonfilm[film[i].title]["atelier"];
        film[i].autorScript = jsonfilm[film[i].title]["autor script"];
        film[i].director = jsonfilm[film[i].title]["producer"];
        for(int j = 0; j < jsonfilm[film[i].title]["actors"].size(); ++j)
        {
            Actor actor;
            actor.actorName = jsonfilm[film[i].title]["actors"][j]["actor name"];
            actor.actingPerson = jsonfilm[film[i].title]["actors"][j]["acting person"];
            film[i].actors.push_back(actor);
        }
    }
}

void checkFile(Film film[], nlohmann::json& jsonFormate)
{
    std::ifstream file(name);
    if(!file.is_open()) createFile();
    file >> jsonFormate;
    fillFilm(film, jsonFormate);
    file.close();
}

void actorSearch(Film film[], nlohmann::json& filmJson, std::string& name)
{
    for(int i = 0; i <filmJson.size(); ++i)
    {
        for(int j = 0; j < filmJson[film[i].title]["actors"].size(); ++j)
        {
            if(filmJson[film[i].title]["actors"][j]["actor name"] == name)
            {
                for(int k = 0; k < 40; ++k) std::cout << "-";
                std::cout << "\nFilm - " << film[i].title << " acting person " << filmJson[film[i].title]["actors"][j]["acting person"] << std::endl;
            }

//            if(filmJson.at(film[i].title).at("actors")[j].find(name) != filmJson.at(film[i].title).at("actors")[j].end())
//            {
//                for( int i = 0; i < 40; ++i) std::cout << "-";
//                std::cout << "\nFilm - " << film[i].title << " acting person " << filmJson[film[i].title]["actors"][j]["acting person"] << std::endl;
//            }
        }
    }
    std::cout << std::endl;
}

int main()
{
    Film film[SIZE];
    nlohmann::json filmJson;
    checkFile(film, filmJson);
    std::cout << "The program is looking for an actor in the movie list." << std::endl;
    while(true)
    {
        char answer;
        std::string name;
        std::cout << "Enter the name actor: ";
        std::getline(std::cin, name);
        actorSearch(film, filmJson, name);
        std::cout << "repiat search?(y/n)";
        std::cin >> answer;
        if(answer =='n') break;
        std::cin.ignore();
    }

    return 0;
}
