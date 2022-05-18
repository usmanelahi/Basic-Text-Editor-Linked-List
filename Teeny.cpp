#include <iostream>
#include <string>
#include "Teeny.h"
using namespace std;


struct Node {
    char ch;
    Node* next;
    Node* prev;

    Node(char c) {
        ch = c;
        next = nullptr;
        prev = nullptr;
    }
};

//Skeleton of class LinkedText
class LinkedText {
    Node* head, * tail, * cursorPos;
    int textSize;

public:
    LinkedText() {
        head = tail = cursorPos = NULL;
        textSize = 0;
    }

    //some suggested methods
    //All these methods (except copying) are O(1) thanks to the linked list!
    void addCharAtCursorPos(char input) //when char entered
    {
        if (head == nullptr) {
            Node* temp = new Node(input);
            temp->ch = input;
            temp->next = nullptr;
            temp->prev = nullptr;
            head = temp;
            tail = temp;
            cursorPos = temp;
        }
        else {
            Node* temp = new Node(input);
            if (cursorPos == tail) {
                cursorPos->next = temp;
                temp->prev = cursorPos;
                tail = temp;
                cursorPos = temp;
            }
            else if (cursorPos == head) {
                cursorPos->prev = temp;
                temp->next = cursorPos;
                head = temp;
            }
            else {
                cursorPos->next->prev = temp;
                temp->next = cursorPos->next;
                cursorPos->next = temp;
                temp->prev = cursorPos;
                cursorPos = temp;
            }
        }
        textSize++;
    }

    void delCharAtCursorPos() //when bksp pressed
    {
        if (head != nullptr) {
            if (textSize == 1) {
                head = tail = cursorPos = nullptr;
            }
            else {
                Node* temp = cursorPos;
                if (temp == tail) {
                    tail = temp->prev;
                    tail->next = nullptr;
                    cursorPos = tail;
                }
                else if (temp == head) {
                    head = head->next;
                    head->prev = nullptr;
                    cursorPos = head;
                }
                else {
                    temp->prev->next = temp->next;
                    temp->next->prev = temp->prev;
                    cursorPos = temp->prev;
                }
                delete temp;
            }
            textSize--;
        }
    }

    void moveCursorRight()//right arrow
    {
        if (cursorPos->next != nullptr) {
            cursorPos = cursorPos->next;
        }
    }

    void moveCursorLeft()//left arrow
    {
        if (cursorPos->prev != nullptr) {
            cursorPos = cursorPos->prev;
        }
    }

    /*the following method returns the sub-list after cutting,
    and also adjusts cursor position*/
    Node* cutTextBetween(Node* cursorpos1, Node* cursorpos2)
    {
        Node* temp = head;
        bool sorted = false;
        for (; temp != cursorpos2; temp = temp->next) {
            if (temp == cursorpos1) {
                sorted = true;
            }
        }
        if (sorted == false) {
            temp = cursorpos1;
            cursorpos1 = cursorpos2;
            cursorpos2 = temp;
        }
        cursorPos = cursorpos1;
        int i = 1;
        Node* count = cursorpos1;
        for (; count != cursorpos2; count = count->next, i++);
        Node* buffer = cursorpos1;
        if (cursorpos1 != cursorpos2) {
            if (cursorpos1 != head) {
                cursorpos1->prev->next = cursorpos2->next;
                cursorPos = cursorpos1->prev;
                if (cursorpos2 != tail) {
                    cursorpos2->next->prev = cursorpos1->prev;
                }
                else {
                    tail = cursorpos1->prev;
                    tail->next = nullptr;
                }
            }
            else if (cursorpos1 == head) {
                head = cursorpos2->next;
                head->prev = nullptr;
                cursorPos = head;
            }
        }
        else {
            if (cursorpos1 == head) {
                head = head->next;
                head->prev = nullptr;
                buffer->next = nullptr;
                cursorPos = head;
            }
            else if (cursorpos1 == tail) {
                tail = tail->prev;
                tail->next = nullptr;
                buffer->prev = nullptr;
                cursorPos = tail;
            }
            else {
                cursorpos1->prev->next = cursorpos1->next;
                cursorpos1->next->prev = cursorpos1->prev;
                cursorPos = cursorpos1->prev;
            }
        }
        cursorpos2->next = nullptr;
        textSize -= i;
        return buffer;
    }
    /*the following method returns the duplicated sub-list after copying,
    and also adjusts cursor position*/
    Node* copyTextBetween(Node* cursorpos1, Node* cursorpos2)
    {
        Node* buffer = nullptr;
        Node* temp = head;
        bool sorted = false;
        for (; temp != cursorpos2; temp = temp->next) {
            if (temp == cursorpos1) {
                sorted = true;
            }
        }
        if (sorted == false) {
            temp = cursorpos1;
            cursorpos1 = cursorpos2;
            cursorpos2 = temp;
        }
        if (cursorpos1 == cursorpos2) {
            Node* ite = new Node(cursorpos1->ch);
            buffer = ite;
        }
        else {
            Node* ite = new Node(cursorpos1->ch);
            buffer = ite;
            Node* temp1 = buffer;
            cursorpos1 = cursorpos1->next;
            while (cursorpos1 != cursorpos2) {
                ite = new Node(cursorpos1->ch);
                temp1->next = ite;
                ite->prev = temp1;
                temp1 = ite;
                cursorpos1 = cursorpos1->next;
            }
            ite = new Node(cursorpos1->ch);
            temp1->next = ite;
            ite->prev = temp1;
            temp1 = ite;
            temp1->next = nullptr;
        }
        return buffer;
    }

    void insertTextAtCursorPos(Node* subList)
    {
        if (subList != nullptr) {
            int i = 0;
            Node* count = subList;
            for (; count != nullptr; count = count->next, i++);
            Node* temp = subList;
            for (; temp->next != nullptr; temp = temp->next);
            if (cursorPos == head) {
                head->prev = temp;
                temp->next = head;
                head = subList;
            }
            else if (cursorPos == tail) {
                tail->next = subList;
                subList->prev = tail;
                tail = temp;
                tail->next = nullptr;
            }
            else {
                temp->next = cursorPos->next;
                cursorPos->next->prev = temp;
                cursorPos->next = subList;
                subList->prev = cursorPos;
            }
            textSize += i;
        }
    }

    /*Method returns the number of times key occurs
    in LinkedText*/
    int findInText(const string& key)
    {
        int len1 = textSize, len2 = key.size();
        int count = 0;
        Node* temp = head;
        for (int i = 0; i <= (len1 - len2); i++, temp = temp->next) {
            bool match = true;
            Node* temp1 = temp;
            for (int k = 0; k < len2 && match; temp1 = temp1->next, k++) {
                if (temp1->ch != key[k]) {
                    match = false;
                }
            }
            if (match) {
                count++;
            }
        }
        return count;
    }

    //You may add appropriate printing methods and other methods below
    ~LinkedText() {
        head = tail = cursorPos = NULL;
        textSize = 0;
    };//delete the list


   /*The methods below will be used to keep
     the screen cursor inside the text area
     only.
   */
    inline bool textToLeft() {
        return (cursorPos != NULL && cursorPos->prev != NULL);
    }


    inline bool textToRight() {
        return (cursorPos != NULL);
    }

    void print() {
        Node* temp = head;
        if (temp != nullptr) {
            for (; temp->next != nullptr; temp = temp->next) {
                cout << temp->ch;
            }
            cout << temp->ch;
        }
    }

    Node* getCursorPos() {
        return cursorPos;
    }

    int readjust() {
        Node* temp = tail;
        int i = 0;
        if (cursorPos != tail) {
            while (temp != cursorPos) {
                i++;
                temp = temp->prev;
            }
        }
        return i;
    }
};

int main()
{
    GetConsoleWindowDims();
    /*This starter code is capable of detecting the
      left and right arrow keys; the backspace key;
      the escape key (for quit); the F1, F2 and F3 keys;
      and the regular text keys.
      Written for CS-218 "Data Structures" BCS-3A, FAST-NU, Lahore.
    */
    LinkedText text;
    Node* start = nullptr;
    Node* end = nullptr;
    Node* buffer = nullptr;
    string in;
    int count = 0;
    int key;
    key = ARROW_LEFT;
    while (key != ESCAPE) {
        key = _getch();
        //either an arrow or function key is pressed
        if (SPECIAL_KEY(key)) {
            key = _getch();//get 2nd part of code from buffer
            switch (key) {
            case ARROW_LEFT:
                if (text.textToLeft()) {
                    moveScreenCursorLeft();
                    text.moveCursorLeft();
                }
                break;
            case ARROW_RIGHT:
                if (text.textToRight()) {
                    moveScreenCursorRight();
                    text.moveCursorRight();
                }
                break;
            case F1://start or end text selection
                start = text.getCursorPos();
                break;
            case F2://cut option
                end = text.getCursorPos();
                buffer = text.cutTextBetween(start, end);
                start = end = nullptr;
                system("cls");
                text.print();
                for (int i = 0; i < text.readjust(); i++) {
                    moveScreenCursorLeft();
                }
                break;
            case F3://copy option
                end = text.getCursorPos();
                buffer = text.copyTextBetween(start, end);
                start = end = nullptr;
                system("cls");
                text.print();
                for (int i = 0; i < text.readjust(); i++) {
                    moveScreenCursorLeft();
                }
                break;
            case F5://for search
                cout << endl << "Please enter a word to find:";
                getline(cin, in);
                count = text.findInText(in);
                cout << "The key occurs in the text " << count << " times." << endl;
                system("pause");
                break;
            case INSERT://to insert text
                text.insertTextAtCursorPos(buffer);
                buffer = nullptr;
                break;
            };
        }
        else if (key == BACKSPACE) {
            text.delCharAtCursorPos();
            moveScreenCursorLeft();
        }
        else {
            text.addCharAtCursorPos(key);
        }
        system("cls");
        text.print();
        for (int i = 0; i < text.readjust(); i++) {
            moveScreenCursorLeft();
        }
    }
    return 0;
}
