# cc3K+

## AVOID PUSHING .o and .d FILESgit push origin main ALSO ANY EXECUTABLE YOU MAKEgit push origin main

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

### **Player Mechanics**
- Player ability must be applied correctly
- Proper generation order (IN PROGRESS)

### **Enemy Class**
- Merchant/Dragon specific behavior

### **Items Class**
- Potion generation
- Implement `usePotion` method (must be within 1 block radius of potion)
- Potions are unknown until used or bought from a merchant
- Implement permanent vs temp potions:
  - Stats cannot drop below 0
  - Temp potions disappear when entering a new floor
- Item character display in `Tile` class
- Treasure generation (implement enemy behavior of Dragons/Merchants)
- Implement major items
