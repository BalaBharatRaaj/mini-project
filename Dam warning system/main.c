//C program to create an early warning system

#include <stdio.h>
#include <stdlib.h>
#define g 9.8

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
void cond(int check, int flag, int y);
void file_print_struct(m dam, int n);

//Creating a function for the protocols to be followed during a signal red emergency

void protocol_1()
{
   printf("\n");
   printf("\n\t\t\tPlease follow the protocols given below immediately:");
   printf("\n");
   printf("\n1. Rise the dam shutters uniformly to allow the free outflow to increase outward velocity of dam");
   printf("\n2. Evacuate the people who are near the dam for atleast a radius of 40km for rehabilitation purposes from potential inundation areas.");
   printf("\n3. Immediately open the check dams further ahead to allow the free outward flow of water from the dam");
   printf("\n4. Make sure there is no water overflowing through the dam crests or large overflow through the channels (piping) incase of embankent erosion");
   printf("\n5. Kindly assume the dam failure is in progress and take the above the steps necessary");
}

//Creating a function to find the squareroot of a number
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
	
	sqt = (n / 2*temp)/2;
        // Then, replace values (256 / 128)
    }
    return sqt;	
}
//Function to check whether the dam and its surrounding area is safe from flooding

void cond(int check, int flag, int y)

{
    int chfl = check + flag; 
    if((chfl)==2)
    {
        FILE *file;
        file = fopen("records.txt", "a");
	    
        printf("\nAt time t= %d hours \nSignal = RED", y);
        printf("\n\nAlert!!The dam and its surrounding areas are on the verge of flooding."
               "\nSo kindly evacuate the people from the surrounding areas and move them them to higher grounds until futher adviced.");
	protocol_1();
	    
        fprintf(file, "\nAt time t=%d hours \nSignal=RED", y);
        fprintf(file, "\nAlert!!The dam and its surrounding areas are on the verge of flooding."
                "\nSo kindly evacuate the people from the surrounding areas and move them them to higher grounds until futher adviced.");
	    
        fclose(file);
    }
	
    else if((chfl)==1)
    {
        FILE *file;
        file = fopen("records.txt", "a");
	    
        printf("\nAt time t= %d hours \nSignal = ORANGE", y);
        printf("\n\nThe dam and its surrounding areas are at high risk of flooding."
               "\nSo kindly take the necessary steps required");
	    
        fprintf(file, "\nAt time t = %d hours \nSignal = ORANGE", y);
        fprintf(file, "\n\nThe dam and its surrounding areas are at high risk of flooding."
                "\nSo kindly take the necessary steps required");
	    
        fclose(file);
    }
	
    else if((chfl)==0)
    {
        FILE *file;
        file = fopen("records.txt", "a");
	    
        printf("\nAt time t= %d hours \nSignal = GREEN", y);
        printf("\n\nThe dam and its surrounding area is safe from flooding now and no need to evacuate the people from neighbouring areas."
               "\nNo need to panic.");
	    
        fprintf(file, "\nAt time t = %d hours \nSignal = GREEN", y);
        fprintf(file, "\n\nThe dam and its surrounding area is safe from flooding now and no need to evacuate the people from neighbouring areas"
        "\nNo need to panic");
	    
        fclose(file);
	    
        exit(0);
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
    FILE *ftr;

    //Creating a file called 'records'
    ftr=fopen("records.txt","w");

    //Closing the file
    fclose(ftr);

    printf("\t\t\t\t\tEARLY WARNING FLOOD SYSTEM\n\n");
    int n;
    int num;
    printf("\nEnter the number of dams in the system that are being monitored :");

    scanf("%d", &n);
    m dam[n];
    for(int i=0; i<n; i++)
    {
        printf("\nEnter the name of the dam :");
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
        file_print_struct(dam[i], n);
        double flow_out = 0.00, shut_height = 0.00;
        int check, flag, y = 0;

        //Checking the criticality of the dam

        check = capacity(dam[i]);
        flag = decision(dam[i], flow_out);
        cond(check, flag, y);
        y = y + 1;

	while(2)
        {
            if(check==0 && flag==0 && y!=0)                     //Checking if signal is GREEN
                {
                    FILE *file;
                    
                    file = fopen("records.txt", "a");           //Opening the file called 'records'
                    
                    printf("\nAt time t = %d hours \nSignal = GREEN", y);
                    printf("\nThe dam and its surrounding area is safe from flooding now and no need to evacuate the people from neighbouring areas. \nAnd no need to panic.");
                    fprintf(file, "\nAt time t=%d hours signal=GREEN", y);
                    fprintf(file, "\nThe dam and its surrounding area is safe from flooding now and no need to evacuate the people from neighbouring areas.And no need to panic");
                    
                    fclose(file);                               //Closing the file
                    
                    exit(0);
                }

            else
                {
                           ftr = fopen("records.txt","a");                              //Opening the file called 'records'

                           printf("\n\nRise the shutter further to raise the outward flow in the dam ");
                           fprintf(ftr,"\n\nRise the shutter further to raise the outward flow in the dam ");

                           printf("\n\n1.Continue the program.");                       //Menu
                           printf("\n2.Exit the program immediately.");
                           printf("\n\nEnter any one of the above values: ");
                           
                           scanf("%d",&num);
                           
                           if(num == 2)
                           {
                               fprintf(file,"\n\nProgram finished.");
                               fclose(file);
                               exit(0);                                                 //Exiting the program 
                           }    
                           else
                           {
                               printf("\n\nEnter the amount by which the shutter in the dam is to be risen: ");     
                               scanf("%lf",&shut_height);                               //Input for shutter height 


                               fprintf(ftr,"\n\nEnter the amount by which the shutter in the dam is to be risen: %lf",shut_height);


                               flow_out = calculate(dam[i], shut_height);               //Calculating the outward flow
                               printf("\nEnter the current water level in the dam in SI units:");
                               scanf("%lf",&dam[i].water_level);                        //Input for water level
                               printf("\n\n");

                               fprintf(ftr,"\nEnter the current water level in the dam in SI units: %lf\n\n",dam[i].water_level);

                               //Checking the capacity 
                               check = capacity(dam[i]);
                               
                               //Getting the decision required
                               flag = decision(dam[i], flow_out);

                               cond(check, flag, y);
                               y = y + 1;

                               fclose(ftr);                             //Closing the file
                            }

                    }

           }
    }

    return 0;
}
