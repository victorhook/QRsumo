#ifndef QRSUMO_H
#define QRSUMO_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN_VBUS_DETECT 0
#define PIN_VSYS_MEASURE 0
#define PIN_RANGE_FRONT_LEFT 0
#define PIN_RANGE_FRONT_CENTER 0
#define PIN_RANGE_FRONT_RIGHT 0
#define PIN_PWM_AIN1 0
#define PIN_PWM_AIN2 0
#define PIN_PWM_BIN1 0
#define PIN_PWM_BIN2 0
#define PIN_NFAULT 0
#define PIN_LINE_SENSE_ENABLE 0
#define PIN_LINE_SENSE_FRONT_LEFT 0
#define PIN_LINE_SENSE_BACK_CENTER 0
#define PIN_LINE_SENSE_FRONT_RIGHT 0
#define PIN_RGB 0
#define PIN_LED_GREEN 0
#define PIN_LED_RED 0
#define PIN_IR_RECEIVER 0
#define PIN_IR_RANGE_ENABLE 0


class QRSumo
{
    public:
        QRSumo();
        ~QRSumo();
        void init();
    private:
        Adafruit_NeoPixel m_strip;
        
        void blink_bootup_sequence();
};


extern QRSumo qrsumo;


#endif /* QRSUMO_H */
