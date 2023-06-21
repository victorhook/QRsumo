#include "qrsumo.h"


QRsumo::QRsumo()
: m_rgb(Adafruit_NeoPixel(1, PIN_RGB, NEO_GRB + NEO_KHZ800)),
  m_motor_left({
    .type=MOTOR_LEFT,
    .direction=DIRECTION_FORWARD,
    .duty=0,
    .pin_in1=PIN_PWM_AIN1,
    .pin_in2=PIN_PWM_AIN2
  }),
  m_motor_right({
    .type=MOTOR_RIGHT,
    .direction=DIRECTION_FORWARD,
    .duty=0,
    .pin_in1=PIN_PWM_BIN1,
    .pin_in2=PIN_PWM_BIN2
  })
{

}

QRsumo::~QRsumo()
{

}

void QRsumo::init()
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
    digitalWrite(PIN_LED_RED, LOW);
    digitalWrite(PIN_LINE_SENSE_ENABLE, LOW);
    digitalWrite(PIN_IR_RANGE_ENABLE, LOW);
    digitalWrite(PIN_PWM_AIN1, LOW);
    digitalWrite(PIN_PWM_AIN2, LOW);
    digitalWrite(PIN_PWM_BIN1, LOW);
    digitalWrite(PIN_PWM_BIN2, LOW);

    // Set initial motor settings
    setMotorDirection(MOTOR_LEFT,  DIRECTION_FORWARD);
    setMotorDirection(MOTOR_RIGHT, DIRECTION_FORWARD);

    // Turn on all sensors by default
    lineSenseEnableSet(true);
    irRangingEnableSet(true);

    m_rgb.begin();

    blinkBootupSequence();
}


void QRsumo::ledSetRgb(const uint32_t color)
{
   m_rgb.setPixelColor(0, color);
   m_rgb.show();
}

void QRsumo::ledSetGreen(const bool on)
{
    digitalWrite(PIN_LED_GREEN, on);
}

void QRsumo::ledSetRed(const bool on)
{
    digitalWrite(PIN_LED_RED, on);
}

bool QRsumo::setMotorDirection(const motor_type_t motor, const direction_t direction)
{
    if (direction != DIRECTION_FORWARD || direction != DIRECTION_BACKWARD)
    {
        return false;
    }

    switch (motor)
    {
        case MOTOR_LEFT:
            m_motor_left.direction = direction;
            break;
        case MOTOR_RIGHT:
            m_motor_right.direction = direction;
            break;
        default:
            return false;
    }

    return true;
}

bool QRsumo::setMotorDutyCycle(const motor_type_t motor, const uint8_t duty)
{
    if (duty > 100)
    {
        return false;
    }

    switch (motor)
    {
        case MOTOR_LEFT:
            m_motor_left.duty = duty;
            break;
        case MOTOR_RIGHT:
            m_motor_right.duty = duty;
            break;
        default:
            return false;
    }

    return true;
}

float QRsumo::getBatteryVoltage()
{
    const int R1 = 5000;
    const int R2 = 10000;
    const float VREF = 3.3;
    constexpr float conversion = 1.0 / (R2 / (float) (R1 + R2));

    int raw = analogRead(PIN_VSYS_MEASURE);
    
    return (raw / 1024.0) * conversion * VREF;
}

bool QRsumo::usbIsConnected()
{
    return digitalRead(PIN_VBUS_DETECT);
}

void QRsumo::lineSenseEnableSet(const bool enable)
{
    digitalWrite(PIN_LINE_SENSE_ENABLE, enable);
}

void QRsumo::irRangingEnableSet(const bool enable)
{
    digitalWrite(PIN_IR_RANGE_ENABLE, enable);
}



// -- Private -- //

void QRsumo::blinkBootupSequence()
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

void QRsumo::updateMotors()
{
   setMotor(m_motor_left);
   setMotor(m_motor_right);
}

void QRsumo::setMotor(const Motor& motor)
{
    /*
        xIN1 xIN2 
        PWM     0   Forward PWM, fast decay
          1   PWM   Forward PWM, slow decay
          0   PWM   Reverse PWM, fast decay
        PWM     1   Reverse PWM, slow decay
    */
   int constrained_duty = map(motor.duty, 0, 100, 0, 1024);
    if (motor.direction == DIRECTION_FORWARD)
    {
        analogWrite(motor.pin_in1, constrained_duty);
        analogWrite(motor.pin_in2, 0);
    }
    else
    {
        analogWrite(motor.pin_in1, 0);
        analogWrite(motor.pin_in2, constrained_duty);
    }
}


QRsumo qrsumo;
