#include <Servo.h>

#define SERVOS 5

Servo* motors[SERVOS] = {new Servo(), new Servo(), new Servo(), new Servo(), new Servo()};
Servo* hand = new Servo();

uint8_t pins[] = {3, 5, 6, 9, 10};

char chord_ids[] = {' ', 'C', 'G', 'a', 'F'};
uint8_t chords[][SERVOS] = { {90, 90, 90, 90, 100},
                             {90, 90, 90, 40, 100},
                             {90, 150, 140, 150, 100},
                             {50, 90, 90, 90, 100},
                             {50, 90, 90, 90, 50} };

/* transform chord (char) into number (uint) */
uint8_t transform(char chord)
{
    for (uint8_t i = 0; i < (sizeof(chord_ids)/sizeof(*chord_ids)); i++) {
        if (chord == chord_ids[i])
            return i;
    }
}

void play(char chord)
{
    uint8_t chord_id = transform(chord);

    for (uint8_t i = 0; i < (sizeof(motors)/sizeof(*motors)); i++)
        motors[i]->write(chords[chord_id][i]);
}

void move_hand(char dir)
{
    if (dir == 'u')
        hand->write(30);
    else if (dir == 'd')
        hand->write(150);
}

void setup()
{
    for (uint8_t i = 0; i < (sizeof(motors)/sizeof(*motors)); i++)
        motors[i]->attach(pins[i]);

    hand->attach(11);
    move_hand('u');
}

void loop()
{
    play('C');
    move_hand('u');
    delay(800);

    play('G');
    move_hand('d');
    delay(800);

    play('a');
    move_hand('u');
    delay(800);

    play('F');
    move_hand('d');
    delay(800);

    play('C');
    move_hand('u');
    delay(800);

    play('G');
    move_hand('d');
    delay(800);

    play('a');
    move_hand('u');
    delay(800);

    play('C');
    move_hand('d');
    delay(800);
}
