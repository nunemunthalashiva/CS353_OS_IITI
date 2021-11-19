#include <stdio.h>
#define pages 5
int main()
{
      int reference_string[10], num_page_faults = 0, s, frames;
      printf("\nEnter reference string values:\n");
      for(int m = 0; m < pages; m++)
      {
            printf("Page value of %d : ", m + 1);
            scanf("%d", &reference_string[m]);
      }
      printf("\nPlease enter number of frames: ");
      scanf("%d", &frames);
      
      int temp[frames];
      for(int i = 0; i < frames; i++)
      {
            temp[i] = -1;
      }
      for(int i = 0; i < pages; i++)
      {
            s = 0;
            for(int j = 0; j < frames; j++)
            {
                  if(reference_string[i] == temp[j])
                  {
                        s++;
                        num_page_faults--;
                  }
            }     
            num_page_faults++;
            if((num_page_faults <= frames) && (s == 0))
            {
                  temp[i] = reference_string[i];
            }   
            else if(s == 0)
            {
                  temp[(num_page_faults - 1) % frames] = reference_string[i];
            }
           
      } 
      printf("\nNumber of page faults are : %d\n", num_page_faults);
      return 0;
}
