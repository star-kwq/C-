#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<graphics.h>
#include<dos.h>
#include<conio.h>
#define PI 3.14159
#define S 16            
#define WJ  "hzk16" /*ºº×Ö¿â*/
typedef struct /*student*/
{
    char name[8];
    double math;
    double english;
    double computer;
    double sum;
}STU;
typedef struct         /*×Ö¶Î*/
{
    char name[11];
    char type;
    long start; 
    char size;
    char field_dight;
    char empty[14];
}File;
typedef struct       /*ÎÄ¼þ±êÖ¾ÐÅÏ¢*/
{
    char type;
    char date[3];
    long file_num;
    short file_sidth;
    short file_width;
    char empty[20];
}Head;

/*ºº×Ö*/
void disphz(int x,int y,char *zi,int color,int n)/*nÎª·Å´ó±¶Êý*/
{
	FILE *fp;
	char qh,wh;
	long offset;
	int i,j,t;
	int m=0;
	int k=0;
	char buffer[S*S/8];
	char mask[]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
	fp=fopen(WJ,"rb");
	if(fp==NULL)
	{
		exit(0);
	}

	while(*zi!='\0')
	{
		qh=*zi-160;
		zi++;
		wh=*zi-160;
		zi++;
		offset=(94L*(qh-1)+wh-1)*S*S/8;
		fseek(fp,offset,0);
		fread(buffer,S*S/8,1,fp);

		for(i=0;i<S;i++)
		{
			for(j=0;j<S;j++)
			{
				t=buffer[S/8*i+j/8]&mask[j%8];
				if(t!=0)
				for(k=0;k<n;k++)
				for(m=0;m<n;m++)
				putpixel(x+j*n+k,y+i*n+m,color);

			}
		}
		x+=S*m;
	}
	fclose(fp);
}

void dyy()               /*µÚÒ»Ò³*/
 {
    int *zi;
	int gdriver=DETECT;
	int gmode;
	int i;
	initgraph(&gdriver,&gmode,"");

	setbkcolor(15);
	setcolor(1);
	for(i=90;i<540;i=i+110)
	{
		setfillstyle(1,1);
		circle(i,100,60);/*»­Ô²*/
		floodfill(i,100,1);
	}
	setcolor(0);
	settextstyle(1,0,12);
	outtextxy(60,35,"C");
	disphz(160,65,"×Û",0,5);
	disphz(285,65,"ºÏ",0,5);/*5¸ö×Ö*/
	disphz(380,65,"Ó¦",0,5);
	disphz(495,65,"ÓÃ",0,5);

	setcolor(1);
	setfillstyle(1,1);
	bar(190,260,450,400);/*×¢ÊÍµÄ¿ò*/
	floodfill(320,280,1);

	disphz(200,270,"³ÌÐò¹¦ÄÜ",0,1);
	disphz(215,302,"Õ¹Ê¾Ñ§Éú³É¼¨ÈýÎ¬Ö±·½Í¼",0,1);
	disphz(215,325,"Õ¹Ê¾¸÷·Ö¶Î³É¼¨Õ¼±ÈÔ²±ýÍ¼",0,1);
	disphz(270,380,"°´ÈÎÒâ¼ü¼ÌÐø",0,1);

	getch();
	cleardevice();
}

void dey()                 /*µÚ¶þÒ³*/
{
	int *zi;
	int gdriver=DETECT;
	int gmode;
	initgraph(&gdriver,&gmode,"");

	setcolor(15);
	setfillstyle(1,0);/*ÊäÈë¿ò*/
	rectangle(30,65,300,100);
	floodfill(50,80,15);

	disphz(30,40,"ÇëÊäÈëÊý¾Ý¿âÎÄ¼þÃû£º",15,1);
	disphz(25,110,"ÌáÊ¾£º",15,1);
	disphz(65,130,"¿ÉÒÔ´øÅÌ·ûºÍÂ·¾¶£¬Èç",15,1);
	disphz(121,157,"¿ÉÒÔºöÂÔ",15,1);

	settextstyle(1,0,1);
	setcolor(15);
    outtextxy(55,127,"1.");
	outtextxy(55,155,"2.");
	setcolor(4);
	outtextxy(250,127,"D:\\TC\\TC\\DISK_C\\TC20\\sss3.dbf");
	outtextxy(85,155,".dbf");
}
/*»­Ö±·½ºÍÔ²±ýÍ¼*/
void picture(STU *stu,long count)
{
	int *zi;
	int gmode,gdriver=DETECT;
	int key;
	char *g;
	int prev=0,angle=0;
	char fun[2];
	long i=0,panduan,a1=0,a2=0,a3=0,a4=0,a5=0,j,eve,w;
	long kmp=50;
	long yanse=9;
	initgraph(&gdriver,&gmode,"");
	eve=360/count;
	fun[1]=0;
	for(j=0;j<count;j++)
	{
		if(stu[j].sum/3<60)
			a1++;
		if(stu[j].sum/3>=60&&stu[j].sum/3<70)
			a2++;
		if(stu[j].sum/3>=70&&stu[j].sum/3<80)
			a3++;
		if(stu[j].sum/3>=80&&stu[j].sum/3<90)
			a4++;
		if(stu[j].sum/3>=90)
			a5++;
	}
	while(fun[1]!=1)
	{
		if(count%3==2)
			panduan=count-2;
		else
			panduan=count-1;
		for(;i<panduan;)                          /*Âú*/
		{
            cleardevice();
			setcolor(RED);
			rectangle(0,0,639,479);
			setcolor(15);
			setfillstyle(1,12);
			bar3d(150,25,180,35,5,1);
			floodfill(155,24,15);
			floodfill(182,30,15);
			disphz(195,23,"ÊýÑ§",12,1);

			setcolor(4);
			setfillstyle(1,10);
			bar3d(300,25,330,35,5,1);
			floodfill(305,24,4);
			floodfill(332,30,4);
			disphz(345,23,"¼ÆËã»ú",10,1);

			setcolor(14);
			setfillstyle(1,11);
			bar3d(450,25,480,35,5,1);
			floodfill(455,24,14);
			floodfill(482,30,14);
			disphz(495,23,"Ó¢Óï",11,1);

			rectangle(0,0,639,479);
			disphz(225,345,"Ñ§Éú³É¼¨Ê¾ÒâÍ¼",14,2);

			setcolor(14);
			setfillstyle(1,7);
			bar3d(20,400,140,475,15,1);
			floodfill(50,390,14);
			floodfill(145,450,14);

			bar3d(260,400,380,475,15,1);
			floodfill(300,390,14);
			floodfill(385,450,14);

			bar3d(500,400,620,475,15,1);
			floodfill(530,390,14);
			floodfill(625,450,14);
			setcolor(5);
			settextstyle(1,0,2);
			outtextxy(65,440,"(O)");
			disphz(54,410,"ÉÏÒ»Ò³",15,1);

			disphz(304,410,"½áÊø",15,1);
			outtextxy(295,440,"(ESC)");

			disphz(534,410,"ÏÂÒ»Ò³",15,1);
			outtextxy(545,440,"(P)");


			setcolor(WHITE);/*math*/
			setfillstyle(1,12);
			bar3d(150,300-2*stu[i].math,190,300,20,1);
			floodfill(170,290-2*stu[i].math,WHITE);
			floodfill(192,300-2*stu[i].math,WHITE);

			bar3d(300,300-2*stu[i+1].math,340,300,20,1);
			floodfill(320,290-2*stu[i+1].math,WHITE);
			floodfill(342,300-2*stu[i+1].math,WHITE);

			bar3d(450,300-2*stu[i+2].math,490,300,20,1);
			floodfill(470,290-2*stu[i+2].math,WHITE);
			floodfill(492,300-2*stu[i+2].math,WHITE);

			setcolor(RED);/*com*/
			setfillstyle(1,10);
			bar3d(190,300-2*stu[i].computer,230,300,20,1);
			floodfill(210,290-2*stu[i].computer,RED);
			floodfill(232,300-2*stu[i].computer,RED);

			bar3d(340,300-2*stu[i+1].computer,380,300,20,1);
			floodfill(360,290-2*stu[i+1].computer,RED);
			floodfill(382,300-2*stu[i+1].computer,RED);

			bar3d(490,300-2*stu[i+2].computer,530,300,20,1);
			floodfill(510,290-2*stu[i+2].computer,RED);
			floodfill(532,300-2*stu[i+2].computer,RED);

			setcolor(YELLOW);/*engl*/
			setfillstyle(1,CYAN);
			bar3d(230,300-2*stu[i].english,270,300,20,1);
			floodfill(250,290-2*stu[i].english,YELLOW);
			floodfill(272,300-2*stu[i].english,YELLOW);

			bar3d(380,300-2*stu[i+1].english,420,300,20,1);
			floodfill(400,290-2*stu[i+1].english,YELLOW);
			floodfill(422,300-2*stu[i+1].english,YELLOW);

			bar3d(530,300-2*stu[i+2].english,570,300,20,1);
			floodfill(550,290-2*stu[i+2].english,YELLOW);
			floodfill(572,300-2*stu[i+2].english,YELLOW);

			setcolor(15);
			settextstyle(0,0,1);
			line(100,50,100,300);
			line(100,50,95,55);
			line(100,50,105,55);
			outtextxy(82,55,"x");

			line(100,300,615,300);
			line(615,300,610,295);
			line(615,300,610,305);
			outtextxy(620,302,"y");
			outtextxy(95,300,"0");

			line(100,260,110,260);
			outtextxy(80,260,"20");
			line(100,220,110,220);
			outtextxy(80,220,"40");
			line(100,180,110,180);
			outtextxy(80,180,"60");
			line(100,140,110,140);
			outtextxy(80,140,"80");
			line(100,100,110,100);
			outtextxy(75,100,"100");


			disphz(190,310,stu[i].name,6,1);

			disphz(340,310,stu[i+1].name,6,1);

			disphz(490,310,stu[i+2].name,6,1);
			break;
		}
		key=bioskey(0);
		fun[0]=key;
		fun[1]=key>>8;
		if(fun[1]==25&&i<(count-count%3))
			i+=3;
		if(fun[1]==24&&i!=0)
			i-=3;
		if(count%3==1&&i==panduan)                /*ÉÙ2*/
		{
			cleardevice();
			setcolor(RED);
			rectangle(0,0,639,479);
			setcolor(15);
			setfillstyle(1,12);
			bar3d(150,25,180,35,5,1);
			floodfill(155,24,15);
			floodfill(182,30,15);

			disphz(195,23,"ÊýÑ§",12,1);

			setcolor(4);
			setfillstyle(1,10);
			bar3d(300,25,330,35,5,1);
			floodfill(305,24,4);
			floodfill(332,30,4);

			disphz(345,23,"¼ÆËã»ú",10,1);

			setcolor(14);
			setfillstyle(1,11);
			bar3d(450,25,480,35,5,1);
			floodfill(455,24,14);
			floodfill(482,30,14);

			disphz(495,23,"Ó¢Óï",11,1);

			rectangle(0,0,639,479);
			disphz(225,345,"Ñ§Éú³É¼¨Ê¾ÒâÍ¼",14,2);

			setcolor(14);
			setfillstyle(1,7);
			bar3d(20,400,140,475,15,1);
			floodfill(50,390,14);
			floodfill(145,450,14);

			bar3d(260,400,380,475,15,1);
			floodfill(300,390,14);
			floodfill(385,450,14);

			bar3d(500,400,620,475,15,1);
			floodfill(530,390,14);
			floodfill(625,450,14);
			setcolor(5);
			settextstyle(1,0,2);
			outtextxy(65,440,"(O)");
			disphz(54,410,"ÉÏÒ»Ò³",15,1);

			disphz(304,410,"½áÊø",15,1);
			outtextxy(295,440,"(ESC)");

			disphz(534,410,"ÏÂÒ»Ò³",15,1);
			outtextxy(545,440,"(P)");


			setcolor(WHITE);/*math*/
			setfillstyle(1,12);
			bar3d(150,300-2*stu[i].math,190,300,20,1);
			floodfill(170,290-2*stu[i].math,WHITE);
			floodfill(192,300-2*stu[i].math,WHITE);

			setcolor(RED);/*com*/
			setfillstyle(1,10);
			bar3d(190,300-2*stu[i].computer,230,300,20,1);
			floodfill(210,290-2*stu[i].computer,RED);
			floodfill(232,300-2*stu[i].computer,RED);

			setcolor(YELLOW);/*engl*/
			setfillstyle(1,CYAN);
			bar3d(230,300-2*stu[i].english,270,300,20,1);
			floodfill(250,290-2*stu[i].english,YELLOW);
			floodfill(272,300-2*stu[i].english,YELLOW);

			setcolor(15);
			settextstyle(0,0,1);
			line(100,50,100,300);
			line(100,50,95,55);
			line(100,50,105,55);
			outtextxy(82,55,"x");

			line(100,300,615,300);
			line(615,300,610,295);
			line(615,300,610,305);
			outtextxy(620,302,"y");
			outtextxy(95,300,"0");

			line(100,260,110,260);
			outtextxy(80,260,"20");
			line(100,220,110,220);
			outtextxy(80,220,"40");
			line(100,180,110,180);
			outtextxy(80,180,"60");
			line(100,140,110,140);
			outtextxy(80,140,"80");
			line(100,100,110,100);
			outtextxy(75,100,"100");

			disphz(190,310,stu[i].name,6,1);

		}
		if(count%3==2&&i==panduan)            /*ÉÙ1*/
		{
			cleardevice();
			setcolor(RED);
			rectangle(0,0,639,479);
			setcolor(15);
			setfillstyle(1,12);
			bar3d(150,25,180,35,5,1);
			floodfill(155,24,15);
			floodfill(182,30,15);

			disphz(195,23,"ÊýÑ§",12,1);

			setcolor(4);
			setfillstyle(1,10);
			bar3d(300,25,330,35,5,1);
			floodfill(305,24,4);
			floodfill(332,30,4);

			disphz(345,23,"¼ÆËã»ú",10,1);

			setcolor(14);
			setfillstyle(1,11);
			bar3d(450,25,480,35,5,1);
			floodfill(455,24,14);
			floodfill(482,30,14);

			disphz(495,23,"Ó¢Óï",11,1);

			disphz(225,345,"Ñ§Éú³É¼¨Ê¾ÒâÍ¼",14,2);

			setcolor(14);
			setfillstyle(1,7);
			bar3d(20,400,140,475,15,1);
			floodfill(50,390,14);
			floodfill(145,450,14);

			bar3d(260,400,380,475,15,1);
			floodfill(300,390,14);
			floodfill(385,450,14);

			bar3d(500,400,620,475,15,1);
			floodfill(530,390,14);
			floodfill(625,450,14);
			setcolor(5);
			settextstyle(1,0,2);
			outtextxy(65,440,"(O)");
			disphz(54,410,"ÉÏÒ»Ò³",5,1);

			disphz(304,410,"½áÊø",5,1);
			outtextxy(295,440,"(ESC)");

			disphz(534,410,"ÏÂÒ»Ò³",5,1);
			outtextxy(545,440,"(P)");


			setcolor(WHITE);/*math*/
			setfillstyle(1,12);
			bar3d(150,300-2*stu[i].math,190,300,20,1);
			floodfill(170,290-2*stu[i].math,WHITE);
			floodfill(192,300-2*stu[i].math,WHITE);

			bar3d(300,300-2*stu[i+1].math,340,300,20,1);
			floodfill(320,290-2*stu[i+1].math,WHITE);
			floodfill(342,300-2*stu[i+1].math,WHITE);

			setcolor(RED);/*com*/
			setfillstyle(1,10);
			bar3d(190,300-2*stu[i].computer,230,300,20,1);
			floodfill(210,290-2*stu[i].computer,RED);
			floodfill(232,300-2*stu[i].computer,RED);

			bar3d(340,300-2*stu[i+1].computer,380,300,20,1);
			floodfill(360,290-2*stu[i+1].computer,RED);
			floodfill(382,300-2*stu[i+1].computer,RED);

			setcolor(YELLOW);/*engl*/
			setfillstyle(1,CYAN);
			bar3d(230,300-2*stu[i].english,270,300,20,1);
			floodfill(250,290-2*stu[i].english,YELLOW);
			floodfill(272,300-2*stu[i].english,YELLOW);

			bar3d(380,300-2*stu[i+1].english,420,300,20,1);
			floodfill(400,290-2*stu[i+1].english,YELLOW);
			floodfill(422,300-2*stu[i+1].english,YELLOW);

			setcolor(15);
			settextstyle(0,0,1);
			line(100,50,100,300);
			line(100,50,95,55);
			line(100,50,105,55);
			outtextxy(82,55,"x");

			line(100,300,615,300);
			line(615,300,610,295);
			line(615,300,610,305);
			outtextxy(620,302,"y");
			outtextxy(95,300,"0");

			line(100,260,110,260);
			outtextxy(80,260,"20");
			line(100,220,110,220);
			outtextxy(80,220,"40");
			line(100,180,110,180);
			outtextxy(80,180,"60");
			line(100,140,110,140);
			outtextxy(80,140,"80");
			line(100,100,110,100);
			outtextxy(75,100,"100");
			rectangle(0,0,639,479);


			disphz(190,310,stu[i].name,6,1);

			disphz(340,310,stu[i+1].name,6,1);
		}
}
	cleardevice();
	setcolor(6);
	rectangle(480,40,610,210);
	/*±ý*/
    for(i=0;i<5;i++)
{
	setcolor(14);
	settextstyle(1,0,2);
	setfillstyle(1,yanse++);
	bar(490,kmp,515,20+kmp);
	if(i==0)
		outtextxy(520,kmp,"0--60");
	if(i==1)
		outtextxy(520,kmp,"60--70");
	if(i==2)
		outtextxy(520,kmp,"70--80");
	if(i==3)
		outtextxy(520,kmp,"80--90");
	if(i==4)
		outtextxy(520,kmp,"90--100");
	kmp+=30;
}

	setfillstyle(1,9);
    angle=eve*a1;
    sprintf(g,"%d",a1*10);
	pieslice(200,200,0,angle,150);
	outtextxy(180+113*cos(angle*PI/360),200-115*sin(angle*PI/360),g);
	outtextxy(180+113*cos(angle*PI/360)+16,200-115*sin(angle*PI/360),"%");


	setfillstyle(1,10);
    prev=angle;
    angle=angle+eve*a2;
    sprintf(g,"%d",a2*10);
	pieslice(200,200,prev,angle,150);
	outtextxy(180+113*cos((prev+angle)*PI/360),200-115*sin((prev+angle)*PI/360),g);
	outtextxy(180+113*cos((prev+angle)*PI/360)+16,200-115*sin((prev+angle)*PI/360),"%");


	setfillstyle(1,11);
    prev=angle;
    angle=angle+eve*a3;
    sprintf(g,"%d",a3*10);
	pieslice(200,200,prev,angle,150);
	outtextxy(180+113*cos((prev+angle)*PI/360),200-115*sin((prev+angle)*PI/360),g);
	outtextxy(180+113*cos((prev+angle)*PI/360)+16,200-115*sin((prev+angle)*PI/360),"%");


	setfillstyle(1,12);
    prev=angle;
    angle=angle+eve*a4;
    sprintf(g,"%d",a4*10);
	pieslice(200,200,prev,angle,150);
	outtextxy(180+113*cos((prev+angle)*PI/360),200-115*sin((prev+angle)*PI/360),g);
	outtextxy(180+113*cos((prev+angle)*PI/360)+16,200-115*sin((prev+angle)*PI/360),"%");

	setfillstyle(1,13);
    prev=angle;
    angle=angle+eve*a5;
    sprintf(g,"%d",a5*10);
	pieslice(200,200,prev,angle,150);
	outtextxy(180+113*cos((prev+angle)*PI/360),200-115*sin((prev+angle)*PI/360),g);
	outtextxy(180+113*cos((prev+angle)*PI/360)+16,200-115*sin((prev+angle)*PI/360),"%");

	disphz(300,420,"¸÷·Ö¶Î³É¼¨Ô²±ýÍ¼",15,2);
    getch();
    cleardevice();
}
void read_file()/*¶ÁÈ¡*/
{
        FILE *fp;
        Head headd;
        File file[5];
        STU stu[100];
        STU qq;
        long i=0,n=0,k,j=0,count=0,p,o;
        char huan[20],filename[20];
        char fun;
        gotoxy(5,6);
		scanf("%s",&filename);
		if(strcmp(&filename[strlen(filename)-4],".dbf")!=0)/*ÅÐ¶Ï.dbf£¿*/		
        strcat(filename,".dbf");
		fp=fopen(filename,"rb");

		if(fp==NULL)
        {
		disphz(210,250,"ÎÞ·¨´ò¿ªÎÄ¼þ£¬ÇëÖØÐÂÔËÐÐ³ÌÐò!",4,1);
		disphz(210,300,"ÈÎÒâ¼üÍË³ö³ÌÐò",15,1);
            getch();
            exit(1);
        }
		fread(&headd,32,1,fp);                       
		for(i=1;i<=(headd.file_sidth-33)/32;i++)
		{
			fread(&file[0],32,1,fp);
			if(strcmp(file[0].name,"ÐÕÃû")==0)
				file[1]=file[0];
			else
				if(strcmp(file[0].name,"ÊýÑ§")==0)
					file[2]=file[0];
				else
					if(strcmp(file[0].name,"Ó¢Óï")==0)
						file[3]=file[0];
					else
						if(strcmp(file[0].name,"¼ÆËã»ú")==0)
							file[4]=file[0];
		}

		for(i=0;i<headd.file_num;i++)
		{
			fseek(fp,headd.file_sidth+headd.file_width*i,0);
			fread(&fun,1,1,fp);
			if(fun=='*')
				continue;
			fseek(fp,headd.file_sidth+headd.file_width*i+file[1].start,0);
			fread(stu[count].name,file[1].size,1,fp);
			stu[count].name[file[1].size]=0;
			for(p=file[1].size-1;p>=0;p--)
			{
				if(stu[count].name[p]==' ')
					stu[count].name[p]=0;
				else
					break;
			}
			fseek(fp,headd.file_sidth+headd.file_width*i+file[2].start,0);
			ftell(fp);
			fread(huan,file[2].size,1,fp);
			huan[file[2].size]=0;
			stu[count].math=(float)atof(huan);

			fseek(fp,headd.file_sidth+headd.file_width*i+file[3].start,0);
			ftell(fp);
			fread(huan,file[3].size,1,fp);
			huan[file[3].size]=0;
			stu[count].english=(float)atof(huan);

			fseek(fp,headd.file_sidth+headd.file_width*i+file[4].start,0);
			ftell(fp);
			fread(huan,file[4].size,1,fp);
			huan[file[4].size]=0;
			stu[count].computer=(float)atof(huan);

			stu[count].sum=stu[count].computer+stu[count].math+stu[count].english;
			count++;
		}

		fclose(fp);
		picture(stu,count);
		return 0;
}
 void  music(unsigned int freq, int times)       /*ÒôÀÖ*/
{
    int i;
    union
   {
		int divisor;
		char c[2];/*³õÊ¼ÆµÂÊ*/
   }sound;
	char bits;
	sound.divisor=1193180/freq;

	outportb(0x43,0xb6);
	outportb(0x42,sound.c[0]);/*·¢Éù*/
	outportb(0x42,sound.c[1]);

	bits=inportb(0x61);
	outportb(0x61,bits|3);
	for(i=0;i<times;i++)
	delay(100);

	outportb(0x61,bits&0xfc);/*²»·¢Éù*/
	outportb(0x61,bits);
}
void end()
{
	int freq[8] = {0,349,392,440,494,524,588,660};
	int song[] ={-6,-7,1,2,3,5,6,5,3,2,1,2,3,3,-6,-7,1,2,3,5,6,5,3,2,1,2,3,-6,-6,-7,1,2,3,5,6,5,3,2,1,2,3,3,-6,-7,1,2,3,5,6,5,3,2,1,2,3,-6,0};
	int div[] = {8,8,8,8,8,16,16,8,8,8,8,8,8,2,8,8,8,8,8,16,16,8,8,8,8,8,8,2,8,8,8,8,8,16,16,8,8,8,8,8,8,2,8,8,8,8,8,16,16,8,8,8,8,8,8,2,0};
	char arr[][10]={"±¾","³Ì","Ðò","ÓÉ","¼Æ","Êý","¶þ","Áã","¶þ","¿×","ÎÄ","Ç¿","±à","Ð´","¡£"};
	char brr[][10]={"ÔÚ","´Ë","¸Ð","Ð»","²Ü","ÀÏ","Ê¦","Ò»","Äê","À´","µÄ","½Ì","»Ú","¡£"};
	unsigned int f;
	int k=0,y=0;
	int i,s,x,times,gdriver, gmode;
     gdriver = DETECT;
	initgraph(&gdriver, &gmode,"");
	for(x=0;x<=13;x++)
	{
		disphz(20+y,50,brr[x],15,2);
		y+=32;                                  /*Á½ÐÐ×Ö*/
		delay(100);
	}
	for(s=0;s<=14;s++)
	{
		 disphz(20+k,400,arr[s],15,1);
		 k+=20;
		 delay(100);
	}
	for(i=0;song[i];i++)
	{
		if(song[i] < 0)
			f = freq[-song[i]]/2;
		else if(song[i]>7)
			f = freq[song[i] % 7]*2;
		else
			f = freq[song[i]];/*Èý¸öifÊÇ¸ßµÍÒô*/
		times=16/div[i];
		music(f,times);
		if(i==14)
		{
			disphz(300,350,"³ÌÐò½áÊøÐ»Ð»¹Û¿´",15,2);
		}
		if(i==25)
		{
			setcolor(15);
			settextstyle(3,0,3);
			outtextxy(10,450,"The END");
		}
		if(i==55)
		{
			disphz(500,450,"°´ÈÎÒâ¼üÍË³ö",15,1);
		}

	}

    getch();
    closegraph();
}

int main()                                         /*Ö÷º¯Êý*/
{
	int *zi;
	int mode,driver=DETECT;
	initgraph(&driver,&mode,"");
	dyy();                                /*ÏÔÊ¾µÚÒ»Ò³*/
	dey();
	read_file();
	end();
	return 0;
}
