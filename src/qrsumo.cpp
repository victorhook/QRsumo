#include "qrsumo.h"


QRSumo::QRSumo()
: m_strip(Adafruit_NeoPixel(1, PIN_RGB, NEO_GRB + NEO_KHZ800))
{

}

void QRSumo::init()
{
    // Outputs
    pinMode(PIN_LED_GREEN, OUTPUT);
    pinMode(PIN_LED_RED, OUTPUT);
    pinMode(PIN_LINE_SENSE_ENABLE, OUTPUT);
    pinMode(PIN_IR_RANGE_ENABLE, OUTPUT);
    pinMode(PIN_PWM_AIN1, OUTPUT);
    pinMode(PIN_PWM_AIN2, OUTPUT);
    pinMode(PIN_PWM_BIN1, OUTPUT);
    pinMode(PIN_PWM_BIN2, OUTPUT);

    // Inputs
    pinMode(PIN_VBUS_DETECT, INPUT);
    pinMode(PIN_VSYS_MEASURE, INPUT);
    pinMode(PIN_RANGE_FRONT_LEFT, INPUT);
    pinMode(PIN_RANGE_FRONT_CENTER, INPUT);
    pinMode(PIN_RANGE_FRONT_RIGHT, INPUT);
    pinMode(PIN_LINE_SENSE_FRONT_LEFT, INPUT);
    pinMode(PIN_LINE_SENSE_BACK_CENTER, INPUT);
    pinMode(PIN_LINE_SENSE_FRONT_RIGHT, INPUT);
    pinMode(PIN_NFAULT, INPUT);

    // Set default values to outputs
    digitalWrite(PIN_LED_GREEN, LOW);
    digitalWrite(PIN_LED_GREEN, LOW);
    digitalWrite(PIN_LINE_SENSE_ENABLE, LOW);
    digitalWrite(PIN_IR_RANGE_ENABLE, LOW);
    digitalWrite(PIN_PWM_AIN1, LOW);
    digitalWrite(PIN_PWM_AIN2, LOW);
    digitalWrite(PIN_PWM_BIN1, LOW);
    digitalWrite(PIN_PWM_BIN2, LOW);

    m_strip.begin();
}


// -- Private -- //

void QRSumo::blink_bootup_sequence()
{
    for (int i = 0; i < 3; i++)
    {
        digitalWrite(PIN_LED_GREEN, HIGH);
        digitalWrite(PIN_LED_RED, LOW);
        delay(250);
        digitalWrite(PIN_LED_GREEN, LOW);
        digitalWrite(PIN_LED_RED, HIGH);
        delay(250);
    }
}


QRSumo qrsumo;