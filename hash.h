#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here

        //creating an array of letters translated into values
        int translated[k.length()];
        for (int i = k.length()-1; i >= 0; i--){
            translated[i] = letterDigitToNumber(k[i]); //reverse order
        }

        unsigned long long w[5] = {0, 0, 0, 0, 0};
        int index = 4; //index in w[]
        int power = 0; //what power to raise 36 to
        unsigned long long sum = 0;

        for (int i = k.length()-1; i >= 0; i--){
            sum = sum + (translated[i]*pow(36,power));
            power++;

            //if you have reached the 6th char
            if (power == 6){
                //reset everything
                power = 0;
                w[index] = sum;
                index--;
                sum = 0;
            }
        }

        //if you reach end of loop and there isn't 6 chars
        if (sum != 0){
            w[index] = sum;
        }
        sum = 0;

        //multiplying with the "random" numbers for the final hashing process
        HASH_INDEX_T end = 0;
        for (int i = 0; i<5; i++){
            end = end + (w[i]*rValues[i]);
        }
        return end;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        
        //if letter is lowercase
        if (int(letter) >= 97 && int(letter) <=122){
            return int(letter)-97;
        }
        //if letter is uppercase
        else if (int(letter) >= 65 && int(letter) <= 90){
            return int(letter)-65;
        }
        //if letter is a number
        else {
            return int(letter)-22;
        }
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
