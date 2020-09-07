#!/bin/bash

BOARD_NAME=esp32:esp32
MODEL_NAME=ttgo-lora32-v1
FQBN=$BOARD_NAME:$MODEL_NAME
SKETCH=bio_feedback_xr
PORT=/dev/cu.SLAB_USBtoUART

INSTALL_LINK=https://arduino.github.io/arduino-cli/latest/installation/
BOARD_URL=https://dl.espressif.com/dl/package_esp32_index.json

# TODO: create a android-cli install flow
# TODO: create a setup flow
# TODO: handle dependencies

if [[ "$1" == "install" ]]; then
  echo "$OSTYPE";
  if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh
  elif [[ "$OSTYPE" == "darwin"* ]]; then
    echo "Installing Android CLI on Mac"
    brew update;
    brew install android-cli;
  elif [[ "$OSTYPE" == "cygwin" ]]; then
    # POSIX compatibility layer and Linux environment emulation for Windows
    curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh
  elif [[ "$OSTYPE" == "msys" ]]; then
    # Lightweight shell and GNU utilities compiled for Windows (part of MinGW)
    curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh
  elif [[ "$OSTYPE" == "win32" ]]; then
    # I'm not sure this can happen.
    echo "Please check Android-CLI website: $INSTALL_LINK"
  else
    echo "Please check Android-CLI website: $INSTALL_LINK"
  fi

elif [[ "$1" == "setup" ]]; then
  echo "Setting up project"
  arduino-cli config init
  # install libs
  arduino-cli lib install TFT_eSPI
  arduino-cli  core update-index --additional-urls $BOARD_URL
  # TODO: check if it really works, otherwise it will be needed to add the URL on the config file
  arduino-cli core install --additional-urls $BOARD_URL $BOARD_NAME

elif [[ "$1" == "build" ]]; then
  echo "arduino-cli compile --fqbn $FQBN $SKETCH"
  arduino-cli compile --fqbn $FQBN $SKETCH

elif [ -z "$1" ]; then # check if there is no arguments

  arduino-cli compile --fqbn $FQBN $SKETCH
  RESULT=$?
  if [ $RESULT -eq 0 ]; then
    echo ""
    echo "-> Compilation completed! Starting upload ..."
    echo ""

    cd ..
    arduino-cli upload -p $PORT --fqbn $FQBN $SKETCH
  fi

else
  echo "Invalid parameter: $1"
fi