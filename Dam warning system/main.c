//C program to create an early warning system

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h> 
#include <pthread.h> 
#define g 9.8

pthread_mutex_t loc;
//Creating a structure variable to store several dam details.

typedef struct flood_system
{
    char name[30];
    double threshold;
    double lat_area;
    double flow_in;
    double width;
    double water_level;
    double init_height;
}m;

//Functions are declared

double square_root(double number);
int capacity(m dam);
void protocol_1();
void protocol_2();
double calculate(m dam, double shut_height);
int decision(m dam, double flow_out);
void cond(int check, int flag, int y, int i);
void file_print_struct(m dam, int n);
void write_to_file(char dam_info[][10], int i);
void* create_sample(void* args);
void split_string(char str[100], int ent);
double cube_root(double number);


//Creating a function for the protocols to be followed during a signal red emergency

void protocol_1()
{
   printf("\n");
   printf("\n\t\t\tPlease follow the protocols given below immediately:");
   printf("\n");
   printf("\n1. Rise the dam shutters uniformly to allow the free outflow to increase outward velocity of dam ");
   printf("\n2. Evacuate the people who are near the dam for at least a radius of 40 km for "
	      "rehabilitation purposes from potential inundation areas.");
   printf("\n3. Immediately open the check dams further ahead to allow the free outward flow of water from the dam ");
   printf("\n4. Make sure there is no water overflowing through the dam crests or "
	      "large overflow through the channels (piping) in case of embankment erosion");
   printf("\n5. Kindly assume the dam failure is in progress and take the above the steps necessary");
}

//Creating a function for the protocols to be followed during a signal orange emergency

void protocol_2()
{
	printf("\n");
	printf("\n\t\t\tPlease follow the protocol given below immediately:");
	printf("\n");
	printf("\n1. Rise the shutters slowly and fairly allow the outward flow of the water from the dam");
	printf("\n2. Make sure that the adverse meteorological conditions affect the dam capacity "
	       "and the outward flow of the water from the dam further or not");
	printf("\n3. Open the check dams slowly and fairly to allow the free outward flow of the water from the dam");
	printf("\n4. Make sure there is no transverse cracking of the embankment");
	printf("\n5. Authorities responsible for rescue and relief gear for evacuation of people and property from inundation areas "
	       "immediately");
}

//Creating a function to find the square root of a number
double square_root(double number)
{
    double temp, sqt;

    // store the half of the given number e.g from 256 => 128
    sqt = number / 2;
    temp = 0.00;


    // Iterate until sqrt is different of temp, that is updated on the loop
    while(sqt != temp){
        // initially 0, is updated with the initial value of 128
        // (on second iteration = 65)
        // and so on
        temp = sqt;
	
	// Then, replace values (256 / 2 * 128) / 2 = 65
	//(on second iteration 34.46923076923077)
	//and so on
	sqt = (number /temp + temp)/2;      
    }
    return sqt;
}
//Function to check whether safe from flooding

double cube_root(double num) 
{ 
    double ans; 
    ans = pow(num, 1.0/3.0);
    ans++; 
    return ans; 
}

void cond(int check, int flag, int y, int i)
{
    int chfl = check + flag;
    if((chfl) == 2)
    {
            FILE *file;
            file = fopen("records.txt", "a");

            printf("\nAt time t= %d seconds  \nSignal = RED", i);
            printf("\n\nAlert!!The dam and its surrounding areas are on the verge of flooding."
                    "\nSo kindly evacuate the people from the surrounding areas and move them them to higher grounds until futher adviced.\n");
            protocol_1();

            fprintf(file, "\nAt time t = %d seconds \nSignal = RED", i);
            fprintf(file, "\nAlert!!The dam and its surrounding areas are on the verge of flooding."
                    "\nSo kindly evacuate the people from the surrounding areas and move them them to higher grounds until futher adviced.\n");

            fclose(file);
    }

    else if((chfl)==1)
    {
        FILE *file;
        file = fopen("records.txt", "a");

        printf("\nAt time t= %d seconds \nSignal = ORANGE", i);
        printf("\n\nThe dam and its surrounding areas are at high risk of flooding."
                "\nSo kindly take the necessary steps required\n");
        protocol_2();

        fprintf(file, "\nAt time t = %d seconds \nSignal = ORANGE", i);
        fprintf(file, "\n\nThe dam and its surrounding areas are at high risk of flooding."
                "\nSo kindly take the necessary steps required\n");

        fclose(file);
    }

    else if((chfl)==0)
    {
        FILE *file;
        file = fopen("records.txt", "a");

        printf("\nAt time t = %d seconds \nSignal = GREEN", i);
        printf("\n\nThe dam and its surrounding area is safe from flooding now and no need to evacuate the people "
                "from neighbouring areas."
                "\nNo need to panic.\n");

        fprintf(file, "\nAt time t = %d seconds \nSignal = GREEN", i);
        fprintf(file, "\n\nThe dam and its surrounding area is safe from flooding now and no need to evacuate the people "
                "from neighbouring areas"
                "\nNo need to panic\n");

        fclose(file);

        //exit(0);
    }
}

//Function to check if the dam capacity is below the threshold capacity

int capacity(m dam)
{
    double cap = dam.lat_area*dam.water_level;

   
    if(cap>dam.threshold)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//Function to calculate the outward flow of water in the dam

double calculate(m dam, double shut_height)
{
    double velocity = square_root((2*g*shut_height));
    double area = dam.width * shut_height;
   
    return (area * velocity);
}

//Function to check whether the dam is safe from breaking due to the inward flow of water

int decision(m dam, double flow_out)
{
    double dh = (dam.flow_in - flow_out)/dam.lat_area;
    
   

    if(dh > dam.init_height)
    {
        return 1;
    }

    else
    {
        return 0;
    }
}

//Function to generate a sample record for a dam

void* create_sample(void* args)
{
    pthread_mutex_lock(&loc);
    FILE* fptr;
    double threshold = 443230000;
    double lat_area = 19623.462;
    double flow_in = 1028400;
    double width = 365.7;
    double water_level = 20000;
    double init_height = 53.6;
    fptr=fopen("sample.txt","w");
    fprintf(fptr, "Name,Threshold_Capacity,Lateral_Area,Inward_Flow,Width,Water_Level,Initial_Height\n");
    for(int t=0;t<1440;t++)
    {
        fprintf(fptr, "Periyar,%lf,%lf,%lf,%lf,%lf,%lf\n",threshold, lat_area, flow_in, width, water_level, init_height);
        water_level += 10;
        flow_in += 250;
    }
    fclose(fptr);
    pthread_mutex_unlock(&loc);
}

//Function to find shutter height

double find_shut_height(double flow_in, double init_height, double width, double lat_area)
{
    double shut_height, value;
    value = square_root(flow_in - lat_area*init_height);
    shut_height = value/(width*2*g);
    shut_height = cube_root(shut_height) + 1;
    return shut_height;
}
//Function to read from a given record

void split_string(char str[100], int ent)
{
    char splitString[7][10]; //Only 7 columns
    int i,j,cnt;
    j=0; cnt=0;
    for(i=0;i<=(strlen(str));i++)
    {
        // if comma or NULL found, assign NULL into splitStrings[cnt]
        if(str[i]==','||str[i]=='\0')
        {
            splitString[cnt][j]='\0';
            cnt++;  //for next value
            j=0;    //for next value, init index to 0
        }
        else
        {
            splitString[cnt][j]=str[i];
            j++;
        }
    }
    write_to_file(splitString, ent);
}

//Function to assign values from split_string()
m dam[1440];
void write_to_file(char dam_info[][10], int i)
{
    //atof is used to convert the numerical string to type double, should
    //there be a limit on the decimal places?
    strcpy(dam[i].name,dam_info[0]);
    dam[i].threshold = atof(dam_info[1]);
    dam[i].lat_area = atof(dam_info[2]);
    dam[i].flow_in = atof(dam_info[3]);
    dam[i].width = atof(dam_info[4]);
    dam[i].water_level = atof(dam_info[5]);
    dam[i].init_height = atof(dam_info[6]);
    //printf("%s,%lf,%lf,%lf,%lf,%lf,%lf\n", dam[i].name, dam[i].threshold, dam[i].lat_area, dam[i].flow_in, dam[i].width, dam[i].water_level, dam[i].init_height);
}    
//Function to store the entered details of the dam in a file for future reference

void file_print_struct(m dam, int n)
{
    FILE *fptr;

    //Opening the file called 'records'
    fptr = fopen("records.txt","a");

    //Printing all necessary information in the "records" file

    fprintf(fptr, "\t\t\t\t\t\tReport\n\n");
    fprintf(fptr, "\t\t\t\t\tEarly Warning Flood System\n\n\n");

    fprintf(fptr, "\n\nThe number of dams in the system that are being monitored : %d", n);
    fprintf(fptr, "\n\nThe name of the dam : %s", dam.name);
    fprintf(fptr, "\n\nThe threshold capacity of the dam in SI units : %lf", dam.threshold);
    fprintf(fptr, "\n\nThe lateral area of the contact surface in SI units : %lf", dam.lat_area);
    fprintf(fptr, "\n\nThe inward flow in the dam in SI units : %lf", dam.flow_in);
    fprintf(fptr, "\n\nThe width of the dam_shutter in SI units : %lf", dam.width);
    fprintf(fptr, "\n\nThe critical height of the dam in SI units : %lf", dam.init_height);
    fprintf(fptr, "\n\nThe water level in the dam in SI units : %lf", dam.water_level);

    //Closing the file
    fclose(fptr);
}

//Main function

int main()
{
    pthread_t trd;
    pthread_create(&trd, NULL, &create_sample, NULL);
    pthread_join(trd, NULL);
    FILE *ftr1,*ftr2;
    pthread_mutex_lock(&loc);
    //Opening the file called 'sample'
    ftr1 = fopen("sample.txt","r");
    //Creating a file called 'records'
    ftr2 = fopen("records.txt","w");

    //Closing the file
    fclose(ftr2);
    
    printf("\t\t\t\t\tEARLY WARNING FLOOD SYSTEM\n\n");
    
    char line[256];
    int i = 0, test=0;                                //Dam Entry Number
    while (fgets(line, sizeof(line), ftr1))
    {
        //We don't want the first row as it consists of the column names.
        if(test==0)
        {
            test++;
            continue;                                   
        }
        //printf("%s", line); 
        split_string(line,i);
        
        /* printf("\nEnter the name of the dam :");
        scanf("%s", dam[i].name);

        printf("\nEnter the threshold capacity of the dam in SI units :");
        scanf("%lf", &dam[i].threshold);

        printf("\nEnter the lateral area of the contact surface in SI units :");
        scanf("%lf", &dam[i].lat_area);

        printf("\nEnter the inward flow in the dam in SI units :");
        scanf("%lf", &dam[i].flow_in);

        printf("\nEnter the width of the dam shutter in SI units :");
        scanf("%lf", &dam[i].width);

        printf("\nEnter the critical height of the dam in SI units :");
        scanf("%lf", &dam[i].init_height);

        printf("\nEnter the water level in the dam in SI units :");
        scanf("%lf", &dam[i].water_level); 

        //Saving the details of the dam into a file
        
        //file_print_struct(dam[i], n);*/
        double flow_out = 0.00, shut_height = 0.00;
        int check, flag, y = 0;

        //Checking the criticality of the dam

        check = capacity(dam[i]);
        flag = decision(dam[i], flow_out);
        cond(check, flag, y, i);
        y++;
        sleep(0.5);

	    while(2)
        {
            if(check==0 && flag==0 && y!=0)                     //Checking if signal is GREEN
                {
                    /*FILE *file;

                    file = fopen("records.txt", "a");           //Opening the file called 'records'

                    printf("\nAt time t = %d seconds \nSignal = GREEN", i);
                    printf("\nThe dam and its surrounding area is safe from flooding now and no need to evacuate the people "
			               "from neighbouring areas."
			               "\nAnd no need to panic.\n");
                    fprintf(file, "\nAt time t = %d seconds signal = GREEN", i);
                    fprintf(file, "\nThe dam and its surrounding area is safe from flooding now and no need to evacuate the people "
			                "from neighbouring areas. "
			                "And no need to panic\n");

                    fclose(file);                               //Closing the file*/
                }

            else
                {
                           ftr2 = fopen("records.txt","a");                              //Opening the file called 'records'

                           printf("\n\nRise the shutter further to raise the outward flow in the dam ");
                           fprintf(ftr2,"\n\nRise the shutter further to raise the outward flow in the dam ");

                           //printf("\n\n1.Continue the program.");                       //Menu
                           //printf("\n2.Exit the program immediately.");
                           //printf("\n\nEnter any one of the above values: ");

                           //scanf("%d",&num);
                            if(1)
                            {
                               //flow_out = calculate(dam[i], shut_height);               //Calculating the outward flow
                               printf("\nThe current water level in the dam is: %lf\n\n",dam[i].water_level);
                               printf("\n\n");

                               fprintf(ftr2,"\nThe current water level in the dam is: %lf\n\n",dam[i].water_level);
                               
                               shut_height = find_shut_height(dam[i].flow_in, dam[i].init_height, dam[i].width, dam[i].lat_area);
                               printf("\n\nThe amount by which the shutter in the dam has to be risen is : %lf",shut_height);


                               fprintf(ftr2,"\n\nThe amount by which the shutter in the dam has to be risen is : %lf",shut_height);

                               

                               fclose(ftr2);                             //Closing the file
                            }

                    }
            break;
           } 
        i++;   
    }
    pthread_mutex_unlock(&loc);
    pthread_mutex_destroy(&loc);
    fclose(ftr1);
    return 0;
}
