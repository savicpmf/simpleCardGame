#include <iostream>
#include <algorithm>
#include <ctime>
#include <random>
#include <vector>

using namespace std;


void showField(vector<int> field)
{
    cout << "Cards on the field " << endl;
    int row = 0;
    for (const auto& card : field)
    {
        row++;
        if (card != -1)
        {
            cout << card << " ";
        }
        else
        {
            cout << "X" << " ";
        }
       
        if (row == 3)
        {
            row = row - 3;
            cout << endl;
        }
    }
    cout << endl;
}


int main() 
{
    cout << "The following is a card game in which you want to empty out your deck by placing cards on the field while" << endl
        << "guessing if the next card is higher or lower, first you select a field (1 - 9) and then select if you think the" << endl 
        << "next card is higher or lower than the selected card on the field (h - l)"
        << " good luck!!" << endl;


    srand(time(0));

    vector<int> cards(52);
    vector<int> field;

    // Creates the deck of cards
    for (int i = 0; i < 52; ++i) 
    {
        cards[i] = (i % 13) + 1;
    }

    //randomizes cards
    shuffle(begin(cards), end(cards), default_random_engine(time(0)));

   

    // drawing the first 9 cards for the field
    int numberOfFields = 9; 

    for (int i = 0; i < numberOfFields; ++i) 
    {
        field.push_back(cards.back());
        cards.pop_back();
    }
    cout << endl;

    
    int chosenField=-1;
    char higherOrLower;
    while (numberOfFields>0 && !cards.empty())
    {
        showField(field);

        cout << "pick a field (1-9)" << endl;
        cin >> chosenField;
        chosenField--; // because the fields go from 0-8
        if ((chosenField < 0 || chosenField > 8) || field[chosenField]==-1)
        {
            cout << "the field must be a number 1-9 and cannot be disabled" << endl;
            continue;
        }
        cout << "higher or lower? (h/l)" << endl;
        cin >> higherOrLower;
        if (higherOrLower != 'l' && higherOrLower != 'h')
        {
            cout << "the choice must be h or l lowercase" << endl;
            continue;
        }

        int nextCard = cards.back();

        cout << "the next card was " << nextCard << endl << endl;
        
        
        if (higherOrLower == 'h')
        {
            if (nextCard > field[chosenField])
            {
                cards.pop_back();
                field[chosenField] = nextCard;
            }
            else
            {
                cards.pop_back();
                field[chosenField] = -1;
                numberOfFields--;

                cout << "Incorrect! Field " << chosenField + 1 << " is disabled." << endl;
            }
           
        }
        else if (nextCard < field[chosenField])
        {
            cards.pop_back();
            field[chosenField] = nextCard;
        }
        else
        {
            cards.pop_back();
            field[chosenField] = -1;
            numberOfFields--;

            cout << "Incorrect! Field " << chosenField+1 << " is disabled." << endl;
        }

        
        if (cards.size() % 5 == 0)
        {
            cout << "there are " << cards.size() << " cards left in the deck!" << endl << endl;
        }

    }

    if (numberOfFields == 0)
    {
        cout << "you lost :(" << endl;
    }
    if (cards.empty())
    {
        cout << "you won :D, you rock :)" << endl;
    }

    return 0;
}
