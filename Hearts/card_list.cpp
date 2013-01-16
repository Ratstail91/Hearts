/* File Name: card_list.cpp
 * Copyright: (c) Kayne Ruse 2011, 2012
 * This file is part of Hearts.
 * 
 * Hearts is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Hearts is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Hearts.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * Author: Kayne Ruse
 * Date: 5/6/2011
 * Version: 
 * Description: Designed for Project Hearts, 4th try.
*/
#include <iostream>
#include <time.h>
#include "card_list.h"
using namespace std;

//-------------------------
//Public access members
//-------------------------

CardList::CardList() {
	headCard = NULL;
}

//-------------------------
//List accessors
//-------------------------

void CardList::Receive(Card* slabHead) {
	if (headCard == NULL)
		headCard = slabHead;
	else {
		iterator it = headCard;
		while(it->GetNext() != NULL)
			it = it->GetNext();
		it->SetNext(slabHead);
	}
}

Card* CardList::Read(int index) {
	iterator it = headCard;

	for (int i = 0; i < index; i++) {
		if (it != NULL)
			it = it->GetNext();
		else
			return NULL;
	}

	return it;
}

Card* CardList::Pass(int index) {
	//special cases
	if (headCard == NULL)
		return NULL;

	if (index == 0) {
		iterator ret = headCard;
		headCard = headCard->GetNext();
		ret->SetNext(NULL);
		return ret;
	}

	//iterate through the list
	iterator it = headCard;
	iterator prev = NULL;

	for (int i = 0; i < index; i++) {
		if (it->GetNext() != NULL) {
			prev = it;
			it = it->GetNext();
		}
		else
			return NULL;
	}

	//return this card
	prev->SetNext(it->GetNext());
	it->SetNext(NULL);
	return it;
}

Card* CardList::PassSlab(int first, int count) {
	//special cases
	if (headCard == NULL)
		return NULL;

	if (count < 2)
		return Pass(first);

	//Find the first & last card
	iterator prevFirst = (first < 1) ? NULL : Read(first - 1);
	iterator prevLast = Read(first + count - 1);

	//return this section of the list
	iterator ret = NULL;

	if (prevFirst != NULL && prevLast != NULL) {
		//everything is normal
		ret = prevFirst->GetNext();
		prevFirst->SetNext(prevLast->GetNext());
		prevLast->SetNext(NULL);
	}

	else if (prevFirst == NULL && prevLast != NULL) {
		//returning the first card
		ret = headCard;
		headCard = prevLast->GetNext();
		prevLast->SetNext(NULL);
	}

	else if (prevFirst == NULL && prevLast == NULL) {
		ret = headCard;
		headCard = NULL;
	}

	else if (prevFirst != NULL && prevLast == NULL) {
		ret = prevFirst->GetNext();
		prevFirst->SetNext(NULL);
	}

	return ret;
}

//-------------------------
//Misc members
//-------------------------

void CardList::Shuffle() {
	//New version
	srand((unsigned int)time(NULL)); //TODO: Remove this, initiate randomization in the Scene (and shuffle 3 times ;) )
	iterator shuffleHead = NULL;
	iterator prev = NULL;

	do {
		//shuffling backwards
		prev = shuffleHead;
		shuffleHead = Pass(rand() % Size());
		shuffleHead->SetNext(prev);
	}
	while(headCard != NULL);

	headCard = shuffleHead;
}

void CardList::Sort() {
	//Sort the cards in the list
	if (headCard == NULL) {
		return;
	}

	iterator sortHead = Pass();
	iterator it = sortHead;

	while(it != NULL && Size()) {
		//first card
		if (*it > *Read()) {
			//insert the new card at the start of the list
			it = Pass();
			it->SetNext(sortHead);
			sortHead = it;
			continue;
		}

		while (it->GetNext() != NULL && *Read() > *it->GetNext()) {
			//place the iterator just before the position to insert the card
			it = it->GetNext();
		}

		//insert the next card here
		iterator tmp = Pass();
		tmp->SetNext(it->GetNext());
		it->SetNext(tmp);

		//reset
		it = sortHead;
	}

	headCard = sortHead;
}

void CardList::SortRank() {
	//Sort the cards in the list
	if (headCard == NULL) {
		return;
	}

	iterator sortHead = Pass();
	iterator it = sortHead;

	while(it != NULL && Size()) {
		//first card
		if (it->Rank() > Read()->Rank()) {
			//insert the new card at the start of the list
			it = Pass();
			it->SetNext(sortHead);
			sortHead = it;
			continue;
		}

		while (it->GetNext() != NULL && Read()->Rank() > it->GetNext()->Rank()) {
			//place the iterator just before the position to insert the card
			it = it->GetNext();
		}

		//insert the next card here
		iterator tmp = Pass();
		tmp->SetNext(it->GetNext());
		it->SetNext(tmp);

		//reset
		it = sortHead;
	}

	headCard = sortHead;
}

int CardList::Size() {
	int count = 0;
	for (iterator it = headCard; it != NULL; count++)
		it = it->GetNext();
	return count;
}

Card* CardList::Head() {
	return headCard;
}

void CardList::DrawAll(SDL_Surface* dest) {
	for (iterator it = headCard;it != NULL;it = it->GetNext())
		it->Draw(dest);
}
