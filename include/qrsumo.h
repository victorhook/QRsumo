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


typedef enum
{
    MOTOR_LEFT  = 0,
    MOTOR_RIGHT = 1
} motor_type_t;

typedef enum
{
    DIRECTION_FORWARD  = 0,
    DIRECTION_BACKWARD = 1
} direction_t;

struct Motor {
    motor_type_t type;
    direction_t  direction;
    uint8_t      duty;
    uint8_t      pin_in1;
    uint8_t      pin_in2;
};


class QRsumo
{
    public:
        QRsumo();
        ~QRsumo();
        void init();

        /*
        Parameters:
            color: 24 bit RGB, MSB.
        */
        void ledSetRgb(const uint32_t color);
        void ledSetGreen(const bool on);
        void ledSetRed(const bool on);

        /*
        Parameters:
            motor: Which motor to set direction for.
            direction: Which direction to set.
        
        Returns true if direction was successfully set.
        */
        bool setMotorDirection(const motor_type_t motor, const direction_t direction);

        /*
        Parameters:
            motor: Which motor to set duty cycle for.
            duty: Motor duty cycle, value between 0-100.
        
        Returns true if duty cycle was successfully set.
        */
        bool setMotorDutyCycle(const motor_type_t motor, const uint8_t duty);

        /*
            Returns the battery voltages, in volts.
        */
        float getBatteryVoltage();

        /*
            Returns true if USB power is detected.
        */
        bool usbIsConnected();

        /*
            Enables or disables the line sensing sensors.
        */
        void lineSenseEnableSet(const bool enable);

        /*
            Enables or disables the ir ranging sensors.
        */
        void irRangingEnableSet(const bool enable);

    private:
        Adafruit_NeoPixel m_rgb;
        struct Motor m_motor_left;
        struct Motor m_motor_right;
        
        void blinkBootupSequence();
        void updateMotors();
        void setMotor(const Motor& motor);
};


extern QRsumo qrsumo;


#endif /* QRSUMO_H */
