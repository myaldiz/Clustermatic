#include "MyForm.h"
#include <math.h>g
#include <algorithm>
#include <limits.h>
#include <cstdlib>
#include <ctime>
#include <process.h>
#include <cstdio>

using namespace System;
using namespace System::Windows::Forms;
using namespace std;

#define canli 100
#define migration 60
#define caprazlama 155
#define mutations2 3
#define mutations1 50
#define maxmat 100
#define yukle12 0
#define yontem1 1
#define mal1 0


struct asd {
	int x, y, sira;
	double egim;
}gdata[maxmat][maxmat], gref[maxmat][maxmat];

struct popi {
	int dizi[maxmat], toplam;
}population[maxmat][1500];

int fl, mx, my, grup, q, point[maxmat], renk[maxmat], eski[maxmat], randmat[maxmat], bitis, wait, tempNum[maxmat];
int markthread[maxmat], generation[maxmat], flag1, cvp, distance1[maxmat][maxmat];

int mesafe(asd a, asd b)
{
	if (mal1)
		return distance1[a.sira][b.sira];
	else
		return (int)sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}
bool operator<(const popi &a, const popi &b)
{
	return a.toplam<b.toplam;
}

bool operator<(const asd &a, const asd &b)
{
	return a.egim<b.egim;
}

int control()
{
	for (int i = 1; i <= grup; i++)
		if (!markthread[i])return 0;
	return 1;
}
void randomize1(void* number)
{
	while (!bitis)
	{
		for (int i = 1; i <= grup; i++)
			randmat[i] = rand();
		wait = 1;
	}
	_endthread();
}
int randomize(int pnum)
{
	while (eski[pnum] == randmat[pnum]);
	eski[pnum] = randmat[pnum];
	return randmat[pnum];
}

int maliyet(int k, int pnum)//Cost Function
{
	int toplam3 = 0;
	for (int m = 1; m<point[pnum]; m++)
		toplam3 += mesafe(gdata[pnum][population[pnum][k].dizi[m]], gdata[pnum][population[pnum][k].dizi[m + 1]]);
	toplam3 += mesafe(gdata[pnum][population[pnum][k].dizi[point[pnum]]], gdata[pnum][population[pnum][k].dizi[1]]);
	return toplam3;
}

void kumelematik(int pnum)
{
	for (int i = 1; i <= point[pnum]; i++)
		gdata[pnum][i].sira = i;
	for (int t = 1; t <= canli; t++)//n
	{
		for (int i = 1; i <= point[pnum]; i++)
			gref[pnum][i] = gdata[pnum][i];
		for (int i = 1; i <= point[pnum]; i++)
			gref[pnum][i].egim = atan2(gref[pnum][t%point[pnum] + 1].y - gref[pnum][i].y, gref[pnum][t%point[pnum] + 1].x - gref[pnum][i].x);
		swap(gref[pnum][t%point[pnum] + 1], gref[pnum][1]);
		sort(gref[pnum] + 2, gref[pnum] + point[pnum] + 1);//nlogn
		gref[pnum][point[pnum] + 1] = gref[pnum][1];
		for (int i = 1; i <= point[pnum]; i++)
			population[pnum][t].dizi[i] = gref[pnum][i].sira;
	}
}

void randgen(int pnum)//First Population Create Function
{
	int random;
	for (int j = 1; j <= canli; j++)
		for (int i = 1; i <= point[pnum]; i++)
		{
			random = randomize(pnum) % point[pnum] + 1;
			if (!population[pnum][j].dizi[random])
				population[pnum][j].dizi[random] = i;
			else i--;
		}
}
///////////////////////////////

char name[100] = { "cikti1.yis" };

///////////////////////////////
void yukle()
{
	FILE *loadmap = fopen(name, "r");
	int a, b;
	grup = 1;
	while (!feof(loadmap))
	{
		point[grup]++;
		fscanf(loadmap, "%d,%d\n", &a, &b);
		if (a == 0 && b == 0)
		{
			point[grup]--;
			grup++;
		}
		else
		{
			gdata[grup][point[grup]].x = a;
			gdata[grup][point[grup]].y = b;
		}
	}

	grup--;
	fclose(loadmap);
}

void yukle2()
{

	FILE *loadmap = fopen("uzaklik.txt", "r");
	int a, b, m;
	while (!feof(loadmap))
	{
		fscanf(loadmap, "(%d,%d)-->%dm\n", &a, &b, &m);
		distance1[a + 1][b + 1] = m;
	}

	fclose(loadmap);
}

char path[100];
void kaydet()
{
	int kayitno = 1;
	FILE *savemap;
	while (1)
	{
		sprintf(path, "cikti%d.yis", kayitno);
		if (fopen(path, "r") != 0)
			kayitno++;
		else
		{
			savemap = fopen(path, "w");
			for (int j = 1; j <= grup; j++)
			{
				fprintf(savemap, "<group>\n");
				for (int i = 1; i <= point[j]; i++)
					fprintf(savemap, "%d,%d\n", gdata[j][population[j][1].dizi[i]].x, gdata[j][population[j][1].dizi[i]].y);
				fprintf(savemap, "</group>\n");
			}
			printf(" \"%d.yis\" dosyasina kaydedildi", kayitno);
			fclose(savemap);
			return;
		}
	}

}

void randekle(int pnum)//First Population Create Function
{
	int random;
	for (int j = canli + 1; j <= canli + migration; j++)
		for (int i = 1; i <= point[pnum]; i++)
		{
			random = randomize(pnum) % point[pnum] + 1;
			if (!population[pnum][j].dizi[random])
				population[pnum][j].dizi[random] = i;
			else i--;
		}
}

void caprazla(int pnum)//Two Point Crossover
{
	int syc1, syc2, a = canli + migration;
	int mark1[maxmat], mark2[maxmat], kes1, ata1, ata2;
	for (int i = 1; i <= caprazlama; i++)
	{
		for (int j = 0; j<maxmat; j++)
		{
			mark1[j] = 0;
			mark2[j] = 0;
		}
		ata1 = randomize(pnum) % a + 1;
		do
		{
			ata2 = randomize(pnum) % a + 1;
		} while (ata1 == ata2);
		kes1 = randomize(pnum) % (point[pnum] - 2) + 1;
		for (int j = 1; j <= kes1; j++)
		{
			mark1[population[pnum][ata1].dizi[j]] = 1;
			mark2[population[pnum][ata2].dizi[j]] = 1;
			population[pnum][a + i * 2 - 1].dizi[j] = population[pnum][ata1].dizi[j];
			population[pnum][a + i * 2].dizi[j] = population[pnum][ata2].dizi[j];

		}
		syc1 = kes1 + 1;
		syc2 = kes1 + 1;

		for (int j = 1; j <= point[pnum]; j++)
		{
			if (!mark1[population[pnum][ata2].dizi[j]])
			{
				population[pnum][a + i * 2 - 1].dizi[syc1] = population[pnum][ata2].dizi[j];
				syc1++;
			}
			if (!mark2[population[pnum][ata1].dizi[j]])
			{
				population[pnum][a + i * 2].dizi[syc2] = population[pnum][ata1].dizi[j];
				syc2++;
			}
		}

	}
}

void mutation1(int pnum)
{
	int ata, gen1, gen2, maliyet1, maliyet2, say1 = 0;
	for (int i = 1; i <= mutations1; i++)
	{
		if (!say1)
			ata = randomize(pnum) % (canli + migration) + 1;
		gen1 = randomize(pnum) % point[pnum] + 1;
		do
		{
			gen2 = randomize(pnum) % point[pnum] + 1;
		} while (gen1 == gen2);
		maliyet1 = maliyet(ata, pnum);
		swap(population[pnum][ata].dizi[gen1], population[pnum][ata].dizi[gen2]);
		maliyet2 = maliyet(ata, pnum);
		if (maliyet1<maliyet2)
		{
			swap(population[pnum][ata].dizi[gen1], population[pnum][ata].dizi[gen2]);
			if (say1<20)
			{
				say1++;
				i--;
			}
			else say1 = 0;
		}
	}
}

void mutation2(int pnum)
{
	int ata, gen1, gen2;
	for (int i = 1; i <= mutations2; i++)
	{
		ata = randomize(pnum) % (canli + migration + caprazlama * 2) + 1;
		gen1 = randomize(pnum) % point[pnum] + 1;
		do
		{
			gen2 = randomize(pnum) % point[pnum] + 1;
		} while (gen1 == gen2);
		swap(population[pnum][ata].dizi[gen1], population[pnum][ata].dizi[gen2]);
	}
}

void sirala(int pnum)//Sort Population to Their Fitness
{
	int tum = canli + migration + caprazlama * 2;
	for (int a = 1; a <= tum; a++)
		population[pnum][a].toplam = maliyet(a, pnum);
	sort(population[pnum] + 1, population[pnum] + tum);
}

void eleme(int pnum)//Natural Selection
{
	int m = canli + migration + caprazlama * 2;
	for (int j = canli + 1; j <= m; j++)
	{
		population[pnum][j].toplam = 0;
		for (int i = 1; i <= point[pnum]; i++)
			population[pnum][j].dizi[i] = 0;
	}
}

void test2()
{
	int i = 1;
	clear_to_color(buffer, makecol(255, 255, 255));
	for (int pnum = 1; pnum <= grup; pnum++)
	{
		for (int m = 1; m<point[pnum]; m++)
		{
			line(buffer, gdata[pnum][population[pnum][i].dizi[m]].x, gdata[pnum][population[pnum][i].dizi[m]].y, gdata[pnum][population[pnum][i].dizi[m + 1]].x, gdata[pnum][population[pnum][i].dizi[m + 1]].y, renk[pnum]);
			circlefill(buffer, gdata[pnum][population[pnum][i].dizi[m]].x, gdata[pnum][population[pnum][i].dizi[m]].y, 3, makecol(0, 0, 0));
		}
		line(buffer, gdata[pnum][population[pnum][i].dizi[1]].x, gdata[pnum][population[pnum][i].dizi[1]].y, gdata[pnum][population[pnum][i].dizi[point[pnum]]].x, gdata[pnum][population[pnum][i].dizi[point[pnum]]].y, renk[pnum]);
		circlefill(buffer, gdata[pnum][population[pnum][i].dizi[point[pnum]]].x, gdata[pnum][population[pnum][i].dizi[point[pnum]]].y, 3, makecol(0, 0, 0));
	}
	draw_sprite(screen, buffer, 0, 0);
}

void genetic(void* number)
{
	int pnum = *(int*)number;
	if (generation[pnum] == 0)
	{
		if (yontem1 == 1)
			kumelematik(pnum);
		else
			randgen(pnum);
	}
	while (generation[pnum]<800)
	{
		randekle(pnum);
		mutation1(pnum);
		caprazla(pnum);
		mutation2(pnum);
		sirala(pnum);
		eleme(pnum);
		generation[pnum]++;
		if (generation[pnum] % 15 == 0)
		{
			flag1 = 1;
			break;
		}
	}
	markthread[pnum] = 1;
	_endthread();
}
[STAThread]
void main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Clustermaticv50::MyForm form;
	Application::Run(%form);
	srand(time(NULL));
	q = 1;
	if (!yukle12)
		while (q)
		{
			grup++;
			fl = 0;
			printf("%d. Grup Noktalari Giriniz", grup);
			int r = rand() % 255 + 1, g = rand() % 255 + 1, b = rand() % 255 + 1;
			renk[grup] = makecol(r, g, b);
			while (1)
			{
				if (key[KEY_SPACE])break;
				if (mouse_b & 1 && !fl)
				{
					fl = 1;
					mx = mouse_x;
					my = mouse_y;
					data[grup][++point[grup]].x = mx;
					data[grup][point[grup]].y = my;
					circlefill(buffer, mx, my, 4, renk[grup]);
					draw_sprite(screen, buffer, 0, 0);
				}
				if (!(mouse_b & 1))
					fl = 0;
				if (mouse_b & 2)
				{
					q = 0;
					break;
				}
			}
		}
	///////////////////////////////////////
	if (yukle12)
	{
		yukle();
		if (mal1)
			yukle2();
		int r, g, b;
		for (int i = 1; i <= grup; i++)
		{
			r = rand() % 255 + 1;
			g = rand() % 255 + 1;
			b = rand() % 255 + 1;
			renk[i] = makecol(r, g, b);
		}
	}

	int coz = 0;
	for (int i = 1; i <= grup; i++)
	{
		coz += mesafe(gdata[i][1], gdata[i][point[i]]);
		for (int a = 1; a<point[i]; a++)
			coz += mesafe(gdata[i][a], gdata[i][a + 1]);
	}
	printf("%d", coz);

	//////////////////////////////////////
	printf("Nokta Girisi Tamamlandi");
	_beginthread(randomize1, 0, 0);
	while (wait);
	while (1)
	{
		for (int i = 1; i <= grup; i++)
		{
			tempNum[i] = i;
			_beginthread(genetic, 0, (void*)&tempNum[i]);//Begin
		}
		while (!control())rest(20);
		if (flag1)
		{
			for (int i = 1; i <= grup; i++)
				markthread[i] = 0;
			test2();
			flag1 = 0;
		}
		else
			break;
	}
	printf("Program Sonlandi");
	int top = 0;
	for (int i = 1; i <= grup; i++)
		top += population[i][1].toplam;

	printf("%d", top);
	kaydet();
}