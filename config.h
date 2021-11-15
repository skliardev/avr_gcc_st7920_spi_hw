/*
 * config.h
 *
 * Created: 13.11.2021 18:50:18
 *  Author: Dmitry
 */ 
#ifndef CONFIG_H_
#define CONFIG_H_

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

inline void CPU_init() {
	CLKPR = 0x80;
	CLKPR = 0x00;
}

inline void copy1byte(void* dst, void* src) {
	*((uint8_t*)dst) = *((uint8_t*)src);
}

inline void copy2byte(void* dst, void* src) {
	*((uint16_t*)dst) = *((uint16_t*)src);
}

inline void copy4byte(void* dst, void* src) {
	*((uint32_t*)dst) = *((uint32_t*)src);
}

inline void copy8byte(void* dst, void* src) {
	*((uint64_t*)dst) = *((uint64_t*)src);
}

#endif /* CONFIG_H_ */