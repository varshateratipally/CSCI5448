//
//  edca_simulate.c
//
//
//  Created by varsha teratipally on 4/12/18.
//

// The below program is to simulate the edca protocol

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

//Global Variables
#define BACKOFF_SIZE 3
#define MAX_BACKOFF_SIZE 10
#define MAX_FRAME_SIZE 10
//Maximum number of nodes
#define NO_OF_NODES 10

//Number of nodes is 2 because for any channel there would be two end points
int num_of_nodes=2;

#define MAX_TIME 10000

// States of the users
enum States {START,BACKOFF,DIFS,TRANSMIT,SUCCESS,FAILURE};
// Channel States
// when there is no user = IDLE
// when there is a single user = BUSY
// when there are multiple users = COLLIDE
enum Channel_States {IDLE,BUSY,COLLIDE};


// Channel structure
// If the prev state is busy in the channel, then the current state will be collide
// If the prev state is collide in the channel, then current state will be idle
// if the prev state is idle in the channel, then the current state will be busy
typedef struct {    
    enum Channel_States curr_state;
    enum Channel_States prev_state;
    char users[NO_OF_NODES];
    int num_users;
    unsigned long end_of_time;
} Channel;

Channel ch;
//Number of iterations
int iteration=1;

//User nodes structure
typedef struct
{
    int channel_id;
    int txop;
    int cw_min;
    int cw_max;
    int var_ifs;
    int be; // backoff exponent
    int numofb; // max backoff values
    int cw; //contention width
    int fsize; //frame size
    enum Channel_States ch_state; // channel state
    enum States state; //user state
    int num_collisions; //number of collisions occured
    int num_of_success; // number of successful transmissions
    int num_failure; // number of failed transmissions
    unsigned long occupied_time; // time for which the channel is been occuppied
    
}Node;


typedef Node * node;

//Resetting the values
void del_node (node n)
{
    n->be=BACKOFF_SIZE;
    n->cw=0;
    n->var_ifs=0;
    n->fsize=MAX_FRAME_SIZE;
    n->state=START;
}
//Initializing the variables
void init_node(node n,int num_of_node)
{
    int i;
    
    for(i=0;i<num_of_node;i++) {
        memset(&n[i],0,sizeof(Node));
        //based on the id varying the values
        n[i].channel_id=i;
        n[i].txop=1*(i+1);
        n[i].cw_min=(n[i].txop)*2;
        n[i].cw_max=(n[i].txop)*4;
        del_node(&n[i]);
    }
    memset(&ch,0,sizeof(Channel));
}

// Displaying the output of the channel for every iteration
void display_output(node n,int num_of_node)
{
    int i;
    for(i=0;i<num_of_node;i++) {
        printf("For the Channel %d with parameters TXOP = %d, cwmax = %d ,cwmin = %d,channel access time = %-3ld, success rate = %d,collsion rate = %d,failure rate = %d,ratio = %6.2lf\n",
               n[i].channel_id,n[i].txop,n[i].cw_max,n[i].cw_min,n[i].occupied_time,n[i].num_of_success,n[i].num_collisions, n[i].num_failure,(float)n[i].occupied_time/MAX_TIME);
    }
    for(i=0;i<num_of_node;i++) {
        printf("ratio=%6.2lf\n",(float) n[i].occupied_time/n[0].occupied_time);
    }
}

// Update the channel state
int update_channel_state(node n,int num_of_node)
{
    int i;
    int j=0;
    int noofusers=0;
    for(i=0;i<num_of_node;i++) {
        if (n[i].state==TRANSMIT) {
            ch.users[noofusers++]=n[i].channel_id;
        } else if (n[i].state==SUCCESS || n[i].state==FAILURE) {
            j++;
        }
        
        
    }
    ch.prev_state=ch.curr_state;
    if (noofusers==0) ch.curr_state=IDLE;
    else if (noofusers==1) ch.curr_state=BUSY;
    else if (noofusers>1) ch.curr_state=COLLIDE;
    ch.num_users=noofusers;
    return noofusers;
}

void backoff_network(node n)
{
    int mod;
    n->state=BACKOFF;
    
    if(n->numofb==MAX_BACKOFF_SIZE) {
        n->state=FAILURE;
        n->num_failure++;
        del_node(n);
        n->numofb=0;
        return ;
    }
    mod =(int)pow(2,n->be);
    n->cw=rand()%mod;
    n->cw=(n->cw_min>n->cw?n->cw_min:n->cw);
    n->cw=(n->cw_max<n->cw?n->cw_max:n->cw);
    n->numofb++;
    n->be++;
}

int main()
{
    
    int i;
    unsigned long t=0;
    Node nodes[NO_OF_NODES];
    srand(time(0));
    
        for(;num_of_nodes<=NO_OF_NODES;num_of_nodes++) {
            for (iteration=1;iteration<=10;iteration++) {
                init_node(nodes,NO_OF_NODES);
                update_channel_state(nodes,num_of_nodes);
                
                for(t=0;t<MAX_TIME;t++)
                {
                    
                    for(i=0;i<num_of_nodes ;i++) {
                        if (nodes[i].state==SUCCESS || nodes[i].state==FAILURE)
                            continue;
                        switch (ch.curr_state) {
                                
                            case IDLE:
                                
                                if(nodes[i].var_ifs >= nodes[i].txop) {
                                    if (nodes[i].state==START) {
                                        backoff_network(&nodes[i]);
                                        
                                        
                                    }
                                }
                                if (nodes[i].state==BACKOFF && nodes[i].cw <=0) {
                                    nodes[i].cw=0;
                                    nodes[i].state=TRANSMIT;
                                    nodes[i].fsize--;
                                    nodes[i].occupied_time++;
                                    nodes[i].numofb=0;
                                    
                                } else if (nodes[i].state==BACKOFF)	{
                                    if (nodes[i].var_ifs >= nodes[i].txop ) {
                                        nodes[i].cw--;
                                        if(nodes[i].cw<0) nodes[i].cw=0;
                                        
                                        
                                    }
                                }
                                
                                nodes[i].var_ifs++;
                                
                                break;
                                
                                
                            case BUSY:
                                nodes[i].var_ifs=0;
                                if (nodes[i].state==TRANSMIT) {
                                    nodes[i].fsize--;
                                    nodes[i].occupied_time++;
                                    nodes[i].numofb=0;
                                }
                                if(nodes[i].fsize==0) {
                                    nodes[i].state=SUCCESS;
                                    nodes[i].num_of_success++;
                                    nodes[i].state=START;
                                    del_node(&nodes[i]);
                                    
                                }
                                
                                break;
                                
                            case COLLIDE:
                                nodes[i].var_ifs=0;
                                
                                if (nodes[i].state==TRANSMIT) {
                                    nodes[i].fsize--;
                                    nodes[i].occupied_time++;
                                }
                                
                                if(nodes[i].fsize==0) {
                                    del_node(&nodes[i]);
                                    backoff_network(&nodes[i]);
                                    if(nodes[i].cw==0) {
                                        nodes[i].state=START;
                                    }else
                                        nodes[i].cw--;
                                    
                                    
                                    nodes[i].num_collisions++;
                                }
                                
                                
                                
                                
                                break;
                                
                        }
                        
                        
                    }
                    
                    
                    
                    update_channel_state(nodes,num_of_nodes);
                    ch.end_of_time=t;
                }
                display_output(nodes,num_of_nodes);
            }
            
            printf("\nIteration=%d\tL=%d\tN=%d\n",10,MAX_FRAME_SIZE,num_of_nodes);
        }
        
    
    
    return 0;
}
