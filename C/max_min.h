/*
 * Minimum and maximum functions
 *
 * Make sure you know what types you are comparing,
 *   void* can cause runtime errors if your type cannot
 *   be compared. You have been warned.
 *
 * Author: Thomas Maher
 * Modified: 2/11/2020 
*/


void* max(void* obj1, void* obj2) {
  /*
    Takes in pointers to two comparable objects and returns the higher valued object

    @param obj1: first object to compare
    @param obj2: second object to compare

    @return: The object with higher value
  */
  return (obj1 > obj2) ? obj1 : obj2;
}

void* min(void* obj1, void* obj2) {
  /*
    Takes in pointers to two comparable objects and returns the lower valued object

    @param obj1: first object to compare
    @param obj2: second object to compare

    @return: The object with lower value
  */
  return (obj1 < obj2) ? obj1 : obj2;
}

