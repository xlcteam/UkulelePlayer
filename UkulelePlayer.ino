#include <Servo.h>

#define SERVOS 5
#define WRIST_DELAY 100
#define HAND_DELAY 360

#define LED 13

#define START_BUTTON 53

Servo* motors[SERVOS] = {new Servo(), new Servo(), new Servo(), new Servo(), new Servo()};
Servo* hand = new Servo();
Servo* wrist = new Servo();
Servo* drums[2] = {new Servo(), new Servo()};

uint8_t pins[] = {2, 3, 4, 5, 6};
uint8_t drum_pins[] = {9, 10};
uint8_t drum_to_play = 1;

uint8_t drum_chords[][2] = { {0, 180}, /* default position */
                             {50, 180}, /* right arm down */
                             {0, 130} }; /* left arm down */

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

void play_drum(uint8_t pos)
{
    for (uint8_t i = 0; i < (sizeof(drums)/sizeof(*drums)); i++)
        drums[i]->write(drum_chords[pos][i]);
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

void led(void)
{
    digitalWrite(LED, HIGH);
    delay(5);
    digitalWrite(LED, LOW);
}

void strings(uint8_t count)
{
    for (uint8_t i = 0; i < count; i++) {
        wrist_on();
        delay(WRIST_DELAY);
        move_hand('d');

        play_drum(drum_to_play);
        drum_to_play = (drum_to_play % 2) + 1;

        delay(HAND_DELAY);
        wrist_off();
        delay(WRIST_DELAY);
        move_hand('u');
        delay(HAND_DELAY);
    }
}

void setup()
{
    for (uint8_t i = 0; i < (sizeof(motors)/sizeof(*motors)); i++)
        motors[i]->attach(pins[i]);
        
    pinMode(LED, OUTPUT);
    pinMode(START_BUTTON, INPUT_PULLUP);

    hand->attach(7);
    wrist->attach(8);

    drums[0]->attach(drum_pins[0]);
    drums[1]->attach(drum_pins[1]);

    /* reset servos to default position */
    play_drum(0);
    play(' ');
    wrist_off();
    delay(WRIST_DELAY);
    move_hand('u');
    delay(500);
}

char chords_to_play[] = {'C', 'G', 'a', 'F', 'C', 'G', 'a', 'C'};
void loop()
{
    if (digitalRead(START_BUTTON) == 0) {
        for (uint8_t rounds = 0; rounds < 3; rounds++) {
            for (uint8_t i = 0; i < (sizeof(chords_to_play)/sizeof(*chords_to_play)); i++) {
                play(chords_to_play[i]);
                strings(2);
            }
        }
    }
}
