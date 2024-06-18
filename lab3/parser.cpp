//
//  parser.cpp
//  lab3
//
//  Modified by Tarek Abdelrahman on 2020-10-04.
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018-2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "Shape.h"

// This is the shape array, to be dynamically allocated
Shape **shapesArray;

// The number of shapes in the database, to be incremented
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here

bool checkNameValidity(string name)
{
    bool found = false;
    for (int i = 0; i < NUM_KEYWORDS; i++)
    {
        if (name == keyWordsList[i])
        {
            found = true;
            break;
        }
    }
    for (int i = 0; i < NUM_TYPES; i++)
    {
        if (name == shapeTypesList[i])
        {
            found = true;
            break;
        }
    }
    return !found;
}

bool checkTypeValidity(string type)
{
    bool found = false;
    for (int i = 0; i < NUM_TYPES; i++)
    {
        if (type == shapeTypesList[i])
        {
            found = true;
            break;
        }
    }
    return found;
}

bool searchShape(string name)
{
    for (int i = 0; i < shapeCount; i++)
    {
        if (shapesArray[i] == NULL)
            continue;
        if (shapesArray[i]->getName() == name)
        {
            return true;
        }
    }
    return false;
}

int main()
{

    string line;
    string command;

    cout << "> ";       // Prompt for input
    getline(cin, line); // Get a line from standard input

    while (!cin.eof())
    {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are cleared
        stringstream lineStream(line);

        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        if (command == "maxShapes")
        {
            if (lineStream.eof())
            {
                cout << "Error: too few arguments" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            lineStream >> max_shapes;
            if (lineStream.fail())
            {
                cout << "Error: invalid argument" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            if (max_shapes < 0)
            {
                cout << "Error: invalid value" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            if (!lineStream.eof())
            {
                cout << "Error: too many arguments" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            for (int i = 0; i < shapeCount; i++)
            {
                delete shapesArray[i];
            }
            delete[] shapesArray;
            shapesArray = new Shape *[max_shapes];
            for (int i = 0; i < max_shapes; i++)
            {
                shapesArray[i] = NULL;
            }
            shapeCount = 0;
            cout << "New database: max shapes is " << max_shapes << endl;
        }
        else if (command == "create")
        {
            string name, type;
            int x_loc, x_sz, y_loc, y_sz;
            if (lineStream.eof())
            {
                cout << "Error: too few arguments" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            lineStream >> name;
            if (lineStream.fail())
            {
                cout << "Error: invalid argument" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            if (!checkNameValidity(name))
            {
                cout << "Error: invalid shape name" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            if (searchShape(name))
            {
                cout << "Error: shape " << name << " exists" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            if (lineStream.eof())
            {
                cout << "Error: too few arguments" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            lineStream >> type;
            if (lineStream.fail())
            {
                cout << "Error: invalid argument" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            if (!checkTypeValidity(type))
            {
                cout << "Error: invalid shape type" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            if (lineStream.eof())
            {
                cout << "Error: too few arguments" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            lineStream >> x_loc;
            if (lineStream.fail())
            {
                cout << "Error: invalid argument" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            if (x_loc < 0)
            {
                cout << "Error: invalid value" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            if (lineStream.eof())
            {
                cout << "Error: too few arguments" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            lineStream >> y_loc;
            if (lineStream.fail())
            {
                cout << "Error: invalid argument" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            if (y_loc < 0)
            {
                cout << "Error: invalid value" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            if (lineStream.eof())
            {
                cout << "Error: too few arguments" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            lineStream >> x_sz;
            if (lineStream.fail())
            {
                cout << "Error: invalid argument" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            if (x_sz < 0)
            {
                cout << "Error: invalid value" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            if (lineStream.eof())
            {
                cout << "Error: too few arguments" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            lineStream >> y_sz;
            if (lineStream.fail())
            {
                cout << "Error: invalid argument" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            if (y_sz < 0)
            {
                cout << "Error: invalid value" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            if (type == "circle" && x_sz != y_sz)
            {
                cout << "Error: invalid value" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            if (!lineStream.eof())
            {
                cout << "Error: too many arguments" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            if (shapeCount >= max_shapes)
            {
                cout << "Error: shape array is full" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            Shape *shape = new Shape(name, type, x_loc, x_sz, y_loc, y_sz);
            shapesArray[shapeCount] = shape;
            shapeCount++;
            cout << "Created " << name << ": " << type << " " << x_loc << " " << y_loc << " " << x_sz << " " << y_sz << endl;
        }
        else if (command == "move")
        {
            string name;
            int x_loc, y_loc;
            if (lineStream.eof())
            {
                cout << "Error: too few arguments" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            lineStream >> name;
            if (lineStream.fail())
            {
                cout << "Error: invalid argument" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            Shape *shape = NULL;
            bool found = false;
            for (int i = 0; i < shapeCount; i++)
            {
                if (shapesArray[i] == NULL)
                    continue;
                if (shapesArray[i]->getName() == name)
                {
                    found = true;
                    shape = shapesArray[i];
                    break;
                }
            }
            if (!found)
            {
                cout << "Error: shape " << name << " not found" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            if (lineStream.eof())
            {
                cout << "Error: too few arguments" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            lineStream >> x_loc;
            if (lineStream.fail())
            {
                cout << "Error: invalid argument" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            if (x_loc < 0)
            {
                cout << "Error: invalid value" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            if (lineStream.eof())
            {
                cout << "Error: too few arguments" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            lineStream >> y_loc;
            if (lineStream.fail())
            {
                cout << "Error: invalid argument" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            if (y_loc < 0)
            {
                cout << "Error: invalid value" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            if (!lineStream.eof())
            {
                cout << "Error: too many arguments" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            shape->setXlocation(x_loc);
            shape->setYlocation(y_loc);
            cout << "Moved " << name << " to " << x_loc << " " << y_loc << endl;
        }
        else if (command == "rotate")
        {
            string name;
            int angle;
            if (lineStream.eof())
            {
                cout << "Error: too few arguments" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            lineStream >> name;
            if (lineStream.fail())
            {
                cout << "Error: invalid argument" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            Shape *shape = NULL;
            bool found = false;
            for (int i = 0; i < shapeCount; i++)
            {
                if (shapesArray[i] == NULL)
                    continue;
                if (shapesArray[i]->getName() == name)
                {
                    found = true;
                    shape = shapesArray[i];
                    break;
                }
            }
            if (!found)
            {
                cout << "Error: shape " << name << " not found" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            if (lineStream.eof())
            {
                cout << "Error: too few arguments" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            lineStream >> angle;
            if (lineStream.fail())
            {
                cout << "Error: invalid argument" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            if (angle < 0 || angle > 360)
            {
                cout << "Error: invalid value" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            if (!lineStream.eof())
            {
                cout << "Error: too many arguments" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            shape->setRotate(angle);
            cout << "Rotated " << name << " by " << angle << " degrees" << endl;
        }
        else if (command == "draw")
        {
            string name;
            if (lineStream.eof())
            {
                cout << "Error: too few arguments" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            lineStream >> name;
            if (lineStream.fail())
            {
                cout << "Error: invalid argument" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            
            if (name == "all")
            {
                if (!lineStream.eof())
            {
                cout << "Error: too many arguments" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
                cout << "Drew all shapes ";
                for (int i = 0; i < shapeCount; i++)
                {
                    if (shapesArray[i] == NULL)
                        continue;
                    shapesArray[i]->draw();
                }
                cout << endl;
            }
            else
            {
                Shape *shape = NULL;
                bool found = false;
                for (int i = 0; i < shapeCount; i++)
                {
                    if (shapesArray[i] == NULL)
                        continue;
                    if (shapesArray[i]->getName() == name)
                    {
                        found = true;
                        shape = shapesArray[i];
                        break;
                    }
                }
                if (!found)
                {
                    cout << "Error: shape " << name << " not found" << endl;
                    cout << "> "; // Prompt for input
                    getline(cin, line);
                    continue;
                }
                if (!lineStream.eof())
            {
                cout << "Error: too many arguments" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
                cout << "Drew ";
                shape->draw();
                cout << endl;
            }
        }
        else if (command == "delete")
        {
            string name;
            if (lineStream.eof())
            {
                cout << "Error: too few arguments" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            lineStream >> name;
            if (lineStream.fail())
            {
                cout << "Error: invalid argument" << endl;
                cout << "> "; // Prompt for input
                getline(cin, line);
                continue;
            }
            
            if (name == "all")
            {
                if (!lineStream.eof())
                {
                    cout << "Error: too many arguments" << endl;
                    cout << "> "; // Prompt for input
                    getline(cin, line);
                    continue;
                }
                for (int i = 0; i < shapeCount; i++)
                {
                    delete shapesArray[i];
                    shapesArray[i] = NULL;
                }
                shapeCount = 0;
                cout << "Deleted: all shapes" << endl;
            }
            else
            {
                bool found = false;
                int index = 0;
                for (int i = 0; i < shapeCount; i++)
                {
                    if (shapesArray[i] == NULL)
                        continue;
                    if (shapesArray[i]->getName() == name)
                    {
                        found = true;
                        index = i;
                        break;
                    }
                }
                if (!found)
                {
                    cout << "Error: shape " << name << " not found" << endl;
                    cout << "> "; // Prompt for input
                    getline(cin, line);
                    continue;
                }
                if (!lineStream.eof())
                {
                    cout << "Error: too many arguments" << endl;
                    cout << "> "; // Prompt for input
                    getline(cin, line);
                    continue;
                }
                delete shapesArray[index];
                shapesArray[index] = NULL;
                // shapeCount--;
                cout << "Deleted shape " << name << endl;
            }
        }
        else
        {
            cout << "Error: invalid command" << endl;
        }

        // Once the command has been processed, prompt for the
        // next command
        cout << "> "; // Prompt for input
        getline(cin, line);

    } // End input loop until EOF.
    for(int i = 0; i < shapeCount; i++)
    {
        delete shapesArray[i];
    }
    delete[] shapesArray;
    return 0;
}
