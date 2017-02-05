package whattheactualfact;

public class Constants 
{
	public static enum MachinesTypes
	{
		ELECTRONICS(0),DISPLAY(1),CASE(2),BATTERY(3);
		public int value;
		
		MachinesTypes(int value)
		{
			this.value=value;
		}
		public int getValue()
		{
			return this.value;
		}
		
		
	}
}
