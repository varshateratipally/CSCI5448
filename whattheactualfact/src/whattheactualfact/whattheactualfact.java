//Design patterns used: Builder 

package whattheactualfact;
import java.time.LocalDate;


//derive currentrequirement from formula based on machines
public class whattheactualfact
{
	public static LocalDate currentDate= LocalDate.now();
	
	
	public static void main(String[] args)
	{
		Employee George = new EmployeeBuilder().buildFirstName("George").buildEmployee();
		SalesAndInventory aaop= new SalesAndInventory();
		System.out.println(aaop.currentSellPrice[4]);
	}

}
