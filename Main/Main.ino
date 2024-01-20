#include "Animation.h"
#include "FileManagement.h"

Animation animation = Animation(2, 2, 2);
FileManagement fileManagement = FileManagement(2, 2, 2);
void setup() {
    //animation.execute();
    //fileManagement.execute();
}

void loop() {
    animation.execute();
    //fileManagement.execute();
}
