#include <stdio.h>

#define DLE 16
#define STX 2
#define ETX 3

// Function to process and print the stream
void process_and_print(char arr[], int start, int end, int stuffing)
{
    for (int j = start; j < end; j++)
    {
        if (arr[j] == DLE)
        {
            printf("DLE");
            if (stuffing && arr[j + 1] == DLE)
                j++; // Skip stuffed DLE during de-stuffing
        }
        else if (arr[j] == STX)
        {
            printf("STX");
        }
        else if (arr[j] == ETX)
        {
            printf("ETX");
        }
        else
        {
            printf("%c", arr[j]);
        }
    }
}

int main()
{
    int ch;
    char arr[100] = {DLE, STX};
    int i = 2;

    printf("\nEnter the data stream (CTRL+B -> STX, CTRL+C -> ETX, CTRL+P -> DLE, ENTER to stop):\n");
    while ((ch = getchar()) != '\n')
    {
        if (ch == DLE)
            arr[i++] = DLE; // Handle byte stuffing for DLE
        arr[i++] = ch;
    }

    arr[i++] = DLE;
    arr[i++] = ETX;

    // Print the stuffed stream
    printf("\nThe stuffed stream is:\n");
    process_and_print(arr, 0, i, 0);

    // Print the de-stuffed stream
    printf("\n\nThe de-stuffed data is:\n");
    process_and_print(arr, 2, i - 2, 1);

    return 0;
}
