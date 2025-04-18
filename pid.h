#ifndef PID_H
#define PID_H

typedef enum
{
	PID_MODE_P = 0,
	PID_MODE_PI = 1,
	PID_MODE_PD = 2,
	PID_MODE_PID = 3
} PID_Mode_Type;


struct PID
{
	float Kp;
	float Ki;
	float Kd;

	float IntegralLimit;

	float DeltaT;
	float Target;

	float LastError;
	float Integral;

	float (*PID_Calculate_Function) (struct PID* self, float current);
	int (*PID_Control_Quantization_Fucntion) (float Uk);
};

typedef struct PID PID;

void PID_Init(PID* self, float Kp, float Ki, float Kd, float DeltaT ,float Target ,int (*PID_Control_Quantization_Fucntion)(float Uk));

void PID_Set_Target(PID* self, float target);

int PID_Update(PID* self, float current);

void PID_Reset_State(PID* self);

void PID_Set_IntegralLimit(PID* self, float IntegralLimit);

void PID_Set_Mode(PID* self, PID_Mode_Type mode);

void PID_Set_DeltaT(PID* self, float DeltaT);
void PID_Set_Factor(PID* self, float Kp, float Ki, float Kd);
void PID_Set_Kp(PID* self, float Kp);
void PID_Set_Ki(PID* self, float Ki);
void PID_Set_Kd(PID* self, float Kd);


#endif

