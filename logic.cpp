#include<windows.h>
#include<bits/stdc++.h>
#define O(xx) (tr[tr[(xx)].fa].son[0]==(xx)?(xx)+1:(xx)-1)
#define ls tr[x].son[0]
#define rs tr[x].son[1]
using namespace std;
int read(){
	int x=0,f=1;char ch=getchar();
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=-1;
	for(;isdigit(ch);ch=getchar())x=x*10+ch-'0';
	return x*f;
}
const int N=(1<<14)+28;
struct WORK{
	int tot;
	struct NODE{
		int val,son[2],fa,mark,judge,turn;
		NODE(int v=0,int f=0,int t=0){val=v,fa=f,turn=t,mark=0,judge=0,son[0]=son[1]=0;}
	}tr[N];
	void dfs(int x,int round){
		if(round>12)return;
		int f=tr[x].fa;
		ls=++tot,rs=++tot;
		int t=6-tr[x].turn-tr[f].turn;
		tr[ls]=NODE(tr[x].val+tr[f].val,x,t),tr[rs]=NODE(abs(tr[x].val-tr[f].val),x,t);
		if(tr[x].val==tr[f].val)tr[ls].mark=x;
		tr[rs].val=abs(tr[x].val-tr[f].val);
		if(tr[x].mark==0&&tr[f].val==tr[rs].val)tr[x].mark=rs;
		if(tr[f].mark==0&&tr[x].val==tr[rs].val)tr[f].mark=rs;
	//	printf("#%d %d %d (%d,%d)\n",x,tr[x].val,tr[x].turn,ls,rs);
		dfs(ls,round+1);
		dfs(rs,round+1);
	}
	int now,know;
	int GetSame(int x){
		int t=tr[x].turn;
		x=tr[x].fa;
		while(x&&tr[x].turn!=t)x=tr[x].fa;
		if(x)return tr[x].val;
		return -1;
	}
	void dfs2(int x,int round){
		if(x==0||round>12)return;
		int t=tr[x].turn,f=tr[x].fa;
		if(tr[x].mark&&t==now&&!(tr[x].judge)){
			if(know==1)tr[tr[x].mark].judge=1,tr[O(tr[x].mark)].judge=-1;
			else tr[tr[x].mark].judge=-1,tr[O(tr[x].mark)].judge=1;
		}
		if(!(tr[x].judge)){
			dfs2(ls,round+1);
			dfs2(rs,round+1);
		}
		if(t==now){
			if(know==1){
				if(!(tr[x].judge)){
					tr[f].judge=-1;
					tr[O(f)].judge=1;
				}
			}else{
				if(tr[x].judge){
					tr[f].judge=-1;
					tr[O(f)].judge=1;
				}
			}
		}
		int num=GetSame(x);
		if(num==-1)return;
		if(tr[x].val==num){
			if(tr[x].judge==-1){
				tr[f].judge=-1;
				tr[O(f)].judge=1;
			}
		}else{
			if(tr[x].judge==1){
				tr[f].judge=-1;
				tr[O(f)].judge=1;
			}
		}
	}
	char s[4];
	queue<int>I,O;
	void Input(int x){I.push(x);}
	int In(){
		while(I.empty())Sleep(10);
		int re=I.front();
		I.pop();
		return re;
	}
	void Output(int x){O.push(x);}
	int Out(){
		while(O.empty())Sleep(10);
		int re=O.front();
		O.pop();
		return re;
	}
	signed Main(){
		int k=In();
		tr[++tot].val=In(),tr[++tot].val=In();
		if(k==1)tr[1].turn=2,tr[2].turn=3;
		if(k==2)tr[1].turn=1,tr[2].turn=3;
		if(k==3)tr[1].turn=1,tr[2].turn=2;
		tr[1].son[0]=2,tr[2].fa=1;
		dfs(2,1);
		int ans=0;
		for(int t=1;;t=(t==3?1:t+1)){
			if(tr[3].judge==1)ans=tr[3].val;
			else if(tr[4].judge==1)ans=tr[4].val;
			if(t==k){
				if(ans)Output(ans);
				else know=0,now=t,Output(0);
			}else know=In(),now=t;
			if(!ans)dfs2(1,0);
		}
	}
	WORK(){tot=0;}
}cct[3];
DWORD WINAPI Start(LPVOID lParam){
	WORK *x=(WORK*)lParam;
	x->Main();
}
signed main(){
	for(int i=0;i<3;i++){
		CreateThread(0,0,Start,cct+i,0,0);
		cct[i].Input(i+1);
		Sleep(10);
	}
	int ans[3]={read(),read(),read()},knew[3]={0,0,0};
	cct[0].Input(ans[1]),cct[0].Input(ans[2]);
	cct[1].Input(ans[0]),cct[1].Input(ans[2]);
	cct[2].Input(ans[0]),cct[2].Input(ans[1]);
	for(int t=1,r=1;r<=12;t=(t==3?1:t+1),r++){
		int know=cct[t-1].Out();
		printf("Round %d   %s",r,r<10?" ":"");
		if(know){
			if(know==ans[t-1])printf("No.%d gave the correct answer.\n",t);
			else printf("No.%d gave the wrong answer.\n",t);
			know=knew[t-1]=1;
		}else printf("No.%d didn't know.\n",t);
		if(knew[0]==1&&knew[1]==1&&knew[2]==1)break;
		for(int p=1;p<=3;p++){
			if(t==p)continue;
			cct[p-1].Input(know);
		}
	}
	puts("--------------------Dividing Line--------------------");
	for(int i=1;i<=3;i++){
		int t=i-1;
		if(knew[t])printf("No.%d finally knew.\n",i);
		else printf("No.%d will never know.\n",i);
	}
	puts("\n");
	system("pause");
	return 0;
}
/*
12 20 8

8 3 5

*/
