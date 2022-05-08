/**
 * @file main.cpp
 * A simple C++ program that manipulates an image.
 *
 * @author CS 221: Basic Algorithms and Data Structures
**/

#include <iostream>
#include <cmath>
#include <cctype>
#include <stdio.h>
#include <cstdlib>
#include <thread>
#include <queue>
#include <mutex>
#include <vector>
#include "imago.h"
#include "cs221util/PNG.h"

int NUM_OF_THREADS = 8;
mutex stack_mutex;

queue<int> numberQueue;
cs221util::PNG png;
int luminance, saturation, hue, highlights, shadows, vignette;

void dequeue() {
  while(!numberQueue.empty()) {
    int column;
    stack_mutex.lock();
    if (numberQueue.empty()) {
      stack_mutex.unlock();
      break;
    } 
    column = numberQueue.front();
    numberQueue.pop();
    stack_mutex.unlock();
    adjustColumn(&png, column, luminance, saturation, hue, highlights, shadows, vignette);
  }
}

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && (std::isdigit(*it) || *it == '-')) ++it;
    return !s.empty() && it == s.end();
}

void exitMessage(string message) {
  cout << message << endl;
  exit (EXIT_FAILURE);
}

int askForSetting(string setting) {
  string userInput;
  int intValue;
  do {
    cout << setting << ": ";
    cin >> userInput;
    if (is_number(userInput) != 0) {
      intValue = stoi(userInput);
      if (intValue >= -100 && intValue <= 100) return intValue;
    }
    cout << "Incorrect input. Enter an integer between -100 and 100." << endl;
  } while (true);
}

int main(int argc, char *argv[]) {

  string fileName;

  if (argc > 1) {
    if ( argc != 8) exitMessage("Incorrect number of command-line arguments. Exiting");
    if (argv[1][0] == '\0' || !is_number(argv[2]) || !is_number(argv[3]) || !is_number(argv[4]) || !is_number(argv[5]) 
    || !is_number(argv[6]) || !is_number(argv[7])) exitMessage("Incorrect value entered. Exiting");

    fileName = argv[1];
    luminance = stoi(argv[2]);
    saturation = stoi(argv[3]);
    hue = stoi(argv[4]);
    highlights = stoi(argv[5]);
    shadows = stoi(argv[6]);
    vignette = stoi(argv[7]);

    cout << "Importing image..." << endl;
    bool readSuccess = png.readFromFile("./input-images/" + fileName + ".png");
    if (!readSuccess) {
      cout << "File not found. Make sure that the image is in the input-images folder. Exiting." << endl;
      return 0;
    }

  } else {

    cout << "Please enter the name of the file you want to enter (excluding file type): ";
    cin >> fileName;
    cout << "Importing image..." << endl;
    bool readSuccess = png.readFromFile("./input-images/" + fileName + ".png");
    if (!readSuccess) {
      cout << "File not found. Make sure that the image is in the input-images folder. Exiting." << endl;
      return 0;
    }

    cout << "Please enter the amount of adjustment you want for each setting (between -100 and 100):" << endl;

    luminance = askForSetting("luminance");
    saturation = askForSetting("saturation");
    hue = askForSetting("hue");
    highlights = askForSetting("highlights");
    shadows = askForSetting("shadows");
    vignette = askForSetting("vignette");
    
  }

  cout << "Adjusting image..." << endl;

  for (unsigned int i=0; i<png.width(); i++) {
    numberQueue.push(i);
  }

  vector<thread> threads(NUM_OF_THREADS);
  for (int i=0; i<NUM_OF_THREADS; i++) {
    threads[i] = thread(dequeue);
  } 
  for (int i=0; i<NUM_OF_THREADS; i++) {
    threads[i].join();
  }

  cout << "Exporting image..." << endl;
  png.writeToFile("./exported-images/out-" + fileName + ".png");

  cout << "You can find your exported image in the \'exported-images\' folder" << endl;

  return 0;
}