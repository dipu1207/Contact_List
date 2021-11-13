#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#define P 12
#define PI 3.14159

void  calculate_ri(long double input[],int N,long double r[]){
	//Calculate Ri and save them in array r
	int i,j;
	long double tempsum=0;//will keep track of the sum
	for(j=0;j<=P;j++){
		tempsum=0;//init the tempsum 0 before every iteration
		for(i=0;i<N-j;i++){
			tempsum+=input[i]*input[i+j];
		}
		r[j]=tempsum;//save tempsum as r[j]
	}
}
void calculate_ai(long double r[],long double alpha[P+1][P+1],long double a[P+1]){
	long double k[P+1]; //will be used to store k values
	long double e[P+1];//will be used to store e values
	e[0]=r[0];//init e[0] as r[0];
	int i,j;
	long double tempsum=0;//init tempsum as 0
	for(i=1;i<=P;i++){
		tempsum=0;//init tempsum as zero in every loop
		for(j=1;j<i;j++)
			tempsum+=alpha[i-1][j]*r[i-j];
		k[i]=(r[i]-tempsum)*1.0/e[i-1];
		alpha[i][i]=k[i];
		for(j=1;j<i;j++){
			alpha[i][j]=alpha[i-1][j]-k[i]*alpha[i-1][i-j];}
		e[i]=(1-k[i]*k[i])*e[i-1];
		}
	for(i=0;i<=P;i++){a[i]=(1)*alpha[P][i];// save the ai in the array	A
		}
	}
void calculate_ci(long double r[],long double a[], long double c[]){
	c[0]=log(r[0]*r[0]);
	long double tempsum=0;
	int m ,k;
	for(m=1;m<=P;m++){
		tempsum=0;
		for(k=1;k<m;k++)
			tempsum+=(k*c[k]*a[m-k])/m;
		c[m]=a[m]+tempsum;
	}
}
void sine_window(long double c[],long double w[]){
	int i;
	for(i=1;i<=P;i++){
		w[i]=(1+6*(sin((PI*i)/12)));
				w[i]*=c[i];
	}
	return;
}
void skip_start(FILE* fp){
	//will be used to skip the initial part of the file , ie the text and 1 0 values
	char c='c';
	long double read=0;
	if(fp){
		
		while(isalpha(c) && !feof(fp)){
			//Keep on reading until we find digits to skip the text part
			c=fgetc(fp);
			fscanf(fp, "%*[^\n]\n");
		}
		while(abs(read)<2 && !feof(fp)){
			//Keep on reading until the value are -1,0,1
			
			fscanf(fp,"%lf \n",&read);
		}
		
	}
	else{
		//if the file is not opened , exit
		printf("error openeing the file \n");
		exit(0);
	}

}

void read_file_and_calculate_req1(char *filename,char *output,char *mode){
		//Read the initial input from the initial samples files
	//Calculate Dc shift and max amp
	//Normalize the samples and write the values to Normalized.txt file
	//Read Normalized value and sum up consecutive 320 samples to calculate energy of a frame and write in energy.txt
	//Calculate max energy to find 3rd frame of the steady part, from the frame no find the line no to read the samples 
	//Calculate the rasied Ci's and write those 5 row(one row per frame) into the output file 
	FILE *fp=fopen(filename,"r");//initial input 
	if(!fp){
		printf("file could not be opened for preprocessing\n");
		exit(0);
	}
	double read=0;//to save temp values read from a file
	double zcr=0,eng=0,dcshift=0;
	double max_amp=0;//will save max amp req for normalization
	double nf;//normalization factor;
	double avg_eng=0,thresh_eng=0;
	double temp;
	fpos_t tpos;
	int num_of_samples=0;
	skip_start(fp);//skip the text part and 0's and 1's from start of the file
	
	while(!feof(fp)){
		num_of_samples++;//increase the count for the samples increased
		fscanf(fp,"%lf \n",&read);//scan the value from the file
		dcshift+=read;//add the reading to the dcshift
		if(max_amp<abs(read))max_amp=read;//if present reading is more than
		
	}
	dcshift/=num_of_samples;
	if(max_amp>5000)
	nf=(max_amp-5000)/max_amp;
	else nf=1;
	rewind(fp);
	skip_start(fp);
	FILE *wp=fopen("normalized.txt","w");
	while(!feof(fp)){
		//write the normalized value in file normalized.txt
		fscanf(fp,"%lf \n",&read);
		temp=(read-dcshift)*nf;
		fprintf(wp,"%lf \n",temp);
	}
	fclose(wp);
	fclose(fp);
	
	FILE *fp1=fopen("normalized.txt","r");//open file to read normalized values
	FILE *wp1=fopen("energy.txt","w");
	FILE *ftemp;
	num_of_samples=0;
	avg_eng=0;//init the avg energy as 0, and summing the energy of 320 samples to calculate the avg energy
	while(!feof(fp1)){
		//write the energy into the energy.txt file
		fscanf(fp1,"%lf \n",&read);
		if(num_of_samples==80)fgetpos(fp1,&tpos);
		if(num_of_samples==320){ 
			avg_eng/=320;//dividing the total sum by 320 (num of samples) to get avg energy
			fprintf(wp1,"%lf \n",avg_eng);//writing average energy in the file "energy.txt"
			avg_eng=0;//restoring avg_eng as present eng
			num_of_samples=1;//restoring num_of_samples =0 as we have read 320 samples
			fsetpos(fp1,&tpos);
			
		}
		else{
			avg_eng+=read*read;//adding present energy to the avg_eng
			num_of_samples++;//incrementing the num_of_samples counter
		}
	}
	fclose(wp1);
	fclose(fp1);//closing file pointers
	FILE *fp2=fopen("energy.txt","r");//opening the energy file to read the energy
	int i,j;
	int start_line=0,count_eng_above_thresh=0;
	rewind(fp2);//rewinding to the start of the energy file
	long double max_eng=0;//to store max energy
	int third_frame_start=0;//to store the frame no of the 3rd frame
	int frame_start_line=0;
	int ten=10;
	long double noise_eng=0;;
	while(ten){
		fscanf(fp2,"%lf \n",&read);
		ten=ten-1;
		noise_eng+=read;
	}
	noise_eng/=10;
	printf("noise energy is %lf\n",noise_eng);
	rewind(fp2);
	int consecutive_increase=0;
	while(!feof(fp2)){
		fscanf(fp2,"%lf \n",&read);
		
		start_line++;//keep incrementing the start line as we read a line
	//	if(frame_start_line==0 && consecutive_increase==20){frame_start_line=start_line; printf("Setting frame start line %d\n",frame_start_line);}
		if(max_eng<read){
			//if present energy is more than max_eng , set the third start frame to present start line(frame no having  the max eng) and update the max energy
			third_frame_start=start_line;
			max_eng=read;//update the max energy encountered yet
		}		
	}
	rewind(fp2);
	start_line=0;
	while(!feof(fp2)){
			
			fscanf(fp2,"%lf \n",&read);
			//printf(" %lf ",read);
			if(read>0.009*max_eng){
				frame_start_line=start_line;
				printf("Setting frame start line %d\n",frame_start_line);
				break; 
			}
			start_line++;		
	}
	//printf("max energy:%lf\n",max_eng);
	//printf("third frame start %d\n",third_frame_start);
	//printf(" frame start line %d\n",frame_start_line);
	//printf("\nmax energy frame starts from line %d\n",third_frame_start);
	if((third_frame_start-frame_start_line)>75)
		start_line=(third_frame_start-75)*80;//we stored the line num of the 3rd frame , to get the line num of 1st frame we subtract 2. We multiply by 320 as all 
										//frames contains 320 samples and we need to know line num of starting sample to read from normalized values
	else start_line=frame_start_line*80;
	//printf("frame start line %d\n",frame_start_line);
	//printf("start_line%d\n",start_line);
	if(start_line<0)start_line=0;
	//printf("reading starts from line %d\n",start_line);
	
	FILE *fp3=fopen("normalized.txt","r");//opening file pointer to normalized.txt file
	if(!fp3){
		//if file pointer is not opening print and exit
		printf("error opening the file\n");
		exit(0);
	}
	//rewind(fp2);
	while(!feof(fp3) && start_line){
		//keep looping until we reach to the start line
		fscanf(fp3,"%lf \n",&read);
		start_line--;//Keep decrementing the count as we read a line 
	}
	long double input[320];
	long double ri[P+1];
	long double  alpha[P+1][P+1];
	long double a[P+1];
	long double c[P+1];
	long double w[P+1];
	int num_frames;
//	long double last_frame_eng=80*noise_eng+1;
	int frame_length=0;
	FILE* wp3=fopen(output,mode);//Append the Ci's into the output file
	for(j=0;(j<150 && !feof(fp3) && read> 0.005*max_eng ) || j<10 ;j++){
		fscanf(fp2,"%lf \n",&read);
		//printf("read %lf \n",read);
		frame_length++;
		//Reading 85 steady frames from the file
		for( i=0;i<320;i++){
			if(i==80)fgetpos(fp3,&tpos);
			fscanf(fp3," %lf",&input[i]);//reading next 320 samples from the Normalized inputs file and saving it into the input array
			//last_frame_eng+=(input[i]*input[i]);
		}
		//printf("Last frame eng %lf\n",last_frame_eng);
		calculate_ri(input,320,ri);
		calculate_ai(ri,alpha,a);
		calculate_ci(ri,a,c);
		sine_window(c,w);
		//FILE* wp3=fopen(output,mode);//Append the Ci's into the output file
		fprintf(wp3,"%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n",w[1],w[2],w[3],w[4],w[5],w[6],w[7],w[8],w[9],w[10],w[11],w[12]);//write the calculated Cis after sine raising sine window into the output file
		fsetpos(fp3,&tpos);
	}
	
	fclose(fp2);//closing the file pinter 
	fclose(wp3);//close the file pointer
	fclose(fp3);
}

/*long double tokhura_distance(long double test[P+1], long double ref[P+1]){
	//Will calculate tokhura distance between two sets of Ci's and returns the distance
	long  double tokhura_wt[P+1]={0,1.0, 3.0, 7.0, 13.0, 19.0, 22.0, 25.0, 33.0, 42.0, 50.0, 56.0, 61.0};//tokhura weights provided 
	long double tempsum=0;//will keep track of tokhura distances
	int j;	
	for(j=1;j<=P;j++)
		tempsum+=(tokhura_wt[j]*(test[j]-ref[j])*(test[j]-ref[j]));//sum the distance for all the diff values of j
	return tempsum;	
}
int tokura_wrapper(char vowel,long double test[5][P+1]){
	//will calculate tokhura distances for all the vowels reference files and the vowel given for input and return vowel index for prediction
	long double tokhura_distances[5];//will save tokhura distances for all the 5 vowels and the vowel
	long double pres_sum_distances=0;//will keep sum of the dist for all 5 readings
	char vowels[5]={'a','e','i','o','u'};//will map integer to the vowel
	int j=0,row=0;//will be used in loop
	for(j=0;j<5;j++){
		//comparing the given vowel with all the vowels 
		pres_sum_distances=0;//init the dist as 0
		char ref_file[100]={vowels[j],'r','e','f','.','t','x','t'};//the reference file which will be used to compare the present vowel
		FILE* reff=fopen(ref_file,"r");//pointer to the vowel file which is being compared to the input vowel
		if(!reff){
			//if any of the file pointers are null, print the error and exit
			printf("tokhura file not opened\n");
			exit(0);
		}
		for(row=0;row<5;row++){
			//loop through 5 rows of the reference file
			
			long double ref[P+1];
			fscanf(reff,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf \n",&ref[1],&ref[2],&ref[3],&ref[4],&ref[5],&ref[6],&ref[7],&ref[8],&ref[9],&ref[10],&ref[11],&ref[12]);
			pres_sum_distances+=tokhura_distance(test[row],ref);

		}
		tokhura_distances[j]=pres_sum_distances/5;//thokura distance will be equal to sum of distances/5;
	}
	int m=0;//index of the minimum tokhura distance
	for(j=0;j<5;j++){
		//loop through all thokura distances to get the index to the minimum and printing distances between all the vowels
		printf("tokhura dist bw %c and %c is %lf\n",vowel,vowels[j],tokhura_distances[j]);
		if(tokhura_distances[m]>tokhura_distances[j])m=j;//if present index j is having less value than the index m, then make m=j
	}
	return m;//return the vowel index having minimum tokhura distance
}
void clear_files(){
	//will clear all the intermediate filed which are appended during thr program
	FILE *fp=fopen("a.txt","w");
	fclose(fp);
	fp=fopen("e.txt","w");
	fclose(fp);
	fp=fopen("i.txt","w");
	fclose(fp);
	fp=fopen("o.txt","w");
	fclose(fp);
	fp=fopen("u.txt","w");
	fclose(fp);
	fp=fopen("at.txt","w");
	fclose(fp);
	fp=fopen("et.txt","w");
	fclose(fp);
	fp=fopen("it.txt","w");
	fclose(fp);
	fp=fopen("ot.txt","w");
	fclose(fp);
	fp=fopen("ut.txt","w");
	fclose(fp);
}
void verification(){
	//This function will run to verify the values generated for Ri Ci Ai are correct or not
	long double input[320];
	const int p=12;
	long double ri[P+1];
	long double  alpha[P+1][P+1];
	long double a[P+1];
	long double c[P+1];
	long double w[P+1];
	int i;

	FILE *fp=fopen("test.txt","r");
	if(!fp){
		printf(" test.txt file could not be openend \n");
		exit(1);
	}
	for( i=0;i<320;i++){
		//reading 320 samples from the test file
		fscanf(fp," %lf",&input[i]);
	}
	//calcaulate the required parameters
	calculate_ri(input,320,ri);
	calculate_ai(ri,alpha,a);
	calculate_ci(ri,a,c);
	sine_window(c,w);
	printf("Printing Cis values for verification purpose\n");
	printf("c::%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf \n",c[1],c[2],c[3],c[4],c[5],c[6],c[7],c[8],c[9],c[10],c[11],c[12]);
	

}
*/