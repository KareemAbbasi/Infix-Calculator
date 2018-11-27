#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"

#define MAX_CHAR_IN_LINE 100

enum Type
{
    plus = -2,
    minus = -3,
    times = -4,
    divide = -5,
    power = -6,
    leftParenthesis = -7,
    rightParenthesis = -8
};

/**
 * Finds the sum of two numbers.
 * @param x num1.
 * @param y num2.
 * @return sum of x y.
 */
int plusFun(int x, int y)
{
    return ((x) + (y));
}


/**
 * x minus y.
 * @param x n1.
 * @param y n2.
 * @return x minus y.
 */
int minusFun(int x, int y)
{
    return ((x) - (y));
}


/**
 * x times y.
 * @param x n1.
 * @param y n2.
 * @return x times y.
 */
int timesFun(int x, int y)
{
    return ((x) * (y));
}


/**
 * x divided by y.
 * @param x n1.
 * @param y n2.
 * @return x divided by y.
 */
int divideFun(int x, int y)
{
    return ((x) / (y));
}


/**
 * x to the power y.
 * @param x n1.
 * @param y n2.
 * @return x to the power y.
 */
int powerFun(int x, int y)
{
    return ((int) pow((double)(x), (double)(y)));
}


/**
 * Receives a line and returns an array that contains the contents of the line separated into
 * different strings.
 * @param line The line that we want to find its contents.
 * @param amnt The number of contents in the line (passed as 0 and changed by the function to the
 * number of contents in the line).
 * @return an array of strings where each string is a different content of the original line.
 */
char** lineContents(char line[MAX_CHAR_IN_LINE], int *amnt)
{
    char **contents = NULL;
    int contentsNum = 0;
    int i = 0;
    int numLength = 0;
    char *num = NULL;

    for (i = 0; line[i] != '\0' && line[i] != '\n'; ++i)
    {
        if ((line[i] >= '0') && (line[i] <= '9'))
        {
            numLength++;
            num = (char *) realloc(num, (numLength + 1) * sizeof(char));
            num[numLength - 1] = line[i];
        }
        else
        {
            if (num != NULL)
            {
                num[numLength] = '\0';
                contentsNum++;
                contents = (char**) realloc(contents, (contentsNum + 1) * sizeof(char*));
                contents[contentsNum - 1] = num;
                numLength = 0;
                num = NULL;

            }
            contentsNum++;
            char *operator = (char*) malloc(2* sizeof(char));
            operator[0] = line[i];
            operator[1] = '\0';
            contents = (char**) realloc(contents, (contentsNum + 1) * sizeof(char*));
            contents[contentsNum - 1] = operator;
            operator = NULL;
            free(operator);
        }
    }
    if (num != NULL)
    {
        contentsNum++;
        num[numLength] = '\0';
        contents = (char**) realloc(contents, (contentsNum + 1) * sizeof(char*));
        contents[contentsNum - 1] = num;
        num = NULL;
    }
    free(num);
    *amnt = contentsNum;
    return contents;
}


/**
 * Receives a line and returns the type of the string.
 * @param str The given line.
 * @return The type value of the line. If the string is a number the function returns the value of the
 * number. If it is an operator the function returns an appropriate value from the defined enum above.
 * It returns -1 otherwise.
 */
int checkType(char *str)
{
    size_t strLength = strlen(str);

    int value = (int)strtod(str, NULL);
    if ((strLength > 1) && value != 0)
    {
        return value;
    }
    else
    {
        if ((value == 0) && (strcmp(str, "0") == 0))
        {
            return 0;
        }
        else if (strcmp(str, "(") == 0)
        {
            return leftParenthesis;
        }
        else if (strcmp(str, ")") == 0)
        {
            return rightParenthesis;
        }
        else if (strcmp(str, "+") == 0)
        {
            return plus;
        }
        else if (strcmp(str, "-") == 0)
        {
            return minus;
        }
        else if (strcmp(str, "*") == 0)
        {
            return times;
        }
        else if (strcmp(str, "/") == 0)
        {
            return divide;
        }
        else if (strcmp(str, "^") == 0)
        {
            return power;
        }
    }
    if (value > 0)
    {
        return value;
    }
    return -1;
}


/**
 * Receives a line and finds the Infix representation of the line.
 * @param line The array that contains the separated contents of the line.
 * @param numOfElements The number of contents in the given line.
 * @return Infix representation of the given line.
 */
char* findInfix(char **line, int numOfElements)
{
    char *finalString = (char*)malloc(sizeof(char));
    int lineSize = 0;

    for (int i = 0; i < numOfElements; ++i)
    {
        int lineType = checkType(line[i]);
        if (lineType == -1)
        {
            return NULL;
        }
        else if (lineType >= 0)
        {
            finalString[lineSize] = '\0';
            int numberSize = (int)strlen(line[i]);
            lineSize += (2 + numberSize);
            finalString = (char*)realloc(finalString, (lineSize + 1) * sizeof(char));
            strcat(finalString, " ");
            strcat(finalString, line[i]);
            strcat(finalString, " ");
        }
        else
        {
            finalString[lineSize] = '\0';
            lineSize += 1;
            finalString = (char*)realloc(finalString, (lineSize + 1) * sizeof(char));
            strcat(finalString, line[i]);
        }
    }

    return finalString;
}


/**
 * Finds the Postfix representation of a given line in Infix form.
 * @param line The array that contains the separated parts of the infix line.
 * @param numOfElements The number of elements of the line.
 * @return A string that is the postfix representation of a line.
 */
char* infixToPostfix(char **line, int numOfElements)
{
    char *finalString = (char*)malloc(sizeof(char));
    Stack *stack = stackAlloc(sizeof(char*));
    int lineSize = 0;


    for (int i = 0; i < numOfElements; ++i)
    {
        int lineType = checkType(line[i]);
        if (lineType == -1)
        {
            return NULL;
        }
        else if (lineType >= 0) // if operand is found
        {
            finalString[lineSize] = '\0';
            int numberSize = (int)strlen(line[i]);
            lineSize += (2 + numberSize);
            finalString = (char*)realloc(finalString, (lineSize + 1) * sizeof(char));
            strcat(finalString, " ");
            strcat(finalString, line[i]);
            strcat(finalString, " ");
        }
        else if (lineType == leftParenthesis) // left parenthesis is found
        {
            push(stack, line[i]);
        }
        else if (lineType == rightParenthesis) // if right parenthesis is found
        {
            while ((isEmptyStack(stack) == 0) && (checkType(stack->_top->_data) != leftParenthesis))
            {

                char headData;
                pop(stack, &headData);
                lineSize += 1;
                finalString = (char*)realloc(finalString, (lineSize + 1) * sizeof(char));
                finalString[lineSize] = '\0';
                strcat(finalString, &headData);
            }
            char *headData;
            pop(stack, &headData);

        }
        else if (lineType < -1)
        {
            if (isEmptyStack(stack) || (checkType(stack->_top->_data) == leftParenthesis))
            {
                push(stack, line[i]);
            }
            else
            {
                while ((isEmptyStack(stack) == 0) &&
                       (checkType(stack->_top->_data) != leftParenthesis) &&
                       abs(lineType) <= abs(checkType(stack->_top->_data)))
                {

                    char headData;
                    pop(stack, &headData);
                    lineSize += 1;
                    finalString = (char*)realloc(finalString, (lineSize + 1) * sizeof(char));
                    finalString[lineSize] = '\0';
                    strcat(finalString, &headData);
                }
                push(stack, line[i]);
            }
        }
    }

    while(isEmptyStack(stack) == 0)
    {
        char headData;
        pop(stack, &headData);
        lineSize += 1;

        finalString = (char*)realloc(finalString, (lineSize + 1) * sizeof(char));
        finalString[lineSize] = '\0';
        strcat(finalString, &headData);
    }
    freeStack(&stack);
    return finalString;
}


/**
 * Receives a type of operator and return a pointer to the function that performs the operators function.
 * @param type the type of the operator.
 */
int (*operatorPtr(int type))(int, int)
{
    if (type == plus)
    {
        return &plusFun;
    }
    else if (type == minus)
    {
        return &minusFun;
    }
    else if (type == times)
    {
        return &timesFun;
    }
    else if (type == divide)
    {
        return &divideFun;
    }
    else if (type == power)
    {
        return &powerFun;
    }
    return NULL;
}


/**
 * Receives a line in postfix representation and find the value of the operations in the line.
 * @param postfixLine The line in postfix representation.
 * @return The final value after all the operations in the line are performed.
 */
int postfixToValue(char *postfixLine)
{
    int contentsNum = 0;
    char **line = lineContents(postfixLine, &contentsNum);
    Stack *stack = stackAlloc(sizeof(int));

    for (int i = 0; i < contentsNum; ++i)
    {
        int contentType = checkType(line[i]);
        if (contentType == -1)
        {
            continue;
        }
        else if (contentType >= 0)
        {
            push(stack, &contentType);
        }
        else if (contentType < -1)
        {
            int valA, valB;
            pop(stack, &valA);
            pop(stack, &valB);

            int (*ptr2MathFunction)(int, int) = NULL;
            ptr2MathFunction = operatorPtr(contentType);
            int ans = (*ptr2MathFunction)(valB, valA);
            push(stack, &ans);
        }
    }

    int finalAns;
    pop(stack, &finalAns);
    freeStack(&stack);

    for (int i = 0; i < contentsNum; ++ i)
    {
        free(line[i]);
    }
    free(line);
    return finalAns;
}


/**
 * Reads a given file and finds the Infix and Postfix representations of the line, and the value of
 * the operations in the line.
 * @param fileName The path to the file to be read.
 * @return -1 if no file was found. 0 if everything ok.
 */
int readFile(char* fileName)
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        return -1;
    }

    char currLine[MAX_CHAR_IN_LINE];

    int lineNum = 0;
    while(fgets(currLine, MAX_CHAR_IN_LINE, file) != NULL)
    {
        lineNum++;
        int numLineContents = 0;
        char **lineContentsArr = lineContents(currLine, &numLineContents);
        if (numLineContents == 0)
        {
            continue;
        }
        char *infix = findInfix(lineContentsArr, numLineContents);
        char *postfixString = infixToPostfix(lineContentsArr, numLineContents);

        if ((infix == NULL) || (postfixString == NULL) )
        {
            fprintf(stderr, "Line %d is not a valid line.\n", lineNum);
            return -1;
        }

        int lineAnswer = postfixToValue(postfixString);

        printf("Infix: %s\n", infix);
        printf("Postfix: %s\n", postfixString);
        printf("The value is %d\n", lineAnswer);

        for (int i = 0; i < numLineContents; ++i)
        {
            free(lineContentsArr[i]);
        }
        free(lineContentsArr);

        free(infix);
        free(postfixString);

    }
    fclose(file);
    return 0;
}


/**
 * The main function of the program.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char **argv)
{
    if (argc > 1)
    {
        char* fileName = argv[1];
        readFile(fileName);
    }
    else
    {
        fprintf(stderr, "Couldn't find file path\n");
    }

}
