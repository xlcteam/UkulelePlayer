#include <Servo.h>

#define SERVOS 5
#define WRIST_DELAY 100

Servo* motors[SERVOS] = {new Servo(), new Servo(), new Servo(), new Servo(), new Servo()};
Servo* hand = new Servo();
Servo* wrist = new Servo();

uint8_t pins[] = {2, 3, 4, 5, 6};

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

void wrist_on(void)
{
    wrist->write(20);    
}

void wrist_off(void)
{
    wrist->write(70);
}

void strings(uint8_t count)
{
    for (uint8_t i = 0; i < count; i++) {
        wrist_on();
        delay(WRIST_DELAY);
        move_hand('d');
        delay(500);
        wrist_off();
        delay(WRIST_DELAY);
        move_hand('u');
        delay(500);
    }
}

void setup()
{
    for (uint8_t i = 0; i < (sizeof(motors)/sizeof(*motors)); i++)
        motors[i]->attach(pins[i]);

    hand->attach(7);
    wrist->attach(8);

    /* reset servos to default position */
    play(' ');
    wrist_off();
    delay(WRIST_DELAY);
    move_hand('u');
    delay(500);
}

char chords_to_play[] = {'C', 'G', 'a', 'F', 'C', 'G', 'a', 'C'};
void loop()
{
    for (uint8_t i = 0; i < (sizeof(chords_to_play)/sizeof(*chords_to_play)); i++) {
        play(chords_to_play[i]);
        strings(2);
    }
}
