 #include<stdio.h>
 #define n 5 // number of pages 5
int main()
{
	int q[20],p[50],c=0,c1,k=0,t,b[20],c2[20];
	printf("Enter the reference string values : \n");
	for(int i=0;i<n;i++)
	{
	    printf("Page value of %d :\n", i + 1);
            scanf("%d",&p[i]);
        }
	int frames;
	printf("\nPlease enter number of frames:\t");
            scanf("%d", &frames);
      
	q[k]=p[k];
	c++;
	k++;
	for(int i=1;i<n;i++)
            {
                        c1=0;
                        for(int j=0;j<frames;j++)
                        {
                                    if(p[i]!=q[j])
                                    c1++;
                        }
                        if(c1==frames)
                        {
                                    c++;
                                    if(k<frames)
                                    {
                                                q[k]=p[i];
                                                k++;
                                    }
                                    else
                                    {
                                                for(int r=0;r<frames;r++)
                                                {
                                                            c2[r]=0;
                                                            for(int j=i-1;j<n;j--)
                                                            {
                                                            if(q[r]!=p[j])
                                                            c2[r]++;
                                                            else
                                                            break;
                                                }
                                    }
                                    for(int r=0;r<frames;r++)
                                     b[r]=c2[r];
                                    for(int r=0;r<frames;r++)
                                    {
                                                for(int j=r;j<frames;j++)
                                                {
                                                            if(b[r]<b[j])
                                                            {
                                                                        t=b[r];
                                                                        b[r]=b[j];
                                                                        b[j]=t;
                                                            }
                                                }
                                    }
                                    for(int r=0;r<frames;r++)
                                    {
                                                if(c2[r]==b[0])
                                                q[r]=p[i];
                                               
                                    }
                                    printf("\n");
                        }
            }
}
printf("\nnumber of page faults : %d\n",c);
return 0;
}
