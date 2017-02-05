package whattheactualfact;

public class SalesAndInventory
{
	public enum LaptopModels
	{
		X86V1,X86V2,X64V1,X64V2,X128V1
	}
	
	public int[] currentMonthSales=new int[5];
	public int[] currentStock=new int[5];
	public int[] currentSellPrice=new int[5];
	public int[] currentCostPrice=new int[5];
	
	public int[] inventory= new int[] {0,0,0,0};
	
	
	public LaptopModels model = null;
	
	public SalesAndInventory()
	{
		
	}
	
	public SalesAndInventory(LaptopModels _model)
	{
		this.model=_model;
	}

}
