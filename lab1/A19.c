#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Header.h"


list_t* CreateList(void) {
	list_t* list = malloc(sizeof(list));
	if (list == NULL)
		return NULL;
	list->head = NULL;
	list->tail = NULL;
	return list;
}

list_t* DestroyList(list_t* list) {
	while (list->head != NULL) {
		node_t* p = list->head;
		list->head = list->head->next;
		free(p);
	}
	return list->head;
}

void PrintLine(char* str) {
	while ((*str) != 0) {
		printf("%c", *str);
		str++;
	}
}

void PrintList(list_t* list) {
	node_t* tmp = list->head;
	while (tmp != NULL) {
		PrintLine(tmp->data);
		printf("\n");
		tmp = tmp->next;
	}
}

int Length(char* str) {
	int len = 0;
	while (str[len++]);
	return len;
}

char* CopyStr(char* from) {
	int length = Length(from), i;
	char* to = malloc((length + 1) * sizeof(char));
	if (to == NULL)
		return NULL;
	for (i = 0; i <= length; i++) {
		to[i] = from[i];
	}
	return to;
}

void AddToList(list_t* list, char data[]) {
	node_t* newNode = malloc(sizeof(node_t));
	if (newNode == NULL)
		list == NULL;
	newNode->data = CopyStr(data);
	newNode->next = list->head;
	newNode->prev = NULL;
	if (list->head != NULL) {
		list->head->prev = newNode; // Óñòàíàâëèâàåì îáðàòíóþ ññûëêó ó ñòàðîé ãîëîâû
	}
	list->head = newNode;
	if (list->tail == NULL) {
		list->tail = newNode; // Åñëè ñïèñîê áûë ïóñò, óñòàíàâëèâàåì tail
	}
}

list_t* SortList(list_t* list) {
	if (list == NULL || list->head == NULL) {
		return list; // Åñëè ñïèñîê ïóñò, íè÷åãî íå äåëàåì
	}

	list_t* newlist = (list_t*)malloc(sizeof(list_t));
	if (newlist == NULL) {
		return NULL; // Ïðîâåðêà íà óñïåøíîå âûäåëåíèå ïàìÿòè
	}
	newlist->head = NULL;
	newlist->tail = NULL;

	while (list->head != NULL) {
		node_t* current = list->head;
		node_t* maxNode = current;

		// Ïîèñê ìàêñèìàëüíîãî ýëåìåíòà â ñïèñêå
		while (current != NULL) {
			if (strcmp(current->data, maxNode->data) > 0) {
				maxNode = current;
			}
			current = current->next;
		}

		// Óäàëåíèå ìàêñèìàëüíîãî ýëåìåíòà èç ñòàðîãî ñïèñêà
		if (maxNode->prev) {
			maxNode->prev->next = maxNode->next;
		}
		else {
			list->head = maxNode->next; // åñëè maxNode - ãîëîâà ñïèñêà
		}

		if (maxNode->next) {
			maxNode->next->prev = maxNode->prev;
		}
		else {
			list->tail = maxNode->prev; // åñëè maxNode - õâîñò ñïèñêà
		}

		// Äîáàâëåíèå ìàêñèìàëüíîãî ýëåìåíòà â íîâûé ñïèñîê
		maxNode->next = newlist->head;
		maxNode->prev = NULL;

		if (newlist->head != NULL) {
			newlist->head->prev = maxNode;
		}
		newlist->head = maxNode;

		if (newlist->tail == NULL) {
			newlist->tail = maxNode; // Îáíîâëÿåì õâîñò íîâîãî ñïèñêà
		}
	}

	return newlist; // Âîçâðàùàåì îòñîðòèðîâàííûé ñïèñîê
}

int main(void) {
	list_t* list = CreateList();
	AddToList(list, "cckvbskdjvsdj flk");
	AddToList(list, "-DOFH4");
	AddToList(list, "2f ngpDNSJDCNjjhdvb0");
	AddToList(list, "4kf deffn gp0");
	AddToList(list, "&3298 328u31/fwef12./,");
	AddToList(list, "u *%");
	AddToList(list, "--");
	AddToList(list, "&3298 328u31/fwef12./,");
	AddToList(list, "u6789 9 *%");
	AddToList(list, "-9999 bf n-");

	PrintList(list);
	list = SortList(list);
	printf("\n");
	PrintList(list);
	DestroyList(list);
	return 0;
}
