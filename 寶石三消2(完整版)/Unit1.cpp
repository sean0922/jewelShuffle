//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
TImage *img[5][5];
int tmpplace;
int nowplace;
String tmpcolor;
String nowcolor;
int bb=0;
int point=0;
int times=60;
bool gameover=false;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
    time_t t;
	srand((unsigned)time(&t));    //亂數種子
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
            img[i][j]=NULL;
        }
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::whenimgclk(TObject *Sender)//圖片按下時
{
  //ShowMessage((img2->Hint)+"號寶石"+(IntToStr(img2->Tag))+"號位");
  TImage *img2;
  img2=(TImage *)Sender;
  if(bb==1&&(img2->Tag!=tmpplace-1&&img2->Tag!=tmpplace+1&&img2->Tag!=tmpplace-5&&img2->Tag!=tmpplace+5))
  {
	ShowMessage(IntToStr(tmpplace)+IntToStr(img2->Tag));
	ShowMessage("不能選");
	return;
  }
  bb+=1;
  img2->Picture->LoadFromFile(img2->Hint+img2->Hint+".png");
  //ShowMessage(bb);
  if(bb==2)
  {
	nowplace = img2->Tag;
	nowcolor = img2->Hint;

	img[(tmpplace-1)/5][(tmpplace-1)%5]->Picture->LoadFromFile(img2->Hint+".png");
	img[(tmpplace-1)/5][(tmpplace-1)%5]->Hint=img2->Hint;

	img2->Picture->LoadFromFile(tmpcolor+".png");
	img2->Hint=tmpcolor;
	gameover=true;
	bb=0;
  }
  if(bb==1)
  {
	tmpplace = img2->Tag;
	tmpcolor = img2->Hint;
	//ShowMessage(IntToStr(tmpplace)+tmpcolor);
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	times=60;
    gameover=false;
	point=0;
    Label1->Caption=point;
	setplace();
	Timer1->Enabled=true;
}
void TForm1::setplace()//設定圖片及位置
{
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			if(img[i][j]!=NULL)
			{
			 ShowMessage("fail");
			 return;
			}
			int a=0;
			//a=(rand()%RAND_NUM);
			a=(rand()%(6-1+1))+1;
			img[i][j]=new TImage(this);
			img[i][j]->Top=50+(i*60);
			img[i][j]->Left=50+(j*70);
			img[i][j]->Tag=(i*5)+j+1;
			img[i][j]->Hint=a;
			img[i][j]->OnClick=whenimgclk;
			img[i][j]->Height=50;
			img[i][j]->Width=50;
			img[i][j]->Stretch=true;
			img[i][j]->Parent=this;
			img[i][j]->Picture->LoadFromFile(IntToStr(a)+".png");
		}
	}
}
void TForm1:: cleanp()//清除動態圖片
{
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			if(img[i][j]==NULL)
			{
			 ShowMessage("無垃圾");
			 return;
			}
			delete img[i][j];
			img[i][j]=NULL;
		}
	}
			 ShowMessage("清除成功");
}

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	Timer1->Enabled=false;
	cleanp();

}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
	Timer1->Enabled=false;
	cleanp();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
	ShowMessage("讓三顆以上的寶石連線即可得分");
}
//---------------------------------------------------------------------------
void TForm1:: count()
{
	if(times==0)
	{
		Timer1->Enabled=false;
		ShowMessage("GAME OVER"+IntToStr(point)+"分");
		cleanp();
        return;
	}
    Label3->Caption=times;
	times-=1;
	int count=1;
	int lef=0,right=0,up=0,down=0;
	int a[25];
	int randn;
	String num="";
	for(int i=0;i<25;i++)
	{
	count=1;
	a[i]=0;
	lef=0;
	right=0;
	up=0;
	down=0;
			while((i%5)-count>=0&&(img[i/5][i%5]->Hint)!=69&&(img[i/5][i%5]->Hint)==(img[i/5][(i%5)-count]->Hint))//判斷左
			{
				lef+=1;
				count+=1;
			}
			count=1;
			while((i%5)+count<=4&&(img[i/5][i%5]->Hint)!=69&&(img[i/5][i%5]->Hint)==(img[i/5][(i%5)+count]->Hint))//判斷左
			{
				right+=1;
				count+=1;
			}
			count=1;
			while((i/5)-count>=0&&(img[i/5][i%5]->Hint)!=69&&(img[i/5][i%5]->Hint)==(img[(i/5)-count][i%5]->Hint))//判斷左
			{
				up+=1;
				count+=1;
			}
			count=1;
			while((i/5)+count<=4&&(img[i/5][i%5]->Hint)!=69&&(img[i/5][i%5]->Hint)==(img[(i/5)+count][i%5]->Hint))//判斷左
			{
				down+=1;
				count+=1;
			}


			if((lef+right)>=2||(up+down)>=2)
			{
				a[i]=1;
				point+=5;
				Label1->Caption=IntToStr(point);
			}
			num+=IntToStr(a[i]);
			if((i+1)%5==0)
			{
			Memo1->Lines->Add(num);
			num="";
			}
			if(i==24)
			{
			Memo1->Lines->Add("");
			}



	}
	int cche=0; //判斷有無消除
	for(int i=0;i<25;i++) //把標記住的照片變白
	{
		if(a[i]==1)
		{
			//randn=(rand()%(6-1+1))+1;
			img[i/5][i%5]->Picture->LoadFromFile("0.png");
			img[i/5][i%5]->Hint=69;
			cche=1;
		}
	}

	for(int i=24;i>=0;i--)
	{
	int cc=1;
	int onoff=0;

		if(img[i/5][i%5]->Hint==69&&i>4)
		{
			while((i/5)-cc>=0&&onoff==0)
			{
				if(img[(i/5)-cc][i%5]->Hint!=69)
				{
				onoff=1;
				}

				if(img[(i/5)-cc][i%5]->Hint==69)
				{
				cc+=1;
				}
			}
			if(onoff==1)
			{
				img[i/5][i%5]->Picture->LoadFromFile(img[(i/5)-cc][i%5]->Hint+".png");
				img[i/5][i%5]->Hint=img[(i/5)-cc][i%5]->Hint;
				img[(i/5)-cc][i%5]->Picture->LoadFromFile("0.png");
				img[(i/5)-cc][i%5]->Hint=69;
			}
			else
			{
				int randn;
				randn=(rand()%(6-1+1))+1;
				img[i/5][i%5]->Picture->LoadFromFile(IntToStr(randn)+".png");
				img[i/5][i%5]->Hint=randn;
			}
		}
		if(i<5&&img[i/5][i%5]->Hint==69)
		{
			randn=(rand()%(6-1+1))+1;
			img[i/5][i%5]->Picture->LoadFromFile(IntToStr(randn)+".png");
			img[i/5][i%5]->Hint=randn;
        }
	}
	if((gameover==true)&&(cche==0))
	{
		gameover=false;
		img[(tmpplace-1)/5][(tmpplace-1)%5]->Picture->LoadFromFile(tmpcolor+".png");
		img[(nowplace-1)/5][(nowplace-1)%5]->Picture->LoadFromFile(nowcolor+".png");
		img[(tmpplace-1)/5][(tmpplace-1)%5]->Hint=tmpcolor;
		img[(nowplace-1)/5][(nowplace-1)%5]->Hint=nowcolor;
	   //	ShowMessage("有近來"+tmp);
		//Timer1->Enabled=false;
		//ShowMessage("GAME OVER"+IntToStr(point)+"分");
		//cleanp();
	}
	gameover=false;
}

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
    count();
}
//---------------------------------------------------------------------------

