// Day9Test.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <map>
#include <list>

#include "Marble.h"
#include "Day14.h"
int main()
{
    //Marble * current;

    //int numberOfPlayers = 438;
    //int lastMarbleWorth = 71626 * 100;

    //int numplayers = 438;
    //int lastmarble = 71626*100;

    //int currentmarble = 1;
    //int currentplayer = 1;

    //Marble * root = new Marble();
    //root->_value = 0;
    //current = root;
    //std::map<int, long long> scores;
    //for (size_t i = 1; i <= numplayers; i++)
    //{
    //    scores[i] = 0;
    //}

    //while (true)
    //{
    //    if (currentmarble == lastmarble)
    //        break;

    //    if (currentmarble % 23 == 0)
    //    {
    //        scores[currentplayer] += currentmarble;
    //        for (size_t i = 0; i < 7; i++)
    //        {
    //            current = current->_prev;
    //        }
    //        scores[currentplayer] += current->_value;

    //        Marble * temp = current;
    //        Marble * prev = current->_prev;
    //        Marble * next = current->_next;

    //        prev->_next = current->_next;
    //        next->_prev = prev;
    //        current = next;

    //        currentmarble++;
    //        currentplayer++;
    //        if (currentplayer > numplayers)
    //            currentplayer = 1;

    //        delete temp;
    //        continue;
    //    }

    //    if (current->_next == nullptr)
    //    {
    //        Marble * m = new Marble();
    //        current->_next = m;

    //        m->_value = currentmarble;
    //        m->_prev = current;

    //        current = m;
    //        current->_next = root;
    //        root->_prev = current;
    //    }
    //    else
    //    {
    //        current = current->_next;

    //        Marble * m = new Marble();
    //        m->_next = current->_next;
    //        m->_prev = current; 
    //        m->_value = currentmarble;

    //        Marble * next = current->_next;
    //        current->_next = m;
    //        next->_prev = m;
    //        current = m;
    //    }

    //    currentplayer++;       
    //    if (currentplayer > numplayers)
    //        currentplayer = 1;
    //    currentmarble++;
    //}

    //current = root;
    //root->_prev->_next = nullptr;

    ///*while (current != nullptr)
    //{
    //    std::cout << current->_value << " ";
    //    current = current->_next;
    //}*/
    //std::cout << std::endl;
    //std::map<int, long long>::iterator iter;
    //long long highscore = 0;
    //int winningplayer = 0;
    //for (iter = scores.begin(); iter != scores.end(); iter++)
    //{
    //    if (iter->second > highscore)
    //    {
    //        highscore = iter->second;
    //        winningplayer = iter->first;
    //    }
    //}

    //std::cout << "Player " << winningplayer << " had high score " << highscore << std::endl;

	std::list<int> l;
	std::cout << "Max list size is " << l.max_size() << std::endl;
	std::vector<int> v;
	std::cout << "Max vector size is " << v.max_size() << std::endl;

	Day14 d14;
	d14.Run();

    return 0;
}

