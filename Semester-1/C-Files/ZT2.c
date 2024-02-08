#include <stdio.h>

enum type{
    passenger = (int)'p',
    sleeper = (int)'s',
    diner = (int)'d'
};

struct carriage {
    enum type type;
    int capacity;
};

struct train {
    struct carriage carriages[10];
    int length;
};

void printCarriage(struct carriage c)
{
    int currCap = c.capacity;

    if(currCap < 100)
    {
        printf("[%c:0%d]", (char)(c.type - 32), c.capacity);
    }
    else
    {
        printf("[%c:%d]", (char)(c.type - 32), c.capacity);
    }
}

void printTrain(struct train *t)
{
    printf("\nTrain: ");
    if(t->length != 0)
    {
        for (int i = 0; i < t->length; i++)
        {
            printf("%d:", i);
            printCarriage(t->carriages[i]);

            if(i < t->length - 1)
            {
                printf("-");
            }
        }
        printf(" Length: %d", t->length);
    }
    else
    {
        printf("No Carriages!");
    }
}

int checkIfValidCharInput(char c, char charArray[], int arrayLength)
{
    int isInArray;
    for (int i = 0; i < arrayLength; i++)
    {
        if(c == charArray[i])
        {
            isInArray = 1;
            break;
        }
        else
        {
            isInArray = 0;
        }
    }

    if(isInArray)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int checkIfValidNumberInput(int i, int minN, int maxN)
{
    if(i < minN || i > maxN)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

char getMenu()
{
    char charInput;
    char menuInputs[] = {'p', 'n', 's', 'x'};

    printf("\nChoose Action: print train (p), new carriage (n), print stats (s) or exit (x): ");
    scanf(" %c", &charInput);

    int isValidCharInput = checkIfValidCharInput(charInput, menuInputs, 4);
    if (isValidCharInput == 0)
    {
        do
        {
            printf("\nInput invalid! Try again: ");
            scanf(" %c", &charInput);
            isValidCharInput = checkIfValidCharInput(charInput, menuInputs, 4);
        } while (isValidCharInput == 0);
    }

    return charInput;
}

struct carriage getCarriage()
{
    char charInput;
    int capacityInput;
    char carriageTypes[] = {'p', 's', 'd'};

    printf("\nChoose type of carriage: passenger (p), sleeper (s) or diner (d): ");
    scanf(" %c", &charInput);

    int isValidCharInput = checkIfValidCharInput(charInput, carriageTypes, 3);
    if(isValidCharInput == 0)
    {
        do
        {
            printf("\nInput invalid! Try again: ");
            scanf(" %c", &charInput);
            isValidCharInput = checkIfValidCharInput(charInput, carriageTypes, 3);
        } while (isValidCharInput == 0);
    }

    printf("\nChoose capacity (20 - 130): ");
    scanf(" %d", &capacityInput);

    int isValidCapacityInput = checkIfValidNumberInput(capacityInput, 20, 130);
    if(isValidCapacityInput == 0)
    {
        do
        {
            printf("\nInput invalid! Try again: ");
            scanf(" %d", &capacityInput);
            isValidCapacityInput = checkIfValidNumberInput(capacityInput, 20, 130);
        } while (isValidCapacityInput == 0);
    }

    struct carriage newCarriage = {.type = (int)charInput, .capacity = capacityInput};

    return newCarriage;
}

int getPosition(int trainLength)
{
    int posInput;

    printf("\nChoose position for the new carriage (0-%d): ", trainLength);
    scanf(" %d", &posInput);

    int isValidPosition = checkIfValidNumberInput(posInput, 0, trainLength);
    if(isValidPosition == 0)
    {
        do
        {
            printf("\nInput invalid! Try again: ");
            scanf(" %d", &posInput);
            isValidPosition = checkIfValidNumberInput(posInput, 0, trainLength);
        } while (isValidPosition == 0);
    }

    return posInput;
}

int checkIfValidSleeper(int pos, struct train *t)
{
    if(pos >= t->length - 1)
    {
        return 0;
    }
    else
    {
        if(t->carriages[pos].type == (int)'p' && t->carriages[pos + 1].type == (int)'p')
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

int insertCarriage(struct train *t, int pos, struct carriage newCarriage)
{
    int trainLength = t->length;

    int isSleeperValid = 1;
    if(newCarriage.type == (int)'s')
    {
        isSleeperValid = checkIfValidSleeper(pos, t);
    }


    if(trainLength == 10)
    {
        return -1;
    }
    else if(pos > trainLength)
    {
        return -2;
    }
    else if(isSleeperValid == 0)
    {
        return -3;
    }
    else
    {
        if(t->carriages[pos].capacity == 0)
        {
            t->carriages[pos] = newCarriage;
        }
        else
        {
            for (int i = trainLength - 1; i >= pos; i--)
            {
                t->carriages[i + 1] = t->carriages[i];
            }

            t->carriages[pos] = newCarriage;
        }

        t->length += 1;
        return 0;
    }
}

int sumCapacity(struct train *t, enum type waggonType)
{
    int sumC = 0;

    for (int i = 0; i < t->length; i++)
    {
        if(t->carriages[i].type == waggonType)
        {
            sumC += t->carriages[i].capacity;
        }
    }

    return sumC;
}

void printTrainStats(struct train *t)
{
    printTrain(t);

    printf("\nCapacities:");

    printf("\n  Passenger: ");
    int passengerCapacity = sumCapacity(t, (int)'p');
    printf("%d", passengerCapacity);
    if(passengerCapacity < 65)
    {
        printf(" - invalid");
    }

    printf("\n  Sleeper: ");
    int sleeperCapacity = sumCapacity(t, (int)'s');
    printf("%d", sleeperCapacity);

    printf("\n  Diner: ");
    int dinerCapacity = sumCapacity(t, (int)'d');
    printf("%d", dinerCapacity);
}

int main()
{
    char input;

    struct train t = {.length = 0};

    do
    {
        input = getMenu();

        if(input == 'p')
        {
            printTrain(&t);
        }
        else if(input == 'n')
        {
            struct carriage newCarr = getCarriage();
            int posForNewCarr = getPosition(t.length);

            int insertCarrCheck = insertCarriage(&t, posForNewCarr, newCarr);

            if(insertCarrCheck == 0)
            {

            }
            else if(insertCarrCheck == -1)
            {
                printf("\nError: Train too long!");
            }
            else if(insertCarrCheck == -2)
            {
                printf("\nError: Position not possible!");
            }
            else if(insertCarrCheck == -3)
            {
                printf("\nError: Sleeper only possible directly before two passenger carriages!");
            }
        }
        else if(input == 's')
        {
            printTrainStats(&t);
        }

    } while (input != 'x');


}
