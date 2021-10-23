#pragma once
#include<iostream>
#include<math.h>
#include<assert.h>
using namespace std;

class Vector3D
{
public:
    float x, y, z;

    //Constructors
    Vector3D();  //constructor	
        Vector3D(float x1, float y1, float z1 = 0);  //construct with values.
        Vector3D(const Vector3D& vector); //copy constructor

    //Arithemetic Operators – note use of overloading
    //Addition
    Vector3D operator+(const Vector3D& vector); 

    //Assign new result to vector
    Vector3D& operator+=(const Vector3D& vector);

    //Substraction
    Vector3D operator-(const Vector3D& vector); 

    //Assign new result to vector
    Vector3D& operator-=(const Vector3D& vector);

    //Multiplication
    Vector3D operator*(float value);    

    //Assign new result to vector
    Vector3D& operator*=(float value);

    //Division
    Vector3D operator/(float value);    

    //Assign new result to vector
    Vector3D& operator/=(float value);

    Vector3D& operator=(const Vector3D& vector);

    //vectortor operations
    float dot_product(const Vector3D& vector);      //scalar dot_product
    Vector3D cross_product(const Vector3D& vector); //cross_product
    Vector3D normalization();                    //normalized vector

    //Scalar operations - Operations using whole/real numbers

    float square(); //gives square of the vectortor
    
    
    float distance(const Vector3D& vector); //distance between two vectortors
    
    
    float magnitude();  //magnitude of the vectortor


    //Display operations 
    float show_X(); //return x
    float show_Y(); //return y
    float show_Z(); //return z
    void disp();    //display value of vectortors
};

