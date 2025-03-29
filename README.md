# cc3K-

## AVOID PUSHING .o and .d FILES!! ALSO ANY EXECUTABLE YOU MAKE!!

## Work Division:
### Alim - item and it’s classes
### Luka - enemy and it’s classes
### Sunae - player and the rest of the classes

### Notes:
### - the action line should be implemented within the action method by calling setCommandLine after creating the appropriate string

### Things do do:
### - player ability must be applied correctly
### - random player spawn (stairs must be spawned in seperate chamber)
### - proper generation order
### - player score generation (humans get 50% boost)

### - Enemy class:
###     - enemy generation
###     - enemy random movement "Note that enemies should be moved in a line by line fashion"
###     - hoard spawns 
###     - merchant/dragon specific behaviour
###     - player vs enemy battle mechanics
###     - enemy character display in tile class

### - Items class:
###     - potion generation
###     - use potion method implementation (must be within 1 block radius of potion)
###     - potions are unknown until used or bought from merchant
###     - implement permanent vs temp potions (stats cannot drop below 0), (temp potions are gone when entering new floor)
###     - item character display in tile class
###     - treasure generation (implement enemy behaviour of dragons/merchant)
###     - implement major items
### 