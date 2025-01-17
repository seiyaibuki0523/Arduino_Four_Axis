#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <printf.h>

RF24 radio(8, 9);				 // 指定 Arduino Nano 腳位對應 nRF24L01 之 (CE, CSN)
const byte address[6] = "1Node"; // 節點位址為 5 bytes + \0=6 bytes

void setup() {
	Serial.begin(9600);
	radio.begin();					   // 初始化 nRF24L01 模組
	printf_begin();					   // 初始化 RF24 的列印輸出功能
	radio.setChannel(83);
	radio.setDataRate(RF24_2MBPS);
	radio.openReadingPipe(0, address); // 開啟 pipe 0 之讀取管線
	radio.setPALevel(RF24_PA_MAX);	   // 設為低功率, 預設為 RF24_PA_MAX
	radio.startListening();			   // 接收端開始接收
	radio.printDetails();			   // 印出 nRF24L01 詳細狀態
	Serial.println("NRF24L01 receiver");
	Serial.println("waiting...");
}

void loop() {
	if (radio.available()) {									 // 偵測接收緩衝器是否有資料
		char text[32] = "";				 // 用來儲存接收字元之陣列
		radio.read(&text, sizeof(text)); // 讀取接收字元
		Serial.println(text);
	}
	delay(20);
}