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
const int N=(1<<15)+28;
int tot;
struct NODE{
	int val,son[2],fa,mark,judge,turn;
	NODE(int v=0,int f=0,int t=0){val=v,fa=f,turn=t,mark=0,judge=0,son[0]=son[1]=0;}
}tr[N];
void dfs(int x,int round){
	if(round>4)return;
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
int k,st,now,know;
int GetSame(int x){
	int t=tr[x].turn;
	x=tr[x].fa;
	while(x&&tr[x].turn!=t)x=tr[x].fa;
	if(x)return tr[x].val;
	return -1;
}
void dfs2(int x,int round){
	if(x==0||round>4)return;
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
void debug(){
	puts("Debug");
	for(int i=1;i<=tot;i++){
		if(tr[i].judge==1)printf("$%d %d %d\n",i,tr[i].turn,tr[i].val);
		if(tr[i].mark)printf("%d(%d)[%d] connect to %d(%d)[%d]\n",
		i,tr[i].val,tr[i].turn,tr[i].mark,tr[tr[i].mark].val,tr[tr[i].mark].turn);
	}
}
char s[4];
signed main(){
	printf("Which one are you?(1/2/3)\n");
	k=read();
	printf("Please enter other two numbers.\n");
	tr[++tot].val=read(),tr[++tot].val=read();
	if(k==1)tr[1].turn=2,tr[2].turn=3;
	if(k==2)tr[1].turn=1,tr[2].turn=3;
	if(k==3)tr[1].turn=1,tr[2].turn=2;
	tr[1].son[0]=2;
	tr[2].fa=1;
	dfs(2,1);
	int ans=0;
	for(int t=1;;t=(t==3?1:t+1)){
		if(tr[3].judge==1)ans=tr[3].val;
		else if(tr[4].judge==1)ans=tr[4].val;
		if(t==k){
			if(ans)return printf("You are %d.\n",ans),0;
			else puts("You don't know."),know=0,now=t;
		}else{
			printf("Does No.%d know the number?(y/n)\n",t);
			scanf("%s",s);
			know=s[0]=='y',now=t;
		}
		if(!ans)dfs2(1,0);
//		debug();
	}
	return 0;
}
/*
1
8 12
n
n

2
20 12
n
n
y

3
20 8
n
n
y
y

*/
