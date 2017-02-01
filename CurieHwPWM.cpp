#include "CurieHwPWM.h"

CurieHwPWMStateType pwmPinState[4] = {UNRESERVED, UNRESERVED, UNRESERVED, UNRESERVED};

CurieHwPWM::CurieHwPWM(uint8_t pin) {
    PinDescription *_p = &g_APinDescription[pin];

    if (digitalPinHasPWM(pin) && pwmPinState[_p->ulPwmChan] == UNRESERVED) {
        p = _p;
        p->ulGPIOType = SOC_PWM;
        p->ulPinMode = PWM_MUX_MODE;
        SET_PIN_MODE(p->ulSocPin, PWM_MUX_MODE);
        pwmPinState[p->ulPwmChan] = UNCONFIGURED;
    }
};

void CurieHwPWM::reserve() {
    if (pwmPinState[p->ulPwmChan] != UNRESERVED) return;
    p->ulGPIOType = SOC_PWM;
    p->ulPinMode = PWM_MUX_MODE;
    SET_PIN_MODE(p->ulSocPin, PWM_MUX_MODE);
    pwmPinState[p->ulPwmChan] = UNCONFIGURED;
}

void CurieHwPWM::dutyCycle(double dc) {
    if (dc < 0.0 || dc > 100.0 || pwmPinState[p->ulPwmChan] == UNRESERVED) return;

    high = (dc * period)/100.0;
    low = period - high;

    uint32_t offset;
    offset = ((p->ulPwmChan * QRK_PWM_N_LCNT2_LEN) + QRK_PWM_N_LOAD_COUNT2);
    MMIO_REG_VAL_FROM_BASE(QRK_PWM_BASE_ADDR, offset) = high;
    offset = ((p->ulPwmChan * QRK_PWM_N_REGS_LEN) + QRK_PWM_N_LOAD_COUNT1);
    MMIO_REG_VAL_FROM_BASE(QRK_PWM_BASE_ADDR, offset) = low;

    if (pwmPinState[p->ulPwmChan] == UNCONFIGURED)
        pwmPinState[p->ulPwmChan] = STOPPED;
}

void CurieHwPWM::start() {
    if (pwmPinState[p->ulPwmChan] != STOPPED) return;

    uint32_t offset;
    offset = ((p->ulPwmChan * QRK_PWM_N_REGS_LEN) + QRK_PWM_N_CONTROL);
    MMIO_REG_VAL_FROM_BASE(QRK_PWM_BASE_ADDR, offset) |= QRK_PWM_CONTROL_ENABLE;
    pwmPinState[p->ulPwmChan] = RUNNING;
}

void CurieHwPWM::stop() {
    if (pwmPinState[p->ulPwmChan] != RUNNING) return;

    uint32_t offset;
    offset = ((p->ulPwmChan * QRK_PWM_N_REGS_LEN) + QRK_PWM_N_CONTROL);
    MMIO_REG_VAL_FROM_BASE(QRK_PWM_BASE_ADDR, offset) &= ~QRK_PWM_CONTROL_ENABLE;
    pwmPinState[p->ulPwmChan] = STOPPED;
}

void CurieHwPWM::release(){
    uint32_t offset;
    offset = ((p->ulPwmChan * QRK_PWM_N_REGS_LEN) + QRK_PWM_N_CONTROL);
    MMIO_REG_VAL_FROM_BASE(QRK_PWM_BASE_ADDR, offset) &= ~QRK_PWM_CONTROL_ENABLE;
    SET_PIN_MODE(p->ulSocPin, GPIO_MUX_MODE);
    p->ulGPIOType = SS_GPIO;
    p->ulPinMode = GPIO_MUX_MODE;
    low = 0;
    high = 0;
    pwmPinState[p->ulPwmChan] = UNRESERVED;
}

void CurieHwPWM::setRate(double f) {
    period = 32000000/f;
}

CurieHwPWM::~CurieHwPWM() {
    release();
}

