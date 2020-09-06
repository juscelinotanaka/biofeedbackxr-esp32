#!/bin/bash

BOARD_NAME=esp32:esp32
MODEL_NAME=ttgo-lora32-v1
FQBN=$BOARD_NAME:$MODEL_NAME
SKETCH=bio_feedback_xr
PORT=/dev/cu.SLAB_USBtoUART

INSTALL_LINK=https://arduino.github.io/arduino-cli/latest/installation/

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
  arduino-cli core update-index
  # TODO: find a way to change config file and add ESP32 board
  arduino-cli core install $BOARD_NAME

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