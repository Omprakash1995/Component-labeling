kernel void component_labeling(const int h,const int w, const __global float* bitmap,const __global float *labelmap){
const int row=get_local_id(0);
const int col=get_local_id(1);
const int globalRow=2*get_group_id(0)+row;
const int globalCol=2*get_group_id(1)+col;
__local unsigned char bitmap_sub[h][2];
__local int labelmap_sub[h][2];
__local int labelindex=0,componentCount=0,tracingdirection;
__local char tracingstopflag=0,searchAgain=1;
__loacal int fx,fy,sx,sy,i,y,x,searchDirection[8][2]={{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};

Trace:
	for(i=0;i<7;i++)
	{
	 y=k+searchDirection[tracingdirection][0];
	 x=w+searchDirection[tracingdirection][1];
	 if(bitmap_sub[k][w]=='0')
	 {
	  labelmap_sub[y][x]=-1;
	  tracingdirection=(tracingdirection+1)%8;
	 }
	 else
	 {
	  k=y;
	  w=x;
 	  break;
	 }
	}
contourTracing:
	sx=w;sy=k;
	goto Trace;
	if(w!=sx||k!=sy)
	{
	 fx=w;
	 fy=k;
	 while(searchAgain)
	 {
	  tracingdirection=(tracingdirection+6)%8;
	  labelmap_sub[k][w]=labelindex;
	  goto Trace:
	  
	  if(w==sx&&k==sy)
	  {
	   tracingstopflag=1;
	  }
	  else if(tracingstopflag)
	  {
	   if(w==fx&&k==fy)
	   {
	    searchAgain=0;
	   } 
	   else 
	   {
 	    tracingstopflag=0;
	   }
	  }
	 }
	}
const int numTiles=w/2;
for(int t=0;t<numTiles;t++)
 {
  const int tiledRow=2*t+row;
  const int tiledCOl=2*t+col;
  bitmap_sub[col][row]=bitmap_sub[tiledCol*h+globalRow];
  labelmap_sub[col][row]=labelmap_sub[gloabalCOl*h+tiledRow];
 
  barrier(CLK_LOCAL_MEM_FENCE);

  for(int k=0;k<2;k++)
  {
    if(bitmap_sub[k][w]=='1')
    {
	if(labelindex!=0)
	{
	 labelmap_sub[k][w]=labelindex;
	}
	else
	{
	 labelindex=labelmap[k][w];
	 if(labelindex==0)
	 {
	  labelindex=++componentCount;
	  tracingdirection=0;
	  goto contourTracing;
	  labelmap_sub[k][w]=labelindex;
	 }     	 
	}
    }
    else if(labelindex!=0)
    {
	if(labelmap_sub[k][w]==0)
	{
	 tracingdirection=1;
	 goto contourTracing;
	}
    }
  }
   barrier(CLK_LOCAL_MEM_FENCE);
 }

}