## 1. Header File Updates

- [x] 1.1 Add TurnRound() method declaration to robot_executor.h
- [x] 1.2 Add Forward(int32_t steps) method declaration to robot_executor.h
- [x] 1.3 Add Backward(int32_t steps) method declaration to robot_executor.h

## 2. Implementation File Updates

- [x] 2.1 Implement TurnRound() method - call TurnRight() twice
- [x] 2.2 Implement Forward(int32_t steps) method - loop steps times calling Forward()
- [x] 2.3 Implement Backward(int32_t steps) method - loop steps times calling Backward()
- [x] 2.4 Add validation for steps > 0 in Forward/Backward methods

## 3. Testing

- [x] 3.1 Add unit tests for TurnRound in all four heading directions
- [x] 3.2 Add unit tests for Forward(steps) - verify position changes correctly
- [x] 3.3 Add unit tests for Backward(steps) - verify position changes correctly
- [x] 3.4 Add unit tests for edge cases: steps = 0, steps < 0
- [ ] 3.5 Add unit tests for alert and cleanup triggering behavior

## 4. Build and Verify

- [x] 4.1 Build project with ./ccup.sh -b
- [x] 4.2 Run tests with ./ccup.sh -t