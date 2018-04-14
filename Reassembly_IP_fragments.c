#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <arpa/inet.h>
struct data * createNode();
void display();
void display1();
void reassembly();
struct data
{
    unsigned long int ip;
    int id,fo,mf;
    int length;
    int frag_duplicate;
    int dup_dif_len;
    struct data *next;
};
struct data *root=NULL;
struct data *root1=NULL;
int main(int argc, char *argv[])
{
    unsigned long int tip;
    int i,j=0,l,count=0;
    char str[50],temp[20];
    struct data *new_node, *current_node,*temp_node;
    FILE *fp=fopen(argv[1],"r");
    if(fp==NULL)
    {
        printf("\n\t File not found.......");
        printf("\n\t Press any key to exit");
        getchar();
        exit(0);
    }
    //parse data
    while  ((fgets (str, 50, fp)) != NULL||count++ )
    {
        new_node=createNode();
        
        i=0;
        l=0;
        while(str[i]!=' ')
        {
                temp[l++]=str[i++];
        }
        temp[l]='\0';
        tip=inet_addr(temp);
        new_node->ip=tip;
        while(str[i]==' ')
            i++;
        l=0;
        while(str[i]!=' ')
        {
            temp[l++]=str[i++];
        }
	temp[l]='\0';
        new_node->id=atoi(temp);
        while(str[i]==' ')
            i++;
        l=0;
        while(str[i]!=' ')
        {
            temp[l++]=str[i++];
        }
	temp[l]='\0';
        new_node->fo=atoi(temp);
        while(str[i]==' ')
            i++;
        while(str[i]!=' ')
        {
            new_node->mf=str[i++]-'0';
        }
        while(str[i]==' ')
            i++;
        l=0;
        while(str[i]!='\0')
        {   
                temp[l++]=str[i++];
        }
	temp[l]='\0';
        new_node->length=atoi(temp);

        if(new_node->fo == 0 && new_node->mf == 0 )
        {
            //printf(" IP %s  ID %d 		- full datagram\n",inet_ntoa(*(struct in_addr *)&new_node->ip), new_node->id);
			
	    //fragments inserted in linked list in sorted order
            if(root1==NULL)
            {
                root1=new_node;
            }
            else 
            {
                struct data *temp_node1 = root1, *prev_node1 = root1;
	        int f_d = 0;
                while(temp_node1 != NULL)
                {
                    if(new_node->ip < temp_node1->ip) break;
                    if(new_node->ip == temp_node1->ip && new_node->id < temp_node1->id) break;
                    if(new_node->ip == temp_node1->ip && new_node->id == temp_node1->id  && new_node->fo < temp_node1->fo) break;  
		    if(new_node->ip == temp_node1->ip && new_node->id == temp_node1->id  && new_node->fo == temp_node1->fo &&  new_node->mf == temp_node1->mf)// && new_node->length == temp_node->length) 
		    {
			temp_node1->frag_duplicate = temp_node1->frag_duplicate + 1;
			f_d = 1;
			if(new_node->length == temp_node1->length)
			{
				temp_node1->dup_dif_len = temp_node1->dup_dif_len + 1;
			}
		    	break;
		    }  
                    prev_node1 = temp_node1;
                    temp_node1 = temp_node1->next;
                }
                if(temp_node1 == root1 && !f_d)
                {
                        new_node->next = root1;
                        root1 = new_node;
                }
                else if(!f_d)
                {
                        prev_node1->next = new_node;
                        new_node->next = temp_node1;
                }

            }
        
        }
        else
        {	
	    //fragments inserted in linked list in sorted order
            if(root==NULL)
            {
                root=new_node;
            }
            else 
            {
                struct data *temp_node = root, *prev_node = root;
	        int f_d = 0;
                while(temp_node != NULL)
                {
                    if(new_node->ip < temp_node->ip) break;
                    if(new_node->ip == temp_node->ip && new_node->id < temp_node->id) break;
                    if(new_node->ip == temp_node->ip && new_node->id == temp_node->id  && new_node->fo < temp_node->fo) break;  
		    if(new_node->ip == temp_node->ip && new_node->id == temp_node->id  && new_node->fo == temp_node->fo &&  new_node->mf == temp_node->mf)// && new_node->length == temp_node->length) 
		    {
			temp_node->frag_duplicate = temp_node->frag_duplicate + 1;
			f_d = 1;
		    	break;
		    }  
                    prev_node = temp_node;
                    temp_node = temp_node->next;
                }
                if(temp_node == root && !f_d)
                {
                        new_node->next = root;
                        root = new_node;
                }
                else if(!f_d)
                {
                        prev_node->next = new_node;
                        new_node->next = temp_node;
                }

            }
        }
        j=j+1;

    }
    fclose(fp);
    //display();
	display1();
    reassembly();
    printf("\n\n");
    return 0;
}
struct data * createNode()
{
    struct data *t=(struct data *)calloc(1,sizeof(struct data));
    t->next=NULL;
    t->frag_duplicate=0;
    t->dup_dif_len=0;
    return t;
}
void display()
{
    struct data *new_node,*end_node;
    printf("\n\nThe fragmented IPs are: \n");
    new_node=root;
    while(new_node!=NULL)
    {
	printf("( %s ) ",inet_ntoa(*(struct in_addr *)&new_node->ip));   	
	printf("%ld--->",new_node->ip);
   	printf("%d--->",new_node->id);
   	printf("%d--->",new_node->fo);
   	printf("%d--->",new_node->mf);
   	printf("%d---",new_node->length);
	printf("%d\n",new_node->frag_duplicate);
	end_node=new_node;   
   	new_node=new_node->next;
    }
}
void display1()
{
    struct data *new_node,*end_node;
    printf("\n\nThe fragmented IPs are: \n");
    new_node=root1;
    while(new_node!=NULL)
    {
	if(new_node->frag_duplicate == 0)
	{
		printf(" IP %s  ID %d 		- datagram\n",inet_ntoa(*(struct in_addr *)&new_node->ip), new_node->id);
	}
	else
	{
		if(new_node->frag_duplicate != 0 && new_node->dup_dif_len != 0)
		{
			printf(" IP %s  ID %d		- duplicate datagram\n",inet_ntoa(*(struct in_addr *)&new_node->ip), new_node->id);
		}
		else
		{
			printf(" IP %s  ID %d		- duplicate datagram with different lengths\n",inet_ntoa(*(struct in_addr *)&new_node->ip), new_node->id);
		}
	}	
	/*printf("( %s ) ",inet_ntoa(*(struct in_addr *)&new_node->ip));   	
	printf("%ld--->",new_node->ip);
   	printf("%d--->",new_node->id);
   	printf("%d--->",new_node->fo);
   	printf("%d--->",new_node->mf);
   	printf("%d---",new_node->length);
	printf("%d--->",new_node->frag_duplicate);
	printf("%d\n",new_node->dup_dif_len);*/
	end_node=new_node;   
   	new_node=new_node->next;
    }
}
void reassembly()
{
    int datagram=0,flag=0,flag1=1,count=0,fs=0,ls=0;
    struct data *temp_node,*current_node;
    temp_node=current_node=root;
    while(current_node != NULL)
    {
        if((temp_node->ip == current_node->ip) && (temp_node->id == current_node->id))
        {
		if((current_node->fo == 0) && (current_node->mf == 1)) //Checking 1st fragment
                {
                        datagram=datagram + current_node->length - 20;
                        flag = 1;
			fs=1;
			if(current_node->frag_duplicate > 0)
				count++;
                }
                else if((current_node->fo > 0) && (current_node->mf == 0) && flag) //Checking last fragment
                {
			if(current_node->frag_duplicate > 0)
				count++;                        
			datagram = datagram + current_node->length - 20;
                        if((current_node->fo + current_node->length) == datagram)
                        {
				if(count > 0)
				{
					printf(" IP %s  ID %d		- reassembly successful (duplicate fragment) \n",inet_ntoa(*(struct in_addr *)&current_node->ip), current_node->id);
				}  
			        else
				{
					printf(" IP %s  ID %d		- complete fragmented datagram \n",inet_ntoa(*(struct in_addr *)&current_node->ip), current_node->id);
				}	
                        }
                        else
                        {
				if((current_node->fo + current_node->length) > datagram)
				{
					printf(" IP %s  ID %d		- reassembly unsuccessful (fraglen < totallen)\n",inet_ntoa(*(struct in_addr *)&current_node->ip), current_node->id);
				}
				else
				{
					printf(" IP %s  ID %d		- reassembly unsuccessful (fraglen > totallen)\n",inet_ntoa(*(struct in_addr *)&current_node->ip), current_node->id);
				}
                                
                        }
                        flag=0;
			ls=1;
                }
                else if((current_node->fo > 0) && (current_node->mf == 1) && flag)
                {
                        datagram = datagram + current_node->length;

                }
		temp_node=current_node;
        	current_node=current_node->next;
        }
        else
        {	if(ls == 0 || fs == 0)
		{			
			printf(" IP %s  ID %d		- incomplete fragmented datagram\n",inet_ntoa(*(struct in_addr *)&temp_node->ip), temp_node->id);	
		}
		datagram=0;
		temp_node=current_node;
		flag1=1;
		count=0;
		ls=0;
		fs=0;	
        }
        
    }
}
