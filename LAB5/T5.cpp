//
//  T5.cpp
//  LAB5
//
//  Created by Laith Oudah on 2020-12-09.
//

#include <iostream>

using namespace std;

// Abstract class, dessa behöver replaceas
class Creature {
public:
    Creature(string name) {
        CreatureName = name;
    }
    virtual void DoAction() = 0;
    virtual void DrawOnScreen() = 0;
protected: // Får ej ändras
    string CreatureName;
};

class Player : public Creature {
public:
    Player(string name) : Creature(name) {}
    void DoAction() {
        cout << " is attacking!!" << endl;
    }

    void DrawOnScreen() {
        cout << "Player <" << CreatureName << ">";
        DoAction();
    }
};

class Monster : public Creature {
public:
    Monster(string name) : Creature(name) {}
    void DoAction() {
        cout << " is doing monster stuff!!" << endl;
    }

    void DrawOnScreen() {
        cout << "Monster <" << CreatureName << ">";
        DoAction();
    }
};

class Dragon : public Monster {
public:
    Dragon(string name) : Monster(name) {}

    void DoAction() {
        cout << " is breathing fire!!" << endl;
    }

    void DrawOnScreen() {
        cout << "Dragon <" << CreatureName << ">";
        DoAction();
    }
};

class Wildpig : public Monster {
public:
    Wildpig(string name) : Monster(name) {}
    void DoAction() {
        cout << " is running!!" << endl;
    }

    void DrawOnScreen() {
        cout << "Wildpig <" << CreatureName << ">";
        DoAction();
    }
};

int main() {

    Player hero("Kick_Ass"); // En hero som heter Kick_Ass osv.
    Monster mon("UFO");
    Wildpig pig("I'm_Hungry");
    Dragon drag("I'm_the_Boss");

    // Objekt som pekar på 4st adresser, nedan.
    Creature* object[4];

    object[0] = &hero;
    object[1] = &mon;
    object[2] = &pig;
    object[3] = &drag;
    object[0]->DrawOnScreen();
    object[1]->DrawOnScreen();
    object[2]->DrawOnScreen();
    object[3]->DrawOnScreen();

    return 0;
}


