#include <ServoTimer2.h>
#include <PCM.h>

// Pin definitions
const int STOCK_LED_PIN_1 = 8;
const int STOCK_LED_PIN_2 = 9;
const int READY_LED_PIN = 10;
const int UDS_TRIG_PIN = 5;
const int UDS_ECHO_PIN = 6;
const int SPEAKER_PIN = 13;
const int SERVO_ONE_PIN = 7;
const int SERVO_TWO_PIN = 11;

ServoTimer2 servo_one;
ServoTimer2 servo_two;

// Audio data
const unsigned char softChime[] PROGMEM = {
  135, 28, 91, 255, 255, 71, 106, 159, 110, 135, 99, 3, 61, 194, 66, 0, 113, 212, 85, 73, 180, 206, 168, 194, 192, 194, 233, 224, 145, 161, 210, 152, 75, 99, 112, 57, 26, 35, 24, 19, 24, 15, 19, 61, 78, 70, 98, 150, 166, 170, 201, 231, 240, 247, 255, 252, 252, 247, 224, 201, 189, 168, 131, 105, 87, 63, 36, 21, 8, 0, 0, 0, 3, 17, 36, 54, 73, 101, 129, 150, 173, 198, 217, 229, 240, 245, 247, 241, 233, 217, 201, 182, 157, 133, 110, 89, 66, 47, 33, 22, 17, 15, 19, 26, 40, 56, 73, 94, 119, 142, 163, 184, 201, 217, 227, 234, 236, 234, 227, 215, 201, 184, 163, 142, 119, 96, 75, 57, 42, 29, 21, 17, 19, 24, 35, 47, 64, 84, 105, 126, 147, 168, 187, 203, 217, 226, 231, 231, 227, 219, 208, 192, 175, 156, 135, 113, 92, 75, 57, 45, 35, 29, 28, 29, 36, 47, 61, 77, 94, 115, 135, 154, 173, 189, 203, 213, 220, 222, 222, 217, 208, 194, 180, 163, 143, 124, 105, 85, 70, 56, 45, 36, 33, 33, 38, 45, 56, 70, 87, 105, 124, 142, 161, 177, 191, 203, 212, 217, 217, 215, 208, 198, 185, 170, 154, 136, 117, 99, 84, 68, 56, 47, 42, 40, 42, 47, 54, 66, 80, 96, 113, 131, 149, 164, 180, 192, 201, 208, 212, 210, 206, 199, 189, 175, 161, 145, 128, 110, 94, 80, 66, 57, 49, 45, 45, 49, 54, 64, 75, 89, 105, 120, 138, 154, 168, 182, 192, 199, 205, 206, 203, 199, 191, 180, 166, 152, 136, 120, 105, 91, 77, 66, 57, 52, 50, 52, 56, 63, 71, 84, 98, 113, 128, 143, 157, 171, 182, 191, 198, 199, 199, 198, 191, 182, 171, 159, 145, 129, 115, 101, 87, 77, 66, 61, 56, 56, 57, 63, 70, 80, 92, 105, 120, 135, 149, 161, 173, 182, 189, 194, 196, 194, 191, 184, 175, 164, 150, 138, 124, 110, 98, 85, 75, 68, 63, 61, 61, 64, 70, 78, 87, 99, 112, 126, 140, 152, 164, 173, 182, 187, 191, 191, 189, 184, 177, 168, 156, 143, 131, 119, 106, 94, 84, 75, 70, 66, 64, 66, 70, 77, 85, 94, 106, 119, 131, 143, 156, 166, 173, 180, 185, 187, 185, 184, 177, 170, 161, 150, 138, 126, 113, 103, 92, 84, 77, 71, 70, 70, 71, 77, 82, 91, 101, 112, 124, 136, 147, 157, 166, 173, 178, 182, 182, 182, 177, 171, 163, 154, 143, 133, 120, 110, 99, 91, 84, 77, 73, 73, 73, 77, 82, 89, 98, 106, 119, 129, 140, 150, 159, 166, 173, 177, 178, 178, 177, 171, 166, 157, 149, 138, 128, 117, 106, 98, 91, 84, 78, 77, 77, 78, 82, 87, 94, 103, 113, 122, 133, 143, 152, 161, 166, 171, 175, 175, 175, 171, 166, 159, 152, 143, 133, 124, 113, 105, 96, 89, 84, 80, 80, 80, 82, 87, 92, 99, 108, 117, 128, 136, 145, 154, 161, 166, 170, 171, 171, 170, 166, 161, 154, 147, 138, 129, 120, 112, 103, 96, 89, 85, 84, 82, 84, 87, 91, 98, 105, 113, 122, 131, 140, 147, 156, 161, 166, 168, 170, 168, 166, 163, 157, 150, 142, 135, 126, 117, 108, 101, 96, 91, 87, 85, 85, 87, 91, 96, 103, 110, 117, 126, 135, 142, 149, 156, 161, 164, 166, 166, 164, 163, 157, 152, 145, 138, 129, 122, 113, 106, 101, 96, 91, 89, 89, 89, 91, 96, 101, 106, 113, 120, 129, 136, 143, 150, 156, 159, 163, 164, 163, 161, 159, 154, 149, 142, 135, 126, 119, 112, 105, 99, 96, 92, 91, 91, 92, 94, 99, 105, 110, 117, 124, 133, 140, 145, 150, 156, 159, 161, 161, 161, 157, 154, 150, 143, 138, 131, 124, 117, 110, 105, 99, 96, 94, 92, 94, 96, 99, 103, 108, 113, 120, 128, 135, 142, 147, 152, 156, 157, 159, 159, 157, 156, 150, 147, 140, 135, 128, 120, 115, 108, 105, 99, 98, 96, 96, 96, 99, 101, 106, 112, 117, 124, 131, 136, 142, 147, 152, 154, 156, 157, 156, 154, 152, 147, 143, 136, 131, 126, 119, 113, 108, 105, 101, 98, 98, 98, 99, 101, 105, 110, 115, 120, 126, 133, 138, 143, 147, 150, 154, 156, 156, 154, 152, 149, 145, 140, 135, 128, 122, 117, 112, 108, 105, 101, 99, 99, 99, 101, 105, 108, 113, 119, 124, 129, 135, 140, 143, 147, 150, 152, 154, 152, 152, 149, 145, 142, 136, 131, 126, 120, 115, 112, 106, 105, 103, 101, 101, 103, 105, 108, 112, 115, 120, 126, 131, 136, 140, 145, 147, 150, 150, 152, 150, 149, 147, 143, 138, 135, 129, 124, 119, 115, 110, 106, 105, 103, 103, 103, 105, 106, 110, 113, 119, 122, 128, 133, 136, 142, 145, 147, 149, 150, 150, 149, 147, 143, 140, 136, 131, 128, 122, 117, 113, 110, 108, 105, 105, 105, 105, 106, 110, 113, 117, 120, 126, 129, 135, 138, 142, 145, 147, 149, 149, 147, 147, 143, 142, 138, 133, 129, 126, 120, 117, 113, 110, 108, 106, 106, 106, 106, 110, 112, 115, 119, 122, 128, 131, 135, 138, 142, 145, 145, 147, 147, 145, 143, 142, 138, 135, 131, 128, 124, 119, 115, 113, 110, 108, 108, 106, 108, 110, 112, 113, 117, 120, 124, 129, 133, 136, 140, 142, 143, 145, 145, 145, 143, 142, 140, 136, 133, 129, 126, 122, 119, 115, 113, 110, 110, 108, 108, 110, 112, 113, 115, 119, 122, 126, 129, 133, 136, 140, 142, 143, 143, 143, 143, 142, 140, 138, 135, 131, 128, 124, 120, 117, 115, 113, 112, 110, 110, 110, 112, 113, 115, 119, 120, 124, 128, 131, 135, 138, 140, 142, 143, 143, 143, 142, 140, 138, 136, 133, 129, 126, 122, 120, 117, 115, 113, 112, 112, 112, 112, 113, 115, 117, 120, 122, 126, 129, 133, 135, 138, 140, 142, 142, 142, 142, 140, 138, 136, 135, 131, 128, 126, 122, 119, 117, 115, 113, 112, 112, 112, 113, 113, 117, 119, 120, 124, 128, 131, 133, 136, 138, 140, 140, 142, 142, 140, 140, 138, 135, 133, 129, 128, 124, 120, 119, 117, 115, 113, 112, 112, 113, 113, 115, 117, 120, 122, 126, 129, 131, 135, 136, 138, 140, 140, 142, 140, 140, 138, 136, 135, 131, 129, 126, 122, 120, 117, 115, 113, 113, 113, 113, 113, 115, 117, 119, 120, 124, 128, 129, 133, 135, 136, 138, 140, 140, 140, 140, 138, 136, 135, 133, 129, 128, 124, 122, 119, 117, 115, 113, 113, 113, 113, 115, 115, 119, 120, 122, 126, 128, 131, 133, 135, 136, 138, 140, 140, 140, 138, 138, 136, 135, 131, 129, 126, 124, 120, 119, 117, 115, 115, 113, 113, 115, 115, 117, 119, 120, 124, 126, 129, 131, 135, 136, 138, 138, 140, 140, 138, 138, 136, 135, 133, 129, 128, 126, 122, 120, 119, 117, 115, 115, 113, 115, 115, 117, 119, 120, 122, 126, 128, 129, 133, 135, 136, 138, 138, 138, 138, 138, 136, 135, 133, 131, 129, 126, 124, 122, 120, 119, 117, 115, 115, 115, 115, 117, 117, 119, 122, 124, 126, 129, 131, 133, 135, 136, 138, 138, 138, 138, 138, 136, 135, 133, 131, 128, 126, 124, 120, 119, 117, 117, 115, 115, 115, 115, 117, 119, 120, 122, 124, 128, 129, 131, 133, 135, 136, 138, 138, 138, 138, 136, 135, 133, 131, 129, 128, 124, 122, 120, 119, 117, 117, 115, 115, 115, 117, 119, 119, 122, 124, 126, 128, 129, 133, 135, 135, 136, 138, 138, 138, 136, 136, 135, 133, 131, 128, 126, 124, 122, 120, 119, 117, 117, 115, 117, 117, 117, 119, 120, 122, 124, 128, 129, 131, 133, 135, 136, 136, 136, 136, 136, 136, 135, 133, 131, 129, 128, 126, 122, 120, 119, 119, 117, 117, 117, 117, 117, 119, 120, 122, 124, 126, 128, 129, 131, 133, 135, 136, 136, 136, 136, 136, 135, 135, 133, 131, 128, 126, 124, 122, 120, 119, 119, 117, 117, 117, 117, 119, 119, 120, 122, 124, 126, 128, 131, 133, 133, 135, 136, 136, 136, 136, 135, 135, 133, 131, 129, 128, 126, 124, 122, 120, 119, 119, 117, 117, 117, 119, 119, 120, 122, 124, 126, 128, 129, 131, 133, 135, 135, 136, 136, 136, 135, 135, 133, 133, 131, 129, 128, 124, 122, 120, 120, 119, 119, 117, 117, 119, 119, 120, 120, 122, 124, 126, 128, 129, 131, 133, 135, 135, 135, 136, 135, 135, 135, 133, 131, 129, 128, 126, 124, 122, 120, 120, 119, 119, 119, 119, 119, 119, 120, 122, 124, 126, 128, 129, 131, 131, 133, 135, 135, 135, 135, 135, 135, 133, 131, 131, 129, 128, 126, 124, 122, 120, 119, 119, 119, 119, 119, 119, 120, 120, 122, 124, 126, 128, 129, 131, 133, 133, 135, 135, 135, 135, 135, 133, 133, 131, 129, 128, 126, 124, 122, 122, 120, 119, 119, 119, 119, 119, 120, 120, 122, 124, 126, 126, 128, 129, 131, 133, 133, 135, 135, 135, 135, 135, 133, 131, 131, 129, 128, 126, 124, 122, 120, 120, 119, 119, 119, 119, 119, 120, 122, 122, 124, 126, 128, 129, 131, 131, 133, 133, 135, 135, 135, 135, 133, 133, 131, 129, 128, 126, 126, 124, 122, 120, 120, 119, 119, 119, 119, 120, 120, 122, 124, 124, 126, 128, 129, 131, 131, 133, 133, 135, 135, 135, 133, 133, 131, 131, 129, 128, 126, 124, 122, 122, 120, 120, 119, 119, 119, 120, 120, 122, 122, 124, 126, 128, 129, 129, 131, 133, 133, 133, 135, 135, 133, 133, 131, 131, 129, 128, 128, 126, 124, 122, 122, 120, 120, 120, 120, 120, 120, 120, 122, 124, 124, 126, 128, 129, 131, 131, 133, 133, 133, 133, 133, 133, 133, 131, 131, 129, 128, 126, 124, 124, 122, 120, 120, 120, 120, 120, 120, 120, 122, 122, 124, 126, 128, 128, 129, 131, 131, 133, 133, 133, 133, 133, 133, 131, 131, 129, 128, 128, 126, 124, 122, 122, 120, 120, 120, 120, 120, 120, 122, 122, 124, 124, 126, 128, 129, 129, 131, 131, 133, 133, 133, 133, 133, 133, 131, 129, 129, 128, 126, 126, 124, 122, 122, 120, 120, 120, 120, 120, 120, 122, 122, 124, 126, 126, 128, 129, 129, 131, 131, 133, 133, 133, 133, 133, 131, 131, 129, 128, 128, 126, 124, 124, 122, 122, 120, 120, 120, 120, 120, 122, 122, 124, 124, 126, 128, 128, 129, 131, 131, 133, 133, 133, 133, 133, 131, 131, 129, 129, 128, 126, 126, 124, 124, 122, 122, 120, 120, 120, 120, 122, 122, 122, 124, 126, 126, 128, 129, 129, 131, 131, 133, 133, 133, 133, 131, 131, 131, 129, 128, 128, 126, 126, 124, 122, 122, 122, 120, 120, 120, 122, 122, 122, 124, 124, 126, 128, 128, 129, 129, 131, 131, 131, 133, 133, 131, 131, 131, 129, 129, 128, 128, 126, 124, 124, 122, 122, 122, 120, 120, 122, 122, 122, 124, 124, 126, 126, 128, 128, 129, 131, 131, 131, 131, 133, 131, 131, 131, 131, 129, 129, 128, 126, 126, 124, 124, 122, 122, 122, 122, 122, 122, 122, 122, 124, 124, 126, 128, 128, 129, 129, 131, 131, 131, 131, 131, 131, 131, 131, 129, 129, 128, 128, 126, 126, 124, 124, 122, 122, 122, 122, 122, 122, 122, 124, 124, 126, 126, 128, 128, 129, 129, 131, 131, 131, 131, 131, 131, 131, 129, 129, 129, 128, 126, 126, 124, 124, 122, 122, 122, 122, 122, 122, 122, 122, 124, 124, 126, 126, 128, 129, 129, 129, 131, 131, 131, 131, 131, 131, 131, 129, 129, 128, 128, 126, 126, 124, 124, 122, 122, 122, 122, 122, 122, 122, 124, 124, 126, 126, 128, 128, 129, 129, 131, 131, 131, 131, 131, 131, 131, 129, 129, 129, 128, 126, 126, 124, 124, 124, 122, 122, 122, 122, 122, 122, 124, 124, 124, 126, 126, 128, 128, 129, 129, 131, 131, 131, 131, 131, 131, 131, 129, 129, 128, 128, 126, 126, 124, 124, 124, 122, 122, 122, 122, 122, 122, 124, 124, 126, 126, 128, 128, 129, 129, 129, 131, 131, 131, 131, 131, 131, 129, 129, 129, 128, 128, 126, 126, 124, 124, 124, 122, 122, 122, 122, 122, 124, 124, 124, 126, 126, 128, 128, 129, 129, 129, 131, 131, 131, 131, 131, 129, 129, 129, 128, 128, 126, 126, 124, 124, 124, 122, 122, 122, 122, 122, 124, 124, 124, 126, 126, 126, 128, 128, 129, 129, 129, 131, 131, 131, 131, 129, 129, 129, 129, 128, 128, 126, 126, 124, 124, 124, 122, 122, 122, 122, 124, 124, 124, 124, 126, 126, 128, 128, 129, 129, 129, 129, 131, 131, 131, 129, 129, 129, 129, 128, 128, 126, 126, 126, 124, 124, 124, 124, 122, 122, 124, 124, 124, 124, 126, 126, 126, 128, 128, 129, 129, 129, 129, 131, 131, 129, 129, 129, 129, 128, 128, 128, 126, 126, 124, 124, 124, 124, 124, 122, 124, 124, 124, 124, 124, 126, 126, 128, 128, 128, 129, 129, 129, 129, 129, 129, 129, 129, 129, 129, 128, 128, 128, 126, 126, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 126, 126, 126, 128, 128, 129, 129, 129, 129, 129, 129, 129, 129, 129, 129, 128, 128, 128, 126, 126, 126, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 126, 126, 128, 128, 128, 129, 129, 129, 129, 129, 129, 129, 129, 129, 129, 128, 128, 128, 126, 126, 126, 124, 124, 124, 124, 124, 124, 124, 124, 124, 126, 126, 126, 128, 128, 128, 129, 129, 129, 129, 129, 129, 129, 129, 129, 128, 128, 128, 126, 126, 126, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 126, 126, 126, 128, 128, 128, 129, 129, 129, 129, 129, 129, 129, 129, 129, 128, 128, 128, 126, 126, 126, 124, 124, 124, 124, 124, 124, 124, 124, 124, 126, 126, 126, 128, 128, 128, 129, 129, 129, 129, 129, 129, 129, 129, 129, 128, 128, 128, 126, 126, 126, 126, 124, 124, 124, 124, 124, 124, 124, 124, 126, 126, 126, 126, 128, 128, 128, 129, 129, 129, 129, 129, 129, 129, 129, 129, 128, 128, 128, 126, 126, 126, 124, 124, 124, 124, 124, 124, 124, 124, 124, 126, 126, 126, 128, 128, 128, 128, 129, 129, 129, 129, 129, 129, 129, 129, 128, 128, 128, 128, 126, 126, 126, 124, 124, 124, 124, 124, 124, 124, 124, 126, 126, 126, 126, 128, 128, 128, 129, 129, 129, 129, 129, 129, 129, 129, 128, 128, 128, 128, 126, 126, 126, 126, 124, 124, 124, 124, 124, 124, 124, 124, 126, 126, 126, 128, 128, 128, 128, 129, 129, 129, 129, 129, 129, 129, 129, 128, 128, 128, 128, 126, 126, 126, 126, 124, 124, 124, 124, 124, 124, 124, 126, 126, 126, 126, 128, 128, 128, 128, 129, 129, 129, 129, 129, 129, 129, 128, 128, 128, 128, 126, 126, 126, 126, 124, 124, 124, 124, 124, 124, 124, 126, 126, 126, 126, 126, 128, 128, 128, 128, 129, 129, 129, 129, 129, 129, 129, 128, 128, 128, 128, 126, 126, 126, 126, 124, 124, 124, 124, 124, 124, 124, 126, 126, 126, 126, 128, 128, 128, 128, 128, 129, 129, 129, 129, 129, 129, 128, 128, 128, 128, 126, 126, 126, 126, 126, 124, 124, 124, 124, 124, 124, 126, 126, 126, 126, 126, 128, 128, 128, 128, 129, 129, 129, 129, 129, 129, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 124, 124, 124, 124, 124, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 129, 129, 129, 129, 129, 129, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 124, 124, 124, 124, 124, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 129, 129, 129, 129, 129, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 124, 124, 124, 124, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 129, 129, 129, 129, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 124, 124, 124, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 129, 129, 129, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 124, 124, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 129, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 129, 128, 129, 126, 129, 126, 129, 124, 129, 122, 63, 243, 163, 170, 124, 64, 75, 3, 70, 24, 126, 110, 206, 206, 255, 250, 234, 215, 147, 124, 42, 38, 0, 14, 7, 64, 99, 157, 203, 229, 252, 233, 220, 163, 129, 64, 36, 1, 5, 15, 50, 98, 145, 199, 227, 255, 245, 233, 187, 147, 92, 52, 21, 8, 19, 43, 87, 133, 182, 217, 243, 243, 229, 196, 152, 103, 57, 26, 8, 12, 31, 71, 113, 164, 203, 233, 241, 233, 205, 164, 119, 71, 38, 15, 15, 28, 63, 103, 152, 192, 224, 240, 234, 213, 175, 133, 85, 49, 22, 15, 24, 54, 92, 138, 182, 215, 236, 236, 222, 187, 149, 101, 63, 33, 19, 24, 45, 82, 124, 170, 203, 229, 233, 224, 194, 156, 112, 70, 38, 21, 22, 36, 71, 110, 156, 192, 220, 231, 226, 203, 168, 128, 84, 52, 28, 24, 35, 64, 99, 143, 182, 212, 227, 226, 210, 177, 138, 94, 61, 33, 26, 31, 54, 89, 129, 171, 203, 224, 226, 215, 187, 152, 110, 73, 43, 29, 31, 49, 80, 117, 159, 191, 217, 224, 217, 192, 159, 119, 82, 50, 31, 31, 42, 71, 105, 147, 182, 210, 222, 220, 201, 171, 133, 94, 63, 40, 35, 40, 64, 96, 136, 171, 201, 217, 219, 205, 177, 143, 103, 71, 43, 35, 36, 57, 87, 124, 161, 191, 213, 217, 210, 185, 156, 117, 84, 54, 40, 38, 52, 80, 113, 150, 182, 206, 213, 212, 191, 163, 126, 91, 61, 42, 38, 47, 71, 101, 140, 171, 199, 212, 213, 198, 171, 138, 103, 73, 50, 42, 45, 66, 94, 129, 163, 191, 206, 210, 201, 177, 147, 110, 80, 54, 43, 43, 61, 85, 119, 152, 182, 203, 210, 205, 184, 157, 122, 92, 64, 49, 45, 57, 80, 110, 143, 173, 196, 206, 205, 189, 164, 131, 99, 71, 52, 47, 52, 73, 99, 133, 163, 191, 203, 206, 194, 171, 142, 110, 82, 59, 50, 52, 68, 92, 124, 154, 182, 198, 203, 196, 177, 150, 117, 89, 64, 52, 50, 63, 85, 115, 145, 173, 194, 201, 199, 182, 159, 128, 99, 73, 57, 52, 61, 80, 106, 136, 164, 187, 198, 199, 185, 164, 135, 106, 78, 61, 54, 57, 75, 98, 128, 156, 182, 194, 199, 191, 171, 145, 115, 89, 68, 57, 57, 71, 91, 120, 147, 173, 189, 196, 191, 175, 152, 122, 96, 71, 61, 56, 66, 85, 112, 140, 166, 185, 194, 194, 180, 161, 133, 106, 80, 66, 59, 64, 80, 105, 131, 157, 180, 191, 192, 182, 164, 138, 112, 87, 70, 61, 63, 77, 96, 124, 149, 173, 187, 192, 185, 171, 147, 120, 96, 75, 64, 63, 73, 91, 117, 142, 166, 182, 191, 187, 173, 154, 128, 103, 80, 68, 63, 70, 85, 108, 135, 159, 178, 187, 189, 178, 161, 136, 112, 87, 73, 66, 70, 82, 103, 128, 150, 171, 184, 187, 180, 164, 142, 117, 94, 77, 66, 68, 78, 96, 120, 143, 166, 180, 187, 182, 170, 149, 126, 103, 82, 71, 68, 77, 91, 113, 136, 159, 175, 184, 182, 171, 154, 131, 108, 87, 75, 68, 73, 85, 106, 129, 152, 171, 182, 184, 175, 161, 138, 117, 94, 80, 71, 73, 84, 101, 124, 145, 166, 177, 182, 177, 164, 143, 122, 99, 84, 73, 71, 80, 96, 117, 138, 159, 173, 182, 178, 168, 150, 129, 108, 89, 78, 73, 80, 92, 112, 133, 154, 170, 178, 178, 170, 154, 135, 113, 92, 80, 73, 77, 87, 106, 126, 147, 164, 175, 178, 173, 159, 140, 120, 99, 85, 77, 78, 85, 101, 120, 142, 159, 171, 177, 173, 163, 145, 126, 105, 89, 78, 77, 82, 96, 115, 135, 154, 168, 177, 175, 166, 150, 133, 112, 94, 84, 78, 82, 92, 110, 129, 149, 163, 173, 173, 168, 154, 136, 117, 99, 85, 78, 80, 89, 105, 122, 143, 159, 170, 173, 170, 159, 142, 124, 105, 91, 82, 82, 87, 101, 119, 136, 154, 166, 173, 170, 161, 145, 129, 110, 94, 84, 80, 85, 96, 113, 131, 149, 163, 171, 171, 164, 150, 135, 115, 99, 89, 84, 85, 94, 108, 126, 143, 157, 168, 170, 166, 154, 138, 120, 103, 91, 84, 84, 91, 105, 120, 138, 154, 164, 170, 166, 157, 143, 128, 110, 96, 87, 85, 89, 101, 117, 133, 149, 161, 168, 166, 159, 147, 131, 113, 99, 89, 85, 87, 98, 112, 128, 145, 157, 166, 168, 163, 150, 136, 119, 105, 92, 87, 89, 96, 108, 124, 140, 154, 163, 166, 163, 154, 140, 124, 108, 96, 89, 87, 92, 105, 119, 135, 149, 161, 166, 164, 157, 143, 129, 113, 101, 91, 89, 92, 101, 115, 131, 145, 157, 163, 164, 159, 147, 133, 117, 103, 92, 89, 91, 98, 110, 126, 142, 154, 161, 164, 161, 150, 138, 122, 108, 98, 91, 91, 96, 108, 120, 136, 149, 159, 163, 161, 152, 140, 126, 112, 99, 92, 91, 94, 105, 117, 133, 145, 156, 161, 161, 156, 145, 131, 117, 105, 96, 92, 94, 103, 113, 128, 142, 152, 159, 161, 157, 147, 135, 120, 108, 98, 92, 92, 99, 110, 124, 138, 149, 157, 161, 157, 150, 138, 126, 112, 101, 96, 94, 98, 108, 120, 133, 145, 156, 159, 157, 152, 142, 128, 115, 105, 96, 94, 96, 105, 115, 129, 142, 152, 157, 159, 154, 145, 133, 119, 108, 99, 96, 96, 103, 113, 126, 138, 149, 156, 157, 154, 147, 136, 122, 112, 101, 96, 96, 101, 110, 122, 135, 145, 154, 157, 156, 149, 140, 128, 115, 105, 99, 98, 99, 108, 119, 131, 142, 152, 156, 156, 150, 142, 129, 119, 106, 99, 98, 98, 105, 115, 128, 138, 149, 154, 156, 152, 145, 135, 122, 112, 103, 99, 99, 105, 113, 124, 135, 145, 152, 156, 152, 147, 136, 124, 113, 105, 99, 98, 103, 110, 120, 133, 142, 150, 154, 154, 149, 140, 129, 119, 108, 101, 99, 101, 108, 117, 129, 140, 149, 152, 154, 149, 142, 131, 120, 110, 103, 99, 101, 106, 115, 126, 136, 145, 152, 154, 150, 145, 135, 124, 113, 106, 101, 101, 105, 112, 122, 133, 143, 149, 152, 150, 145, 138, 126, 117, 108, 103, 101, 103, 110, 119, 129, 140, 147, 152, 152, 147, 140, 131, 120, 112, 105, 101, 103, 108, 117, 128, 136, 145, 150, 152, 149, 142, 133, 122, 113, 106, 103, 103, 106, 113, 124, 133, 143, 149, 150, 149, 143, 136, 126, 117, 108, 105, 103, 106, 112, 122, 131, 140, 147, 150, 149, 145, 138, 128, 119, 110, 105, 103, 105, 110, 119, 128, 138, 145, 149, 150, 147, 140, 131, 122, 113, 108, 105, 105, 110, 117, 126, 135, 142, 147, 149, 147, 142, 133, 124, 115, 108, 105, 105, 108, 113, 122, 131, 140, 145, 149, 147, 143, 136, 128, 119, 112, 106, 105, 108, 113, 120, 129, 138, 143, 147, 147, 143, 138, 129, 120, 113, 108, 105, 106, 112, 119, 126, 135, 142, 147, 149, 145, 140, 133, 124, 115, 110, 106, 106, 110, 117, 124, 133, 140, 145, 147, 145, 142, 135, 126, 117, 112, 106, 106, 108, 113, 122, 129, 138, 143, 147, 147, 143, 136, 129, 120, 113, 108, 106, 108, 113, 120, 128, 136, 142, 145, 145, 143, 138, 131, 122, 115, 110, 106, 108, 112, 117, 126, 133, 140, 145, 145, 143, 140, 133, 126, 119, 112, 108, 108, 112, 117, 124, 131, 138, 143, 145, 143, 140, 135, 128, 119, 113, 110, 108, 110, 115, 120, 129, 136, 142, 145, 145, 142, 136, 129, 122, 115, 112, 108, 110, 113, 120, 126, 135, 140, 143, 143, 142, 138, 131, 124, 117, 112, 110, 110, 112, 117, 124, 131, 138, 142, 143, 143, 140, 133, 128, 120, 113, 110, 110, 112, 117, 122, 129, 136, 140, 143, 143, 140, 135, 128, 120, 115, 112, 110, 112, 115, 120, 128, 135, 140, 143, 143, 142, 136, 131, 124, 117, 113, 110, 112, 113, 119, 126, 133, 138, 142, 143, 142, 138, 131, 126, 119, 113, 112, 110, 113, 117, 124, 129, 136, 140, 142, 142, 138, 135, 128, 120, 115, 112, 112, 113, 117, 122, 128, 135, 138, 142, 142, 140, 135, 129, 122, 117, 113, 112, 112, 115, 120, 126, 133, 138, 142, 142, 140, 136, 131, 126, 119, 115, 112, 112, 115, 119, 124, 131, 136, 140, 142, 140, 136, 133, 126, 120, 115, 113, 112, 113, 117, 122, 129, 135, 138, 142, 140, 138, 135, 129, 122, 117, 113, 113, 113, 117, 122, 128, 133, 136, 140, 140, 138, 135, 129, 124, 119, 115, 113, 113, 115, 120, 126, 131, 136, 140, 140, 140, 136, 131, 126, 120, 117, 113, 113, 115, 119, 124, 129, 135, 138, 140, 140, 136, 133, 128, 122, 117, 113, 113, 115, 117, 122, 128, 133, 136, 140, 140, 138, 135, 129, 124, 119, 115, 113, 115, 117, 120, 126, 131, 136, 138, 140, 138, 135, 131, 126, 120, 117, 113, 113, 117, 120, 124, 129, 135, 138, 140, 138, 136, 131, 128, 122, 117, 115, 115, 115, 119, 124, 129, 133, 136, 138, 138, 136, 133, 128, 122, 119, 115, 115, 115, 119, 122, 128, 131, 136, 138, 138, 136, 135, 129, 124, 120, 117, 115, 115, 117, 120, 126, 131, 135, 136, 138, 138, 135, 131, 126, 122, 117, 115, 115, 117, 120, 124, 129, 133, 136, 138, 138, 136, 133, 128, 122, 119, 117, 115, 117, 119, 122, 128, 131, 135, 136, 138, 136, 133, 129, 124, 120, 117, 115, 115, 119, 122, 126, 131, 135, 136, 138, 136, 135, 129, 126, 122, 119, 117, 117, 119, 120, 126, 129, 133, 136, 136, 136, 135, 131, 126, 122, 119, 117, 117, 117, 120, 124, 128, 133, 135, 136, 136, 135, 133, 128, 124, 120, 117, 117, 117, 119, 122, 128, 131, 135, 136, 136, 135, 133, 129, 124, 120, 119, 117, 117, 119, 122, 126, 129, 133, 136, 136, 136, 133, 131, 126, 122, 119, 117, 117, 119, 120, 124, 129, 133, 135, 136, 136, 135, 131, 128, 124, 120, 119, 117, 119, 120, 124, 128, 131, 135, 136, 136, 135, 133, 129, 124, 120, 119, 117, 119, 120, 122, 126, 129, 133, 135, 136, 135, 133, 129, 126, 122, 119, 117, 117, 119, 122, 126, 129, 133, 135, 136, 135, 133, 131, 128, 124, 120, 119, 119, 119, 120, 124, 128, 131, 135, 135, 135, 133, 131, 128, 124, 120, 119, 119, 119, 120, 124, 128, 129, 133, 135, 135, 135, 133, 129, 126, 122, 120, 119, 119, 120, 122, 126, 129, 133, 135, 135, 135, 133, 129, 126, 122, 120, 119, 119, 119, 122, 124, 128, 131, 133, 135, 135, 133, 131, 128, 124, 120, 119, 119, 119, 120, 124, 128, 131, 133, 135, 135, 133, 131, 128, 126, 122, 120, 119, 119, 120, 124, 126, 129, 133, 135, 135, 133, 131, 129, 126, 122, 120, 119, 119, 120, 122, 126, 129, 131, 133, 135, 135, 133, 129, 128, 124, 120, 120, 119, 120, 122, 124, 128, 131, 133, 135, 135, 133, 131, 128, 124, 122, 120, 119, 120, 120, 124, 126, 129, 131, 133, 135, 133, 131, 129, 126, 122, 120, 120, 120, 120, 122, 126, 129, 131, 133, 135, 133, 131, 129, 126, 124, 122, 120, 120, 120, 122, 126, 128, 131, 133, 133, 133, 133, 129, 128, 124, 122, 120, 120, 120, 122, 124, 128, 129, 131, 133, 133, 133, 131, 128, 126, 122, 120, 120, 120, 122, 124, 126, 129, 131, 133, 133, 133, 131, 129, 126, 124, 122, 120, 120, 120, 122, 126, 128, 131, 133, 133, 133, 131, 129, 128, 124, 122, 120, 120, 120, 122, 124, 128, 129, 131, 133, 133, 131, 129, 128, 126, 122, 120, 120, 120, 122, 124, 126, 129, 131, 133, 133, 133, 131, 128, 126, 124, 122, 120, 120, 122, 124, 126, 128, 131, 133, 133, 133, 131, 129, 126, 124, 122, 120, 120, 122, 122, 126, 128, 129, 131, 133, 133, 131, 129, 128, 124, 122, 122, 120, 120, 122, 124, 128, 129, 131, 133, 133, 131, 129, 128, 126, 124, 122, 120, 120, 122, 124, 126, 129, 131, 131, 133, 131, 131, 129, 126, 124, 122, 120, 120, 122, 124, 126, 128, 129, 131, 133, 131, 131, 129, 128, 124, 122, 122, 120, 122, 124, 126, 128, 129, 131, 131, 131, 131, 129, 128, 126, 124, 122, 122, 122, 122, 124, 126, 129, 131, 131, 131, 131, 129, 128, 126, 124, 122, 122, 122, 122, 124, 126, 128, 129, 131, 131, 131, 131, 129, 126, 124, 122, 122, 122, 122, 124, 126, 128, 129, 131, 131, 131, 131, 129, 128, 126, 124, 122, 122, 122, 124, 124, 128, 129, 131, 131, 131, 131, 129, 128, 126, 124, 122, 122, 122, 122, 124, 126, 128, 129, 131, 131, 131, 129, 128, 126, 124, 122, 122, 122, 122, 124, 126, 128, 129, 131, 131, 131, 129, 129, 128, 126, 124, 122, 122, 122, 124, 126, 128, 129, 131, 131, 131, 131, 129, 128, 126, 124, 122, 122, 122, 124, 124, 126, 128, 129, 131, 131, 131, 129, 128, 126, 124, 124, 122, 122, 122, 124, 126, 128, 129, 131, 131, 131, 129, 128, 128, 126, 124, 122, 122, 122, 124, 126, 128, 129, 129, 131, 131, 129, 129, 128, 126, 124, 122, 122, 122, 124, 126, 128, 128, 129, 131, 131, 131, 129, 128, 126, 124, 124, 122, 122, 124, 124, 126, 128, 129, 131, 131, 131, 129, 128, 126, 126, 124, 122, 122, 124, 124, 126, 128, 129, 129, 131, 131, 129, 129, 128, 126, 124, 124, 122, 124, 124, 126, 128, 129, 129, 131, 131, 129, 129, 128, 126, 124, 124, 122, 122, 124, 126, 126, 128, 129, 129, 131, 129, 129, 128, 126, 124, 124, 122, 122, 124, 124, 126, 128, 129, 129, 131, 129, 129, 128, 128, 126, 124, 124, 122, 124, 124, 126, 128, 129, 129, 129, 129, 129, 129, 128, 126, 124, 124, 124, 124, 124, 126, 128, 128, 129, 129, 129, 129, 129, 128, 126, 124, 124, 124, 124, 124, 126, 126, 128, 129, 129, 129, 129, 129, 128, 126, 126, 124, 124, 124, 124, 124, 126, 128, 129, 129, 129, 129, 129, 128, 128, 126, 124, 124, 124, 124, 124, 126, 128, 128, 129, 129, 129, 129, 129, 128, 126, 124, 124, 124, 124, 124, 126, 126, 128, 129, 129, 129, 129, 129, 128, 126, 126, 124, 124, 124, 124, 126, 126, 128, 129, 129, 129, 129, 129, 128, 128, 126, 124, 124, 124, 124, 124, 126, 128, 128, 129, 129, 129, 129, 128, 128, 126, 124, 124, 124, 124, 124, 126, 128, 128, 129, 129, 129, 129, 129, 128, 126, 126, 124, 124, 124, 124, 126, 126, 128, 129, 129, 129, 129, 129, 128, 126, 126, 124, 124, 124, 124, 126, 126, 128, 128, 129, 129, 129, 129, 128, 128, 126, 124, 124, 124, 124, 124, 126, 128, 128, 129, 129, 129, 129, 128, 128, 126, 126, 124, 124, 124, 124, 126, 126, 128, 129, 129, 129, 129, 129, 128, 126, 126, 124, 124, 124, 124, 126, 126, 128, 128, 129, 129, 129, 129, 128, 128, 126, 124, 124, 124, 124, 126, 126, 128, 128, 129, 129, 129, 129, 128, 128, 126, 126, 124, 124, 124, 124, 126, 126, 128, 129, 129, 129, 129, 128, 128, 126, 126, 124, 124, 124, 124, 126, 126, 128, 128, 129, 129, 129, 128, 128, 126, 126, 124, 124, 124, 124, 126, 126, 128, 128, 129, 129, 129, 129, 128, 128, 126, 126, 124, 124, 124, 126, 126, 128, 128, 129, 129, 129, 129, 128, 128, 126, 126, 124, 124, 124, 126, 126, 126, 128, 128, 129, 129, 129, 128, 128, 126, 126, 126, 124, 124, 124, 126, 126, 128, 128, 129, 129, 129, 128, 128, 128, 126, 126, 124, 124, 124, 126, 126, 128, 128, 128, 129, 129, 129, 128, 128, 126, 126, 124, 124, 124, 126, 126, 126, 128, 128, 129, 129, 129, 128, 128, 126, 126, 126, 124, 124, 126, 126, 126, 128, 128, 129, 129, 129, 128, 128, 126, 126, 126, 124, 124, 124, 126, 126, 128, 128, 128, 129, 129, 128, 128, 128, 126, 126, 124, 124, 124, 126, 126, 128, 128, 128, 129, 129, 128, 128, 128, 126, 126, 126, 124, 124, 126, 126, 126, 128, 128, 128, 129, 128, 128, 128, 126, 126, 126, 124, 124, 126, 126, 126, 128, 128, 128, 129, 129, 128, 128, 128, 126, 126, 126, 124, 126, 126, 126, 128, 128, 128, 128, 129, 128, 128, 128, 126, 126, 126, 124, 126, 126, 126, 126, 128, 128, 128, 129, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 126, 128, 128, 128, 128, 128, 128, 128, 126, 126, 126, 126, 126
};

// --------------------------
// Setup and loop
// --------------------------
void setup() {
  // Set LED pins to output mode
  pinMode(STOCK_LED_PIN_1, OUTPUT);
  pinMode(STOCK_LED_PIN_2, OUTPUT);
  pinMode(READY_LED_PIN, OUTPUT);

  // Set up UDS pins
  pinMode(UDS_TRIG_PIN, OUTPUT);
  pinMode(UDS_ECHO_PIN, INPUT);

  // Set up serial monitor
  Serial.begin(9600);

  // Play a test tune on the speaker
  startPlayback(softChime, sizeof(softChime));

  delay(500);
  Serial.println("Uno ready!");
  Serial.println("");
}

void loop() {
  Serial.println("Looping!");

  // Turn on both stock indicator LEDs
  digitalWrite(STOCK_LED_PIN_1, HIGH);
  digitalWrite(STOCK_LED_PIN_2, HIGH);

  // Measure distance
  int dist = measureDistance();
  
  // Blink the "Medication ready" LED
  blinkLED(READY_LED_PIN);

  // Rotate both servos
  rotateServoCont(servo_one);
  rotateServoCont(servo_two);
}


// --------------------------
// Functions
// --------------------------
void blinkLED(int pin) {
  digitalWrite(pin, HIGH);
  delay(1000);
  digitalWrite(pin, LOW);
  delay(1000);
}

int measureDistance() {
  const float speedSound = 0.034; // Centimeters per microsecond

  digitalWrite(UDS_TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(UDS_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(UDS_TRIG_PIN, LOW);

  long duration = pulseIn(UDS_ECHO_PIN, HIGH);
  Serial.print("Pulse duration: ");
  Serial.println(duration);
  
  int distance = duration * speedSound / 2;

  Serial.print("Distance: ");
  Serial.println(distance);
  
  return distance;
}

void rotateServoCont(ServoTimer2 servo) {
  // Attach servos to PWM generator
  servo_one.attach(SERVO_ONE_PIN);
  servo_two.attach(SERVO_TWO_PIN);
  delay(1000);
  
  // Let the servo turn at a speed of 100 for 2260ms
  servo.write(100);
  delay(2260);

  // Stop the servo from rotating (90 is neutral)
  servo.write(90);
  delay(2000);

  // Detach servos from PWM generator
  servo_one.detach();
  servo_two.detach();
  delay(1000);

  Serial.println("Finished rotating servo!");
}
