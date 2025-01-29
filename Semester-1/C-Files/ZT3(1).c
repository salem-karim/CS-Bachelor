#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// to whomever reads this: this is the result of over caffeinated after-work
// programming

enum node_type { number_type = 1, operator_type, parenthesis_type };

struct node {
  char operator;
  int number;
  enum node_type type;
  struct node *next;
};

struct node *inputToNode(const char *input);

struct node *createParenthesisNode(char operator);
struct node *createOperatorNode(char operator);
struct node *createNumberNode(int number);

// add at last position to Linked list
struct node *addLast(struct node *head, struct node *newNode);

// search functions

// finds element before the current node
struct node *findPrevious(struct node *head, struct node *node);
// finds first point operator in list
struct node *findFirstPointOperator(struct node *startNode);
// finds first dash operator in list
struct node *findFirstDashOperator(struct node *startNode);
// finds last '(' Parenthesis
struct node *findLastParenthesisOpen(struct node *head);

// calculator functions

// resolves calculations within Parentheses and eliminates them from list once
// done
struct node *resolveParenthesis(struct node *head);
// function used to remove Parentheses from list
struct node *eliminateParent(struct node *head, struct node *pNode);
// returns total amount of Parentheses in list
int ParentExists(struct node *startNode);
// finds highest order of operation and sends it into the calculation, then
// adjusts list to reflect results
void calculate(struct node *head);
// actual calculations are done here, returns result of
int Calc(struct node *head, struct node *op);

// node functionalities

// returns 1 if a operator_type is found
int isCalcOperator(struct node *node);
// returns 1 if list is valid for evaluation
int verifyInput(struct node *head);
// frees all memory within linked list
void freeAll(struct node *head);
// prints all Nodes in order
void printNodes(struct node *head);

int main() {
  char *input = (char *)malloc(32 * sizeof(char));
  int loops = 0;
  struct node *head;

  while (1) {
    printf("\nInput: ");
    scanf("%[^\n]%*c", input);

    if (*input == '=') {
      break;
    }

    // terrible solution to add the first Node element, loops is basically a
    // boolean
    if (!loops) {
      head = inputToNode(input);
      ++loops;
      printf("\nTerm: ");
      printNodes(head);
      continue;
    }

    // turns input into node via function, then adds it at the end of the linked
    // list
    head = addLast(head, inputToNode(input));
    printf("\nTerm: ");
    printNodes(head);
  }
  if (verifyInput(head)) {
    // function in while checks for parentheses, once there are none left, while
    // loop is exited
    while (ParentExists(head)) {
      head = resolveParenthesis(head);
    }

    // the linked list shrinks thanks to the calculate function, once it has
    // fully finished its calculations, the result is printed one last time and
    // the loop is exited
    while (head->next != NULL) {
      calculate(head);
      printf("\nResulting term: ");
      printNodes(head);
    }
  } else {
    printf("\nCould not verify list to correct calcuation");
  }

  // free all mallocs
  freeAll(head);
  free(input);
  exit(0);
}

// node Creations, should be self explanatory, malloc to reserve memory, then
// return pointer to the newly created Node

struct node *createParenthesisNode(char operator) {
  struct node *newNode = (struct node *)malloc(sizeof(struct node));

  newNode->operator= operator;
  newNode->type = parenthesis_type;
  newNode->next = NULL;

  return newNode;
}

struct node *createOperatorNode(char operator) {
  struct node *newNode = (struct node *)malloc(sizeof(struct node));

  newNode->operator= operator;
  newNode->type = operator_type;
  newNode->next = NULL;

  return newNode;
}

struct node *createNumberNode(int number) {
  struct node *newNode = (struct node *)malloc(sizeof(struct node));

  newNode->number = number;
  newNode->type = number_type;
  newNode->next = NULL;

  return newNode;
}

struct node *inputToNode(const char *input) {
  int number = atoi(input);
  if (number != 0) {
    return createNumberNode(number);
  }
  if (input[0] == '0') {
    return createNumberNode(0);
  }
  if (strcmp(input, "(") == 0 || strcmp(input, ")") == 0) {
    return createParenthesisNode(input[0]);
  }

  if (strcmp(input, "+") == 0 || strcmp(input, "-") == 0 ||
      strcmp(input, "*") == 0 || strcmp(input, "/") == 0) {
    return createOperatorNode(input[0]);
  }
  return NULL;
}

// goes from head to the end of the linked list, where the new Node is then
// added, returns head with finished modifications
struct node *addLast(struct node *head, struct node *newNode) {
  struct node *temp = head;
  while (temp->next != NULL) {
    temp = temp->next;
  }
  temp->next = newNode;
  return head;
}

// compares addresses saved in pointer to find the previous element in the
// linked list
struct node *findPrevious(struct node *head, struct node *node) {
  struct node *temp = head;
  while (temp->next != node) {
    temp = temp->next;
  }
  return temp;
}

// search for a point operator from a specified node, distinction needed due to
// calculations within Parentheses
struct node *findFirstPointOperator(struct node *startNode) {
  struct node *temp = startNode;
  // while loop goes to NULL then checks whether it is the first closing
  // Parenthesis it can find
  while (temp->next != NULL) {
    if (temp->type == parenthesis_type && temp->operator== ')') {
      break;
    }

    // conditions check for enum operator type and only if that condition is
    // fulfilled the operator within the node is checked for its identity
    if (temp->next->type == operator_type &&
        (temp->next->operator== '*' || temp->next->operator== '/')) {
      // returns a pointer to the element within the linked list that fulfils
      // the functions condition (first point operator)
      return temp->next;
    }
    temp = temp->next;
  }
  // if no point Operator is found, returns the starting point
  return startNode;
}

// works exactly the same as findFirstPointOperator, except it searches for '+'
// and '-'
struct node *findFirstDashOperator(struct node *startNode) {
  struct node *temp = startNode;
  // while loop goes to NULL or the first closing Parenthesis it can find
  while (temp->next != NULL) {
    if (temp->type == parenthesis_type && temp->operator== ')') {
      break;
    }
    if (temp->next->type == operator_type &&
        (temp->next->operator== '+' || temp->next->operator== '-')) {
      return temp->next;
    }
    temp = temp->next;
  }
  return startNode;
}

struct node *findLastParenthesisOpen(struct node *head) {
  struct node *temp = head;
  // open parenthesis count
  int o_p_count = ParentExists(head);

  // count how many opening parenthesis are in list, old code, replaced by
  // ParentExists function
  /*while(temp != NULL){
      if(temp->type == parenthesis_type && temp->operator == '(')
          ++o_p_count;

      temp = temp->next;
  }

  temp = head;*/
  // by decreasing the count for every parenthesis found, the node which lowers
  // the count to 0 is the last opening parenthesis, if there are none...
  //...head will always be the return
  while (temp != NULL) {
    if (temp->type == parenthesis_type && temp->operator== '(')
      --o_p_count;

    if (!o_p_count) {
      return temp;
    }

    temp = temp->next;
  }

  // error handling for unexpected results
  printf("\n\n\nERROR: UNEXPECTEDLY REACHED END OF "
         "'findLastParenthesisOpen'\n\n\n");
  return temp;
}

struct node *resolveParenthesis(struct node *head) {
  struct node *startNode = findLastParenthesisOpen(head);

  // while loop continues to calculate until there is only one number between
  // the parenthesis
  while (startNode->next->next->operator!= ')') {
    // call calculate to resolve the Parentheses
    calculate(startNode);
    printf("\nResulting term: ");
    printNodes(head);
  }
  // eliminate the solved Parentheses from the linked list
  return eliminateParent(head, startNode);
}

// returns the head in case of a change to the list, adjusts the list by
// removing the Parentheses around the result
struct node *eliminateParent(struct node *head, struct node *pNode) {
  struct node *tempParentOpen = pNode;
  struct node *tempParentClose = pNode->next->next;

  // if the Parentheses is in First position, properly deal with the removal of
  // the head of the linked list
  if (tempParentOpen == head) {
    head = head->next;
    free(tempParentOpen);
    head->next = tempParentClose->next;
    free(tempParentClose);
    return head;
  } else {
    struct node *previous = findPrevious(head, tempParentOpen);
    // Previous gets number between brackets as next
    previous->next = tempParentOpen->next;
    // Number between brackets gets whatever is after the enclosing bracket as
    // next
    previous->next->next = tempParentClose->next;
    free(tempParentOpen);
    free(tempParentClose);
    return head;
  }
}

// for loop purposes, counts the total amount of opening parentheses in linked
// list
int ParentExists(struct node *startNode) {
  struct node *temp = startNode;
  int parentCount = 0;
  while (temp != NULL) {
    if (temp->type == parenthesis_type && temp->operator== '(')
      ++parentCount;

    temp = temp->next;
  }
  return parentCount;
}

// determines where, how and what to calculate and then sends the necessary
// information into the Calc function. Once the result returns, makes the
// necessary modifications and removals...
//...to reflect the changes within the query in the linked list
void calculate(struct node *startNode) {
  struct node *temp = startNode;
  struct node *previous;
  struct node *nextNumber;
  int newNumber;

  // only enters the if-clause if a Point Op is found
  if (findFirstPointOperator(temp) != temp) {
    // Calc returns the result of the Op
    newNumber = Calc(startNode, findFirstPointOperator(temp));
    // set the previous Pointer to the node which is about to be modified
    previous = findPrevious(startNode, findFirstPointOperator(temp));
  }
  // same but in Dash Operator
  else if (findFirstDashOperator(temp) != temp) {
    newNumber = Calc(startNode, findFirstDashOperator(temp));
    previous = findPrevious(startNode, findFirstDashOperator(temp));
  }
  // change number in first part of operation
  previous->number = newNumber;
  // change temp to be the operator
  temp = previous->next;
  // write the 2nd number into the next pointer
  nextNumber = temp->next;
  // change previous' next node to the one following the last part of the
  // operation
  previous->next = nextNumber->next;
  // free memory from temp->next and temp;
  free(nextNumber);
  free(temp);
}

// The actual calculator
int Calc(struct node *startNode, struct node *op) {
  int result;
  struct node *previous = findPrevious(startNode, op);
  struct node *next = op->next;

  // switch to determine which operation is needed
  switch (op->operator) {
  case ('*'):
    result = previous->number * next->number;
    break;
  case ('/'):
    // If the divisor is 0, divide by 1 as per instructions
    if (!(next->number)) {
      result = previous->number / 1;
    } else {
      result = previous->number / next->number;
    }
    break;
  case ('+'):
    result = previous->number + next->number;
    break;
  case ('-'):
    result = previous->number - next->number;
    break;
  }

  return result;
}

// not necessary for test
int isCalcOperator(struct node *node) {
  if (node->type != operator_type)
    return 0;

  switch (node->operator) {
  case ('('):
    return 0;
  case (')'):
    return 0;
  default:
    return 1;
  }

  // unexpected end of isCalcOperator
  return -1;
}

// not necessary for test
int verifyInput(struct node *head) {
  struct node *temp = head;
  // verify whether the head is a valid type either a number or '('
  if ((temp->type == operator_type || temp->type == parenthesis_type) &&
      (temp->operator== ')' || isCalcOperator(temp))) {
    return 0;
  }

  // verify number of parentheses in list by first counting number of opening
  // Parentheses
  int Oparent = ParentExists(head);
  // and then counting them against the amount of closing parentheses found
  int Cparent = 0;
  while (temp != NULL) {
    if (temp->type == parenthesis_type && temp->operator== ')')
      ++Cparent;

    temp = temp->next;
  }
  // if the amount found isn't equal, return invalid
  if (Oparent != Cparent) {
    return 0;
  }

  temp = head;
  while (temp->next != NULL) {
    if (temp->type == parenthesis_type && temp->operator== '(') {
      // checks if the node following an opening parenthesis is another opening
      // parenthesis, then moves the pointer until it points to non-parenthesis
      while (temp->next->type == parenthesis_type &&
             temp->next->operator== '(') {
        temp = temp->next;
      }
      // return 0 if next type is not a number, as the loop ensures it can't be
      // an opening parenthesis and any other option is invalid
      if (temp->next->type != number_type) {
        return 0;
      }
      // if next is a number_type, variable is set to next and loop is continued
      temp = temp->next;
      continue;
    } else if (temp->type == number_type) {
      // if the node following the number node is neither a calc operator nor a
      // closing operator, return 0, numbers and closing parenthesis are allowed
      // to be in last position
      if (temp->next != NULL && (!(isCalcOperator(temp->next)) &&
                                 !(temp->next->type == parenthesis_type &&
                                   temp->next->operator== ')'))) {
        return 0;
      }
      temp = temp->next;
      continue;
    } else if (isCalcOperator(temp)) {
      // if the node following an Operator is not a Number or a closing
      // Parenthesis, return 0
      if (temp->next->type != number_type &&
          (temp->next->type == parenthesis_type &&
           temp->next->operator== ')')) {
        return 0;
      }

      temp = temp->next;
      continue;
    }
    // as closing and opening parentheses behave differently in context, they
    // need their own verification
    else if (temp->type == parenthesis_type && temp->operator== ')') {
      // if the node following a closing parenthesis is neither NULL (ending
      // node) nor an operator, return 0;
      if (temp->next != NULL && !(isCalcOperator(temp->next)) &&
          (temp->next->type == parenthesis_type &&
           temp->next->operator!= ')')) {
        return 0;
      }

      temp = temp->next;
      continue;
    }
  }

  // if it reaches end of loop it should have been successfully verified
  return 1;
}

void freeAll(struct node *head) {
  struct node *temp;
  while (head != NULL) {
    temp = head;
    head = head->next;
    free(temp);
  }
}

void printNodes(struct node *head) {
  struct node *temp = head;
  while (temp != NULL) {
    // switch case to check the enums and print accordingly;
    switch (temp->type) {
    case (number_type):
      printf("%d", temp->number);
      break;
    case (parenthesis_type):
      printf("%c", temp->operator);
      break;
    case (operator_type):
      printf("%c", temp->operator);
      break;
    }
    temp = temp->next;
  }
}
