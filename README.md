# 7-Segment Counter with Increment/Decrement Buttons – STM32

An embedded systems project that increments or decrements a single-digit number (0–9) on a 7-segment display using two push buttons.  
The buttons are handled via external interrupts (EXTI peripheral) for immediate response.

---

## 📌 Project Overview

This project demonstrates:

- Interfacing a 7-segment display with STM32
- Configuring GPIO pins as outputs (segments a–g)
- Using GPIO pins as inputs for push buttons
- Handling button presses with external interrupts (EXTI)
- Incrementing and decrementing a counter from 0–9
- Implementing modulo logic to wrap around:
  - Increment: 9 → 0
  - Decrement: 0 → 9
