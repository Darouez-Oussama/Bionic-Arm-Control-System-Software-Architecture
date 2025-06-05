#include <Arduino.h>

#ifdef APP_FULL_ARM
#include "FullArm.h"
#elif defined(APP_DATASET_GENERATION)
#include "DatasetGeneration.h"
#else
#error "No application selected"
#endif

static BionicArmApp& app = BionicArmApp::getInstance();

void setup() {
  app.run();
}

void loop() {

}

