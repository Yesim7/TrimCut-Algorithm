#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
using namespace std;
#define n 500
#define MAXint 999

FILE *f,*f1,*f2,*f3;
int a[n+1][n+1]={0};
int t[n+1][n+1]={0};
int sakla[n+1][n+1]={0};
int k[n+1][n+1]={0};
int ch[n+1][n+1]={0};
int ban[n+1]={0};
int rooted[n+1]={0};
int parent[n+1]={0};
int ns[n+1]={0};
int cutn[n+1]={0};
int use[n+1]={0};
int deg[n+1]={0};
int indis[n+1]={0};
int list[n+1]={0};
int silnode[n+1]={0};
int rank[n+1]={0};
int au[n+1]={0};
int ck;

int iterasyon=0;

void parcala()
{
	int gidildi[n+1]={0};
	int com[n+1]={0};
	int comsay=0,cnp=0,maxeleman;
	int i,j,z,m;
	int syc1=0;


	for(i=0;i<=n;i++)
	{
		gidildi[i]=0;
		com[i]=0;	
	}
	comsay=0; // MaxNum cevabi
	maxeleman=0; // MinMaxC cevabi
	cnp=0; // CNP cevabi
	
	/// BFS root seçiliyor
devam:

	for(i=1;i<=n;i++)
	{
		if (gidildi[i]==0 && silnode[i]==0)
		{ // Silinmiþ olmayan her tepe konrol edilmeli
			z=i;
			goto find;
		}
	}
find:
	gidildi[0]++;
	gidildi[z]=1;
	
	com[0]++;
	com[com[0]]=z;
	
	for(i=1;i<=com[0];i++)
	{
		m=com[i];
		for(j=1;j<=k[m][0];j++)
		{
			if (gidildi[k[m][j]]==0)
			{
				gidildi[k[m][j]]=1;
				gidildi[0]++;
						
				com[0]++;
				com[com[0]]=k[m][j];
			}
		}
	}
	
	comsay++;
	cnp=cnp + (com[0]*(com[0]-1))/2;
	
	if (maxeleman<com[0])
	{
		maxeleman=com[0];
	}
	if (gidildi[0]!=(n-silnode[0]))
	{

		for(i=0;i<=n;i++)
			com[i]=0;

		goto devam;
	}
	else
	{	//Tüm elemanlar iþleme alýnmýþ
		// maxeleman = MinMaxC
		// comsay = MaxNum
		if (iterasyon==1)
		{
			fprintf(f1,"%d",cnp);	
			
		}else
		{
			fprintf(f1,", %d ",cnp);  	
		}
		printf("\nCNP:\t %d \t %d\n",silnode[0],cnp);
	}	
}

int main()
{
	int iter,current,i,j,z,m,min,mstnumber=0,scoremin,fmax;
	int hangi,kontrol,cnsay,mevcut,kok,komsu1,komsu2,as,scoremax,y1,y2,saklaa;
	int old_cnp,fark_cnp,r_cnp,ust_agac,maxfark,max_degree, max_hangi;
	int c1,fc1,fc2,fark,cost,sil_node,max_tsize,cikar;
	float min_value,max,oran;

	clock_t start_time;
	
	system("Color 6");	
	f = fopen("ba500.txt", "r");
	
	ck= 50;
	printf("CK:%d",ck);
	
	for(i=1; i<=n; i++)
		for(j=1;j<=n;j++)
		{
			fscanf(f, "%d", &a[i][j]);
			if (a[i][j]==1)
			{
				sakla[i][j]=a[i][j];
				k[i][0]++;
				k[i][k[i][0]]=j;
			}
		}
	fclose(f);
	
	start_time = clock();
	
moredeg:
	for(i=1; i<=n; i++)
	{
		deg[i]=k[i][0];
		indis[i]=i;
	}
	max_degree=0;
	max_hangi=0;
	
	for(i=1;i<n;i++)
	{
		if (deg[i]>max_degree)
		{
			max_degree=deg[i];
			max_hangi=i;
		}
	}

	silnode[0]++;
	silnode[max_hangi]=1;
	
	for(j=1;j<=n;j++)
	{
		a[j][max_hangi]=0;
		a[max_hangi][j]=0;
	}	
	
	for(i=0; i<=n; i++)
		for(j=0;j<=n;j++)
			k[i][j]=0;
			
	for(i=1; i<=n; i++)
		for(j=1;j<=n;j++)
		{
			if (a[i][j]==1)
			{
				k[i][0]++;
				k[i][k[i][0]]=j;
			}
		}
	if  (silnode[0]<ck/2) goto moredeg;
	
sildevam:
	iterasyon++;
	for(i=0;i<=n;i++)
	{
		ban[i]=0;
		ns[i]=0;
		rooted[i]=0;
		use[i]=0;
		parent[i]=0;
		for(j=0;j<=n;j++)
		{
			t[i][j]=0;
			ch[i][j]=0;
		}	
	}
	for(i=0;i<=n;i++)
	{
		au[i]=10000;
		rank[i]=0;	
	}
	max_tsize=0;
kokbul:
	max=-1.0;
	for(i=1;i<=n;i++)
	{
		if (silnode[i]==0 && ban[i]==0) 
		{ 
			kok=i;
		}
	}
	
	for(i=0;i<=n;i++)
		list[i]=0;
		
	rooted[kok]=1;
	ban[kok]=1;
	ban[0]++;
	
	iter=1;
	mevcut=1; //token
	
	list[0]++;
	list[list[0]]=kok;
	
	au[kok]=0;
	rank[kok]=0;
	for(i=1;i<=k[kok][0];i++)
	{
		au[k[kok][i]]=0;
	}

agacadevam:
	z=list[mevcut];
	scoremin=10000;
	scoremax=0;
	for(i=1;i<=k[z][0];i++)
	{
		if (ban[k[z][i]]==0 && silnode[k[z][i]]==0)
		{
			scoremax=1;
			hangi=k[z][i];
		}
	}
	
	if (mevcut!=1 && scoremax==0)
	{
		
		if (au[z]<au[parent[z]]) 
		{
			au[parent[z]]=au[z];
		}
		if (use[z]==0)
		{
			ns[parent[z]]+=ns[z]+1;
			t[parent[z]][0]++;
			t[parent[z]][t[parent[z]][0]]=ns[z]+1;
			use[z]=1;
		}
		mevcut--;
		goto agacadevam;
	}
	if (scoremax==0 && mevcut==1 && (ban[0]==(n-silnode[0])) )
	{
		goto forestcomplete;
	}
	if (mevcut==1 && scoremax==0)
	{
		goto kokbul;
	}
	
	parent[hangi]=z;
	iter++;
	mevcut=iter;
	
	ban[0]++;
	ban[hangi]=1;
	
	list[0]++;
	list[list[0]]=hangi;
	
	ch[z][0]++;
	ch[z][ch[z][0]]=hangi;
	rank[hangi]=rank[z]+1;
	
	for(i=1;i<=k[hangi][0];i++)
	{
		if (au[k[hangi][i]]>rank[hangi])  
		{
			au[k[hangi][i]]=rank[hangi];
		}
	}
 	goto agacadevam;
	
forestcomplete:
	cnsay=0;
	for(i=1;i<=n;i++)
	if (k[i][0]>1 && rooted[i]==0)
	{
		kontrol=0;
		for(j=1;j<=ch[i][0];j++)
		{
			if (au[ch[i][j]]==rank[i]) kontrol=1;
		}
		if (kontrol==1) 
		{
			cnsay++;
			cutn[i]=1;
		}
	}
	for(i=1;i<=n;i++)
	if (rooted[i]==1)
	{
		if (ch[i][0]>1) 
		{
			cnsay++;
			cutn[i]=1;
		}
	}
	maxfark=0;
	for(i=1;i<=n;i++)
	{
		if (cutn[i]==1)
		{
			r_cnp=0;
			old_cnp=0;
			fark_cnp=0;
			cikar=0;
			z=i;
			while(parent[z]!=0)
			{
				z=parent[z];
			}
			for(j=1;j<=t[i][0];j++)
			{
				if ((au[ch[i][j]]==rank[i]))
				{
					r_cnp+= (t[i][j]*(t[i][j]-1)) /2;
					cikar+=t[i][j];
				}
				
			}
			ust_agac= ns[z]-cikar;
			r_cnp+=  	(ust_agac*(ust_agac-1))/ 2;
			old_cnp= ((ns[z]+1)*ns[z]) /2;
			fark=old_cnp-r_cnp;
			
			if (fark>maxfark)
			{
				maxfark=fark;
				sil_node=i;
			}
		}
	}
	if (maxfark==0)
	{
		for(i=1;i<=n;i++)
		{
			if (t[i][0]>maxfark)
			{
				maxfark=t[i][0];
				sil_node=i;
			}
		}
	
	}
	
	silnode[0]++;
	silnode[sil_node]=1;

	for(j=1;j<=n;j++)
	{
		a[j][sil_node]=0;
		a[sil_node][j]=0;
	}	
	
	for(i=0; i<=n; i++)
		for(j=0;j<=n;j++)
			k[i][j]=0;
	
	for(i=1; i<=n; i++)
		for(j=1;j<=n;j++)
		{
			if (a[i][j]==1)
			{
				k[i][0]++;
				k[i][k[i][0]]=j;
			}
		}

	if (silnode[0]<ck) goto sildevam;	

	parcala();
	
	clock_t end_time = clock();

    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Kodun calisma suresi: %.3f saniye\n", elapsed_time);
}
