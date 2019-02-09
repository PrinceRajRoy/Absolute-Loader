# include<stdio.h>
# include<string.h>

void main(){

char ch[90],ch1,ch2;
int i,j=0,k=0,start,counter=0,next,temp=0;
int long a;
FILE *fp,*fo;
fp=fopen("Object.txt","r+");
fo=fopen("Absolute.txt","w+");


if(!fp)
    printf("File Not Found!!!");

else{


//READING HEADER RECORD--------------------------------------------

while(j<2){
    ch1=fgetc(fp);
    if(ch1=='^')
        j++;
}

while(ch1=fgetc(fp)=='0');

fseek(fp,-1,SEEK_CUR);


//READING THE STARTING ADDRESS-------------------------------------

fscanf(fp,"%[^^]s",ch);

start = strtol(ch,NULL,16);

i=0;

while(i<start){

    if(i>0)
    fprintf(fo,"\n");
    if(i<16)
    fprintf(fo,"000%0X     ",i);
    else if(i<256)
    fprintf(fo,"00%0X     ",i);
    else if(i<4096)
    fprintf(fo,"0%0X     ",i);
    else
    fprintf(fo,"%0X     ",i);



    j=0;
    while(j<16&&i<start){

    fprintf(fo,"xx");
    if((j+1)%4==0)
        fprintf(fo,"     ");
    j++;
    i++;
    }

}


//fprintf(fo,"%0X",start);


//-----------------------------------------------------------------


fgets(ch,30,fp);
fseek(fp,-1,SEEK_CUR);

//------------------------------------------------------------------


//READING TEXT RECORD-----------------------------------------------

counter = j;
start = start-j;


while(!feof(fp)){

j=0;

while(counter<16){

if(counter%4==0)
    fprintf(fo,"     ");

ch1=fgetc(fp);


if(ch1=='\n'||ch1=='T'||ch1=='^'){

       if(ch1!='^'){

            if(ch1=fgetc(fp)=='E')
            {
                k=1;
                break;
            }


            while(j<3){

            ch1=fgetc(fp);
            if(ch1=='^')
                j++;

            if(j==1){
            fscanf(fp,"%[^^]s",ch);
            next = strtol(ch,NULL,16);
            }

            }

           if(next-start>=16){
           start += counter;

                        while(start<next){

                            while(counter<16&&start<next){

                            fprintf(fo,"xx");
                            if((counter+1)%4==0)
                                fprintf(fo,"     ");
                            counter++;
                            start++;

                            }


                            if(start<next){

                            if(start<16)
                            fprintf(fo,"\n000%0X     ",start);
                            else if(i<256)
                            fprintf(fo,"\n00%0X     ",start);
                            else if(i<4096)
                            fprintf(fo,"\n0%0X     ",start);
                            else
                            fprintf(fo,"\n%0X     ",start);
                            counter=0;

                            }
                        }
start -= counter;
           }
           }


ch1 = fgetc(fp);


}
ch2 = fgetc(fp);

fprintf(fo,"%c%c",ch1,ch2);
counter += (sizeof(ch1)+sizeof(ch2))/2;

}

if(k==1)
    break;

start += counter;

counter = 0;
fprintf(fo,"\n%0X",start);

}

while(counter<16){
    fprintf(fo,"xx");
    if((counter+1)%4==0)
        fprintf(fo,"     ");
    counter++;
}

}

fclose(fp);
fclose(fo);

}
