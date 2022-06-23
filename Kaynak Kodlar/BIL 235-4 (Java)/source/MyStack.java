public class MyStack {
	public int top=-1;
	public int size;
	public MyStackElement starray[];
	public MyStack(int size)
	{
		this.size=size;
		starray =new  MyStackElement [size];
	}
	
	public void push(MyStackElement ele)
	{
		
		if(top!=size-1)
		{	
			top++;
			starray[top]=ele;
		}
		else{
			int i=0 ;
			while(i<size-1)
			{
				if(starray[i]==ele){
					while(i<size-1){
						starray[i]=starray[i+1];
						i++;
					}
				}
				i++;
			}
			starray[i-1]=ele;
		}
	}
	public MyStackElement pop()
	{
			return starray[top--];
	}
	public void flushstack() {
		top=0;
	}

}

