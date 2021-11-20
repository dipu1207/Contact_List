
#include "stdafx.h"
#include "Preprocess.h"
#include "Lgb.h"
#define T 150
#define N 5
#define M 32
#define total 20
#define Zero 0.000000000000000000000000000001
long double delta[T+1][N],si[T+1][N];
long double a[N][N],b[N][M+1],pi[N],piBar[N],obs[T+1],alpha[T+1][N],beta[T+1][N],zi[T+1][N][N],gamma[T+1][N],aBar[T+1][N],bBar[T+1][N],Pold=0.1,Pnew=0;
long double ga[N][N],gb[N][M+1],gpi[N];
long double parr[10];
long double prob;
int Tdash;//will keep count of number of frames used from current sample file
int count[10]={0};//will keep the count of correct digit wise
char *numToChar[100]={"zero","one","two","three","four","five","six","seven","eight","nine"};
void viturbi(){
	//This function will set values of delta and save P* in Pnew
	//viturbi
	
	//initialization
	//long double a[N][N],b[N][M+1],pi[N],obs[T+1];

		for(int i=0;i<N;i++){
			delta[1][i]=pi[i]*b[i][int(obs[1])];
			si[1][i]=0;
		}
	
	//recursion
	long double tempmax=0,tempval;
	int argmax=-1;

	for(int t=2;t<=Tdash;t++){
		for(int j=0;j<N;j++){
			tempmax=-1;
			for(int i=0;i<N;i++){
				tempval=delta[t-1][i]*a[i][j];
				if(tempval>tempmax){
					tempmax=tempval;
					argmax=i;
				}
			}
			delta[t][j]=tempmax*b[j][int(obs[t])];
			si[t][j]=argmax;
		}
	}
	tempval=0;
	tempmax=0;
	//printf("\n\n\n");
	//for(int t=1;t<=T;t++){
		//printf("t=%d ",t);
		//for(int i=0;i<N;i++){
			//printf("%g ",delta[t][i]);
		//}
		//printf("\n");
	//}
	//termination
	for(int i=0;i<N;i++){
		//printf("%g ",delta[T][i]);
		if(tempmax<delta[Tdash][i])tempmax=delta[Tdash][i];
	}
	//printf("\n");
	Pnew=tempmax;
	//printf("Printing P* %g",tempmax);
	//printf("Printing observation sequence\n");
	for(int t=1;t<=Tdash;t++){
		tempmax=-1;
		for(int i=0;i<N;i++){
			if(tempmax<delta[t][i]){
				tempmax=delta[t][i];
				argmax=i;
			}
		}
	//	printf(" %d",argmax);

	}
	


	
}

void forwardProcedure(){
	// this function will set values of alpha matrix. and set probability in global variable prob
	//Problem1 Forward procedure
	//initialization
	for(int i=0;i<N;i++){
		alpha[1][i]=pi[i]*b[i][int(obs[1])];
	}
	//Induction
	//printf("\n\n");
	long double tempsum;
	for(int t=1;t<Tdash;t++){
	//	printf("t:%d ",t+1);
		for(int j=0;j<N;j++){
			tempsum=0;
			for(int i=0;i<N;i++){
				tempsum+=alpha[t][i]*a[i][j];
			}
			alpha[t+1][j]=tempsum*b[j][int(obs[t+1])];
			//printf(" %g",alpha[t+1][j]);
		}
		//printf("\n");
	}
	tempsum=0;
	for(int i=0;i<N;i++){
		tempsum+=alpha[Tdash][i];
	}
	prob=tempsum;
	//printf("Probability is %g \n",tempsum);
}
void backwardProcedure(){
	//This function will perform backward procedure and set values of beta
	//printf("starting to print beta\n");
	//initialization
	for(int i=0;i<N;i++){
		beta[Tdash][i]=1;
	}
	long double tempsum;
	//printf("start here\n");
	for(int t=Tdash-1;t>0;t--){
		for(int i=0;i<N;i++){
			tempsum=0;
			for(int j=0;j<N;j++){
				tempsum+=a[i][j]*b[j][int(obs[t+1])]*beta[t+1][j];
			////	printf("a %g\n",a[i][j]);
			//	printf("j:%d obs%d\n",j,obs[t+1]);
			//	printf("b %g\n",b[j][int(obs[t+1])]);
			//	printf("tempsum %g \n",tempsum);
			}
			beta[t][i]=tempsum;
			//printf("%g ",beta[t][i]);
			//printf("\n");
		}
		//printf("\n");
	}
	tempsum=0;
	for(int i=0;i<N;i++){
		tempsum+=b[0][i];
	}
//	printf("%g\n",tempsum);


}
void correctB(){
	//this function will make sure that B matrix is stochastic and does not contain any 0's
	int indmax=0,incr_count=0;
	for(int i=0;i<N;i++){
		indmax=0;
		for(int m=1;m<=M;m++){
			if(b[i][m]==0){
				incr_count++;
				b[i][m]=Zero;

			}
			if(b[i][indmax]<b[i][m]){
				indmax=m;
			}
		}
		b[i][indmax]-=(Zero* incr_count);
		//printf("\n");
	
	}
}
void Reestimation(){
	//This function will  calculate Abar , Bbar, and Pibar after reestimation	
	long double tempsum,denomsum,tempsum1,numerator,numeratorB;
	for(int t=1;t<=Tdash-1;t++){
		denomsum=0;
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				denomsum+=alpha[t][i]*a[i][j]*b[j][int(obs[t+1])]*beta[t+1][j];
			}
		}
		//printf("denomsum %g",denomsum);
		for(int i=0;i<N;i++){
			//gamma[t][i]=0;
			for(int j=0;j<N;j++){
				numerator=alpha[t][i]*a[i][j]*b[j][int(obs[t+1])]* beta[t+1][j];
				zi[t][i][j]=numerator/denomsum;
				//gamma[t][i]+=zi[t][i][j];
				//printf("%g ",zi[t][i][j]);
			}
			//printf("\n");
		}
		//printf("\n");
	}
	for(int t=1;t<=Tdash-1;t++){
		for(int i=0;i<N;i++){
			gamma[t][i]=0;
			for(int j=0;j<N;j++){
				gamma[t][i]+=zi[t][i][j];
			}
		}
	}
	for(int t=1;t<=Tdash;t++){
		//printf("t=%d ",t);
		for(int i=0;i<N;i++){
			//printf("%g ",gamma[t][i]);
		}
		//printf("\n");
	}
	//calculating new a matrix and b matrix
	denomsum=0;
	for(int i=0;i<N;i++){
		denomsum=0;
		for(int t=1;t<=Tdash-1;t++){
			denomsum+=gamma[t][i];
		}
		//printf("denomsum %g\n",denomsum);
		numeratorB=0;
		for(int j=0;j<N;j++){
			//printf("denomsum: %g",denomsum);
			numeratorB=0;
			for(int t=1;t<=Tdash-1;t++){
				numeratorB+=zi[t][i][j];
			}
			aBar[i][j]=numeratorB/denomsum;
		}
	}
//	printf("***************************\n");
	long double denominator=0;
	for(int j=0;j<N;j++){
		for(int k=1;k<=M;k++){
			numerator=0;
			denominator=0;
			for(int t=1;t<=Tdash-1;t++){
				denominator+=gamma[t][j];		
			}
			for(int t=1;t<=Tdash-1;t++){
				if(obs[t]==k){
					numerator+=gamma[t][j];
				}
			}
			b[j][k]=(numerator/denominator);
		//	printf("%g ",bBar[j][k]);
		}
		//printf("\n");
	}
	for(int i=0;i<N;i++){
		piBar[i]=gamma[1][i];
	}		

	
	//copying new lambda to old lambda
	//copying a from aBar
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			//coming fine
			a[i][j]=aBar[i][j];
			//printf("%g ",a[i][j]);
		}
		//printf("\n");
	}
	//copying a from abar
	//printf("***********************\n");
	for(int i=0;i<N;i++){
		for(int m=1;m<=M;m++){
				//b[i][m]=bBar[i][m];
				//printf("%g ",bBar[i][m]);
		}
		//	printf("\n");
	}
	//copying pi from pi bar
	for(int i=0;i<N;i++){
		pi[i]=piBar[i];
	}
	//correctB();
	//Pold=Pnew;
}
void addGlobal(){
	//will add values of a, b , pi , matrix to gb, ga, gpi matrix. To calculate average later
	for(int row=0;row<N;row++){
		for(int k=1;k<=M;k++) {
			gb[row][k]+=b[row][k];
		}
	}
	for(int row=0;row<N;row++){
		for(int i=0;i<N;i++){
			ga[row][i]+=a[row][i];
		}
	}
	for(int row=0;row<N;row++){
		gpi[row]+=pi[row];
	}
}
void zeroGlobal(){
	//sets gb,ga,gpi matrix as zero
	for(int row=0;row<N;row++){
		for(int k=1;k<=M;k++) {
			gb[row][k]=0;
		}
	}
	for(int row=0;row<N;row++){
		for(int i=0;i<N;i++){
			ga[row][i]=0;
		}
	}
	for(int row=0;row<N;row++){
		gpi[row]=0;
	}
}
void getAvg(){//calculates average of values of A,B,Pi matrices to calculate average lambda

	for(int row=0;row<N;row++){
		for(int k=1;k<=M;k++) {
			b[row][k]=gb[row][k]/total;
		}
	}
	for(int row=0;row<N;row++){
		for(int i=0;i<N;i++){
			a[row][i]=ga[row][i]/total;
		}
	}
	for(int row=0;row<N;row++){
			pi[row]=gpi[row]/total;
	}

	
}
void printLambda(){
	//prints lambda in console
	printf("\n***********Printing pi****************\n");
	for(int row=0;row<N;row++){
			printf("%g ",pi[row]);
	}
	printf("\n***********Printing A***********\n");
	for(int row=0;row<N;row++){
		for(int i=0;i<N;i++){
			printf("%g ",a[row][i]);
		}
		printf("\n");
	}
	printf("\n***********Printing B***********\n");
	for(int row=0;row<N;row++){
		for(int k=1;k<=M;k++) {
			printf("%g ",b[row][k]);
		}
		printf("\n");
	}
}
void readLambda(char  *fname){
	//reads lambda from the file
	FILE* fp=fopen(fname,"r");
	if(!fp){
		printf("unable to open file for reading lambda\n");
		exit(0);
	}
	fscanf(fp,"***********Printing pi****************\n");
	for(int row=0;row<N;row++){
			fscanf(fp,"%Lf ",&pi[row]);
			//printf("%Lf ",pi[row]);

	}
	fscanf(fp,"\n***********Printing A***********\n");
	for(int row=0;row<N;row++){
		for(int i=0;i<N;i++){
			fscanf(fp,"%Lf",&a[row][i]);
		}
		fscanf(fp,"\n");
	}
	fscanf(fp,"***********Printing B***********\n");
	for(int row=0;row<N;row++){
		for(int k=1;k<=M;k++) {
			fscanf(fp,"%Lf ",&b[row][k]);
		}
		fscanf(fp,"\n");
	}
	fclose(fp);

}
void init_lambda_feedforward(){
	//init lambda as feed forward model
	char fdyna[500];
	sprintf(fdyna,"fa.txt");
	FILE *fp=fopen((const char *)fdyna,"r");

	if(!fp){
		printf("File could not be opened\n");
		perror("File cant be openend\n");
		return;
	}
	char line[1000];
	for(int row=0;row<N;row++){
		fscanf(fp,"%Lf %Lf %Lf %Lf %Lf\n",&a[row][0],&a[row][1],&a[row][2],&a[row][3],&a[row][4]);
		//printf("%Lf %Lf %Lf %Lf %Lf \n",a[row][0],a[row][1],a[row][2],a[row][3],a[row][4]);
	}
	fclose(fp);
	sprintf(fdyna,"fb.txt");
	fp=fopen((const char *)fdyna,"r");
	int ind=0;
	for(int row=0;row<N;row++){
		ind=0;
		for(int k=1;k<=M;k++) {
			fscanf(fp, "%Lf ", &b[row][k]);
		//	printf("%g ", b[row][k]);
			
		}
		printf("\n");
	}
	fclose(fp);
	sprintf(fdyna,"fpi.txt");
	fp=fopen((const char *)fdyna,"r");
	ind=0;
//	printf("Printing pi\n");
	while (fscanf(fp, "%Lf ", &pi[ind++]) ==1) {
		//printf("%Lf ", pi[ind++]);
	}

}

void generateObsSeq(char *fname){
	//will read cepstral coefficient and generate the observation sequence
	FILE *fp=fopen(fname,"r");
	if(!fp){
		printf("File not opened, for generating seq\n");
		exit(0);
	}
	long double cepstral[13];
	//fprintf("%d ",Tdash);
	printf("Printing obsertvation sequence generated\n");
	FILE * wp=fopen("buff.txt","a");
	for(int t=1;t<=Tdash;t++){
		read_values(fp,cepstral); //read the cepstral coeff
		//print_values(cepstral);
		obs[t]=tokhura_wrapper(cepstral,32);//get the nearest centeroid using tokhura dist

		fprintf(wp,"%g ",obs[t]);
	
	}
	fprintf(wp,"\n");
	fclose(wp);
	printf("\n");
}
void saveLambda(char* fname){
	//will save lambda in file named fname
	FILE* fp=fopen(fname,"w");
	fprintf(fp,"***********Printing pi****************\n");
	for(int row=0;row<N;row++){
			fprintf(fp,"%g ",pi[row]);
	}
	fprintf(fp,"\n***********Printing A***********\n");
	for(int row=0;row<N;row++){
		for(int i=0;i<N;i++){
			fprintf(fp,"%g ",a[row][i]);
		}
		fprintf(fp,"\n");
	}
	fprintf(fp,"***********Printing B***********\n");
	for(int row=0;row<N;row++){
		for(int k=1;k<=M;k++) {
			fprintf(fp,"%g ",b[row][k]);
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
}
void write_obs(FILE *fp){
	//will write obs sequence in the file after wiritig length of the obs seq
	if(!fp){
		printf("file could not be opened for writing obs\n");
	}
	
	fprintf(fp,"%d ",Tdash);
	for(int t=1;t<=Tdash;t++)
		{fprintf(fp,"%Lf ",obs[t]);}
	fprintf(fp,"\n");
}
void read_obs(FILE *fp){
	//will read the observation from the file
	
	if(!fp){
		printf("file could not be opened for reading obs\n");
	}

	fscanf(fp,"%d ",&Tdash);
	printf("Tdash is %d\n",Tdash);
	FILE * tfile=fopen("buff.txt","a");
	fprintf(tfile,"%d ",Tdash);
	for(int t=1;t<=Tdash;t++){
		fscanf(fp,"%Lf ",&obs[t]);
		fprintf(tfile,"%d ",int(obs[t]));
	}
	fclose(tfile);

}
void read_file_and_calculate_req(char *filename,char *output,char *mode){
	//Read the initial input from the initial samples files
	//Calculate Dc shift and max amp
	//Normalize the samples and write the values to Normalized.txt file
	//Read Normalized value and sum up consecutive 320 samples to calculate energy of a frame and write in energy.txt
	//Calculate max energy to find frame of the steady part, from the frame no find the line no to read the samples 
	//Calculate the rasied Ci's and write those  rows(one row per frame) into the output file 
	FILE *fp=fopen(filename,"r");//initial input 
	FILE* tfile;
	if(!fp){
		tfile=fopen("buff.txt","a");
			fprintf(tfile,"not opening");
			fclose(tfile);
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
		//read energy of initial 10 frames to caclculate noise energy
		fscanf(fp2,"%lf \n",&read);
		ten=ten-1;
		noise_eng+=read;
	}
	noise_eng/=10;
	//printf("noise energy is %lf\n",noise_eng);
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
		//	printf(" %lf ",read);
			if(read>0.009*max_eng){
				frame_start_line=start_line;
			//	printf("Setting frame start line %d\n",frame_start_line);
				break; 
			}
			start_line++;		
	}
	//printf("max energy:%lf\n",max_eng);
	//printf("third frame start %d\n",third_frame_start);
	//printf(" frame start line %d\n",frame_start_line);
	//printf("\nmax energy frame starts from line %d\n",third_frame_start);
	if((third_frame_start-frame_start_line)>50)
		start_line=(third_frame_start-int(T/2))*80;//we stored the line num of the 3rd frame , to get the line num of 1st frame we subtract 2. We multiply by 320 as all 
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
		fprintf(wp3,"%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n",w[1],w[2],w[3],w[4],w[5],w[6],w[7],w[8],w[9],w[10],w[11],w[12]);//write the calculated Cis after sine raising sine window into the output file
		fsetpos(fp3,&tpos);
	}
	Tdash=frame_length;
	printf("Number of frames used  from recording %d\n",frame_length);
	fclose(fp2);//closing the file pinter 
	fclose(wp3);//close the file pointer
	fclose(fp3);
}
void printMenu(){
	printf("***************Menu***************\n");
	printf("0: To generate codebook again\n");
	printf("1: To generate Lambdas for training samples\n");
	printf("2: To check accuracy on test samples\n");
	printf("3: To test live\n");
	printf("4: Reprint Menu\n");
	printf("5: Exit\n");
}
void createLambda(char *word){
	//this->label1->Text="Recording started";
	char codebook[100]="codebook.txt";
	read_centeroids(codebook);//read the centeroids from the present codebook
	FILE * tfile=fopen("buff.txt","w");
	fprintf(tfile,"h1");
	fclose(tfile);
	int max_run;
	long double tempmax;
	int argmax;
	char oname[100]="out.txt";
	char fname[100];
	char lambdaName1[100];
	char lambdaName[100];
	for(int trial=0;trial<5;trial++){
			tfile=fopen("buff.txt","a");
			fprintf(tfile,"trial%d\n",trial);
			fclose(tfile);
			zeroGlobal();
			FILE* obsfp;
			if(trial==0){
					//for 0th trial generate obse sequence and save in file
					char obsf[100];
					sprintf(obsf,"%sobs.txt",word);
					obsfp=fopen(obsf,"w");//open file to read
			}
			else{
				//for other trial read the already generated sequece ffrom the file
				char obsf[100];
				sprintf(obsf,"%sobs.txt",word);
				obsfp=fopen(obsf,"r");
			}
			for(int i=1;i<=20;i++){
				//iterate over all 20 samples for test files
				tfile=fopen("buff.txt","a");
				fprintf(tfile,"sample%d\n",i);
				fclose(tfile);
				char mode[2]="w";
				tfile=fopen("buff.txt","a");
				fprintf(tfile,"************Reading sample %d for word %s Iteartion %d************ \n",i,word,trial);
				
				fclose(tfile);
				
				if(trial==0){
					sprintf(fname,"training\\%s_%d.txt",word,i);
					//sprintf(fname,"input_file.txt");
					tfile=fopen("buff.txt","a");
				fprintf(tfile,"%s",fname);
				fclose(tfile);
					//this->label1->Text=fname;
					read_file_and_calculate_req(fname,oname,mode);//preprocess the sample file and write the cepstral coeff in a file
					generateObsSeq(oname);//will generate observation seq and save in obs array
					write_obs(obsfp);//write obs into a file
				}
				else{
					read_obs(obsfp);
					//read obs file
				}
				if (trial==0)init_lambda_feedforward();//for initial trial init lambda as feedforward
				else {
					//for other trial read last saved lambda
					sprintf(lambdaName1,"lambda\\%sLambda.txt",word);
					readLambda(lambdaName1);
				}
				//printf("Init lambda\n");
				//printLambda();
				Pold=0;
				Pnew=1;
				tfile=fopen("buff.txt","a");
				fprintf(tfile,"************starting rec************ \n",i,word,trial);
				
				fclose(tfile);
				max_run=300;//will run max for 300 iterations
				while(Pold!=Pnew && max_run){//keep on reestimating until we reach saturation
					//	printf("pold %g pnew %g\n",Pold,Pnew);
						Pold=Pnew;
						viturbi();//performing virturbi 
						forwardProcedure();//performing feedforward procedure
						backwardProcedure();//calculate beta
						Reestimation();//reestimating the value of lambda
						correctB();//keeping B stochastic and making zero values as 10e-30
						max_run=max_run-1;//decrease count of max_run
				}
				tfile=fopen("buff.txt","a");
				fprintf(tfile,"************completed************ \n",i,word,trial);
				
				fclose(tfile);
				printf("Final Prob %g\n",Pnew);
				//printLambda();
				//printGlobal();//printitng the best lambda 
				//at this point we have best lambda for a digit
				addGlobal();//adding the lamba to the global lambda 
			}
			getAvg();
			//printLambda();
			sprintf(lambdaName,"lambda\\%sLambda.txt",word);
			printf("saving lambda for %s\n",lambdaName);
			saveLambda(lambdaName);//save the average lambda in a file
			tfile=fopen("buff.txt","a");
				fprintf(tfile,"************lambda saved************ \n",word,trial);
				
				fclose(tfile);
			fclose(obsfp);
			printLambda();
		
		}
	}
char* getNumber(){
	char bestName[100]="Unknown",bestNumber[100];
	char presName[100],presNumber[100];
	char codebook[100]="codebook.txt";
	read_centeroids(codebook);//read the centeroids from the present codebook
	char oname[100]="out.txt";
	//FILE* fp=fopen(fname,"r");
	FILE* cp=fopen("list.txt","r");
	FILE * tfile;
	tfile=fopen("buff.txt","a");
	fprintf(tfile,"starting detection\n");
	fclose(tfile);
	char iname[100];
	char *mode="w";
	sprintf(iname,"d.txt");
	read_file_and_calculate_req(iname,oname,mode);//preprocess the sample file and write the cepstral coeff in a file
	generateObsSeq(oname);//will generate observation seq and save in obs array
	long double max_p=0;
	int res=0;
	//calculate prob P* for all digits lambdas
	while(!feof(cp)){
		fscanf(cp,"%s\t%s\n",&presName,&presNumber);

		tfile=fopen("buff.txt","a");
		fprintf(tfile,"read %s\t%s",presName,presNumber);
		fclose(tfile);

		//printf("\nStarting testing for tdigit %d \n",tdigit);
		char lambdaName[100];
		sprintf(lambdaName,"lambda\\%sLambda.txt",presName);
		readLambda(lambdaName);//read the laambda for digit
		viturbi();
		forwardProcedure();
		if(prob>max_p){//if probability of present digit is more than the max porb, then make current digit as result
			max_p=prob;
			sprintf(bestName,"%s %s",presName,presNumber);
			sprintf(bestNumber,"%s",presNumber);
		}
		tfile=fopen("buff.txt","a");
		fprintf(tfile,"Probability for recording being digit  %s is %g\n",presName,prob);//print the probability of the digit
		fclose(tfile);
	}
	tfile=fopen("buff.txt","a");
	
	if(max_p)//if max prob is non 0 then print the result
			fprintf(tfile,"**********Result for test:%s*********\n",bestName);	
		else//else print that no digit is matched
			printf("No digit is matched\n");
	fclose(tfile);
	return bestName;
}


/*printf("Generating lambda for training samples\n");
			for(int digit=0;digit<=9;digit++){
				//itearte over all the digits
				for(int trial=0;trial<5;trial++){
					//do this 5 times
					zeroGlobal();//make global lambda zero
					char lambdaName[100],lambdaName1[100];
					FILE* obsfp;
					if(trial==0){
						//for 0th trial generate obse sequence and save in file
						char obsf[100];
						sprintf(obsf,"%sobs.txt",numToChar[digit]);
						obsfp=fopen(obsf,"w");//open file to read
					}
					else{
						//for other trial read the already generated sequece ffrom the file
						char obsf[100];
						sprintf(obsf,"%sobs.txt",numToChar[digit]);
						obsfp=fopen(obsf,"r");
					}
					for(int i=1;i<=20;i++){
						//iterate over all 20 samples for test files
						char mode[2]="w";
						printf("************Reading sample %d for digit %d Iteartion %d************ \n",i,digit,trial);
				
						if(trial==0){
							sprintf(fname,"Training\\%s\\%d.txt",numToChar[digit],i);
							//printf("opening file %s\n",fname);
							read_file_and_calculate_req(fname,oname,mode);//preprocess the sample file and write the cepstral coeff in a file
							generateObsSeq(oname);//will generate observation seq and save in obs array
							write_obs(obsfp);//write obs into a file
							
						}
						else{
							read_obs(obsfp);
							//read obs file
						}
						if (trial==0)init_lambda_feedforward();//for initial trial init lambda as feedforward
						else {
							//for other trial read last saved lambda
							sprintf(lambdaName1,"lambda\\%sLambda.txt",numToChar[digit]);
							readLambda(lambdaName1);
						}
						//printf("Init lambda\n");
						//printLambda();
						Pold=0;
						Pnew=1;
						max_run=300;//will run max for 300 iterations
						while(Pold!=Pnew && max_run){//keep on reestimating until we reach saturation
							//	printf("pold %g pnew %g\n",Pold,Pnew);
								Pold=Pnew;
								viturbi();//performing virturbi 
								forwardProcedure();//performing feedforward procedure
								backwardProcedure();//calculate beta
								Reestimation();//reestimating the value of lambda
								correctB();//keeping B stochastic and making zero values as 10e-30
								max_run=max_run-1;//decrease count of max_run
						}
						printf("Final Prob %g\n",Pnew);
						//printLambda();
						//printGlobal();//printitng the best lambda 
						//at this point we have best lambda for a digit
						addGlobal();//adding the lamba to the global lambda 
					}
					getAvg();
					//printLambda();
					sprintf(lambdaName,"lambda\\%sLambda.txt",numToChar[digit]);
					printf("saving lambda for %s\n",lambdaName);
					saveLambda(lambdaName);//save the average lambda in a file
					fclose(obsfp);
					printLambda();
		
				}
			}?*/