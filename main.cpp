#include <iostream>
#include <SDL2/SDL.h>
#include <fstream>
#include <vector>

using namespace std;

short dip_r1,dip_r2;
short dip_g1,dip_g2;
short dip_b1,dip_b2;

void avg_color()
{
	cout<<"Enter diaposon red \u00b1 25:\nFirst: ";
	cin>>dip_r1; cout<<"Last: "; cin>>dip_r2;

	cout<<"Enter diaposon green \u00b1 25:\nFirst: ";
	cin>>dip_g1; cout<<"Last: "; cin>>dip_g2;

	cout<<"Enter diaposon blue \u00b1 25:\nFirst: ";
	cin>>dip_b1; cout<<"Last: "; cin>>dip_b2;
}

int main()
{
	bool no=false;
	bool save=false;
	cout<<"Enter filename: ";
	string file_name;
	cin>>file_name;
	cout<<"Do you want enter values average color?[y/n]: ";
	char y_o_n;
	getchar();
	y_o_n=getchar();

	if (y_o_n=='y') {avg_color();}
	else if (y_o_n=='n') {no=true;}
	else {cout<<"Error\n";return 1;}

	cout<<"Do you want save?[y/n]: ";
	char y_n;
	getchar();
	y_n=getchar();
	if (y_n=='y') {save=true;}
	else if (y_n=='n') {save=false;}
	else {cout<<"Error\n";return 1;}

 	
	vector<short> r_c;
	vector<short> g_c;
	vector<short> b_c;

	ifstream file(file_name);
	

	char ch;

	string str;
	string line;

	int width;
	int height;

	vector<int> x;
	vector<int> y;

	vector<int> red;
	vector<int> green;
	vector<int> blue;
	
	int check_line=0;
	while (getline(file,line))
	{
		line+=" ";
		int rgb=0;
		check_line++;
		for (int i=0;i<line.size();i++)
		{
			
			if (line.at(i)!=' ')
			{
				str+=line.at(i);
			}

			else
			{
				rgb++;
				
				if (str.empty())
				{
					break;
				}

				
				if (str.at(str.size()-1)=='W')
				{
					
					string width_string;
					for (int w_s=0;w_s<str.size()-1;w_s++)
					{
						width_string+=str.at(w_s);
					}
					
					width=stoi(width_string);
					
				}

				else if (str.at(str.size()-1)=='H')
				{
					
					string height_string;
					
					for (int h_s=0;h_s<str.size()-1;h_s++)
					{
						height_string+=str.at(h_s);
					}
					height=stoi(height_string);
					
				}

				if (check_line>1)
				{
					if (rgb==1)
					{
					
						string red_string;
						for (int r_s=0;r_s<str.size();r_s++)
						{
							red_string+=str.at(r_s);
						}
					
						int r_v=stoi(red_string);
						red.push_back(r_v);
						r_c.push_back(r_v);
					}

					else if (rgb==2)
					{
						string green_string;
						for (int g_s=0;g_s<str.size();g_s++)
						{
							green_string+=str.at(g_s);
						}
						int g_v=stoi(green_string);
						green.push_back(g_v);
						g_c.push_back(g_v);
					}

					else if (rgb==3)
					{
						string blue_string;
						for (int b_s=0;b_s<str.size();b_s++)
						{
							blue_string+=str.at(b_s);
						}
						int b_v=stoi(blue_string);
						blue.push_back(b_v);
						b_c.push_back(b_v);
					}
				}

				str="";
			}
		}
	}
	
	for (int i=0;i<height;i++)
	{
		for (int t=0;t<width;t++)
		{
			y.push_back(i);
			x.push_back(t);
		}
		
	}
	

	short avg_r;
	short avg_g;
	short avg_b;

	int avg=0;
	for (int i=0;i<r_c.size();i++) {avg+=r_c.at(i);}
	avg_r=avg/r_c.size();
	avg=0;
	for (int i=0;i<g_c.size();i++) {avg+=g_c.at(i);}
	avg_g=avg/g_c.size();
	avg=0;
	for (int i=0;i<b_c.size();i++) {avg+=b_c.at(i);}
	avg_b=avg/b_c.size();
	
	if (no==true)
	{
		dip_r1=avg_r-25;
		dip_r2=avg_r+25;

		dip_g1=avg_g-25;
		dip_g2=avg_g+25;

		dip_b1=avg_b-25;
		dip_b2=avg_b+25;
	}
	srand(time(0));
	
	short last_r=0; short last_g=0; short last_b=0;
	for (int i=0;i<height;i++)
	{
		for (int j=0;j<width;j++)
		{
			int index_pix=i*width+j;
			short pixel_r=red.at(index_pix);
			short pixel_g=green.at(index_pix);
			short pixel_b=blue.at(index_pix);

		
			if ((pixel_r>dip_r1 && pixel_r<dip_r2) && (pixel_g>dip_g1 && pixel_g<dip_g2) && (pixel_b>dip_b1 && pixel_b<dip_b2))
			{
				short col_r;
				short col_g;
				short col_b;
	
				if (last_r==0 && last_g==0 && last_b==0)
				{
					col_r=rand()%255;
					col_g=rand()%255;
					col_b=rand()%255;
					
					last_r=col_r; last_g=col_g; last_b=col_b;
				}
				else
				{
					col_r=rand()%(255-last_r+1)-last_r;
					col_g=rand()%(255-last_g+1)-last_g;
					col_b=rand()%(255-last_g+1)-last_b;
				}
				red.at(index_pix)=col_r;
				green.at(index_pix)=col_g;
				blue.at(index_pix)=col_b;

			}
		}
		if (i%rand()%3==0) {last_r=0;last_g=0;last_b=0;}
		
		
		
	}

	if (save==true)
	{
		ofstream fl("glitch.whld");
		fl<<width<<"W "<<height<<"H\n";
		for (int i=0;i<height;i++)
		{
			for (int j=0;j<width;j++)
			{
				int ind_px=i*width+j;
				fl<<red.at(ind_px)<<' '<<green.at(ind_px)<<' '<<blue.at(ind_px)<<endl;
			}
		}
		fl.close();
	}
	else {save=false;}

	SDL_Window* window=SDL_CreateWindow(file_name.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_SHOWN);
	

	SDL_Renderer* ren=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

	bool run=true;
	SDL_Event event;
	
	while (run)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type==SDL_QUIT)
			{
				run=false;
			}
		}

		SDL_SetRenderDrawColor(ren,0,0,0,255);
		SDL_RenderClear(ren);
		
		
		for (int i=0;i<x.size()&&y.size();i++)
		{
			
			SDL_SetRenderDrawColor(ren,red.at(i),green.at(i),blue.at(i),255);
			
			SDL_RenderDrawPoint(ren,x.at(i),y.at(i));
			
				
		}
		
		SDL_RenderPresent(ren);
		
	}

	
}
