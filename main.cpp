// application
#include "ichigoplus/layer_application/cycle_checker.hpp"
#include "ichigoplus/layer_application/cycle_once_checker.hpp"
#include "ichigoplus/layer_application/timer.hpp"
#include "ichigoplus/layer_application/console.hpp"
#include "ichigoplus/layer_application/execute_function.hpp"

// controller
#include "ichigoplus/layer_controller/filtered_encoder.hpp"
#include "ichigoplus/layer_controller/photo_interrputer.hpp"
#include "layer_controller/SRC.hpp"
#include "layer_controller/SRC_arm.hpp"
#include "layer_controller/SRC_front.hpp"
#include "layer_controller/SRC_leg.hpp"
#include "layer_controller/SRC_location.hpp"
#include "layer_controller/SRC_sw.hpp"

// circuit
#include "ichigoplus/layer_driver/circuit/bno055.hpp"
#include "ichigoplus/layer_driver/circuit/lap_motor_driver.hpp"

//lib_src
#include "ichigoplus/lib_src/utilplus.hpp"

// device
#include "layer_driver/device/pin.hpp"

// using
using encoder::Enc0;
using encoder::Enc1;
using encoder::Enc2;
using encoder::Enc3;
using PhotoInt = photo_interrputer::PhotoInterrputerDigital;
using rp_lib::pi;
using rp_lib::rtod;


int main(){
	// cycle period [ms]
	constexpr int ctrl_period = 2;
	constexpr int disp_period = 100;

	// Switch
	Sw0 sw0;
	sw0.setupDigitalIn();
	Sw1 sw1;
	sw1.setupDigitalIn();
	Sw2 sw2;
	sw2.setupDigitalIn();
	Sw3 sw3;
	sw3.setupDigitalIn();

	// Varaible-Voltage(3.3V/5V)inDigital
	D0 d0;
	D1 d1;
	D2 d2;
	D3 d3;

	// Analog, Digital
	A0 a0;
	A1 a1;
	A2 a2;
	A3 a3;
	A4 a4;
	A5 a5;
	A6 a6;

	// Serial
	Serial0 forCons;
	Serial1 serialGyro;

	// Console
	Console cons(forCons);
	cons.setup(115200);
	cons.setNewLine(Console::NEWLINE_CRLF);

	// ExecuteFunction
	ExecuteFunction exeFunc("func");
	cons.addCommand(exeFunc);

	// Gyro
	Bno055 gyro(serialGyro);
	gyro.setup();
	gyro.rev(true);

	// PhotoInterrputer
	PhotoInt topPhoto(d0, PhotoInt::SetupType::in);
	topPhoto.setup();
	PhotoInt bottomPhoto(d1, PhotoInt::SetupType::in);
	bottomPhoto.setup();

	// Encoder
	Enc0 enc0;
	Enc2 enc1;
	enc1.setup();
	enc1.cpr(2000);
	Enc1 enc2;
	enc2.setup();
	enc2.cpr(2000);
	Enc3 enc3;
	enc3.setup();
	enc3.cpr(400);//アームのところ
	//Filtered encoder
	encoder::FilteredEncoder filEnc1(enc1);
	filEnc1.setup();
	filEnc1.rev(true);
	encoder::FilteredEncoder filEnc2(enc2);
	filEnc2.setup();
	filEnc2.rev(true);
	encoder::FilteredEncoder filEnc3(enc3);
	filEnc3.setup();
	filEnc3.rev(true);

	// MD
	Md0l md0l;
	Md0r md0r;
	Md1l md1l;
	Md1r md1r;
	Md2l md2l;
	Md2r md2r;
	Md3l md3l;
	Md3r md3r;
	Md4l md4l;
	Md4r md4r;
	LAPMotorDriver mcRightWheel(md4l,md4r,100);
	mcRightWheel.setup();
	LAPMotorDriver mcLeftWheel(md2l,md2r,100);
	mcLeftWheel.setup();
	LAPMotorDriver mcBackWheel(md3l,md3r,100);
	mcBackWheel.setup();
	LAPMotorDriver mcArmWheel(md1l,md1r,100);
	mcArmWheel.setup();

	// Cycle Timer
	Timer ctrlCycle;
	ctrlCycle(ctrl_period, true);
	Timer dispCycle;
	dispCycle(disp_period, true);

	// CycleChecker
	CycleChecker cycleChecker(ctrl_period);

	// CycleCounter
	cycle_once_checker::CycleCounter cycleCounter;

	// ExecuteFunction(add func)
	exeFunc.addFunc("reset", [&]{ NVIC_SystemReset(); });
	exeFunc.addFunc("gyro",[&]{ printf("angleZ:%f\n", rtod(gyro.angleZ())); });
	exeFunc.addFunc("photo", [&] { printf("top: %d  bottom: %d \n", topPhoto.read(), bottomPhoto.read()); });
	exeFunc.addFunc("rwheel",[&]{ mcRightWheel.duty(0.3); }); //右のホイール回す duty0.3 dutyは-0.95~0.95
	exeFunc.addFunc("gyro",[&]{ printf("sw0: %d", sw0.digitalRead()); });

	//SRCclass
	SRC_arm arc_arm(topPhoto, bottomPhoto, mcArmWheel);
	SRC_front src_front(gyro);
	SRC_leg src_leg(mcRightWheel,mcLeftWheel,mcBackWheel,src_front);
	SRC_sw src_sw(sw0,sw1,sw2,sw3,a1,a2,a3,a4);
	SRC_location src_location(gyro,filEnc1,filEnc2);
	SRC src(src_location,arc_arm,src_leg,src_sw);
	
	//ExecuteFunction(add func)
	exeFunc.addFunc("reset", [&]{ NVIC_SystemReset(); });
	exeFunc.addFunc("enc",[&]{printf("enc0: %f,enc1: %f\n", filEnc1.radian(),filEnc2.radian(),filEnc3.radian());});
	exeFunc.addFunc("gyro", [&]{ printf("angleZ: %f\n", gyro.angleZ()); });
	// main loop
	while(1){
		if(ctrlCycle()) {
			cycleChecker.cycle();
			cycleCounter.cycle();
			filEnc1.cycle();
			filEnc2.cycle();
			gyro.cycle();
			src.cycle();
			mcRightWheel.cycle();
			mcLeftWheel.cycle();
			mcBackWheel.cycle();
			mcArmWheel.cycle();
			
		}

		if(dispCycle()) {
			if(cycleChecker()){
				forCons.printf("cycle was delayed : %lld[ms]\n",cycleChecker.getMaxDelay());
				cycleChecker.reset();
			}
			cons.cycle();
			a0.digitalHigh();
		}

	}

}
