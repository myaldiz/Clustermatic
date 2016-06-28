#include <allegro.h>
#include <time.h>
#include <cstdio>
#include <algorithm>
#include <math.h>
#include <climits>
#include <stack>
#define kmeans 4
#define canli 100
#define migration 50
#define caprazlama 145
#define mutation1 3
#define mutation2 45
#define Devam 50
#define puanyont 4
#define MGS kmeans+2
#define pb push
#define yukle12 0
#define aax 450
#define aay 300
using namespace std;
void init();
void deinit();
BITMAP *buffer;
struct asd{
	int x,y,renk;
	double egim;
}data[250],merkez[150],kayitci[250],kamil[MGS][250],a,b,c,once;

int mesafe(asd a,asd b)
{
	return (int)sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
bool ccw(asd a,asd b,asd c)
{
	return (c.x-a.x)*(b.y-a.y)-(c.y-a.y)*(b.x-a.x)>0;
}
bool operator<(const asd &a,const asd &b)
{
	return a.egim<b.egim;	
}
struct wer{
    int x,y,sayi;
}ort[100];
int colorspace[MGS];
struct popi{
	int dizi[250];
    long int toplam;
}population[1250]; 

bool operator<(const popi &a,const popi &b)
{
	return a.toplam<b.toplam;
}
stack <asd > s;
int grup,fl,point,mx,my,m1,m2,generation,Minx[MGS],Miny[MGS],index[MGS],lastdot[MGS];
int baslangic[300],onceki;
int rangen()
{
    int asd,flag[150];
    for(int j=1;j<=canli;j++)
        {
            for(int i=1;i<=149;i++)
                flag[i]=0;
            for(int i=1;i<=kmeans;i++)
            {
                asd=rand()%point+1;
                if(flag[asd])
                {
                    i--;
                    continue;
                }
                flag[asd]=1;
                population[j].dizi[i]=asd;                
            }
        }    
}
char name[100]={"1.txt"};
void yukle()
{
    FILE *loadmap=fopen(name,"r");
    
	while(! feof(loadmap))
    {
            point++;
    		fscanf(loadmap,"%d,%d\n",&data[point].x,&data[point].y);
    }
    fclose(loadmap);
}
char path[100];
void kaydet()
{
  int kayitno=1;
	FILE *savemap;
	while(1)
	{
		sprintf(path,"cikti%d.yis",kayitno);
		if(fopen(path,"r")!=0)
			kayitno++;
		else
		{
		savemap=fopen(path,"w");
		for(int j=1;j<=kmeans;j++)
		{
            for(int i=1;i<=point;i++)
		    {
                if(kayitci[i].renk==j)
                    fprintf(savemap,"%d,%d\n",kayitci[i].x,kayitci[i].y);
            }
            fprintf(savemap,"0,0\n");
        }
			allegro_message(" \"%d.yis\" dosyasina kaydedildi",kayitno);
            fclose(savemap);
			return;
		}
	}

}
int randekle()
{
    int asd,flag[200];
    for(int j=canli+1;j<=canli+migration;j++)
        {
            for(int i=1;i<=199;i++)
                flag[i]=0;
            for(int i=1;i<=kmeans;i++)
            {
                asd=rand()%point+1;
                if(flag[asd])
                {
                    i--;
                    continue;
                }
                flag[asd]=1;
                population[j].dizi[i]=asd;                
            }
        }    
}

int caprazla()
{
    int flag[200];
    for(int i=1;i<=caprazlama;i++)
    {
        int kese[200];
        for(int j=1;j<=199;j++)
        flag[j]=0;
        int tur1=rand()%(canli+migration)+1,tur2;
        do{
        tur2=rand()%(canli+migration)+1;        
        }
        while(tur1==tur2);
        for(int j=1;j<=kmeans;j++)
        {
            kese[j]=population[tur1].dizi[j];
            kese[j+kmeans]=population[tur2].dizi[j];
        }
        int randtur,x=i*2+canli+migration,syc3=0;
        for(int j=1;j<kmeans*2;j++)
            for(int m=j+1;m<=kmeans*2;m++)
                if(kese[j]==kese[m])
                {
                    flag[j]=2;
                    flag[m]=2;
                    population[x-1].dizi[kmeans-syc3]=kese[j];
                    population[x].dizi[kmeans-syc3]=kese[j];
                    syc3++;
                }      
        int klm=0;
        while(klm!=kmeans-syc3)
        {
            randtur=rand()%(kmeans*2)+1;
            if(flag[randtur]==0)
            {
                flag[randtur]=1;
                klm++;
            }
        }
        int syc1=0,syc2=0;
        for(int j=1;j<=kmeans*2;j++)
        {
            if(flag[j]==1)
            {
                syc1++;
                population[x-1].dizi[syc1]=kese[j];   
            }
            if(flag[j]==0)
            {
                syc2++;
                population[x].dizi[syc2]=kese[j];
            }
        }          
    }   
}

int ualan(asd a,asd b,asd c)
{
	double x1,x2,x3,u;
	x1=sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
	x2=sqrt((c.x-b.x)*(c.x-b.x)+(c.y-b.y)*(c.y-b.y));
	x3=sqrt((a.x-c.x)*(a.x-c.x)+(a.y-c.y)*(a.y-c.y));
	u=(x1+x2+x3)/2;
	return (int)sqrt(u*(u-x1)*(u-x2)*(u-x3));
}

int maliyet(int sira,int draw)
{
    for(int i=1;i<=kmeans;i++)
            merkez[i]=data[population[sira].dizi[i]];
    int tekrar=1;
    while(tekrar)
    {    
        for(int i=1;i<=point;i++)
            {
                int last=1,lastuz=INT_MAX;
                data[i].renk=0;
                for(int j=1;j<=kmeans;j++)
                    {
                        int berk=mesafe(data[i],merkez[j]);
                        if(berk<lastuz)
                        {
                            lastuz=berk;
                            last=j;
                        }
                    } 
                data[i].renk=last;  
            }
        for(int j=1;j<=kmeans;j++)
            {
                int mfo=0;//=point*100;
                ort[j].x=aax*mfo;
                ort[j].y=aay*mfo;
                ort[j].sayi=mfo;
            }
        for(int i=1;i<=point;i++)
            {
                ort[data[i].renk].x+=data[i].x;
                ort[data[i].renk].y+=data[i].y;
                ort[data[i].renk].sayi++;
            }
        int x1,y1,mark[100];
        for(int i=1;i<=kmeans;i++)
            mark[i]=0;
        for(int j=1;j<=kmeans;j++)
            {
                if(ort[j].sayi==0)ort[j].sayi=1;
                x1=ort[j].x/ort[j].sayi;
                y1=ort[j].y/ort[j].sayi;
                if(merkez[j].x==x1 && merkez[j].y==y1)
                    mark[j]=1; 
                merkez[j].x=x1;
                merkez[j].y=y1;
            }
        tekrar=0;
        for(int i=1;i<=kmeans;i++)
            if(!mark[i])tekrar=1; 
        
    }
    population[sira].toplam=0;
int t1=0,t2=0,t3=0;
if(puanyont==1)
    for(int i=1;i<point;i++)
        for(int j=i+1;j<=point;j++)
        if(data[i].renk==data[j].renk)
            t1+=mesafe(data[i],data[j]);
if(puanyont==4)
    for(int i=1;i<=point;i++)
        t1+=mesafe(merkez[data[i].renk],data[i]);
	if(puanyont==2 || puanyont==3)
    {
    //////////////////////////////////////////////////
    	for(int i=1;i<=kmeans;i++)
    	{
			Minx[i]=0;
    		Miny[i]=0;
    		lastdot[i]=0;
		}
    //	clear_to_color(buffer,makecol(255,255,255));
		for(int i=1;i<point;i++)
		{
		//	circlefill(buffer,data[i].x,data[i].y,3,makecol(0,0,0));
			kamil[data[i].renk][lastdot[data[i].renk]].x=data[i].x;
			kamil[data[i].renk][lastdot[data[i].renk]].y=data[i].y;
			kamil[data[i].renk][lastdot[data[i].renk]].egim=0;
			if(data[i].y==Miny[data[i].renk])
				if(data[i].x<Minx[data[i].renk])
					{
						Minx[data[i].renk]=data[i].x;
						index[data[i].renk]=lastdot[data[i].renk];
					}
			if(data[i].y>Miny[data[i].renk])
			{
				Miny[data[i].renk]=data[i].y;
				Minx[data[i].renk]=data[i].x;
				index[data[i].renk]=lastdot[data[i].renk];
			}
			lastdot[data[i].renk]++;
		}
		for(int i=1;i<=kmeans;i++)
		{
			swap(kamil[i][0],kamil[i][index[i]]);
			for(int j=1;j<lastdot[i];j++)
			{
				kamil[i][j].egim=atan2((kamil[i][j].y-kamil[i][0].y),(kamil[i][j].x-kamil[i][0].x));
			}
			sort(kamil[i],kamil[i]+lastdot[i]);
			
			for(int j=0;j<lastdot[i];j++)
			{
				s.pb(kamil[i][j]);
				while(s.size()>2)
				{
					c=s.top();s.pop();
					b=s.top();s.pop();
					a=s.top();
					if(ccw(a,b,c))
					{
						s.pb(c);
					}
					else
					{
						s.pb(b);
						s.pb(c);
						break;
					}
				}
			}
			once=kamil[i][0];
			if(puanyont==2)
				while(!s.empty())
				{
					a=s.top();
					s.pop();
			      //line(buffer,a.x,a.y,once.x,once.y,makecol(0,0,255));
					t2+=(int)mesafe(once,a);
					once=a;
				}
			
			if(puanyont==3 && !s.empty())
            {
				
                once=s.top();s.pop();
				while(!s.empty())
					{
						a=s.top();
						s.pop();
						t3+=ualan(kamil[i][0],once,a);
						once=a;
					}
				}
		//	draw_sprite(screen,buffer,0,0);
		}	
	}
//	allegro_message("asdasd");
    //clear_to_color(buffer,makecol(255,255,255));
    //////////////////////////////////////////////////
    
    population[sira].toplam=t1+t2+t3;
    if(sira==1 && draw==1)
        {
            textprintf_ex(buffer,font,10,10,makecol(10,10,10),-1,"Generation:%d Cost:%d  Point:%d",generation,population[sira].toplam,point);
            for(int i=1;i<=point;i++)
            {
                line(buffer,data[i].x,data[i].y,merkez[data[i].renk].x,merkez[data[i].renk].y,colorspace[data[i].renk]);
                circlefill(buffer,data[i].x,data[i].y,3,makecol(255,0,0));
            }        
            for(int i=1;i<=kmeans;i++)
                circlefill(buffer,merkez[i].x,merkez[i].y,5,makecol(0,0,255));
            if(generation==Devam)
            {
            for(int i=1;i<=point;i++)
                kayitci[i]=data[i];
            }
            //circlefill(buffer,450,300,5,makecol(0,255,0));
            draw_sprite(screen,buffer,0,0);
            clear_to_color(buffer,makecol(255,255,255));
        }
    return population[sira].toplam;
}

void mutations1()//Random
{
int top=canli+migration,rand1,rand2,rand3,flag;
    for(int i=1;i<=mutation1;i++)
    {
        rand1=rand()%top+1;
        rand2=rand()%kmeans+1;
        flag=1;
        while(flag)
        {
            rand3=rand()%point+1;
            for(int j=1;j<=kmeans;j++)
            {
                if(population[rand1].dizi[j]==rand3)break;
                else if(j==kmeans)flag=0;
            }
        }
        /*for(int n=1;n<=kmeans;n++)
            textprintf_ex(buffer,font,n*30,30,makecol(10,10,10),-1,"%d ",population[rand1].dizi[n]);
        */
        population[rand1].dizi[rand2]=rand3;
        /*for(int n=1;n<=kmeans;n++)
            textprintf_ex(buffer,font,n*30,60,makecol(10,10,10),-1,"%d ",population[rand1].dizi[n]);
            draw_sprite(screen,buffer,0,0);
            allegro_message("asdasd");
        clear_to_color(buffer,makecol(255,255,255)); 
        */
    }
}

int mutations2()//Yararlý
{
int top=canli+migration+caprazlama*2,rand1,rand2,rand3,flag,top1,top2,yedek;
    for(int i=1;i<=mutation2;i++)
    {
        rand1=rand()%top+1;
        rand2=rand()%kmeans+1;
        flag=1;
        while(flag)
        {
            rand3=rand()%point+1;
            for(int j=1;j<=kmeans;j++)
            {
                if(population[rand1].dizi[j]==rand3)break;
                else if(j==kmeans)flag=0;
            }
        }
        yedek=population[rand1].dizi[rand2];
        top1=maliyet(rand1,0);
        population[rand1].dizi[rand2]=rand3;
        top2=maliyet(rand1,0);
        if(top2>top1)
            population[rand1].dizi[rand2]=yedek;
        
    }
}
void sirala()//Sort Population to Their Fitness 
{
	int tum=canli+migration+caprazlama*2;
    for(int a=1;a<=tum;a++)      
        maliyet(a,1);
	sort(population+1,population+tum);
	/*if(onceki<population[1].toplam)
		allegro_message("%lf %lf",onceki,population[1].toplam);
	onceki=population[1].toplam;
    */
}
void eleme()//Natural Selection
{
    int m=canli+migration+caprazlama*2;
    for(int j=canli+1;j<=m;j++)
        {   
            population[j].toplam=0;
            for(int i=1;i<=kmeans;i++)
                population[j].dizi[i]=0;
        }
}

int main() 
{
	init();
	srand(time(NULL));
	buffer=create_bitmap(900,600);
	clear_to_color(buffer,makecol(255,255,255));
/////////////////////////////////////////////////////////////
if(!yukle12)
    while(!key[KEY_SPACE])
	{            	
		if(mouse_b&1 && !fl)
        {
    		fl=1;
            mx=mouse_x;
            my=mouse_y;
    		data[++point].x=mx;
    		data[point].y=my;
    		circlefill(buffer,mx,my,3,makecol(0,0,0));
            draw_sprite(screen,buffer,0,0);
        }
    	if(!(mouse_b&1))
			fl=0;
	}	
    for(int i=1;i<=kmeans;i++)
        {
            int r,g,b;
            r=rand()%255;
            g=rand()%255;
            b=rand()%255;
            colorspace[i]=makecol(r,g,b);
        }
	//////////////////////
    if(yukle12)
        yukle();
    //////////////////////
    allegro_message("Nokta Girisi Tamamlandi");
	rangen();		
	while (generation<=Devam) {
        generation++;
        randekle();
        mutations1();
        caprazla();
        mutations2();
        sirala();
        eleme();
	}
	kaydet();
	deinit();
	return 0;
}
END_OF_MAIN()

void init() {
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 900, 600, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}
	clear_to_color(screen,makecol(255,255,255));
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
