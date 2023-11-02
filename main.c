//Libraries we used
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Structure Initialization
struct turbine {
  char name[100];
  double ratedCap;      // kW
  double hubH;          // m
  double ratedWS;       // m/s
  double startupWS;     // m/s
  double fStartWS;      // m/s
  double cutOutWS;      // m/s
  double pcurveout[15]; //Kw
};
struct windData {
  int year;
  int month;
  int day;
  int hour;
  int windS;
};
struct monthlySummary {
  int month; // 1 is january 2 is february etc.
  double sumWS;
  double avgWS;
  double maxWS;
  double minWS;
  double timeTotal;
  double timeOff;
  double timeOn;
  double PercentOnline;
};

// initializing functions
struct turbine newModel(struct turbine t);
struct turbine hardcode(struct turbine t, int n);
struct windData *dataGet(struct windData *);
struct monthlySummary *summary(struct windData *FileData, struct turbine Tbine,struct monthlySummary *summaryData);
void displaySummary(struct monthlySummary *summaryData);
void fileSave(struct monthlySummary *summaryData);

// Main Function
int main(void) {
  // Variable Initialization
  int input, tSize = 2, checkCP = 0;
  double num;
  struct turbine *t;
  struct windData *arrData;
  struct monthlySummary *MonthlySummary;
  // Memory Allocation for Array of hardcoded turbine Structures
  t = malloc(tSize * sizeof(struct turbine));

  // Hard Coded Data; TESTING PURPOSES
  t[0] = hardcode(t[0], 0); // Raum 1.3kW hardcoded
  t[1] = hardcode(t[1], 1); // Raum 3.5kW hardcoded

  // INFINITE MENU START
  do{
    puts("Please make a selection from the following:");
    puts("1. Model a new Wind Turbine (WT)");
    puts("2. Import climate profile");
    puts("3. Simulate location");
    puts("4. Save simulation");
    puts("5. Exit");

    scanf("%d", &input);
    switch (input){
    // Menu Option 1
      case 1:
        tSize++;
        t = realloc(t, tSize * sizeof(struct turbine));//Increases the amount of memory I am reserving for my turbines
        t[tSize - 1] = newModel(t[tSize - 1]);//calls the newModel function that returns the data of a user created turbine
      break;
    // Menu Option 2
      case 2: 
        arrData = dataGet(arrData);
        checkCP = 1;
      break;
    // Menu Option 3
      case 3:
        if (checkCP == 0)//checks if the user has inputted a file already
          puts("ERROR: Climate profile not uploaded");
        else if (checkCP == 1) {
          printf("Available WT units:\n");
          for (int i = 0; i < tSize; ++i) {//Prints out all the created turbines
            printf("   %d.  %s\n", i+1, t[i].name);
          }
          scanf("%d", &input);
          MonthlySummary = summary(arrData, t[input - 1], MonthlySummary);
        }
      break;
    // Menu Option 4
      case 4:
        fileSave(MonthlySummary);
      break;
    // Menu Option 5
      case 5:
        puts("\n-------------------\nProgram Terminated.\n-------------------\n");
      break;
    default:
      printf("ERROR: Invalid Input Only 1-5 Allowed");
    break;
    }
  }while(input !=5);
  
  //frees the memory
  free(arrData);
  free(MonthlySummary);
  free(t);
  return 0;
}

//This section allows the user to create there own turbines
//With the use of a linked list, the user is allowed to make as many turbines as there memory lets them
struct turbine newModel(struct turbine t) {
  double num;
  printf("Please enter the following information:");

  printf("\nName (no spaces): ");
  scanf("%s", t.name);

  puts("Rated Capacity (kW): ");
  scanf("%lf", &t.ratedCap);

  puts("\nHub Height (m): ");
  scanf("%lf", &t.hubH);

  puts("\nOperational Data:\n");

  puts("\nRated Wind Speed (m/s): ");
  scanf("%lf", &t.ratedWS);

  puts("\nStart-up Wind Speed (m/s): ");
  scanf("%lf", &t.startupWS);

  printf("\nFurling Start-Up Wind Speed (m/s): ");
  scanf("%lf", &t.fStartWS);

  printf("\nCut-Out Wind Speed: (m/s): ");
  scanf("%lf", &t.cutOutWS);

  printf("\nPower Curve: x m/s = y kW");

  for (int x = 0; x < 15; x++) {//For loop gets 15 points for power curve
    printf("\n%d. ", x + 1);
    scanf("%lf", &num);
    t.pcurveout[x] = num;
  }

  return t;//returns the data of the user inputted turbine
}
//This section is used to hardcode the raum turbines data into the turbine structure
struct turbine hardcode(struct turbine t, int n) {
  if (n == 0) {
    strcpy(t.name, "Raum 1.3kW");
    t.ratedCap = 1.3;
    t.hubH = 14.5;
    t.ratedWS = 11;
    t.startupWS = 3;
    t.fStartWS = 10;
    t.cutOutWS = 45;
    t.pcurveout[0] = 0;
    t.pcurveout[1] = 0;
    t.pcurveout[2] = 0;
    t.pcurveout[3] = 0.058;
    t.pcurveout[4] = 0.127;
    t.pcurveout[5] = 0.241;
    t.pcurveout[6] = 0.429;
    t.pcurveout[7] = 0.673;
    t.pcurveout[8] = 0.914;
    t.pcurveout[9] = 1.200;
    t.pcurveout[10] = 1.200;
    t.pcurveout[11] = 1.200;
    t.pcurveout[12] = 1.200;
    t.pcurveout[13] = 1.200;
    t.pcurveout[14] = 1.200;
  } else if (n == 1) {
    strcpy(t.name, "Raum 3.5kW");
    t.ratedCap = 3.5;
    t.hubH = 14.5;
    t.ratedWS = 11;
    t.startupWS = 2.8;
    t.fStartWS = 22;
    t.cutOutWS = 50;
    t.pcurveout[0] = 0;
    t.pcurveout[1] = 0;
    t.pcurveout[2] = 0;
    t.pcurveout[3] = 0.051;
    t.pcurveout[4] = 0.134;
    t.pcurveout[5] = 0.297;
    t.pcurveout[6] = 0.563;
    t.pcurveout[7] = 1;
    t.pcurveout[8] = 1.569;
    t.pcurveout[9] = 2.233;
    t.pcurveout[10] = 3.064;
    t.pcurveout[11] = 3.500;
    t.pcurveout[12] = 3.500;
    t.pcurveout[13] = 3.500;
    t.pcurveout[14] = 3.500;
  }
  return t;
}

//This section reads the users desired file and allows it to be used with other parts of the program
struct windData *dataGet(struct windData *arrData) {
  // Variable Initialization
  char words[50], fileName[0];
  char fileComma, fileNoUse;
  int fileData, timeData, linecount = 0, pos = 0;

  // Prompt for File Name
  puts("What file would you like to open:");
  scanf("%s", &fileName);

  // File Opening
  FILE *fileio = fopen(fileName, "r");
  if (!fileio) {//if the user inputted the wrong file location we just return them to the menu
    puts("ERROR: File not located");
    return 0;
  } else
    puts("File located successfully");

  while (!feof(fileio)) { // Gets the total lines in the file for malloc
    fscanf(fileio, "%s", &words);
    linecount++;
  }

  arrData = (struct windData *)malloc(linecount * sizeof(struct windData));//allocates memory based on the amount of lines are in a file
  rewind(fileio);//Rewinds the fileio cursor the the beginning of the file
  while (!feof(fileio)) {
    fscanf(fileio, "%d %c %d %c %d %c %d %c %d %c %d \n", &arrData[pos].year,
           &fileComma, &arrData[pos].month, &fileComma, &arrData[pos].day,
           &fileComma, &arrData[pos].hour, &fileNoUse, &timeData, &fileComma,
           &arrData[pos].windS);//for reading the file to the structure. It was difficult to figure out how to avoid the commas,
           //but in the end we cam up with the idea to just read them as normal chars but just disregard them
    pos++;//used for saving data in the next struct section
  }

  fclose(fileio);//closed file
  puts("Uploading Complete");
  return arrData;
}


//This section takes a chosen turbine and your file data and creates a monthly summary that contains the sum,avg,max and min power generated from it along with the
//total hours offline and online along with the percentage of the time it was online.
struct monthlySummary *summary(struct windData *FileData, struct turbine Tbine,struct monthlySummary *summaryData) {
  //All the months in the year. (in case it wasn't clear)
  char months[12][9]={{"January"},{"February"},{"March"},{"April"},{"May"},{"June"},{"July"},{"August"},{"September"},{"October"},{"November"},{"December"}};
  summaryData = (struct monthlySummary *)malloc(12 * sizeof(struct monthlySummary));//I want to store the summary for 12 months
  int month = 1;//int for month pos
  double curMin=0;
  double curMax=0;
  double number =0; //This is the Number of values I had to add to get the data sum. I use this for calculating average
  int datapoints = 0;//Used to get the number of lines in the file data

  while(FileData[datapoints].year)//counts the amount of lines are in the file
    datapoints++;
  
  printf("Time range employed: %d-%d\n", FileData[0].year,FileData[datapoints - 2].year);//I thought it would be cooler to do a data year range
  printf("Turbine model employed: %s\n", Tbine.name);
  printf("Total hours employed: %d\n", datapoints - 1);//The amount of lines that exist in the file


  while(month <= 12){// I will use this to loop it for all the months
    summaryData[month - 1].sumWS =0;
    int x =0;//array pos
    while(x<=(datapoints-1)){//Goes through the entire file. Not very optimized but the best way I can think of to ensure I get all the data for each month
      for(int i=0;i<15;i++){ //Matches each windspeed value with its pcurve equivalent.
        if (FileData[x].month == month && FileData[x].windS >= i && FileData[x].windS < i+1) {
            if(i>0){//Set this up so I avoid going out of array bounds
              summaryData[month - 1].sumWS = summaryData[month - 1].sumWS + Tbine.pcurveout[i-1];//Adding the pcurve value to the sum
              if(curMin > Tbine.pcurveout[i-1]){//used to determine the minimum power generated
                curMin = Tbine.pcurveout[i-1];
              }
              else if(curMax<Tbine.pcurveout[i-1]){
                curMax = Tbine.pcurveout[i-1];
              }
            }
            else if(i-1<=0){//So I don't go out of array bounds
              summaryData[month - 1].sumWS = summaryData[month - 1].sumWS + Tbine.pcurveout[i];//Adding the pcurve value to the sum
              if(curMin > Tbine.pcurveout[i]){//Used to determine the minimum amount of power generated
                curMin = Tbine.pcurveout[i];
              }
              else if(curMax<Tbine.pcurveout[i]){//Used to determine the maximum amount of power generated
                curMax = Tbine.pcurveout[i];
              }
            }
              number++;
              i=15;//Break out of the for loop since I found the number in the pcurve that matches with he windspeed
        }
        else if(FileData[x].month == month && FileData[x].windS >= 15){//For all the windspeed data 15m/s or above
              summaryData[month - 1].sumWS = summaryData[month - 1].sumWS + Tbine.ratedCap;//Adding the pcurve value to the sum
              if(curMin > Tbine.ratedCap){//Used to determine the minimum amount of power generated
                curMin = Tbine.ratedCap;
              }
              else if(curMax<Tbine.ratedCap){//Used to determine the maximum amount of power generated
                curMax = Tbine.ratedCap;
              }
              number++;
              i=15;//Break out of the for loop since I found the number in the pcurve that matches with he windspeed
        }
      } 
      if (FileData[x].month == month)
      summaryData[month-1].timeTotal++;//Calculates the total data hours
      if (FileData[x].month == month && FileData[x].windS > 0){
        summaryData[month-1].timeOn++;//if the wind was blowing the time on increases
      }
      x++;//Changes the value I am evalulating
    }//According to the pdf the total sum for january should be 29.527 but I am getting 302. I don't think the data in the pdf is accurate though
    summaryData[month-1].timeOff = (summaryData[month-1].timeTotal) - summaryData[month-1].timeOn;      //calculates hours offline
    summaryData[month-1].PercentOnline = (summaryData[month-1].timeOn)/(summaryData[month-1].timeTotal);//calculates percent online
    summaryData[month-1].avgWS = (summaryData[month-1].sumWS)/number;                                   //calculates average
    summaryData[month-1].minWS = curMin;                                                                //Gets the minimum power out of the month
    summaryData[month-1].maxWS = curMax;                                                                //Gets the maximum power out of the month
    month++;//increase this to change the month I am storing data for
  }
  displaySummary(summaryData);
  return summaryData;
}


//This section is used to create a visual table in the console. This probably won't lineup for you.
void displaySummary(struct monthlySummary *summaryData){
  char months[12][4] = { "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };
  puts("\nMonth\t\tSum\t\tAvg\t\tMax\t\tMin\t\tHrs Offline\tHrs Online\t% Online");

  for (int i = 0; i < 12; i++) {
		printf("%s\t\t%.2lf\t\t%.2lf\t\t%.2lf\t\t%.1lf\t\t%.lf\t\t%.lf\t\t%.2lf\n", months[i], summaryData[i].sumWS, summaryData[i].avgWS, summaryData[i].maxWS, summaryData[i].minWS, summaryData[i].timeOff, summaryData[i].timeOn, summaryData[i].PercentOnline*100);
	}
  puts("File succefully printed!");
  return;
}
//This section takes the data from the monthly summary and prints it out to a user specified file.
void fileSave(struct monthlySummary *summaryData){
   char months[12][4] = { "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };
  //Variable Initialization
  char fileName[50];

  //File name prompt
  puts("The simulation has previously been completed and the results will now be saved.");
  puts("What file name would you like the results to have(50 characters): ");
  puts("Warning! If you select a file with data in it, the file will be erased and replaced with this data.");
  scanf("%s", &fileName);
  FILE *fileio = fopen(fileName, "w");//opens or creates the file if it doesn't exist and writes data in it
  fprintf(fileio,"Month\t\tSum\t\tAvg\t\tMax\t\tMin\t\tHrs Offline\tHrs Online\t% Online\n");
  for (int i = 0; i < 12; i++) {//for loop to write the summary of each month into the file
		fprintf(fileio,"%s\t\t%.2lf\t\t%.2lf\t\t%.2lf\t\t%.1lf\t\t%.lf\t\t%.lf\t\t%.2lf\n", months[i], summaryData[i].sumWS, summaryData[i].avgWS, summaryData[i].maxWS, summaryData[i].minWS, summaryData[i].timeOff, summaryData[i].timeOn, summaryData[i].PercentOnline*100);
	}
  fclose(fileio);//closes the file
  return;//we don't need to return anything
}
