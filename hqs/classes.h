#include <string>

using namespace std;

#ifndef CLASSES_H
#define CLASSES_H
    class Superpower{
        private:
            string name;
            int level;

        public:
            Superpower(string name, int level);

            int getLevel();

            int getSuperpower();
    }

    class Character{
        private:
            string name;
            string realLifeName;
            Superpower* powers = new Superpower[4];

        public:

    }
#endif