# cc3K+

## AVOID PUSHING .o and .d FILES ALSO ANY EXECUTABLE YOU MAKE

---

## Work Division:
- **Alim** - Item and its classes
- **Luka** - Enemy and its classes
- **Sunae** - Player and the rest of the classes

---

## Notes:
- The action line should be implemented within the `action` method by calling `setCommandLine` after creating the appropriate string.

---

## Things to Do:

### **Other Mechanics**
- ASCII colour output codes for player, enemies, treasure, potions
- https://medium.com/@vitorcosta.matias/print-coloured-texts-in-console-a0db6f589138 for guide
- generating floors based off a command line argument file

### **Player Mechanics**
- Player ability must be applied correctly

### **Enemy Class**
- Implement Dragon hositlity when PC is near its gold (needs protected item implementation)

### **Items Class**
- Implement `usePotion`/pickUp method (must be within 1 block radius of potion)
- Potions are unknown until used or bought from a merchant (Buying from merchants is optional)
- Implement permanent vs temp potions:
  - Stats cannot drop below 0
  - Temp potions disappear when entering a new floor
- Protected item implementation
- Implement major items
