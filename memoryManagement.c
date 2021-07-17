#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

void fifo_policy(int *pages, int page_size, int *frame, int frame_size)
{
    int counter =0;
    int i;  //main loop counter
    int j = 0; // counter to print content of frames
    int z = 0; // holds the index of the next value to be replaced
    int k; // second loop counter

    printf("Page\tContent of Frames\n");
    printf("----\t-----------------\n");


    for(i = 0; i < page_size; i++)
    {
        int flag = 0;
        /*flag to check if element already exists in
          my frames if so i do nothing */
        for(k = 0; k < j; k++)
            {
                if(pages[i] == frame[k])
                    flag = 1;
            }

        printf("%.2d ", pages[i]);
        //frame is initialized by -1 (since if input = -1 we terminate)
        //so if frame[j] = -1 we still didn't fill the pages
        if(frame[j] == -1)
        {
            if(flag == 0)
            {
                frame[j] = pages[i];
                j++;
            }
        }
        // if my frame array is full here i use the z counter to
        // keep tracking of which element will be removed
        else if(j == frame_size)
        {
            if(flag == 0)
            {
                // following the fifo policy we start at the first element then incerement
                // if we reach the end we restart at the first
                frame[z] = pages[i];
                printf("F ");
                counter++;
                z++;
                if(z == frame_size)
                {
                    z = 0;
                }
            }
        }
        printf("\t");
        for(k = 0; k < j; k++)
        {
            printf("%.2d ", frame[k]);
        }
        printf("\n");
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n", counter);
}

void lru_policy(int *pages, int page_size, int *frame, int frame_size)
{
    int counter =0;
    int clock[frame_size]; // array to hold the time at which each element was used
    int i;  //main loop counter
    int j = 0; // counter to print content of frames
    int z = 0; // holds the index of the next value to be replaced
    int k; // second loop counter

    printf("Page\tContent of Frames\n");
    printf("----\t-----------------\n");

    for(i = 0; i < page_size; i++)
    {
        int flag = 0;
        /*flag to check if element already exists in
          my frames if so i do nothing */
        for(k = 0; k < j; k++)
            {
                if(pages[i] == frame[k])
                {
                    flag = 1;
                    clock[k] = i;
                }
            }

        printf("%.2d ", pages[i]);
        //frame is initialized by -1 (since if input = -1 we terminate)
        //so if frame[j] = -1 we still didn't fill the pages
        if(frame[j] == -1)
        {
            if(flag == 0)
            {
                frame[j] = pages[i];
                clock[j] = i;
                j++;
            }
        }
        // if my frame array is full here i use the z counter to
        // keep tracking of which element will be removed
        else if(j == frame_size)
        {
            if(flag == 0)
            {   //here clocks holds the time for each element in array frame
                //so we get the minimum time and remove it
                int minimum = INT_MAX;
                int minimum_index = 0;
                for(k = 0; k < j; k++)
                {
                    if(clock[k] < minimum)
                    {
                        minimum = clock[k];
                        minimum_index = k;
                    }
                }
                z = minimum_index;
                frame[z] = pages[i];
                printf("F ");
                clock[z] = i;
                counter++;
            }
        }

        printf("\t");
        for(k = 0; k < j; k++)
        {
            printf("%.2d ", frame[k]);
        }
        printf("\n");
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n", counter);
}

void clock_policy(int *pages, int page_size, int *frame, int frame_size)
{
    int counter =0;
    int i;  //main loop counter
    int j = 0; // counter to print content of frames
    int z = 0; // holds the index of the next value to be replaced
    int k; // second loop counter

    printf("Page\tContent of Frames\n");
    printf("----\t-----------------\n");

    for(i = 0; i < page_size; i++)
    {
        int flag = 0;
        /*flag to check if element already exists in
          my frames if so i do nothing */
        for(k = 0; k < j; k++)
            {
                if(pages[i] == frame[k])
                    flag = 1;
            }

        printf("%.2d ", pages[i]);
        //frame is initialized by -1 (since if input = -1 we terminate)
        //so if frame[j] = -1 we still didn't fill the pages
        if(frame[j] == -1)
        {
            if(flag == 0)
            {
                frame[j] = pages[i];
                j++;
            }
        }
        // if my frame array is full here i use the z counter to
        // keep tracking of which element will be removed
        else if(j == frame_size)
        {
            if(flag == 0)
            {
                frame[z] = pages[i];
                printf("F ");
            }
        }

        printf("\t");
        for(k = 0; k < j; k++)
        {
            printf("%.2d ", frame[k]);
        }
        printf("\n");
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n", counter);
}

void optimal_policy(int *pages, int page_size, int *frame, int frame_size)
{
    int counter =0;
    int next[frame_size]; //array holds the index to the next occurency of every frame entry
    int i;  //main loop counter
    int j = 0; // counter to print content of frames
    int z = 0; // holds the index of the next value to be replaced
    int k; // second loop counter

    printf("Page\tContent of Frames\n");
    printf("----\t-----------------\n");

    for(i = 0; i < page_size; i++)
    {
        int flag = 0;
        /*flag to check if element already exists in
          my frames if so i do nothing */
        for(k = 0; k < j; k++)
            {
                if(pages[i] == frame[k])
                    flag = 1;
            }

        printf("%.2d ", pages[i]);
        //frame is initialized by -1 (since if input = -1 we terminate)
        //so if frame[j] = -1 we still didn't fill the pages
        if(frame[j] == -1)
        {
            if(flag == 0)
            {
                frame[j] = pages[i];
                j++;
            }
        }
        // if my frame array is full here i use the z counter to
        // keep tracking of which element will be removed
        else if(j == frame_size)
        {
            if(flag == 0)
            {
                int temp = i;
                for(k = 0; k < j; k++)
                {
                    for(temp = i; temp < page_size; temp++)
                    {
                        if(pages[temp] == frame[k])
                        {
                            next[k] = temp;
                        }
                    }
                }
                int maximum = 0;
                int maximum_index = 0;

                for(k = 0; k < j; k++)
                {
                    if(next[k] > maximum)
                    {
                        maximum = next[k];
                        maximum_index = k;
                    }
                }
                z = maximum_index;
                frame[z] = pages[i];
                printf("F ");
                counter++;
            }
        }

        printf("\t");
        for(k = 0; k < j; k++)
        {
            printf("%.2d ", frame[k]);
        }
        printf("\n");
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n", counter);
}

int main()
{
    int frame_size;
    int page_size=0;
    int x;
    int i;
    int *pages = malloc(sizeof(int));
    char policy[10];

    scanf("%d", &frame_size);
    int frame[frame_size];
    for(i = 0; i < frame_size; i++)
    {
        frame[i] = -1;
    }
    scanf("%s", policy);

    while(1)
    {
        scanf("%d", &x);
        if(x == -1)
            break;
        pages[page_size] = x;
        page_size++;
        pages = realloc(pages, sizeof(int) * (page_size + 1));
    }

    if(strcmp(policy, "FIFO") == 0)
    {
        printf("Replacement Policy = FIFO\n");
        printf("-------------------------------------\n");
        fifo_policy(pages, page_size, frame, frame_size);
    }
    else if(strcmp(policy, "LRU") == 0)
    {
        printf("Replacement Policy = LRU\n");
        printf("-------------------------------------\n");
        lru_policy(pages, page_size, frame, frame_size);
    }
    else if(strcmp(policy, "CLOCK") == 0)
    {
        printf("Replacement Policy = CLOCK\n");
        printf("-------------------------------------\n");
        clock_policy(pages, page_size, frame, frame_size);
    }
    else if(strcmp(policy, "OPTIMAL") == 0)
    {
        printf("Replacement Policy = OPTIMAL\n");
        printf("-------------------------------------\n");
        optimal_policy(pages, page_size, frame, frame_size);
    }
    else
    {
        printf("no such policy\n");
    }
    return 0;
}
