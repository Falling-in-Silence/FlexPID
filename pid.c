#include "pid.h"


float PID_Calculate_Mode_PID(PID* self, float current)
{
    float error = self -> Target - current;
    self -> Integral += error * self -> DeltaT;
    float derivative = (error - self -> LastError) / self -> DeltaT;
    if(self -> Integral > self -> IntegralLimit)
    {
        self -> Integral = self -> IntegralLimit;
    }
    else if(self -> Integral < -self -> IntegralLimit)
    {
        self -> Integral = -self -> IntegralLimit;
    }
    float Uk = (self -> Kp * error) + (self -> Ki * self -> Integral) + (self -> Kd * derivative);
    self -> LastError = error;
    return Uk;
}

void PID_Init(PID* self, float Kp, float Ki, float Kd, float DeltaT ,float Target ,int (*PID_Control_Quantization_Fucntion)(float Uk))
{
    self -> Kp = Kp;
    self -> Ki = Ki;
    self -> Kd = Kd;
    self -> DeltaT = DeltaT;
    self -> Target = Target;
    self -> LastError = 0;
    self -> Integral = 0;
    self -> PID_Calculate_Function = PID_Calculate_Mode_PID;
    self -> IntegralLimit = 100.0f;
    self -> PID_Control_Quantization_Fucntion = PID_Control_Quantization_Fucntion;
}

void PID_Set_Target(PID* self, float target)
{
    self -> Integral = 0.0f;  
    self -> LastError = 0.0f;
    self -> Target = target;
}

void PID_Reset_State(PID* self)
{
    self -> Integral = 0.0f;  
    self -> LastError = 0.0f;
}

int PID_Update(PID* self, float current)
{
    return self -> PID_Control_Quantization_Fucntion( self -> PID_Calculate_Function(self, current));
}



float PID_Calculate_Mode_P(PID* self, float current)
{
    float error = self -> Target - current;
    float Uk = (self -> Kp * error);
    self -> LastError = error;
    return Uk;
}

float PID_Calculate_Mode_PI(PID* self, float current)
{
    float error = self -> Target - current;
    self -> Integral += error * self -> DeltaT;
    if(self -> Integral > self -> IntegralLimit)
    {
        self -> Integral = self -> IntegralLimit;
    }
    else if(self -> Integral < -self -> IntegralLimit)
    {
        self -> Integral = -self -> IntegralLimit;
    }
    float Uk = (self -> Kp * error) + (self -> Ki * self -> Integral);
    self -> LastError = error;
    return Uk;
}

float PID_Calculate_Mode_PD(PID* self, float current)
{
    float error = self -> Target - current;
    float derivative = (error - self -> LastError) / self -> DeltaT;
    float Uk = (self -> Kp * error) + (self -> Kd * derivative);
    self -> LastError = error;
    return Uk;
}

void PID_Set_IntegralLimit(PID* self, float IntegralLimit)
{
    self -> IntegralLimit = IntegralLimit;
}

void PID_Set_Mode(PID* self, PID_Mode_Type mode)
{
    switch (mode)
    {
        case PID_MODE_P:
            self -> PID_Calculate_Function = PID_Calculate_Mode_P;
            break;
        case PID_MODE_PI:
            self -> PID_Calculate_Function = PID_Calculate_Mode_PI;
            break;
        case PID_MODE_PD:
            self -> PID_Calculate_Function = PID_Calculate_Mode_PD;
            break;
        case PID_MODE_PID:
            self -> PID_Calculate_Function = PID_Calculate_Mode_PID;
            break;
    }
}

void PID_Set_DeltaT(PID* self, float DeltaT)
{
    self -> DeltaT = DeltaT;
}

void PID_Set_Factor(PID* self, float Kp, float Ki, float Kd)
{
    self -> Kp = Kp;
    self -> Ki = Ki;
    self -> Kd = Kd;
}

void PID_Set_Kp(PID* self, float Kp)
{
    self -> Kp = Kp;
}

void PID_Set_Ki(PID* self, float Ki)
{
    self -> Ki = Ki;
}

void PID_Set_Kd(PID* self, float Kd)
{
    self -> Kd = Kd;
}


