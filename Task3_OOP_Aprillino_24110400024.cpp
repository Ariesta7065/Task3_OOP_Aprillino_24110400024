#include <iostream>
#include <vector>
using namespace std;

// ===== KASUS 1: NOTIFIKASI SISTEM =====
class Notification {
public:
    virtual void send(string message, string recipient) = 0;
    virtual ~Notification() {}
};

class EmailNotification : public Notification {
public:
    void send(string message, string recipient) override {
        cout << "[Email] To: " << recipient << " | Message: " << message << endl;
    }
};

class SMSNotification : public Notification {
public:
    void send(string message, string recipient) override {
        cout << "[SMS] To: " << recipient << " | Message: " << message << endl;
    }
};

class PushNotification : public Notification {
public:
    void send(string message, string recipient) override {
        cout << "[Push] To: " << recipient << " | Message: " << message << endl;
    }
};

class NotificationManager {
private:
    vector<Notification*> channels;
public:
    void addChannel(Notification* channel) {
        channels.push_back(channel);
    }
    void sendAll(string message, string recipient) {
        for (auto channel : channels) {
            channel->send(message, recipient);
        }
    }
};

// ===== KASUS 2: GAME CHARACTER SYSTEM =====
class Character {
protected:
    string name;
    int health;
    int attackPower;
public:
    Character(string n, int h, int a) : name(n), health(h), attackPower(a) {}
    virtual void display() = 0;
    virtual void takeDamage(int damage) {
        health -= damage;
        cout << name << " takes " << damage << " damage! Remaining Health: " << health << endl;
    }
    virtual ~Character() {}
    string getName() { return name; }
};

class Player : public Character {
public:
    Player(string n, int h, int a) : Character(n, h, a) {}
    void display() override {
        cout << "[Player] Name: " << name << " | Health: " << health << " | Attack Power: " << attackPower << endl;
    }
};

class Enemy : public Character {
public:
    Enemy(string n, int h, int a) : Character(n, h, a) {}
    void display() override {
        cout << "[Enemy] Name: " << name << " | Health: " << health << " | Attack Power: " << attackPower << endl;
    }
};

class NPC : public Character {
public:
    NPC(string n, int h) : Character(n, h, 0) {}
    void display() override {
        cout << "[NPC] Name: " << name << " | Health: " << health << endl;
    }
};

class Healer {
public:
    virtual void heal(Character& target) = 0;
};

class Attacker {
public:
    virtual void attack(Character& target) = 0;
};

class Defender {
public:
    virtual void defend() = 0;
};

class Warrior : public Player, public Attacker, public Defender {
public:
    Warrior(string n, int h, int a) : Player(n, h, a) {}

    void attack(Character& target) override {
        cout << name << " attacks " << target.getName() << " for " << attackPower << " damage!" << endl;
        target.takeDamage(attackPower);
    }

    void defend() override {
        cout << name << " is defending! Damage received will be reduced." << endl;
    }
};

class Mage : public Player, public Healer {
public:
    Mage(string n, int h, int a) : Player(n, h, a) {}

    void heal(Character& target) override {
        int healAmount = 20;
        cout << name << " heals " << target.getName() << " for " << healAmount << " HP!" << endl;
    }
};

int main() {
    // Notifikasi
    NotificationManager manager;
    EmailNotification email;
    SMSNotification sms;
    PushNotification push;

    manager.addChannel(&email);
    manager.addChannel(&sms);
    manager.addChannel(&push);

    manager.sendAll("System update available!", "User123");

    // Game Characters
    Warrior w("Knight", 100, 25);
    Mage m("Wizard", 80, 10);
    Enemy e("Orc", 120, 15);

    w.display();
    m.display();
    e.display();

    w.attack(e);
    m.heal(w);
    w.defend();

    return 0;
}
