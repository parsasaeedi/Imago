/**
 * @file main.cpp
 * A simple C++ program that manipulates an image.
 *
 * @author CS 221: Basic Algorithms and Data Structures
**/

#include <iostream>
#include <cmath>
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
    adjustColumn(&png, column, -20, 0, 0, 0, 0, 0);
  }
}

int main() {

  png.readFromFile("input.png");

  for (unsigned int i=0; i<png.width(); i++) {
    numberQueue.push(i);
  }

  vector<thread> threads(NUM_OF_THREADS);
  for (int i=0; i<NUM_OF_THREADS; i++) {
    threads[i] = std::thread(dequeue);
  } 

  for (int i=0; i<NUM_OF_THREADS; i++) {
    threads[i].join();
  }

  png.writeToFile("output.png");
  return 0;
}