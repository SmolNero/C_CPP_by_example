#include <iostream>
#include "help.hpp"
#include <vector>
#include <map>
#include "serialize.hpp"
#include <thread>
#include <atomic>
namespace fs = std::filesystem;

bool isLoggedOut;
std::string GenerateId(int length = 8) {
    const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::string ID;
    for (int i = 0; i < length; i++) {
        ID += chars[Random::rand(0, (int)chars.size() - 1)];
        }
    return ID;
    }

class Game {
private:
    std::atomic<bool> autoClickerRunning{ false };
    struct Room {
        std::string name;
        std::string description;
        std::vector<std::string> items;
        std::map<std::string, int> exits;
        std::string game;
        std::string game_description;
        std::string requiredItem;
        };

    struct Click {
        bool bought1 = false;
        bool bought2 = false;
        bool bought3 = false;
        bool bought4 = false;

        bool auto1 = false;
        bool auto2 = false;
        bool auto3 = false;
        bool auto4 = false;
        bool auto5 = false;

        bool haveAny = false;
        bool haveAuto = false;
        bool GoldenF = false;
        bool hasLuckyCharm = false;


        int autoTime;
        long long clicks;
        int force;
        int mult;
        Click() {
            force = 1;
            mult = 1;
            }
        STDX_REFLECT(Click, clicks, force, mult, bought1, bought2, bought3, bought4, auto1, auto2, auto3, auto4, auto5, haveAuto, autoTime, haveAny, GoldenF, hasLuckyCharm);
        };
    struct Arena {
        std::vector<std::string> weapon = {};
        std::vector<std::string> armor = {};
        std::vector<std::string> shield = {};
        std::vector<std::string> potion = {};
        std::string currentWeapon;
        std::string currentArmor;
        std::string currentShield;
        int speed;
        int defense = 0;
        std::vector<std::string> inventory;
        STDX_REFLECT(Arena, weapon, armor, shield, potion, currentWeapon, currentArmor, currentShield, inventory, defense);
        };

    struct Player {
        std::string name;
        std::string password;
        int age;
        std::map<std::string, int> inv;
        std::vector<std::string> c_inv;
        int health;
        int xp;
        int xpNeeded;
        int level;
        bool isLogged;
        std::string id;
        std::string Ip;
        int damage;
        int gold;
        Click click;
        Arena arena;

        Player() : click() {
            id = GenerateId(Random::rand(20, 35));
            Ip = hp::getIp();
            isLogged = false;
            c_inv.push_back("Key");
            health = 100;
            damage = 30;
            level = 1;
            xp = 0;
            gold = 0;
            xpNeeded = 100;
            }

        STDX_REFLECT(Player, name, age, password, inv, health, xp, level, isLogged, Ip, id, c_inv, click, arena, damage, gold, xpNeeded);
        };


    std::map<int, Room> rooms;
    std::vector<std::string> users;
    int currentRoom;
    Player player;

public:
    Game() {
        Room forest;
        forest.name = "Forest";
        forest.description = "You are in a dark forest. Trees surround you.";
        forest.items = { "Berry", "Stick", "Bush", "Heal potion", "Mushroom", "Wood" };
        forest.exits["north"] = 1;
        forest.exits["south"] = 2;
        forest.exits["west"] = 5;
        forest.game = "Guess Game";
        forest.game_description = "Guess The Number between 1 to 10 !";
        rooms[0] = forest;

        Room cave;
        cave.name = "Cave";
        cave.description = "You enter a damp cave. It's cold and dark.";
        cave.exits["south"] = 0;
        cave.exits["west"] = 6;
        cave.items = { "Torch", "Golden ore", "Diamond", "Crystal", "Iron ore", "Stone", "Rope" };
        cave.game = "Memory Game";
        cave.game_description = "Remeber The memory pattern !";
        cave.requiredItem = "Torch";
        rooms[1] = cave;

        Room river;
        river.name = "River";
        river.description = "You stand by a flowing river. Water sparkles.";
        river.exits["west"] = 4;
        river.exits["south"] = 3;
        river.game = "Speed Typer";
        river.game_description = "Type The Word as fast as you Can !";
        river.items = { "Fish", "Water stone", "Pearl", "Swordfish" };
        river.requiredItem = "Fishing rod";
        rooms[2] = river;

        Room castle;
        castle.name = "Castle";
        castle.description = "A magnificent castle stands before you!";
        castle.exits["north"] = 2;
        castle.items = { "Sword", "Shield", "Crown" };
        castle.requiredItem = "Castle Key";
        rooms[3] = castle;

        Room wizard;
        wizard.name = "Wizard Tower";
        wizard.description = "A tall tower. Books and potions clutter the windows. The Wizard await";
        wizard.exits["east"] = 2;
        wizard.exits["north"] = 5;
        wizard.items = { "Magic essence", "Mana shard", "Spell book", "Dust" };
        wizard.game = "Spell Game";
        wizard.game_description = "Multiple Spell Game, Win them all to get a nice reward!";
        rooms[4] = wizard;

        Room forge;
        forge.name = "Crafting Forge";
        forge.description = "Craft Items";
        forge.exits["south"] = 4;
        forge.exits["east"] = 0;
        forge.exits["north"] = 6;
        forge.game = "Crafting Items";
        forge.game_description = "Craft items to unlock new features";
        rooms[5] = forge;

        Room arena;
        arena.name = "Arena";
        arena.description = "";
        arena.exits["south"] = 5;
        arena.exits["east"] = 1;
        arena.game = "Arena | Battle Game";
        arena.game_description = "Defeat The Enemies to win Awesome rewards !";
        rooms[6] = arena;

        currentRoom = 0;
        }

    void savePlayer() {
        hp::File file;
        file.write(player.name + ".sav", hp::serialize(player));
        }

    void spellGame() {
        hp::cls();
        std::cout << "\033[1;3H";
        hp::sp(" Spell Game ", 100);

        int wins = 0;
        std::vector<std::string> spells = {
   "fireball", "blizzard","thunder","invisible", "levitate",
   "barrier","phantom","meteor","freeze","shadow","dragon",
   "crystal","lightning","sorcery","enchanted","mystic",
   "arcane","potion","rune","teleport"
            };

        for (int i = 0; i < 5; i++) {
            std::string random = Random::choice(spells);
            std::string reversed(random.rbegin(), random.rend());

            std::cout << "\033[8;45H\033[2K";
            std::cout << "Round " << (i + 1) << "/5";

            std::cout << "\033[10;45H\033[2K";
            std::cout << "Spell: " << hp::getColorCode(hp::YELLOW) << reversed << hp::getColorCode(hp::RESET);
            std::string answer = hp::timedInput(14, 40, 30, 5, "Enter the spell: ", "Time's up! You lost");
            hp::clearInputField(14, 40, 30);

            if (answer == random) {
                hp::Field(14, 40, 30, "Correct!", hp::GREEN);
                wins++;
                }
            else {
                hp::Field(14, 40, 30, "Wrong!", hp::RED);
                }
            hp::wait(0.8);
            hp::clearInputField(14, 40, 30);
            }

        if (wins >= 3) {
            int a = Random::rand<int>(1, 3);
            std::string item = Random::choice(rooms[currentRoom].items);
            hp::Field(14, 40, "You won! Earned: " + std::to_string(a) + " " + item, hp::GREEN);
            player.inv[item] += a;
            savePlayer();
            }
        else {
            hp::Field(14, 40, 30, "You lost! Need 3/5 wins", hp::RED);
            }
        hp::wait(1.5);
        play();
        }

    void play() {
        hp::cls();
        int lastRoom = -1;

        while (true) {
            hp::updateKeyboard();

            if (currentRoom != lastRoom) {
                hp::cls();
                displayRoom();
                std::cout << "\n";
                std::cout << "Arrow keys to move, E to play the game, I for inventory, Esc to quit\n";
                lastRoom = currentRoom;
                }

            if (hp::KeyIsPressed::Escape) {
                GameMenu();
                return;
                }

            if (hp::KeyIsPressed::Right) {
                if (rooms[currentRoom].exits.find("east") != rooms[currentRoom].exits.end()) {
                    moveTo(rooms[currentRoom].exits["east"]);
                    }
                else {
                    std::cout << hp::getColorCode(hp::RED) << "Can't go that way" << hp::getColorCode(hp::RESET) << '\n';
                    }
                }

            if (hp::KeyIsPressed::Left) {
                if (rooms[currentRoom].exits.find("west") != rooms[currentRoom].exits.end()) {
                    moveTo(rooms[currentRoom].exits["west"]);
                    }
                else {
                    std::cout << hp::getColorCode(hp::RED) << "Can't go that way" << hp::getColorCode(hp::RESET) << '\n';
                    }
                }

            if (hp::KeyIsPressed::Up) {
                if (rooms[currentRoom].exits.find("north") != rooms[currentRoom].exits.end()) {
                    moveTo(rooms[currentRoom].exits["north"]);
                    }
                else {
                    std::cout << hp::getColorCode(hp::RED) << "Can't go that way" << hp::getColorCode(hp::RESET) << '\n';
                    }
                }

            if (hp::KeyIsPressed::Down) {
                if (rooms[currentRoom].exits.find("south") != rooms[currentRoom].exits.end()) {
                    moveTo(rooms[currentRoom].exits["south"]);
                    }
                else {
                    std::cout << hp::getColorCode(hp::RED) << "Can't go that way" << hp::getColorCode(hp::RESET) << '\n';
                    }
                }

            if (hp::KeyIsPressed::E) {
                while (_kbhit()) _getch();

                if (rooms[currentRoom].game == "Memory Game") {
                    memoryGame();
                    }
                else if (rooms[currentRoom].game == "Guess Game") {
                    guessGame();
                    }
                else if (rooms[currentRoom].game == "Speed Typer") {
                    speedTyper();
                    }
                else if (rooms[currentRoom].game == "Spell Game") {
                    spellGame();
                    }
                else if (rooms[currentRoom].game == "Crafting Items") {
                    craft();
                    }
                else if (rooms[currentRoom].game == "Knight's Duel") {
                    duel();
                    }
                else if (rooms[currentRoom].game == "Arena | Battle Game") {
                    arena();
                    }
                else {
                    hp::printlnCl("No game found!", hp::RED);
                    }
                }

            if (hp::KeyIsPressed::I) {
                hp::sp("Inventory");
                if (player.inv.empty()) {
                    hp::printlnCl("Your inventory is empty.", hp::YELLOW);
                    }
                else {
                    int i = 1;
                    for (auto& [item, qty] : player.inv) {
                        if (qty > 0) {
                            std::cout << hp::getColorCode(hp::YELLOW) << i << ". "
                                << hp::getColorCode(hp::WHITE) << qty << "x " << item
                                << hp::getColorCode(hp::RESET) << '\n';
                            i++;

                            }
                        }
                    }
                }

            hp::wait(0.1);
            }
        }

    void arena() {
        hp::cls();
        std::cout << "\033[1;3H";
        hp::sp(" Arena ", 100);
        int choice = hp::CenteredMenu({ "Play","Shop","Inventory","Stats","Exit" });
        switch (choice) {
            case 0: a_play(); break;
            case 1: a_shop(); break;
            case 2: a_inventory(); break;
            case 3: a_stats(); break;
            case 4: play(); break;
            default: break;
            }
        }
    void a_stats() {
        bool answer = false;
        hp::cls();
        std::cout << "\033[1;3H";
        hp::sp(" Arena Stats ", 100);
        std::cout << "\033[3;40H";
        std::cout << "Level: " << player.level << std::endl;
        std::cout << "\033[4;40H";
        std::cout << "XP: " << player.xp << "/" << player.xpNeeded << std::endl;
        std::cout << "\033[5;40H";
        std::cout << "Gold: " << player.gold << std::endl;
        std::cout << "\033[6;40H";
        std::cout << "Armor: " << player.arena.currentArmor << std::endl;
        std::cout << "\033[7;40H";
        std::cout << "Shield: " << player.arena.currentShield << std::endl;
        std::cout << "\033[8;40H";
        std::cout << "Weapon: " << player.arena.currentWeapon << std::endl;
        while (!answer) {
            hp::updateKeyboard();
            if (hp::KeyIsPressed::Escape) {
                answer = true;
                arena();
                return;
                }
            }
        }
    void a_shop() {
        hp::cls();
        std::cout << "\033[1;3H";
        hp::sp(" Arena Shop ", 100);
        std::cout << "\033[15;3H";
        std::cout << "Gold: " << player.gold << std::endl;
        int choice = hp::CenteredMenu({ "Buy Weapon","Buy Armor","Buy Shield","Buy Potion","Exit" });
        switch (choice) {
            case 0: a_buyWeapon(); break;
            case 1: a_buyArmor(); break;
            case 2: a_buyShield(); break;
            case 3: a_buyPotion(); break;
            case 4: arena(); break;
            default: break;
            }
        }
    void a_buyPotion() {
        hp::cls();
        std::cout << "\033[1;3H";
        hp::sp(" Arena Shop - Buy Potion ", 100);
        int choice = hp::CenteredMenu({ "Health Potion - 50 Gold"," Strength Potion - 75 Gold","Defense Potion - 100 Gold","Exit" });
        std::cout << "\033[20;40H";
        switch (choice) {
            case 0:
                if (player.gold >= 50) {
                    player.gold -= 50;
                    player.arena.potion.push_back("Health Potion");
                    hp::printlnCl("You bought a Health Potion!", hp::GREEN);
                    savePlayer();
                    }
                else {
                    hp::printlnCl("Not enough gold!", hp::RED);
                    }
                break;
            case 1:
                if (player.gold >= 75) {
                    player.gold -= 75;
                    player.arena.potion.push_back("Strength Potion");
                    hp::printlnCl("You bought a Strength Potion!", hp::GREEN);
                    savePlayer();
                    }
                else {
                    hp::printlnCl("Not enough gold!", hp::RED);
                    }
                break;
            case 2:
                if (player.gold >= 100) {
                    player.gold -= 100;
                    player.arena.potion.push_back("Defense Potion");
                    hp::printlnCl("You bought a Defense Potion!", hp::GREEN);
                    savePlayer();
                    }
                else {
                    hp::printlnCl("Not enough gold!", hp::RED);
                    }
                break;
            case 3: a_shop(); break;
            default: break;
            }
        hp::wait(1);
        a_buyPotion();
        }
    void a_potions() {
        hp::cls();
        std::cout << "\033[1;3H";
        hp::sp(" Potions ", 100);
        bool answer = false;
        for (int i = 0; i < player.arena.potion.size(); i++) {
            std::cout << "\033[" << (3 + i) << ";40H";
            std::cout << "  " << (i + 1) << ". " << player.arena.potion[i];
            }
        while (!answer) {
            hp::updateKeyboard();
            if (hp::KeyIsPressed::Escape) {
                answer = true;
                a_inventory();
                return;
                }
            }
        }
    void a_buyShield() {
        hp::cls();
        std::cout << "\033[1;3H";
        hp::sp(" Arena Shop - Buy Shield ", 100);
        int choice = hp::CenteredMenu({ "Wooden Shield - 50 Gold","Iron Shield - 100 Gold","Steel Shield - 150 Gold","Exit" });
        switch (choice) {
            case 0:
                if (player.gold >= 50) {
                    player.gold -= 50;
                    player.arena.shield.push_back("Wooden Shield");
                    hp::printlnCl("You bought a Wooden Shield!", hp::GREEN);

                    savePlayer();
                    }
                else {
                    hp::printlnCl("Not enough gold!", hp::RED);
                    }
                break;
            case 1:
                if (player.gold >= 100) {
                    player.gold -= 100;
                    player.arena.shield.push_back("Iron Shield");
                    hp::printlnCl("You bought an Iron Shield!", hp::GREEN);
                    savePlayer();
                    }
                else {
                    hp::printlnCl("Not enough gold!", hp::RED);
                    }
                break;
            case 2:
                if (player.gold >= 150) {
                    player.gold -= 150;
                    player.arena.shield.push_back("Steel Shield");
                    hp::printlnCl("You bought a Steel Shield!", hp::GREEN);
                    savePlayer();
                    }
                else {
                    hp::printlnCl("Not enough gold!", hp::RED);
                    }
                break;
            case 3: a_shop(); break;
            default: break;
            }
        hp::wait(1.3);
        a_buyShield();
        }
    void a_buyWeapon() {
        hp::cls();
        std::cout << "\033[1;3H";
        hp::sp(" Arena Shop - Buy Weapon ", 100);
        int choice = hp::CenteredMenu({ "Sword - 100 Gold","Axe - 150 Gold","Bow - 200 Gold","Exit" });
        std::cout << "\033[20;40H";
        switch (choice) {
            case 0:
                if (player.gold >= 100) {
                    player.gold -= 100;
                    player.arena.weapon.push_back("Sword");
                    hp::printlnCl("You bought a Sword!", hp::GREEN);
                    savePlayer();
                    }
                else {
                    hp::printlnCl("Not enough gold!", hp::RED);
                    }
                break;
            case 1:
                if (player.gold >= 150) {
                    player.gold -= 150;
                    player.arena.weapon.push_back("Axe");
                    hp::printlnCl("You bought an Axe!", hp::GREEN);
                    savePlayer();
                    }
                else {
                    hp::printlnCl("Not enough gold!", hp::RED);
                    }
                break;
            case 2:
                if (player.gold >= 200) {
                    player.gold -= 200;
                    player.arena.weapon.push_back("Bow");
                    hp::printlnCl("You bought a Bow!", hp::GREEN);
                    savePlayer();
                    }
                else {
                    hp::printlnCl("Not enough gold!", hp::RED);
                    }
                break;
            case 3: a_shop(); break;
            default: break;
            }
        hp::wait(1.3);
        a_buyWeapon();
        }
    void a_inventory() {
        hp::cls();
        std::cout << "\033[1;3H";
        hp::sp(" Inventory ", 100);
        int choice = hp::CenteredMenu({ "Weapons","Armors","Shields","Potions","Exit" });
        std::cout << "\033[3;40H";
        switch (choice) {
            case 0:
                if (player.arena.weapon.empty()) {
                    hp::cls();
                    std::cout << "\033[1;3H";
                    hp::sp(" Weapons ", 100);
                    std::cout << "\033[3;40H";
                    hp::printlnCl("You have no weapons.", hp::YELLOW);
                    hp::wait(1.5);
                    arena();
                    }
                else {
                    a_weapons(); break;
                    }
                break;
            case 1:
                if (player.arena.armor.empty()) {
                    hp::cls();
                    std::cout << "\033[1;3H";
                    hp::sp(" Armors ", 100);
                    std::cout << "\033[3;40H";
                    hp::printlnCl("You have no armors.", hp::YELLOW);
                    hp::wait(1.5);
                    arena();
                    }
                else {
                    a_armors(); break;
                    }
                break;
            case 2:
                if (player.arena.shield.empty()) {
                    hp::cls();
                    std::cout << "\033[1;3H";
                    hp::sp(" Shields ", 100);
                    std::cout << "\033[3;40H";
                    hp::printlnCl("You have no shields.", hp::YELLOW);
                    hp::wait(1.5);
                    arena();
                    }
                else {
                    a_shields(); break;
                    }
                break;
            case 3:
                if (player.arena.potion.empty()) {
                    hp::cls();
                    std::cout << "\033[1;3H";
                    hp::sp(" Potions ", 100);
                    std::cout << "\033[3;40H";
                    hp::printlnCl("You have no potions.", hp::YELLOW);
                    hp::wait(1.5);
                    arena();
                    }
                else {
                    a_potions(); break;
                    }
                break;
            case 4: arena(); break;
            }
        }

    void a_armors() {
        hp::cls();
        std::cout << "\033[1;3H";
        hp::sp(" Armors ", 100);
        std::vector<std::string> options = player.arena.armor;
        options.push_back("Exit");
        int choice = hp::CenteredMenu(options, hp::YELLOW);
        std::cout << "\033[20;40H";
        std::string currentArmor = player.arena.currentArmor;
        std::string currentWeapon = player.arena.currentWeapon;

        if (choice == options.size() - 1) {
            a_inventory();
            return;
            }

        if (choice >= 0 && choice < player.arena.armor.size()) {
            if (currentArmor == player.arena.armor[choice]) {
                hp::printlnCl("You already have this armor equipped!", hp::YELLOW);
                hp::wait(1.1);
                a_armors();
                }
            else {
                player.arena.currentArmor = player.arena.armor[choice];
                hp::printlnCl("Equipped " + player.arena.currentArmor + "!", hp::GREEN);
                if (player.arena.currentArmor == "Leather Armor") {
                    player.arena.defense = 5;
                    }
                else if (player.arena.currentArmor == "Chainmail Armor") {
                    player.arena.defense = 10;
                    player.arena.speed += 3;
                    }
                else if (player.arena.currentArmor == "Plate Armor") {
                    player.arena.defense = 15;
                    }
                else if (player.arena.currentArmor == "Iron Armor") {
                    player.arena.defense = 20;
                    }
                hp::wait(1.1);
                a_armors();
                savePlayer();
                }
            }
        }
    void a_weapons() {
        hp::cls();
        std::cout << "\033[1;3H";
        hp::sp(" Weapons ", 100);
        std::vector<std::string> options = player.arena.weapon;
        options.push_back("Exit");
        int choice = hp::CenteredMenu(options, hp::YELLOW);

        std::string currentWeapon = player.arena.currentWeapon;
        if (choice == options.size() - 1) {
            a_inventory();
            return;
            }

        if (choice >= 0 && choice < player.arena.weapon.size()) {
            if (currentWeapon == player.arena.weapon[choice]) {
                hp::printlnCl("You already have this weapon equipped!", hp::YELLOW);
                hp::wait(1.1);
                a_weapons();
                }
            else {
                player.arena.currentWeapon = player.arena.weapon[choice];
                hp::printlnCl("Equipped " + player.arena.currentWeapon + "!", hp::GREEN);
                if (player.arena.currentWeapon == "Sword") {
                    player.damage = 30;
                    }
                else if (player.arena.currentWeapon == "Axe") {
                    player.damage = 40;
                    }
                else if (player.arena.currentWeapon == "Bow") {
                    player.damage = 35;
                    player.arena.speed += 5;
                    }
                hp::wait(1.1);
                a_weapons();
                savePlayer();
                }
            }
        }
    void a_shields() {
        hp::cls();
        std::cout << "\033[1;3H";
        hp::sp(" Shields ", 100);
        std::vector<std::string> options = player.arena.shield;
        options.push_back("Exit");
        int choice = hp::CenteredMenu(options, hp::YELLOW);

        if (choice == options.size() - 1) {
            a_inventory();
            return;
            }

        if (choice >= 0 && choice < player.arena.shield.size()) {
            if (player.arena.currentShield == player.arena.shield[choice]) {
                hp::printlnCl("You already have this shield equipped!", hp::YELLOW);
                hp::wait(1.5);
                a_shields();
                }
            else {
                player.arena.currentShield = player.arena.shield[choice];
                hp::printlnCl("Equipped " + player.arena.currentShield + "!", hp::GREEN);
                if (player.arena.currentShield == "Wooden Shield") {
                    player.arena.defense = 5;
                    }
                else if (player.arena.currentShield == "Iron Shield") {
                    player.arena.defense = 10;
                    }
                else if (player.arena.currentShield == "Steel Shield") {
                    player.arena.defense = 12;
                    player.arena.speed += 5;
                    }
                savePlayer();
                }
            hp::wait(1.1);
            a_shields();
            }
        }
    void a_buyArmor() {
        hp::cls();
        std::cout << "\033[1;3H";
        hp::sp(" Armors ", 100);
        int choice = hp::CenteredMenu({ "Leather Armor - 100 Gold","Chainmail Armor - 150 Gold","Plate Armor - 200 Gold", "Iron Armor - 250 Gold","Exit" });
        switch (choice) {
            case 0:
                if (player.gold >= 100) {
                    player.gold -= 100;
                    player.arena.armor.push_back("Leather Armor");
                    hp::printlnCl("You bought Leather Armor!", hp::GREEN);
                    savePlayer();
                    hp::wait(1);
                    a_buyArmor();
                    }
                else {
                    hp::printlnCl("Not enough gold!", hp::RED);
                    hp::wait(1);
                    a_buyArmor();
                    }
                break;
            case 1:
                if (player.gold >= 150) {
                    player.gold -= 150;
                    player.arena.armor.push_back("Chainmail Armor");
                    hp::printlnCl("You bought Chainmail Armor!", hp::GREEN);
                    savePlayer();
                    hp::wait(1);
                    a_buyArmor();
                    }
                else {
                    hp::printlnCl("Not enough gold!", hp::RED);
                    hp::wait(1);
                    a_buyArmor();
                    }
                break;
            case 2:
                if (player.gold >= 200) {
                    player.gold -= 200;
                    player.arena.armor.push_back("Plate Armor");
                    hp::printlnCl("You bought Plate Armor!", hp::GREEN);
                    savePlayer();
                    hp::wait(1);
                    a_buyArmor();
                    }
                else {
                    hp::printlnCl("Not enough gold!", hp::RED);
                    hp::wait(1);
                    a_buyArmor();
                    }
                break;
            case 3:
                if (player.gold >= 250) {
                    player.gold -= 250;
                    player.arena.armor.push_back("Iron Armor");
                    hp::printlnCl("You bought Iron Armor!", hp::GREEN);
                    savePlayer();
                    hp::wait(1);
                    a_buyArmor();
                    }
                else {
                    hp::printlnCl("Not enough gold!", hp::RED);
                    hp::wait(1);
                    a_buyArmor();
                    }
                break;
            case 4: a_shop(); break;
            default: break;
            }
        }
    void a_play() {
        hp::cls();
        std::cout << "\033[1;3H";
        hp::sp(" Arena ", 100);
        int choice = hp::CenteredMenu({ "Goblin","Skeleton","Orc","Dark Knight","Kraken","Dragon","Exit" });
        switch (choice) {
            case 0: fight("Goblin", 100, 20, 50, 75); break;
            case 1: fight("Skeleton", 200, 35, 75, 100); break;
            case 2: fight("Orc", 350, 45, 150, 200); break;
            case 3: fight("Dark Knight", 500, 100, 200, 175); break;
            case 4: fight("Kraken", 1200, 150, 350, 300); break;
            case 5: fight("Dragon", 2500, 175, 500, 500); break;
            case 6: arena(); break;
            default: break;
            }

        }
    void fight(const std::string& enemy, int enemyHealth, int enemyDamage, int rewardGold, int rewardXP) {
        hp::cls();
        std::cout << "\033[1;3H";
        hp::sp(" Arena ", 100);

        int Ehp = enemyHealth;
        int Edamage = (enemyDamage - (player.arena.defense / 2)) + Random::rand(enemyDamage / 5, (enemyDamage / 2) + 2);
        int PrevEhp = -1;
        int Prevhp = -1;
        bool isDead = false;

        player.damage = 30 + (player.level * 2) + Random::rand(1, 10);
        if (player.arena.currentWeapon == "Sword") player.damage += 20;
        else if (player.arena.currentWeapon == "Axe") player.damage += 45;
        else if (player.arena.currentWeapon == "Bow") player.damage += 35;

        int XPReward = rewardXP + (player.level * 2) + Random::rand(1, 5);
        player.health = 100 + (player.level * 2);

        int goldReward = rewardGold + (player.level * 5) + Random::rand(1, 10);
        bool canAttack = true;
        while (!isDead) {
            hp::updateKeyboard();

            if (PrevEhp != Ehp || Prevhp != player.health) {
                PrevEhp = Ehp;
                Prevhp = player.health;
                std::cout << "\033[20;20H\033[2K";
                std::cout << "Player HP: " << player.health;
                std::cout << "\033[21;20H\033[2K";
                std::cout << "Enemy HP: " << Ehp;
                std::cout << "\033[23;40H";
                std::cout << "Press A to Attack, S for Skills, I for Inventory, E to Escape";
                }

            if (hp::KeyIsPressed::A && canAttack) {
                if (Random::rand(1, 100) <= 10) {
                    std::cout << "\033[15;40H";
                    std::cout << "Critical Hit! You dealt " << hp::getColorCode(hp::GREEN) << player.damage * 2 << hp::getColorCode(hp::RESET) << " damage!";
                    Ehp -= player.damage * 2;
                    }
                else if (Random::rand(1, 100) + player.arena.speed <= 15) {
                    std::cout << "\033[15;40H";
                    std::cout << "You missed the attack!";
                    if (Ehp > 0) {
                        player.health -= Edamage;
                        std::cout << "\033[15;40H";
                        std::cout << "\033[2K";
                        std::cout << "The enemy attacked you for " << hp::getColorCode(hp::RED) << Edamage << hp::getColorCode(hp::RESET) << " damage!";
                        hp::wait(0.8);
                        }
                    }
                else {
                    Ehp -= player.damage;
                    std::cout << "\033[15;40H";
                    std::cout << "You attacked the enemy for " << hp::getColorCode(hp::GREEN) << player.damage << hp::getColorCode(hp::RESET) << " damage!";
                    hp::wait(0.8);
                    if (Ehp > 0) {
                        player.health -= Edamage;
                        std::cout << "\033[15;40H";
                        std::cout << "\033[2K";
                        std::cout << "The enemy attacked you for " << hp::getColorCode(hp::RED) << Edamage << hp::getColorCode(hp::RESET) << " damage!";
                        hp::wait(0.8);
                        }
                    }
                hp::wait(0.3);
                }
            if (hp::KeyIsPressed::I) {
                std::vector<std::string> options = player.arena.potion;
                options.push_back("Exit");
                int choice = hp::CenteredMenu(options, hp::YELLOW);
                if (choice == options.size() - 1) {
                    continue;
                    }
                if (choice >= 0 && choice < player.arena.potion.size()) {
                    std::string potion = player.arena.potion[choice];
                    player.arena.potion.erase(player.arena.potion.begin() + choice);
                    if (potion == "Health Potion") {
                        player.health += 50;
                        int maxHp = 100 + (player.level * 2);
                        if (player.health > maxHp) player.health = maxHp;
                        }
                    else if (potion == "Strength Potion") {
                        player.damage += 10;
                        hp::printlnCl("You used a Strength Potion! Damage increased to " + std::to_string(player.damage), hp::GREEN);
                        }
                    else if (potion == "Defense Potion") {
                        player.arena.defense += 5;
                        hp::printlnCl("You used a Defense Potion! Defense increased to " + std::to_string(player.arena.defense), hp::GREEN);
                        }
                    savePlayer();
                    }
                }
            if (hp::KeyIsPressed::E) {
                std::cout << "\033[15;40H\033[2K";
                if (Random::rand(1, 100) <= 30) {
                    hp::printlnCl("You escaped the battle!", hp::YELLOW);
                    hp::wait(1.5);
                    isDead = true;
                    }
                else {
                    hp::printlnCl("You failed to escape!", hp::RED);
                    player.health -= Edamage;
                    std::cout << "\033[16;40H\033[2K";
                    std::cout << "The enemy attacked you for " << hp::getColorCode(hp::RED) << Edamage << hp::getColorCode(hp::RESET) << " damage!";
                    hp::wait(1.5);
                    std::cout << "\033[2K";
                    }
                hp::wait(0.3);
                }

            if (player.health <= 0) {
                std::cout << "\033[15;40H";
                std::cout << "\033[2K";
                hp::printCl("You Are Dead!", hp::RED);
                hp::wait(1.5);
                std::cout << "\033[2K";
                isDead = true;
                a_play();
                }
            else if (Ehp <= 0) {
                std::cout << "\033[15;40H";
                std::cout << "\033[2K";
                hp::printlnCl("You have defeated the enemy!", hp::GREEN);
                std::cout << "\033[16;40H";
                hp::printlnCl("You Earned " + std::to_string(goldReward) + " Gold And " + std::to_string(XPReward) + " XP", hp::GREEN);
                player.gold += goldReward;
                player.xp += XPReward;
                savePlayer();
                isDead = true;
                hp::wait(1.5);
                checkLevelUp();
                a_play();
                }
            }
        hp::wait(0.05);
        }

    void checkLevelUp() {
        player.xpNeeded = player.level * 100;
        while (player.xp >= player.xpNeeded) {
            player.xp -= player.xpNeeded;
            player.level++;
            player.health = 100 + (player.level * 2);
            player.damage += 5;
            player.xpNeeded = player.level * 100;

            hp::cls();
            std::cout << "\033[1;3H";
            hp::sp(" LEVEL UP! ", 100);
            std::cout << "\033[10;40H";
            hp::printlnCl("You reached Level " + std::to_string(player.level) + "!", hp::GREEN);
            std::cout << "\033[12;40H";
            hp::printlnCl("HP and Damage increased!", hp::YELLOW);
            std::cout << "\033[14;40H";
            hp::printlnCl("Next level: " + std::to_string(player.xpNeeded) + " XP", hp::WHITE);
            hp::wait(2.3);
            }
        hp::wait(1);
        a_play();
        }
    void duel() {
        hp::cls();
        std::cout << "\033[1;3H";
        hp::sp(" Knight's Duel ", 100);
        int wins = 0;
        int a_wins = 0;
        int b_wins = 0;
        int c_wins = 0;
        int a_loss = 0;
        int c_loss = 0;
        int plays = 0;
        bool end = false;
        std::vector<std::string> ai = { "Paper", "Rock", "Scissors" };
        while (a_wins < 3 && a_loss < 3) {
            std::string aiChoice = Random::choice(ai);
            std::cout << "\033[10;45H";
            hp::printlnCl("Game: Rock, Paper and Sissors", hp::YELLOW);
            std::string choice = hp::inputField(14, 40, 30, "Enter your choice", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
            hp::clearInputField(14, 40, 30);
            if (choice == "paper" || choice == "Paper") {
                if (aiChoice == "Rock") {
                    a_wins++;
                    hp::Field(14, 40, "Knight: Rock. You Won!", hp::GREEN);
                    hp::wait(1.3);
                    }
                else if (aiChoice == "Paper") {
                    hp::Field(14, 40, "Knight: Paper. Tie!", hp::YELLOW);
                    hp::wait(1.3);
                    }
                else if (aiChoice == "Scissors") {
                    hp::Field(14, 40, "Knight: Scissord. You Lose!", hp::RED);
                    a_loss++;
                    hp::wait(1.3);
                    }
                }
            else if (choice == "Rock" || choice == "rock") {
                if (aiChoice == "Rock") {
                    hp::Field(14, 40, "Knight: Rock. Tie!", hp::YELLOW);
                    hp::wait(1.3);
                    }
                else if (aiChoice == "Paper") {
                    hp::Field(14, 40, "Knight: Paper. You Lose!", hp::RED);
                    a_loss++;
                    hp::wait(1.3);
                    }
                else if (aiChoice == "Scissors") {
                    hp::Field(14, 40, "Knight: Scissors. You Won!", hp::GREEN);
                    a_wins++;
                    hp::wait(1.3);
                    }
                }
            else if (choice == "Scissors" || choice == "scissors") {
                if (aiChoice == "Rock") {
                    hp::Field(14, 40, "Knight: Rock. You Lose!", hp::RED);
                    a_loss++;
                    hp::wait(1.3);
                    }
                else if (aiChoice == "Paper") {
                    hp::Field(14, 40, "Knight: Paper. You Win!", hp::GREEN);
                    a_wins++;
                    hp::wait(1.3);
                    }
                else if (aiChoice == "Scissors") {
                    hp::Field(14, 40, "Knight: Scissors. Tie!", hp::YELLOW);
                    hp::wait(1.3);
                    }
                }
            else {
                hp::Field(14, 40, "Invalid Choice", hp::RED);
                }
            }
        std::vector<std::string> riddles = {
    "I have keys but no locks. I have space but no room. You can enter but can't leave. What am I?",
    "The more you take, the more you leave behind. What am I?",
    "I speak without a mouth and hear without ears. I have no body, but I come alive with the wind. What am I?",
    "I can be cracked, made, told, and played. What am I?",
    "I have cities but no houses, forests but no trees, and water but no fish. What am I?",
    "What has a head and a tail but no body?",
    "I am always coming but never arrive. What am I?",
    "What gets wetter the more it dries?",
    "What can travel around the world while staying in a corner?",
    "What has many teeth but can't bite?",
    "I am light as a feather, yet the strongest person can't hold me for 5 minutes. What am I?",
    "What has words but never speaks?",
    "The person who makes it sells it. The person who buys it never uses it. The person who uses it never knows. What is it?",
    "I have lakes with no water, mountains with no stone, and cities with no buildings. What am I?",
    "What can fill a room but takes up no space?"
            };
        std::vector<std::string> answers = {
    "keyboard",
    "footsteps",
    "echo",
    "joke",
    "map",
    "coin",
    "tomorrow",
    "towel",
    "stamp",
    "comb",
    "breath",
    "book",
    "coffin",
    "map",
    "light"
            };

        hp::cls();
        std::cout << "\033[1;3H";
        hp::sp(" Knight's Duel", 100);
        std::cout << "\033[5;45H";
        hp::printlnCl("Game: Riddle Quiz ", hp::YELLOW);
        std::vector<int> indexes;
        for (int i = 0; i < riddles.size(); i++) {
            indexes.push_back(i);
            }
        Random::shuffle(indexes);

        for (int i = 0; i < 5; i++) {
            int riddleIndex = indexes[i];
            std::cout << "\033[8;40H\033[2K";
            hp::printlnCl("Riddle: " + riddles[riddleIndex], hp::YELLOW);
            std::string choice = hp::inputField(14, 40, 30, "Enter your answer: ");
            std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);

            if (choice == answers[riddleIndex]) {
                hp::Field(14, 40, 30, "Correct!", hp::GREEN);
                b_wins++;
                hp::wait(1);
                }
            else {
                hp::Field(14, 40, 30, "Wrong! Answer: " + answers[riddleIndex], hp::RED);
                hp::wait(1);
                }
            }
        int num = 3;
        std::vector<int> sequence;
        hp::cls();
        std::cout << "\033[1;3H";
        hp::sp(" Knight's Duel", 100);
        std::cout << "\033[5;45H";
        hp::printlnCl("Game: Letter Memory", hp::YELLOW);

        while (plays <= 3) {
            sequence.clear();
            for (int i = 0; i < num; i++) {
                int letter = Random::rand(0, 25);
                sequence.push_back(letter);
                showLetter(letter);
                }

            for (int i = 0; i < sequence.size(); i++) {
                bool answered = false;
                while (!answered) {
                    if (_kbhit()) {
                        int ch = _getch();
                        if (ch >= 'a' && ch <= 'z') ch -= 32;

                        if (ch >= 'A' && ch <= 'Z') {
                            answered = true;
                            int pressed = ch - 'A';

                            std::cout << "\033[15;43H\033[2K";
                            if (pressed == sequence[i]) {
                                hp::printlnCl("Correct!", hp::GREEN);
                                c_wins++;
                                }
                            else {
                                hp::printlnCl("Wrong!", hp::RED);
                                }
                            }
                        }
                    }
                }
            plays++;
            num++;
            }
        if (a_wins >= 3 && b_wins >= 3 && c_wins >= 3) {
            hp::wait(1.5);
            hp::cls();
            std::cout << "\033[1;3H";
            hp::title(" Congragulations ! ", 95);
            std::cout << "\033[12;45";
            std::string randomitem = Random::choice(rooms[currentRoom].items);
            hp::printlnCl("Congragulation ! You won all 3 Game ! \n You Earned: a Shield, an Armor, an Adventure Key and a " + randomitem + " !", hp::GREEN);
            hp::waitForAnyKey();
            }
        else {
            hp::wait(1.5);
            hp::cls();
            hp::printlnCl("You lost !", hp::RED);
            hp::waitForAnyKey();
            }
        }



    void showLetter(int letter) {
        std::vector<std::string> letters = {
            "A", "B", "C", "D", "E", "F", "G", "H", "I", "J",
            "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T",
            "U", "V", "W", "X", "Y", "Z"
            };

        std::vector<hp::Color> colors = {
            hp::RED, hp::BLUE, hp::GREEN, hp::YELLOW,
            hp::MAGENTA, hp::CYAN, hp::WHITE, hp::BRIGHT_RED,
            hp::BRIGHT_BLUE, hp::BRIGHT_GREEN, hp::BRIGHT_YELLOW,
            hp::BRIGHT_MAGENTA, hp::BRIGHT_CYAN
            };

        hp::Color randomColor = Random::choice(colors);

        std::cout << "\033[10;52H";
        hp::printCl(letters[letter], randomColor);
        hp::wait(0.8);

        std::cout << "\033[10;52H\033[2K";
        hp::wait(0.3);
        }
    void moveTo(int nextRoom) {
        if (!rooms[nextRoom].requiredItem.empty()) {
            if (player.inv[rooms[nextRoom].requiredItem] < 1) {
                std::cout << hp::getColorCode(hp::RED)
                    << "You need a " << rooms[nextRoom].requiredItem << "!"
                    << hp::getColorCode(hp::RESET) << '\n';
                return;
                }
            }
        currentRoom = nextRoom;
        }

    void speedTyper() {
        hp::cls();
        std::cout << "\033[1;3H";
        hp::sp(" Speed Typer ", 100);

        std::vector<std::string> words = { "cave", "torch", "gold", "dark", "echo", "memory", "bat", "stone" };
        int score = 0;
        int timeLimit = 5;

        while (score < 5) {
            std::string target = Random::choice(words);
            std::cout << "\033[8;50H\033[2K";
            std::cout << "Word: " << hp::getColorCode(hp::YELLOW) << target << hp::getColorCode(hp::RESET);

            auto timer = hp::startTimer();
            std::string answer = hp::inputField(12, 45, 25, "Type the word: ");
            double elapsed = hp::stopTimer(timer);

            if (elapsed > timeLimit) {
                hp::clearInputField(12, 45, 25);
                hp::Field(12, 45, 25, "Time's up! You lost!", hp::RED);
                hp::wait(1.3);
                play();
                return;
                }

            if (answer == target) {
                score++;
                hp::clearInputField(12, 45, 25);
                hp::Field(12, 45, 25, "Correct! " + std::to_string(score) + "/5", hp::GREEN);
                hp::wait(0.8);
                }
            else {
                hp::clearInputField(12, 45, 25);
                hp::Field(12, 45, 25, "Wrong! You lost!", hp::RED);
                hp::wait(1.3);
                play();
                return;
                }
            }

        int a = Random::rand(1, 3);
        std::string randomItem = Random::choice(rooms[currentRoom].items);
        hp::Field(14, 3, 30, "You won! Earned: " + std::to_string(a) + " " + randomItem + "!", hp::GREEN);
        player.inv[randomItem] += a;
        savePlayer();
        hp::wait(1.3);
        play();
        }

    void guessGame() {
        hp::cls();
        std::cout << "\033[1;3H";
        hp::sp(" Guess Game ", 100);

        int plays = 0;
        int num = 10;
        int maxAttempts = 5;

        while (plays < 3) {
            int secret = Random::rand(1, num);
            int attempts = 0;
            bool guessedCorrect = false;

            while (!guessedCorrect && attempts < maxAttempts) {
                std::string guessStr = hp::inputField(5, 3, 30, "Guess (1-" + std::to_string(num) + ")", "0123456789", 2);
                int guess = std::stoi(guessStr);
                attempts++;

                if (guess < secret) {
                    hp::clearInputField(5, 3, 30);
                    hp::Field(5, 3, 30, "Too Low! (" + std::to_string(maxAttempts - attempts) + " left)", hp::RED);
                    hp::wait(1);
                    hp::clearInputField(5, 3, 30);
                    }
                else if (guess > secret) {
                    hp::clearInputField(5, 3, 30);
                    hp::Field(5, 3, 30, "Too High! (" + std::to_string(maxAttempts - attempts) + " left)", hp::RED);
                    hp::wait(1);
                    hp::clearInputField(5, 3, 30);
                    }
                else {
                    guessedCorrect = true;
                    plays++;

                    if (plays >= 3) {
                        hp::clearInputField(5, 3, 30);
                        int a = Random::rand(1, 3);
                        std::string randomItem = Random::choice(rooms[currentRoom].items);
                        hp::Field(5, 3, 30, "You won! Earned: " + std::to_string(a) + " " + randomItem + "!", hp::GREEN);
                        player.inv[randomItem] += a;
                        savePlayer();
                        hp::wait(1.3);
                        play();
                        return;
                        }
                    else {
                        hp::Field(5, 3, 30, "Correct! " + std::to_string(plays) + "/3 wins. Next round...", hp::GREEN);
                        num += 5;
                        hp::wait(1.3);
                        hp::clearInputField(5, 3, 30);
                        }
                    }
                }

            if (!guessedCorrect) {
                hp::Field(5, 3, 30, "Out of attempts! You lost.", hp::RED);
                hp::wait(1.3);
                play();
                return;
                }
            }
        }

    void memoryGame() {
        hp::cls();
        std::vector<int> sequence;
        int num = 3;
        int plays = 1;

        std::cout << "\033[1;3H";
        hp::sp(" Memory Game ", 100);

        while (plays <= 3) {
            sequence.clear();

            for (int i = 0; i < num; i++) {
                int arrow = Random::rand(0, 3);
                sequence.push_back(arrow);
                showArrow(arrow);
                }

            for (int i = 0; i < sequence.size(); i++) {

                bool answered = false;
                while (!answered) {
                    hp::updateKeyboard();

                    int pressed = -1;
                    if (hp::KeyIsPressed::Up) { answered = true; pressed = 0; }
                    if (hp::KeyIsPressed::Down) { answered = true; pressed = 1; }
                    if (hp::KeyIsPressed::Left) { answered = true; pressed = 2; }
                    if (hp::KeyIsPressed::Right) { answered = true; pressed = 3; }

                    if (answered) {
                        std::cout << "\033[14;50H\033[2K";
                        std::cout << "\033[14;50H\033[2K";
                        if (pressed == sequence[i]) {
                            hp::printCl("Correct!", hp::GREEN);
                            }
                        else {
                            hp::printCl("Wrong! You lost", hp::RED);
                            hp::wait(1);
                            play();
                            return;
                            }
                        while (!_kbhit()) hp::wait(0.05);
                        _getch();
                        }
                    hp::wait(0.05);
                    }
                }
            plays++;
            num++;
            }

        std::cout << "\033[16;50H\033[2K";
        if (!rooms[currentRoom].items.empty()) {
            int a = Random::rand(1, 3);
            std::string randomItem = Random::choice(rooms[currentRoom].items);
            hp::printlnCl("You won! Earned: " + std::to_string(a) + " " + randomItem + "!", hp::GREEN);
            player.inv[randomItem] += a;
            savePlayer();
            }
        else {
            hp::printlnCl("Congrats! Sadly you won nothing", hp::RED);
            }
        hp::wait(1.3);
        play();
        }

    void showArrow(int direction) {
        std::vector<std::string> arrows = { "UP", "DOWN", "LEFT", "RIGHT" };
        std::vector<hp::Color> colors = { hp::RED, hp::BLUE, hp::GREEN, hp::YELLOW };

        std::cout << "\033[10;52H";
        hp::printCl(arrows[direction], colors[direction]);
        hp::wait(0.8);

        std::cout << "\033[10;52H\033[2K";
        hp::wait(0.3);
        }


    void displayRoom() {
        hp::title(rooms[currentRoom].name);
        std::cout << rooms[currentRoom].description << std::endl;
        hp::sp("   Game   ", 40, '-');
        std::cout << rooms[currentRoom].game << std::endl;
        std::cout << rooms[currentRoom].game_description << std::endl;
        }

    bool autoLogin() {
        std::string currentIp = hp::getIp();

        for (auto& entry : fs::directory_iterator(".")) {
            std::string filename = entry.path().filename().string();

            if (filename.ends_with(".sav")) {
                hp::File file;
                std::string data = file.read(filename);

                if (data.empty()) continue;

                try {
                    Player loaded = hp::deserialize<Player>(data);
                    if (currentIp == loaded.Ip && loaded.isLogged) {
                        player = loaded;
                        if (player.c_inv.empty()) {
                            player.c_inv.push_back("Key");
                            savePlayer();
                            }
                        return true;
                        }
                    }
                catch (...) {
                    continue;
                    }
                }
            }
        return false;
        }

    void run() {
        hp::cls();
        if (autoLogin() && !isLoggedOut) {
            GameMenu();
            }
        while (true) {
            if (player.isLogged) {
                hp::cls();
                GameMenu();
                return;
                }
            int choice = hp::arrowMenu("Main Menu", { "Login", "Register", "Exit" });
            switch (choice) {
                case 0: LoginMenu(); break;
                case 1: RegisterMenu(); break;
                case 2: hp::exit(); break;
                default: hp::exit(); break;
                }
            }
        }

    void LoginMenu() {
        hp::cls();
        hp::title("Login");

        std::string name = hp::inputField(5, 3, 30, "Enter your name: ");
        hp::clearInputField(5, 3, 30);

        std::string pass = hp::inputField(5, 3, 30, "Enter your password: ");
        hp::clearInputField(5, 3, 30);

        hp::File file;
        if (file.exists(name + ".sav")) {
            std::string data = file.read(name + ".sav");

            if (data.empty()) {
                hp::Field(5, 3, 30, "Corrupted save file!", hp::RED);
                hp::wait(1);
                hp::clearInputField(5, 3, 30);
                run();
                return;
                }

            try {
                Player loaded = hp::deserialize<Player>(data);
                if (pass == loaded.password) {
                    player = loaded;
                    if (player.c_inv.empty()) {
                        player.c_inv.push_back("Key");
                        savePlayer();
                        }
                    player.isLogged = true;
                    isLoggedOut = false;
                    hp::Field(5, 3, 30, "Login Successful ! Welcome " + player.name + "!", hp::GREEN);
                    hp::wait(1.3);
                    hp::clearInputField(5, 3, 30);
                    GameMenu();
                    }
                else {
                    hp::Field(5, 3, 30, "Incorrect Password", hp::RED);
                    hp::wait(1);
                    hp::clearInputField(5, 3, 30);
                    run();
                    }
                }
            catch (...) {
                hp::Field(5, 3, 30, "Error loading save file!", hp::RED);
                hp::wait(1);
                hp::clearInputField(5, 3, 30);
                run();
                }
            }
        else {
            hp::Field(5, 3, 30, "User not found", hp::RED);
            hp::wait(1);
            hp::clearInputField(5, 3, 30);
            run();
            }
        }

    void RegisterMenu() {
        hp::cls();
        hp::title("Register Menu");
        while (true) {
            player.name = hp::inputField(5, 3, 30, "Enter your name: ");
            hp::clearInputField(5, 3, 30);

            std::string ageStr = hp::inputField(5, 3, 20, "Enter your age: ", "0123456789", 2);
            hp::clearInputField(5, 3, 20);
            try {
                player.age = std::stoi(ageStr);
                if (player.age < 10 || player.age > 100) {
                    hp::Field(5, 3, 30, "Age must be between 10 and 100!", hp::RED);
                    hp::wait(1.3);
                    hp::clearInputField(5, 3, 30);
                    continue;
                    }
                }
            catch (...) {
                hp::Field(5, 3, 30, "Invalid age!", hp::RED);
                hp::wait(1.3);
                hp::clearInputField(5, 3, 30);
                continue;
                }

            player.password = hp::inputField(5, 3, 30, "Enter your password: ");
            hp::clearInputField(5, 3, 30);
            if (player.password.length() < 8) {
                hp::Field(5, 3, 30, "Password must be at least 8 characters!", hp::RED);
                hp::wait(1.3);
                hp::clearInputField(5, 3, 30);
                continue;
                }

            std::string validPass = hp::inputField(5, 3, 30, "Confirm Password: ");
            hp::clearInputField(5, 3, 30);

            if (validPass == player.password) {
                player.isLogged = true;
                hp::File file;
                file.write(player.name + ".sav", hp::serialize(player));
                hp::Field(5, 3, 30, "Registration Successful!", hp::GREEN);
                hp::Field(10, 3, 30, "You are being redirected...", hp::YELLOW);
                hp::wait(1.3);
                hp::clearInputField(5, 3, 30);
                hp::clearInputField(10, 3, 30);
                GameMenu();
                }
            else {
                hp::Field(5, 3, 30, "Passwords do not match", hp::RED);
                hp::wait(1);
                hp::clearInputField(5, 3, 30);
                continue;
                }
            }
        }

    void GameMenu() {
        hp::cls();
        int choice = hp::arrowMenu("Game Menu", { "Adventure Game", "Clicking simulator", "Profile", "Exit" });
        switch (choice) {
            case 0: play(); break;
            case 1: clickG(); break;
            case 2: profile(); break;
            case 3: hp::exit(); break;
            default: hp::exit(); break;
            }
        }

    void clickG() {
        hp::cls();
        int choice = hp::arrowMenu("Clicking Simulator", { "Play", "Buy Items", "Exit" });
        switch (choice) {
            case 0: c_play(); break;
            case 1: c_shop(); break;
            case 2: savePlayer(); GameMenu(); break;
            }
        }


    void c_shop() {
        hp::cls();
        std::cout << "\033[1;3H";
        hp::sp(" Clicking Shop ", 97);
        std::cout << "\033[10;40H";
        int choice = hp::CenteredMenu({ "Multipliers", "Auto Clickers", "Special Items", "Exit" }, hp::YELLOW);

        switch (choice) {
            case 0:c_mult(); break;
            case 1:c_autoP(); break;
            case 2:c_special(); break;
            case 3:savePlayer(); clickG(); break;
            }
        savePlayer();
        }

    void c_special() {
        hp::cls();
        std::cout << "\033[1;3H";
        hp::sp(" Special Items ", 97);
        int choice = hp::CenteredMenu({ "Any key To Click -50 Clicks", "Golden Finger -500 Clicks", "Lucky Charm -300 Clicks", "Exit" }, hp::YELLOW);
        switch (choice) {
            case 0:
                if (player.click.clicks >= 50) {
                    player.click.clicks -= 50;
                    player.click.haveAny = true;
                    hp::printlnCl("\nYou Bought: Any Key To Click", hp::GREEN);
                    hp::wait(1.3);
                    c_special();
                    }
                else {
                    hp::printlnCl("\nNot Enough Clicks", hp::RED);
                    hp::wait(1.3);
                    c_special();
                    }
                savePlayer();
                break;
            case 1:
                if (player.click.clicks >= 500) {
                    player.click.clicks -= 500;
                    player.click.GoldenF = true;
                    hp::printlnCl("\nYou Bought: Golden Finger | Doubles Each Ability", hp::GREEN);
                    hp::wait(1.5);
                    c_special();
                    }
                else {
                    hp::printlnCl("\nNot Enough Clicks", hp::RED);
                    hp::wait(1.3);
                    c_special();
                    }
                savePlayer();
                break;
            case 2:
                if (player.click.clicks >= 300) {
                    player.click.clicks -= 300;
                    player.click.hasLuckyCharm = true;
                    hp::printlnCl("\nYou Bought: Lucky Charm | 10% Chance for 10X Clicks", hp::GREEN);
                    hp::wait(1.5);
                    c_special();
                    }
                else {
                    hp::printlnCl("\nNot Enough Clicks", hp::RED);
                    hp::wait(1.3);
                    c_special();
                    }
                savePlayer();
                break;
            case 3: savePlayer(); c_shop(); break;
            }
        }
    void c_autoP() {
        hp::cls();
        std::cout << "\033[1;3H";
        hp::sp(" Auto Clickers Shop", 97);
        std::cout << "\033[10;40H";
        int choice = hp::CenteredMenu({ "Basic Clicker -500 Clicks", "Super Clicker -2000 Clicks", "Extra Clicker -5000 Clicks", "Supreme Clicker -15000 Clicks", "Exit" }, hp::YELLOW);

        switch (choice) {
            case 0:
                if (!player.click.auto1) {
                    if (player.click.clicks >= 500) {
                        player.click.clicks -= 500;
                        player.click.auto1 = true;
                        player.click.haveAuto = true;
                        player.click.autoTime = 0.8;
                        hp::printlnCl("\n Bought: Basic Clicker", hp::GREEN);
                        hp::wait(1.1);
                        savePlayer();
                        c_autoP();
                        }
                    else {
                        hp::printlnCl("\n Not enough clicks!", hp::RED);
                        hp::wait(1.1);
                        savePlayer();
                        c_autoP();
                        }
                    }
                else {
                    hp::printlnCl("\n You already own this Item!", hp::RED);
                    hp::wait(1.1);
                    savePlayer();
                    c_autoP();
                    }
                break;

            case 1:
                if (player.click.auto1 && !player.click.auto2) {
                    if (player.click.clicks >= 2000) {
                        player.click.clicks -= 2000;
                        player.click.auto2 = true;
                        player.click.haveAuto = true;
                        player.click.autoTime = 0.3;
                        hp::printlnCl("\n Bought: Super Clicker", hp::GREEN);
                        hp::wait(1.1);
                        savePlayer();
                        c_autoP();
                        }
                    else {
                        hp::printlnCl("\n Not enough clicks!", hp::RED);
                        hp::wait(1.1);
                        savePlayer();
                        c_autoP();
                        }
                    }
                else {
                    hp::printlnCl("\n You already own this Item!", hp::RED);
                    hp::wait(1.1);
                    savePlayer();
                    c_autoP();
                    }
                break;

            case 2:
                if (player.click.auto2 && !player.click.auto3) {
                    if (player.click.clicks >= 5000) {
                        player.click.clicks -= 5000;
                        player.click.auto3 = true;
                        player.click.haveAuto = true;
                        player.click.autoTime = 0.1;
                        hp::printlnCl("\n Bought: Extra Clicker", hp::GREEN);
                        hp::wait(1.1);
                        savePlayer();
                        c_autoP();
                        }
                    else {
                        hp::printlnCl("\n Not enough clicks!", hp::RED);
                        hp::wait(1.1);
                        savePlayer();
                        c_autoP();
                        }
                    }
                else {
                    hp::printlnCl("\n You already own this Item!", hp::RED);
                    hp::wait(1.1);
                    savePlayer();
                    c_autoP();
                    }
                break;

            case 3:
                if (player.click.auto3 && !player.click.auto4) {
                    if (player.click.clicks >= 15000) {
                        player.click.clicks -= 15000;
                        player.click.auto4 = true;
                        player.click.haveAuto = true;
                        player.click.autoTime = 0.05;
                        hp::printlnCl("\n Bought: Supreme Clicker", hp::GREEN);
                        hp::wait(1.1);
                        savePlayer();
                        c_autoP();
                        }
                    else {
                        hp::printlnCl("\n Not enough clicks!", hp::RED);
                        hp::wait(1.1);
                        savePlayer();
                        c_autoP();
                        }
                    }
                else {
                    hp::printlnCl("\n You already own this Item!", hp::RED);
                    hp::wait(1.1);
                    savePlayer();
                    c_autoP();
                    }
                break;

            case 4:
                hp::cls();
                savePlayer();
                c_shop();
                break;

            default:
                hp::printlnCl("\n Invalid choice!", hp::RED);
                hp::wait(1.1);
                savePlayer();
                c_autoP();
                break;
            }
        }

    void c_mult() {


        hp::cls();
        std::cout << "\033[1;3H";
        hp::sp(" Multipliers Shop ", 97);
        std::cout << "\033[10;40H";
        int choice = hp::CenteredMenu({ "2x Clicks -100 Clicks", "3x Clicks -500 Clicks", "5x Clicks -2000 Clicks", "10x Clicks -10000 Clicks", "Exit" }, hp::YELLOW);

        switch (choice) {
            case 0:
                if (!player.click.bought1) {
                    if (player.click.clicks >= 100) {
                        player.click.clicks -= 100;
                        player.click.mult = 2;
                        hp::printlnCl("\n You bought a 2x Clicks!", hp::GREEN);
                        player.click.bought1 = true;
                        hp::wait(1.3);
                        c_mult();
                        }
                    else {
                        hp::printlnCl("\n Not Enough Clicks!", hp::RED);
                        hp::wait(1.3);
                        c_mult();
                        }
                    }
                else {
                    hp::printlnCl("\n You already have this ability", hp::YELLOW);
                    hp::wait(1.3);
                    c_mult();
                    }
                savePlayer();
                break;

            case 1:
                if (!player.click.bought2) {
                    if (player.click.clicks >= 500) {
                        player.click.clicks -= 500;
                        player.click.mult = 3;
                        hp::printlnCl("\n You bought a 3x Clicks!", hp::GREEN);
                        player.click.bought2 = true;
                        hp::wait(1.3);
                        c_mult();
                        }
                    else {
                        hp::printlnCl("\n Not Enough Clicks!", hp::RED);
                        hp::wait(1.3);
                        c_mult();
                        }
                    }
                else {
                    hp::printlnCl("\n You already have this ability", hp::YELLOW);
                    hp::wait(1.3);
                    c_mult();
                    }
                savePlayer();
                break;

            case 2:
                if (!player.click.bought3) {
                    if (player.click.clicks >= 2000) {
                        player.click.clicks -= 2000;
                        player.click.mult = 5;
                        hp::printlnCl("\n You bought a 5x Clicks!", hp::GREEN);
                        player.click.bought3 = true;
                        hp::wait(1.3);
                        c_mult();
                        }
                    else {
                        hp::printlnCl("\n Not Enough Clicks!", hp::RED);
                        hp::wait(1.3);
                        c_mult();
                        }
                    }
                else {
                    hp::printlnCl("\n You already have this ability", hp::YELLOW);
                    hp::wait(1.3);
                    c_mult();
                    }
                savePlayer();
                break;

            case 3:
                if (!player.click.bought4) {
                    if (player.click.clicks >= 10000) {
                        player.click.clicks -= 10000;
                        player.click.mult = 10;
                        hp::printlnCl("\n You bought a 10x Clicks!", hp::GREEN);
                        player.click.bought4 = true;
                        hp::wait(1.3);
                        c_mult();
                        }
                    else {
                        hp::printlnCl("\n Not Enough Clicks!", hp::RED);
                        hp::wait(1.3);
                        c_mult();
                        }
                    }
                else {
                    hp::printlnCl("\n You already have this ability", hp::YELLOW);
                    hp::wait(1.3);
                    c_mult();
                    }
                savePlayer();
                break;

            case 4:
                savePlayer();
                hp::cls();
                c_shop();
                break;

            default:
                savePlayer();
                hp::printlnCl("\n Invalid choice!", hp::RED);
                hp::wait(1.3);
                c_mult();
                break;
            }
        }
    void c_play() {
        hp::cls();
        std::cout << "\033[1;3H";
        hp::sp(" Clicking Simulator ", 97);
        std::cout << "\033[18;40H";
        if (player.click.haveAny) {
            hp::printlnCl("Press Any Key to click, C for Auto clicker, Esc to quit", hp::GREEN);
            }
        else {
            hp::printlnCl("Press E to click, C for Auto clicker, Esc to quit", hp::GREEN);
            }

        int prevClicks = -1;
        auto timer = hp::startTimer();
        auto autoTimer = hp::startTimer();
        bool autoActive = false;

        while (true) {
            hp::updateKeyboard();

            if (player.click.haveAny) {
                if (hp::isKeyPressed()) {
                    int clicks = player.click.force * player.click.mult;
                    if (player.click.GoldenF) {
                        clicks *= 2;
                        }
                    if (player.click.hasLuckyCharm && Random::rand(1, 10) == 1) {
                        clicks *= 3;
                        }
                    player.click.clicks += clicks;
                    }
                }
            else if (hp::KeyIsPressed::E) {
                int clicks = player.click.force * player.click.mult;
                if (player.click.GoldenF) {
                    clicks *= 2;
                    }
                if (player.click.hasLuckyCharm && Random::rand(1, 10) == 1) {
                    clicks *= 3;
                    }
                player.click.clicks += clicks;
                }

            if (hp::KeyIsPressed::C) {
                if (player.click.haveAuto) {
                    autoActive = !autoActive;
                    if (autoActive) {
                        autoTimer = hp::startTimer();
                        }
                    }
                }

            if (autoActive) {
                double autoElapsed = hp::stopTimer(autoTimer);
                if (autoElapsed >= player.click.autoTime) {
                    player.click.clicks += player.click.force + player.click.mult;
                    autoTimer = hp::startTimer();
                    }
                }

            if (hp::KeyIsPressed::Escape) {
                savePlayer();
                break;
                }

            if (player.click.clicks != prevClicks) {
                std::cout << "\033[15;50H\033[2K";
                std::cout << "Clicks: " << hp::getColorCode(hp::GREEN) << player.click.clicks << hp::getColorCode(hp::RESET);
                if (autoActive) std::cout << " [AUTO]";
                prevClicks = player.click.clicks;
                }
            hp::wait(0.05);
            }
        clickG();
        }
    void c_invDisplay() {
        for (int i = 0;i < player.c_inv.size();i++) {
            std::cout << player.c_inv[i] << std::endl;
            }
        }
    void craft() {
        hp::cls();
        int choice = hp::arrowMenu("Crafting Forge", { "Iron Armor", "Castle Key", "Strength Potion", "Adventure Key", "Fishing Rod", "Torch", "Exit" });
        switch (choice) {
            case 0: r_armor(); break;
            case 1: castle_key(); break;
            case 2: strength_potion(); break;
            case 3: adventure_key(); break;
            case 4: fishing_rod(); break;
            case 5: torch(); break;
            case 6: GameMenu(); break;
            default: hp::printlnCl("Invalid choice!", hp::RED); hp::wait(1); craft(); break;
            }
        }

    void castle_key() {
        hp::cls();
        hp::setMenu("Crafting: Castle Key", { "1 Golden ore", "3 Iron ores", "3 Sticks" }, false);
        std::string choice;
        std::cout << "Do you wanna craft a Castle Key ? (y/n): ";
        std::cin >> choice;
        if (choice == "Y" || choice == "y") {
            if (player.inv["Iron ore"] >= 3 && player.inv["Golden ore"] >= 1 && player.inv["Stick"] >= 3) {
                player.inv["Iron ore"] -= 3;
                player.inv["Stick"] -= 3;
                player.inv["Golden ore"] -= 1;
                player.inv["Castle Key"]++;
                hp::printlnCl("You crafted a Castle Key !", hp::GREEN);
                savePlayer();
                hp::wait(1.3);
                craft();
                }
            else {
                hp::printlnCl("Missing materials!", hp::RED);
                hp::wait(1.3);
                craft();
                }
            }
        else {
            hp::printlnCl("Crafting cancelled", hp::YELLOW);
            hp::wait(1.3);
            craft();
            }
        }

    void r_armor() {
        hp::cls();
        hp::setMenu("Crafting Iron Armor", { "3 Iron ore", "2 Wood", "1 Water Stone" }, false);
        std::string choice;
        std::cout << "Do you want to craft Iron Armor? (y/n): ";
        std::cin >> choice;

        if (choice == "y" || choice == "Y") {
            if (player.inv["Iron ore"] >= 3 && player.inv["Wood"] >= 2 && player.inv["Water stone"] >= 1) {
                player.inv["Iron ore"] -= 3;
                player.inv["Wood"] -= 2;
                player.inv["Water stone"] -= 1;
                player.inv["Iron Armor"]++;
                hp::printlnCl("Crafted Iron Armor successfully!", hp::GREEN);
                savePlayer();
                hp::wait(1.5);
                craft();
                }
            else {
                hp::printlnCl("Missing materials!", hp::RED);
                hp::wait(1.3);
                craft();
                }
            }
        else {
            hp::printlnCl("Crafting cancelled", hp::YELLOW);
            hp::wait(1.3);
            craft();
            }
        }

    void strength_potion() {
        hp::cls();
        hp::setMenu("Crafting: Strength Potion", { "1 Health Potion", "2 Golden ore", "3 Water", "1 Magic Essence" }, false);
        std::string choice;
        std::cout << "Do you want to craft a Strength Potion? (y/n): ";
        std::cin >> choice;

        if (choice == "y" || choice == "Y") {
            if (player.inv["Health Potion"] >= 1 && player.inv["Golden ore"] >= 2 && player.inv["Water"] >= 3 && player.inv["Magic Essence"] >= 1) {
                player.inv["Health Potion"] -= 1;
                player.inv["Golden ore"] -= 2;
                player.inv["Water"] -= 3;
                player.inv["Magic Essence"] -= 1;
                player.inv["Strength Potion"]++;
                hp::printlnCl("Crafted Strength Potion!", hp::GREEN);
                savePlayer();
                hp::wait(1.5);
                craft();
                }
            else {
                hp::printlnCl("Missing materials!", hp::RED);
                hp::wait(1.3);
                craft();
                }
            }
        else {
            hp::printlnCl("Crafting cancelled", hp::YELLOW);
            hp::wait(1.3);
            craft();
            }
        }

    void adventure_key() {
        hp::cls();
        hp::setMenu("Crafting: Adventure Key", { "5 Wood", "3 Iron ore", "1 Golden ore", "1 Diamond" }, false);
        std::string choice;
        std::cout << "Do you want to craft an Adventure Key? (y/n): ";
        std::cin >> choice;

        if (choice == "y" || choice == "Y") {
            if (player.inv["Wood"] >= 5 && player.inv["Iron ore"] >= 3 && player.inv["Golden ore"] >= 1 && player.inv["Diamond"] >= 1) {
                player.inv["Wood"] -= 5;
                player.inv["Iron ore"] -= 3;
                player.inv["Golden ore"] -= 1;
                player.inv["Diamond"] -= 1;
                player.inv["Adventure Key"]++;
                hp::printlnCl("Crafted Adventure Key!", hp::GREEN);
                savePlayer();
                hp::wait(1.5);
                craft();
                }
            else {
                hp::printlnCl("Missing materials!", hp::RED);
                hp::wait(1.3);
                craft();
                }
            }
        else {
            hp::printlnCl("Crafting cancelled", hp::YELLOW);
            hp::wait(1.3);
            craft();
            }
        }

    void fishing_rod() {
        hp::cls();
        hp::setMenu("Crafting: Fishing Rod", { "3 Wood", "1 String", "1 Iron ore" }, false);
        std::string choice;
        std::cout << "Do you want to craft a Fishing Rod? (y/n): ";
        std::cin >> choice;

        if (choice == "y" || choice == "Y") {
            if (player.inv["Wood"] >= 3 && player.inv["String"] >= 1 && player.inv["Iron ore"] >= 1) {
                player.inv["Wood"] -= 3;
                player.inv["String"] -= 1;
                player.inv["Iron ore"] -= 1;
                player.inv["Fishing Rod"]++;
                hp::printlnCl("Crafted Fishing Rod!", hp::GREEN);
                savePlayer();
                hp::wait(1.5);
                craft();
                }
            else {
                hp::printlnCl("Missing materials!", hp::RED);
                hp::wait(1.3);
                craft();
                }
            }
        else {
            hp::printlnCl("Crafting cancelled", hp::YELLOW);
            hp::wait(1.3);
            craft();
            }
        }

    void torch() {
        hp::cls();
        hp::setMenu("Crafting: Torch", { "2 Stick" }, false);
        std::string choice;
        std::cout << "Do you want to craft a Torch? (y/n): ";
        std::cin >> choice;

        if (choice == "y" || choice == "Y") {
            if (player.inv["Stick"] >= 2) {
                player.inv["Stick"] -= 2;;
                player.inv["Torch"]++;
                hp::printlnCl("Crafted Torch!", hp::GREEN);
                savePlayer();
                hp::wait(1.5);
                craft();
                }
            else {
                hp::printlnCl("Missing materials!", hp::RED);
                hp::wait(1.3);
                craft();
                }
            }
        else {
            hp::printlnCl("Crafting cancelled", hp::YELLOW);
            hp::wait(1.3);
            craft();
            }
        }

    void profile() {
        hp::cls();
        int choice = hp::arrowMenu("Settings", { "User Information", "Modify User", "Log Out", "Exit" });
        switch (choice) {
            case 0: UserInfo(); break;
            case 1: ModifyUser(); break;
            case 2:
                player.isLogged = false;
                isLoggedOut = true;
                hp::printlnCl("Logged Out successfully", hp::GREEN);
                savePlayer();
                hp::wait(1);
                run();
                break;
            case 3: GameMenu(); break;
            default:
                hp::printlnCl("Invalid option", hp::RED);
                hp::wait(1);
                profile();
                break;
            }
        }

    void UserInfo() {
        hp::cls();
        hp::title("User Information");
        std::cout << "Username: " << player.name << '\n';
        std::cout << "Age: " << player.age << '\n';
        std::cout << "ID: " << player.id << '\n';
        hp::waitForEnter();
        profile();
        }

    void ModifyUser() {
        hp::cls();
        int choice = hp::arrowMenu("Modify User", { "Modify Username", "Modify Age", "Modify Password", "Delete User", "Generate New ID", "Back" });
        switch (choice) {
            case 0: m_User(); break;
            case 1: m_Age(); break;
            case 2: m_Password(); break;
            case 3: m_Delete(); break;
            case 4: m_ID(); break;
            case 5: profile(); break;
            default: profile(); break;
            }
        }

    void m_Age() {
        hp::cls();
        while (true) {
            int n_age = get<int>("Enter new age: ");
            if (n_age == player.age) {
                hp::printlnCl("This is already your age!", hp::RED);
                hp::wait(1.3);
                continue;
                }
            if (n_age < 10 || n_age > 100) {
                hp::printlnCl("Age must be between 10 and 100", hp::RED);
                hp::wait(1.3);
                continue;
                }
            std::string choice = getStr("Change age from " + std::to_string(player.age) + " to " + std::to_string(n_age) + "? (y/n): ");
            if (choice == "y" || choice == "Y") {
                player.age = n_age;
                savePlayer();
                hp::printlnCl("Modification successful!", hp::GREEN);
                hp::waitForEnter();
                ModifyUser();
                break;
                }
            else {
                hp::printlnCl("Modification Cancelled", hp::RED);
                hp::waitForEnter();
                ModifyUser();
                break;
                }
            }
        }

    void m_User() {
        hp::cls();
        while (true) {
            std::string N_name = getStr("Enter new username: ");
            if (N_name == player.name) {
                hp::printlnCl("This is already your name!", hp::RED);
                hp::wait(1.3);
                continue;
                }

            hp::File file;
            if (file.exists(N_name + ".sav")) {
                hp::printlnCl("Username already taken!", hp::RED);
                hp::wait(1.3);
                continue;
                }

            std::string choice = getStr("Change name from " + player.name + " to " + N_name + "? (y/n): ");
            if (choice == "y" || choice == "Y") {
                hp::File file2;
                file2.del(player.name + ".sav");
                player.name = N_name;
                file2.write(player.name + ".sav", hp::serialize(player));
                hp::printlnCl("Modification successful!", hp::GREEN);
                savePlayer();
                hp::waitForEnter();
                ModifyUser();
                break;
                }
            else {
                hp::printlnCl("Modification Cancelled", hp::RED);
                hp::waitForEnter();
                ModifyUser();
                break;
                }
            }
        }

    void m_Password() {
        hp::cls();
        while (true) {
            std::string oldPass = getStr("Enter old password: ");
            if (oldPass != player.password) {
                hp::printlnCl("Incorrect password!", hp::RED);
                hp::wait(1.3);
                continue;
                }
            std::string newPass = getStr("Enter new password: ");
            std::string confirmPass = getStr("Confirm new password: ");
            if (newPass != confirmPass) {
                hp::printlnCl("Passwords do not match!", hp::RED);
                hp::wait(1.3);
                continue;
                }
            hp::File file;
            file.del(player.name + ".sav");
            player.password = newPass;
            file.write(player.name + ".sav", hp::serialize(player));
            hp::printlnCl("Password changed successfully!", hp::GREEN);
            savePlayer();
            hp::waitForEnter();
            ModifyUser();
            break;
            }
        }

    void m_Delete() {
        hp::cls();
        std::string choice = getStr("Are you sure you want to delete your account? (y/n): ");
        if (choice == "y" || choice == "Y") {
            hp::File file;
            file.del(player.name + ".sav");
            hp::printlnCl("Account deleted successfully!", hp::RED);
            player.isLogged = false;
            hp::wait(1.5);
            run();
            }
        else {
            hp::printlnCl("Deletion cancelled", hp::YELLOW);
            hp::wait(1);
            ModifyUser();
            }
        }

    void m_ID() {
        hp::cls();
        player.id = GenerateId(Random::rand(10, 15));
        savePlayer();
        hp::printlnCl("New ID generated: " + player.id, hp::GREEN);
        savePlayer();
        hp::waitForEnter();
        ModifyUser();
        }
    };

int main() {
    }
