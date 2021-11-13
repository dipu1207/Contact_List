// LGB.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<fstream>
#include<string.h>
#include <time.h>
#define P 12
#define K 32
long double centeroid[K+1][P+1];;
long double codebook[K+1][P+1];
void read_values(FILE* fp,long double values[P+1]){
	//Will read a line with 12 values from the file
	for(int i=1;i<=P;i++){
		fscanf(fp,"%Lf",&values[i]);
		//printf("values %Lf\n",values[i]);
	}

			
}
void print_values(long double values[P+1]){
	printf("%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",values[1],values[2],values[3],values[4],values[5],values[6],values[7],values[8],values[9],values[10],values[11],values[12]);

}
void read_values1(FILE* fp,long double values[P+1]){
	//Will read a line with 12 values from the file
			fscanf(fp,"%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",&values[1],&values[2],&values[3],&values[4],&values[5],&values[6],&values[7],&values[8],&values[9],&values[10],&values[11],&values[12]);
}

long double get_total_num_of_lines(){
	//Will go through universe.txt to read the number of lines present in it;
	FILE* fp =fopen("universe.csv","r");
	if(!fp){
		//Return if not able to open the file
		printf("Could not open the file\n");
		return 0 ;
	}
	char l[500];
	char c;
	long double lines=0;
	 for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n') // Increment count if this character is newline
            lines++;
	return lines;//return lines counter
}
void read_centeroids(char *fname){
	FILE *fp=fopen(fname,"r");
	if(!fp){
		printf("Not able to open the codebook\n");
		exit(0);
	}
	for(int i=1;i<=K;i++){
		read_values(fp,centeroid[i]);
	}
}
void print_centeroids(){
	printf("Printing centeroid\n");
	for(int i=1;i<=K;i++){
		print_values(centeroid[i]);
	}
}

void init_centeroids(long double centeroids[K][P+1],int Ke){
	//Initialize the centeroids as random vectors from the universe.txt
	FILE* fp =fopen("universe.csv","r");
	if(!fp){
		printf("Not able to open universe.csv\n");
		exit(0);
	}
	
	int random_num=rand();//choose a random number
	long double num_of_lines=get_total_num_of_lines();//get total number of lines from the file
	long long int range=num_of_lines/(K+2+random_num);
	int i,j;
	rewind(fp);
	long double temp[P+1];
	for(i=0;i<Ke;i++){
		//Iterating K time to select K random vectors as centeroid
		for(j=0;j<=range && !feof(fp);j++){
			read_values(fp,temp);
		}
		read_values(fp,centeroids[i]);//Read the line and init the values from the present row in file as ith centeroid
	}
}

long double tokhura_distance(long double test[P+1], long double ref[P+1]){
	//Will calculate tokhura distance between two sets of Ci's and returns the distance
	long  double tokhura_wt[P+1]={0,1.0, 3.0, 7.0, 13.0, 19.0, 22.0, 25.0, 33.0, 42.0, 50.0, 56.0, 61.0};//tokhura weights provided 
	long double tempsum=0;//will keep track of tokhura distances
	int j;	
	for(j=1;j<=P;j++)
		tempsum+=(tokhura_wt[j]*(test[j]-ref[j])*(test[j]-ref[j]));//sum the distance for all the diff values of j
	return tempsum;	
}
int tokhura_wrapper(long double test[P+1],int Ke){
	//will calculate tokhura distances for all the vowels reference files and the vowel given for input and return vowel index for prediction
	long double tokhura_dist_pres;//will save tokhura distance for present centeroid
	long double min_tokhura_dist;//will minimum tokhura distance
	long double pres_sum_distances=0;//will keep sum of the dist for all 5 readings
	int j=0,row=0;//will be used in loop
	int m=1;//index of the minimum tokhura distance
	for(j=1;j<=Ke;j++){
		//comparing the test with all the centeroids
		tokhura_dist_pres=tokhura_distance(centeroid[j],test);
		if(j==1){
			m=j;
			min_tokhura_dist=tokhura_dist_pres;
		}
		if(tokhura_dist_pres<min_tokhura_dist){
			m=j;//if present index j is having less value than the index m, then make m=j
			min_tokhura_dist=tokhura_dist_pres;
		}
	}
	return m;//return the centeroid index having minimum tokhura distance
}
long double tokhura_distance1(long double test[P+1], long double ref[P+1]){
	//Will calculate tokhura distance between two sets of Ci's and returns the distance
	long  double tokhura_wt[P+1]={0,1.0, 3.0, 7.0, 13.0, 19.0, 22.0, 25.0, 33.0, 42.0, 50.0, 56.0, 61.0};//tokhura weights provided 
	long double tempsum=0;//will keep track of tokhura distances
	int j;	
	for(j=1;j<=P;j++)
		tempsum+=(tokhura_wt[j]*(test[j]-ref[j])*(test[j]-ref[j]));//sum the distance for all the diff values of j
	return tempsum;	
}
int tokhura_wrapper1(long double centeroids[K][P+1],long double test[P+1],int Ke){
	//will calculate tokhura distances for all the vowels reference files and the vowel given for input and return vowel index for prediction
	long double tokhura_distances[K];//will save tokhura distances for all the 5 vowels and the vowel
	long double pres_sum_distances=0;//will keep sum of the dist for all 5 readings
	int j=0,row=0;//will be used in loop
	for(j=0;j<Ke;j++){
		//comparing the test with all the centeroids
		tokhura_distances[j]=tokhura_distance(centeroids[j],test);
	}
	int m=0;//index of the minimum tokhura distance
	for(j=0;j<Ke;j++){
		
		if(tokhura_distances[m]>tokhura_distances[j])m=j;//if present index j is having less value than the index m, then make m=j
	}
	return m;//return the centeroid index having minimum tokhura distance
}
void k_mean(long double cent[][P+1],int Ke,long double delta_thresh){
	//Function to apply KMeans algorithm to the Ke centeroid's present in cent array.The algorithm will terminate only when delta becomes less than delta_thresh
	long long int M=get_total_num_of_lines();//Saving count of number of vectors in universe
	long double sum_of_all_points[K][P+1]={0};//Will Store sum of all points belonging to respective centeroid
	long double count_of_all_points[K]={0};//Will keep count of points belonging to each centeroid
	long double temp[P+1];//will store the reading of a vector pointed by a filepointer
	long double total_dist=0;//will store total distortion
	long double prev_dist=0;//will store previous distortion
	long double delta=100;//will store absolute difference between present reading and last reading
	FILE* fp=fopen("universe.csv","r");//file pointer pointing to all the vectors 
	//printf("Starting KMeans Algorithm After performing slpit.Present num of centeroids are %d. This may take minutes to finish.Process will stop once delta becomes lower than %lf ......\n",Ke,delta_thresh);
	for(int itr=0;delta>delta_thresh && itr <250;itr++){
		//Keep calculating new set of centeroids till delta is more than delta threshold
		//if(delta==0.1 || delta==0.01 ||delta==0.001 || delta==0.0001)printf("Delta is %lf\n",delta);
		total_dist=0;//init the total distotion as 0 before each iteration
		rewind(fp);//rewind and goto the first reading of the file
		while(!feof(fp)){
			//Go through all the vectors and select assign the closest centeroid to them
			read_values1(fp,temp);//Reading the values of the vector 
			int pres_cent=tokhura_wrapper1(cent,temp,Ke);//Saving the closest centeroid index to the pres_cent(present centeroid) variable
			total_dist+=tokhura_distance1(cent[pres_cent],temp);//adding the distance btw vevtor and present_centeroid to total distoriton
			count_of_all_points[pres_cent]++;//Increasing the count of vectors assigned to present centeroid by 1
			for(int p=1;p<=12;p++){
				//Adding the 12 Ci's values of vector to the sum_of_all_points for the present vector.This will be later used to calculate new 
				//centeroid
				sum_of_all_points[pres_cent][p]+=temp[p];
			}
		}
		for(int k=0;k<Ke;k++){
			//Calculating new centeroids based on the vectors assigned to different regions
			for(int p=1;p<=12;p++){
				//Calculating all 12 Ci for the new centeroids as sum of all points assigned to that centeroid/num_of_all_points assigned to cent
				cent[k][p]=(sum_of_all_points[k][p]/count_of_all_points[k]);
			}
		}
		total_dist/=M;//Calculating average distortion for the vectors
		delta=abs((total_dist-prev_dist));//Calculting delta
		prev_dist=total_dist;//Setting previous distortion as total_distortion for this iteration
	}
	printf("Total Average Distortion After Completion of KMeans Algorithm %lf\n",total_dist);
}
void init_centeroids(long double centeroids[K][P+1]){
	//Initialize 1st vector in codebook as centeroid of the universe
	FILE* fp =fopen("universe.csv","r");
	long double sum_of_all_points[P+1]={0};//Will Store sum of all points belonging to respective centeroid
	long double num_samples=0;
	long double temp[P+1];//will store the reading of a vector pointed by a filepointer
	if(!fp){
		printf("Not able to open universe.csv\n");
		exit(0);
	}
	//printf("running lgb for init centeroids\n");
	while(!feof(fp)){
		//	printf("reading\n");
			//Go through all the vectors and get the centeroid
			read_values1(fp,temp);//Reading the values of the vector 
			//print_values(temp);
			num_samples=num_samples+1;//Increasing the count of vectors by 1
			for(int p=1;p<=12;p++){
				//Adding the 12 Ci's values of vector to the sum_of_all_points for the present vector.This will be later used to calculate new 
				//centeroid
				sum_of_all_points[p]+=temp[p];
			}
			//printf("total samples %lf\n",num_samples);
		}
	for(int i=1;i<=P;i++){
		//printf("%g\n",sum_of_all_points[i]/num_samples);
		//Assign 0th vector of codebook as centeroid of the universe
		codebook[0][i]=sum_of_all_points[i]/num_samples;

	}
	
}

void LGB(long double codebookw[][P+1],long double epsilon,int verbose){
	//Will apply LGB algorithm for K=8 and save the final results in codebook. To split the vector , the passed value of epsilon will be used
	FILE *fp =fopen("universe.csv","r");
	if(!fp){
		printf("file could not be opened\n");
		return ;
	}
	init_centeroids(codebook);//Initailizing the 1st centeroid as centeroid of the all vectors
	printf("Initial Codebook :%lf \t %lf \t %lf \t %lf \t %lf \t %lf \t %lf \t %lf \t %lf \t %lf \t %lf \t %lf \n",codebook[0][1],codebook[0][2],codebook[0][3],codebook[0][4],codebook[0][5],codebook[0][6],codebook[0][7],codebook[0][8],codebook[0][9],codebook[0][10],codebook[0][11],codebook[0][12]);
	printf("Starting LGB Algorithm. This May take 2-4 Minutes to finish....\n");
	for(int i=1;i<=(K/2);i=i*2){
		//Reapeating the process until we have 8 centertoids in codebook
		for(int j=1;j<=i;j++){
			//for all the centeroids already init in the codebook, perform split .After splitting codebook will have 2*i centeroids
			for(int p=1;p<=P;p++){
				//Loop to split all the already initialized vectors
				codebook[(j-1)+i][p]=codebook[j-1][p]*(1+epsilon);
				codebook[j-1][p]=codebook[j-1][p]*(1-epsilon);
			}
		}
		if(1){
			FILE *wp=fopen("codebook.txt","w");
			printf("Printing after splitting codebook. Now Total num of centeroids are %d\n",2*i);
			for(int k=0;k<2*i;k++){
				fprintf(wp,"%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n",codebook[k][1],codebook[k][2],codebook[k][3],codebook[k][4],codebook[k][5],codebook[k][6],codebook[k][7],codebook[k][8],codebook[k][9],codebook[k][10],codebook[k][11],codebook[k][12]);
			}
			fclose(wp);
		}
		
		k_mean(codebook,i*2,0.0001);//Applying KMeans to 2*i (No of centeroids initialized till now)
	}
	printf("LGB is finished. Codebook is saved into codebook.txt\n");
}


