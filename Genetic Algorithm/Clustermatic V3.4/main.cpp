#include <allegro.h>
#include <math.h>
#include <algorithm>
#include <limits.h>
#include <cstdlib>
#include <ctime>
#include <process.h>
#include <cstdio>
#define PI  3.14159265
#define canli 150
#define caprazlama 185
#define mutations1 15 
#define mutations2 10
#define migration 100
#define boyut canli+caprazlama*6+migration
#define keskat 5000
#define ruletyuzde1 3
#define ruletyuzde2 2
#define co_evo 6
#define gelisme 65
using namespace std;
void init();
void deinit();
int last,sag,sol,ust,alt,dusey;
int mx,my,fl,syc,renk[3],g1[3],rulet2[co_evo+1][2],yontem,bitis;
int generation1[co_evo+1],final;
int randmat[co_evo+1],wait,eski[co_evo+1],markthread[co_evo+1];
BITMAP *buffer,*map,*grafik,*ekle1,*ekle2,*save,*load;
struct asd{
	int x,y,sira;
	double egim;
}data[3][200],ref[3][200],yed[3][200];
struct asddsa{
	int ogul1,ogul2,find;
}mark[co_evo+1][1500];
struct popi{
	int dizi[1500],toplam,kesisme;
}population[co_evo+1][1500]; 

int control()
{
for(int i=1;i<co_evo;i++)
    if(!markthread[i])return 0;
bitis=1;
return 1;
}
void randomize1(void* number)
{
    while(!bitis)
    {
        for(int i=1;i<co_evo;i++)
        randmat[i]=rand();
        wait=1;
    }
_endthread();
}
int randomize(int pnum)
{
    if(final)
    {
        int x=rand();
        return x;
    }    
    while(eski[pnum]==randmat[pnum]);
    eski[pnum]=randmat[pnum];
    return randmat[pnum];
}
int rulet(int pnum)
{
int randrulet,x;
randrulet=randomize(pnum)%(15*(ruletyuzde1+ruletyuzde2)+canli-30);
if(randrulet<=(15*ruletyuzde1)){x=(randrulet%16)+1;  if(x==1)rulet2[pnum][0]++; if(x==16)rulet2[pnum][1]++; return x;}
if(randrulet>(15*ruletyuzde1) && randrulet<=15*(ruletyuzde1+ruletyuzde2)){ x=randrulet-15*(ruletyuzde1-1)+1;  return x;}
x=(randrulet-15*(ruletyuzde1+ruletyuzde2-2)+1); return x;
}
int mesafe(asd a,asd b)
{
	return (int)sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
bool operator<(const asd &a,const asd &b)
{
	return a.egim<b.egim;
}

bool operator<(const popi &a,const popi &b)
{
	return a.toplam<b.toplam;
}

int ccw(asd a,asd b,asd c)
{
	return (c.x-a.x)*(b.y-a.y)-(c.y-a.y)*(b.x-a.x)>0;
}

char path[100];
void kaydet()
{
	int kayitno=1;
	FILE *savemap;
	while(1)
	{
		sprintf(path,"%d.yis",kayitno);
		if(fopen(path,"r")!=0)
			kayitno++;
		else
		{
			savemap=fopen(path,"w");
			fprintf(savemap,"%d %d\n",g1[1],g1[2]);
			for(int i=1;i<=g1[1];i++)
                fprintf(savemap,"%d %d\n",data[1][i].x,data[1][i].y);
            for(int i=1;i<=g1[2];i++)
                fprintf(savemap,"%d %d\n",data[2][i].x,data[2][i].y);
			allegro_message(" \"%d.yis\" dosyasina kaydedildi",kayitno);
            fclose(savemap);
			return;
		}
	}
	
}
////////////////////////////////////////////////////////////////////////////////

char name[100]={"14.yis"};

////////////////////////////////////////////////////////////////////////////////
void yukle()
{
	FILE *loadmap=fopen(name,"r");
	fscanf(loadmap,"%d %d",&g1[1],&g1[2]);
	for(int j=1;j<=2;j++)
		for(int i=1;i<=g1[j];i++)
    		fscanf(loadmap,"%d %d\n",&data[j][i].x,&data[j][i].y);
    fclose(loadmap);
}
int ccw2(int k,int pnum)//This Function Find Chromosomes Bad Genes(Ýntersection)
{
int toplamkes=0,i,j,t,c,grupno1,grupno2;
    for(int m=0;m<=g1[1]+g1[2];m++)
            for(int a=m+2;a<=g1[1]+g1[2];a++)
                {
                grupno1=2;
                grupno2=2;
                i=m;
                j=m+1;
                t=a;
                c=a+1;
                if(!m)
                    {
                        i=1;
                        j=g1[1];
                    }
                if(m==g1[1])break;
                if(a==g1[1])continue;
                if(a==g1[1]+g1[2])c=g1[1]+1;
                if(c==i)continue;
                if(j==c)continue;
                if(i<g1[1])grupno1=1;
                if(t<g1[1])grupno2=1;
                    if(ccw(data[grupno1][population[pnum][k].dizi[i]],data[grupno1][population[pnum][k].dizi[j]],data[grupno2][population[pnum][k].dizi[t]])^ccw(data[grupno1][population[pnum][k].dizi[i]],data[grupno1][population[pnum][k].dizi[j]],data[grupno2][population[pnum][k].dizi[c]]))
                   	if(ccw(data[grupno2][population[pnum][k].dizi[t]],data[grupno2][population[pnum][k].dizi[c]],data[grupno1][population[pnum][k].dizi[i]])^ccw(data[grupno2][population[pnum][k].dizi[t]],data[grupno2][population[pnum][k].dizi[c]],data[grupno1][population[pnum][k].dizi[j]]))
                        toplamkes++;
                }
    return toplamkes;    
}

void test(int j,int pnum)
{
		for(int i=2;i<=g1[1];i++)
        {
			circlefill(buffer,data[1][population[pnum][j].dizi[i]].x,data[1][population[pnum][j].dizi[i]].y,3,makecol(100,100,100));
			line(buffer,data[1][population[pnum][j].dizi[i]].x,data[1][population[pnum][j].dizi[i]].y,data[1][population[pnum][j].dizi[i-1]].x,data[1][population[pnum][j].dizi[i-1]].y,renk[1]);
		}
		line(buffer,data[1][population[pnum][j].dizi[1]].x,data[1][population[pnum][j].dizi[1]].y,data[1][population[pnum][j].dizi[g1[1]]].x,data[1][population[pnum][j].dizi[g1[1]]].y,renk[1]);
		circlefill(buffer,data[1][population[pnum][j].dizi[1]].x,data[1][population[pnum][j].dizi[1]].y,4,makecol(20,255,20));
		
        for(int i=g1[1]+2;i<=g1[1]+g1[2];i++)
        {
			circlefill(buffer,data[2][population[pnum][j].dizi[i]].x,data[2][population[pnum][j].dizi[i]].y,3,makecol(100,100,100));
			line(buffer,data[2][population[pnum][j].dizi[i]].x,data[2][population[pnum][j].dizi[i]].y,data[2][population[pnum][j].dizi[i-1]].x,data[2][population[pnum][j].dizi[i-1]].y,renk[2]);
		}
		line(buffer,data[2][population[pnum][j].dizi[g1[1]+1]].x,data[2][population[pnum][j].dizi[g1[1]+1]].y,data[2][population[pnum][j].dizi[g1[1]+g1[2]]].x,data[2][population[pnum][j].dizi[g1[1]+g1[2]]].y,renk[2]);
		circlefill(buffer,data[2][population[pnum][j].dizi[g1[1]+1]].x,data[2][population[pnum][j].dizi[g1[1]+1]].y,4,makecol(20,255,20));
}
int maliyet(int k,int pnum)//Cost Function
{
	int toplam3=0,flag=0,kes=0;
        for(int m=1;m<=g1[1]-1;m++)
            toplam3+=mesafe(data[1][population[pnum][k].dizi[m]],data[1][population[pnum][k].dizi[m+1]]);
        toplam3+=mesafe(data[1][population[pnum][k].dizi[1]],data[1][population[pnum][k].dizi[g1[1]]]);
    for(int m=g1[1]+1;m<=g1[1]+g1[2]-1;m++)
    	toplam3+=mesafe(data[2][population[pnum][k].dizi[m]],data[2][population[pnum][k].dizi[m+1]]);
    toplam3+=mesafe(data[2][population[pnum][k].dizi[g1[1]+1]],data[2][population[pnum][k].dizi[g1[2]+g1[1]]]);    
            kes=ccw2(k,pnum);   
            toplam3+=keskat*kes;
            population[pnum][k].kesisme=kes;
        return toplam3;
}
void mutation1(int pnum)//if improve the fitness do mutation
{
int mutrand,rast1,rast2,maliyet1,maliyet2,p,m=0,grup;
for(int i=1;i<=mutations1;i++)
            {
                grup=randomize(pnum)%2+1;
                if(g1[2]==2)grup=1;
                mutrand=rulet(pnum);         
                do{
					rast1=randomize(pnum)%g1[grup]+1;
                	rast2=randomize(pnum)%g1[grup]+1;
					}while(rast1==rast2);
				if(grup==2)
                {
                    rast1+=g1[1];
                    rast2+=g1[1];
                }
                maliyet1=population[pnum][mutrand].toplam;
                swap(population[pnum][mutrand].dizi[rast1],population[pnum][mutrand].dizi[rast2]);
            	maliyet2=maliyet(mutrand,pnum);
				if(maliyet1>maliyet2)
					{
                        population[pnum][mutrand].toplam=maliyet2; m=0;
                    }
				else
					{
                        swap(population[pnum][mutrand].dizi[rast1],population[pnum][mutrand].dizi[rast2]);
                        i--;
                        m++;
                        if(m>25){i++; m=0;}
                    }            
            }
}
void mutation2(int pnum)//Random Mutation
{
int mutrand,rast1,rast2,grup;
for(int i=1;i<=mutations2;i++)
            {
                grup=randomize(pnum)%2+1;
                if(g1[2]==2)grup=1;
                mutrand=randomize(pnum)%canli+1;         
                do{
				    rast1=randomize(pnum)%g1[grup]+1;
                    rast2=randomize(pnum)%g1[grup]+1;
				  }while(rast1==rast2);
				
                if(grup==2)
                    {
                        rast1+=g1[1];
                        rast2+=g1[1];
                    }
                swap(population[pnum][mutrand].dizi[rast1],population[pnum][mutrand].dizi[rast2]);
            }
}
void randgen(int pnum)//First Population Create Function
{
    int random;
    for(int j=1;j<=canli;j++)
        for(int i=1;i<=g1[1];i++)
        {
            random=randomize(pnum)%g1[1]+1;
            if(!population[pnum][j].dizi[random])
				population[pnum][j].dizi[random]=i;
            else i--;
        }
        
    for(int j=1;j<=canli;j++)
        for(int i=1;i<=g1[2];i++)
        {
            random=(randomize(pnum)%g1[2]+1)+g1[1];
            if(!population[pnum][j].dizi[random])
				population[pnum][j].dizi[random]=i;
            else i--;
        }
}
void eleme(int pnum)//Natural Selection
{
    int m=boyut;
    for(int j=canli+1;j<=m;j++)
        {   
            population[pnum][j].toplam=0;
            population[pnum][j].kesisme=0;
            for(int i=1;i<=g1[1]+g1[2];i++)
                population[pnum][j].dizi[i]=0;
        }
}
void randekle(int pnum)//Migration Function
{            
    int random1,m=(canli+migration);
	for(int j=canli+1;j<=m;j++)
        for(int i=1;i<=g1[1];i++)
        {
            random1=randomize(pnum)%g1[1]+1;
            if(!population[pnum][j].dizi[random1])
				population[pnum][j].dizi[random1]=i;
            else i--;
        }
    
    for(int j=canli+1;j<=m;j++)
        for(int i=1;i<=g1[2];i++)
        {
            random1=(randomize(pnum)%g1[2]+1)+g1[1];
            if(!population[pnum][j].dizi[random1])
				population[pnum][j].dizi[random1]=i;
            else i--;
        }
}
void sirala(int pnum)//Sort Population to Their Fitness
{
	int toplam2,tum=boyut;
    for(int a=1;a<=tum;a++)      
        population[pnum][a].toplam=maliyet(a,pnum);
	sort(population[pnum]+1,population[pnum]+tum);
}
void caprazla(int pnum)//Two Point Crossover
{
int syc1=0,syc2=0,a=canli+migration;
int  ata1,ata2,bol1,bol2;
            for(int i=1;i<=caprazlama;i++)
        {
            for(int j=1;j<=g1[1]+g1[2];j++)
    		{
    			mark[pnum][j].ogul1=0;
    			mark[pnum][j].ogul2=0;
    		}
            ata1=randomize(pnum)%a+1;
			do
			{
			ata2=randomize(pnum)%a+1;
            }while(ata1==ata2);
            bol1=randomize(pnum)%(g1[1]-1)+1;
            for(int j=1;j<=bol1;j++)
                {
                	population[pnum][a+i*6-5].dizi[j]=population[pnum][ata1].dizi[j];
					population[pnum][a+i*6-4].dizi[j]=population[pnum][ata2].dizi[j];
                    population[pnum][a+i*6-3].dizi[j]=population[pnum][ata1].dizi[j];
					population[pnum][a+i*6-2].dizi[j]=population[pnum][ata2].dizi[j];
                	mark[pnum][population[pnum][a+i*6-5].dizi[j]].ogul1=1;
					mark[pnum][population[pnum][a+i*6-4].dizi[j]].ogul2=1;
				}
			syc1=bol1;
    		syc2=bol1;
    		for(int j=1;j<=g1[1];j++)
    		{     
				if(!mark[pnum][population[pnum][ata2].dizi[j]].ogul1)
					{
						population[pnum][a+i*6-5].dizi[++syc1]=population[pnum][ata2].dizi[j];
						population[pnum][a+i*6-3].dizi[syc1]=population[pnum][ata2].dizi[j];
						mark[pnum][population[pnum][ata2].dizi[j]].ogul1=1;
					}
					
				if(!mark[pnum][population[pnum][ata1].dizi[j]].ogul2)
					{
						population[pnum][a+i*6-4].dizi[++syc2]=population[pnum][ata1].dizi[j];
						population[pnum][a+i*6-2].dizi[syc2]=population[pnum][ata1].dizi[j];
                        mark[pnum][population[pnum][ata1].dizi[j]].ogul2=1;
                    }
			}
			
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
            bol2=g1[1]+(randomize(pnum)%(g1[2]-1)+1);
            
            for(int j=1;j<=g1[1]+g1[2];j++)
        		{
        			mark[pnum][j].ogul1=0;
        			mark[pnum][j].ogul2=0;
        		}
        
            for(int j=g1[1]+1;j<=bol2;j++)
                {
                	population[pnum][a+i*6-5].dizi[j]=population[pnum][ata1].dizi[j];
					population[pnum][a+i*6-4].dizi[j]=population[pnum][ata2].dizi[j];
                    population[pnum][a+i*6-3].dizi[j]=population[pnum][ata2].dizi[j];
					population[pnum][a+i*6-2].dizi[j]=population[pnum][ata1].dizi[j];
                	mark[pnum][population[pnum][a+i*6-5].dizi[j]].ogul1=1;
					mark[pnum][population[pnum][a+i*6-4].dizi[j]].ogul2=1;
				}
			syc1=bol2;
    		syc2=bol2;
    		for(int j=g1[1]+1;j<=g1[1]+g1[2];j++)
    		{     
				if(!mark[pnum][population[pnum][ata2].dizi[j]].ogul1)
					{
						population[pnum][a+i*6-5].dizi[++syc1]=population[pnum][ata2].dizi[j];
						population[pnum][a+i*6-2].dizi[syc1]=population[pnum][ata2].dizi[j];
						mark[pnum][population[pnum][ata2].dizi[j]].ogul1=1;
					}
					
				if(!mark[pnum][population[pnum][ata1].dizi[j]].ogul2)
					{
						population[pnum][a+i*6-4].dizi[++syc2]=population[pnum][ata1].dizi[j];
						population[pnum][a+i*6-3].dizi[syc2]=population[pnum][ata1].dizi[j];
                        mark[pnum][population[pnum][ata1].dizi[j]].ogul2=1;
                    }
			}
		for(int b=1;b<=g1[1];b++)
		{
		  population[pnum][a+i*6-1].dizi[b]=population[pnum][ata1].dizi[b];
          population[pnum][a+i*6].dizi[b]=population[pnum][ata2].dizi[b];
        }
        
        for(int b=g1[1]+1;b<=g1[2]+g1[1];b++)
		{
		  population[pnum][a+i*6-1].dizi[b]=population[pnum][ata2].dizi[b];
          population[pnum][a+i*6].dizi[b]=population[pnum][ata1].dizi[b];
        }
         /*
         if(pnum==2)
            {
        for(int m=1;m<=g1[1];m++)
         textprintf_ex(buffer,font,15,m*25,makecol(10,10,10),-1,"%d %d | %d %d %d %d %d %d",population[pnum][ata1].dizi[m],population[pnum][ata2].dizi[m],population[pnum][a+i*6-5].dizi[m],population[pnum][a+i*6-4].dizi[m],population[pnum][a+i*6-3].dizi[m],population[pnum][a+i*6-2].dizi[m],population[pnum][a+i*6-1].dizi[m],population[pnum][a+i*6].dizi[m]);
         for(int m=g1[1]+1;m<=g1[2]+g1[1];m++)
         textprintf_ex(buffer,font,15,(m+1)*25,makecol(10,10,10),-1,"%d %d | %d %d %d %d %d %d",population[pnum][ata1].dizi[m],population[pnum][ata2].dizi[m],population[pnum][a+i*6-5].dizi[m],population[pnum][a+i*6-4].dizi[m],population[pnum][a+i*6-3].dizi[m],population[pnum][a+i*6-2].dizi[m],population[pnum][a+i*6-1].dizi[m],population[pnum][a+i*6].dizi[m]);
         draw_sprite(screen,buffer,0,0);
         allegro_message("bol1:%d bol2:%d ata1:%d ata2:%d",bol1,bol2-g1[1],ata1,ata2); 
         clear_to_color(buffer,makecol(255,255,255));
            }*/ 
        }
}
void randson()
{
for(int i=1;i<co_evo;i++)
    for(int j=(i-1)*30+1;j<=i*30;j++)
            population[co_evo][j]=population[i][j-(i-1)*30];
}
void genetic(void* number)//Algorithm
{
    int pnum = *(int*)number;
    randgen(pnum);
    
    while(generation1[pnum]<gelisme)
    {
        generation1[pnum]++;
        randekle(pnum);
        mutation1(pnum);
        caprazla(pnum);
        mutation2(pnum);
        sirala(pnum);
        eleme(pnum);
    }
    markthread[pnum]=1;
    _endthread();
}
void genetic2()
{
    int pnum=co_evo;
    final=1;
    if(yontem==1)
    randson();
    while(!key[KEY_ESC])
    {
		generation1[pnum]++;
        randekle(pnum);
        mutation1(pnum);
        caprazla(pnum);
        mutation2(pnum);
        sirala(pnum);
        eleme(pnum);
        clear_to_color(buffer,makecol(255,255,255));
	    textprintf_ex(buffer,font,10,10,makecol(10,10,10),-1,"Generation:%d Cost:%d  Point:%d  Kesisme:%d  Process Number:Son Gelisim",generation1[co_evo],population[pnum][1].toplam,g1[1]+g1[2],population[pnum][1].kesisme);
        test(1,pnum);
        draw_sprite(screen,buffer,0,0);
    }
}
double mutlak(double a)
{
	if(a>=0)
		return a;
	return (-1)*a;
}
void kumelematik()
{
	for(int i=1;i<=g1[1];i++)
		data[1][i].sira=i;
	for(int i=1;i<=g1[2];i++)
		data[2][i].sira=i;
	for(int t=1;t<=canli;t++)//n
	{
		for(int i=1;i<=g1[1];i++)
			ref[1][i]=data[1][i];
		for(int i=1;i<=g1[2];i++)
			ref[2][i]=data[2][i];
		for(int i=1;i<=g1[1];i++)
			ref[1][i].egim=atan2(ref[1][t%g1[1]+1].y-ref[1][i].y,ref[1][t%g1[1]+1].x-ref[1][i].x);
		swap(ref[1][t%g1[1]+1],ref[1][1]);
		sort(ref[1]+2,ref[1]+g1[1]+1);//nlogn
			for(int i=1;i<=g1[2];i++)
				ref[2][i].egim=atan2(ref[2][t%g1[2]+1].y-ref[2][i].y,ref[2][t%g1[2]+1].x-ref[2][i].x);
			swap(ref[2][t%g1[2]+1],ref[2][1]);
			sort(ref[2]+2,ref[2]+g1[2]+1);
			ref[1][g1[1]+1]=ref[1][1];
			ref[2][g1[2]+1]=ref[2][1];
			for(int i=1;i<=g1[1];i++)
				population[co_evo][t].dizi[i]=ref[1][i].sira;
			for(int i=g1[1]+1;i<=g1[2]+g1[1];i++)
				population[co_evo][t].dizi[i]=ref[2][i-g1[1]].sira;
		}
}
int gr2()
{
	if(ust-alt<0)
	{
		ust+=5;
		return 0;
	}
	return ust-alt;
}

void safkumelematik();
int main(int argc, char *argv[]) 
{
    srand(time(NULL));
    init();
    int tempNum[15];
    ekle1=load_bitmap("ResimEkle1.bmp",0);
	ekle2=load_bitmap("ResimEkle2.bmp",0);
	save=load_bitmap("save.bmp",0);
	load=load_bitmap("load.bmp",0);
    buffer=create_bitmap(800,600);
    map=create_bitmap(800,600);
    grafik=create_bitmap(2400,1800);
    clear_to_color(grafik,makecol(200,200,200));
 	clear_to_color(buffer,makecol(255,255,255));
    last=grafik->h;
    renk[1]=makecol(255,0,0);
   	renk[2]=makecol(0,0,255);
    draw_sprite(buffer,load,700,10);
	draw_sprite(buffer,save,750,10);
	draw_sprite(screen,buffer,0,0);
	
    while (!key[KEY_ESC]) 
    {
        for(int grup=1;grup<=2;grup++)
    	{
            allegro_message("%d'inci grubu giriniz",grup);
            syc=0;
            while(!key[KEY_SPACE])
            {
            	
				if(mouse_b&1 && !fl)
                {
            		fl=1;
                    if(mouse_x<740 && mouse_x>700 && mouse_y>10 && mouse_y<50)
    				{
    					yukle();
    					for(int j=1;j<=2;j++)
    						for(int i=1;i<=g1[j];i++)
    							circlefill(buffer,data[j][i].x,data[j][i].y,3,renk[j]);
    					draw_sprite(screen,buffer,0,0);
    					continue;
    				}
    				if(mouse_x<790 && mouse_x>750 && mouse_y>10 && mouse_y<50)
    				{
    					kaydet();
    					continue;
    				}
                    g1[grup]++;
                    syc++;
                    mx=mouse_x;
                    my=mouse_y;
            		data[grup][syc].x=mx;
            		data[grup][syc].y=my;
            		circlefill(buffer,mx,my,3,renk[grup]);
                    draw_sprite(screen,buffer,0,0);
                }
            	if(!(mouse_b&1))
					fl=0;
			}
		    
        }
		//yontem=2;
		rectfill(buffer,350,0,450,50,makecol(255,0,0));
		rectfill(buffer,450,0,550,50,makecol(0,0,255));
		rectfill(buffer,550,0,650,50,makecol(0,255,0));
		draw_sprite(screen,buffer,0,0);
		while(1)
		{
			if((mouse_b&1))
			{
				if(mouse_x<450 && mouse_y>0 && mouse_y<50)
				{	
					yontem=1;
					allegro_message("Yontem %d'i Sectiniz",yontem);
					break;
				}
				if(mouse_x>450 && mouse_x<550 && mouse_y<50)
				{
					yontem=2;
					allegro_message("Yontem %d'i Sectiniz",yontem);
                    break;
				}
				if(mouse_x>550 && mouse_x<650 && mouse_y<50)
				{
					yontem=3;
					allegro_message("Yontem %d 'i Sectiniz",yontem);
					break;
				}
			}
		}
		if(yontem==1)
			{
				_beginthread(randomize1,0,0);
                while(wait);
                for(int i=1;i<co_evo;i++)
				{
					tempNum[i] = i;
			    	_beginthread( genetic, 0, (void*)&tempNum[i]);//Begin
				}
				
                while(!control())rest(20);
                allegro_message("genetic bitti");
                for(int pnum=1;pnum<co_evo;pnum++)
	        	{
	                clear_to_color(buffer,makecol(255,255,255));
					textprintf_ex(buffer,font,10,10,makecol(10,10,10),-1,"Generation: %d  Cost: %d  Point: %d Kesisme:%d Process Number:%d",generation1[pnum],population[pnum][1].toplam,g1[1]+g1[2],population[pnum][1].kesisme,pnum);
	                test(1,pnum);
	                draw_sprite(screen,buffer,0,0);
					allegro_message("Process Number:%d",pnum);
	            }
			genetic2();
            }
	    if(yontem==2)
            {
                kumelematik();
                genetic2();
            }
        if(yontem==3)
			safkumelematik();
		
		allegro_message("Program Calismayi Bitirdi");
        deinit();
    	return 0;
	    }
}
END_OF_MAIN()
void safkumelematik()
{
	int uz[3],oran=0;
	int Min=INT_MAX,graph_g1=0,Max;
	clear_to_color(buffer,makecol(255,255,255));
	clear_to_color(map,makecol(255,255,255));
    for(int t=1;t<=g1[1];t++)//n
	{
		for(int i=1;i<=g1[1];i++)
			ref[1][i]=data[1][i];
		for(int i=1;i<=g1[2];i++)
			ref[2][i]=data[2][i];
		for(int i=1;i<=g1[1];i++)
		{
			circlefill(map,ref[1][i].x,ref[1][i].y,3,renk[1]);
			ref[1][i].egim=atan2(ref[1][t].y-ref[1][i].y,ref[1][t].x-ref[1][i].x);
		}
		swap(ref[1][t],ref[1][1]);
		sort(ref[1]+2,ref[1]+g1[1]+1);//nlogn
		for(int i=2;i<=g1[1];i++)
			if(mutlak(ref[1][i-1].egim*180/PI - ref[1][i].egim*180/PI)>180)
			{
				goto asd;
			}
		circlefill(map,ref[1][1].x,ref[1][1].y,3,makecol(0,255,0));//yesil
		for(int i=2;i<=g1[1];i++)
			line(map,ref[1][i-1].x,ref[1][i-1].y,ref[1][i].x,ref[1][i].y,renk[1]);
		line(map,ref[1][g1[1]].x,ref[1][g1[1]].y,ref[1][1].x,ref[1][1].y,renk[1]);
		for(int j=1;j<=g1[2];j++)
		{
			draw_sprite(buffer,map,0,0);
			for(int i=1;i<=g1[2];i++)
			{
				circlefill(buffer,ref[2][i].x,ref[2][i].y,3,renk[2]);
				ref[2][i].egim=atan2(ref[2][j].y-ref[2][i].y,ref[2][j].x-ref[2][i].x);
			}
			swap(ref[2][j],ref[2][1]);
			sort(ref[2]+2,ref[2]+g1[2]+1);
			circlefill(buffer,ref[2][1].x,ref[2][1].y,3,makecol(0,255,0));//yesil
			for(int i=2;i<=g1[2];i++)
				if(mutlak(ref[2][i-1].egim*180/PI-ref[2][i].egim*180/PI)>180)
				{
					goto qwe;
				}
			for(int i=2;i<=g1[2];i++)
			{
				line(buffer,ref[2][i-1].x,ref[2][i-1].y,ref[2][i].x,ref[2][i].y,renk[2]);
			}
			line(buffer,ref[2][g1[2]].x,ref[2][g1[2]].y,ref[2][1].x,ref[2][1].y,makecol(0,0,0));
			ref[1][g1[1]+1]=ref[1][1];
			ref[2][g1[2]+1]=ref[2][1];
			for(int r=1;r<=g1[1];r++)
				for(int t=1;t<=g1[2];t++)
					if(ccw(ref[1][r],ref[1][r+1],ref[2][t])^ccw(ref[1][r],ref[1][r+1],ref[2][t+1]))
						if(ccw(ref[2][t],ref[2][t+1],ref[1][r])^ccw(ref[2][t],ref[2][t+1],ref[1][r+1]))
							goto qwe;
			draw_sprite(screen,buffer,0,0);
			uz[1]=0;
			uz[2]=0;
			for(int i=1;i<=g1[1];i++)
				uz[1]+=mesafe(ref[1][i],ref[1][i+1]);
			for(int i=1;i<=g1[2];i++)
				uz[2]+=mesafe(ref[2][i],ref[2][i+1]);
			if(oran==0)
				oran=(int)(uz[1]+uz[2])/300;
			circlefill(grafik,graph_g1+10,grafik->h-(int)((uz[1]+uz[2])/oran),3,makecol(10,10,10));
			line(grafik,graph_g1,last,graph_g1+10,grafik->h-(int)((uz[1]+uz[2])/oran),makecol(10,10,10));
			graph_g1+=10;
			last=grafik->h-(int)((uz[1]+uz[2])/oran);
            //rest(1000);
			if(Min>uz[1]+uz[2])
				{
					Min=uz[1]+uz[2];
					for(int i=1;i<=g1[1];i++)
						yed[1][i]=ref[1][i];
					for(int i=1;i<=g1[2];i++)
						yed[2][i]=ref[2][i];
				}
			if(Max<uz[1]+uz[2])
				Max=uz[1]+uz[2];
			if(key[KEY_G])
			{
				if(graph_g1>500)
					draw_sprite(screen,grafik,500-(graph_g1),-1536);
				else
					draw_sprite(screen,grafik,0,-1536);
				while(key[KEY_G])
				{
				}
			}
			qwe:;
			clear_to_color(buffer,makecol(255,255,255));
		}
		asd:;
		clear_to_color(map,makecol(255,255,255));
	}
	if(Min!=INT_MAX)
	{
		for(int t=1;t<3;t++)
		{
			circlefill(buffer,yed[t][g1[t]].x,yed[t][g1[t]].y,4,renk[t]);
			for(int i=1;i<g1[t];i++)
			{
 				circlefill(buffer,yed[t][i].x,yed[t][i].y,4,renk[t]);
				line(buffer,yed[t][i].x,yed[t][i].y,yed[t][i+1].x,yed[t][i+1].y,renk[t]);
			}
			line(buffer,yed[t][g1[t]].x,yed[t][g1[t]].y,yed[t][1].x,yed[t][1].y,renk[t]);
			circlefill(buffer,yed[t][1].x,yed[t][1].y,7,makecol(0,255,0));
		}
	}
	else
	   allegro_message("Sonuc yok!");
	draw_sprite(screen,buffer,0,0);
	while(!key[KEY_ESC])
	{
		if(key[KEY_G])
		{
			circlefill(grafik,graph_g1+10,grafik->h-(int)((Min)/oran),5,makecol(50,255,50));
			line(grafik,graph_g1,last,graph_g1+10,grafik->h-(int)((Min)/oran),makecol(50,255,50));
			line(grafik,0,grafik->h-(int)((Min)/oran),graph_g1+10,grafik->h-(int)((Min)/oran),makecol(50,255,50));
			line(grafik,0,grafik->h-(int)((Max)/oran),graph_g1+10,grafik->h-(int)((Max)/oran),makecol(50,255,50));
			if(key[KEY_LEFT])
				sol+=5;
			if(key[KEY_RIGHT])
				sag+=5;
			if(key[KEY_UP])
				ust+=5;
			if(key[KEY_DOWN])
				alt+=5;
			dusey=gr2();
			if((500-(graph_g1)+sol-sag)<=0)
				draw_sprite(screen,grafik,500-(graph_g1)+sol-sag,768+dusey-grafik->h);
			else
			{
				draw_sprite(screen,grafik,0,768+dusey-grafik->h);
				sol-=5;
			}
		}
		else
		{
			sol=0;
			sag=0;
			ust=0;
			alt=0;
		//	draw_sprite(buffer,ekle1,0,0);
			//draw_sprite(buffer,ekle2,40,0);
		//	draw_sprite(screen,buffer,0,0);
			
		}
	}
	
}
void init() { 
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
	clear_to_color(screen,makecol(255,255,255));
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}

	install_timer();
	install_keyboard();
	install_mouse();
	show_mouse(screen);
	/* add other initializations here */
}
void deinit() {
	clear_keybuf();
	/* add other deinitializations here */
}
