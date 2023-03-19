//use in test answer of last year and get help from Roy Simanovich

#include <stdio.h>
#include <stdlib.h>
#include "AdptArray.h"
#include <string.h>

typedef struct AdptArray_
{
	int arrLength;
	PElement  *pElemArr;
	COPY_FUNC copy_func;
	DEL_FUNC del_func;
	PRINT_FUNC print_func;
} AdptArray;


PAdptArray CreateAdptArray(COPY_FUNC copyf, DEL_FUNC delf,PRINT_FUNC pf){
    PAdptArray cur = (PAdptArray) malloc(sizeof(struct AdptArray_));
    if (cur == NULL){
        return NULL;
    }
    cur -> arrLength = 0;
    cur -> pElemArr = NULL;
    cur -> copy_func  = copyf;
    cur -> print_func = pf;
	cur -> del_func = delf;
    return cur;
}

void DeleteAdptArray(PAdptArray PA){
    if (PA == NULL){
        return;
    }
    if (PA ->pElemArr != NULL){
        for(int i=0; i< PA -> arrLength; i++){
            if(*(PA -> pElemArr+i)!= NULL){
                (PA -> del_func)(*(PA ->pElemArr+i ));
            }
        }

        free (PA -> pElemArr);
    }

    free (PA);
}


Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem)
{
	PElement* newpElemArr;
	if (pArr == NULL)
	return FAIL;
	if (idx >= pArr->arrLength)
	{
		// Extend Array
		if ((newpElemArr = (PElement *)calloc((idx + 1), sizeof(PElement))) == NULL)
            return FAIL;

		// Init new array and copy old array to new array
		if (pArr -> pElemArr != NULL){
    			memcpy(newpElemArr, pArr->pElemArr, (pArr->arrLength) * sizeof(PElement));
		}

		// Free old array and save new array
		free(pArr->pElemArr);
		pArr->pElemArr = newpElemArr;
	}

	// Delete Previous Elem and Set New Elem
	if (*(pArr -> pElemArr +idx) != NULL){
	    (pArr -> del_func)(*(pArr -> pElemArr + idx));

	}

	*(pArr -> pElemArr + idx)=(pArr -> copy_func)(pNewElem);

	// Update Array Size
	pArr->arrLength = (idx >= pArr->arrLength) ? (idx + 1) : pArr->arrLength;
	return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray PArr, int x){
	if(x > PArr ->arrLength-1){
		return NULL;
	}
	if(PArr->pElemArr[x] == NULL){
		return NULL;
	}
	else{
		return PArr ->copy_func(PArr-> pElemArr[x]);;
	}
}

int GetAdptArraySize(PAdptArray PAA){
	if (PAA == NULL)
        return -1;
	return PAA->arrLength;
}

void PrintDB(PAdptArray PAA){
	   if (PAA == NULL)
    {
        return;
    }

    for (int i = 0; i < PAA->arrLength; i++)
    {
        if (PAA->pElemArr[i] != NULL)
            PAA->print_func(PAA->pElemArr[i]);
    }
}
 

