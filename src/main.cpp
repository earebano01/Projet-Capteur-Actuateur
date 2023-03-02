/*
Titre : Projet Capteur Actuateur
Auteur: Adonis Rebano
Date : 02/03/2023
Description : créer un projet de votre choix avec les conditions suivantes :
- avoir un capteur
- un actuateur
- une logique importante
- code en orienté objet
Version : 0.0.1
*/

//---------declaration pour notre libraire-----//
#include <Arduino.h>
#include <Wire.h>
#include "DFRobot_LCD.h" 
#include  "Capteur.h"

#define PIR_PIN 2                          // on utilise la broche numero 2
#define FLAMME_PIN 3                       // on utilise la broche numero 3

const int colorR = 211;                      // voici la declaration pour des variable qu'on utilise pour notre
const int colorG = 211;                    // lcd, on declare notre variable pour notre capture de mouvement et
const int colorB = 211;           
                   
int compteurDecran = 0;                    // notre compteur pour changer la position de nos ecran
int next = 1;                              // notre variable pour notre bouton

boolean next_currentState = LOW;           // notre variable pour l'etat actuelle du bouton
boolean next_lastState = LOW;              // notre variable pour l'etat derniere du bouton

//-----on cree une fonctionne pour le debounce-----//
boolean debounce(boolean lastState, int pin)
{
    boolean currentState = digitalRead(pin);
    if (lastState != currentState)
    {
        delay(5);
        currentState = digitalRead(pin);
    }
    return currentState;
}

DFRobot_LCD lcd(16, 2);                     // la classe et objets du notre libraire LCD
capteur myObj1(PIR_PIN, FLAMME_PIN);

void setup()
{
//-----il faut trouver notre code pour initialisation dans partie-----//
    Serial.begin(9600); 

    // notre initialisation pour notre 16x2 LCD
    lcd.init();
    lcd.setRGB(colorR, colorG, colorB); 
    lcd.setCursor(3, 0);
    lcd.print("BONJOUR ET");             // on affiche notre message de bienvenue
    lcd.setCursor(3, 1);
    lcd.print("BIENVENUE");           

    // notre initialisation pour notre capteur de mouvement
    myObj1.init();
}

void loop()
{
    next_currentState = debounce(next_lastState, next); // notre debounce fonctionne pour notre bouton

    if (next_lastState == LOW && next_currentState == HIGH) // lorque le bouton est pressé
    {                
        lcd.clear();                    // l'écran LCD sera effacé et passera à la page suivante.
        if (compteurDecran < 2)         // notre compteur d'écran qui n'est pas plus de 3 écran
        {                                    
            compteurDecran++;           // si notre écran est inférieur à 3, on l'incrémente de 1
        }
        else if (compteurDecran == 2)   // lorsq'on atteint la page 3
        {
            compteurDecran = 1;         // on affiche la page 1, et avec cette façon on fait une boucle
        }
    }

    next_lastState = next_currentState;

//-----on utilise l'instruction switch pour parcourir chaque écran, et on utilise chaque cas pour chaque capteur qu'on affiche-----//
switch (compteurDecran)
    {
        case 1:
            { // Capteur de mouvement
                if (myObj1.readMouvement() == HIGH)
                {
                    lcd.setCursor(3, 0);
                    lcd.print("MOUVEMENT");
                    lcd.setCursor(2, 1);
                    lcd.print("Detecte: Oui");
                    delay(1000);
                }
                else
                {
                    lcd.setCursor(3, 0);
                    lcd.print("MOUVEMENT"); 
                    lcd.setCursor(2, 1);
                    lcd.print("Detecte: Non");
                    delay(1000);
                }
            }
        break;
        case 2:
            { // Capteur de la flamme
                if (myObj1.readFlamme() == HIGH)
                {
                    lcd.setCursor(5, 0);
                    lcd.print("FLAMME");
                    lcd.setCursor(2, 1);
                    lcd.print("Detecte: Oui");
                    delay(1000);
                }
                else
                {
                    lcd.setCursor(5, 0);
                    lcd.print("FLAMME"); 
                    lcd.setCursor(2, 1);
                    lcd.print("Detecte: Non");
                    delay(1000);
                }
            }
        break;
    } // fin du switch
}